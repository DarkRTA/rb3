#ifndef RVL_SDK_WPAD_INTERNAL_WPAD_H
#define RVL_SDK_WPAD_INTERNAL_WPAD_H

#include <revolution/wpad/WPAD.h>

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "lint.h" // ULONG
#include "WPADHIDParser.h" // RPT_MAX_SIZE
#include "WPADMem.h"
#include "WPADMem2.h"


#include <revolution/OS/OSTime.h>
#include <revolution/OS/OSThread.h>

//#include "context_rvl.h"

/*******************************************************************************
 * macros
 */

// WPADStatusEx is the largest WPADStatus variant (size 0x5a)
// 0x20 is an arbitrary power of 2 that rounds up to 0x60
#define RX_BUFFER_SIZE					ROUND_UP(sizeof(WPADStatusEx), 0x20)

#define WPAD_CONFIG_BLOCK_CHECKSUM_BIAS	0x55
#define WPAD_MAX_CONFIG_BLOCKS			2

#define WPAD_DPD_CONFIG_BLOCK_CHECKSUM	10
#define WPAD_DPD_CONFIG_BLOCK_SIZE		11

#define WPAD_DEV_CONFIG_BLOCK_CHECKSUM	9
#define WPAD_DEV_CONFIG_BLOCK_SIZE		10

// for WPADDevConfig::dpd::obj
#define DPD_CFG_OBJ_BL					0
#define DPD_CFG_OBJ_BR					1
#define DPD_CFG_OBJ_TR					2
#define DPD_CFG_OBJ_TL					3

/*
 * Wiimote memory addresses
 */

// https://wiibrew.org/wiki/Wiimote#EEPROM_Memory
#define WM_ADDR_MEM_DEV_CONFIG_0		WM_MEM_ADDR(0x0000)
#define WM_ADDR_MEM_GAME_INFO_0			WM_MEM_ADDR(0x002a)
#define WM_ADDR_MEM_GAME_INFO_1			WM_MEM_ADDR(0x0062)

// out of range??? wiibrew says the wiimote only has 0x1600 bytes of memory
#define WM_ADDR_MEM_176C				WM_MEM_ADDR(0x176c)
#define WM_ADDR_MEM_1770				WM_MEM_ADDR(0x1770)

/*
 * Wiimote extension register addresses
 */

// Speaker register addresses
#define WM_REG_SPEAKER_01				WM_EXT_REG_ADDR(SPEAKER, 0x01)
#define WM_REG_SPEAKER_08				WM_EXT_REG_ADDR(SPEAKER, 0x08)
#define WM_REG_SPEAKER_09				WM_EXT_REG_ADDR(SPEAKER, 0x09)

// Extension register addresses
#define WM_REG_EXTENSION_CONFIG			WM_EXT_REG_ADDR(EXTENSION, 0x20)
#define WM_REG_EXTENSION_40				WM_EXT_REG_ADDR(EXTENSION, 0x40)
#define WM_REG_EXTENSION_CERT_PARAM		WM_EXT_REG_ADDR(EXTENSION, 0x50)
#define WM_REG_EXTENSION_F0				WM_EXT_REG_ADDR(EXTENSION, 0xf0)
#define WM_REG_EXTENSION_CERT_CHALLENGE	WM_EXT_REG_ADDR(EXTENSION, 0xf1)
#define WM_REG_EXTENSION_F2				WM_EXT_REG_ADDR(EXTENSION, 0xf2)
#define WM_REG_EXTENSION_F3				WM_EXT_REG_ADDR(EXTENSION, 0xf3)
#define WM_REG_EXTENSION_EXT_TYPE_2		WM_EXT_REG_ADDR(EXTENSION, 0xf6)
#define WM_REG_EXTENSION_CERT_PROBE		WM_EXT_REG_ADDR(EXTENSION, 0xf7)
#define WM_REG_EXTENSION_FA				WM_EXT_REG_ADDR(EXTENSION, 0xfa)
#define WM_REG_EXTENSION_FB				WM_EXT_REG_ADDR(EXTENSION, 0xfb)
#define WM_REG_EXTENSION_DEV_MODE		WM_EXT_REG_ADDR(EXTENSION, 0xfe)
#define WM_REG_EXTENSION_ID_BYTE		WM_EXT_REG_ADDR(EXTENSION, 0xff)

#define WM_EXTENSION_CONFIG_SIZE		0x20	// 0xa40020 - 0xa4003f
#define WM_EXTENSION_CERT_PARAM_SIZE	0x40	// 0xa40050 - 0xa4008f

// Wiimote Motion Plus register addresses
#define WM_REG_MPLS_F0					WM_EXT_REG_ADDR(MOTION_PLUS, 0xf0)
#define WM_REG_MPLS_DEV_MODE			WM_EXT_REG_ADDR(MOTION_PLUS, 0xfe)
#define WM_REG_MPLS_ID_BYTE				WM_EXT_REG_ADDR(MOTION_PLUS, 0xff)

// IR camera register addresses
#define WM_REG_DPD_CONFIG_BLOCK_1		WM_EXT_REG_ADDR(DPD, 0x00)
#define WM_REG_DPD_CONFIG_BLOCK_2		WM_EXT_REG_ADDR(DPD, 0x1a)
#define WM_REG_DPD_30					WM_EXT_REG_ADDR(DPD, 0x30)
#define WM_REG_DPD_DATA_FORMAT			WM_EXT_REG_ADDR(DPD, 0x33)

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

// NoiZe filter? only thing i can think of idk
// probably confirmed since its only uses are in __wpadCalcAnalogNoise
typedef u8 WPADNZFilter;
enum WPADNZFilter_et
{
	WPAD_NZFILTER_ACC,
	WPAD_NZFILTER_DPD,
	WPAD_NZFILTER_EXT,
	WPAD_NZFILTER_MPLS,

	WPAD_MAX_NZFILTERS	/* name known from asserts */
};

// WPADiControlMpls
typedef u8 WPADMplsCommand;
enum WPADMplsCommand_et
{
	WPAD_MPLS_DISABLE	= 0x00,

	// the command here is actually the device mode
	WPAD_MPLS_MAIN		= WPAD_DEV_MODE_MPLS_PT_MAIN,
	WPAD_MPLS_FS		= WPAD_DEV_MODE_MPLS_PT_FS,
	WPAD_MPLS_CLASSIC	= WPAD_DEV_MODE_MPLS_PT_CLASSIC,

	// except for this
	WPAD_MPLS_CMD_80	= 0x80,
};

typedef u8 WPADMplsCBState;
enum WPADMplsCBState_et
{
	WPAD_STATE_MPLS_CB_START,
	WPAD_STATE_MPLS_CB_1,
	WPAD_STATE_MPLS_CB_CLEAR_DEV_MODE,
	WPAD_STATE_MPLS_CB_WRITE_PENDING_MPLS_DEV_MODE,
	WPAD_STATE_MPLS_CB_INIT_MPLS_EXT,
	WPAD_STATE_MPLS_CB_5,
	WPAD_STATE_MPLS_CB_GET_EXTENSION_ID,
	WPAD_STATE_MPLS_CB_DONE,
	WPAD_STATE_MPLS_CB_RESET,
};

typedef s8 WPADCertValidityStatus;
enum WPADCertValidityStatus_et
{
	WPAD_CERT_INVALID	= -1,
	WPAD_CERT_UNCHECKED	=  0,
	WPAD_CERT_VALID		=  1,
};

typedef s8 WPADCertState;
enum WPADCertState_et
{
	WPAD_STATE_CERT_PROBE_X,
	WPAD_STATE_CERT_GET_X,
	WPAD_STATE_CERT_VERIFY_X,
	WPAD_STATE_CERT_CHALLENGE,
	WPAD_STATE_CERT_PROBE_Y,
	WPAD_STATE_CERT_GET_Y,
	WPAD_STATE_CERT_VERIFY_Y,
	WPAD_STATE_CERT_CALC_MUL_X,
	WPAD_STATE_CERT_CALC_MOD_X,
	WPAD_STATE_CERT_CALC_MUL_Y,
	WPAD_STATE_CERT_CALC_MOD_Y,
	WPAD_STATE_CERT_CHECK,
	WPAD_STATE_CERT_SUCCESS,

	WPAD_STATE_CERT_ERROR_TIMEOUT	= 120,
	WPAD_STATE_CERT_INVALID			= -1,

#define WPAD_STATE_CERT_ETIME	WPAD_STATE_CERT_ERROR_TIMEOUT
};

typedef u8 WPADExtensionState;
enum WPADExtensionState_et
{
	WPAD_STATE_EXT_UNINITIALIZED,
	WPAD_STATE_EXT_INITIALIZED,
	WPAD_STATE_EXT_ENCRYPTED,
	WPAD_STATE_EXT_ENCRYPTED_3RD,
};

// __rvl_wpadcb::radioQuality
typedef u8 WPADRadioQuality;
enum WPADRadioQuality_et
{
	WPAD_RADIO_QUALITY_GOOD,	// 80+
	WPAD_RADIO_QUALITY_BAD		// 80-
	// if radioQuality calculation == 80, state stays the same
};

enum WPADInterleaveBufferFlags
{
	WPAD_ILBUF_NONE		= 0,

	WPAD_ILBUF_BUF3E	= (1 << 0),
	WPAD_ILBUF_BUF3F	= (1 << 1),

	WPAD_ILBUF_ALL		= WPAD_ILBUF_BUF3E | WPAD_ILBUF_BUF3F,
};

struct WPADCmd
{
	u32				reportID;				// size 0x04, offset 0x00
	byte_t			dataBuf[RPT_MAX_SIZE];	// size 0x15, offset 0x04
	// 1 byte padding (alignment)
	u16				dataLength;				// size 0x02, offset 0x1a
	void			*dstBuf;				// size 0x04, offset 0x1c
	u16				readLength;				// size 0x02, offset 0x20
	// 2 bytes padding (alignment? probably)
	u32				readAddress;			// size 0x04, offset 0x24
	WPADInfo		*statusReportOut;		// size 0x04, offset 0x28
	WPADCallback	*cmdCB;					// size 0x04, offset 0x2c
}; // size 0x30

struct WPADCmdQueue
{
	s8				indexOut;	// size 0x01, offset 0x00
	s8				indexIn;	// size 0x01, offset 0x01
	// 2 bytes padding (alignment? probably)
	struct WPADCmd	*queue;		// size 0x04, offset 0x04
	u32				length;		// size 0x04, offset 0x08
}; // size 0x0c

struct WPADMplsCalibration
{
	f32	pitchZero;	// size 0x04, offset 0x00
	f32	pitchScale;	// size 0x04, offset 0x04

	f32	yawZero;	// size 0x04, offset 0x08
	f32	yawScale;	// size 0x04, offset 0x0c

	f32	rollZero;	// size 0x04, offset 0x10
	f32	rollScale;	// size 0x04, offset 0x14

	s32	degrees;	// size 0x04, offset 0x18
}; // size 0x1c

struct WPADDevConfig
{
	DPDObject	dpd[WPAD_MAX_DPD_OBJECTS];	// size 0x20, offset 0x00

	s16			accX0g;						// size 0x02, offset 0x20
	s16			accY0g;						// size 0x02, offset 0x22
	s16			accZ0g;						// size 0x02, offset 0x24

	s16			accX1g;						// size 0x02, offset 0x26
	s16			accY1g;						// size 0x02, offset 0x28
	s16			accZ1g;						// size 0x02, offset 0x2a

	u8			motor;						// size 0x01, offset 0x2c
	u8			volume;						// size 0x01, offset 0x2d
	byte_t		__pad0[2]; // padding to 0x30?
}; // size 0x30

struct WPADExtConfig
{
	union
	{
		struct WPADFSConfig
		{
			s16	stickXCenter;	// size 0x02, offset 0x00
			s16	at_0x02;		// size 0x02, offset 0x02
			s16	at_0x04;		// size 0x02, offset 0x04
			s16	stickYCenter;	// size 0x02, offset 0x06
			s16	at_0x08;		// size 0x02, offset 0x08
			s16	at_0x0a;		// size 0x02, offset 0x0a

			s16	accX0g;			// size 0x02, offset 0x0c
			s16	accY0g;			// size 0x02, offset 0x0e
			s16	accZ0g;			// size 0x02, offset 0x10

			s16	accX1g;			// size 0x02, offset 0x12
			s16	accY1g;			// size 0x02, offset 0x14
			s16	accZ1g;			// size 0x02, offset 0x16
		} fs; // size 0x1a

		struct WPADCLConfig
		{
			s16	lStickXCenter;	// size 0x02, offset 0x00
			s16	at_0x02;		// size 0x02, offset 0x02
			s16	at_0x04;		// size 0x02, offset 0x04
			s16	lStickYCenter;	// size 0x02, offset 0x06
			s16	at_0x08;		// size 0x02, offset 0x08
			s16	at_0x0a;		// size 0x02, offset 0x0a

			s16	rStickXCenter;	// size 0x02, offset 0x0c
			s16	at_0x0e;		// size 0x02, offset 0x0e
			s16	at_0x10;		// size 0x02, offset 0x10
			s16	rStickYCenter;	// size 0x02, offset 0x12
			s16	at_0x14;		// size 0x02, offset 0x14
			s16	at_0x16;		// size 0x02, offset 0x16

			u8	triggerLZero;	// size 0x01, offset 0x18
			u8	triggerRZero;	// size 0x01, offset 0x19
		} cl; // size 0x1a

		byte_t FORCE_UNION_SIZE[0x1c]; // alignment?
	}; // size 0x1c

	struct WPADMplsConfig
	{
		struct WPADMplsCalibration	high;		// size 0x1c, offset 0x00
		struct WPADMplsCalibration	low;		// size 0x1c, offset 0x1c
		u32							calibCRC;	// size 0x04, offset 0x38
		u16							calibID;	// size 0x02, offset 0x3c
		// 2 bytes padding (alignment? probably)
	} mpls; // size 0x40, offset 0x01a
}; // size 0x5c


typedef struct /* possibly untagged, like kpad */
{
	WPADGameInfo			gameInfo;						// size 0x038, offset 0x000
	long signed				at_0x038[2];					// size 0x008, offset 0x038	/* unknown */ // WPADResult[2]? see __wpadGetGameInfo
	byte_t					rxBufMain[RX_BUFFER_SIZE];		// size 0x060, offset 0x040
	byte_t					rxBufs[2][RX_BUFFER_SIZE];		// size 0x060, offset 0x0a0
	struct WPADCmdQueue		stdCmdQueue;					// size 0x00c, offset 0x160
	struct WPADCmd			stdCmdQueueList[24];			// size 0x480, offset 0x16c
	struct WPADCmdQueue		extCmdQueue;					// size 0x00c, offset 0x5ec
	struct WPADCmd			extCmdQueueList[12];			// size 0x240, offset 0x16c
	WPADInfo				wpInfo; 						// size 0x018, offset 0x838
	WPADInfo				*wpInfoOut;						// size 0x004, offset 0x850
	struct WPADDevConfig	devConfig;						// size 0x030, offset 0x854
	struct WPADExtConfig	extConfig;						// size 0x05c, offset 0x884
	WPADCallback			*cmdBlkCB;						// size 0x004, offset 0x8e0
	WPADExtensionCallback	*extensionCB;					// size 0x004, offset 0x8e4
	WPADConnectCallback		*connectCB;						// size 0x004, offset 0x8e8
	WPADSamplingCallback	*samplingCB;					// size 0x004, offset 0x8ec
	void					*samplingBuf;					// size 0x004, offset 0x8f0
	u32						samplingBufIndex;				// size 0x004, offset 0x8f4
	u32						samplingBufSize;				// size 0x004, offset 0x8f8
	WPADDataFormat			dataFormat;						// size 0x004, offset 0x8fc
	WPADResult				status;							// size 0x004, offset 0x900	/* name known from asserts */
	u8						statusReqBusy;					// size 0x001, offset 0x904
	u8						devType;						// size 0x001, offset 0x905	/* possible name from assert */
	u8						devMode;						// size 0x001, offset 0x906
	WUDDevHandle			devHandle;						// size 0x001, offset 0x907
	int signed				unk_0x908;						// size 0x001, offset 0x908	/* unknown */
	u8						rxBufIndex;						// size 0x001, offset 0x90c
	char signed				unk_0x90d;						// size 0x001, offset 0x90d	/* unknown */
	u8						defaultDpdSize;					// size 0x001, offset 0x90e	// maybe?
	u8						currentDpdCommand;				// size 0x001, offset 0x90f
	u8						pendingDpdCommand;				// size 0x001, offset 0x910
	WPADRadioQuality		radioQuality;					// size 0x001, offset 0x911
	u8						radioQualityOkMs;				// size 0x001, offset 0x912	// see __wpadCalcRadioQuality
	u8						audioFrames;					// size 0x001, offset 0x913	/* name known from asserts */
	u32						motorBusy;						// size 0x004, offset 0x914
	BOOL					motorRunning;					// size 0x004, offset 0x918	// signedness known (yes)
	BOOL					used;							// size 0x004, offset 0x91c	/* name known from asserts */
	BOOL					handshakeFinished;				// size 0x004, offset 0x920
	int						configIndex;					// size 0x004, offset 0x924
	OSThreadQueue			threadQueue;					// size 0x008, offset 0x928	/* purpose unknown */
	byte_t					__pad0[4]; /* unknown (can't be alignment) */
	u8						controlMplsBusy;				// size 0x001, offset 0x934
	byte_t					mplsCBReadBuf[2];				// size 0x002, offset 0x935
	u8						mplsCBCounter;					// size 0x001, offset 0x937	// idk???
	u8						pendingMplsCommand;				// size 0x001, offset 0x938
	u8						noParseMplsCount;				// size 0x001, offset 0x939
	u8						isInitingMpls;					// size 0x001, offset 0x93a	// maybe?
	u8						hasReadExtType2;				// size 0x001, offset 0x93b	// maybe?
	char unsigned			unk_0x93c;						// size 0x001, offset 0x93c	/* unknown */
	u8						parseMPState;					// size 0x001, offset 0x93d
	u8						wmParamOffset;					// size 0x001, offset 0x93e
	u8						certWorkCounter;				// size 0x001, offset 0x93f	// idk???
	u16						certWorkMs;						// size 0x002, offset 0x940
	s16						certStateWorkMs;				// size 0x002, offset 0x942
	s8						certChallengeRandomBit;			// size 0x001, offset 0x944
	u8						certWorkBusy;					// size 0x001, offset 0x945
	WPADCertValidityStatus	certValidityStatus;				// size 0x001, offset 0x946
	WPADCertState			certState;						// size 0x001, offset 0x947
	ULONG					*certParamPtr;					// size 0x001, offset 0x948
	ULONG					certBuf0[16 + 2];				// size 0x048, offset 0x94c
	ULONG					certBuf1[16 + 2];				// size 0x048, offset 0x994
	ULONG					certBufBig[64 + 2];				// size 0x048, offset 0x994
	int signed				unk_0xae4;						// size 0x004, offset 0xae4	/* unknown */
	OSTime					lastControllerDataUpdate;		// size 0x008, offset 0xae8
	u16						filterDiff[WPAD_MAX_NZFILTERS];	// size 0x008, offset 0xaf0
	u16						filterSame[WPAD_MAX_NZFILTERS];	// size 0x008, offset 0xaf8
	OSTime					lastReportSendTime;				// size 0x008, offset 0xb00
	char unsigned			unk_0xb08;						// size 0x001, offset 0xb08	/* unknown */
	u8						calibrated;						// size 0x001, offset 0xb09
	u16						recalibHoldMs;					// size 0x002, offset 0xb0a
	byte_t					encryptionKey[16];				// size 0x010, offset 0xb0c
	byte_t					decryptAddTable[8];				// size 0x008, offset 0xb1c
	byte_t					decryptXorTable[8];				// size 0x008, offset 0xb24
	byte_t					wmReadDataBuf[64];				// size 0x020, offset 0xb2c
	byte_t					*wmReadDataPtr;					// size 0x004, offset 0xb6c
	u32						wmReadAddress;					// size 0x004, offset 0xb70
	int						wmReadHadError;					// size 0x004, offset 0xb74
	u16						wmReadLength;					// size 0x002, offset 0xb78
	char signed				unk_0xb7a;						// size 0x001, offset 0xb7a	/* unknown */
	u8						radioSensitivity;				// size 0x001, offset 0xb7b
	u16						copyOutCount;					// size 0x002, offset 0xb7c
	u8						sleeping;						// size 0x001, offset 0xb7e
	u8						lastReportID;					// size 0x001, offset 0xb7f
	WPADCallback			*getInfoCB;						// size 0x004, offset 0xb80
	u8						getInfoBusy;					// size 0x001, offset 0xb84
	u8						extState;						// size 0x001, offset 0xb85
	u8						disableContReport;				// size 0x001, offset 0xb86
	u8						blcBattery;						// size 0x001, offset 0xb87
	u8						savedDevType;					// size 0x001, offset 0xb88	// maybe?
	u8						extWasDisconnected;				// size 0x001, offset 0xb89
	s16						reconnectExtMs;					// size 0x002, offset 0xb8a
	struct WPADMemBlock		memBlock;						// size 0x014, offset 0xb8c
	WPADCallback			*controlMplsCB;					// size 0x004, offset 0xba0
	u8						parseMPBuf;						// size 0x001, offset 0xba4
	u8						certProbeByte;					// size 0x001, offset 0xba5
	u8						dpdBusy;						// size 0x001, offset 0xba6
	u8						interleaveFlags;				// size 0x001, offset 0xba7
	u32						mplsCBReadAddress;				// size 0x004, offset 0xba8
	WPADMplsCBState			mplsCBState;					// size 0x001, offset 0xbac
	u8						mplsUptimeMs;					// size 0x001, offset 0xbad
	s8						certMayVerifyByCalibBlock;		// size 0x001, offset 0xbae
	byte_t					__pad1[2]; /* unknown (can't be alignment) */
	u8						certProbeStartingValue;			// size 0x001, offset 0xbb1
	u16						lastMplsCalibID;				// size 0x002, offset 0xbb2
	u32						lastMplsCalibCRC;				// size 0x004, offset 0xbb4
	u8						noParseExtCount;				// size 0x001, offset 0xbb8
	s8						extErr;							// size 0x001, offset 0xbb9
	u8						extDataLength;					// size 0x001, offset 0xbba
	u8						extDevType;						// size 0x001, offset 0xbbb
	char unsigned			unk_0xbbc;						// size 0x001, offset 0xbbc	/* unknown */ // related to VSM
	byte_t					__pad2[3]; /* unknown (can't be alignment) */
	byte_t					extDataBuf[32];					// size 0x020, offset 0xbc0
} wpad_cb_st; // size 0xbe0

/*******************************************************************************
 * external variables
 */

extern wpad_cb_st *__rvl_p_wpadcb[WPAD_MAX_CONTROLLERS];

/*******************************************************************************
 * functions
 */

void WPADiExcludeButton(WPADChannel chan);
void WPADiCopyOut(WPADChannel chan);

u8 WPADiGetMplsStatus(WPADChannel chan);

WPADResult WPADiControlMpls(WPADChannel chan, WPADMplsCommand command,
                            WPADCallback *cb);

void WPADiGetMplsCalibration(WPADChannel chan, struct WPADMplsCalibration *high,
                             struct WPADMplsCalibration *low);
BOOL WPADiSendSetPort(struct WPADCmdQueue *cmdQueue, u8 port, WPADCallback *cb);
BOOL WPADiSendSetReportType(struct WPADCmdQueue *cmdQueue, s32 format,
                            BOOL notContinuous, WPADCallback *cb);
BOOL WPADiSendEnableDPD(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                          WPADCallback *cb);
BOOL WPADiSendEnableSpeaker(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                            WPADCallback *cb);
BOOL WPADiSendGetContStat(struct WPADCmdQueue *cmdQueue, WPADInfo *wpInfoOut,
                          WPADCallback *cb);
BOOL WPADiSendWriteDataCmd(struct WPADCmdQueue *cmdQueue, u8 cmd, u32 address,
                           WPADCallback *cb);
BOOL WPADiSendWriteData(struct WPADCmdQueue *cmdQueue, const void *p_buf,
                        u16 len, u32 address, WPADCallback *cb);
BOOL WPADiSendReadData(struct WPADCmdQueue *cmdQueue, void *p_buf, u16 len,
                       u32 address, WPADCallback *cb);
BOOL WPADiSendStreamData(struct WPADCmdQueue *cmdQueue, const void *p_buf,
                         u16 len);
BOOL WPADiSendMuteSpeaker(struct WPADCmdQueue *cmdQueue, BOOL muted,
                          WPADCallback *cb);
BOOL WPADiSendDPDCSB(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                     WPADCallback *cb);
BOOL WPADiIsAvailableCmdQueue(struct WPADCmdQueue *cmdQueue, s8 count);

void WPADiClearQueue(struct WPADCmdQueue *cmdQueue);

#if !defined(NDEBUG)
BOOL WPADiIsDummyExtension(WPADChannel chan);
#endif // !defined(NDEBUG)

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_WPAD_H
