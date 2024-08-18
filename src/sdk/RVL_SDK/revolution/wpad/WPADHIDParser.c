#include "WPADHIDParser.h"

/*******************************************************************************
 * headers
 */

#include <errno.h>
#include <math.h>
#include <string.h>

#include <types.h>

#include "WPAD.h"
#include "WPADEncrypt.h"
#include <revolution/WPAD/WUD.h> // WUDIsLinkedWBC

#if 0
#include <revolution/OS/OS.h> // __OSInIPL
#include <revolution/OS/OSCrc.h> // OSCalcCRC32
#include <revolution/OS/OSInterrupt.h>
#endif

#include "context_bte.h" // UINT8
#include "context_rvl.h"

/*******************************************************************************
 * constants
 */

#define CONST_FLOAT_PI	3.141592f

// TODO: may want to move these to <WPAD/WPAD.h>?

#define DPD_MAX_X		0x3ff
#define DPD_MAX_Y		0x2ff

/*******************************************************************************
 * macros
 */

// clang-format off

/* WARNING: This macro cannot be wrapped in a do-while block because the
 * declaration of unusedBits_ would cause the stack to be referenced through r31
 * instead of r1 on debug, so take care when using.
 */
#define RETRIEVE_BUTTON_STATE(chan_, status_, dataPtr_, rptPtr_)				\
	memcpy(dataPtr_, __wpadGetLastRxBuffer(chan_), RX_BUFFER_SIZE);				\
																				\
	(status_) = (dataPtr_);														\
	u16 unusedBits_ = (status_)->button & 0x6000;								\
																				\
	(status_)->button = MAKE_BUTTON((rptPtr_)[RPT_BTN1], (rptPtr_)[RPT_BTN0]);	\
	(status_)->button |= unusedBits_;											\
																				\
	if ((status_)->dev != p_wpd->devType)										\
	{																			\
		(status_)->dev = p_wpd->devType;										\
		(status_)->err = WPAD_EINVAL;											\
	}																			\
																				\
	do {} while (0) // swallow semicolon

/*
 * Calibration (referred to as configuration)
 */

// IR camera (DPD)

// Accelerometer
#define MAKE_DEV_CONFIG_ACC_X(high_, low_)				((u16)(((u16)(high_) << 2) & 0xfffc) | (u16)(((u16)(low_) >> 4) & 0x0003))
#define MAKE_DEV_CONFIG_ACC_Y(high_, low_)				((u16)(((u16)(high_) << 2) & 0xfffc) | (u16)(((u16)(low_) >> 2) & 0x0003))
#define MAKE_DEV_CONFIG_ACC_Z(high_, low_)				((u16)(((u16)(high_) << 2) & 0xfffc) | (u16)( (u16)(low_)       & 0x0003))

// Assorted
#define MAKE_DEV_CONFIG_VOLUME(val_)					((val_) & (u8) 0x7f)
#define MAKE_DEV_CONFIG_MOTOR(val_)						((val_) & (u8)~0x7f)

// Nunchuk extension
#define MAKE_FS_CONFIG_ACC_X							MAKE_DEV_CONFIG_ACC_X
#define MAKE_FS_CONFIG_ACC_Y							MAKE_DEV_CONFIG_ACC_Y
#define MAKE_FS_CONFIG_ACC_Z							MAKE_DEV_CONFIG_ACC_Z

// Motion Plus extension
#define MAKE_MP_CONFIG_ZERO_VALUE(high_, low_)			(((u16)(((u16)(high_) << 8) & 0xff00) | (u16)((u16)(low_) & 0x00ff)) / 10.0f + 5000.0f)
#define MAKE_MP_CONFIG_SCALE_VALUE(high_, low_)			(((s16)(((u16)(high_) << 8) & 0xff00) | (s16)((u16)(low_) & 0x00ff)) / 10.0f)

#define RECALC_MP_CONFIG_SCALE_VALUE(val_)				(val_) = (val_) < 0.0f ? (val_) - 4000.0f : (val_) + 4000.0f

#define MAKE_MPLS_CONFIG_ID(high_, low_)				((u16)((u16)((u16)(high_) << 8) & 0xff00) | (u16)((u16)(low_) & 0x00ff))

/*
 * Data reports
 */

// Buttons
#define MAKE_BUTTON(high_, low_)						((u16)((u16)((u16)((u16)(low_) & 0x00ff)) | (u16)((u16)((high_) << 8) & 0xff00)) & WPAD_BUTTON_ALL)

// Standard accelerometer report
#define MAKE_ACC_STANDARD_X(wpadcb_, high_, low_)		((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)(u16)((low_) >> 5) & 0x03)) - (s16)((wpadcb_)->devConfig.accX0g))
#define MAKE_ACC_STANDARD_Y(wpadcb_, high_, low_)		((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)(u16)((low_) >> 4) & 0x02)) - (s16)((wpadcb_)->devConfig.accY0g))
#define MAKE_ACC_STANDARD_Z(wpadcb_, high_, low_)		((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)(u16)((low_) >> 5) & 0x02)) - (s16)((wpadcb_)->devConfig.accZ0g))

// Interleaved accelerometer reports
#define MAKE_ACC_INTERLEAVED0_X(wpadcb_, high_, low_)	         ((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)(u16)((low_) >> 6) & 0x02)) - (s16)((wpadcb_)->devConfig.accX0g))
#define CALC_ACC_INTERLEAVED0_Z(val_, high_, low_)		(val_) |= (s16)((s16)((s16)((s16)(high_) << 3) & ~0xff) | (s16)((s16)(u16)((low_) << 1) & 0xc0))

#define MAKE_ACC_INTERLEAVED1_Y(wpadcb_, high_, low_)	         ((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)(u16)((low_) >> 6) & 0x02)) - (s16)((wpadcb_)->devConfig.accY0g))
#define CALC_ACC_INTERLEAVED1_Z(val_, high_, low_)		(val_) |= (s16)((s16)((s16)((s16)(high_) >> 1) &  0x30) | (s16)((s16)(u16)((low_) >> 3) & 0x0c))

// Basic IR camera report
#define GET_DPD_BASIC_REPORT_X_LOW_BYTE(data_, i_)		((u8 *)((u32)data_ + ((i_) * 3) - ((i_) / 2)))[0]
#define GET_DPD_BASIC_REPORT_Y_LOW_BYTE(data_, i_)		((u8 *)((u32)data_ + ((i_) * 3) - ((i_) / 2)))[1]
#define GET_DPD_BASIC_REPORT_XY_HIGH_BITS(data_, i_)	((u8 *)((u32)data_ +         5  * ((i_) / 2)))[2]

#define MAKE_DPD_BASIC_X1(high_, low_)					                  ((s16)((low_) & 0xff) | (u16)((u16)((u16)(high_) & 0x30) << 4))
#define MAKE_DPD_BASIC_Y1(high_, low_)					(DPD_MAX_Y - (s16)((s16)((low_) & 0xff) | (u16)((u16)((u16)(high_) & 0xc0) << 2)))
#define MAKE_DPD_BASIC_X2(high_, low_)					                  ((s16)((low_) & 0xff) | (u16)((u16)((u16)(high_) & 0x03) << 8))
#define MAKE_DPD_BASIC_Y2(high_, low_)					(DPD_MAX_Y - (s16)((s16)((low_) & 0xff) | (u16)((u16)((u16)(high_) & 0x0c) << 6)))

// Standard IR camera report
#define MAKE_DPD_STANDARD_X(high_, low_)				                  ((s16)((low_) & 0xff) | (u16)(((u16)(high_) & 0x30) << 4))
#define MAKE_DPD_STANDARD_Y(high_, low_)				(DPD_MAX_Y - (s16)((s16)((low_) & 0xff) | (u16)(((u16)(high_) & 0xc0) << 2)))
#define MAKE_DPD_STANDARD_SIZE(byte_)					                  ((u8)((byte_) & 0x0f) & 0xffff)

#define RECALC_DPD_STANDARD_SIZE(size_)					(size_) = (u8)((f32)(size_) * (f32)(size_) * CONST_FLOAT_PI)

// Extended IR camera report
#define MAKE_DPD_EXTENDED_X(high_, low_)				                  ((s16)((low_) & 0xff) | (u16)((u16)((high_) & 0x30) << 4))
#define MAKE_DPD_EXTENDED_Y(high_, low_)				(DPD_MAX_Y - (s16)((s16)((low_) & 0xff) | (u16)((u16)((high_) & 0xc0) << 2)))
#define MAKE_DPD_EXTENDED_PIXEL(high_, low_)			(u16)((s16)((s16)(((u16)(high_) << 8 ) & 0xff00) | (u16)((low_) & 0xff)) << 6)
#define MAKE_DPD_EXTENDED_RADIUS(data_)					((data_) & 0x0f)

#define CALC_DPD_EXTENDED_X(x_)							(x_) = (x_) << 3
#define CALC_DPD_EXTENDED_Y(y_)							(y_) = (DPD_MAX_Y - (s16)((y_) << 3))
#define MAKE_DPD_EXTENDED_SIZE(radius_)					((f32)(radius_) * (f32)(radius_) * CONST_FLOAT_PI)

// Nunchuk extension report
#define MAKE_FS_ACC_X(wpadcb_, high_, low_)				((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((low_) >> 2) & 0x03)) - (s16)((wpadcb_)->extConfig.fs.accX0g))
#define MAKE_FS_ACC_Y(wpadcb_, high_, low_)				((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((low_) >> 4) & 0x03)) - (s16)((wpadcb_)->extConfig.fs.accY0g))
#define MAKE_FS_ACC_Z(wpadcb_, high_, low_)				((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((low_) >> 6) & 0x03)) - (s16)((wpadcb_)->extConfig.fs.accZ0g))

#define CALC_FS_BUTTON(button_, data_)					(button_) |= (u16)((((u16)~(data_)) << 13) & 0x6000)

#define CLAMP_FS_STICK_X(wpadcb_, x_)					(x_) = __clamp((u8)(x_) - (u8)(wpadcb_)->extConfig.fs.stickXCenter, -128, 127)
#define CLAMP_FS_STICK_Y(wpadcb_, y_)					(y_) = __clamp((u8)(y_) - (u8)(wpadcb_)->extConfig.fs.stickYCenter, -128, 127)

// Classic Controller extension reports
#define CLAMP_CL_STICK_LX(wpadcb_, lx_, low_, high_)	(lx_) = __clamp((lx_) - (wpadcb_)->extConfig.cl.lStickXCenter, (low_), (high_))
#define CLAMP_CL_STICK_LY(wpadcb_, ly_, low_, high_)	(ly_) = __clamp((ly_) - (wpadcb_)->extConfig.cl.lStickYCenter, (low_), (high_))
#define CLAMP_CL_STICK_RX(wpadcb_, rx_, low_, high_)	(rx_) = __clamp((rx_) - (wpadcb_)->extConfig.cl.rStickXCenter, (low_), (high_))
#define CLAMP_CL_STICK_RY(wpadcb_, ry_, low_, high_)	(ry_) = __clamp((ry_) - (wpadcb_)->extConfig.cl.rStickYCenter, (low_), (high_))

#define MAKE_CL_BUTTON(high_, low_)						((u16)((u16)(((u16)((u16)(high_) << 8) & 0xff00) | (u8)(low_)) ^ 0xffff))

// Reduced Classic Controller extension report
#define MAKE_CL_REDUCED_STICK_LX(byte_)					((s16)((byte_) & 0x3f) << 4)
#define MAKE_CL_REDUCED_STICK_LY(byte_)					((s16)((byte_) & 0x3f) << 4)
// Hey Fellas Make Sure This Is A Signed Short
#define MAKE_CL_REDUCED_STICK_RX(high_, mid_, low_)		((s16)((s16)((s16)((s16)((s16)(high_) >> 3) & 0x18) | (s16)((s16)((s16)(mid_) >> 5) & 0x06) | (s16)((s16)((s16)(low_) >> 7) & 0x01)) << 5))
#define MAKE_CL_REDUCED_STICK_RY(byte_)					((s16)((byte_) & 0x1f) << 5)

#define MAKE_CL_REDUCED_TRIGGER_L(high_, low_)			((u8)((u8)((u8)((u8)((high_) >> 2) & 0x18) | (u8)((u8)((low_) >> 5) & 0x07)) << 3))
#define MAKE_CL_REDUCED_TRIGGER_R(byte_)				((u8)((u8)(byte_) & 0x1f) << 3)

// Standard Classic Controller extension report
#define MAKE_CL_STANDARD_STICK_AXIS(byte_)				((s16)((byte_) & 0xff) << 2)

#define MAKE_CL_STANDARD_STICK_LX						MAKE_CL_STANDARD_STICK_AXIS
#define MAKE_CL_STANDARD_STICK_LY						MAKE_CL_STANDARD_STICK_AXIS
#define MAKE_CL_STANDARD_STICK_RX						MAKE_CL_STANDARD_STICK_AXIS
#define MAKE_CL_STANDARD_STICK_RY						MAKE_CL_STANDARD_STICK_AXIS

// Extended Classic Controller extension report
#define MAKE_CL_EXTENDED_STICK_LX(high_, low_)			((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)(      (s16)(low_)       & 0x03))
#define MAKE_CL_EXTENDED_STICK_LY(high_, low_)			((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((s16)(low_) >> 4) & 0x03))
#define MAKE_CL_EXTENDED_STICK_RX(high_, low_)			((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((s16)(low_) >> 2) & 0x03))
#define MAKE_CL_EXTENDED_STICK_RY(high_, low_)			((s16)((s16)((s16)(high_) << 2) & ~0x03) | (s16)((s16)((s16)(low_) >> 6) & 0x03))

// Shinkansen train controller extension report
#define MAKE_TR_BUTTON									MAKE_CL_BUTTON

// Balance Board extension report
#define MAKE_BL_WEIGHT(high_, low_)						((u16)((u16)((high_) << 8) & 0xff00) | (u16)((low_) & 0x00ff))

#define MAKE_BL_WEIGHT_UL								MAKE_BL_WEIGHT
#define MAKE_BL_WEIGHT_UR								MAKE_BL_WEIGHT
#define MAKE_BL_WEIGHT_DL								MAKE_BL_WEIGHT
#define MAKE_BL_WEIGHT_DR								MAKE_BL_WEIGHT

// VSM extension report
/* The extension this report is for is unknown, but was suggested to possibly be
 * the cancelled Vitality Sensor by NWPlayer123.
 */
#define MAKE_VS_SET_0(high_, low_)						((u16)((u16)((u16)(high_) << 2) & 0xfffc) | (u16)((u16)((low_) >> 6) & 0x0003))
#define MAKE_VS_SET_1(high_, low_)						((u16)((u16)((u16)(high_) << 2) & 0xfffc) | (u16)((u16)((low_) >> 4) & 0x0003))
#define MAKE_VS_SET_2(high_, low_)						((u16)((u16)((u16)(high_) << 2) & 0xfffc) | (u16)((u16)((low_) >> 2) & 0x0003))
#define MAKE_VS_SET_3(high_, low_)						((u16)((u16)((u16)(high_) << 2) & 0xfffc) | (u16)((u16)((low_) >> 0) & 0x0003))
#define MAKE_VS_SET_4(high_, low_)						((u16)((u16)((u16)(high_) << 2) & 0xfffc) | (u16)((u16)((low_) >> 6) & 0x0003)) // same as MAKE_VS_SET_1

#define MAKE_VS_42(high_, low_)							((u16)((u16)((u16)((u16)(high_) << 4) & 0xf3f0)) | (u16)((u16)((low_) >> 2) & 0x000f))

#define MAKE_VS_44(byte_)								((u8)((u8)(byte_) & 0x03))

// Motion Plus extension reports

// Motion Plus non-passthrough acc/gyro report
#define MAKE_MP_MAIN_STAT(high_, low_)					((u8)((u8)((u8)((high_) << 2) & 0x0c) | (u8)((u8)(low_) & 0x03)) | WPAD_MPLS_STATUS_DATA_VALID)
#define MAKE_MP_MAIN_PITCH(high_, low_)					(s16)((low_) & 0x00ff) | (s16)((s16)((high_) << 6) & 0x3f00)
#define MAKE_MP_MAIN_YAW(high_, low_)					(s16)((low_) & 0x00ff) | (s16)((s16)((high_) << 6) & 0x3f00)
#define MAKE_MP_MAIN_ROLL(high_, low_)					(s16)((low_) & 0x00ff) | (s16)((s16)((high_) << 6) & 0x3f00)

// Motion Plus passthrough main acc/gyro report
#define CALC_MP_PT_MAIN_BUTTON(button_, cbBox_)			(button_) |= (u16)((cbBox_)->button & 0x6000)
#define MAKE_MP_PT_MAIN_STAT(high_, low_)				((u8)((u8)((u8)((high_) << 2) & 0x0c) | (u8)((u8)(low_) & 3)) | WPAD_MPLS_STATUS_DATA_VALID)
#define MAKE_MP_PT_MAIN_PITCH							MAKE_MP_MAIN_PITCH
#define MAKE_MP_PT_MAIN_YAW								MAKE_MP_MAIN_YAW
#define MAKE_MP_PT_MAIN_ROLL							MAKE_MP_MAIN_ROLL

#define RECALC_MP_PT_MAIN_STAT(stat_, cbBox_)			(stat_) |= (u8)((cbBox_)->stat & WPAD_MPLS_STATUS_EXTENSION_DATA_VALID)

// Motion Plus passthrough extension report
#define CALC_MP_PT_EXT_STAT(stat_, val_)				(stat_) |= (u8)((u8)((val_) & 0x01) | WPAD_MPLS_STATUS_EXTENSION_DATA_VALID)

// Motion Plus Nunchuk passthrough report
#define MAKE_MP_FS_ACC_X(wpadcb_, high_, low_)			((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | ((s16)((s16)((low_) >> 3) & 0x02))) - (s16)(wpadcb_)->extConfig.fs.accX0g)
#define MAKE_MP_FS_ACC_Y(wpadcb_, high_, low_)			((s16)((s16)((s16)((s16)(high_) << 2) & ~0x03) | ((s16)((s16)((low_) >> 4) & 0x02))) - (s16)(wpadcb_)->extConfig.fs.accY0g)
#define MAKE_MP_FS_ACC_Z(wpadcb_, high_, low_)			((s16)((s16)((s16)((s16)(high_) << 2) & ~0x07) | ((s16)((s16)((low_) >> 5) & 0x06))) - (s16)(wpadcb_)->extConfig.fs.accZ0g)

#define CALC_MP_FS_BUTTON(button_, data_)				(button_) |= (u16)((((u16)~(data_)) << 11) & WPAD_BUTTON_FS_ALL)

// Motion Plus Classic Controller passthrough report
#define MAKE_MP_CL_STICK_LX(val_)						((s16)((val_) & 0x3e) << 4)
#define MAKE_MP_CL_STICK_LY(val_)						((s16)((val_) & 0x3e) << 4)
#define MAKE_MP_CL_STICK_RX(high_, mid_, low_)			((s16)((s16)((s16)((s16)(high_) >> 3) & 0x18) | (s16)((s16)((s16)(mid_) >> 5) & 0x06) | (s16)((s16)((s16)(low_) >> 7) & 0x01)) << 5)
#define MAKE_MP_CL_STICK_RY(val_)						((s16)((val_) & 0x1f) << 5)
#define MAKE_MP_CL_TRIGGER_L(high_, low_)				((u8)((u8)((u8)((high_) >> 2) & 0x18) | (u8)((u8)((low_) >> 5) & 0x07)) << 3)
#define MAKE_MP_CL_TRIGGER_R(val_)						((u8)((u8)(val_) & 0x1f) << 3)
#define MAKE_MP_CL_BUTTON(high_, low_, up_, left_)		((u16)(((u16)((u16)(high_) << 8) & 0xfe00) | ((low_) & 0xfc) | (((u16)(left_) << 1) & 0x02) | ((up_) & 0x01)) ^ WPAD_BUTTON_CL_ALL)

// Button report
#define __parse_btn_data(wpadcb_, status_, btnFormat_, data_, length_)				\
	do																				\
	{																				\
		(status_)->button = MAKE_BUTTON((data_)[RPT_BTN1], (data_)[RPT_BTN0]);		\
																					\
		if ((btnFormat_) == BTN_FORMAT_STANDARD)									\
			(wpadcb_)->wpInfo.nearempty = (u8)(((data_)[RPT_BTN0] & 0x80) >> 7);	\
		else if ((btnFormat_) == BTN_FORMAT_INTERLEAVED)							\
			(wpadcb_)->wpInfo.nearempty = FALSE;									\
	} while (0)

// clang-format on

/*******************************************************************************
 * types
 */

typedef u8 ChecksumType;
enum ChecksumType_et
{
	CHECKSUM_SIMPLE_SUM,
	CHECKSUM_CRC32,
};

typedef u8 MplsConfigDataType;
enum MplsConfigDataType_et
{
	MPLS_CALIB_TYPE_HIGH,
	MPLS_CALIB_TYPE_LOW,
};

enum
{
	// Dummy button formats (for use in the __parse_btn_data macro)
	BTN_FORMAT_STANDARD		= 0,
	BTN_FORMAT_INTERLEAVED	= 1,

	// Accelerometer data format
	ACC_FORMAT_STANDARD		= 0,
	ACC_FORMAT_INTERLEAVED0	= 1,
	ACC_FORMAT_INTERLEAVED1	= 2,
};

typedef void InputReportParser(u8 chan, byte_t *hidReport, void *rxBuffer);

/*******************************************************************************
 * local function declarations
 */

static void __wpadAbortInitExtension(WPADChannel chan, WPADResult result);
static void __wpadGetDevConfig(WPADChannel chan, WPADResult result);
static BOOL __wpadCheckCalibration(byte_t *data, u8 checksumOffset,
                                   ChecksumType checksumType);
static void __wpadGetFsConfig(WPADChannel chan, byte_t *config);
static void __wpadGetClConfig(WPADChannel chan, byte_t *config);
static void __wpadGetMpConfig(WPADChannel chan, byte_t *config,
                              MplsConfigDataType type);
static void __wpadGetExtConfig(WPADChannel chan, WPADResult result);
static void __wpadGetExtConfig2(WPADChannel chan, WPADResult result);
static BOOL __wpadIsExtEncryptMain(u8 type);
static void __wpadGetExtType(WPADChannel chan, WPADResult result);
static void __wpadGetExtType2(WPADChannel chan, WPADResult result);
static void __wpadGetGameInfo(WPADChannel chan, WPADResult result, u8);
static void __wpadInitExtension(WPADChannel chan);
static void __wpadInvertRxBuffer(u8 chan);
static void *__wpadGetWorkRxBuffer(u8 chan);
static void *__wpadGetLastRxBuffer(u8 chan);
static void __wpadCheckDataFormat(u8 chan, u8 rep_id, void *data);

static void __a1_20_status_report(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_21_user_data(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_22_ack(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __parse_dpd_data(WPADChannel chan, WPADStatus **status,
                             u8 dpdCommand, byte_t *data, u8 length);
static void __parse_dpdex_data(WPADChannel chan, WPADStatusEx **statusEx,
                               u8 objIndex, byte_t *data, u8 length);
static void __parse_acc_data(WPADChannel chan, WPADStatus **status,
                             u8 accFormat, byte_t *data, u8 length);
static s16 __clamp(s16 x, s16 low, s16 high);
static void __parse_fs_data(WPADChannel chan, WPADFSStatus **fsStatus,
                            u8 fsFormat, byte_t *data, u8 length);
static void __parse_cl_data(WPADChannel chan, WPADCLStatus **clStatus,
                            u8 clFormat, byte_t *data, u8 length);
static void __parse_bk_data(WPADChannel chan, WPADBKStatus **bkStatus,
                            u8 bkFormat, byte_t *data, u8 length);
static void __parse_tr_data(WPADChannel chan, WPADTRStatus **trStatus,
                            u8 trFormat, byte_t *data, u8 length);
static void __parse_bl_data(WPADChannel chan, WPADBLStatus **blStatus,
                            u8 blFormat, byte_t *data, u8 length);
static void __parse_vs_data(WPADChannel chan, WPADVSStatus **vsStatus,
                            u8 vsFormat, byte_t *data, u8 length);
static void __parse_mp_data(WPADChannel chan, WPADMPStatus **mpStatus,
                            u8 mpFormat, byte_t *data, u8 length);
static void __parse_ext_data(WPADChannel chan, void *parseBuf, u8 dataFormat,
                             byte_t *data, u8 length);
static void __a1_30_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_31_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_32_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_33_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_34_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_35_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_36_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_37_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_3d_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_3e_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_3f_data_type(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __a1_unused_report(u8 chan, byte_t *hidReport, void *rxBuffer);
static void __wpadCertReset(WPADChannel chan);

/*******************************************************************************
 * variables
 */

// .rodata

// clang-format off
static const byte_t _cExtInvalidData[RPT_MAX_SIZE] =
{
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const byte_t _cExtInvalidData2[RPT_MAX_SIZE] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// clang-format on

// .data

// clang-format off
static InputReportParser *__a1_input_reports_array[] =
{
	// double-indented entries are the used ones

		&__a1_20_status_report,
		&__a1_21_user_data,
		&__a1_22_ack,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
		&__a1_30_data_type,
		&__a1_31_data_type,
		&__a1_32_data_type,
		&__a1_33_data_type,
		&__a1_34_data_type,
		&__a1_35_data_type,
		&__a1_36_data_type,
		&__a1_37_data_type,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
	&__a1_unused_report,
		&__a1_3d_data_type,
		&__a1_3e_data_type,
		&__a1_3f_data_type,
};
// clang-format on

// .bss
static f32 _wpadCalibrationX[WPAD_MAX_CONTROLLERS];
static f32 _wpadCalibrationY[WPAD_MAX_CONTROLLERS];
static f32 _wpadCenterX[WPAD_MAX_CONTROLLERS];
static f32 _wpadCenterY[WPAD_MAX_CONTROLLERS];
static f32 _wpadRolag[WPAD_MAX_CONTROLLERS];

// .sbss
static u8 _wpadDevType[WPAD_MAX_CONTROLLERS];
static u8 _wpadDevMode[WPAD_MAX_CONTROLLERS];
static u8 _wpadDevType2[WPAD_MAX_CONTROLLERS];
static u8 _wpadDevType2Sub[WPAD_MAX_CONTROLLERS];
static u8 _wpadCLCompt[WPAD_MAX_CONTROLLERS];
static u8 _wpadExtInitRetryCnt[WPAD_MAX_CONTROLLERS];

/*******************************************************************************
 * functions
 */

static void __wpadAbortInitExtension(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (result == WPAD_ESUCCESS)
		return;

	WPADiClearQueue(&p_wpd->extCmdQueue);
	p_wpd->extState = WPAD_STATE_EXT_UNINITIALIZED;

	s32 devType;
	if (result == WPAD_ENODEV)
	{
		devType = WPAD_DEV_NONE;
	}
	else if (p_wpd->wpInfo.attach)
	{
		if (_wpadExtInitRetryCnt[chan]++ < 32)
		{
			__wpadInitExtension(chan);
			return;
		}
		else
		{
			devType = WPAD_DEV_252;
		}
	}
	else
	{
		WPADiSendSetReportType(&p_wpd->extCmdQueue, p_wpd->dataFormat,
		                       p_wpd->disableContReport, NULL);
		return;
	}

	p_wpd->devType = devType;
	p_wpd->savedDevType = p_wpd->devType;
	p_wpd->extWasDisconnected = FALSE;

	if (p_wpd->extensionCB)
		(*p_wpd->extensionCB)(chan, devType);
}

static void __wpadGetDevConfig(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];
	byte_t *data = p_wpd->wmReadDataPtr;

	u8 checksum;
	u8 i;
	int j;
	int index;

	f32 x, y;
	f32 x_atan, y_atan;

	DPDObject obj[WPAD_MAX_DPD_OBJECTS];
	f32 a[WPAD_MAX_DPD_OBJECTS];
	f32 b[WPAD_MAX_DPD_OBJECTS];
	f32 c[WPAD_MAX_DPD_OBJECTS];
	f32 d[WPAD_MAX_DPD_OBJECTS];
	s16 defaultDpdX[WPAD_MAX_DPD_OBJECTS] = {127, 896, 896, 127};
	s16 defaultDpdY[WPAD_MAX_DPD_OBJECTS] = {93, 93, 674, 674};

	for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
	{
		p_wpd->devConfig.dpd[i].x = (s16)defaultDpdX[i];
		p_wpd->devConfig.dpd[i].y = (s16)defaultDpdY[i];
		p_wpd->devConfig.dpd[i].size = p_wpd->defaultDpdSize;
		p_wpd->devConfig.dpd[i].traceId = i;
	}

	p_wpd->devConfig.accX0g = 530;
	p_wpd->devConfig.accY0g = 530;
	p_wpd->devConfig.accZ0g = 530;

	p_wpd->devConfig.accX1g = 636;
	p_wpd->devConfig.accY1g = 636;
	p_wpd->devConfig.accZ1g = 636;

	p_wpd->devConfig.volume = 0;
	p_wpd->devConfig.motor = 0;

	if (result != WPAD_ESUCCESS)
		return;

	if (p_wpd->configIndex == 0)
	{
		for (i = 0; i < WPAD_MAX_CONFIG_BLOCKS; i++)
		{
			checksum = 0;
			index = i * WPAD_DPD_CONFIG_BLOCK_SIZE;

			for (j = index; j < index + WPAD_DPD_CONFIG_BLOCK_CHECKSUM; j++)
				checksum += data[j];

			checksum += WPAD_CONFIG_BLOCK_CHECKSUM_BIAS;
			if (checksum != data[index + WPAD_DPD_CONFIG_BLOCK_CHECKSUM])
				continue;

			obj[0].x = MAKE_DPD_BASIC_X1(data[index + 2], data[index + 0]);
			obj[0].y = MAKE_DPD_BASIC_Y1(data[index + 2], data[index + 1]);
			obj[0].size = p_wpd->defaultDpdSize;
			obj[0].traceId = 0;

			obj[1].x = MAKE_DPD_BASIC_X2(data[index + 2], data[index + 3]);
			obj[1].y = MAKE_DPD_BASIC_Y2(data[index + 2], data[index + 4]);
			obj[1].size = p_wpd->defaultDpdSize;
			obj[1].traceId = 1;

			obj[2].x = MAKE_DPD_BASIC_X1(data[index + 7], data[index + 5]);
			obj[2].y = MAKE_DPD_BASIC_Y1(data[index + 7], data[index + 6]);
			obj[2].size = p_wpd->defaultDpdSize;
			obj[2].traceId = 2;

			obj[3].x = MAKE_DPD_BASIC_X2(data[index + 7], data[index + 8]);
			obj[3].y = MAKE_DPD_BASIC_Y2(data[index + 7], data[index + 9]);
			obj[3].size = p_wpd->defaultDpdSize;
			obj[3].traceId = 3;

			for (j = 0; j < WPAD_MAX_DPD_OBJECTS; j++)
			{
				if (obj[j].x < 0x200 && obj[j].y < 0x180)
				{
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BL].x = obj[j].x;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BL].y = obj[j].y;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BL].size = obj[j].size;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BL].traceId =
						obj[j].traceId;
				}

				if (obj[j].x > 0x200 && obj[j].y < 0x180)
				{
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BR].x = obj[j].x;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BR].y = obj[j].y;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BR].size = obj[j].size;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_BR].traceId =
						obj[j].traceId;
				}

				if (obj[j].x > 0x200 && obj[j].y > 0x180)
				{
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TR].x = obj[j].x;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TR].y = obj[j].y;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TR].size = obj[j].size;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TR].traceId =
						obj[j].traceId;
				}

				if (obj[j].x < 0x200 && obj[j].y > 0x180)
				{
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TL].x = obj[j].x;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TL].y = obj[j].y;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TL].size = obj[j].size;
					p_wpd->devConfig.dpd[DPD_CFG_OBJ_TL].traceId =
						obj[j].traceId;
				}
			}

			break;
		}
	}

	x = y = 0.0f;
	for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
	{
		a[i] = p_wpd->devConfig.dpd[i].x;
		b[i] = p_wpd->devConfig.dpd[i].y;
		x += p_wpd->devConfig.dpd[i].x - defaultDpdX[i];
		y += p_wpd->devConfig.dpd[i].y - defaultDpdY[i];
	}

	// NOTE: specifically not a compound assignment
	x = x / 4.0f;
	y = y / 4.0f;

	x_atan = (f32)atan((x + 126.5f) / 1332.5f) - (f32)atan(0.09493433684110641);
	y_atan = (f32)atan((y + 93.0f) / 1337.4f) - (f32)atan(0.06953790783882141);

	_wpadCalibrationX[chan] = (f32)tan(x_atan) * -1.0f * 1332.5f;
	_wpadCalibrationY[chan] = (f32)tan(y_atan) * -1.0f * 1337.4f;
	_wpadCenterX[chan] = _wpadCenterY[chan] = 0.0f;

	for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
	{
		a[i] += _wpadCalibrationX[chan];
		b[i] += _wpadCalibrationY[chan];

		_wpadCenterX[chan] += a[i];
		_wpadCenterY[chan] += b[i];
	}

	// NOTE: specifically not a compound assignment
	_wpadCenterX[chan] = _wpadCenterX[chan] / 4.0f;
	_wpadCenterY[chan] = _wpadCenterY[chan] / 4.0f;

	_wpadRolag[chan] = 0;

	for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
	{
		c[i] = atan((b[i] - _wpadCenterY[chan]) / (a[i] - _wpadCenterX[chan]));
		d[i] = atan((defaultDpdY[i] - 383.5f) / (defaultDpdX[i] - 511.5f));

		_wpadRolag[chan] += c[i] - d[i];
	}

	_wpadRolag[chan] = _wpadRolag[chan] / 4.0f;

	for (i = 0; i < WPAD_MAX_CONFIG_BLOCKS; i++)
	{
		checksum = 0;
		index = i * WPAD_DEV_CONFIG_BLOCK_SIZE;
		if (p_wpd->configIndex == 0)
			index += WPAD_DPD_CONFIG_BLOCK_SIZE * WPAD_MAX_CONFIG_BLOCKS;

		for (j = index; j < index + WPAD_DEV_CONFIG_BLOCK_CHECKSUM; j++)
			checksum += data[j];

		checksum += WPAD_CONFIG_BLOCK_CHECKSUM_BIAS;

		if (checksum != data[index + WPAD_DEV_CONFIG_BLOCK_CHECKSUM])
			continue;

		p_wpd->devConfig.accX0g =
			MAKE_DEV_CONFIG_ACC_X(data[index + 0], data[index + 3]);
		p_wpd->devConfig.accY0g =
			MAKE_DEV_CONFIG_ACC_Y(data[index + 1], data[index + 3]);
		p_wpd->devConfig.accZ0g =
			MAKE_DEV_CONFIG_ACC_Z(data[index + 2], data[index + 3]);

		p_wpd->devConfig.accX1g =
			MAKE_DEV_CONFIG_ACC_X(data[index + 4], data[index + 7]);
		p_wpd->devConfig.accY1g =
			MAKE_DEV_CONFIG_ACC_Y(data[index + 5], data[index + 7]);
		p_wpd->devConfig.accZ1g =
			MAKE_DEV_CONFIG_ACC_Z(data[index + 6], data[index + 7]);

		p_wpd->devConfig.volume = MAKE_DEV_CONFIG_VOLUME(data[index + 8]);
		p_wpd->devConfig.motor = MAKE_DEV_CONFIG_MOTOR(data[index + 8]);

		break;
	}
}

static BOOL __wpadCheckCalibration(byte_t *data, u8 checksumOffset,
                                   ChecksumType checksumType)
{
	BOOL success = FALSE;
	u32 crc = 0;

	u8 i;
	if (checksumType == CHECKSUM_SIMPLE_SUM)
	{
		for (i = 0; i < checksumOffset; i++)
			crc += data[i];

		if ((u8)(crc + 0x55) == data[checksumOffset]
		    && (u8)(crc + 0xaa) == data[checksumOffset + 1])
		{
			success = TRUE;
		}
	}
	else
	{
		crc = OSCalcCRC32(data, checksumOffset);

		if (crc == *(u32 *)&data[checksumOffset])
			success = TRUE;
	}

	return success;
}

static void __wpadGetFsConfig(WPADChannel chan, byte_t *config)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->extConfig.fs.accX0g = MAKE_DEV_CONFIG_ACC_X(config[0], config[3]);
	p_wpd->extConfig.fs.accY0g = MAKE_DEV_CONFIG_ACC_Y(config[1], config[3]);
	p_wpd->extConfig.fs.accZ0g = MAKE_DEV_CONFIG_ACC_Z(config[2], config[3]);

	p_wpd->extConfig.fs.accX1g = MAKE_DEV_CONFIG_ACC_X(config[4], config[7]);
	p_wpd->extConfig.fs.accY1g = MAKE_DEV_CONFIG_ACC_Y(config[5], config[7]);
	p_wpd->extConfig.fs.accZ1g = MAKE_DEV_CONFIG_ACC_Z(config[6], config[7]);

	p_wpd->extConfig.fs.at_0x04 = (s8)config[8];
	p_wpd->extConfig.fs.at_0x02 = (s8)config[9];
	p_wpd->extConfig.fs.at_0x0a = (s8)config[11];
	p_wpd->extConfig.fs.at_0x08 = (s8)config[12];

	if (!p_wpd->calibrated)
	{
		p_wpd->extConfig.fs.stickXCenter = (s8)config[10];
		p_wpd->extConfig.fs.stickYCenter = (s8)config[13];
	}
}

static void __wpadGetClConfig(WPADChannel chan, byte_t *config)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->extConfig.cl.at_0x04 = (s8)config[0];
	p_wpd->extConfig.cl.at_0x02 = (s8)config[1];
	p_wpd->extConfig.cl.at_0x0a = (s8)config[3];
	p_wpd->extConfig.cl.at_0x08 = (s8)config[4];
	p_wpd->extConfig.cl.at_0x10 = (s8)config[6];
	p_wpd->extConfig.cl.at_0x0e = (s8)config[7];
	p_wpd->extConfig.cl.at_0x16 = (s8)config[9];
	p_wpd->extConfig.cl.at_0x14 = (s8)config[10];

	if (!p_wpd->calibrated)
	{
		p_wpd->extConfig.cl.lStickXCenter = (s8)config[2];
		p_wpd->extConfig.cl.lStickYCenter = (s8)config[5];
		p_wpd->extConfig.cl.rStickXCenter = (s8)config[8];
		p_wpd->extConfig.cl.rStickYCenter = (s8)config[11];

		p_wpd->extConfig.cl.triggerLZero = config[12];
		p_wpd->extConfig.cl.triggerRZero = config[13];
	}

	return;
}

static void __wpadGetMpConfig(WPADChannel chan, byte_t *config,
                              MplsConfigDataType type)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	struct WPADMplsCalibration *calib = type == MPLS_CALIB_TYPE_HIGH
	                                      ? &p_wpd->extConfig.mpls.high
	                                      : &p_wpd->extConfig.mpls.low;

	calib->pitchZero = MAKE_MP_CONFIG_ZERO_VALUE(config[4], config[5]);
	calib->yawZero = MAKE_MP_CONFIG_ZERO_VALUE(config[0], config[1]);
	calib->rollZero = MAKE_MP_CONFIG_ZERO_VALUE(config[2], config[3]);

	calib->degrees = config[12] * 6;
	if (calib->degrees == 0)
		calib->degrees = 91;

	calib->pitchScale = MAKE_MP_CONFIG_SCALE_VALUE(config[10], config[11]);
	calib->yawScale = MAKE_MP_CONFIG_SCALE_VALUE(config[6], config[7]);
	calib->rollScale = MAKE_MP_CONFIG_SCALE_VALUE(config[8], config[9]);

	RECALC_MP_CONFIG_SCALE_VALUE(calib->pitchScale);
	RECALC_MP_CONFIG_SCALE_VALUE(calib->yawScale);
	RECALC_MP_CONFIG_SCALE_VALUE(calib->rollScale);
}

static void __wpadGetExtConfig(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	byte_t *data = p_wpd->wmReadDataPtr;

	if (!p_wpd->wpInfo.attach)
	{
		p_wpd->devType = _wpadDevType[chan] = WPAD_DEV_CORE;
		p_wpd->devMode = _wpadDevMode[chan] = WPAD_DEV_MODE_NORMAL;

		return;
	}

	switch (result)
	{
	case WPAD_ENODEV:
		p_wpd->devType = WPAD_DEV_NONE;
		p_wpd->savedDevType = p_wpd->devType;
		p_wpd->extWasDisconnected = FALSE;
		break;

	case WPAD_ESUCCESS:
		p_wpd->devType = _wpadDevType[chan];
		break;

	default:
		p_wpd->devType = WPAD_DEV_252; // can't get device?
		p_wpd->savedDevType = p_wpd->devType;
		p_wpd->extWasDisconnected = FALSE;
		break;
	}

	p_wpd->devMode = _wpadDevMode[chan];

	if (p_wpd->devType == WPAD_DEV_FS)
	{
		p_wpd->extConfig.fs.accX0g = p_wpd->extConfig.fs.accY0g =
			p_wpd->extConfig.fs.accZ0g = 512;

		p_wpd->extConfig.fs.accX1g = p_wpd->extConfig.fs.accY1g =
			p_wpd->extConfig.fs.accZ1g = 716;

		if (__wpadCheckCalibration(&data[0], 14, CHECKSUM_SIMPLE_SUM))
			__wpadGetFsConfig(chan, &data[0]);
		else if (__wpadCheckCalibration(&data[16], 14, CHECKSUM_SIMPLE_SUM))
			__wpadGetFsConfig(chan, &data[16]);
	}
	else if (p_wpd->devType == WPAD_DEV_CLASSIC)
	{
		if (__wpadCheckCalibration(&data[0], 14, CHECKSUM_SIMPLE_SUM))
			__wpadGetClConfig(chan, &data[0]);
		else
			__wpadGetClConfig(chan, &data[16]);
	}
	else if (p_wpd->devType == WPAD_DEV_MOTION_PLUS
	         || p_wpd->devType == WPAD_DEV_MPLS_PT_FS
	         || p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC
	         || p_wpd->devType == WPAD_DEV_MPLS_PT_UNKNOWN)
	{
		p_wpd->noParseMplsCount = 5;

		p_wpd->extConfig.mpls.high.pitchZero =
			p_wpd->extConfig.mpls.high.yawZero =
				p_wpd->extConfig.mpls.high.rollZero = 8192.0f;
		p_wpd->extConfig.mpls.high.pitchScale =
			p_wpd->extConfig.mpls.high.yawScale =
				p_wpd->extConfig.mpls.high.rollScale = 5333.0f;
		p_wpd->extConfig.mpls.high.degrees = 1200;

		p_wpd->extConfig.mpls.low.pitchZero =
			p_wpd->extConfig.mpls.low.yawZero =
				p_wpd->extConfig.mpls.low.rollZero = 8192.0f;
		p_wpd->extConfig.mpls.low.pitchScale =
			p_wpd->extConfig.mpls.low.yawScale =
				p_wpd->extConfig.mpls.low.rollScale = 5400.0f;
		p_wpd->extConfig.mpls.low.degrees = 270;

		p_wpd->extConfig.mpls.calibID = -1;
		p_wpd->extConfig.mpls.calibCRC = -1;

		byte_t saveCRC[sizeof(u16)];
		saveCRC[0] = data[14];
		saveCRC[1] = data[15];

		memcpy(&data[14], &data[16], 14);

		data[28] = saveCRC[0];
		data[29] = saveCRC[1];

		if (__wpadCheckCalibration(data, 28, CHECKSUM_CRC32))
		{
			__wpadGetMpConfig(chan, &data[0], MPLS_CALIB_TYPE_HIGH);
			__wpadGetMpConfig(chan, &data[14], MPLS_CALIB_TYPE_LOW);

			p_wpd->extConfig.mpls.calibID =
				MAKE_MPLS_CONFIG_ID(data[13], data[27]);

			p_wpd->extConfig.mpls.calibCRC = OSCalcCRC32(data, 28);
		}

		p_wpd->certState = WPAD_STATE_CERT_PROBE_X;

		if (p_wpd->lastMplsCalibID == p_wpd->extConfig.mpls.calibID
		    && p_wpd->lastMplsCalibCRC == p_wpd->extConfig.mpls.calibCRC)
		{
			if (p_wpd->certMayVerifyByCalibBlock == TRUE)
			{
				p_wpd->certValidityStatus = WPAD_CERT_VALID;
				p_wpd->certState = WPAD_STATE_CERT_SUCCESS;
			}
		}
		else
		{
			p_wpd->certMayVerifyByCalibBlock = FALSE;
		}

		if (p_wpd->certMayVerifyByCalibBlock != TRUE
		    && p_wpd->certProbeStartingValue >= 14)
		{
			p_wpd->devType = _wpadDevType[chan] = WPAD_DEV_252;
		}

		p_wpd->lastMplsCalibID = p_wpd->extConfig.mpls.calibID;
		p_wpd->lastMplsCalibCRC = p_wpd->extConfig.mpls.calibCRC;
	}
	else if (p_wpd->devType == WPAD_DEV_BALANCE_CHECKER)
	{
		if (p_wpd->wmReadLength == 1)
			return;
	}

	if (p_wpd->extensionCB)
		(*p_wpd->extensionCB)(chan, p_wpd->devType);

	p_wpd->cmdBlkCB = NULL;
}

static void __wpadGetExtConfig2(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	byte_t *data = p_wpd->wmReadDataPtr;

	if (!p_wpd->hasReadExtType2)
		return;

	if (result == WPAD_ESUCCESS)
	{
		if (_wpadDevType2[chan] == 0)
		{
			p_wpd->extConfig.fs.accX0g = p_wpd->extConfig.fs.accY0g =
				p_wpd->extConfig.fs.accZ0g = 512;

			p_wpd->extConfig.fs.accX1g = p_wpd->extConfig.fs.accY1g =
				p_wpd->extConfig.fs.accZ1g = 716;

			if (__wpadCheckCalibration(data, 14, CHECKSUM_SIMPLE_SUM))
			{
				__wpadGetFsConfig(chan, data);
				p_wpd->parseMPState = 4;
			}
			else
			{
				if (p_wpd->parseMPState == 3)
					p_wpd->parseMPState += 3;
				else
					p_wpd->parseMPState = 4;
			}
		}
		else
		{
			p_wpd->parseMPState = 4;
		}
	}
	else if (result == WPAD_ERR_3)
	{
		p_wpd->parseMPState = 2;
	}
}

static BOOL __wpadIsExtEncryptMain(u8 devType)
{
	// poor WPAD_DEV_TAIKO, wasn't included :(
	if (devType == WPAD_DEV_FS || devType == WPAD_DEV_CLASSIC
	    || devType == WPAD_DEV_BALANCE_CHECKER || devType == WPAD_DEV_GUITAR
	    || devType == WPAD_DEV_DRUM || devType == WPAD_DEV_TURNTABLE
	    || devType == WPAD_DEV_VSM || devType == WPAD_DEV_BULK_1
	    || devType == WPAD_DEV_BULK_2 || devType == WPAD_DEV_BULK_3
	    || devType == WPAD_DEV_BULK_4 || devType == WPAD_DEV_BULK_5
	    || devType == WPAD_DEV_BULK_6 || devType == WPAD_DEV_BULK_7
	    || devType == WPAD_DEV_BULK_8)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static void __wpadGetExtType(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	struct WPADCmdQueue *queue = &p_wpd->extCmdQueue;
	byte_t *data = p_wpd->wmReadDataBuf;

	if (result == WPAD_ESUCCESS)
	{
		if (!p_wpd->wpInfo.attach)
		{
			p_wpd->devType = _wpadDevType[chan] = WPAD_DEV_CORE;
			p_wpd->devMode = _wpadDevMode[chan] = WPAD_DEV_MODE_NORMAL;

			return;
		}

		if (memcmp(data, _cExtInvalidData, 16) == 0
		    || (data[12] == 0 && data[13] == 0))
		{
			_wpadDevType[chan] = WPAD_DEV_252;
			_wpadDevMode[chan] = WPAD_DEV_MODE_NORMAL;
		}
		else
		{
			_wpadCLCompt[chan] = FALSE;
			_wpadDevMode[chan] = data[14];

			switch (data[15])
			{
			case 0:
				_wpadDevType[chan] = WPAD_DEV_FS;
				break;

			case 1:
				_wpadDevType[chan] = WPAD_DEV_CLASSIC;
				break;

			case 2:
				_wpadDevType[chan] =
					WUDIsLinkedWBC() ? WPAD_DEV_BALANCE_CHECKER : WPAD_DEV_251;
				break;

			case 16:
				_wpadDevType[chan] =
					WPADIsEnabledTRN() ? WPAD_DEV_TRAIN : WPAD_DEV_251;
				break;

			case 17:
				_wpadDevType[chan] =
					WPADIsEnabledTKO() ? WPAD_DEV_TAIKO : WPAD_DEV_251;
				break;

			case 3:
				if (__OSInIPL)
				{
					_wpadDevType[chan] = WPAD_DEV_CLASSIC;
					_wpadDevMode[chan] = WPAD_DEV_MODE_CLASSIC_REDUCED;
					_wpadCLCompt[chan] = TRUE;
				}
				else
				{
					switch (data[10])
					{
					case 0:
						_wpadDevType[chan] =
							WPADIsEnabledGTR() ? WPAD_DEV_GUITAR : WPAD_DEV_251;
						break;

					case 1:
						_wpadDevType[chan] =
							WPADIsEnabledDRM() ? WPAD_DEV_DRUM : WPAD_DEV_251;
						break;

					case 3:
						_wpadDevType[chan] = WPADIsEnabledTBL()
						                       ? WPAD_DEV_TURNTABLE
						                       : WPAD_DEV_251;
						break;

					case 4:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_1 : WPAD_DEV_251;
						break;

					case 5:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_2 : WPAD_DEV_251;
						break;

					case 6:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_3 : WPAD_DEV_251;
						break;

					case 7:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_4 : WPAD_DEV_251;
						break;

					case 8:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_5 : WPAD_DEV_251;
						break;

					case 9:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_6 : WPAD_DEV_251;
						break;

					case 10:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_7 : WPAD_DEV_251;
						break;

					case 11:
						_wpadDevType[chan] =
							WPADIsEnabledBLK() ? WPAD_DEV_BULK_8 : WPAD_DEV_251;
						break;

					default:
						_wpadDevType[chan] = WPAD_DEV_251;
						break;
					}
				}

				break;

			case 4:
				if (WPADIsEnabledVSM())
				{
					_wpadDevType[chan] = WPAD_DEV_VSM;
					p_wpd->unk_0xbbc = 0;
				}
				else
				{
					_wpadDevType[chan] = WPAD_DEV_251;
				}

				break;

			case 5:
				switch (data[14])
				{
				case 4:
				case 5:
				case 7:
					_wpadDevType[chan] = WPAD_DEV_MOTION_PLUS;
					break;

				default:
					_wpadDevType[chan] = WPAD_DEV_251;
					break;
				}

				p_wpd->hasReadExtType2 = FALSE;
				p_wpd->parseMPState = 0;
				p_wpd->unk_0x93c = WPAD_DEV_NONE;

				_wpadDevType2[chan] = data[9];
				_wpadDevType2Sub[chan] = data[8];

				p_wpd->mplsUptimeMs = 0;

				break;

			default:
				_wpadDevType[chan] = WPAD_DEV_251;
				break;
			}
		}

		if (_wpadDevType[chan] == WPAD_DEV_CLASSIC
		    && (_wpadDevMode[chan] < WPAD_DEV_MODE_CLASSIC_REDUCED
		        || _wpadDevMode[chan] > WPAD_DEV_MODE_CLASSIC_STANDARD))
		{
			_wpadDevType[chan] = WPAD_DEV_252;
		}

		if (p_wpd->extWasDisconnected
		    && p_wpd->savedDevType == _wpadDevType[chan])
		{
			if (p_wpd->calibrated)
				p_wpd->calibrated = TRUE; // ?
		}
		else
		{
			p_wpd->calibrated = FALSE;
		}

		p_wpd->savedDevType = _wpadDevType[chan];
		p_wpd->extWasDisconnected = FALSE;

		if (_wpadDevType[chan] == WPAD_DEV_251
		    || _wpadDevType[chan] == WPAD_DEV_252)
		{
			p_wpd->devType = _wpadDevType[chan];
			p_wpd->devMode = _wpadDevMode[chan];

			if (p_wpd->extensionCB)
				(*p_wpd->extensionCB)(chan, p_wpd->devType);
		}
		else
		{
			if (_wpadDevType[chan] == WPAD_DEV_MOTION_PLUS
			    || _wpadDevType[chan] == WPAD_DEV_MPLS_PT_FS
			    || _wpadDevType[chan] == WPAD_DEV_MPLS_PT_CLASSIC
			    || _wpadDevType[chan] == WPAD_DEV_MPLS_PT_UNKNOWN)
			{
				__wpadCertReset(chan);
				p_wpd->certProbeStartingValue = data[7];
			}
			else
			{
				// favoritism
				if (__wpadIsExtEncryptMain(_wpadDevType[chan]))
				{
					p_wpd->extState = WPAD_STATE_EXT_ENCRYPTED;
					WPADiCreateKey(chan);
				}
				else
				{
					p_wpd->extState = WPAD_STATE_EXT_ENCRYPTED_3RD;
					WPADiCreateKeyFor3rd(chan);
				}

				// see https://wiibrew.org/wiki/Wiimote/Extension_Controllers#Encryption_setup
				WPADiSendWriteDataCmd(queue, 0xaa, WM_REG_EXTENSION_F0,
				                      &__wpadAbortInitExtension);
				WPADiSendWriteData(queue, &p_wpd->encryptionKey[0], 6,
				                   WM_REG_EXTENSION_40 + 0,
				                   &__wpadAbortInitExtension);
				WPADiSendWriteData(queue, &p_wpd->encryptionKey[6], 6,
				                   WM_REG_EXTENSION_40 + 6,
				                   &__wpadAbortInitExtension);
				WPADiSendWriteData(queue, &p_wpd->encryptionKey[12], 4,
				                   WM_REG_EXTENSION_40 + 12,
				                   &__wpadAbortInitExtension);

				if (_wpadDevType[chan] == WPAD_DEV_BALANCE_CHECKER)
				{
					WPADiSendWriteDataCmd(queue, 0xaa,
					                      WM_REG_EXTENSION_CERT_CHALLENGE,
					                      &__wpadAbortInitExtension);
					WPADiSendWriteDataCmd(queue, 0xaa,
					                      WM_REG_EXTENSION_CERT_CHALLENGE,
					                      &__wpadAbortInitExtension);
					WPADiSendWriteDataCmd(queue, 0xaa,
					                      WM_REG_EXTENSION_CERT_CHALLENGE,
					                      &__wpadAbortInitExtension);
				}
			}

			WPADiSendReadData(queue, p_wpd->wmReadDataBuf,
			                  WM_EXTENSION_CONFIG_SIZE, WM_REG_EXTENSION_CONFIG,
			                  (WPADCallback *)p_wpd->extensionCB);
		}
	}
	else
	{
		p_wpd->devType = WPAD_DEV_252;
		p_wpd->devMode = WPAD_DEV_MODE_NORMAL;
		p_wpd->savedDevType = p_wpd->devType;
		p_wpd->extWasDisconnected = FALSE;
	}
}

static void __wpadGetExtType2(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	byte_t *bufPtr = p_wpd->wmReadDataPtr;

	if (!p_wpd->hasReadExtType2)
		return;

	if (p_wpd->parseMPState != 1)
		return;

	if (result != WPAD_ESUCCESS)
	{
		p_wpd->parseMPState = 0;
		return;
	}

	p_wpd->parseMPState = 2;
	p_wpd->calibrated = FALSE;
	_wpadDevType2[chan] = bufPtr[3];
	_wpadDevType2Sub[chan] = bufPtr[2];
}

static void __wpadGetGameInfo(WPADChannel chan, WPADResult result, u8 param_3)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	int i;

	byte_t *bufPtrRead = p_wpd->wmReadDataPtr;
	byte_t *bufPtrCalc = p_wpd->wmReadDataPtr;
	u8 crc = 0;

	if (result == WPAD_ESUCCESS)
	{
		for (i = 0; i < 47; i++)
			crc += bufPtrCalc[i];

		crc += 0x55;
		if (bufPtrRead[47] == crc)
		{
			memcpy(&p_wpd->gameInfo, bufPtrCalc, sizeof p_wpd->gameInfo);
			p_wpd->at_0x038[param_3] = 0; // WPAD_ESUCCESS?
		}
		else
		{
			p_wpd->at_0x038[param_3] = -4; // WPAD_EINVAL?
		}
	}
	else
	{
		p_wpd->at_0x038[param_3] = -4;
	}
}

static void __wpadInitExtension(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	u8 cmd = 0x00; // TODO: some define?

	WPADiClearQueue(&p_wpd->extCmdQueue);

	WPADiSendSetReportType(&p_wpd->extCmdQueue, p_wpd->dataFormat,
	                       p_wpd->disableContReport, &__wpadAbortInitExtension);

	p_wpd->extState = WPAD_STATE_EXT_INITIALIZED;

	if (p_wpd->isInitingMpls)
	{
		WPADiSendWriteDataCmd(&p_wpd->extCmdQueue, cmd, WM_REG_EXTENSION_FB,
		                      &__wpadAbortInitExtension);
		WPADiSendReadData(&p_wpd->extCmdQueue, p_wpd->wmReadDataBuf, 16,
		                  WM_REG_EXTENSION_F0, &__wpadAbortInitExtension);
	}
	else
	{
		WPADiSendWriteDataCmd(&p_wpd->extCmdQueue, 0x55, WM_REG_EXTENSION_F0,
		                      &__wpadAbortInitExtension);
		WPADiSendWriteDataCmd(&p_wpd->extCmdQueue, cmd, WM_REG_EXTENSION_FB,
		                      &__wpadAbortInitExtension);
		WPADiSendReadData(&p_wpd->extCmdQueue, &p_wpd->wmReadDataBuf[10],
		                  16 - 10, WM_REG_EXTENSION_F0 + 10,
		                  &__wpadAbortInitExtension);
	}

	p_wpd->isInitingMpls = FALSE;
}

static void __wpadInvertRxBuffer(u8 chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
}

static void *__wpadGetWorkRxBuffer(u8 chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	void *rxBuf = &p_wpd->rxBufs[p_wpd->rxBufIndex];

	return rxBuf;
}

static void *__wpadGetLastRxBuffer(u8 chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	u32 lastIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
	void *rxBuf = &p_wpd->rxBufs[lastIndex];

	return rxBuf;
}

static void __wpadCheckDataFormat(u8 chan, u8 rep_id, void *data)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = data;

/*
	WPAD_FMT_BTN					= RPTID_DATA_BTN
	WPAD_FMT_BTN_ACC				= RPTID_DATA_BTN_ACC
	WPAD_FMT_BTN_ACC_DPD			= RPTID_DATA_BTN_ACC_DPD12
	WPAD_FMT_FS_BTN					= RPTID_DATA_BTN_EXT8
	WPAD_FMT_FS_BTN_ACC				= RPTID_DATA_BTN_ACC_EXT16
	WPAD_FMT_FS_BTN_ACC_DPD			= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_CLASSIC_BTN			= RPTID_DATA_BTN_EXT8
	WPAD_FMT_CLASSIC_BTN_ACC		= RPTID_DATA_BTN_ACC_EXT16
	WPAD_FMT_CLASSIC_BTN_ACC_DPD	= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_DPD_EXTENDED			= RPTID_DATA_BTN_ACC_DPD18_1 or 2

	WPAD_FMT_TRAIN					= RPTID_DATA_BTN_EXT8
	WPAD_FMT_GUITAR					= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_BALANCE_CHECKER		= RPTID_DATA_BTN_EXT19
	WPAD_FMT_VSM					= RPTID_DATA_BTN_ACC_EXT16
//	WPAD_FMT_14
	WPAD_FMT_DRUM					= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_MOTION_PLUS			= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_TAIKO					= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_TURNTABLE				= RPTID_DATA_BTN_ACC_DPD10_EXT9
	WPAD_FMT_BULK					= RPTID_DATA_BTN_ACC_EXT16
*/

	// clang-format off
	if ((rep_id == RPTID_DATA_BTN
		&& p_wpd->dataFormat == WPAD_FMT_CORE_BTN)
	|| (rep_id == RPTID_DATA_BTN_ACC
		&& p_wpd->dataFormat == WPAD_FMT_CORE_BTN_ACC)
	|| (rep_id == RPTID_DATA_BTN_EXT8
		&& (p_wpd->dataFormat == WPAD_FMT_FS_BTN
		|| p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN
		|| p_wpd->dataFormat == WPAD_FMT_TRAIN))
	|| (rep_id == RPTID_DATA_BTN_ACC_DPD12
		&& p_wpd->dataFormat == WPAD_FMT_CORE_BTN_ACC_DPD)
	|| (rep_id == RPTID_DATA_BTN_EXT19
		&& p_wpd->dataFormat == WPAD_FMT_BALANCE_CHECKER)
	|| (rep_id == RPTID_DATA_BTN_ACC_EXT16
		&& (p_wpd->dataFormat == WPAD_FMT_FS_BTN_ACC
		|| p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC
		|| p_wpd->dataFormat == WPAD_FMT_VSM
		|| p_wpd->dataFormat == WPAD_FMT_BULK))
	|| (rep_id == RPTID_DATA_BTN_ACC_DPD10_EXT9
		&& (p_wpd->dataFormat == WPAD_FMT_FS_BTN_ACC_DPD
		|| p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC_DPD
		|| p_wpd->dataFormat == WPAD_FMT_GUITAR
		|| p_wpd->dataFormat == WPAD_FMT_DRUM
		|| p_wpd->dataFormat == WPAD_FMT_TURNTABLE
		|| p_wpd->dataFormat == WPAD_FMT_TAIKO
		|| p_wpd->dataFormat == WPAD_FMT_MOTION_PLUS))
	|| (rep_id == RPTID_DATA_BTN_ACC_DPD18_1
		&& p_wpd->dataFormat == WPAD_FMT_BTN_ACC_DPD_EXTENDED)
	|| (rep_id == RPTID_DATA_BTN_ACC_DPD18_2
		&& p_wpd->dataFormat == WPAD_FMT_BTN_ACC_DPD_EXTENDED))
	// clang-format on
	{
		status->err = WPAD_ESUCCESS;
	}
	else
	{
		status->err = WPAD_EINVAL;
	}
}

signed WPADiHIDParser(UINT8 port, UINT8 *p_rpt)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[port];

	BOOL intrStatus;

	signed ret = 0; // is this a WPADResult?
	byte_t *rxBuf;
	if (p_rpt[RPT_REPORT_ID] >= RPTID_IN_LO
	    && p_rpt[RPT_REPORT_ID] <= RPTID_IN_HI)
	{
		intrStatus = OSDisableInterrupts();

		rxBuf = __wpadGetWorkRxBuffer(port);

		if (p_rpt[RPT_REPORT_ID] != RPTID_DATA_BTN_ACC_DPD18_1
		    && p_rpt[RPT_REPORT_ID] != RPTID_DATA_BTN_ACC_DPD18_2)
		{
			memset(rxBuf, 0, RX_BUFFER_SIZE);
		}

		__wpadCheckDataFormat(port, p_rpt[RPT_REPORT_ID], rxBuf);

		(*__a1_input_reports_array[p_rpt[RPT_REPORT_ID] - RPTID_IN_LO])(
			port, p_rpt, rxBuf);

		if (!p_wpd->handshakeFinished)
			((WPADStatus *)(rxBuf))->err = WPAD_EINVAL;

		((WPADStatus *)(rxBuf))->dev = p_wpd->devType;

		if (p_rpt[RPT_REPORT_ID] != RPTID_DATA_BTN_ACC_DPD18_1
		    && p_rpt[RPT_REPORT_ID] != RPTID_DATA_BTN_ACC_DPD18_2)
		{
			__wpadInvertRxBuffer(port);
		}

		OSRestoreInterrupts(intrStatus);

		WPADiExcludeButton(port);
		WPADiCopyOut(port);
	}
	else
	{
		// maybe not, WPAD_ENODEV doesn't make sense here
		ret = -1;
	}

	return ret; // is it a tBTA_STATUS or similar?
}

static void __a1_20_status_report(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	BOOL intrStatus;
	BOOL currentlyHasExtension = p_wpd->wpInfo.attach;

	intrStatus = OSDisableInterrupts();

	if (!p_wpd->handshakeFinished)
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

#if !defined(NDEBUG)
	if (!WPADiIsDummyExtension(chan))
#endif
		p_wpd->wpInfo.attach = (hidReport[RPT20_FLAGS] & 0x02) >> 1;

	p_wpd->wpInfo.lowBat = hidReport[RPT20_FLAGS] & 0x01;
	p_wpd->wpInfo.led = (hidReport[RPT20_FLAGS] & 0xf0) >> 4;

	/* ERRATA: the masks (or shifts?) on the following statements are switched
	 *
	 * protocol is always 0 after the shift (probably wrong)
	 * firmware holds protocol(?) in its upper nibble (probably not intended)
	 */
	p_wpd->wpInfo.protocol = (hidReport[RPT20_PROTO_FW] & 0x0f) >> 4;
	p_wpd->wpInfo.firmware = (hidReport[RPT20_PROTO_FW] & 0xf0) >> 0;

	p_wpd->wpInfo.nearempty = (u8)((hidReport[RPT_BTN0] & 0x80) >> 7);
	p_wpd->wpInfo.dpd = (hidReport[RPT20_FLAGS] & 0x08) >> 3;
	p_wpd->wpInfo.speaker = (hidReport[RPT20_FLAGS] & 0x04) >> 2;

	if (p_wpd->devType == WPAD_DEV_BALANCE_CHECKER)
		p_wpd->wpInfo.battery = p_wpd->blcBattery;
	else if ((u8)hidReport[RPT20_BATTERY] >= 0x55)
		p_wpd->wpInfo.battery = 4;
	else if ((u8)hidReport[RPT20_BATTERY] >= 0x44)
		p_wpd->wpInfo.battery = 3;
	else if ((u8)hidReport[RPT20_BATTERY] >= 0x33)
		p_wpd->wpInfo.battery = 2;
	else if ((u8)hidReport[RPT20_BATTERY] >= 0x03)
		p_wpd->wpInfo.battery = 1;
	else
		p_wpd->wpInfo.battery = 0;

	WPADExtensionCallback *extCB;
	if (p_wpd->wpInfo.attach)
	{
		if (!currentlyHasExtension)
		{
			_wpadExtInitRetryCnt[chan] = 0;

			extCB = p_wpd->extensionCB;
			__wpadInitExtension(chan);

			p_wpd->devType = WPAD_DEV_INITIALIZING;
			p_wpd->devMode = WPAD_DEV_MODE_NORMAL;
			__wpadCertReset(chan);

			if (extCB)
				(*extCB)(chan, WPAD_DEV_INITIALIZING);
		}
	}
	else
	{
		p_wpd->devType = WPAD_DEV_CORE;
		p_wpd->devMode = WPAD_DEV_MODE_NORMAL;

		WPADiClearQueue(&p_wpd->extCmdQueue);
		WPADiSendSetReportType(&p_wpd->extCmdQueue, p_wpd->dataFormat,
		                       p_wpd->disableContReport, NULL);

		if (currentlyHasExtension)
		{
			p_wpd->extWasDisconnected = TRUE;
			p_wpd->reconnectExtMs = 300;
			__wpadCertReset(chan);

			if (p_wpd->extensionCB)
				(*p_wpd->extensionCB)(chan, WPAD_DEV_CORE);
		}
	}

	if (p_wpd->wpInfoOut)
	{
		memcpy(p_wpd->wpInfoOut, &p_wpd->wpInfo, sizeof *p_wpd->wpInfoOut);
		p_wpd->wpInfoOut = NULL;
	}

	RETRIEVE_BUTTON_STATE(chan, status, rxBuffer, hidReport);

	if (p_wpd->cmdBlkCB && p_wpd->statusReqBusy)
	{
		(*p_wpd->cmdBlkCB)(chan, WPAD_ESUCCESS);
		p_wpd->cmdBlkCB = NULL;
	}

	p_wpd->statusReqBusy = FALSE;

	OSRestoreInterrupts(intrStatus);
}

static void __a1_21_user_data(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;
	BOOL intrStatus = OSDisableInterrupts();

	u16 addrLow;
	u16 readAddrLow;
	u16 readAddrHigh;
	s16 addrDiff;

	u8 errCode = (u8)hidReport[RPT21_SIZE_ERR] & 0x0f;
	if (errCode != 0)
	{
		p_wpd->wmReadHadError = -1;

		if (p_wpd->cmdBlkCB)
		{
			if (!p_wpd->extensionCB || p_wpd->extensionCB != p_wpd->cmdBlkCB)
				(*p_wpd->cmdBlkCB)(chan, WPAD_ERR_3);

			p_wpd->cmdBlkCB = NULL;
		}

		p_wpd->status = WPAD_ESUCCESS;
	}

	u8 size = ((u8)((u8)hidReport[RPT21_SIZE_ERR] >> 4) & 0x0f) + 1;
	addrLow = (u16)((u16)((u16)hidReport[RPT21_ADDR0] << 8) & 0xff00)
	        | (u16)((u16)((u16)hidReport[RPT21_ADDR1]) & 0x00ff);

	readAddrLow = p_wpd->wmReadAddress & 0x0000ffff;
	readAddrHigh = (p_wpd->wmReadAddress & 0xffff0000) >> 16;
	addrDiff = addrLow - readAddrLow;

	WPADResult cbRet;
	if ((u16)addrLow >= readAddrLow
	    && addrLow <= readAddrLow + p_wpd->wmReadLength)
	{
		if (errCode == 0)
		{
			memcpy(p_wpd->wmReadDataPtr + addrDiff, &hidReport[RPT21_DATA],
			       size);
		}

		if (readAddrLow + p_wpd->wmReadLength == addrLow + size)
		{
			cbRet = p_wpd->wmReadHadError < 0 ? WPAD_CERR_3 : WPAD_CESUCCESS;

			if (readAddrHigh == 0x04a4
			    && (p_wpd->extState == WPAD_STATE_EXT_ENCRYPTED
			        || p_wpd->extState == WPAD_STATE_EXT_ENCRYPTED_3RD))
			{
				WPADiDecode(chan, p_wpd->wmReadDataPtr, p_wpd->wmReadLength,
				            readAddrLow);
			}

			if ((p_wpd->wmReadAddress == WM_ADDR_MEM_DEV_CONFIG_0
			     && p_wpd->configIndex == 0)
			    || (p_wpd->wmReadAddress == WM_ADDR_MEM_176C
			        && p_wpd->configIndex == 1))
			{
				__wpadGetDevConfig(chan, cbRet);
			}

			if (p_wpd->wmReadAddress == WM_REG_EXTENSION_CONFIG)
				__wpadGetExtConfig(chan, cbRet);

			if (p_wpd->wmReadAddress == WM_REG_EXTENSION_F0
			    || p_wpd->wmReadAddress == WM_REG_EXTENSION_FA)
			{
				__wpadGetExtType(chan, cbRet);
			}

			if (p_wpd->wmReadAddress == WM_REG_EXTENSION_EXT_TYPE_2)
				__wpadGetExtType2(chan, cbRet);

			if (p_wpd->wmReadAddress == WM_REG_EXTENSION_40)
				__wpadGetExtConfig2(chan, cbRet);

			if (p_wpd->wmReadAddress == WM_REG_EXTENSION_F3)
			{
				if (p_wpd->parseMPBuf == 3)
					p_wpd->parseMPState = 9;
				else if (p_wpd->parseMPBuf == 4)
					p_wpd->parseMPState = 6;
			}

			if (p_wpd->wmReadAddress == WM_ADDR_MEM_GAME_INFO_0)
				__wpadGetGameInfo(chan, cbRet, 0);

			if (p_wpd->wmReadAddress == WM_ADDR_MEM_GAME_INFO_1)
				__wpadGetGameInfo(chan, cbRet, 1);

			if (p_wpd->cmdBlkCB)
			{
				(*p_wpd->cmdBlkCB)(chan, cbRet);
				p_wpd->cmdBlkCB = NULL;
			}

			p_wpd->status = WPAD_ESUCCESS;
		}
	}

	RETRIEVE_BUTTON_STATE(chan, status, rxBuffer, hidReport);

	OSRestoreInterrupts(intrStatus);
}

static void __a1_22_ack(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;
	BOOL intrStatus = OSDisableInterrupts();

	RETRIEVE_BUTTON_STATE(chan, status, rxBuffer, hidReport);

	u8 ackedID = (u8)hidReport[RPT22_ACKED_RPT_ID];
	u8 err = (u8)hidReport[RPT22_ERR_CODE];

	WPADResult cbRet = err == 0 ? WPAD_CESUCCESS : WPAD_CERR_3;

	if (p_wpd->lastReportID == ackedID)
	{
		if (p_wpd->cmdBlkCB)
		{
			(*p_wpd->cmdBlkCB)(chan, cbRet);
			p_wpd->cmdBlkCB = NULL;
		}

		p_wpd->status = WPAD_ESUCCESS;
	}

	OSRestoreInterrupts(intrStatus);
}

static void __parse_dpd_data(WPADChannel chan, WPADStatus **status,
                             u8 dpdFormat, byte_t *data, u8 length)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->dpdBusy)
	{
		status[0]->err = WPAD_EINVAL;
		return;
	}

	u8 i;
	u8 a, b, c;
	if (dpdFormat == WPAD_DPD_STANDARD)
	{
		for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
		{
			if (i * 3 + 2 < length)
			{
				a = ((u8 *)(data + i * 3))[0];
				b = ((u8 *)(data + i * 3))[1];
				c = ((u8 *)(data + i * 3))[2];

				status[0]->obj[i].x = MAKE_DPD_STANDARD_X(c, a);
				status[0]->obj[i].y = MAKE_DPD_STANDARD_Y(c, b);
				status[0]->obj[i].size = MAKE_DPD_STANDARD_SIZE(c);
				RECALC_DPD_STANDARD_SIZE(status[0]->obj[i].size);

				if (status[0]->obj[i].size == 0
				    || status[0]->obj[i].x == DPD_MAX_X
				    || status[0]->obj[i].y == DPD_MAX_Y)
				{
					status[0]->obj[i].x = 0;
					status[0]->obj[i].y = DPD_MAX_Y;
					status[0]->obj[i].size = 0;
				}

				status[0]->obj[i].traceId = i;
			}
			else
			{
				status[0]->obj[i].x = 0;
				status[0]->obj[i].y = DPD_MAX_Y;
				status[0]->obj[i].size = 0;
				status[0]->obj[i].traceId = i;
			}
		}
	}
	else if (dpdFormat == WPAD_DPD_BASIC)
	{
		for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
		{
			a = GET_DPD_BASIC_REPORT_X_LOW_BYTE(data, i);
			b = GET_DPD_BASIC_REPORT_Y_LOW_BYTE(data, i);
			c = GET_DPD_BASIC_REPORT_XY_HIGH_BITS(data, i);

			if (i % 2 == 0)
			{
				// First object of the pair
				status[0]->obj[i].x = MAKE_DPD_BASIC_X1(c, a);
				status[0]->obj[i].y = MAKE_DPD_BASIC_Y1(c, b);
			}
			else
			{
				// Second object of the pair
				status[0]->obj[i].x = MAKE_DPD_BASIC_X2(c, a);
				status[0]->obj[i].y = MAKE_DPD_BASIC_Y2(c, b);
			}

			if (status[0]->obj[i].x == DPD_MAX_X
			    || status[0]->obj[i].y == DPD_MAX_Y)
			{
				status[0]->obj[i].x = 0;
				status[0]->obj[i].y = DPD_MAX_Y;
				status[0]->obj[i].size = 0;
			}
			else
			{
				status[0]->obj[i].size = 12;
			}

			status[0]->obj[i].traceId = i;
		}
	}

	f32 fx, fy;
	for (i = 0; i < WPAD_MAX_DPD_OBJECTS; i++)
	{
		if (status[0]->obj[i].x != 0 || status[0]->obj[i].y != DPD_MAX_Y)
		{
			fx = (f32)status[0]->obj[i].x + _wpadCalibrationX[chan]
			   - _wpadCenterX[chan];
			fy = (f32)status[0]->obj[i].y + _wpadCalibrationY[chan]
			   - _wpadCenterY[chan];

			status[0]->obj[i].x = _wpadCenterX[chan]
			                    + ((fx * (f32)cos(_wpadRolag[chan] * -1.0f))
			                       - (fy * (f32)sin(_wpadRolag[chan] * -1.0f)));

			status[0]->obj[i].y = _wpadCenterY[chan]
			                    + ((fx * (f32)sin(_wpadRolag[chan] * -1.0f))
			                       + (fy * (f32)cos(_wpadRolag[chan] * -1.0f)));
		}
	}
}

static void __parse_dpdex_data(WPADChannel chan, WPADStatusEx **statusEx,
                               u8 objIndex, byte_t *data,
                               u8 length __attribute__((unused)))
{
	wpad_cb_st *p_wpd __attribute__((unused)) = __rvl_p_wpadcb[chan];

	statusEx[0]->obj[objIndex].x = MAKE_DPD_EXTENDED_X(data[2], data[0]);
	statusEx[0]->obj[objIndex].y = MAKE_DPD_EXTENDED_Y(data[2], data[1]);
	statusEx[0]->exp[objIndex].pixel =
		MAKE_DPD_EXTENDED_PIXEL(data[7], data[8]);
	statusEx[0]->exp[objIndex].radius = MAKE_DPD_EXTENDED_RADIUS(data[2]);

	statusEx[0]->exp[objIndex].range_x1 = (s8)data[3] == -1 ? 0 : data[3];
	statusEx[0]->exp[objIndex].range_y1 = (s8)data[4] == -1 ? 0 : data[4];
	statusEx[0]->exp[objIndex].range_x2 = (s8)data[5] == -1 ? 0 : data[5];
	statusEx[0]->exp[objIndex].range_y2 = (s8)data[6] == -1 ? 0 : data[6];

	CALC_DPD_EXTENDED_X(statusEx[0]->exp[objIndex].range_x1);
	CALC_DPD_EXTENDED_Y(statusEx[0]->exp[objIndex].range_y1);
	CALC_DPD_EXTENDED_X(statusEx[0]->exp[objIndex].range_x2);
	CALC_DPD_EXTENDED_Y(statusEx[0]->exp[objIndex].range_y2);
	statusEx[0]->obj[objIndex].size =
		MAKE_DPD_EXTENDED_SIZE(statusEx[0]->exp[objIndex].radius);

	if (statusEx[0]->obj[objIndex].size == 0
	    || statusEx[0]->obj[objIndex].x == DPD_MAX_X
	    || statusEx[0]->obj[objIndex].y == DPD_MAX_Y
	    || statusEx[0]->exp[objIndex].radius == 15)
	{
		statusEx[0]->obj[objIndex].x = 0;
		statusEx[0]->obj[objIndex].y = DPD_MAX_Y;
		statusEx[0]->obj[objIndex].size = 0;
		statusEx[0]->exp[objIndex].pixel = 0;
		statusEx[0]->exp[objIndex].radius = 0;
	}

	statusEx[0]->obj[objIndex].traceId = objIndex;
}

static void __parse_acc_data(WPADChannel chan, WPADStatus **status,
                             u8 accFormat, byte_t *data,
                             u8 length __attribute__((unused)))
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	switch (accFormat)
	{
	case ACC_FORMAT_STANDARD:
		status[0]->accX = MAKE_ACC_STANDARD_X(p_wpd, data[2], data[0]);
		status[0]->accY = MAKE_ACC_STANDARD_Y(p_wpd, data[3], data[1]);
		status[0]->accZ = MAKE_ACC_STANDARD_Z(p_wpd, data[4], data[1]);
		break;

	case ACC_FORMAT_INTERLEAVED0:
		status[0]->accX = MAKE_ACC_INTERLEAVED0_X(p_wpd, data[2], data[0]);
		CALC_ACC_INTERLEAVED0_Z(status[0]->accZ, data[1], data[0]);
		break;

	case ACC_FORMAT_INTERLEAVED1:
		status[0]->accY = MAKE_ACC_INTERLEAVED1_Y(p_wpd, data[2], data[0]);
		CALC_ACC_INTERLEAVED1_Z(status[0]->accZ, data[1], data[0]);
		break;
	}
}

static s16 __clamp(s16 x, s16 low, s16 high)
{
	s16 result = x;

	if (x < low)
		result = low;

	if (x > high)
		result = high;

	return result;
}

static void __parse_fs_data(WPADChannel chan, WPADFSStatus **fsStatus,
                            u8 fsFormat __attribute__((unused)), byte_t *data,
                            u8 length __attribute__((unused)))
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	fsStatus[0]->fsStickX = data[0];
	fsStatus[0]->fsStickY = data[1];

	fsStatus[0]->fsAccX = MAKE_FS_ACC_X(p_wpd, data[2], data[5]);
	fsStatus[0]->fsAccY = MAKE_FS_ACC_Y(p_wpd, data[3], data[5]);
	fsStatus[0]->fsAccZ = MAKE_FS_ACC_Z(p_wpd, data[4], data[5]);

	CALC_FS_BUTTON(fsStatus[0]->button, data[5]);

	if (!p_wpd->calibrated)
	{
		p_wpd->calibrated = TRUE;
		p_wpd->extConfig.fs.stickXCenter = fsStatus[0]->fsStickX;
		p_wpd->extConfig.fs.stickYCenter = fsStatus[0]->fsStickY;
	}

	CLAMP_FS_STICK_X(p_wpd, fsStatus[0]->fsStickX);
	CLAMP_FS_STICK_Y(p_wpd, fsStatus[0]->fsStickY);
}

static void __parse_cl_data(WPADChannel chan, WPADCLStatus **clStatus,
                            u8 clFormat, byte_t *data, u8 length)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	switch (clFormat)
	{
	case WPAD_DEV_MODE_CLASSIC_EXTENDED:
		clStatus[0]->clLStickX = MAKE_CL_EXTENDED_STICK_LX(data[0], data[4]);
		clStatus[0]->clRStickX = MAKE_CL_EXTENDED_STICK_RX(data[1], data[4]);
		clStatus[0]->clLStickY = MAKE_CL_EXTENDED_STICK_LY(data[2], data[4]);
		clStatus[0]->clRStickY = MAKE_CL_EXTENDED_STICK_RY(data[3], data[4]);

		clStatus[0]->clTriggerL = (u8)data[5];
		clStatus[0]->clTriggerR = length < 9 ? 0 : (u8)data[6];
		clStatus[0]->clButton =
			length < 9 ? 0 : MAKE_CL_BUTTON(data[7], data[8]);
		break;

	case WPAD_DEV_MODE_CLASSIC_STANDARD:
		clStatus[0]->clLStickX = MAKE_CL_STANDARD_STICK_LX(data[0]);
		clStatus[0]->clRStickX = MAKE_CL_STANDARD_STICK_RX(data[1]);
		clStatus[0]->clLStickY = MAKE_CL_STANDARD_STICK_LY(data[2]);
		clStatus[0]->clRStickY = MAKE_CL_STANDARD_STICK_RY(data[3]);

		clStatus[0]->clTriggerL = (u8)data[4];
		clStatus[0]->clTriggerR = (u8)data[5];
		clStatus[0]->clButton =
			length < 8 ? 0 : MAKE_CL_BUTTON(data[6], data[7]);
		break;

	default:
	case WPAD_DEV_MODE_CLASSIC_REDUCED:
		clStatus[0]->clLStickX = MAKE_CL_REDUCED_STICK_LX(data[0]);
		clStatus[0]->clLStickY = MAKE_CL_REDUCED_STICK_LY(data[1]);
		clStatus[0]->clRStickX =
			MAKE_CL_REDUCED_STICK_RX(data[0], data[1], data[2]);
		clStatus[0]->clRStickY = MAKE_CL_REDUCED_STICK_RY(data[2]);

		clStatus[0]->clTriggerL = MAKE_CL_REDUCED_TRIGGER_L(data[2], data[3]);
		clStatus[0]->clTriggerR = MAKE_CL_REDUCED_TRIGGER_R(data[3]);
		clStatus[0]->clButton = MAKE_CL_BUTTON(data[4], data[5]);
		break;
	}

	if (p_wpd->devType == WPAD_DEV_CLASSIC)
	{
		clStatus[0]->clLStickX -= (s16)512;
		clStatus[0]->clLStickY -= (s16)512;
		clStatus[0]->clRStickX -= (s16)512;
		clStatus[0]->clRStickY -= (s16)512;
	}
	else if (p_wpd->devType != WPAD_DEV_TAIKO)
	{
		clStatus[0]->clLStickX -= (s16)512;
		clStatus[0]->clLStickY -= (s16)512;
	}

	if (!p_wpd->calibrated)
	{
		p_wpd->calibrated = TRUE;

		if (p_wpd->devType != WPAD_DEV_TAIKO)
		{
			p_wpd->extConfig.cl.lStickXCenter = clStatus[0]->clLStickX;
			p_wpd->extConfig.cl.lStickYCenter = clStatus[0]->clLStickY;
		}
		else
		{
			p_wpd->extConfig.cl.lStickXCenter = 0;
			p_wpd->extConfig.cl.lStickYCenter = 0;
		}

		if (p_wpd->devType == WPAD_DEV_CLASSIC)
		{
			p_wpd->extConfig.cl.rStickXCenter = clStatus[0]->clRStickX;
			p_wpd->extConfig.cl.rStickYCenter = clStatus[0]->clRStickY;
			p_wpd->extConfig.cl.triggerLZero = clStatus[0]->clTriggerL;
			p_wpd->extConfig.cl.triggerRZero = clStatus[0]->clTriggerR;
		}
		else
		{
			p_wpd->extConfig.cl.rStickXCenter = 0;
			p_wpd->extConfig.cl.rStickYCenter = 0;
			p_wpd->extConfig.cl.triggerLZero = 0;
			p_wpd->extConfig.cl.triggerRZero = 0;
		}
	}

	if (p_wpd->devType != WPAD_DEV_TAIKO)
	{
		CLAMP_CL_STICK_LX(p_wpd, clStatus[0]->clLStickX, -512, 511);
		CLAMP_CL_STICK_LY(p_wpd, clStatus[0]->clLStickY, -512, 511);
	}
	else
	{
		CLAMP_CL_STICK_LX(p_wpd, clStatus[0]->clLStickX, 0, 1024);
		CLAMP_CL_STICK_LY(p_wpd, clStatus[0]->clLStickY, 0, 1024);
	}

	if (p_wpd->devType == WPAD_DEV_CLASSIC)
	{
		CLAMP_CL_STICK_RX(p_wpd, clStatus[0]->clRStickX, -512, 511);
		CLAMP_CL_STICK_RY(p_wpd, clStatus[0]->clRStickY, -512, 511);

		if (clStatus[0]->clTriggerL > 72)
			clStatus[0]->clButton |= WPAD_BUTTON_CL_FULL_L;

		if (clStatus[0]->clTriggerR > 72)
			clStatus[0]->clButton |= WPAD_BUTTON_CL_FULL_R;

		clStatus[0]->clTriggerL = 0;
		clStatus[0]->clTriggerR = 0;
	}

	if (_wpadCLCompt[chan])
	{
		clStatus[0]->clRStickX = 0;
		clStatus[0]->clRStickY = 0;
		clStatus[0]->clTriggerL = 0;
		clStatus[0]->clTriggerR = 0;
	}
}

static void __parse_bk_data(WPADChannel chan, WPADBKStatus **bkStatus,
                            u8 bkFormat __attribute__((unused)), byte_t *data,
                            u8 length)
{
	wpad_cb_st *p_wpd __attribute__((unused)) = __rvl_p_wpadcb[chan];

	u16 i;
	for (i = 0; i < length; i++)
		bkStatus[0]->bulk[i] = data[i];
}

static void __parse_tr_data(WPADChannel chan __attribute__((unused)),
                            WPADTRStatus **trStatus,
                            u8 trFormat __attribute__((unused)), byte_t *data,
                            u8 length __attribute__((unused)))
{
	trStatus[0]->brake = data[2];
	trStatus[0]->mascon = data[3];
	trStatus[0]->trButton = MAKE_TR_BUTTON(data[6], data[7]);
}

static void __parse_bl_data(WPADChannel chan, WPADBLStatus **blStatus,
                            u8 blFormat __attribute__((unused)), byte_t *data,
                            u8 length __attribute__((unused)))
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	blStatus[0]->press[0] = MAKE_BL_WEIGHT_UL(data[0], data[1]);
	blStatus[0]->press[1] = MAKE_BL_WEIGHT_UR(data[2], data[3]);
	blStatus[0]->press[2] = MAKE_BL_WEIGHT_DL(data[4], data[5]);
	blStatus[0]->press[3] = MAKE_BL_WEIGHT_DR(data[6], data[7]);

	blStatus[0]->temp = data[8];
	blStatus[0]->battery = (u8)data[10];

	int battery = blStatus[0]->battery << 1;

	// what is this optimization??? x < n vs n >= x
	if (battery >= 260)
		p_wpd->blcBattery = 4;
	else if (battery < 260 && battery >= 250)
		p_wpd->blcBattery = 3;
	else if (battery < 250 && battery >= 240)
		p_wpd->blcBattery = 2;
	else if (battery < 240 && battery >= 212)
		p_wpd->blcBattery = 1;
	else
		p_wpd->blcBattery = 0;

	if (!p_wpd->calibrated)
		p_wpd->calibrated = TRUE;
}

static void __parse_vs_data(WPADChannel chan, WPADVSStatus **vsStatus,
                            u8 vsFormat __attribute__((unused)), byte_t *data,
                            u8 length __attribute__((unused)))
{

/*
           +-------------------------------------------------------+
           |                          Bits                         |
           +------+------+------+------+------+------+------+------+
           |    7 |    6 |    5 |    4 |    3 |    2 |    1 |    0 |
+---+------+------+------+------+------+------+------+------+------+
|   |    0 |                       0x40<7:0>                       |
|   +------+-------------------------------------------------------+
|   |    1 |                       0x36<9:2>                       |
|   +------+-------------------------------------------------------+
|   |    2 |                       0x38<9:2>                       |
|   +------+-------------------------------------------------------+
|   |    3 |                       0x3a<9:2>                       |
|   +------+-------------------------------------------------------+
|   |    4 |                       0x3c<9:2>                       |
|   +------+-------------------------------------------------------+
|   |    5 |                       0x3e<9:2>                       |
|   +------+-------------+-------------+-------------+-------------+
|   |    6 |  0x36<1:0>  |  0x38<1:0>  |  0x3a<1:0>  |  0x3c<1:0>  |
| B +------+-------------+-------------+-------------+-------------+
| y |    7 |  0x3e<1:0>  |                0x42<9:4>                |
| t +------+-------------+-----------------------------------------+
| e |    8 |                       0x34<7:0>                       |
| s +------+-------------------------------------------------------+
|   |    9 |                       0x2a<9:2>                       |
|   +------+-------------------------------------------------------+
|   |   10 |                       0x2c<9:2>                       |
|   +------+-------------------------------------------------------+
|   |   11 |                       0x2e<9:2>                       |
|   +------+-------------------------------------------------------+
|   |   12 |                       0x30<9:2>                       |
|   +------+-------------------------------------------------------+
|   |   13 |                       0x32<9:2>                       |
|   +------+-------------+-------------+-------------+-------------+
|   |   14 |  0x2a<1:0>  |  0x2c<1:0>  |  0x2e<1:0>  |  0x30<1:0>  |
|   +------+-------------+-------------+-------------+-------------+
|   |   15 |  0x32<1:0>  |         0x42<3:0>         |  0x44<1:0>  |
+---+------+-------------+---------------------------+-------------+

// likely a group of things
at_0x2a : 10;
at_0x2c : 10;
at_0x2e : 10;
at_0x30 : 10;
at_0x32 : 10;
at_0x34 :  8;

// likely another instance of the above group of things
at_0x36 : 10;
at_0x38 : 10;
at_0x3a : 10;
at_0x3c : 10;
at_0x3e : 10;
at_0x40 :  8;

// likely some other stuff
at_0x42 : 10;
at_0x44 :  2; // error code 255 if outside the range

*/

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	vsStatus[0]->at_0x40 = data[0];
	vsStatus[0]->at_0x36[0] = MAKE_VS_SET_0(data[1], data[6]);
	vsStatus[0]->at_0x36[1] = MAKE_VS_SET_1(data[2], data[6]);
	vsStatus[0]->at_0x36[2] = MAKE_VS_SET_2(data[3], data[6]);
	vsStatus[0]->at_0x36[3] = MAKE_VS_SET_3(data[4], data[6]);
	vsStatus[0]->at_0x36[4] = MAKE_VS_SET_4(data[5], data[7]);

	vsStatus[0]->at_0x34 = data[8];
	vsStatus[0]->at_0x2a[0] = MAKE_VS_SET_0(data[9], data[14]);
	vsStatus[0]->at_0x2a[1] = MAKE_VS_SET_1(data[10], data[14]);
	vsStatus[0]->at_0x2a[2] = MAKE_VS_SET_2(data[11], data[14]);
	vsStatus[0]->at_0x2a[3] = MAKE_VS_SET_3(data[12], data[14]);
	vsStatus[0]->at_0x2a[4] = MAKE_VS_SET_4(data[13], data[15]);

	vsStatus[0]->at_0x42 = MAKE_VS_42(data[7], data[15]);

	if (p_wpd->unk_0xbbc < 8)
		vsStatus[0]->at_0x44 = 255;
	else
		vsStatus[0]->at_0x44 = MAKE_VS_44(data[15]);
}

static void __parse_mp_data(WPADChannel chan, WPADMPStatus **mpStatus,
                            u8 mpFormat, byte_t *data,
                            u8 length __attribute__((unused)))
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->noParseMplsCount)
	{
		p_wpd->noParseMplsCount--;
		mpStatus[0]->err = WPAD_EINVAL;
	}

	if (mpStatus[0]->err != WPAD_ESUCCESS)
		return;

	if (mpFormat == WPAD_DEV_MODE_MPLS_PT_MAIN)
	{
		if ((data[5] & 0x03) == 0x02)
		{
			mpStatus[0]->stat = MAKE_MP_MAIN_STAT(data[3], data[4]);
			mpStatus[0]->pitch = MAKE_MP_MAIN_PITCH(data[5], data[2]);
			mpStatus[0]->yaw = MAKE_MP_MAIN_YAW(data[3], data[0]);
			mpStatus[0]->roll = MAKE_MP_MAIN_ROLL(data[4], data[1]);
		}
		else
		{
			mpStatus[0]->err = WPAD_EBADE;
		}
	}
	else if (mpFormat == WPAD_DEV_MODE_MPLS_PT_FS
	         || mpFormat == WPAD_DEV_MODE_MPLS_PT_CLASSIC)
	{
		u8 bufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
		WPADMPStatus *rxBuf = (WPADMPStatus *)(p_wpd->rxBufs[bufIndex]);

		if (data[5] & 0x01)
		{
			mpStatus[0]->stat = 0;
			mpStatus[0]->err = WPAD_EBADE;
		}
		else if (!(data[5] & 0x02))
		{
			mpStatus[0]->pitch = rxBuf->pitch;
			mpStatus[0]->yaw = rxBuf->yaw;
			mpStatus[0]->roll = rxBuf->roll;
			mpStatus[0]->stat = rxBuf->stat;

			if ((data[0] == 0xff && data[1] == 0xff) || p_wpd->parseMPState != 5
			    || (p_wpd->devType == WPAD_DEV_MPLS_PT_FS
			        && p_wpd->devMode != WPAD_DEV_MODE_MPLS_PT_FS)
			    || (p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC
			        && p_wpd->devMode != WPAD_DEV_MODE_MPLS_PT_CLASSIC)
			    || p_wpd->devType == WPAD_DEV_MPLS_PT_UNKNOWN)
			{
				// ~WPAD_MPLS_STATUS_EXTENSION_DATA_VALID
				mpStatus[0]->stat &= 0xbf;
			}
			else
			{
				CALC_MP_PT_EXT_STAT(mpStatus[0]->stat, data[4]);

				if (p_wpd->devType == WPAD_DEV_MPLS_PT_FS)
				{
					mpStatus[0]->ext.fs.fsStickX = data[0];
					mpStatus[0]->ext.fs.fsStickY = data[1];

					mpStatus[0]->ext.fs.fsAccX =
						MAKE_MP_FS_ACC_X(p_wpd, data[2], data[5]);
					mpStatus[0]->ext.fs.fsAccY =
						MAKE_MP_FS_ACC_Y(p_wpd, data[3], data[5]);
					mpStatus[0]->ext.fs.fsAccZ =
						MAKE_MP_FS_ACC_Z(p_wpd, data[4], data[5]);

					CALC_MP_FS_BUTTON(mpStatus[0]->button, data[5]);

					if (!p_wpd->calibrated)
					{
						p_wpd->calibrated = TRUE;

						p_wpd->extConfig.fs.stickXCenter =
							mpStatus[0]->ext.fs.fsStickX;
						p_wpd->extConfig.fs.stickYCenter =
							mpStatus[0]->ext.fs.fsStickY;
					}

					s16 fsStickXClampVal = (u8)mpStatus[0]->ext.fs.fsStickX
					                     - (u8)p_wpd->extConfig.fs.stickXCenter;
					s16 fsStickYClampVal = (u8)mpStatus[0]->ext.fs.fsStickY
					                     - (u8)p_wpd->extConfig.fs.stickYCenter;

					if (fsStickXClampVal < -128)
						mpStatus[0]->ext.fs.fsStickX = -128;
					else if (127 < fsStickXClampVal)
						mpStatus[0]->ext.fs.fsStickX = 127;
					else
						mpStatus[0]->ext.fs.fsStickX = fsStickXClampVal;

					if (fsStickYClampVal < -128)
					{
						mpStatus[0]->ext.fs.fsStickY = -128;
						goto hack;
					}
					else if (127 < fsStickYClampVal)
					{
						mpStatus[0]->ext.fs.fsStickY = 127;
						goto hack;
					}
					else
					{
						mpStatus[0]->ext.fs.fsStickY = fsStickYClampVal;
						goto hack;
					}
				}
				else if (p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC)
				{
					mpStatus[0]->ext.cl.clLStickX =
						MAKE_MP_CL_STICK_LX(data[0]);
					mpStatus[0]->ext.cl.clLStickY =
						MAKE_MP_CL_STICK_LY(data[1]);
					mpStatus[0]->ext.cl.clRStickX =
						MAKE_MP_CL_STICK_RX(data[0], data[1], data[2]);
					mpStatus[0]->ext.cl.clRStickY =
						MAKE_MP_CL_STICK_RY(data[2]);
					mpStatus[0]->ext.cl.clTriggerL =
						MAKE_MP_CL_TRIGGER_L(data[2], data[3]);
					mpStatus[0]->ext.cl.clTriggerR =
						MAKE_MP_CL_TRIGGER_R(data[3]);
					mpStatus[0]->ext.cl.clButton =
						MAKE_MP_CL_BUTTON(data[4], data[5], data[0], data[1]);

					mpStatus[0]->ext.cl.clLStickX -= (s16)0x200;
					mpStatus[0]->ext.cl.clLStickY -= (s16)0x200;
					mpStatus[0]->ext.cl.clRStickX -= (s16)0x200;
					mpStatus[0]->ext.cl.clRStickY -= (s16)0x200;

					if (!p_wpd->calibrated)
					{
						p_wpd->calibrated = TRUE;

						p_wpd->extConfig.cl.lStickXCenter =
							mpStatus[0]->ext.cl.clLStickX;
						p_wpd->extConfig.cl.lStickYCenter =
							mpStatus[0]->ext.cl.clLStickY;
						p_wpd->extConfig.cl.rStickXCenter =
							mpStatus[0]->ext.cl.clRStickX;
						p_wpd->extConfig.cl.rStickYCenter =
							mpStatus[0]->ext.cl.clRStickY;
						p_wpd->extConfig.cl.triggerLZero =
							mpStatus[0]->ext.cl.clTriggerL;
						p_wpd->extConfig.cl.triggerRZero =
							mpStatus[0]->ext.cl.clTriggerR;
					}

					CLAMP_CL_STICK_LX(p_wpd, mpStatus[0]->ext.cl.clLStickX,
					                  -512, 511);
					CLAMP_CL_STICK_LY(p_wpd, mpStatus[0]->ext.cl.clLStickY,
					                  -512, 511);
					CLAMP_CL_STICK_RX(p_wpd, mpStatus[0]->ext.cl.clRStickX,
					                  -512, 511);
					CLAMP_CL_STICK_RY(p_wpd, mpStatus[0]->ext.cl.clRStickY,
					                  -512, 511);

					if (mpStatus[0]->ext.cl.clTriggerL > 72)
						mpStatus[0]->ext.cl.clButton |= WPAD_BUTTON_CL_FULL_L;

					if (mpStatus[0]->ext.cl.clTriggerR > 72)
						mpStatus[0]->ext.cl.clButton |= WPAD_BUTTON_CL_FULL_R;

					mpStatus[0]->ext.cl.clTriggerL = 0;
					mpStatus[0]->ext.cl.clTriggerR = 0;
				}
			}
		}
		else
		{
			mpStatus[0]->ext = rxBuf->ext;
			CALC_MP_PT_MAIN_BUTTON(mpStatus[0]->button, rxBuf);

			mpStatus[0]->stat = MAKE_MP_PT_MAIN_STAT(data[3], data[4]);
			if (mpStatus[0]->stat & WPAD_MPLS_STATUS_EXTENSION_CONNECTED)
				RECALC_MP_PT_MAIN_STAT(mpStatus[0]->stat, rxBuf);

			mpStatus[0]->pitch = MAKE_MP_PT_MAIN_PITCH(data[5], data[2]);
			mpStatus[0]->yaw = MAKE_MP_PT_MAIN_YAW(data[3], data[0]);
			mpStatus[0]->roll = MAKE_MP_PT_MAIN_ROLL(data[4], data[1]);
		}
hack:; // What
	}
	else
	{
		mpStatus[0]->err = WPAD_EBADE;
	}

	if (mpStatus[0]->err != WPAD_ESUCCESS)
		return;

	u8 hasReadExtType2 = p_wpd->hasReadExtType2;

	if (!(mpStatus[0]->stat & WPAD_MPLS_STATUS_EXTENSION_CONNECTED))
	{
		if (p_wpd->parseMPState != 5)
			hasReadExtType2 = FALSE;

		p_wpd->hasReadExtType2 = FALSE;
		p_wpd->parseMPState = 0;
		p_wpd->devType = WPAD_DEV_MOTION_PLUS;

		/* ~(WPAD_MPLS_STATUS_EXTENSION_DATA_VALID
		 * | WPAD_MPLS_STATUS_EXTENSION_CONNECTED)
		 */
		mpStatus[0]->stat &= 0xbe;

		if (hasReadExtType2 && p_wpd->extensionCB)
			(*p_wpd->extensionCB)(chan, p_wpd->devType);
	}
	else if (!hasReadExtType2 && p_wpd->parseMPState == 0)
	{
		if (WPADiSendReadData(&p_wpd->extCmdQueue, p_wpd->wmReadDataBuf, 4,
		                      WM_REG_EXTENSION_EXT_TYPE_2, NULL))
		{
			p_wpd->hasReadExtType2 = TRUE;
			p_wpd->parseMPState = 1;
		}
	}

	if (p_wpd->parseMPState == 2 || p_wpd->parseMPState == 9)
	{
		if (WPADiSendReadData(&p_wpd->extCmdQueue, p_wpd->wmReadDataBuf, 16,
		                      WM_REG_EXTENSION_40, NULL))
		{
			p_wpd->parseMPState++;
		}
	}
	else if (p_wpd->parseMPState == 4)
	{
		p_wpd->parseMPState = 5;

		switch (_wpadDevType2[chan])
		{
		case 0:
			p_wpd->devType = WPAD_DEV_MPLS_PT_FS;
			break;

		case 1:
			p_wpd->devType = WPAD_DEV_MPLS_PT_CLASSIC;
			break;

		case 3:
			if (__OSInIPL)
				p_wpd->devType = WPAD_DEV_MPLS_PT_CLASSIC;
			else
				p_wpd->devType = WPAD_DEV_MPLS_PT_UNKNOWN;

			break;

		default:
			p_wpd->devType = WPAD_DEV_MPLS_PT_UNKNOWN;
			break;
		}

		if (p_wpd->extensionCB)
			(*p_wpd->extensionCB)(chan, p_wpd->devType);
	}
	else if (p_wpd->parseMPState == 6)
	{
		if (WPADiIsAvailableCmdQueue(&p_wpd->extCmdQueue, 2))
		{
			WPADiSendWriteDataCmd(&p_wpd->extCmdQueue, 0x01,
			                      WM_REG_EXTENSION_F3, NULL);
			WPADiSendReadData(&p_wpd->extCmdQueue, &p_wpd->parseMPBuf, 1,
			                  WM_REG_EXTENSION_F3, NULL);

			p_wpd->parseMPState = 7;
		}
	}
}

static void __parse_ext_data(WPADChannel chan, void *parseBuf,
                             u8 extFormat __attribute__((unused)), byte_t *data,
                             u8 length)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = parseBuf;

	if (p_wpd->extErr == WPAD_ENODEV)
	{
		p_wpd->extErr = status->err;
		p_wpd->extDevType = p_wpd->devType;
		p_wpd->extDataLength = length;

		memcpy(p_wpd->extDataBuf, data, length);
	}

	if (status->err == WPAD_ESUCCESS)
	{
		if (memcmp(data, _cExtInvalidData2, length) == 0)
		{
			status->err = WPAD_EINVAL;
		}
		else if (memcmp(data, _cExtInvalidData, length) == 0)
		{
			status->err = WPAD_EBADE;
			p_wpd->noParseExtCount = 3;
		}
		else if (!p_wpd->wpInfo.attach)
		{
			status->err = WPAD_EBADE;
			p_wpd->noParseExtCount = 3;
		}
		else if (p_wpd->noParseExtCount)
		{
			status->err = WPAD_EBADE;
			p_wpd->noParseExtCount--;
		}
	}

	if (p_wpd->extErr == WPAD_ESUCCESS && status->err == WPAD_EBADE)
		p_wpd->extErr = WPAD_EBADE;

	if (p_wpd->extDevType != p_wpd->devType)
		p_wpd->extErr = WPAD_EINVAL;

	if (p_wpd->extErr == WPAD_ESUCCESS)
	{
		p_wpd->noParseExtCount = 0;

		WPADiDecode(chan, p_wpd->extDataBuf, p_wpd->extDataLength, 0);

		if (p_wpd->devType == WPAD_DEV_FS)
		{
			__parse_fs_data(chan, (WPADFSStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_CLASSIC
		         || p_wpd->devType == WPAD_DEV_GUITAR
		         || p_wpd->devType == WPAD_DEV_DRUM
		         || p_wpd->devType == WPAD_DEV_TURNTABLE
		         || p_wpd->devType == WPAD_DEV_TAIKO)

		{
			__parse_cl_data(chan, (WPADCLStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_BULK_1
		         || p_wpd->devType == WPAD_DEV_BULK_2
		         || p_wpd->devType == WPAD_DEV_BULK_3
		         || p_wpd->devType == WPAD_DEV_BULK_4
		         || p_wpd->devType == WPAD_DEV_BULK_5
		         || p_wpd->devType == WPAD_DEV_BULK_6
		         || p_wpd->devType == WPAD_DEV_BULK_7
		         || p_wpd->devType == WPAD_DEV_BULK_8)
		{
			__parse_bk_data(chan, (WPADBKStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_TRAIN)
		{
			__parse_tr_data(chan, (WPADTRStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_BALANCE_CHECKER)
		{
			__parse_bl_data(chan, (WPADBLStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_VSM)
		{
			// note the use of dataFormat instead of devMode here
			__parse_vs_data(chan, (WPADVSStatus **)&parseBuf, p_wpd->dataFormat,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
		else if (p_wpd->devType == WPAD_DEV_MOTION_PLUS
		         || p_wpd->devType == WPAD_DEV_MPLS_PT_FS
		         || p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC
		         || p_wpd->devType == WPAD_DEV_MPLS_PT_UNKNOWN)
		{
			__parse_mp_data(chan, (WPADMPStatus **)&parseBuf, p_wpd->devMode,
			                p_wpd->extDataBuf, p_wpd->extDataLength);
		}
	}

	s8 tempErr = status->err;
	status->err = p_wpd->extErr;
	p_wpd->extErr = tempErr;

	p_wpd->extDevType = p_wpd->devType;
	p_wpd->extDataLength = length;

	memcpy(p_wpd->extDataBuf, data, length);
}

static void __a1_30_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
}

static void __a1_31_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_STANDARD,
	                 &hidReport[RPT_ACC_OFFSET], 0);
}

static void __a1_32_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT32_EXT_OFFSET], RPT32_EXT_LENGTH);
}

static void __a1_33_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_STANDARD,
	                 &hidReport[RPT_ACC_OFFSET], 0);
	__parse_dpd_data(chan, &status, p_wpd->currentDpdCommand,
	                 &hidReport[RPT33_DPD_OFFSET], RPT33_DPD_LENGTH);
}

static void __a1_34_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT34_EXT_OFFSET], RPT34_EXT_LENGTH);
}

static void __a1_35_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_STANDARD,
	                 &hidReport[RPT_ACC_OFFSET], 0);
	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT35_EXT_OFFSET], RPT35_EXT_LENGTH);
}

static void __a1_36_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_dpd_data(chan, &status, p_wpd->currentDpdCommand,
	                 &hidReport[RPT36_DPD_OFFSET], RPT36_DPD_LENGTH);
	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT36_EXT_OFFSET], RPT36_EXT_LENGTH);
}

static void __a1_37_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	__parse_btn_data(p_wpd, status, BTN_FORMAT_STANDARD, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_STANDARD,
	                 &hidReport[RPT_ACC_OFFSET], 0);
	__parse_dpd_data(chan, &status, p_wpd->currentDpdCommand,
	                 &hidReport[RPT37_DPD_OFFSET], RPT37_DPD_LENGTH);
	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT37_EXT_OFFSET], RPT37_EXT_LENGTH);
}

static void __a1_3d_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status __attribute__((unused)) = rxBuffer;

	__parse_ext_data(chan, rxBuffer, p_wpd->devMode,
	                 &hidReport[RPT3D_EXT_OFFSET], RPT3D_EXT_LENGTH);
}

static void __a1_3e_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	if (p_wpd->interleaveFlags == WPAD_ILBUF_NONE)
		memset(rxBuffer, 0, RX_BUFFER_SIZE);

	__parse_btn_data(p_wpd, status, BTN_FORMAT_INTERLEAVED, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_INTERLEAVED0,
	                 &hidReport[RPT_ACC_OFFSET], 0);
	__parse_dpdex_data(chan, (WPADStatusEx **)&rxBuffer, RPT3E_DPD0,
	                   &hidReport[RPT3E_DPD0_OFFSET], 0);
	__parse_dpdex_data(chan, (WPADStatusEx **)&rxBuffer, RPT3E_DPD1,
	                   &hidReport[RPT3E_DPD1_OFFSET], 0);

	BOOL intrStatus = OSDisableInterrupts();

	p_wpd->interleaveFlags |= WPAD_ILBUF_BUF3E;
	if (p_wpd->interleaveFlags == WPAD_ILBUF_ALL)
	{
		status->accZ -= (s16)p_wpd->devConfig.accZ0g;
		p_wpd->rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
		p_wpd->interleaveFlags = WPAD_ILBUF_NONE;
	}

	OSRestoreInterrupts(intrStatus);
}

static void __a1_3f_data_type(u8 chan, byte_t *hidReport, void *rxBuffer)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADStatus *status = rxBuffer;

	if (p_wpd->interleaveFlags == WPAD_ILBUF_NONE)
		memset(rxBuffer, 0, RX_BUFFER_SIZE);

	__parse_btn_data(p_wpd, status, BTN_FORMAT_INTERLEAVED, hidReport, 0);
	__parse_acc_data(chan, &status, ACC_FORMAT_INTERLEAVED1,
	                 &hidReport[RPT_ACC_OFFSET], 0);
	__parse_dpdex_data(chan, (WPADStatusEx **)&rxBuffer, RPT3F_DPD2,
	                   &hidReport[RPT3F_DPD2_OFFSET], 0);
	__parse_dpdex_data(chan, (WPADStatusEx **)&rxBuffer, RPT3F_DPD3,
	                   &hidReport[RPT3F_DPD3_OFFSET], 0);

	BOOL intrStatus = OSDisableInterrupts();

	p_wpd->interleaveFlags |= WPAD_ILBUF_BUF3F;
	if (p_wpd->interleaveFlags == WPAD_ILBUF_ALL)
	{
		status->accZ -= (s16)p_wpd->devConfig.accZ0g;
		p_wpd->rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
		p_wpd->interleaveFlags = WPAD_ILBUF_NONE;
	}

	OSRestoreInterrupts(intrStatus);
}

static void __a1_unused_report(u8 chan __attribute__((unused)),
                               byte_t *hidReport __attribute__((unused)),
                               void *rxBuffer __attribute__((unused)))
{
	return;
}

static void __wpadCertReset(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->certValidityStatus = WPAD_CERT_UNCHECKED;
	p_wpd->certWorkBusy = FALSE;
	p_wpd->certChallengeRandomBit = -1;
	p_wpd->certState = WPAD_STATE_CERT_INVALID;
	p_wpd->certStateWorkMs = 0;
	p_wpd->certWorkCounter = 0;
	p_wpd->certWorkMs = 0;

	memset(p_wpd->certBuf0, 0, sizeof p_wpd->certBuf0);
	memset(p_wpd->certBuf1, 0, sizeof p_wpd->certBuf1);
	memset(p_wpd->certBufBig, 0, sizeof p_wpd->certBufBig);
	p_wpd->certBuf0[0] = p_wpd->certBuf1[0] = p_wpd->certBufBig[0] = 1;

	p_wpd->wmParamOffset = 0;
}
