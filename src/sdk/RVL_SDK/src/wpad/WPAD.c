#include <revolution/wpad/WPAD.h>
#include "WPAD.h"

/*******************************************************************************
 * headers
 */

#include <string.h>

#include <types.h>

#include "lint.h"
#include "WPADHIDParser.h"
#include "WPADMem.h"
#include "WUD.h"

#include <revolution/bte/context_bte.h>
#include <revolution/os/OSAlarm.h>
#include <revolution/os/OSCache.h>
#include <revolution/os/OSContext.h>
#include <revolution/os/OSError.h>
#include <revolution/os/OSInterrupt.h>
#include <revolution/os/OSReset.h>
#include <revolution/os/OSTime.h>
// #include <revolution/os/__OSGlobals.h>
#include <revolution/ipc/ipcMain.h>
#include <revolution/sc/scapi.h>
#include <revolution/sc/scsystem.h>
#include <revolution/vi/vi.h>

/*******************************************************************************
 * macros
 */

#if defined(NDEBUG)
#define RVL_SDK_WPAD_VERSION_STRING	\
	"<< RVL_SDK - WPAD \trelease build: Dec 11 2009 15:59:48 (" STR(__CWCC__) "_" STR(__CWBUILD__) ") >>"
#else
#define RVL_SDK_WPAD_VERSION_STRING	\
	"<< RVL_SDK - WPAD \tdebug build: Dec 11 2009 15:55:10 (" STR(__CWCC__) "_" STR(__CWBUILD__) ") >>"
#endif

/*******************************************************************************
 * local function declarations
 */

static void *__wpadNoAlloc(size_t size);
static int __wpadNoFree(void *ptr);

static BOOL OnShutdown(OSShutdownPass pass, OSShutdownEvent event);
static WPADResult __wpadSendDataSub(WPADChannel chan, struct WPADCmd cmdBlk);
static WPADResult __wpadSendData(WPADChannel chan, struct WPADCmd cmdBlk);
static void __wpadCalcRadioQuality(WPADChannel chan);
static u32 __wpadFmt2Size(WPADDataFormat fmt);
static u8 __wpadIsButtonChanged(WPADButton lhs, WPADButton rhs);
static u8 __wpadIsAnalogChanged(s32 lhs, s32 rhs, s32 minDiff);
static BOOL __wpadCalcAnalogNoise(wpad_cb_st *p_wpd, WPADNZFilter filter_type,
                                  BOOL analogChanged);
static BOOL __wpadIsControllerDataChanged(wpad_cb_st *p_wpd, void *lhs,
                                          void *rhs);
static void __wpadCalcRecalibration(WPADChannel chan, void *status);
static void __wpadCalcControllerData(WPADChannel chan);
static BOOL __wpadProcExtCommand(WPADChannel chan, BOOL previousSuccess);
static void __wpadRumbleMotor(WPADChannel chan, BOOL procSuccess);
static BOOL __wpadProcCommand(WPADChannel chan, BOOL previousSuccess);
static void __wpadCalcSystemSettings(void);
static void __wpadCalcAfh(void);
static BOOL __wpadCalcReconnectWait(void);
static void __wpadManageHandler(OSAlarm *alarm, OSContext *context);
static void __wpadManageHandler0(OSAlarm *alarm, OSContext *context);
static void __wpadClearControlBlock(WPADChannel chan);
static void __wpadInitSub(void);

static void __wpadShutdown(BOOL saveSimpleDevs);
static void __wpadCleanup(void);
static void __wpadResetModule(BOOL saveSimpleDevs);
static void __wpadReconnectStart(BOOL saveSimpleDevs);

static void __wpadSetupConnectionCallback(WPADChannel chan, WPADResult result);
static void __wpadAbortConnectionCallback(WPADChannel chan, WPADResult result);
static void __wpadInitConnectionCallback(WPADChannel chan, WPADResult result);
static WPADChannel __wpadRetrieveChannel(WUDDevInfo *devInfo);
static void __wpadConnectionCallback(WUDDevInfo *devInfo, u8 success);
static void __wpadReceiveCallback(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len);
static WPADResult __wpadGetConnectionStatus(WPADChannel chan);
static void __wpadDisconnectCallback(WPADChannel chan, WPADResult result);
static inline void __wpadDisconnect(WPADChannel chan, BOOL afkDisconnect);

static void __wpadInfoCallback(WPADChannel chan, WPADResult result);

static void __wpadDpdCallback(WPADChannel chan, WPADResult result);

static void __wpadMplsCallback(WPADChannel chan, WPADResult result);

static s8 __wpadGetQueueSize(struct WPADCmdQueue *cmdQueue);

static BOOL __wpadPushCommand(struct WPADCmdQueue *cmdQueue,
                              struct WPADCmd cmdBlk);
static BOOL __wpadGetCommand(struct WPADCmdQueue *cmdQueue,
                             struct WPADCmd *cmdBlkOut);
static BOOL __wpadPopCommand(struct WPADCmdQueue *cmdQueue);
static BOOL __wpadSetSensorBarPower(BOOL enabled);
static void __wpadSetScreenSaverFlag(BOOL disabled);
static u8 __wpadGetDpdSensitivity(void);
static u8 __wpadGetSensorBarPosition(void);
static u32 __wpadGetMotorMode(void);
static u8 __wpadClampSpeakerVolume(u8 volume);
static u8 __wpadGetSpeakerVolume(void);
static u16 __wpadGetBTEBufferStatus(WPADChannel chan);
static u16 __wpadGetBTMBufferStatus(WPADChannel chan);

static void __wpadCertFailed(WPADChannel chan);
static void __wpadCertCalcMulX(WPADChannel chan);
static void __wpadCertCalcModX(WPADChannel chan);
static void __wpadCertCalcMulY(WPADChannel chan);
static void __wpadCertCalcModY(WPADChannel chan);
static void __wpadCertChallengeCallback(WPADChannel chan, WPADResult result);
static void __wpadCertChallenge(WPADChannel chan);
static void __wpadCertProbeReadyCallback(WPADChannel chan, WPADResult result);
static void __wpadCertProbeReady(WPADChannel chan);
static void __wpadCertGetParamCallback(WPADChannel chan, WPADResult result);
static u8 __wpadCertGetParam(WPADChannel chan, ULONG *certParamOut);
static void __wpadCertGetParamX(WPADChannel chan);
static void __wpadCertVerifyParamX(WPADChannel chan);
static inline void __wpadCertGetParamY(WPADChannel chan);
static void __wpadCertVerifyParamY(WPADChannel chan);
static void __wpadCertWork(WPADChannel chan);

/*******************************************************************************
 * variables
 */

// .rodata

// clang-format off
static const ULONG certn[] =
{
	16,

	0xa3dc5f11, 0x1b2ec797,
	0xac9657b8, 0xcbeb788d,
	0x991ef8b8, 0x70caa54e,
	0x071ce896, 0x63252cd0,
	0xfd8b6316, 0x9e835020,
	0xbf9ed1ef, 0x0f870932,
	0xbc88b819, 0xaf2c02e5,
	0x657bbfb9, 0x81194f1c,

	0
};

static const ULONG certv[] =
{
	16,

	0x99d2071a, 0x8d823a01,
	0x4c50a978, 0xd8a5bfff,
	0x4caf5ce8, 0x13a71cba,
	0x6fcff21b, 0x8c5399bf,
	0x8896982d, 0xcb6ec891,
	0x6ba136da, 0x25b8f224,
	0x8f0f42c0, 0x15ea9941,
	0xfdd1903e, 0x1af308b6,

	0
};
// clang-format on

// .data, .sdata
const char *__WPADVersion = RVL_SDK_WPAD_VERSION_STRING;
static OSShutdownFunctionInfo ShutdownFunctionInfo;

// .bss
static OSAlarm _wpadManageAlarm;
wpad_cb_st __rvl_wpadcb[WPAD_MAX_CONTROLLERS] __attribute__((aligned(0x20)));
static WUDDevHandle _wpadHandle2PortTable[WUD_MAX_DEV_ENTRY];
static byte_t __wpadManageHandlerStack[0x1000] __attribute__((aligned(0x20)));
wpad_cb_st *__rvl_p_wpadcb[WPAD_MAX_CONTROLLERS];

// .sdata
static s32 _wpadOnReconnect = -1;
static u16 _wpad_diff_count_threshold[WPAD_MAX_NZFILTERS] = {6, 4, 6, 12};
static u16 _wpad_hyst_count_threshold[WPAD_MAX_NZFILTERS] = {30, 30, 30, 30};

// .sbss
static OSAppType _wpadGameType;
static const char *_wpadGameCode;

#if !defined(NDEBUG)
static u8 _wpadDummyAttach[WPAD_MAX_CONTROLLERS];
#endif // !defined(NDEBUG)

static u8 _wpadSleepTime;
static u8 _wpadDpdSense;
static u8 _wpadSensorBarPos;
static BOOL _wpadRumbleFlag;
static u8 _wpadSpeakerVol;
static u8 _wpadSCSetting;
static u8 _wpadShutdownFlag;
static s8 _wpadAfhChannel;
static u8 _wpadIsUsedChannel[WPAD_MAX_CONTROLLERS];
static BOOL _wpadInitialized;
static BOOL _wpadUsedCallback;
__attribute__((weak)) BOOL _enabledBLK;
__attribute__((weak)) BOOL _enabledTBL;
__attribute__((weak)) BOOL _enabledTKO;
__attribute__((weak)) BOOL _enabledDRM;
__attribute__((weak)) BOOL _enabledGTR;
__attribute__((weak)) BOOL _enabledTRN;
__attribute__((weak)) BOOL _enabledVSM;
__attribute__((weak)) WPADInitFunc *_wpadBLKInit;
__attribute__((weak)) WPADInitFunc *_wpadTBLInit;
__attribute__((weak)) WPADInitFunc *_wpadTKOInit;
__attribute__((weak)) WPADInitFunc *_wpadDRMInit;
__attribute__((weak)) WPADInitFunc *_wpadGTRInit;
__attribute__((weak)) WPADInitFunc *_wpadTRNInit;
__attribute__((weak)) WPADInitFunc *_wpadVSMInit;
static s32 _wpadReconnectWait;
static BOOL _wpadStartup;
static u8 _wpadRumbleCnt[WPAD_MAX_CONTROLLERS];
static u8 _wpadExtCnt[WPAD_MAX_CONTROLLERS];
static u16 _wpadAfhCnt;
static u8 _wpadCheckCnt;
static u16 _wpadSenseCnt;
static u8 _wpadRegisterShutdownFunc;

/*******************************************************************************
 * functions
 */

static void *__wpadNoAlloc(size_t size __attribute__((unused)))
{
	return NULL;
}

static int __wpadNoFree(void *ptr __attribute__((unused)))
{
	return 0;
}

BOOL WPADIsEnabledVSM(void)
{
	return _enabledVSM;
}

BOOL WPADIsEnabledTRN(void)
{
	return _enabledTRN;
}

BOOL WPADIsEnabledGTR(void)
{
	return _enabledGTR;
}

BOOL WPADIsEnabledDRM(void)
{
	return _enabledDRM;
}

BOOL WPADIsEnabledTKO(void)
{
	return _enabledTKO;
}

BOOL WPADIsEnabledTBL(void)
{
	return _enabledTBL;
}

BOOL WPADIsEnabledBLK(void)
{
	return _enabledBLK;
}

__attribute__((weak)) WPADResult WBCSetupCalibration(void)
{
	return WPAD_ESUCCESS;
}

__attribute__((weak)) signed WBCGetCalibrationStatus(void)
{
	return 0;
}

__attribute__((weak)) signed WBCGetBatteryLevel(u8 param_1
                                                __attribute__((unused)))
{
	return 0;
}

// perhaps param_3 is ARRAY_LENGTH of param_2? who knows
__attribute__((weak)) WPADResult WBCRead(WPADBLStatus *param_1
                                         __attribute__((unused)),
                                         f64 *param_2 __attribute__((unused)),
                                         int param_3 __attribute__((unused)))
{
	return WPAD_ENODEV;
}

__attribute__((weak)) WPADResult WBCSetZEROPoint(f64 *param_1
                                                 __attribute__((unused)),
                                                 int param_2
                                                 __attribute__((unused)))
{
	return WPAD_ENODEV;
}

__attribute__((weak)) WPADResult WBCGetTGCWeight(
	f64 param_1 __attribute__((unused)), f64 *param_2 __attribute__((unused)),
	WPADBLStatus *param_3 __attribute__((unused)))
{
	return WPAD_ENODEV;
}

static BOOL OnShutdown(OSShutdownPass pass, OSShutdownEvent event)
{
	WUDLibStatus wudLibStatus = WUDGetStatus();

	if (pass != OS_SHUTDOWN_PASS_FIRST || wudLibStatus == WUD_LIB_STATUS_0)
		return TRUE;

	if (wudLibStatus == WUD_LIB_STATUS_4 || wudLibStatus == WUD_LIB_STATUS_1
	    || wudLibStatus == WUD_LIB_STATUS_2)
	{
		return FALSE;
	}

	if (WUDIsBusy())
	{
		WPADCancelSyncDevice();
		return FALSE;
	}

	BOOL isCleanup;
	switch (event)
	{
	case OS_SHUTDOWN_EVENT_FATAL:
		WPADRegisterAllocator(&__wpadNoAlloc, &__wpadNoFree);

		// fallthrough

	case OS_SHUTDOWN_EVENT_SHUTDOWN:
	case OS_SHUTDOWN_EVENT_3:
		isCleanup = TRUE;
		break;

	case OS_SHUTDOWN_EVENT_1:
	case OS_SHUTDOWN_EVENT_RESTART:
	case OS_SHUTDOWN_EVENT_LAUNCH_APP:
		isCleanup = FALSE;
		break;

	case OS_SHUTDOWN_EVENT_RETURN_TO_MENU:
		isCleanup = __OSIsReturnToIdle ? 1 : 0;
		break;

	default:
		// ERRATA: isCleanup is uninitialized here on release builds
		OSAssertMessage_Line(1082, FALSE,
		                     "WPAD: OnShutDown(): Unknown event %d\n", event);
	}

	if (isCleanup)
		__wpadCleanup();
	else
		__wpadReconnectStart(TRUE);

	return FALSE;
}

// clang-format off
static OSShutdownFunctionInfo ShutdownFunctionInfo =
{
	&OnShutdown,
	127,
	NULL,
	NULL
};
// clang-format on

static WPADResult __wpadSendDataSub(WPADChannel chan, struct WPADCmd cmdBlk)
{
	BOOL intrStatus;
	BOOL rumbleFlag;
	WUDDevHandle devHandle;
	wpad_cb_st *p_wpd;
	UINT8 rep_id;
	BT_HDR *p_buf;
	byte_t *rptData;
	WPADResult status;
	byte_t *cmdData;
	UINT16 len;

	p_buf = NULL;
	p_wpd = __rvl_p_wpadcb[chan];

	rep_id = cmdBlk.reportID;
	cmdData = cmdBlk.dataBuf;
	len = cmdBlk.dataLength;

	OSAssert_Line(1138, rep_id >= 0x10 && rep_id <= 0x1a);

	intrStatus = OSDisableInterrupts();

	status = p_wpd->status;

	devHandle = p_wpd->devHandle;
	if (devHandle < 0)
	{
		OSRestoreInterrupts(intrStatus);
		return WPAD_EINVAL;
	}

	p_wpd->status = WPAD_ECOMM;
	rumbleFlag = p_wpd->motorRunning & _wpadRumbleFlag; // bitand is fine here

	if (rep_id == RPTID_SET_RUMBLE)
	{
		p_wpd->status = status;
	}
	else if (rep_id == RPTID_SEND_SPEAKER_DATA)
	{
		OSAssert_Line(1160, p_wpd->audioFrames > 0);

		p_wpd->status = status;
		p_wpd->audioFrames--;
	}
	else
	{
		switch (rep_id)
		{
		case RPTID_WRITE_DATA:
			break;

		case RPTID_READ_DATA:
			p_wpd->wmReadHadError = 0;
			p_wpd->wmReadAddress = cmdBlk.readAddress;
			p_wpd->wmReadLength = cmdBlk.readLength;
			p_wpd->wmReadDataPtr = cmdBlk.dstBuf;
			break;

		case RPTID_REQUEST_STATUS:
			p_wpd->status = status;
			p_wpd->wpInfoOut = cmdBlk.statusReportOut;
			p_wpd->statusReqBusy = TRUE;
			break;

		default:
			cmdData[0] |= (1 << RPT_OUT_FLAG_REQUEST_ACK_RPT);
			break;
		}

		p_wpd->cmdBlkCB = cmdBlk.cmdCB;
		p_wpd->lastReportID = rep_id;
		p_wpd->lastReportSendTime = __OSGetSystemTime() + OS_TIMER_CLOCK * 2;
		p_wpd->unk_0xb08 = 0;
	}

	OSRestoreInterrupts(intrStatus);

	p_buf = GKI_getbuf((u8)(len + 18));
	OSAssert_Line(1202, p_buf != NULL);

	p_buf->len = (u8)(len + 1);
	p_buf->offset = 10;

	rptData = (byte_t *)(p_buf + 1) + p_buf->offset;
	rptData[0] = rep_id;
	memcpy(&rptData[1], cmdData, len);

	if (rumbleFlag)
		rptData[RPT_OUT_FLAGS] |= (1 << RPT_OUT_FLAG_RUMBLE);
	else
		rptData[RPT_OUT_FLAGS] &= ~(1 << RPT_OUT_FLAG_RUMBLE);

	BTA_HhSendData((UINT8)devHandle, p_buf);
	return WPAD_ESUCCESS;
}

static WPADResult __wpadSendData(WPADChannel chan, struct WPADCmd cmdBlk)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult connStatus =
		p_wpd->statusReqBusy ? WPAD_ECOMM : __wpadGetConnectionStatus(chan);

	OSRestoreInterrupts(intrStatus);

	if (connStatus == WPAD_ESUCCESS)
	{
		connStatus = __wpadSendDataSub(chan, cmdBlk);
	}
	else if (connStatus == WPAD_ECOMM)
	{
		if ((__OSGetSystemTime() - p_wpd->lastReportSendTime) / OS_TIMER_CLOCK
		    > 1)
		{
			p_wpd->lastReportSendTime = __OSGetSystemTime();
			__wpadDisconnect(chan, FALSE);
		}
	}

	return connStatus;
}

static void __wpadCalcRadioQuality(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];
	u32 two = 2; // some define?

	if (_wpadSenseCnt != 10)
		return;

	u16 a = p_wpd->radioSensitivity * 9;
	a += (u16)(p_wpd->copyOutCount * 100 / two);
	a /= 10;
	a = MIN(100, a);

	p_wpd->radioSensitivity = a;
	p_wpd->copyOutCount = 0;

	if (p_wpd->radioQuality != WPAD_RADIO_QUALITY_GOOD)
	{
		if (a > 85)
		{
			p_wpd->radioQuality = WPAD_RADIO_QUALITY_GOOD;
			p_wpd->radioQualityOkMs = 0;
		}
		else if (a > 80)
		{
			p_wpd->radioQualityOkMs++;

			if (p_wpd->radioQualityOkMs >= 20)
			{
				p_wpd->radioQuality = WPAD_RADIO_QUALITY_GOOD;
				p_wpd->radioQualityOkMs = 0;
			}
		}
	}
	else
	{
		if (a < 75)
		{
			p_wpd->radioQuality = WPAD_RADIO_QUALITY_BAD;
			p_wpd->radioQualityOkMs = 0;
		}
		else if (a < 80)
		{
			p_wpd->radioQualityOkMs++;

			if (p_wpd->radioQualityOkMs >= 1)
			{
				p_wpd->radioQuality = WPAD_RADIO_QUALITY_BAD;
				p_wpd->radioQualityOkMs = 0;
			}
		}
	}
}

static u32 __wpadFmt2Size(WPADDataFormat fmt)
{
	u32 fmtSize;

	switch (fmt)
	{
	case WPAD_FMT_FS_BTN:
	case WPAD_FMT_FS_BTN_ACC:
	case WPAD_FMT_FS_BTN_ACC_DPD:
		fmtSize = sizeof(WPADFSStatus);
		break;

	case WPAD_FMT_CLASSIC_BTN:
	case WPAD_FMT_CLASSIC_BTN_ACC:
	case WPAD_FMT_CLASSIC_BTN_ACC_DPD:

	case WPAD_FMT_GUITAR:
	case WPAD_FMT_DRUM:
	case WPAD_FMT_TAIKO:
	case WPAD_FMT_TURNTABLE:
		fmtSize = sizeof(WPADCLStatus);
		break;

	case WPAD_FMT_BULK:
		fmtSize = sizeof(WPADBKStatus);
		break;

	case WPAD_FMT_TRAIN:
		fmtSize = sizeof(WPADTRStatus);
		break;

	case WPAD_FMT_BALANCE_CHECKER:
		fmtSize = sizeof(WPADBLStatus);
		break;

	case WPAD_FMT_VSM:
		fmtSize = sizeof(WPADVSStatus);
		break;

	case WPAD_FMT_BTN_ACC_DPD_EXTENDED:
		fmtSize = sizeof(WPADStatusEx);
		break;

	case WPAD_FMT_MOTION_PLUS:
		fmtSize = sizeof(WPADMPStatus);
		break;

	default:
	/* these are not explicit cases */
	// case WPAD_FMT_BTN:
	// case WPAD_FMT_BTN_ACC:
	// case WPAD_FMT_BTN_ACC_DPD:
		fmtSize = sizeof(WPADStatus);
		break;
	}

	return fmtSize;
}

static u8 __wpadIsButtonChanged(u16 lhs, u16 rhs)
{
	return lhs != rhs ? 1 : 0;
}

static u8 __wpadIsAnalogChanged(s32 lhs, s32 rhs, s32 minDiff)
{
	s32 diff = lhs - rhs < 0 ? rhs - lhs : lhs - rhs;

	return diff > minDiff ? 1 : 0;
}

static BOOL __wpadCalcAnalogNoise(wpad_cb_st *p_wpd, WPADNZFilter filter_type,
                                  BOOL analogChanged)
{
	OSAssert_Line(1387, filter_type >= 0 && filter_type < WPAD_MAX_NZFILTERS);

	if (analogChanged)
	{
		p_wpd->filterDiff[filter_type]++;

		if (p_wpd->filterDiff[filter_type]
		    > _wpad_diff_count_threshold[filter_type])
		{
			p_wpd->filterDiff[filter_type] = 0;
			p_wpd->filterSame[filter_type] = 0;
			return TRUE;
		}
	}
	else
	{
		p_wpd->filterSame[filter_type] =
			(p_wpd->filterSame[filter_type] + 1)
			% _wpad_hyst_count_threshold[filter_type];

		if (p_wpd->filterSame[filter_type]
		        == _wpad_hyst_count_threshold[filter_type] - 1
		    && p_wpd->filterDiff[filter_type])
		{
			p_wpd->filterDiff[filter_type]--;
		}
	}

	return FALSE;
}

static BOOL __wpadIsControllerDataChanged(wpad_cb_st *p_wpd, void *lhs,
                                          void *rhs)
{
	WPADStatus *lhsCore = lhs;
	WPADStatus *rhsCore = rhs;
	u8 isChanged = FALSE;

	if ((lhsCore->err == WPAD_ESUCCESS || lhsCore->err == WPAD_EBADE)
	    && (rhsCore->err == WPAD_ESUCCESS || rhsCore->err == WPAD_EBADE))
	{
		isChanged |= __wpadIsButtonChanged(lhsCore->button, rhsCore->button);

		isChanged |= __wpadCalcAnalogNoise(
			p_wpd, WPAD_NZFILTER_ACC,
			__wpadIsAnalogChanged(lhsCore->accX, rhsCore->accX, 12)
				| __wpadIsAnalogChanged(lhsCore->accY, rhsCore->accY, 12)
				| __wpadIsAnalogChanged(lhsCore->accZ, rhsCore->accZ, 12));

		isChanged |= __wpadCalcAnalogNoise(
			p_wpd, WPAD_NZFILTER_DPD,
			__wpadIsAnalogChanged(lhsCore->obj[0].x, rhsCore->obj[0].x, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[0].y, rhsCore->obj[0].y, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[1].x, rhsCore->obj[1].x, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[1].y, rhsCore->obj[1].y, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[2].x, rhsCore->obj[2].x, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[2].y, rhsCore->obj[2].y, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[3].x, rhsCore->obj[3].x, 2)
				| __wpadIsAnalogChanged(lhsCore->obj[3].y, rhsCore->obj[3].y,
				                        2));
	}

	if (lhsCore->err == WPAD_ESUCCESS && rhsCore->err == WPAD_ESUCCESS)
	{
		switch (p_wpd->dataFormat)
		{
		case WPAD_FMT_FS_BTN:
		case WPAD_FMT_FS_BTN_ACC:
		case WPAD_FMT_FS_BTN_ACC_DPD:
		{
			WPADFSStatus *lhsFS = lhs;
			WPADFSStatus *rhsFS = rhs;

			isChanged |= __wpadCalcAnalogNoise(
				p_wpd, WPAD_NZFILTER_EXT,
				__wpadIsAnalogChanged(lhsFS->fsAccX, rhsFS->fsAccX, 12)
					| __wpadIsAnalogChanged(lhsFS->fsAccY, rhsFS->fsAccY, 12)
					| __wpadIsAnalogChanged(lhsFS->fsAccZ, rhsFS->fsAccZ, 12));

			isChanged |=
				__wpadIsAnalogChanged(lhsFS->fsStickX, rhsFS->fsStickX, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsFS->fsStickY, rhsFS->fsStickY, 1);
		}
			break;

		case WPAD_FMT_CLASSIC_BTN:
		case WPAD_FMT_CLASSIC_BTN_ACC:
		case WPAD_FMT_CLASSIC_BTN_ACC_DPD:

		case WPAD_FMT_GUITAR:
		case WPAD_FMT_DRUM:
		case WPAD_FMT_TAIKO:
		case WPAD_FMT_TURNTABLE:
		{
			WPADCLStatus *lhsCL = lhs;
			WPADCLStatus *rhsCL = rhs;

			s32 leftStickDiv;
			s32 rightStickDiv;
			s32 triggerDiv;
			switch (p_wpd->devMode)
			{
			case WPAD_DEV_MODE_CLASSIC_REDUCED:
				leftStickDiv = 16;
				rightStickDiv = 32;
				triggerDiv = 8;
				break;

			case WPAD_DEV_MODE_CLASSIC_STANDARD:
				leftStickDiv = 4;
				rightStickDiv = 4;
				triggerDiv = 1;
				break;

			default:
				leftStickDiv = 1;
				rightStickDiv = 1;
				triggerDiv = 1;
				break;
			}

			isChanged |=
				__wpadIsButtonChanged(lhsCL->clButton, rhsCL->clButton);

			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clLStickX / leftStickDiv,
			                          rhsCL->clLStickX / leftStickDiv, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clLStickY / leftStickDiv,
			                          rhsCL->clLStickY / leftStickDiv, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clRStickX / rightStickDiv,
			                          rhsCL->clRStickX / rightStickDiv, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clRStickY / rightStickDiv,
			                          rhsCL->clRStickY / rightStickDiv, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clTriggerL / triggerDiv,
			                          rhsCL->clTriggerL / triggerDiv, 1);
			isChanged |=
				__wpadIsAnalogChanged(lhsCL->clTriggerR / triggerDiv,
			                          rhsCL->clTriggerR / triggerDiv, 1);
		}
			break;

		case WPAD_FMT_TRAIN:
		{
			WPADTRStatus *lhsTR = lhs;
			WPADTRStatus *rhsTR = rhs;

			isChanged |=
				__wpadIsButtonChanged(lhsTR->trButton, rhsTR->trButton);
			isChanged |= __wpadIsAnalogChanged(lhsTR->brake, rhsTR->brake, 1);
			isChanged |= __wpadIsAnalogChanged(lhsTR->mascon, rhsTR->mascon, 1);
		}
			break;

		case WPAD_FMT_BALANCE_CHECKER:
		{
			WPADBLStatus *lhsBL = lhs;
			WPADBLStatus *rhsBL = rhs;

			isChanged |= __wpadCalcAnalogNoise(
				p_wpd, WPAD_NZFILTER_EXT,
				__wpadIsAnalogChanged(lhsBL->press[0], rhsBL->press[0], 50)
					| __wpadIsAnalogChanged(lhsBL->press[1], rhsBL->press[1],
			                                50)
					| __wpadIsAnalogChanged(lhsBL->press[2], rhsBL->press[2],
			                                50)
					| __wpadIsAnalogChanged(lhsBL->press[3], rhsBL->press[3],
			                                50));
		}
			break;

		case WPAD_FMT_VSM:
		{
			WPADVSStatus *lhsVS = lhs;

			if (p_wpd->unk_0xbbc)
				isChanged |= lhsVS->at_0x42 > 200 ? 1 : 0;
		}
			break;

		case WPAD_FMT_MOTION_PLUS:
		{
			WPADMPStatus *lhsMP = lhs;
			WPADMPStatus *rhsMP = rhs;

			isChanged |= __wpadCalcAnalogNoise(
				p_wpd, WPAD_NZFILTER_MPLS,
				__wpadIsAnalogChanged(lhsMP->pitch, rhsMP->pitch, 64)
					| __wpadIsAnalogChanged(lhsMP->yaw, rhsMP->yaw, 64)
					| __wpadIsAnalogChanged(lhsMP->roll, rhsMP->roll, 64));

			if (lhsMP->stat & WPAD_MPLS_STATUS_EXTENSION_CONNECTED
			    && rhsMP->stat & WPAD_MPLS_STATUS_EXTENSION_CONNECTED)
			{
				if (p_wpd->devMode == WPAD_DEV_MODE_MPLS_PT_FS)
				{
					isChanged |= __wpadCalcAnalogNoise(
						p_wpd, WPAD_NZFILTER_EXT,
						__wpadIsAnalogChanged(lhsMP->ext.fs.fsAccX,
					                          rhsMP->ext.fs.fsAccX, 12)
							| __wpadIsAnalogChanged(lhsMP->ext.fs.fsAccY,
					                                rhsMP->ext.fs.fsAccY, 12)
							| __wpadIsAnalogChanged(lhsMP->ext.fs.fsAccZ,
					                                rhsMP->ext.fs.fsAccZ, 12));

					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.fs.fsStickX, rhsMP->ext.fs.fsStickX, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.fs.fsStickY, rhsMP->ext.fs.fsStickY, 1);
				}
				else if (p_wpd->devMode == WPAD_DEV_MODE_MPLS_PT_CLASSIC)
				{
					s32 lStickDiv = 16;
					s32 rStickDiv = 32;
					s32 triggerDiv = 8;

					isChanged |= __wpadIsButtonChanged(lhsMP->ext.cl.clButton,
					                                   rhsMP->ext.cl.clButton);

					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clLStickX / lStickDiv,
						rhsMP->ext.cl.clLStickX / lStickDiv, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clLStickY / lStickDiv,
						rhsMP->ext.cl.clLStickY / lStickDiv, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clRStickX / rStickDiv,
						rhsMP->ext.cl.clRStickX / rStickDiv, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clRStickY / rStickDiv,
						rhsMP->ext.cl.clRStickY / rStickDiv, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clTriggerL / triggerDiv,
						rhsMP->ext.cl.clTriggerL / triggerDiv, 1);
					isChanged |= __wpadIsAnalogChanged(
						lhsMP->ext.cl.clTriggerR / triggerDiv,
						rhsMP->ext.cl.clTriggerR / triggerDiv, 1);
				}
			}
		}
			break;
		}
	}

	return isChanged;
}

static void __wpadCalcRecalibration(WPADChannel chan, void *status)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADCLStatus *clStatus = status;
	WPADMPStatus *mpStatus = status;

	s8 recalibrateComboPressed = 0;
	WPADExtButton clPressed = 0;

	if (clStatus->err != WPAD_ESUCCESS && clStatus->err != WPAD_EBADE)
		return;

	if (clStatus->button
	     == (WPAD_BUTTON_CL_A | WPAD_BUTTON_CL_PLUS | WPAD_BUTTON_CL_MINUS
	         | WPAD_BUTTON_CL_HOME)
	    && (p_wpd->dataFormat == WPAD_FMT_FS_BTN
	        || p_wpd->dataFormat == WPAD_FMT_FS_BTN_ACC
	        || p_wpd->dataFormat == WPAD_FMT_FS_BTN_ACC_DPD
	        || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN
	        || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC
	        || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC_DPD
	        || p_wpd->dataFormat == WPAD_FMT_MOTION_PLUS))
	{
		recalibrateComboPressed = 1;
	}

	if (p_wpd->devType == WPAD_DEV_CLASSIC)
		clPressed = clStatus->clButton;

	if (p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC)
		clPressed = mpStatus->ext.cl.clButton;

	if (clPressed
	     == (WPAD_BUTTON_CL_A | WPAD_BUTTON_CL_B | WPAD_BUTTON_CL_PLUS
	         | WPAD_BUTTON_CL_MINUS)
	    && (p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN
	        || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC
	        || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC_DPD
	        || p_wpd->dataFormat == WPAD_FMT_MOTION_PLUS))
	{
		recalibrateComboPressed = 1;
	}

	p_wpd->recalibHoldMs += recalibrateComboPressed;

	if (p_wpd->recalibHoldMs > 600)
		WPADRecalibrate(chan);
}

static void __wpadCalcControllerData(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL isChanged = FALSE;
	BOOL screenSaverFlag = FALSE;

	if (_wpadCheckCnt != 5)
		return;

	BOOL intrStatus = OSDisableInterrupts();

	u8 rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
	WPADStatus *status = (WPADStatus *)p_wpd->rxBufs[rxBufIndex];

	OSRestoreInterrupts(intrStatus);

	isChanged = __wpadIsControllerDataChanged(p_wpd, status, p_wpd->rxBufMain);

	__wpadCalcRecalibration(chan, status);

	if (isChanged)
	{
		screenSaverFlag = TRUE;
		p_wpd->lastControllerDataUpdate = __OSGetSystemTime();
		memcpy(p_wpd->rxBufMain, status, sizeof p_wpd->rxBufMain);
	}
	else if (_wpadSleepTime)
	{
		s32 time = (__OSGetSystemTime() - p_wpd->lastControllerDataUpdate)
		         / OS_TIMER_CLOCK;

		if (time > _wpadSleepTime * 60)
			__wpadDisconnect(chan, 0);
	}

	if (((WPADStatus *)(p_wpd->rxBufMain))->err != WPAD_ESUCCESS
	     && ((WPADStatus *)(p_wpd->rxBufMain))->err != WPAD_EBADE)
	{
		memcpy(p_wpd->rxBufMain, status, sizeof p_wpd->rxBufMain);
	}

	__wpadSetScreenSaverFlag(screenSaverFlag);
}

static BOOL __wpadProcExtCommand(WPADChannel chan, BOOL previousSuccess)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL success = FALSE;

	if (previousSuccess)
		return TRUE;

	if (_wpadExtCnt[chan] != 5)
		goto end;

	struct WPADCmd cmdBlk;
	if (!__wpadGetCommand(&p_wpd->extCmdQueue, &cmdBlk))
		goto end;

	if (cmdBlk.reportID != RPTID_SET_DATA_REPORT_MODE && !p_wpd->wpInfo.attach)
		goto end;

	if (__wpadSendData(chan, cmdBlk) != WPAD_ESUCCESS)
		goto end;

	__wpadPopCommand(&p_wpd->extCmdQueue);
	success = TRUE;
	_wpadExtCnt[chan] = 0;

end:
	_wpadExtCnt[chan] =
		_wpadExtCnt[chan] == 5 ? _wpadExtCnt[chan] : _wpadExtCnt[chan] + 1;

	return success;
}

static void __wpadRumbleMotor(WPADChannel chan, BOOL procSuccess)
{
	struct WPADCmd cmdBlk;

	if (procSuccess == TRUE
	    || __wpadGetQueueSize(&__rvl_p_wpadcb[chan]->stdCmdQueue) > 0)
	{
		__rvl_p_wpadcb[chan]->motorBusy = FALSE;
	}
	else if (_wpadRumbleCnt[chan] == 5)
	{
		__rvl_p_wpadcb[chan]->motorBusy = FALSE;

		cmdBlk.reportID = RPTID_SET_RUMBLE;
		cmdBlk.dataLength = RPT10_SIZE;
		cmdBlk.dataBuf[RPT10_RUMBLE] = FALSE;
		cmdBlk.cmdCB = NULL;
		__wpadSendDataSub(chan, cmdBlk);
	}

	_wpadRumbleCnt[chan] =
		__rvl_p_wpadcb[chan]->motorBusy ? _wpadRumbleCnt[chan] + 1 : 0;
}

static BOOL __wpadProcCommand(WPADChannel chan, BOOL previousSuccess)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (previousSuccess)
		return TRUE;

	struct WPADCmd cmdBlk;
	if (__wpadGetCommand(&p_wpd->stdCmdQueue, &cmdBlk)
	    && __wpadSendData(chan, cmdBlk) == WPAD_ESUCCESS)
	{
		__wpadPopCommand(&p_wpd->stdCmdQueue);
		return TRUE;
	}

	return FALSE;
}

static void __wpadCalcSystemSettings(void)
{
	if (SCCheckStatus() != SC_STATUS_READY)
		return;

	WUDUpdateSCSetting();

	if (_wpadSCSetting)
	{
		_wpadDpdSense = __wpadGetDpdSensitivity();
		_wpadSensorBarPos = __wpadGetSensorBarPosition();
		_wpadRumbleFlag = __wpadGetMotorMode();
		_wpadSpeakerVol = __wpadGetSpeakerVolume();

		_wpadSCSetting = FALSE;
	}
}

static void __wpadCalcAfh(void)
{
	if (_wpadAfhCnt != 60000)
		return;

#define CURRENT_AFH_CHANNEL_PHYS_ADDR	(void *)0x31a2
	u8 *currAfhChannel = OSPhysicalToCached(CURRENT_AFH_CHANNEL_PHYS_ADDR);
	DCInvalidateRange(currAfhChannel, sizeof *currAfhChannel);

	if (_wpadAfhChannel == *currAfhChannel)
		return;

	BOOL intrStatus = OSDisableInterrupts();

	_wpadAfhChannel = *currAfhChannel;

	OSRestoreInterrupts(intrStatus);

	WUDSetDisableChannel(_wpadAfhChannel);
}

static BOOL __wpadCalcReconnectWait(void)
{
	if (_wpadOnReconnect >= 0)
	{
		if (--_wpadReconnectWait <= 0)
			__wpadResetModule(_wpadOnReconnect);

		return TRUE;
	}

	return FALSE;
}

static void __wpadManageHandler(OSAlarm *alarm __attribute__((unused)),
                                OSContext *context __attribute__((unused)))
{
	WPADLibStatus status = WPADGetStatus();

	if (status != WPAD_LIB_STATUS_3)
	{
		if (status == WPAD_LIB_STATUS_2 && !_wpadInitialized)
		{
			_wpadInitialized = TRUE;
			_wpadReconnectWait = 50;

			WUDSetHidConnCallback(&__wpadConnectionCallback);
			WUDSetHidRecvCallback(&__wpadReceiveCallback);
		}

		return;
	}

	if (__wpadCalcReconnectWait())
		return;

	__wpadCalcAfh();
	__wpadCalcSystemSettings();

	WPADChannel chan;
	BOOL procSuccess;
	for (chan = WPAD_CHAN0; chan < WPAD_MAX_CONTROLLERS; chan++)
	{
		procSuccess = FALSE;

		if (__rvl_p_wpadcb[chan]->used)
		{
			procSuccess |= __wpadProcExtCommand(chan, procSuccess);
			procSuccess |= __wpadProcCommand(chan, procSuccess);

			__wpadRumbleMotor(chan, procSuccess);
			__wpadCalcControllerData(chan);
			__wpadCalcRadioQuality(chan);
		}

		if (__rvl_p_wpadcb[chan]->extWasDisconnected
		    && __rvl_p_wpadcb[chan]->reconnectExtMs-- < 0)
		{
			__rvl_p_wpadcb[chan]->extWasDisconnected = FALSE;
		}

		__wpadCertWork(chan);

		if (__rvl_p_wpadcb[chan]->devType == WPAD_DEV_MOTION_PLUS
		     || __rvl_p_wpadcb[chan]->devType == WPAD_DEV_MPLS_PT_FS
		     || __rvl_p_wpadcb[chan]->devType == WPAD_DEV_MPLS_PT_CLASSIC
		     || __rvl_p_wpadcb[chan]->devType == WPAD_DEV_MPLS_PT_UNKNOWN)
		{
			if (__rvl_p_wpadcb[chan]->mplsUptimeMs < 200)
				__rvl_p_wpadcb[chan]->mplsUptimeMs++;
		}
	}

	_wpadSenseCnt = _wpadSenseCnt == 10 ? 0 : _wpadSenseCnt + 1;
	_wpadCheckCnt = _wpadCheckCnt == 5 ? 0 : _wpadCheckCnt + 1;
	_wpadAfhCnt = _wpadAfhCnt == 60000 ? 0 : _wpadAfhCnt + 1;

	BTA_HhGetAclQueueInfo();
}

static void __wpadManageHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx(
		(register_t)alarm, (register_t)context, 0, 0, &__wpadManageHandler,
		&__wpadManageHandlerStack[sizeof __wpadManageHandlerStack]);
}

static void __wpadClearControlBlock(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];
	WPADStatus *status;
	int filter;

	p_wpd->wpInfoOut = NULL;

	p_wpd->motorRunning = FALSE;

	p_wpd->cmdBlkCB = NULL;
	p_wpd->extensionCB = NULL;
	p_wpd->samplingCB = NULL;

	p_wpd->samplingBuf = NULL;
	p_wpd->samplingBufIndex = 0;
	p_wpd->samplingBufSize = 0;

	p_wpd->dataFormat = WPAD_FMT_CORE_BTN;
	p_wpd->status = WPAD_ENODEV;
	p_wpd->devType = WPAD_DEV_NONE;
	p_wpd->devMode = WPAD_DEV_MODE_NORMAL;

	p_wpd->calibrated = FALSE;
	p_wpd->recalibHoldMs = 0;

	p_wpd->statusReqBusy = FALSE;

	p_wpd->defaultDpdSize = 12;
	p_wpd->currentDpdCommand = WPAD_DPD_DISABLE;
	p_wpd->pendingDpdCommand = 0;

	for (filter = 0; filter < WPAD_MAX_NZFILTERS; filter++)
	{
		p_wpd->filterDiff[filter] = 0;
		p_wpd->filterSame[filter] = 0;
	}

	p_wpd->lastControllerDataUpdate = __OSGetSystemTime();
	p_wpd->lastReportSendTime = __OSGetSystemTime();
	p_wpd->unk_0xb08 = 0;
	p_wpd->unk_0x90d = 0;
	p_wpd->unk_0x908 = 0;
	p_wpd->wmReadDataPtr = NULL;
	p_wpd->wmReadAddress = 0;
	p_wpd->wmReadLength = 0;
	p_wpd->wmReadHadError = 0;
	p_wpd->devHandle = WUD_DEV_HANDLE_INVALID;
	p_wpd->used = FALSE;
	p_wpd->handshakeFinished = FALSE;
	p_wpd->configIndex = 0;
	p_wpd->radioQuality = WPAD_RADIO_QUALITY_BAD;
	p_wpd->radioQualityOkMs = 0;
	p_wpd->audioFrames = 0;
	p_wpd->unk_0xb7a = 0;
	p_wpd->radioSensitivity = 0;
	p_wpd->copyOutCount = 0;
	p_wpd->sleeping = TRUE;
	p_wpd->getInfoBusy = FALSE;
	p_wpd->getInfoCB = NULL;
	p_wpd->disableContReport = FALSE;
	p_wpd->blcBattery = 4;
	p_wpd->savedDevType = WPAD_DEV_NONE;
	p_wpd->extWasDisconnected = FALSE;
	p_wpd->reconnectExtMs = 0;
	p_wpd->interleaveFlags = WPAD_ILBUF_NONE;

	memset(&p_wpd->wpInfo, 0, sizeof p_wpd->wpInfo);
	memset(&p_wpd->wmReadDataBuf, 0, sizeof p_wpd->wmReadDataBuf);
	memset(&p_wpd->devConfig, 0, sizeof p_wpd->devConfig);
	memset(&p_wpd->extConfig, 0, sizeof p_wpd->extConfig);
	memset(&p_wpd->encryptionKey, 0, sizeof p_wpd->encryptionKey);
	memset(&p_wpd->decryptAddTable, 0, sizeof p_wpd->decryptAddTable);
	memset(&p_wpd->decryptXorTable, 0, sizeof p_wpd->decryptXorTable);
	memset(&p_wpd->gameInfo, 0, sizeof p_wpd->gameInfo);

	p_wpd->rxBufIndex = 0;
	memset(p_wpd->rxBufs, 0, sizeof p_wpd->rxBufs);
	status = (WPADStatus *)p_wpd->rxBufs[0];
	status->err = WPAD_ERR_NO_CONTROLLER;
	status = (WPADStatus *)p_wpd->rxBufs[1];
	status->err = WPAD_ERR_NO_CONTROLLER;
	memcpy(p_wpd->rxBufMain, p_wpd->rxBufs[0], sizeof p_wpd->rxBufMain);

	p_wpd->at_0x038[0] = -1;
	p_wpd->at_0x038[1] = -1;

	p_wpd->stdCmdQueue.queue = p_wpd->stdCmdQueueList;
	p_wpd->stdCmdQueue.length = ARRAY_LENGTH(p_wpd->stdCmdQueueList);
	p_wpd->extCmdQueue.queue = p_wpd->extCmdQueueList;
	p_wpd->extCmdQueue.length = ARRAY_LENGTH(p_wpd->extCmdQueueList);

	WPADiClearQueue(&p_wpd->stdCmdQueue);
	WPADiClearQueue(&p_wpd->extCmdQueue);

	p_wpd->isInitingMpls = FALSE;
	p_wpd->controlMplsBusy = FALSE;
	p_wpd->mplsCBReadBuf[0] = 0;
	p_wpd->mplsCBReadBuf[1] = 0;
	p_wpd->pendingMplsCommand = 0;
	p_wpd->mplsCBCounter = 3;
	p_wpd->noParseMplsCount = 5;
	p_wpd->controlMplsCB = NULL;
	p_wpd->mplsUptimeMs = 0;

	p_wpd->certChallengeRandomBit = -1;
	p_wpd->certWorkBusy = FALSE;
	p_wpd->certState = WPAD_STATE_CERT_INVALID;
	p_wpd->certValidityStatus = WPAD_CERT_UNCHECKED;
	p_wpd->certStateWorkMs = 3000;
	p_wpd->certWorkCounter = 2;
	p_wpd->wmParamOffset = 0;
	p_wpd->certParamPtr = NULL;

	memset(p_wpd->certBuf0, 0, sizeof p_wpd->certBuf0);
	memset(p_wpd->certBuf1, 0, sizeof p_wpd->certBuf1);
	memset(p_wpd->certBufBig, 0, sizeof p_wpd->certBufBig);
	p_wpd->certBuf0[0] = p_wpd->certBuf1[0] = p_wpd->certBufBig[0] = 1;

	p_wpd->noParseExtCount = 0;
	p_wpd->extErr = WPAD_ENODEV;
	p_wpd->extDevType = WPAD_DEV_NONE;
	p_wpd->extDataLength = 0;
	memset(&p_wpd->extDataBuf, 0, sizeof p_wpd->extDataBuf);

	WPADiClearMemBlock(chan);

	p_wpd->unk_0xae4 = 0;

	_wpadExtCnt[chan] = 0;
	_wpadRumbleCnt[chan] = 0;

#if !defined(NDEBUG)
	_wpadDummyAttach[chan] = FALSE;
#endif // !defined(NDEBUG)
}

// TODO on release
static void __wpadInitSub(void)
{
	__wpadSetSensorBarPower(TRUE);

	WPADChannel chan;
	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY; i++)
		_wpadHandle2PortTable[i] = WUD_DEV_HANDLE_INVALID;

	for (chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++)
	{
		__rvl_p_wpadcb[chan] = &__rvl_wpadcb[chan];

		_wpadIsUsedChannel[chan] = FALSE;

		__rvl_p_wpadcb[chan]->connectCB = NULL;
		__wpadClearControlBlock(chan);
		OSInitThreadQueue(&__rvl_wpadcb[chan].threadQueue);
		__rvl_p_wpadcb[chan]->certMayVerifyByCalibBlock = FALSE;

		_wpadExtCnt[chan] = 0;
		_wpadRumbleCnt[chan] = 0;
	}

	_wpadSleepTime = 5;
	_wpadGameCode = OSGetAppGamename();
	_wpadGameType = OSGetAppType();
	_wpadDpdSense = __wpadGetDpdSensitivity();
	_wpadSensorBarPos = __wpadGetSensorBarPosition();
	_wpadRumbleFlag = __wpadGetMotorMode();
	_wpadSpeakerVol = __wpadGetSpeakerVolume();
	_wpadSenseCnt = 0;
	_wpadCheckCnt = 0;
	_wpadAfhCnt = 0;
	_wpadShutdownFlag = FALSE;
	_wpadSCSetting = TRUE;
	_wpadAfhChannel = -1;
	_wpadUsedCallback = FALSE;

	OSRegisterVersion(__WPADVersion);

	// dont care
	// clang-format off
	if (_wpadVSMInit) (*_wpadVSMInit)();
	if (_wpadTRNInit) (*_wpadTRNInit)();
	if (_wpadGTRInit) (*_wpadGTRInit)();
	if (_wpadDRMInit) (*_wpadDRMInit)();
	if (_wpadTKOInit) (*_wpadTKOInit)();
	if (_wpadTBLInit) (*_wpadTBLInit)();
	if (_wpadBLKInit) (*_wpadBLKInit)();
	// clang-format on

	OSCreateAlarm(&_wpadManageAlarm);
	OSSetPeriodicAlarm(&_wpadManageAlarm, OSGetTime(), OSMillisecondsToTicks(1),
	                   &__wpadManageHandler0);
}

void WPADInit(void)
{
	_wpadStartup = TRUE;

	if (!_wpadRegisterShutdownFunc)
	{
		OSRegisterShutdownFunction(&ShutdownFunctionInfo);
		_wpadRegisterShutdownFunc = TRUE;
	}

	BOOL wudInitSuccess = WUDInit();
	if (wudInitSuccess)
	{
		_wpadInitialized = FALSE;
		_wpadOnReconnect = -1;
		_wpadReconnectWait = 50;
		__wpadInitSub();
	}
}

void WPADShutdown(void)
{
	return;
}

static void __wpadShutdown(BOOL saveSimpleDevs)
{
	OSCancelAlarm(&_wpadManageAlarm);
	WUDSetHidRecvCallback(NULL);
	WUDShutdown(saveSimpleDevs);
}

static void __wpadCleanup(void)
{
	BOOL intrStatus = OSDisableInterrupts();

	if (_wpadShutdownFlag)
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	_wpadShutdownFlag = TRUE;
	WUDSetVisibility(FALSE, FALSE);

	WPADChannel chan;
	for (chan = WPAD_CHAN0; chan < WPAD_MAX_CONTROLLERS; chan++)
		WUDSetDeviceHistory(chan, NULL);

	__wpadShutdown(FALSE);

	OSRestoreInterrupts(intrStatus);
}

static void __wpadResetModule(BOOL saveSimpleDevs)
{
	BTA_DmSendHciReset();
	__wpadShutdown(saveSimpleDevs);
}

static void __wpadReconnectStart(BOOL saveSimpleDevs)
{
	BOOL intrStatus = OSDisableInterrupts();

	if (!_wpadStartup)
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	if (_wpadShutdownFlag)
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	_wpadShutdownFlag = TRUE;
	_wpadOnReconnect = saveSimpleDevs ? 1 : 0;

	OSRestoreInterrupts(intrStatus);
}

BOOL WPADStartFastSimpleSync(void)
{
	return WUDStartFastSyncSimple();
}

BOOL WPADStopSimpleSync(void)
{
	return WUDStopSyncSimple();
}

BOOL WPADCancelSyncDevice(void)
{
	return WUDCancelSyncDevice();
}

WPADSimpleSyncCallback *WPADSetSimpleSyncCallback(WPADSimpleSyncCallback *cb)
{
	return WUDSetSyncSimpleCallback(cb);
}

void WPADRegisterAllocator(WPADAllocFunc *alloc, WPADFreeFunc *free)
{
	WUDRegisterAllocator(alloc, free);
}

WPADLibStatus WPADGetStatus(void)
{
	return WUDGetStatus();
}

u8 WPADGetRadioSensitivity(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	u8 radioSensitivity = p_wpd->radioSensitivity;

	OSRestoreInterrupts(intrStatus);

	return radioSensitivity;
}

void WPADGetAddress(WPADChannel chan, BD_ADDR_PTR addr)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(2666, addr != NULL);

	BOOL intrStatus = OSDisableInterrupts();

	s8 dev_handle = p_wpd->devHandle;

	OSRestoreInterrupts(intrStatus);

	BD_ADDR_PTR devAddr = _WUDGetDevAddr(dev_handle);

	if (devAddr)
		memcpy(addr, devAddr, BD_ADDR_LEN);
	else
		memset(addr, 0, BD_ADDR_LEN);
}

// WPADGetCalibratedDPDObject ([SGLEA4]/MAP/GormitiDebug.MAP:25309)
extern void __deadstrip1(void)
{
	(void)"Failed assertion src != NULL && dst != NULL";
}

u8 WPADGetSensorBarPosition(void)
{
	BOOL intrStatus = OSDisableInterrupts();

	u8 sensorBarPos = _wpadSensorBarPos;

	OSRestoreInterrupts(intrStatus);

	return sensorBarPos;
}

static void __wpadSetupConnectionCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (result == WPAD_ESUCCESS)
	{
		p_wpd->handshakeFinished = TRUE;

		if (p_wpd->connectCB)
			(*p_wpd->connectCB)(chan, result);
	}
	else
	{
		__wpadDisconnect(chan, 0);
	}
}

static void __wpadAbortConnectionCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (result != WPAD_ESUCCESS)
	{
		WPADiClearQueue(&p_wpd->stdCmdQueue);
		__wpadDisconnect(chan, 0);
	}
}

static void __wpadInitConnectionCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (result == WPAD_ENODEV)
		return;

	u32 address;

	BOOL intrStatus = OSDisableInterrupts();

	p_wpd->configIndex = result == WPAD_ESUCCESS ? 1 : 0;
	p_wpd->status = WPAD_ESUCCESS;

	OSRestoreInterrupts(intrStatus);

	u16 size = result == WPAD_ESUCCESS ? 20 : 42;
	address =
		result == WPAD_ESUCCESS ? WM_ADDR_MEM_176C : WM_ADDR_MEM_DEV_CONFIG_0;
	u8 port = p_wpd->devType == WPAD_DEV_BALANCE_CHECKER ? 1 : 1 << chan;

	WPADiSendSetReportType(&p_wpd->stdCmdQueue, 0, p_wpd->disableContReport,
	                       &__wpadAbortConnectionCallback);
	WPADiSendDPDCSB(&p_wpd->stdCmdQueue, FALSE, &__wpadAbortConnectionCallback);
	WPADiSendSetPort(&p_wpd->stdCmdQueue, port, &__wpadAbortConnectionCallback);
	WPADiSendReadData(&p_wpd->stdCmdQueue, p_wpd->wmReadDataBuf,
	                  sizeof(WPADGameInfo), WM_ADDR_MEM_GAME_INFO_0,
	                  &__wpadAbortConnectionCallback);
	WPADiSendReadData(&p_wpd->stdCmdQueue, p_wpd->wmReadDataBuf,
	                  sizeof(WPADGameInfo), WM_ADDR_MEM_GAME_INFO_1,
	                  &__wpadAbortConnectionCallback);
	WPADiSendReadData(&p_wpd->stdCmdQueue, p_wpd->wmReadDataBuf, size, address,
	                  &__wpadSetupConnectionCallback);
	WPADiSendGetContStat(&p_wpd->stdCmdQueue, NULL, NULL);
}

static WPADChannel __wpadRetrieveChannel(WUDDevInfo *devInfo)
{
	BD_ADDR_PTR devAddr;
	int i;
	WPADChannel chan = WPAD_CHAN_INVALID;

	u8 devHandle = devInfo->devHandle;
	devAddr = _WUDGetDevAddr(devHandle);

	if (WUD_DEV_NAME_IS_WBC(devInfo->small.devName))
	{
		chan = WPAD_CHAN3;

		if (__rvl_p_wpadcb[chan]->used)
		{
			btm_remove_acl(devAddr);
			return WPAD_CHAN_INVALID;
		}
	}
	else
	{
		for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
		{
			if (WUDIsLatestDevice(i, devAddr) && !_wpadIsUsedChannel[i])
			{
				chan = i;
				break;
			}

			if (!_wpadIsUsedChannel[i] && chan < WPAD_CHAN0)
				chan = i;
		}
	}

	OSAssert_Line(2922, (chan >= 0) && (chan < WPAD_MAX_CONTROLLERS));
	OSAssert_Line(2923, __rvl_p_wpadcb[chan]->used == FALSE);

	if (!WUDIsLatestDevice(chan, devAddr))
		WUDSetDeviceHistory(chan, devAddr);

	_wpadIsUsedChannel[chan] = TRUE;
	return chan;
}

static void __wpadConnectionCallback(WUDDevInfo *devInfo, u8 success)
{
	UINT8 dev_handle = devInfo->devHandle;

	OSAssertMessage_Line(2951, dev_handle <= WUD_MAX_DEV_ENTRY,
	                     "__wpadConnectionCallback(): Illegal dev_handle\n");

	WPADChannel chan;
	wpad_cb_st *p_wpd;
	struct WPADCmd cmdBlk;

	if (success)
	{
		chan = __wpadRetrieveChannel(devInfo);
		if (chan < 0)
			return;

		_wpadHandle2PortTable[dev_handle] = (UINT8)chan;

		__wpadClearControlBlock(chan);
		p_wpd = __rvl_p_wpadcb[chan];

		if (WUD_DEV_NAME_IS_CNT(&devInfo->small.devName))
		{
			p_wpd->devType = WPAD_DEV_CORE;
			p_wpd->dataFormat = WPAD_FMT_CORE_BTN;
		}
		else if (WUD_DEV_NAME_IS_WBC(&devInfo->small.devName)
		         && WUDIsLinkedWBC())
		{
			p_wpd->devType = WPAD_DEV_BALANCE_CHECKER;
			p_wpd->dataFormat = WPAD_FMT_BALANCE_CHECKER;
		}
		else
		{
			p_wpd->devType = WPAD_DEV_251;
			p_wpd->dataFormat = WPAD_FMT_CORE_BTN;
		}

		p_wpd->devHandle = dev_handle;
		p_wpd->used = TRUE;
		p_wpd->status = WPAD_ESUCCESS;
		p_wpd->radioSensitivity = 100;
		p_wpd->sleeping = FALSE;
		p_wpd->extState = WPAD_STATE_EXT_UNINITIALIZED;
		p_wpd->savedDevType = p_wpd->devType;

		WPADiSendReadData(&p_wpd->stdCmdQueue, p_wpd->wmReadDataBuf, 1,
		                  WM_ADDR_MEM_1770, &__wpadInitConnectionCallback);
		__wpadSetScreenSaverFlag(TRUE);
	}
	else
	{
		chan = _wpadHandle2PortTable[dev_handle];
		_wpadHandle2PortTable[dev_handle] = WUD_DEV_HANDLE_INVALID;
		if (chan == WUD_DEV_HANDLE_INVALID)
			return;

		/* ERRATA: sanctioned OOB access of __rvl_p_wpadcb if
		 * chan == WPAD_MAX_CONTROLLERS
		 */
		OSAssert_Line(2991, chan <= WPAD_MAX_CONTROLLERS);

		p_wpd = __rvl_p_wpadcb[chan];
		p_wpd->status = WPAD_ENODEV;

		if (p_wpd->cmdBlkCB)
			(*p_wpd->cmdBlkCB)(chan, WPAD_ENODEV);
		else if (p_wpd->memBlock.at_0x10)
			(*p_wpd->memBlock.at_0x10)(chan, WPAD_ENODEV);

		while (__wpadGetCommand(&p_wpd->stdCmdQueue, &cmdBlk))
		{
			if (cmdBlk.cmdCB)
				(*cmdBlk.cmdCB)(chan, WPAD_ENODEV);

			__wpadPopCommand(&p_wpd->stdCmdQueue);
		}

		if (p_wpd->samplingBuf)
		{
			WPADSetAutoSamplingBuf(chan, p_wpd->samplingBuf,
			                       p_wpd->samplingBufSize);
		}

		__wpadClearControlBlock(chan);
		_wpadIsUsedChannel[chan] = FALSE;

		if (p_wpd->connectCB)
			(*p_wpd->connectCB)(chan, WPAD_ENODEV);
	}
}

static void __wpadReceiveCallback(UINT8 dev_handle, UINT8 *p_rpt,
                                  UINT16 len __attribute__((unused)))
{
	signed result __attribute__((unused));

	OSAssertMessage_Line(3052, dev_handle <= WUD_MAX_DEV_ENTRY,
	                     "__wpadReceiveCallback(): Illegal dev_handle!\n");

	if (dev_handle > WUD_MAX_DEV_ENTRY)
		return;

	UINT8 port = _wpadHandle2PortTable[dev_handle];

	if (port < (u32)WPAD_MAX_CONTROLLERS)
		result = WPADiHIDParser(port, p_rpt);

	(void)result; // cool
}

static WPADResult __wpadGetConnectionStatus(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3088, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult connStatus = p_wpd->status;

	OSRestoreInterrupts(intrStatus);

	return connStatus;
}

void WPADGetAccGravityUnit(WPADChannel chan, WPADAccGravityUnitType type,
                           WPADAccGravityUnit *acc)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3112, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));
	OSAssert_Line(3113, p_wpd->status != WPAD_ERR_NO_CONTROLLER);
	OSAssert_Line(3114, acc != NULL);

	BOOL intrStatus = OSDisableInterrupts();

	if (acc != NULL)
	{
		switch (type)
		{
		case WPAD_ACC_GRAVITY_UNIT_CORE:
			acc->x = p_wpd->devConfig.accX1g - p_wpd->devConfig.accX0g;
			acc->y = p_wpd->devConfig.accY1g - p_wpd->devConfig.accY0g;
			acc->z = p_wpd->devConfig.accZ1g - p_wpd->devConfig.accZ0g;
			break;

		case WPAD_ACC_GRAVITY_UNIT_FS:
			acc->x = p_wpd->extConfig.fs.accX1g - p_wpd->extConfig.fs.accX0g;
			acc->y = p_wpd->extConfig.fs.accY1g - p_wpd->extConfig.fs.accY0g;
			acc->z = p_wpd->extConfig.fs.accZ1g - p_wpd->extConfig.fs.accZ0g;
			break;
		}
	}

	OSRestoreInterrupts(intrStatus);
}

// WPADGetCLTriggerThreshold ([SGLEA4]/MAP/GormitiDebug.MAP:25321)
extern void __deadstrip2(void)
{
	(void)"Failed assertion p_wpd->devType == WPAD_DEV_CLASSIC";
	(void)"Failed assertion left != NULL && right != NULL";
}

static void __wpadDisconnectCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (result == WPAD_ENODEV)
		return;

	BTA_HhClose(p_wpd->devHandle);
}

static inline void __wpadDisconnect(WPADChannel chan, BOOL afkDisconnect)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADResult connStatus = __wpadGetConnectionStatus(chan);
	if (connStatus == WPAD_ENODEV)
		return;

	if (afkDisconnect)
	{
		BOOL intrStatus = OSDisableInterrupts();

		if (p_wpd->sleeping)
		{
			OSRestoreInterrupts(intrStatus);
			return;
		}

		p_wpd->sleeping = TRUE;

		OSRestoreInterrupts(intrStatus);

		WPADControlLed(chan, 0, &__wpadDisconnectCallback);
	}
	else
	{
		BD_ADDR devAddr;
		WPADGetAddress(chan, devAddr);

		btm_remove_acl(devAddr);
	}
}

void WPADDisconnect(WPADChannel chan)
{
	wpad_cb_st *p_wpd __attribute__((unused)) = __rvl_p_wpadcb[chan];

	WPADResult connStatus = __wpadGetConnectionStatus(chan);
	if (connStatus == WPAD_ENODEV)
		return;

	WUDSetDeviceHistory(chan, NULL);
	__wpadDisconnect(chan, TRUE);
}

WPADResult WPADProbe(WPADChannel chan, WPADDeviceType *devTypeOut)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3332, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	BOOL intrStatus = OSDisableInterrupts();

	if (devTypeOut)
		*devTypeOut = p_wpd->devType;

	WPADResult status = p_wpd->status;
	if (status != WPAD_ENODEV)
	{
		if (p_wpd->devType == WPAD_DEV_NONE)
			status = WPAD_ENODEV;
		else if (!p_wpd->handshakeFinished)
			status = WPAD_ECOMM;
	}

	OSRestoreInterrupts(intrStatus);

	return status;
}

WPADSamplingCallback *WPADSetSamplingCallback(WPADChannel chan,
                                              WPADSamplingCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3371, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	if (WPADIsUsedCallbackByKPAD())
	{
		// clang-format off
		OSReport("WARNING: Overwritten the callback needed by KPAD.\n");
		OSReport("         Please call KPADSetSamplingCallback instead of "
		                  "WPADSetSamplingCallback.\n");
		// clang-format on
	}

	WPADSamplingCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wpd->samplingCB;
	p_wpd->samplingCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

WPADConnectCallback *WPADSetConnectCallback(WPADChannel chan,
                                            WPADConnectCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3402, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	if (WPADIsUsedCallbackByKPAD())
	{
		// clang-format off
		OSReport("WARNING: Overwritten the callback needed by KPAD.\n");
		OSReport("         Please call KPADSetConnectCallback instead of "
		                  "WPADSetConnectCallback.\n");
		// clang-format on
	}

	WPADConnectCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wpd->connectCB;
	p_wpd->connectCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

WPADExtensionCallback *WPADSetExtensionCallback(WPADChannel chan,
                                                WPADExtensionCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3434, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	WPADExtensionCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wpd->extensionCB;
	p_wpd->extensionCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

WPADDataFormat WPADGetDataFormat(WPADChannel chan)
{
	WPADDataFormat format;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3477, 0 <= chan && chan < WPAD_MAX_CONTROLLERS);

	BOOL intrStatus = OSDisableInterrupts();

	format = p_wpd->dataFormat;

	OSRestoreInterrupts(intrStatus);

	return format;
}

WPADResult WPADSetDataFormat(WPADChannel chan, WPADDataFormat fmt)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3524, 0 <= chan && chan < WPAD_MAX_CONTROLLERS);
	OSAssert_Line(3525, WUDIsLinkedWBC() || fmt != WPAD_FMT_BALANCE_CHECKER);
	OSAssert_Line(3526, WPADIsEnabledTRN() || fmt != WPAD_FMT_TRAIN);
	OSAssert_Line(3527, WPADIsEnabledGTR() || fmt != WPAD_FMT_GUITAR);
	OSAssert_Line(3528, WPADIsEnabledDRM() || fmt != WPAD_FMT_DRUM);
	OSAssert_Line(3529, WPADIsEnabledVSM() || fmt != WPAD_FMT_VSM);
	OSAssert_Line(3530, WPADIsEnabledTKO() || fmt != WPAD_FMT_TAIKO);
	OSAssert_Line(3531, WPADIsEnabledTBL() || fmt != WPAD_FMT_TURNTABLE);
	OSAssert_Line(3532, WPADIsEnabledBLK() || fmt != WPAD_FMT_BULK);

	WPADResult status;
	BOOL intrStatus = OSDisableInterrupts();

	BOOL handshakeFinished = p_wpd->handshakeFinished;
	status = p_wpd->status;
	WPADDataFormat currFormat = p_wpd->dataFormat;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		return WPAD_ENODEV;

	if (!handshakeFinished)
		return WPAD_ECOMM;

	if (currFormat == fmt)
		return WPAD_ESUCCESS;

	if (WPADiSendSetReportType(&p_wpd->stdCmdQueue, fmt,
	                           p_wpd->disableContReport, NULL))
	{
		intrStatus = OSDisableInterrupts();

		p_wpd->dataFormat = fmt;
		p_wpd->interleaveFlags = WPAD_ILBUF_NONE;

		OSRestoreInterrupts(intrStatus);

		status = WPAD_ESUCCESS;
	}
	else
	{
		status = WPAD_ECOMM;
	}

	return status;
}

static void __wpadInfoCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->getInfoCB)
		(*p_wpd->getInfoCB)(chan, result);

	p_wpd->getInfoCB = NULL;
	p_wpd->getInfoBusy = FALSE;
}

WPADResult WPADGetInfoAsync(WPADChannel chan, WPADInfo *info, WPADCallback *cb)
{
	BOOL handshakeFinished;
	WPADResult status;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3619, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	BOOL intrStatus = OSDisableInterrupts();

	handshakeFinished = p_wpd->handshakeFinished;
	status = p_wpd->status;
	u8 getInfoBusy = p_wpd->getInfoBusy;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished || getInfoBusy)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	intrStatus = OSDisableInterrupts();

	p_wpd->getInfoBusy = TRUE;
	p_wpd->getInfoCB = cb;

	OSRestoreInterrupts(intrStatus);

	if (WPADiSendGetContStat(&p_wpd->stdCmdQueue, info, &__wpadInfoCallback))
	{
		status = WPAD_ESUCCESS;
		goto end;
	}

	status = WPAD_ECOMM;

	intrStatus = OSDisableInterrupts();

	p_wpd->getInfoBusy = FALSE;
	p_wpd->getInfoCB = NULL;

	OSRestoreInterrupts(intrStatus);

end:
	if (status != WPAD_ESUCCESS && cb)
		(*cb)(chan, status);

	return status;
}

// WPADGetSyncType ([SGLEA4]/MAP/GormitiDebug.MAP:25337)
extern void __deadstrip3(void)
{
	(void)"Failed assertion type != NULL";
}

void WPADControlMotor(WPADChannel chan, WPADMotorCommand command)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	int a __attribute__((unused)) = 0; // What

	OSAssert_Line(3723, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));
	OSAssert_Line(3724, ( WPAD_MOTOR_STOP == command ) || ( WPAD_MOTOR_RUMBLE == command ));

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult status = p_wpd->status;

	if (status == WPAD_ENODEV)
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	if (!_wpadRumbleFlag
	    && (command != WPAD_MOTOR_STOP || p_wpd->motorRunning != TRUE))
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	if ((command == WPAD_MOTOR_STOP && p_wpd->motorRunning == FALSE)
	    || (command == WPAD_MOTOR_RUMBLE && p_wpd->motorRunning == TRUE))
	{
		OSRestoreInterrupts(intrStatus);
		return;
	}

	p_wpd->motorRunning = command == WPAD_MOTOR_STOP ? 0 : 1;
	p_wpd->motorBusy = TRUE;

	OSRestoreInterrupts(intrStatus);
}

void WPADEnableMotor(BOOL enabled)
{
	BOOL intrStatus = OSDisableInterrupts();

	_wpadRumbleFlag = enabled;

	OSRestoreInterrupts(intrStatus);
}

BOOL WPADIsMotorEnabled(void)
{
	BOOL enabled;

	BOOL intrStatus = OSDisableInterrupts();

	enabled = _wpadRumbleFlag;

	OSRestoreInterrupts(intrStatus);

	return enabled;
}

WPADResult WPADControlLed(WPADChannel chan, u8 ledFlags, WPADCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL success;
	BOOL intrStatus;
	BOOL handshakeFinished;
	WPADResult status;

	status = WPAD_ESUCCESS;

	OSAssert_Line(3818, ( 0 <= chan ) && ( chan < WPAD_MAX_CONTROLLERS ));

	intrStatus = OSDisableInterrupts();

	status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	success = WPADiSendSetPort(&p_wpd->stdCmdQueue, ledFlags, cb);

	status = success ? WPAD_CESUCCESS : WPAD_CECOMM;

end:
	if (status != WPAD_ESUCCESS && cb)
		(*cb)(chan, status);

	return status;
}

BOOL WPADSaveConfig(SCFlushCallback *cb)
{
	BOOL success = TRUE;

	if (SCCheckStatus() != SC_STATUS_READY)
		return FALSE;

	BOOL intrStatus = OSDisableInterrupts();

	u8 speakerVol = _wpadSpeakerVol;
	u8 rumble = _wpadRumbleFlag ? 1 : 0;

	OSRestoreInterrupts(intrStatus);

	success &= SCSetWpadSpeakerVolume(speakerVol);
	success &= SCSetWpadMotorMode(rumble);

	if (success)
		SCFlushAsync(cb);
	else if (cb)
		(*cb)(SC_STATUS_FATAL);

	return success;
}

void WPADRead(WPADChannel chan, WPADStatus *status)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3905, (0 <= chan) && (chan < WPAD_MAX_CONTROLLERS));
	OSAssert_Line(3906, status != NULL);

	BOOL intrStatus = OSDisableInterrupts();

	u8 rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
	WPADStatus *rxStatus = (WPADStatus *)p_wpd->rxBufs[rxBufIndex];
	u32 fmtSize = __wpadFmt2Size(p_wpd->dataFormat);

	if (rxStatus->err != WPAD_ESUCCESS)
		fmtSize = sizeof(WPADStatus);

	memcpy(status, rxStatus, fmtSize);

	OSRestoreInterrupts(intrStatus);
}

void WPADSetAutoSamplingBuf(WPADChannel chan, void *buf, u32 length)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(3944, (0 <= chan) && (chan < WPAD_MAX_CONTROLLERS));
	OSAssert_Line(3945, (buf && length > 0) || (buf == NULL));

	BOOL intrStatus = OSDisableInterrupts();

	s8 defaultErr = p_wpd->status == WPAD_ENODEV ? WPAD_CENODEV : WPAD_CEINVAL;
	u32 fmtSize = __wpadFmt2Size(p_wpd->dataFormat);

	int i;
	if (buf)
	{
		memset(buf, 0, fmtSize * length);

		for (i = 0; (u32)i < length; i++)
			((WPADStatus *)((u32)buf + i * fmtSize))->err = defaultErr;

		p_wpd->samplingBufIndex = -1;
		p_wpd->samplingBufSize = length;
	}

	p_wpd->samplingBuf = buf;

	OSRestoreInterrupts(intrStatus);
}

void WPADiExcludeButton(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	u8 rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
	void *rxBuf = p_wpd->rxBufs[rxBufIndex];

	WPADStatus *status = rxBuf;

	if ((status->button & (WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT))
	     == (WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT))
	{
		status->button &= ~WPAD_BUTTON_RIGHT;
	}

	if ((status->button & (WPAD_BUTTON_UP | WPAD_BUTTON_DOWN))
	     == (WPAD_BUTTON_UP | WPAD_BUTTON_DOWN))
	{
		status->button &= ~WPAD_BUTTON_DOWN;
	}

	WPADCLStatus *clStatus;
	if (p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN
	     || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC
	     || p_wpd->dataFormat == WPAD_FMT_CLASSIC_BTN_ACC_DPD
	     || p_wpd->dataFormat == WPAD_FMT_GUITAR
	     || p_wpd->dataFormat == WPAD_FMT_DRUM
	     || p_wpd->dataFormat == WPAD_FMT_TAIKO)
	{
		clStatus = rxBuf;

		if ((clStatus->clButton
		      & (WPAD_BUTTON_CL_LEFT | WPAD_BUTTON_CL_RIGHT))
		     == (WPAD_BUTTON_CL_LEFT | WPAD_BUTTON_CL_RIGHT))
		{
			clStatus->clButton &= ~(WPAD_BUTTON_CL_RIGHT);
		}

		if ((clStatus->clButton & (WPAD_BUTTON_CL_UP | WPAD_BUTTON_CL_DOWN))
		     == (WPAD_BUTTON_CL_UP | WPAD_BUTTON_CL_DOWN))
		{
			clStatus->clButton &= ~WPAD_BUTTON_CL_DOWN;
		}
	}

	WPADTRStatus *trStatus;
	if (p_wpd->dataFormat == WPAD_FMT_TRAIN)
	{
		trStatus = rxBuf;

		if ((trStatus->trButton
		      & (WPAD_BUTTON_TR_LEFT | WPAD_BUTTON_TR_RIGHT))
		     == (WPAD_BUTTON_TR_LEFT | WPAD_BUTTON_TR_RIGHT))
		{
			trStatus->trButton &= ~WPAD_BUTTON_TR_RIGHT;
		}

		if ((trStatus->trButton & (WPAD_BUTTON_TR_UP | WPAD_BUTTON_TR_DOWN))
		     == (WPAD_BUTTON_TR_UP | WPAD_BUTTON_TR_DOWN))
		{
			trStatus->trButton &= ~WPAD_BUTTON_TR_DOWN;
		}
	}

	OSRestoreInterrupts(intrStatus);
}

void WPADiCopyOut(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	u32 fmtSize;
	u8 rxBufIndex = p_wpd->rxBufIndex != 0 ? 0 : 1;
	WPADStatus *status = (WPADStatus *)p_wpd->rxBufs[rxBufIndex];
	fmtSize = __wpadFmt2Size(p_wpd->dataFormat);

	WPADStatus *statusOut;
	if (p_wpd->samplingBuf)
	{
		p_wpd->samplingBufIndex++;
		if (p_wpd->samplingBufIndex >= p_wpd->samplingBufSize)
			p_wpd->samplingBufIndex = 0;

		statusOut = (WPADStatus *)((u32)p_wpd->samplingBuf
		                           + p_wpd->samplingBufIndex * fmtSize);

		if (status->err != WPAD_ESUCCESS)
			fmtSize = sizeof(WPADStatus);

		memcpy(statusOut, status, fmtSize);
	}

	if (p_wpd->samplingCB)
		(*p_wpd->samplingCB)(chan);

	p_wpd->copyOutCount++;

	OSRestoreInterrupts(intrStatus);
}

BOOL WPADIsSpeakerEnabled(WPADChannel chan)
{
	BOOL enabled;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	enabled = p_wpd->wpInfo.speaker;

	OSRestoreInterrupts(intrStatus);

	return enabled;
}

WPADResult WPADControlSpeaker(WPADChannel chan, WPADSpeakerCommand command,
                              WPADCallback *cb)
{
	// the last two bytes are different than wiibrew? so they must mean something
	byte_t data[7] = {0x00, 0x00, 0xd0, 0x07, 0x40, 0x0c, 0x0e};

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	BOOL speakerEnabled = p_wpd->wpInfo.speaker;
	BOOL handshakeFinished;
	WPADResult status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	if (command == WPAD_SPEAKER_DISABLE)
	{
		if (!speakerEnabled)
		{
			status = WPAD_ESUCCESS;
			goto end;
		}

		intrStatus = OSDisableInterrupts();

		if (WPADiIsAvailableCmdQueue(&p_wpd->stdCmdQueue, 5))
		{
			WPADiSendMuteSpeaker(&p_wpd->stdCmdQueue, TRUE, NULL);
			WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x01, WM_REG_SPEAKER_01,
			                      NULL);
			WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x00, WM_REG_SPEAKER_09,
			                      NULL);
			WPADiSendEnableSpeaker(&p_wpd->stdCmdQueue, FALSE, NULL);
			WPADiSendGetContStat(&p_wpd->stdCmdQueue, NULL, cb);

			OSRestoreInterrupts(intrStatus);

			return WPAD_ESUCCESS;
		}

		status = WPAD_ECOMM;
		OSRestoreInterrupts(intrStatus);
	}
	else
	{
		switch (command)
		{
		case WPAD_SPEAKER_ENABLE:
		case WPAD_SPEAKER_CMD_05:
			intrStatus = OSDisableInterrupts();

			if (WPADiIsAvailableCmdQueue(&p_wpd->stdCmdQueue, 7))
			{
				WPADiSendEnableSpeaker(&p_wpd->stdCmdQueue, TRUE, NULL);
				WPADiSendMuteSpeaker(&p_wpd->stdCmdQueue, TRUE, NULL);
				WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x01,
				                      WM_REG_SPEAKER_09, NULL);

				// sends 0x80 instead of 0x08?
				WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x80,
				                      WM_REG_SPEAKER_01, NULL);

				data[4] = _wpadSpeakerVol;
				WPADiSendWriteData(&p_wpd->stdCmdQueue, &data, sizeof data,
				                   WM_REG_SPEAKER_01, NULL);
				WPADiSendMuteSpeaker(&p_wpd->stdCmdQueue, FALSE, NULL);
				WPADiSendGetContStat(&p_wpd->stdCmdQueue, NULL, cb);

				OSRestoreInterrupts(intrStatus);

				return WPAD_ESUCCESS;
			}

			status = WPAD_ECOMM;

			OSRestoreInterrupts(intrStatus);

			break;

		case WPAD_SPEAKER_MUTE:
			if (!WPADiSendMuteSpeaker(&p_wpd->stdCmdQueue, TRUE, cb))
			{
				status = WPAD_ECOMM;
				goto end;
			}

			return WPAD_ESUCCESS;

		case WPAD_SPEAKER_UNMUTE:
			if (!WPADiSendMuteSpeaker(&p_wpd->stdCmdQueue, FALSE, cb))
			{
				status = WPAD_ECOMM;
				goto end;
			}

			return WPAD_ESUCCESS;

		case WPAD_SPEAKER_PLAY:
			if (!WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x01,
			                           WM_REG_SPEAKER_08, cb))
			{
				status = WPAD_ECOMM;
				goto end;
			}

			return WPAD_ESUCCESS;
		}
	}

end:
	if (cb)
		(*cb)(chan, status);

	return status;
}

u8 WPADGetSpeakerVolume(void)
{
	BOOL intrStatus = OSDisableInterrupts();

	u8 speakerVolume = _wpadSpeakerVol;

	OSRestoreInterrupts(intrStatus);

	return speakerVolume;
}

void WPADSetSpeakerVolume(u8 volume)
{
	BOOL intrStatus = OSDisableInterrupts();

	_wpadSpeakerVol = __wpadClampSpeakerVolume(volume);

	OSRestoreInterrupts(intrStatus);
}

static BOOL __wpadIsBusyStream(WPADChannel chan)
{
	BOOL intrStatus;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	intrStatus = OSDisableInterrupts();

	WPADRadioQuality radioQuality = p_wpd->radioQuality;
	u32 devType = p_wpd->devType;
	u8 bufferStatus = WUDGetBufferStatus();

	// I Love Declaration Order!!!
	u16 bteBufferStatus __attribute__((unused));
	u16 btmBufferStatus;
	u8 audioFrames;

	s8 queueSize = __wpadGetQueueSize(&p_wpd->stdCmdQueue);

	bteBufferStatus = __wpadGetBTEBufferStatus(chan); // hm?
	btmBufferStatus = __wpadGetBTMBufferStatus(chan);
	audioFrames = p_wpd->audioFrames;

	u8 linkNumber = _WUDGetLinkNumber();

	OSRestoreInterrupts(intrStatus);

	if (radioQuality != WPAD_RADIO_QUALITY_GOOD || btmBufferStatus > 3
	    || bufferStatus == 10 || bufferStatus >= linkNumber * 2 + 2
	    || devType == WPAD_DEV_INITIALIZING || queueSize >= 21
	    || audioFrames >= 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL WPADCanSendStreamData(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	BOOL handshakeFinished;
	WPADResult status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV || !handshakeFinished || __wpadIsBusyStream(chan))
		return FALSE;
	else
		return TRUE;
}

WPADResult WPADSendStreamData(WPADChannel chan, void *p_buf, u16 len)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(4420, p_buf != NULL);
	OSAssert_Line(4421, len >= 0 && len <= 20);

	BOOL intrStatus = OSDisableInterrupts();

	BOOL handshakeFinished;
	WPADResult status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		return WPAD_ENODEV;

	if (!handshakeFinished)
		return WPAD_ECOMM;

	if (__wpadIsBusyStream(chan))
		return WPAD_ECOMM;

	if (!WPADiSendStreamData(&p_wpd->stdCmdQueue, p_buf, len))
		return WPAD_ECOMM;

	intrStatus = OSDisableInterrupts();

	p_wpd->audioFrames++;

	OSRestoreInterrupts(intrStatus);

	return WPAD_ESUCCESS;
}

// WPADSetDpdSensitivity ([SGLEA4]/MAP/GormitiDebug.MAP:25355)
extern void __deadstrip4(void)
{
	(void)"Sensitivity must be from 1 to 5.\n";
}

u8 WPADGetDpdSensitivity(void)
{
	BOOL intrStatus = OSDisableInterrupts();

	u8 dpdSensitivity = _wpadDpdSense;

	OSRestoreInterrupts(intrStatus);

	return dpdSensitivity;
}

BOOL WPADIsDpdEnabled(WPADChannel chan)
{
	BOOL enabled;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	enabled = p_wpd->wpInfo.dpd;

	OSRestoreInterrupts(intrStatus);

	return enabled;
}

static void __wpadDpdCallback(WPADChannel chan,
                              WPADResult result __attribute__((unused)))
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->currentDpdCommand = p_wpd->pendingDpdCommand;
	p_wpd->dpdBusy = FALSE;
	p_wpd->wpInfo.dpd = p_wpd->pendingDpdCommand == WPAD_DPD_DISABLE ? 0 : 1;

	(void)result; // OfCourse
}

WPADResult WPADControlDpd(WPADChannel chan, WPADDpdCommand command,
                          WPADCallback *cb)
{
	// clang-format off
	static const byte_t cfg1[WPAD_MAX_DPD_SENS][9] =
	{
		{0x02, 0x00, 0x00, 0x71, 0x01, 0x00, 0x64, 0x00, 0xfe},
		{0x02, 0x00, 0x00, 0x71, 0x01, 0x00, 0x96, 0x00, 0xb4},
		{0x02, 0x00, 0x00, 0x71, 0x01, 0x00, 0xaa, 0x00, 0x64},
		{0x02, 0x00, 0x00, 0x71, 0x01, 0x00, 0xc8, 0x00, 0x36},
		{0x07, 0x00, 0x00, 0x71, 0x01, 0x00, 0x72, 0x00, 0x20}
	};

	static const byte_t cfg2[WPAD_MAX_DPD_SENS][2] =
	{
		{0xfd, 0x05},
		{0xb3, 0x04},
		{0x63, 0x03},
		{0x35, 0x03},
		{0x1f, 0x03}
	};
	// clang-format on

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	BOOL dpdEnabled = p_wpd->wpInfo.dpd;
	BOOL handshakeFinished;

	u8 currCmd __attribute__((unused)) = p_wpd->currentDpdCommand;
	u8 pendingCmd = p_wpd->pendingDpdCommand;
	WPADResult status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	if (command == WPAD_DPD_DISABLE)
	{
		if (!dpdEnabled)
		{
			status = WPAD_ESUCCESS;
			goto end;
		}

		intrStatus = OSDisableInterrupts();

		if (WPADiIsAvailableCmdQueue(&p_wpd->stdCmdQueue, 3))
		{
			p_wpd->pendingDpdCommand = command;

			WPADiSendEnableDPD(&p_wpd->stdCmdQueue, FALSE, NULL);
			WPADiSendDPDCSB(&p_wpd->stdCmdQueue, FALSE, &__wpadDpdCallback);
			WPADiSendGetContStat(&p_wpd->stdCmdQueue, NULL, cb);

			OSRestoreInterrupts(intrStatus);

			return WPAD_ESUCCESS;
		}

		status = WPAD_ECOMM;

		OSRestoreInterrupts(intrStatus);
	}
	else
	{
		if (command == pendingCmd)
			goto end;

		intrStatus = OSDisableInterrupts();

		if (WPADiIsAvailableCmdQueue(&p_wpd->stdCmdQueue, 8))
		{
			p_wpd->pendingDpdCommand = command;
			p_wpd->dpdBusy = TRUE;

			WPADiSendEnableDPD(&p_wpd->stdCmdQueue, TRUE, NULL);
			WPADiSendDPDCSB(&p_wpd->stdCmdQueue, TRUE, NULL);
			WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x01, WM_REG_DPD_30,
			                      NULL);
			WPADiSendWriteData(&p_wpd->stdCmdQueue, cfg1[_wpadDpdSense - 1],
			                   sizeof cfg1[_wpadDpdSense - 1],
			                   WM_REG_DPD_CONFIG_BLOCK_1, NULL);
			WPADiSendWriteData(&p_wpd->stdCmdQueue, cfg2[_wpadDpdSense - 1],
			                   sizeof cfg2[_wpadDpdSense - 1],
			                   WM_REG_DPD_CONFIG_BLOCK_2, NULL);
			WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, command,
			                      WM_REG_DPD_DATA_FORMAT, NULL);
			WPADiSendWriteDataCmd(&p_wpd->stdCmdQueue, 0x08, WM_REG_DPD_30,
			                      &__wpadDpdCallback);
			WPADiSendGetContStat(&p_wpd->stdCmdQueue, NULL, cb);

			OSRestoreInterrupts(intrStatus);

			return WPAD_ESUCCESS;
		}

		status = WPAD_ECOMM;

		OSRestoreInterrupts(intrStatus);
	}

end:
	if (cb)
		(*cb)(chan, status);

	return status;
}

WPADResult WPADControlBLC(WPADChannel chan, WPADBLCCommand command,
                          WPADCallback *cb)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(4763, WUDIsLinkedWBC());

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult status = p_wpd->status;
	BOOL handshakeFinished = p_wpd->handshakeFinished;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished || !WUDIsLinkedWBC())
	{
		status = WPAD_ECOMM;
		goto end;
	}
	else
	{
		byte_t data[7];
		data[0] = data[1] = data[2] = 0xaa;
		data[3] = 0x55;
		data[4] = data[5] = data[6] = command;

		intrStatus = OSDisableInterrupts();

		switch (command)
		{
		case WPAD_BLC_ENABLE:
			if (WPADiIsAvailableCmdQueue(&p_wpd->stdCmdQueue, 4))
			{
				WPADWriteExtReg(chan, data, sizeof data, WPAD_EXT_REG_EXTENSION,
				                0xf1, NULL);
				WPADWriteExtReg(chan, data, 1, WPAD_EXT_REG_EXTENSION, 0xf1,
				                NULL);
				WPADWriteExtReg(chan, data, 1, WPAD_EXT_REG_EXTENSION, 0xf1,
				                NULL);
				WPADWriteExtReg(chan, data, 1, WPAD_EXT_REG_EXTENSION, 0xf1,
				                cb);

				OSRestoreInterrupts(intrStatus);

				return WPAD_ESUCCESS;
			}

			status = WPAD_ECOMM;
			break;

		case WPAD_BLC_CMD_55:
			status = WPADWriteExtReg(chan, data, sizeof data,
			                         WPAD_EXT_REG_EXTENSION, 0xf1, cb);

			if (status == WPAD_ESUCCESS)
			{
				OSRestoreInterrupts(intrStatus);
				return WPAD_ESUCCESS;
			}

			break;

		case WPAD_BLC_DISABLE:
			status = WPADWriteExtReg(chan, data, 1, WPAD_EXT_REG_EXTENSION,
			                         0xf1, cb);

			if (status == WPAD_ESUCCESS)
			{
				OSRestoreInterrupts(intrStatus);
				return WPAD_ESUCCESS;
			}

			break;

		default:
			status = WPAD_ECOMM;
			break;
		}
	}

	OSRestoreInterrupts(intrStatus);

end:
	if (cb)
		(*cb)(chan, status);

	return status;
}

// clang-format off
// Various functions in between ([SGLEA4]/MAP/GormitiDebug.MAP:25366-25379)
extern void __deadstrip5(void)
{
	(void)"Failed assertion ( addr >= 0x20 && addr < 0x24 ) || ( addr >= 0xf1 && addr < 0xf6 )";
	(void)"Failed assertion ( addr >= WPAD_BLCLB_BLK1_ADDR && addr + (len - 1) < WPAD_BLCLB_BLK3_ADDR + WPAD_BLCLB_BLK3_LEN ) || ( addr >= WPAD_BLCLB_BLK4_ADDR && addr + (len - 1) < WPAD_BLCLB_BLK5_ADDR + WPAD_BLCLB_BLK5_LEN )";
	(void)"Failed assertion addr >= WPAD_VSMCLB_ADDR1 && addr + (len - 1) < WPAD_VSMCLB_ADDR1 + WPAD_VSMCLB_LEN";
}
// clang-format on

u8 WPADiGetMplsStatus(WPADChannel chan)
{
	u8 status = 0;

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	if (p_wpd->devType == WPAD_DEV_MOTION_PLUS
	     || p_wpd->devType == WPAD_DEV_MPLS_PT_FS
	     || p_wpd->devType == WPAD_DEV_MPLS_PT_CLASSIC
	     || p_wpd->devType == WPAD_DEV_MPLS_PT_UNKNOWN)
	{
		status = p_wpd->devMode;
	}

	OSRestoreInterrupts(intrStatus);

	return status;
}

// WPADGetMplsStatus ([SGLEA4]/MAP/GormitiDebug.MAP:25381)
extern void __deadstrip6(void)
{
	(void)"WPADGetMplsStatus is obsolete.\n";
}

static void __wpadMplsCallback(WPADChannel chan, WPADResult result)
{
#define CALC_STATUS(x)	(!(x) ? WPAD_CECOMM : WPAD_CESUCCESS)

	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADResult status = result;
	WPADCallback *controlMplsCB;
	u32 addr;

	switch (p_wpd->mplsCBState)
	{
	case WPAD_STATE_MPLS_CB_1:
		if (result == WPAD_ESUCCESS)
		{
			if (p_wpd->mplsCBReadBuf[1] != WPAD_DEV_MOTION_PLUS
			     && p_wpd->mplsCBReadBuf[1] != WPAD_DEV_MPLS_PT_FS
			     && p_wpd->mplsCBReadBuf[1] != WPAD_DEV_MPLS_PT_CLASSIC
			     && p_wpd->mplsCBReadBuf[1] != WPAD_DEV_MPLS_PT_UNKNOWN)
			{
				p_wpd->mplsCBCounter--;
				if (!p_wpd->mplsCBCounter)
				{
					status = WPAD_ERR_3;
				}
				else
				{
					if (p_wpd->mplsCBCounter > 1)
						p_wpd->mplsCBReadAddress = WM_REG_MPLS_DEV_MODE;
					else
						p_wpd->mplsCBReadAddress = WM_REG_EXTENSION_DEV_MODE;

					status = CALC_STATUS(WPADiSendReadData(
						&p_wpd->stdCmdQueue, &p_wpd->mplsCBReadBuf, 2,
						p_wpd->mplsCBReadAddress, &__wpadMplsCallback));
				}
			}
			else
			{
				addr = (p_wpd->mplsCBReadAddress & ~0xff) | 0xf0;
				if (addr == WM_REG_MPLS_F0)
				{
					p_wpd->mplsCBState =
						WPAD_STATE_MPLS_CB_WRITE_PENDING_MPLS_DEV_MODE;
					status = CALC_STATUS(WPADiSendWriteDataCmd(
						&p_wpd->stdCmdQueue, 0x55, addr, &__wpadMplsCallback));
				}
				else if (p_wpd->mplsCBReadBuf[0] == p_wpd->pendingMplsCommand)
				{
					p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_START;
				}
				else if (--p_wpd->mplsCBCounter)
				{
					p_wpd->mplsCBReadAddress = WM_REG_EXTENSION_DEV_MODE;
					status = CALC_STATUS(WPADiSendReadData(
						&p_wpd->stdCmdQueue, &p_wpd->mplsCBReadBuf, 2,
						p_wpd->mplsCBReadAddress, &__wpadMplsCallback));
				}
				else
				{
					p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_GET_EXTENSION_ID;
					status = CALC_STATUS(WPADiSendWriteDataCmd(
						&p_wpd->stdCmdQueue, 0x00, WM_REG_EXTENSION_DEV_MODE,
						&__wpadMplsCallback));
				}
			}
		}
		else if (result == WPAD_ERR_3)
		{
			if (p_wpd->mplsCBCounter)
			{
				if (--p_wpd->mplsCBCounter > 1)
					p_wpd->mplsCBReadAddress = WM_REG_MPLS_DEV_MODE;
				else
					p_wpd->mplsCBReadAddress = WM_REG_EXTENSION_DEV_MODE;

				status = CALC_STATUS(WPADiSendReadData(
					&p_wpd->stdCmdQueue, &p_wpd->mplsCBReadBuf, 2,
					p_wpd->mplsCBReadAddress, &__wpadMplsCallback));
			}
		}
		break;

	case WPAD_STATE_MPLS_CB_CLEAR_DEV_MODE:
		if (result == WPAD_ESUCCESS)
		{
			if (p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MOTION_PLUS
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_FS
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_CLASSIC
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_UNKNOWN)
			{
				p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_DONE;

				status = CALC_STATUS(WPADiSendWriteDataCmd(
					&p_wpd->stdCmdQueue, 0x00, WM_REG_EXTENSION_DEV_MODE,
					&__wpadMplsCallback));
			}
			else
			{
				status = WPAD_ERR_3;
			}
		}

		break;

	case WPAD_STATE_MPLS_CB_WRITE_PENDING_MPLS_DEV_MODE:
		if (result == WPAD_ESUCCESS)
		{
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_INIT_MPLS_EXT;

			status = CALC_STATUS(WPADiSendWriteDataCmd(
				&p_wpd->stdCmdQueue, p_wpd->pendingMplsCommand,
				WM_REG_MPLS_DEV_MODE, &__wpadMplsCallback));
		}

		break;

	case WPAD_STATE_MPLS_CB_INIT_MPLS_EXT:
		if (result == WPAD_ESUCCESS)
		{
			p_wpd->isInitingMpls = TRUE;
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_START;
		}

		break;

	case WPAD_STATE_MPLS_CB_5:
		if (result == WPAD_ESUCCESS)
		{
			if (p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MOTION_PLUS
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_FS
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_CLASSIC
			     || p_wpd->mplsCBReadBuf[1] == WPAD_DEV_MPLS_PT_UNKNOWN)
			{
				p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_RESET;

				status = CALC_STATUS(WPADiSendWriteDataCmd(
					&p_wpd->stdCmdQueue, 0x00, WM_REG_EXTENSION_F2,
					&__wpadMplsCallback));
			}
			else
			{
				status = WPAD_ERR_3;
			}
		}

		break;

	case WPAD_STATE_MPLS_CB_GET_EXTENSION_ID:
		if (result == WPAD_ESUCCESS)
		{
			p_wpd->mplsCBCounter = 4;
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_1;

			status = CALC_STATUS(
				WPADiSendReadData(&p_wpd->stdCmdQueue, &p_wpd->mplsCBReadBuf, 1,
			                      WM_REG_MPLS_ID_BYTE, &__wpadMplsCallback));
		}

		break;

	case WPAD_STATE_MPLS_CB_DONE:
		status = WPAD_ESUCCESS;

		// fallthrough

	case WPAD_STATE_MPLS_CB_RESET:
		p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_START;
		break;
	}

	if (p_wpd->mplsCBState == WPAD_STATE_MPLS_CB_START
	    || status != WPAD_ESUCCESS)
	{
		controlMplsCB = p_wpd->controlMplsCB;
		p_wpd->controlMplsBusy = FALSE;
		p_wpd->controlMplsCB = NULL;

		if (controlMplsCB)
			(*controlMplsCB)(chan, status);
	}

#undef CALC_STATUS
}

WPADResult WPADiControlMpls(WPADChannel chan, WPADMplsCommand command,
                            WPADCallback *cb)
{
	BOOL intrStatus;
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	intrStatus = OSDisableInterrupts();

	BOOL handshakeFinished;
	u32 devType = p_wpd->devType;
	u8 devMode = p_wpd->devMode;
	WPADResult status = p_wpd->status;
	handshakeFinished = p_wpd->handshakeFinished;
	u8 controlMplsCBRegistered =
		p_wpd->controlMplsCB ? TRUE : p_wpd->controlMplsBusy;

	if (status == WPAD_ENODEV)
		goto end;

	if (!handshakeFinished || controlMplsCBRegistered)
	{
		status = WPAD_ECOMM;
		goto end;
	}

	if (p_wpd->certValidityStatus < 0) // == WPAD_CERT_INVALID
	{
		status = WPAD_EINVAL;
		goto end;
	}

	if (command == devMode)
	{
		status = WPAD_ESUCCESS;
		goto end;
	}

	// clang-format off
	if (((devType == WPAD_DEV_MOTION_PLUS
		|| devType == WPAD_DEV_MPLS_PT_FS
		|| devType == WPAD_DEV_MPLS_PT_CLASSIC
		|| devType == WPAD_DEV_MPLS_PT_UNKNOWN)
			&& (command == WPAD_MPLS_DISABLE
			|| command == WPAD_MPLS_CMD_80))
		|| ((devType != WPAD_DEV_MOTION_PLUS
		&& devType != WPAD_DEV_MPLS_PT_FS
		&& devType != WPAD_DEV_MPLS_PT_CLASSIC
		&& devType != WPAD_DEV_MPLS_PT_UNKNOWN)
			&& (command == WPAD_MPLS_MAIN
			|| command == WPAD_MPLS_FS
			|| command == WPAD_MPLS_CLASSIC)))
	// clang-format on
	{
		if (command == WPAD_MPLS_CMD_80 && p_wpd->mplsUptimeMs < 200)
		{
			status = WPAD_ECOMM;
			goto end;
		}

		p_wpd->pendingMplsCommand = command;
		p_wpd->mplsCBCounter = 4;
		status = WPAD_ESUCCESS;

		switch (command)
		{
		case WPAD_MPLS_DISABLE:
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_CLEAR_DEV_MODE;
			p_wpd->mplsCBReadAddress = WM_REG_EXTENSION_DEV_MODE;
			break;

		case WPAD_MPLS_CMD_80:
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_5;
			p_wpd->mplsCBReadAddress = WM_REG_EXTENSION_DEV_MODE;
			break;

		default:
			p_wpd->mplsCBState = WPAD_STATE_MPLS_CB_1;
			p_wpd->mplsCBReadAddress = WM_REG_MPLS_DEV_MODE;
			break;
		}

		if (!WPADiSendReadData(&p_wpd->stdCmdQueue, &p_wpd->mplsCBReadBuf, 2,
		                       p_wpd->mplsCBReadAddress, &__wpadMplsCallback))
		{
			status = WPAD_ECOMM;
			goto end;
		}

		p_wpd->controlMplsBusy = TRUE;
		p_wpd->controlMplsCB = cb;

		OSRestoreInterrupts(intrStatus);

		return WPAD_ESUCCESS;
	}
	else
	{
		status = WPAD_EINVAL;
	}

end: // earlier this time. hm
	OSRestoreInterrupts(intrStatus);

	if (cb)
		(*cb)(chan, status);

	return status;
}

// WPADControlMpls ([SGLEA4]/MAP/GormitiDebug.MAP:25384)
extern void __deadstrip7(void)
{
	(void)"WPADControlMpls is obsolete.\n";
}

void WPADiGetMplsCalibration(WPADChannel chan, struct WPADMplsCalibration *high,
                             struct WPADMplsCalibration *low)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSAssert_Line(5516, high != NULL && low != NULL);

	BOOL intrStatus = OSDisableInterrupts();

	if (high != NULL && low != NULL)
	{
		*high = p_wpd->extConfig.mpls.high;
		*low = p_wpd->extConfig.mpls.low;
	}

	OSRestoreInterrupts(intrStatus);
}

// WPADGetMplsCalibration ([SGLEA4]/MAP/GormitiDebug.MAP:25386)
extern void __deadstrip8(void)
{
	(void)"WPADGetMplsCalibration is obsolete.\n";
}

// WPADSetMplsCalibration ([SGLEA4]/MAP/GormitiDebug.MAP:25387)
extern void __deadstrip9(void)
{
	(void)"WPADSetMplsCalibration is obsolete.\n";
}

BOOL WPADiSendSetPort(struct WPADCmdQueue *cmdQueue, u8 port, WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_SET_PORT;
	cmdBlk.dataLength = RPT11_SIZE;
	cmdBlk.dataBuf[RPT11_LED] = port << 4;
	cmdBlk.cmdCB = cb;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendSetReportType(struct WPADCmdQueue *cmdQueue, s32 format,
                            BOOL notContinuous, WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_SET_DATA_REPORT_MODE;
	cmdBlk.dataLength = RPT12_SIZE;
	cmdBlk.dataBuf[RPT12_CONT_REPORT] = notContinuous ? 0 : 4;
	cmdBlk.cmdCB = cb;

	switch (format)
	{
	case WPAD_FMT_CORE_BTN:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN;
		break;

	case WPAD_FMT_CORE_BTN_ACC:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC;
		break;

	case WPAD_FMT_CORE_BTN_ACC_DPD:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD12;
		break;

	case WPAD_FMT_FS_BTN:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_EXT8;
		break;

	case WPAD_FMT_FS_BTN_ACC:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_EXT16;
		break;

	case WPAD_FMT_FS_BTN_ACC_DPD:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_CLASSIC_BTN:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_EXT8;
		break;

	case WPAD_FMT_CLASSIC_BTN_ACC:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_EXT16;
		break;

	case WPAD_FMT_CLASSIC_BTN_ACC_DPD:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_BTN_ACC_DPD_EXTENDED:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD18_1;
		break;

	case WPAD_FMT_TRAIN:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_EXT8;
		break;

	case WPAD_FMT_GUITAR:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_DRUM:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_TURNTABLE:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_BULK:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_EXT16;
		break;

	case WPAD_FMT_BALANCE_CHECKER:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_EXT19;
		break;

	case WPAD_FMT_VSM:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_EXT16;
		break;

	case WPAD_FMT_TAIKO:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;

	case WPAD_FMT_MOTION_PLUS:
		cmdBlk.dataBuf[RPT12_DATA_REPORT_MODE] = RPTID_DATA_BTN_ACC_DPD10_EXT9;
		break;
	}

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendEnableDPD(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                        WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_ENABLE_DPD;
	cmdBlk.dataLength = RPT13_SIZE;
	cmdBlk.dataBuf[RPT13_DPD_ENABLE] = enabled ? 4 : 0;
	cmdBlk.cmdCB = cb;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendEnableSpeaker(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                            WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_ENABLE_SPEAKER;
	cmdBlk.dataLength = RPT14_SIZE;
	cmdBlk.dataBuf[RPT14_SPEAKER_ENABLE] = enabled ? 4 : 0;
	cmdBlk.cmdCB = cb;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

// SendGetContinuousStatus?
// this is just the request status report report; what is Cont
BOOL WPADiSendGetContStat(struct WPADCmdQueue *cmdQueue, WPADInfo *wpInfoOut,
                          WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_REQUEST_STATUS;
	cmdBlk.dataLength = RPT15_SIZE;
	cmdBlk.dataBuf[0] = 0; // nothing special
	cmdBlk.cmdCB = cb;
	cmdBlk.statusReportOut = wpInfoOut;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendWriteDataCmd(struct WPADCmdQueue *cmdQueue, u8 cmd, u32 address,
                           WPADCallback *cb)
{
	return WPADiSendWriteData(cmdQueue, &cmd, sizeof cmd, address, cb);
}

BOOL WPADiSendWriteData(struct WPADCmdQueue *cmdQueue, const void *p_buf,
                        u16 len, u32 address, WPADCallback *cb)
{
	BOOL success;
	u8 packedLen = len & 0x1f;

	OSAssert_Line(5721, len > 0 && len <= 16);
	OSAssert_Line(5722, p_buf != NULL);

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_WRITE_DATA;
	cmdBlk.dataLength = RPT16_SIZE;
	cmdBlk.cmdCB = cb;
	memcpy(&cmdBlk.dataBuf[RPT16_DATA_DST_ADDRESS], &address, sizeof address);
	memcpy(&cmdBlk.dataBuf[RPT16_DATA_LENGTH], &packedLen, sizeof packedLen);
	memcpy(&cmdBlk.dataBuf[RPT16_DATA], p_buf, len);

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendReadData(struct WPADCmdQueue *cmdQueue, void *p_buf, u16 len,
                       u32 address, WPADCallback *cb)
{
	BOOL success;

	OSAssert_Line(5740, p_buf != NULL);

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_READ_DATA;
	cmdBlk.dataLength = RPT17_SIZE;
	cmdBlk.cmdCB = cb;
	memcpy(&cmdBlk.dataBuf[RPT17_DATA_SRC_ADDRESS], &address, sizeof address);
	memcpy(&cmdBlk.dataBuf[RPT17_DATA_LENGTH], &len, sizeof len);
	cmdBlk.dstBuf = p_buf;
	cmdBlk.readLength = len;
	cmdBlk.readAddress = address;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendStreamData(struct WPADCmdQueue *cmdQueue, const void *p_buf,
                         u16 len)
{
	BOOL success;
	u8 packedLen = len << 3;

	OSAssert_Line(5764, len > 0 && len <= 20);

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_SEND_SPEAKER_DATA;
	cmdBlk.dataLength = sizeof cmdBlk.dataBuf;
	cmdBlk.dataBuf[RPT18_DATA_LENGTH] = packedLen;
	cmdBlk.cmdCB = NULL;
	memcpy(&cmdBlk.dataBuf[RPT18_DATA], p_buf, len);

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendMuteSpeaker(struct WPADCmdQueue *cmdQueue, BOOL muted,
                          WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_MUTE_SPEAKER;
	cmdBlk.dataLength = RPT19_SIZE;
	cmdBlk.dataBuf[RPT19_SPEAKER_MUTE] = muted ? 4 : 0;
	cmdBlk.cmdCB = cb;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiSendDPDCSB(struct WPADCmdQueue *cmdQueue, BOOL enabled,
                     WPADCallback *cb)
{
	BOOL success;

	struct WPADCmd cmdBlk;
	cmdBlk.reportID = RPTID_SEND_DPD_CSB;
	cmdBlk.dataLength = RPT1A_SIZE;
	cmdBlk.dataBuf[RPT1A_DPD_CSB] = enabled ? 4 : 0;
	cmdBlk.cmdCB = cb;

	success = __wpadPushCommand(cmdQueue, cmdBlk);
	return success;
}

BOOL WPADiIsAvailableCmdQueue(struct WPADCmdQueue *cmdQueue, s8 num)
{
	s8 queueSize = __wpadGetQueueSize(cmdQueue);

	if ((u32)(queueSize + num) <= cmdQueue->length - 1)
		return TRUE;
	else
		return FALSE;
}

static s8 __wpadGetQueueSize(struct WPADCmdQueue *cmdQueue)
{
	BOOL intrStatus = OSDisableInterrupts();

	s8 queueRemaining = cmdQueue->indexIn - cmdQueue->indexOut;

	if (queueRemaining < 0)
		queueRemaining += cmdQueue->length;

	OSRestoreInterrupts(intrStatus);

	return queueRemaining;
}

void WPADiClearQueue(struct WPADCmdQueue *cmdQueue)
{
	BOOL intrStatus = OSDisableInterrupts();

	cmdQueue->indexOut = 0;
	cmdQueue->indexIn = 0;
	memset(cmdQueue->queue, 0, sizeof *cmdQueue->queue * cmdQueue->length);

	OSRestoreInterrupts(intrStatus);
}

static BOOL __wpadPushCommand(struct WPADCmdQueue *cmdQueue,
                              struct WPADCmd cmdBlk)
{
	BOOL intrStatus = OSDisableInterrupts();

	if (cmdQueue->length - 1 == (u32)__wpadGetQueueSize(cmdQueue))
	{
		OSRestoreInterrupts(intrStatus);

		return FALSE;
	}

	// unnecessary call
	memset(&cmdQueue->queue[cmdQueue->indexIn], 0,
	       sizeof cmdQueue->queue[cmdQueue->indexIn]);

	memcpy(&cmdQueue->queue[cmdQueue->indexIn], &cmdBlk,
	       sizeof cmdQueue->queue[cmdQueue->indexIn]);

	cmdQueue->indexIn = (u32)cmdQueue->indexIn == ((cmdQueue->length) - 1)
	                      ? 0
	                      : cmdQueue->indexIn + 1;

	OSRestoreInterrupts(intrStatus);

	return TRUE;
}

static BOOL __wpadGetCommand(struct WPADCmdQueue *cmdQueue,
                             struct WPADCmd *cmdBlkOut)
{
	if (__wpadGetQueueSize(cmdQueue) == 0)
		return FALSE;

	BOOL intrStatus = OSDisableInterrupts();

	memcpy(cmdBlkOut, &cmdQueue->queue[cmdQueue->indexOut], sizeof *cmdBlkOut);

	OSRestoreInterrupts(intrStatus);

	return TRUE;
}

static BOOL __wpadPopCommand(struct WPADCmdQueue *cmdQueue)
{
	BOOL intrStatus = OSDisableInterrupts();

	if (__wpadGetQueueSize(cmdQueue) == 0)
	{
		OSRestoreInterrupts(intrStatus);
		return FALSE;
	}

	memset(&cmdQueue->queue[cmdQueue->indexOut], 0,
	       sizeof cmdQueue->queue[cmdQueue->indexOut]);

	cmdQueue->indexOut = (u32)cmdQueue->indexOut == cmdQueue->length - 1
	                       ? 0
	                       : cmdQueue->indexOut + 1;

	OSRestoreInterrupts(intrStatus);

	return TRUE;
}

static BOOL __wpadSetSensorBarPower(BOOL enabled)
{
	u32 reg;
	BOOL intrStatus = OSDisableInterrupts();

	reg = ACRReadReg(0xc0);

	register_t newStatus;
	if (enabled)
		newStatus = reg | (1 << 8);
	else
		newStatus = reg & ~(1 << 8);

	ACRWriteReg(0xc0, newStatus);
	BOOL oldStatus = reg & (1 << 8) ? 1 : 0;

	OSRestoreInterrupts(intrStatus);

	return oldStatus;
}

static void __wpadSetScreenSaverFlag(BOOL disabled)
{
	if (disabled)
		__VIResetRFIdle();
}

static u8 __wpadGetDpdSensitivity(void)
{
	u8 dpdSens = SCGetBtDpdSensibility();

	if (dpdSens < WPAD_MIN_DPD_SENS)
		dpdSens = WPAD_MIN_DPD_SENS;

	if (dpdSens > WPAD_MAX_DPD_SENS)
		dpdSens = WPAD_MAX_DPD_SENS;

	return dpdSens;
}

static u8 __wpadGetSensorBarPosition(void)
{
	return SCGetWpadSensorBarPosition() == SC_SENSOR_BAR_TOP
	         ? SC_SENSOR_BAR_TOP
	         : SC_SENSOR_BAR_BOTTOM;
}

static u32 __wpadGetMotorMode(void)
{
	// ?
	return !!(SCGetWpadMotorMode() == 1);
}

static u8 __wpadClampSpeakerVolume(u8 volume)
{
	u8 clampedVol = volume;

	if (volume <= 0)
		clampedVol = 0;

	if (volume >= 127)
		clampedVol = 127;

	return clampedVol;
}

static u8 __wpadGetSpeakerVolume(void)
{
	u8 volume = SCGetWpadSpeakerVolume();
	volume = __wpadClampSpeakerVolume(volume);
	return volume;
}

static u16 __wpadGetBTEBufferStatus(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult status = p_wpd->status;
	WUDDevHandle dev_handle = p_wpd->devHandle;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		return 0;

	return _WUDGetQueuedSize(dev_handle);
}

static u16 __wpadGetBTMBufferStatus(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	WPADResult status = p_wpd->status;
	WUDDevHandle dev_handle = p_wpd->devHandle;

	OSRestoreInterrupts(intrStatus);

	if (status == WPAD_ENODEV)
		return 0;

	return _WUDGetNotAckedSize(dev_handle);
}

void WPADRecalibrate(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	BOOL intrStatus = OSDisableInterrupts();

	p_wpd->calibrated = FALSE;
	p_wpd->recalibHoldMs = 0;

	OSRestoreInterrupts(intrStatus);
}

#if !defined(NDEBUG)
BOOL WPADiIsDummyExtension(WPADChannel chan)
{
	return _wpadDummyAttach[chan];
}
#endif

BOOL WPADIsUsedCallbackByKPAD(void)
{
	return _wpadUsedCallback;
}

void WPADSetCallbackByKPAD(BOOL isKPAD)
{
	_wpadUsedCallback = isKPAD;
}

static void __wpadCertFailed(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	switch (p_wpd->certState)
	{
	case WPAD_STATE_CERT_PROBE_X:
	case WPAD_STATE_CERT_GET_X:
	case WPAD_STATE_CERT_VERIFY_X:
	case WPAD_STATE_CERT_CHALLENGE:
	case WPAD_STATE_CERT_PROBE_Y:
	case WPAD_STATE_CERT_GET_Y:
	case WPAD_STATE_CERT_VERIFY_Y:
	case WPAD_STATE_CERT_CHECK:
	case WPAD_STATE_CERT_ETIME:
	default: // ???
		p_wpd->certValidityStatus = WPAD_CERT_INVALID;
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
		p_wpd->certMayVerifyByCalibBlock = -1;
		p_wpd->devType = WPAD_DEV_252;

		break;
	}

	if (p_wpd->extensionCB)
		(*p_wpd->extensionCB)(chan, WPAD_DEV_252);
}

static void __wpadCertCalcMulX(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->certChallengeRandomBit != 0)
		LINTMul(p_wpd->certBufBig, p_wpd->certBuf0, certv);
	else
		memcpy(p_wpd->certBufBig, p_wpd->certBuf0, sizeof p_wpd->certBuf0);

	p_wpd->certWorkBusy = FALSE;
	p_wpd->certStateWorkMs = 0;
	p_wpd->certState = WPAD_STATE_CERT_CALC_MOD_X;
}

static void __wpadCertCalcModX(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSTime start = OSGetTime();

	int msbCertn = LINTMsb(certn);
	int msbBuf;

	ULONG buf[64 + 2];
	do
	{
		msbBuf = LINTMsb(p_wpd->certBufBig);

		if (msbBuf > msbCertn)
		{
			LINTLshift(buf, (ULONG *)certn, msbBuf - msbCertn - 1);

			if (LINTCmp(p_wpd->certBufBig, buf) >= 0)
				LINTSub(p_wpd->certBufBig, p_wpd->certBufBig, buf);
		}
		else
		{
			if (LINTCmp(p_wpd->certBufBig, certn) >= 0)
				LINTSub(p_wpd->certBufBig, p_wpd->certBufBig, certn);

			memcpy(p_wpd->certBuf0, p_wpd->certBufBig, sizeof p_wpd->certBuf0);

			p_wpd->certState = WPAD_STATE_CERT_CALC_MUL_Y;
		}
	} while (OSTicksToMicroseconds(OSDiffTick(OSGetTime(), start)) < 80);

	p_wpd->certWorkBusy = FALSE;
	p_wpd->certStateWorkMs = 0;
}

static void __wpadCertCalcMulY(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	LINTMul(p_wpd->certBufBig, p_wpd->certBuf1, p_wpd->certBuf1);

	p_wpd->certWorkBusy = FALSE;
	p_wpd->certStateWorkMs = 0;
	p_wpd->certState = WPAD_STATE_CERT_CALC_MOD_Y;
}

static void __wpadCertCalcModY(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	OSTime start = OSGetTime();

	int msbCertn = LINTMsb(certn);
	int msbBuf;

	ULONG buf[64 + 2];
	do
	{
		msbBuf = LINTMsb(p_wpd->certBufBig);

		if (msbBuf > msbCertn)
		{
			LINTLshift(buf, (ULONG *)certn, msbBuf - msbCertn - 1);

			if (LINTCmp(p_wpd->certBufBig, buf) >= 0)
				LINTSub(p_wpd->certBufBig, p_wpd->certBufBig, buf);
		}
		else
		{
			if (LINTCmp(p_wpd->certBufBig, certn) >= 0)
				LINTSub(p_wpd->certBufBig, p_wpd->certBufBig, certn);

			memcpy(p_wpd->certBuf1, p_wpd->certBufBig, sizeof p_wpd->certBuf1);

			p_wpd->certState = WPAD_STATE_CERT_CHECK;
		}
	} while (OSTicksToMicroseconds(OSDiffTick(OSGetTime(), start)) < 80);

	p_wpd->certWorkBusy = FALSE;
	p_wpd->certStateWorkMs = 0;
}

static void __wpadCertCheckResult(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	int result = LINTCmp(p_wpd->certBuf0, p_wpd->certBuf1);

	p_wpd->certWorkBusy = FALSE;
	p_wpd->certStateWorkMs = 0;
	p_wpd->certState = WPAD_STATE_CERT_SUCCESS;

	if (result == 0)
	{
		p_wpd->certValidityStatus = WPAD_CERT_VALID;
		p_wpd->certMayVerifyByCalibBlock = TRUE;
	}
	else
	{
		__wpadCertFailed(chan);
	}
}

static void __wpadCertChallengeCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->certWorkBusy = FALSE;

	if (result == WPAD_ESUCCESS)
	{
		p_wpd->certStateWorkMs =
			p_wpd->certChallengeRandomBit == 0 ? 1000 : 9000;
		p_wpd->certState = WPAD_STATE_CERT_PROBE_Y;
	}
	else if (p_wpd->certWorkCounter++)
	{
		p_wpd->certStateWorkMs = 0;
		__wpadCertFailed(chan);
	}
}

static void __wpadCertChallenge(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADiSendWriteDataCmd(&p_wpd->extCmdQueue, p_wpd->certChallengeRandomBit,
	                      WM_REG_EXTENSION_CERT_CHALLENGE,
	                      &__wpadCertChallengeCallback);
}

static void __wpadCertProbeReadyCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->certWorkBusy = FALSE;

	if (result == WPAD_ESUCCESS)
	{
		p_wpd->certStateWorkMs = 0;
		p_wpd->certWorkCounter++;

		if (p_wpd->certState == WPAD_STATE_CERT_PROBE_X)
		{
			/* NOTE: unnecessary check, because if x <= 4, then x also <= 12 and
			 * certWorkCounter is set to 0 anyways
			 */
			if (p_wpd->certProbeByte <= 4)
				p_wpd->certWorkCounter = 0;

			if (p_wpd->certProbeByte <= 12)
			{
				p_wpd->certStateWorkMs = 5500;
				p_wpd->certWorkCounter = 0;
			}

			if (p_wpd->certProbeByte == 14)
			{
				p_wpd->certState = WPAD_STATE_CERT_GET_X;
				p_wpd->certWorkCounter = 0;
			}
		}

		if (p_wpd->certState == WPAD_STATE_CERT_PROBE_Y)
		{
			if (p_wpd->certProbeByte == 26)
			{
				p_wpd->certState = WPAD_STATE_CERT_GET_Y;
				p_wpd->certWorkCounter = 0;
			}
		}
	}
	else
	{
		p_wpd->certStateWorkMs = 1000;
		p_wpd->certWorkCounter += 4;
	}

	if (p_wpd->certWorkCounter > 100)
		__wpadCertFailed(chan);
}

static void __wpadCertProbeReady(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	WPADiSendReadData(&p_wpd->extCmdQueue, &p_wpd->certProbeByte,
	                  sizeof p_wpd->certProbeByte, WM_REG_EXTENSION_CERT_PROBE,
	                  &__wpadCertProbeReadyCallback);
}

static void __wpadCertGetParamCallback(WPADChannel chan, WPADResult result)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	p_wpd->certWorkBusy = FALSE;

	u32 i;
	if (result == WPAD_ESUCCESS)
	{
		for (i = 0; i < p_wpd->wmReadLength / (int)sizeof(ULONG); i++)
		{
			// lwbrx op
			u32 wbr = p_wpd->wmReadDataBuf[i * 4 + 0] << 0
			        | p_wpd->wmReadDataBuf[i * 4 + 1] << 8
			        | p_wpd->wmReadDataBuf[i * 4 + 2] << 16
			        | p_wpd->wmReadDataBuf[i * 4 + 3] << 24;

			LINTNextElement(p_wpd->certParamPtr,
			                i + p_wpd->wmParamOffset / (int)sizeof(ULONG)) =
				wbr;
		}

		p_wpd->certWorkCounter = 0;

		p_wpd->wmParamOffset += p_wpd->wmReadLength;
		if (p_wpd->wmParamOffset < WM_EXTENSION_CERT_PARAM_SIZE)
		{
			p_wpd->certStateWorkMs = 0;
		}
		else
		{
			for (i = 0; i < WM_EXTENSION_CERT_PARAM_SIZE / (int)sizeof(ULONG);
			     i++)
			{
				if (LINTNextElement(p_wpd->certParamPtr, i))
					*p_wpd->certParamPtr = i + 1;
			}
		}
	}
	else
	{
		if (p_wpd->certWorkCounter++ < 1)
			p_wpd->certStateWorkMs = 0;
		else
			__wpadCertFailed(chan);
	}
}

static u8 __wpadCertGetParam(WPADChannel chan, ULONG *certParamOut)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->wmParamOffset < WM_EXTENSION_CERT_PARAM_SIZE)
	{
		p_wpd->certParamPtr = certParamOut;
		WPADiSendReadData(&p_wpd->extCmdQueue, p_wpd->wmReadDataBuf,
		                  sizeof p_wpd->wmReadDataBuf,
		                  WM_REG_EXTENSION_CERT_PARAM + p_wpd->wmParamOffset,
		                  &__wpadCertGetParamCallback);

		return FALSE;
	}
	else
	{
		p_wpd->certWorkBusy = FALSE;
		p_wpd->wmParamOffset = 0;

		return TRUE;
	}
}

static void __wpadCertGetParamX(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (!__wpadCertGetParam(chan, p_wpd->certBuf0))
		return;

	if (p_wpd->certBuf0[0] <= 1 && p_wpd->certBuf0[1] <= 1)
		goto fail;

	if (LINTCmp(p_wpd->certBuf0, certn) != -1)
		goto fail;

	p_wpd->certState = WPAD_STATE_CERT_VERIFY_X;
	p_wpd->certStateWorkMs = 500;

	return;

fail:
	__wpadCertFailed(chan);
}

static void __wpadCertVerifyParamX(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (!__wpadCertGetParam(chan, p_wpd->certBufBig))
		return;

	if (p_wpd->certBufBig[0] <= 1 && p_wpd->certBufBig[1] <= 1)
		goto fail;

	if (LINTCmp(p_wpd->certBufBig, certn) != -1)
		goto fail;

	if (LINTCmp(p_wpd->certBufBig, p_wpd->certBuf0) != 0)
		goto fail;

	memset(p_wpd->certBufBig, 0, sizeof p_wpd->certBufBig);
	p_wpd->certBufBig[0] = 1;
	p_wpd->certChallengeRandomBit = OSGetTick() % 2;
	p_wpd->certState = WPAD_STATE_CERT_CHALLENGE;
	p_wpd->certStateWorkMs = 0;

	return;

fail:
	__wpadCertFailed(chan);
}

static inline void __wpadCertGetParamY(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (!__wpadCertGetParam(chan, p_wpd->certBuf1))
		return;

	{ // block
		ULONG localCert[16 + 2];
		__memcpy(localCert, certn, sizeof localCert);

		localCert[1]--;

		if (p_wpd->certBuf1[0] <= 1 && p_wpd->certBuf1[1] <= 1)
			goto fail;

		// could be a ternary to be more concise
		if ((!p_wpd->certChallengeRandomBit
		     || LINTCmp(p_wpd->certBuf1, certn) != -1)
		    && (p_wpd->certChallengeRandomBit
		        || LINTCmp(p_wpd->certBuf1, localCert) != -1))
		{
			goto fail;
		}

		p_wpd->certStateWorkMs = 500;
		p_wpd->certState = WPAD_STATE_CERT_VERIFY_Y;
	}

	return;

fail:
	__wpadCertFailed(chan);
}

static void __wpadCertVerifyParamY(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (!__wpadCertGetParam(chan, p_wpd->certBufBig))
		return;

	{ // block
		ULONG localCert[16 + 2];
		__memcpy(localCert, certn, sizeof localCert);

		localCert[1]--;

		if (p_wpd->certBufBig[0] <= 1 && p_wpd->certBufBig[1] <= 1)
			goto fail;

		// same here
		if ((!p_wpd->certChallengeRandomBit
		     || LINTCmp(p_wpd->certBufBig, certn) != -1)
		    && (p_wpd->certChallengeRandomBit
		        || LINTCmp(p_wpd->certBufBig, localCert) != -1))
		{
			goto fail;
		}

		if (LINTCmp(p_wpd->certBufBig, p_wpd->certBuf1) != 0)
			goto fail;

		memset(p_wpd->certBufBig, 0, sizeof p_wpd->certBufBig);
		p_wpd->certBufBig[0] = 1;
		p_wpd->certState = WPAD_STATE_CERT_CALC_MUL_X;
		p_wpd->certStateWorkMs = 0;
	}

	return;

fail:
	__wpadCertFailed(chan);
}

static void __wpadCertWork(WPADChannel chan)
{
	wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

	if (p_wpd->certValidityStatus != WPAD_CERT_UNCHECKED)
		return;

	if (p_wpd->certState < 0)
		return;

	if (!p_wpd->wpInfo.attach)
		return;

	if (!p_wpd->certWorkBusy && p_wpd->certStateWorkMs-- < 0)
	{
		p_wpd->certWorkBusy = TRUE;

		switch (p_wpd->certState)
		{
		case WPAD_STATE_CERT_PROBE_X:
			__wpadCertProbeReady(chan);
			break;

		case WPAD_STATE_CERT_GET_X:
			__wpadCertGetParamX(chan);
			break;

		case WPAD_STATE_CERT_VERIFY_X:
			__wpadCertVerifyParamX(chan);
			break;

		case WPAD_STATE_CERT_CHALLENGE:
			__wpadCertChallenge(chan);
			break;

		case WPAD_STATE_CERT_PROBE_Y:
			__wpadCertProbeReady(chan);
			break;

		case WPAD_STATE_CERT_GET_Y:
			__wpadCertGetParamY(chan);
			break;

		case WPAD_STATE_CERT_VERIFY_Y:
			__wpadCertVerifyParamY(chan);
			break;

		case WPAD_STATE_CERT_CALC_MUL_X:
			__wpadCertCalcMulX(chan);
			break;

		case WPAD_STATE_CERT_CALC_MOD_X:
			__wpadCertCalcModX(chan);
			break;

		case WPAD_STATE_CERT_CALC_MUL_Y:
			__wpadCertCalcMulY(chan);
			break;

		case WPAD_STATE_CERT_CALC_MOD_Y:
			__wpadCertCalcModY(chan);
			break;

		case WPAD_STATE_CERT_CHECK:
			__wpadCertCheckResult(chan);
			break;
		}
	}

	if (p_wpd->certWorkMs++ > 60000)
	{
		p_wpd->certState = WPAD_STATE_CERT_ETIME;
		__wpadCertFailed(chan);
	}
}
