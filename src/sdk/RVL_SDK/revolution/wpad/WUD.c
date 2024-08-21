#include <revolution/WPAD/WUD.h>
#include "WUD.h"
#if 0

/* References:
 * Bluetooth Assigned Numbers
 * [1] https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Assigned_Numbers/out/en/Assigned_Numbers.pdf
 */

/*******************************************************************************
 * headers
 */

#include <string.h>

#include <macros.h>
#include <types.h>

#include "WUDHidHost.h" // WUDiHidHostEventCallback


#include <revolution/OS/OSContext.h> // OSSwitchFiberEx
#include <revolution/OS/OSError.h>
#include <revolution/OS/OSInterrupt.h>
#include <revolution/OS/OSTime.h>
#include <revolution/NAND.h>
#include <revolution/SC/scapi.h>
#include <revolution/SC/scapi_prdinfo.h>
#include <revolution/SC/scsystem.h>

#include "context_bte.h"

/*******************************************************************************
 * macros
 */

// misspellings
#define __wudPowerManageEventStackCallback	__wudPowerMangeEventStackCallback

// Wii Fit callback things
#define WII_FIT_TITLE_ID					"RFNJ"
#define RP_HEALTH_FILE_PATH					"/title/00010004/52464e4a/data/RPHealth.dat"

#define RP_HEALTH_FILE_OFFSET				0x4af18 // TODO: what is at this offset?
#define RP_HEALTH_FILE_WRITE_SIZE			((int)(128 + sizeof(u32))) // u32 crc;

// VSC opcodes
#define BT_VSC_NINTENDO_SUPER_PEEK_POKE		0xFC0A
#define BT_VSC_NINTENDO_WRITE_PATCH			0xFC4C
#define BT_VSC_NINTENDO_INSTALL_PATCH		0xFC4F

#define INSTALL_PATCH_SIZE					13
#define INSTALL_PATCH_TOTAL_SIZE(count_)	(INSTALL_PATCH_SIZE * (count_))
// highest value of x where INSTALL_PATCH_TOTAL_SIZE(x) <= 256
#define INSTALL_PATCH_MAX_NUM				19
#define INSTALL_PATCH_MAX_BUF				INSTALL_PATCH_TOTAL_SIZE(INSTALL_PATCH_MAX_NUM)

// ?
#if defined(NDEBUG)
# define DEV_HANDLE_BOUNDS_CHECK(val_)	((UINT8)(val_) <= WUD_MAX_DEV_ENTRY - 1)
#else
# define DEV_HANDLE_BOUNDS_CHECK(val_)	(0 <= (val_) && (val_) < WUD_MAX_DEV_ENTRY)
#endif // defined(NDEBUG)

/*******************************************************************************
 * types
 */

typedef WUDState WUDNandState;
enum WUDNandState_et
{
	WUD_STATE_NAND_OPEN			= 1,
	WUD_STATE_NAND_SEEK			= 2,
	WUD_STATE_NAND_READ			= 3,
	WUD_STATE_NAND_GET_DEV_INFO	= 4,
	WUD_STATE_NAND_CLOSE		= 5,
	WUD_STATE_NAND_DONE			= 6,
};

struct wud_patch_install_cmd_array
{
	u8		num;
	byte_t	installCmds[/* num */][INSTALL_PATCH_SIZE];
};

struct wud_discovery_response
{
	BD_ADDR				devAddr;		// size 0x06, offset 0x000
	char				at_0x006[64];	// size 0x40, offset 0x006
	byte_t				__pad0[0xba];
	tBTA_SERVICE_MASK	services;		// size 0x04, offset 0x100
	byte_t				__pad1[0x04]; // alignment?
}; // size 0x108

struct wud_nand_wbc_info
{
	SCBtDeviceInfo	scDevInfo;	// size 0x46, offset 0x00
	byte_t			__pad0[0x5a];
}; // size 0xa0

/*******************************************************************************
 * local function declarations
 */

// GKI callout functions
extern void *App_MEMalloc(size_t size);
extern int App_MEMfree(void *ptr);

// ---

static void __wudReverseAddr(BD_ADDR_PTR dst, BD_ADDR src);
static signed __wudSetPinCode(BD_ADDR dev_addr);
static void __wudClearDiscoverResult(void);
static BOOL __wudIsBusyLinkKeyCmd(void);
static BOOL __wudIsBusyScCmd(void);
static void __wudPrepareWBCDevInfo(BD_ADDR dev_addr, LINK_KEY link_key, void *);
static void __wudSyncFlushCallback(SCStatus result);
static WUDSyncState __wudSyncPrepareSearch(void);
static WUDSyncState __wudSyncWaitForStartSearch(void);
static WUDSyncState __wudSyncStartSearch(void);
static WUDSyncState __wudSyncWaitForSearchResult(void);
static WUDSyncState __wudSyncCheckSearchResult(void);
static WUDSyncState __wudSyncWaitForIncoming(void);
static WUDSyncState __wudSyncIsExistedDevice(void);
static WUDSyncState __wudSyncPrepareForExistedDevice(void);
static WUDSyncState __wudSyncPrepareForUnknownDevice(void);
static WUDSyncState __wudSyncTryConnect(void);
static WUDSyncState __wudSyncRegisterDevice(void);
static WUDSyncState __wudSyncVirginSimple(void);
static WUDSyncState __wudSyncVirginStandard(void);
static WUDSyncState __wudSyncChangeSmp2Std(void);
static WUDSyncState __wudSyncStoredLinkKeyToE2prom(void);
static WUDSyncState __wudSyncWaitForStoring(void);
static WUDSyncState __wudSyncStoredDevInfoToNand(void);
static void __wudOpenWiiFitCallback(NANDResult result,
                                    NANDCommandBlock *cmdBlock);
static void __wudOpenWiiFitFile(void);
static void __wudSeekWiiFitCallback(NANDResult result,
                                    NANDCommandBlock *cmdBlock);
static void __wudSeekWiiFitFile(void);
static void __wudUpdateWiiFitCallback(NANDResult result,
                                      NANDCommandBlock *cmdBlock);
static void __wudUpdateWiiFitFile(void);
static void __wudCloseWiiFitCallback(NANDResult result,
                                     NANDCommandBlock *cmdBlock);
static void __wudCloseWiiFit(void);
static void __wudSyncScFlush(void);
static WUDSyncState __wudSyncWaitForReading(void);
static WUDSyncState __wudSyncComplete(void);
static WUDSyncState __wudSyncError(void);
static WUDSyncState __wudSyncDone(void);
static void __wudSyncHandler(void);
static void __wudSyncHandler0(OSAlarm *alarm, OSContext *context);
static void __wudDeleteFlushCallback(SCStatus result);
static WUDDeleteState __wudDeleteDisallowIncoming(void);
static WUDDeleteState __wudDeleteDisconnectAll(void);
static WUDDeleteState __wudDeleteCleanupDatabase(void);
static void __wudDeleteCleanupSetting(void);
static WUDDeleteState __wudDeleteDone(void);
static void __wudDeleteHandler(void);
static void __wudDeleteHandler0(OSAlarm *alarm, OSContext *context);
static WUDStackState __wudStackGetStoredLinkKey(void);
static WUDStackState __wudStackCheckDeviceInfo(void);
static WUDStackState __wudStackDone(void);
static void __wudStackHandler(void);
static void __wudStackHandler0(OSAlarm *alarm, OSContext *context);
static void __wudInitFlushCallback(SCStatus result);
static WUDInitState __wudInitWaitForDeviceUp(void);
static WUDInitState __wudInitWaitForInitialization(void);
static BOOL __wudIsExistedDevice(BD_ADDR dev_addr);
static WUDInitState __wudInitDevInfo(void);
static WUDInitState __wudInitDone(void);
static void __wudNandResultCallback(NANDResult result, NANDCommandBlock *block);
static void __wudNandFlushCallback(SCStatus result);
static u32 __wudCalcWiiFitCrc1(void *data, u32 length);
static u32 __wudCalcWiiFitCrc2(void *data, u32 length, u32 crc);
static WUDInitState __wudGetDevInfoFromWiiFit(void);
static void __wudInitHandler(void);
static void __wudInitHandler0(OSAlarm *alarm, OSContext *context);
static void __wudShutdownFlushCallback(SCStatus result);
static void __wudShutdownStoreSetting(void);
static void __wudShutdownDone(void);
static void __wudShutdownHandler(void);
static void __wudShutdownHandler0(OSAlarm *alarm, OSContext *context);
static void __wudClearControlBlock(void);

static BOOL __wudStartSyncDevice(WUDSyncType syncType, s8 syncLopNum, u8 target,
                                 signed);
static BOOL __wudStartSyncStandard(signed);
static BOOL __wudStartSyncSimple(signed);

static BOOL __wudStopSyncDevice(void);

static void __wudModuleRebootCallback(void *p1);
static void __wudModuleReboot(void);
static void __wudInstallPatchCallback(tBTM_VSC_CMPL *p1);
static void __wudInstallPatch(void);
static void __wudWritePatchCallback(tBTM_VSC_CMPL *p1);
static void __wudWritePatch(void);
static void __wudRemovePatchCallback(tBTM_VSC_CMPL *p1);
static void __wudRemovePatch(void);
static void __wudSuperPeekPokeCallback(tBTM_VSC_CMPL *p1);
static void __wudSuperPeekPoke(void);
static void __wudAppendRuntimePatch(void);
static void __wudCheckFirmwareVersion(void);
static void __wudInitSub(void);
static void __wudEnableStack(void);
static void __wudProcSyncEvent(void);
static void __wudProcDeleteEvent(void);

static WUDDevInfo *__wudGetDevInfoByIndex(int index);
static WUDDevInfo *__wudGetNewStdDevInfo(void);
static WUDDevInfo *__wudGetNewSmpDevInfo(void);
static WUDDevInfo *__wudGetNewDevInfo(void);
static void __wudRemoveDevInfo(BD_ADDR dev_addr);
static void __wudClearDevInfos(void);
static u8 __wudGetStdDevNumber(void);
static u8 __wudGetSmpDevNumber(void);
static u8 __wudGetConnectionNumber(void);
static u8 __wudGetLinkNumber(void);

static WUDDevInfo *__wudGetOldestSmpDevice(void);
static WUDDevInfo *__wudGetOldestStdDevice(void);

static void __wudCleanupStackCallback(tBTA_STATUS status);
static void __wudSecurityEventStackCallback(tBTA_DM_SEC_EVT event,
                                            tBTA_DM_SEC *p_data);
static void __wudSearchEventStackCallback(tBTA_DM_SEARCH_EVT event,
                                          tBTA_DM_SEARCH *p_data);
static void __wudVendorSpecificEventStackCallback(UINT8 len, UINT8 *p);
static void __wudDeviceStatusEventStackCallback(tBTM_DEV_STATUS status);
static void __wudLinkKeyEventStackCallback(void *p1);
static void __wudPowerManageEventStackCallback(BD_ADDR p_bda,
                                               tBTM_PM_STATUS status,
                                               UINT16 value, UINT8 hci_status);
static void __wudResetAuthFailCount(void);
static WUDDevInfo *__wudGetWbcDevice(void);

/*******************************************************************************
 * variables
 */

// .data

/* comments are from throwing the array into
 * https://eleccelerator.com/usbdescreqparser
 * so shout out to that website thank you
 */
static byte_t _wudWiiRemoteDescriptor[] =
{
	0x05, 0x01,			//	Usage Page (Generic Desktop Ctrls)
	0x09, 0x05,			//	Usage (Game Pad)

	0xa1, 0x01,			//	Collection (Application)

	0x85, 0x10,			//		Report ID (16)
	0x15, 0x00,			//		Logical Minimum (0)
	0x26, 0xff, 0x00,	//		Logical Maximum (255)
	0x75, 0x08,			//		Report Size (8)
	0x95, 0x01,			//		Report Count (1)
	0x06, 0x00, 0xff,	//		Usage Page (Vendor Defined 0xFF00)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x11,			//		Report ID (17)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x12,			//		Report ID (18)
	0x95, 0x02,			//		Report Count (2)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x13,			//		Report ID (19)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x14,			//		Report ID (20)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x15,			//		Report ID (21)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x16,			//		Report ID (22)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x17,			//		Report ID (23)
	0x95, 0x06,			//		Report Count (6)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x18,			//		Report ID (24)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x19,			//		Report ID (25)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x1a,			//		Report ID (26)
	0x95, 0x01,			//		Report Count (1)
	0x09, 0x01,			//		Usage (0x01)
	0x91, 0x00,			//		Output (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0x85, 0x20,			//		Report ID (32)
	0x95, 0x06,			//		Report Count (6)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x21,			//		Report ID (33)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x22,			//		Report ID (34)
	0x95, 0x04,			//		Report Count (4)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x30,			//		Report ID (48)
	0x95, 0x02,			//		Report Count (2)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x31,			//		Report ID (49)
	0x95, 0x05,			//		Report Count (5)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x32,			//		Report ID (50)
	0x95, 0x0a,			//		Report Count (10)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x33,			//		Report ID (51)
	0x95, 0x11,			//		Report Count (17)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x34,			//		Report ID (52)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x35,			//		Report ID (53)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x36,			//		Report ID (54)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x37,			//		Report ID (55)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x3d,			//		Report ID (61)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x3e,			//		Report ID (62)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x85, 0x3f,			//		Report ID (63)
	0x95, 0x15,			//		Report Count (21)
	0x09, 0x01,			//		Usage (0x01)
	0x81, 0x00,			//		Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0xc0,				//	End Collection
};

static byte_t _wudSuperPeekPokeCmd[] =
{
	0x05, 0x00, 0x9a, 0x0e,
	0x00, 0x01, 0x00, 0x00,
	0x00
};

static byte_t _wudPatchData[] =
{
	0x70, 0x99, 0x08, 0x00,	// address (little-endian)
	0xb4, 0x00, 0x00, 0x00,	// size (little-endian)

	// data
	0x88, 0x43, 0xd1, 0x07,
	0x09, 0x0c, 0x08, 0x43,
	0xa0, 0x62, 0x19, 0x23,
	0xdb, 0x01, 0x33, 0x80,
	0x7c, 0xf7, 0x88, 0xf8,
	0x28, 0x76, 0x80, 0xf7,
	0x17, 0xff, 0x43, 0x78,
	0xeb, 0x70, 0x19, 0x23,
	0xdb, 0x01, 0x33, 0x87,
	0x7c, 0xf7, 0xbc, 0xfb,
	0x0b, 0x60, 0xa3, 0x7b,
	0x01, 0x49, 0x0b, 0x60,
	0x90, 0xf7, 0x96, 0xfb,
	0xd8, 0x1d, 0x08, 0x00,
	0x00, 0xf0, 0x04, 0xf8,
	0x00, 0x23, 0x79, 0xf7,
	0xe3, 0xfa, 0x00, 0x00,
	0x00, 0xb5, 0x00, 0x23,
	0x11, 0x49, 0x0b, 0x60,
	0x1d, 0x21, 0xc9, 0x03,
	0x0b, 0x60, 0x7d, 0x20,
	0x80, 0x01, 0x01, 0x38,
	0xfd, 0xd1, 0x0e, 0x4b,
	0x0e, 0x4a, 0x13, 0x60,
	0x47, 0x20, 0x00, 0x21,
	0x96, 0xf7, 0x96, 0xff,
	0x46, 0x20, 0x00, 0x21,
	0x96, 0xf7, 0x92, 0xff,
	0x0a, 0x4a, 0x13, 0x68,
	0x0a, 0x48, 0x03, 0x40,
	0x13, 0x60, 0x0a, 0x4a,
	0x13, 0x68, 0x0a, 0x48,
	0x03, 0x40, 0x13, 0x60,
	0x09, 0x4a, 0x13, 0x68,
	0x09, 0x48, 0x03, 0x40,
	0x13, 0x60, 0x00, 0xbd,
	0x24, 0x80, 0x0e, 0x00,
	0x81, 0x03, 0x0f, 0xfe,
	0x5c, 0x00, 0x0f, 0x00,
	0x60, 0xfc, 0x0e, 0x00,
	0xfe, 0xff, 0x00, 0x00,
	0xfc, 0xfc, 0x0e, 0x00,
	0xff, 0x9f, 0x00, 0x00,
	0x30, 0xfc, 0x0e, 0x00,
	0x7f, 0xff, 0x00, 0x00
};

static struct wud_patch_install_cmd_array _wudPatchInstallCmd =
{
	7,

	{
		{0x20, 0xbc, 0x65, 0x01, 0x00, 0x84, 0x42, 0x09, 0xd2, 0x84, 0x42, 0x09, 0xd1},
		{0x21, 0x84, 0x5a, 0x00, 0x00, 0x83, 0xf0, 0x74, 0xff, 0x09, 0x0c, 0x08, 0x43},
		{0x22, 0x00, 0x61, 0x00, 0x00, 0x83, 0xf0, 0x40, 0xfc, 0x00, 0x00, 0x00, 0x00},
		{0x23, 0xcc, 0x9f, 0x01, 0x00, 0x6f, 0xf0, 0xe4, 0xfc, 0x03, 0x28, 0x7d, 0xd1},
		{0x24, 0x3c, 0x62, 0x01, 0x00, 0x28, 0x20, 0x00, 0xe0, 0x60, 0x8d, 0x23, 0x68},
		{0x25, 0x04, 0x12, 0x01, 0x00, 0x20, 0x1c, 0x20, 0x1c, 0x24, 0xe0, 0xb0, 0x21},
		{0x26, 0x74, 0x2f, 0x00, 0x00, 0x86, 0xf0, 0x18, 0xfd, 0x21, 0x4f, 0x3b, 0x60}
	}
};

static byte_t _wudResetAuthCountCmd[] =
{
	0x30, 0x36, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

// .bss
wud_cb_st __rvl_wudcb;
static WUDDevInfo _wudDiscWork;
static struct wud_discovery_response _wudDiscResp;
static struct wud_nand_wbc_info _wudNandWbcInfo __attribute__((aligned(0x20)));
static SCBtDeviceInfoArray _scArray;
static NANDFileInfo _wudNandFileInfo;
static NANDCommandBlock _wudNandBlock;
static byte_t _wudHandlerStack[0x1000] __attribute__((aligned(0x20)));
static SCBtCmpDevInfoArray _spArray;
static BD_ADDR_PTR _dev_handle_to_bda[WUD_MAX_DEV_ENTRY];
static u16 _dev_handle_queue_size[WUD_MAX_DEV_ENTRY];
static u16 _dev_handle_notack_num[WUD_MAX_DEV_ENTRY];

// .sbss
static u8 _wudDiscNumResps;
static s8 _wudDiscRssi;
static u8 _wudTarget;
static u8 _scFlush;
static u32 _wudPatchSize;
static s32 _wudPatchOffset;
static u32 _wudPatchAddress;
static u8 _wudPatchNum;
static u8 _wudInstallNum;
static u8 _wudNandLocked;
static signed _wudNandPhase;
static u32 _wudNandWbcCrc;
__attribute__((weak)) BOOL _linkedWBC;
__attribute__((weak)) void (*_initWBC)(void);
static byte_t *_wudNandBufPtr;
static u8 __bte_trace_level;
static byte_t _wudPatchRemoveCmd;
static BOOL _wudAbortSync;
static BOOL _wudReadNand;
static BOOL _wudInitialized;

/*******************************************************************************
 * functions
 */

BOOL WUDIsLinkedWBC(void)
{
	return _linkedWBC;
}

extern void *App_MEMalloc(size_t size)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	void *buf = (*p_wcb->allocFunc)(size);

	return buf;
}

extern int App_MEMfree(void *ptr)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	int ret = (*p_wcb->freeFunc)(ptr);

	return ret;
}

static void __wudReverseAddr(BD_ADDR_PTR dst, BD_ADDR src)
{
	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < BD_ADDR_LEN; i++)
		dst[i] = src[(BD_ADDR_LEN - 1) - i];

	OSRestoreInterrupts(intrStatus);
}

static signed __wudSetPinCode(BD_ADDR dev_addr)
{
	BD_ADDR_PTR myAddr = __rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD
	                       ? __rvl_wudcb.hostAddr
	                       : dev_addr;

	if (_wudDiscWork.at_0x5b == 4)
	{
		WUDiRemoveDevice(_wudDiscWork.devAddr);
		btm_remove_acl(_wudDiscWork.devAddr);
	}

	_wudDiscWork.at_0x5a = 1;

	BD_ADDR pin;
	__wudReverseAddr(pin, myAddr);

	BTA_DmPinReply(dev_addr, TRUE, BD_ADDR_LEN, pin);

	return 0;
}

static void __wudClearDiscoverResult(void)
{
	_wudDiscNumResps = 0;
	memset(&_wudDiscResp, 0, sizeof _wudDiscResp);
}

static BOOL __wudIsBusyLinkKeyCmd(void)
{
	return __rvl_wudcb.linkKeyState != WUD_STATE_START ? 1 : 0;
}

static BOOL __wudIsBusyScCmd(void)
{
	return SCCheckStatus() == SC_STATUS_BUSY ? 1 : 0;
}

static void __wudPrepareWBCDevInfo(BD_ADDR dev_addr, LINK_KEY link_key,
                                   void *param_3)
{
	u8 offset = 0;

	if (dev_addr)
		memcpy((void *)((u32)&_wudNandWbcInfo + offset), dev_addr, BD_ADDR_LEN);

	offset += BD_ADDR_LEN;

	if (link_key)
	{
		memcpy((void *)((u32)&_wudNandWbcInfo + offset), link_key,
		       LINK_KEY_LEN);
	}

	offset += LINK_KEY_LEN;

	if (param_3)
		memcpy((void *)((u32)&_wudNandWbcInfo + offset), param_3, 64);

	offset += 64;

	u32 crc = __wudCalcWiiFitCrc2(&_wudNandWbcInfo, 128, _wudNandWbcCrc);
	memcpy((void *)((u32)&_wudNandWbcInfo + 128), &crc, sizeof crc);
}

static void __wudSyncFlushCallback(SCStatus result)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (p_wcb->syncState == WUD_STATE_START)
		return;

	if (result == SC_STATUS_READY)
		p_wcb->syncState = WUD_STATE_SYNC_COMPLETE;
	else
		p_wcb->syncState = WUD_STATE_ERROR;
}

static WUDSyncState __wudSyncPrepareSearch(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDSetVisibility(FALSE, FALSE);

	if (!p_wcb->syncLoopNum)
		return WUD_STATE_SYNC_DONE;

	if (__wudGetLinkNumber() == WUD_MAX_CHANNELS
	    && __wudGetConnectionNumber() == WUD_MAX_CHANNELS)
	{
		return WUD_STATE_SYNC_DONE;
	}

	int i;
	WUDDevInfo *p_info;
	if (p_wcb->syncSkipChecks)
	{
		for (i = 0; i < WUD_MAX_DEV_ENTRY; i++)
		{
			p_info = __wudGetDevInfoByIndex(i);
			if (p_info->at_0x59 == 9)
			{
				WUDSetSniffMode(p_info->devAddr, 0);
				return WUD_STATE_SYNC_PREPARE_SEARCH;
			}
		}
	}

	if (p_wcb->syncLoopNum > 0)
		p_wcb->syncLoopNum--;

	p_wcb->waitStartSearchFrames = 50;

	return WUD_STATE_SYNC_WAIT_FOR_START_SEARCH;
}

static WUDSyncState __wudSyncWaitForStartSearch(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (!p_wcb->syncLoopNum)
		return WUD_STATE_SYNC_DONE;

	if (__wudGetLinkNumber() == WUD_MAX_CHANNELS
	    && __wudGetConnectionNumber() == WUD_MAX_CHANNELS)
	{
		return WUD_STATE_SYNC_DONE;
	}

	if (--p_wcb->waitStartSearchFrames < 0)
		return WUD_STATE_SYNC_START_SEARCH;
	else
		return WUD_STATE_SYNC_WAIT_FOR_START_SEARCH;
}

static WUDSyncState __wudSyncStartSearch(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	tBTA_DM_INQ dm_inq;
	dm_inq.mode = BTM_LIMITED_INQUIRY;
	dm_inq.max_resps = 1;
	dm_inq.report_dup = FALSE;

	if (p_wcb->syncSkipChecks)
	{
		dm_inq.duration = 5 - 2;
	}
	else if (p_wcb->syncType == WUD_SYNC_TYPE_STANDARD)
	{
		dm_inq.duration = __wudGetLinkNumber() == 3 ? 10 : 5;

		dm_inq.duration -= p_wcb->syncLoopNum;
	}
	else
	{
		dm_inq.duration = __wudGetLinkNumber() == 3 ? 10 - 2 : 5 - 2;
	}

	__wudClearDiscoverResult();
	BTA_DmSearch(&dm_inq, 0, &__wudSearchEventStackCallback);

	return WUD_STATE_SYNC_WAIT_FOR_SEARCH_RESULT;
}

static WUDSyncState __wudSyncWaitForSearchResult(void)
{
	if (__wudGetLinkNumber() == WUD_MAX_CHANNELS
	    && __wudGetConnectionNumber() == WUD_MAX_CHANNELS)
	{
		BTA_DmSearchCancel();
		return WUD_STATE_SYNC_26;
	}

	return WUD_STATE_SYNC_WAIT_FOR_SEARCH_RESULT;
}

static WUDSyncState __wudSyncCheckSearchResult(void)
{
	WUDSyncState nextState = WUD_STATE_SYNC_PREPARE_SEARCH;

	if (_wudDiscNumResps > 0)
	{
		if (WUD_DEV_NAME_IS_CNT(_wudDiscResp.at_0x006))
			nextState = WUD_STATE_SYNC_IS_EXISTED_DEVICE;

		if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(_wudDiscResp.at_0x006))
			nextState = WUD_STATE_SYNC_IS_EXISTED_DEVICE;

		if (_wudDiscRssi < __rvl_wudcb.syncRssi)
			nextState = WUD_STATE_SYNC_PREPARE_SEARCH;
	}

	if (__rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD
	    && nextState == WUD_STATE_SYNC_PREPARE_SEARCH)
	{
		nextState = WUD_STATE_SYNC_WAIT_FOR_INCOMING;

		__rvl_wudcb.waitIncomingFrames = __wudGetLinkNumber() == 3 ? 200 : 100;

		WUDSetVisibility(FALSE, TRUE);
	}

	return nextState;
}

static WUDSyncState __wudSyncWaitForIncoming(void)
{
	WUDSyncState nextState = WUD_STATE_SYNC_WAIT_FOR_INCOMING;

	if (__wudGetLinkNumber() == WUD_MAX_CHANNELS
	    && __wudGetConnectionNumber() == WUD_MAX_CHANNELS)
	{
		nextState = WUD_STATE_SYNC_DONE;
	}

	if (--__rvl_wudcb.waitIncomingFrames < 0)
		nextState = WUD_STATE_SYNC_PREPARE_SEARCH;

	return nextState;
}

static WUDSyncState __wudSyncIsExistedDevice(void)
{
	WUDDevInfo *ptr;
	WUDSyncState nextState = WUD_STATE_SYNC_PREPARE_FOR_UNKNOWN_DEVICE;

	ptr = WUDiGetDevInfo(_wudDiscResp.devAddr);
	if (ptr)
	{
		memcpy(&_wudDiscWork, ptr, sizeof _wudDiscWork);

		nextState = WUD_STATE_SYNC_PREPARE_FOR_EXISTED_DEVICE;
	}

	return nextState;
}

static WUDSyncState __wudSyncPrepareForExistedDevice(void)
{
	WUDDevInfo *p_work = &_wudDiscWork;

	p_work->at_0x59 = 1;

	switch (p_work->at_0x5b)
	{
	case 0:
	case 2:
	case 4:
	case 5:
		if (__rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD)
		{
			WUDiMoveBottomStdDevInfoPtr(p_work);
			WUDiRemoveDevice(p_work->devAddr);
			return WUD_STATE_SYNC_PREPARE_FOR_UNKNOWN_DEVICE;
		}
		else
		{
			p_work->at_0x5b = 4;
		}

		break;

	case 1:
	case 3:
		WUDiMoveBottomSmpDevInfoPtr(p_work);
		WUDiRemoveDevice(__rvl_wudcb.smpListTail->devInfo->devAddr);
		return WUD_STATE_SYNC_PREPARE_FOR_UNKNOWN_DEVICE;
	}

	return WUD_STATE_SYNC_TRY_CONNECT;
}

static WUDSyncState __wudSyncPrepareForUnknownDevice(void)
{
	WUDDevInfo *p_work = &_wudDiscWork;

	p_work->at_0x59 = 1;
	p_work->at_0x5b = __rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD ? 0 : 1;

	WUD_BDCPY(p_work->devAddr, _wudDiscResp.devAddr);
	memcpy(p_work, _wudDiscResp.at_0x006, 64);
	memset(p_work->linkKey, 0, LINK_KEY_LEN);

	return WUD_STATE_SYNC_TRY_CONNECT;
}

static WUDSyncState __wudSyncTryConnect(void)
{
	WUDSyncState nextState = WUD_STATE_ERROR;

	if (WUD_DEV_NAME_IS_CNT(_wudDiscResp.at_0x006))
	{
		_wudDiscWork.at_0x59 = 2;
		BTA_HhOpen(_wudDiscWork.devAddr, BTA_HH_PROTO_RPT_MODE,
		           BTA_SEC_AUTHENTICATE);

		nextState = WUD_STATE_SYNC_6;
	}

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(_wudDiscResp.at_0x006))
	{
		WUDDevInfo *wbcInfo = __wudGetWbcDevice();
		if (wbcInfo)
		{
			if (wbcInfo->at_0x59 > 1)
				return nextState;

			if (WUD_BDCMP(_wudDiscResp.devAddr, wbcInfo->devAddr) != 0)
			{
				WUDiMoveBottomStdDevInfoPtr(wbcInfo);
				WUDiRemoveDevice(wbcInfo->devAddr);
			}
		}

		_wudDiscWork.at_0x59 = 2;
		BTA_HhOpen(_wudDiscWork.devAddr, BTA_HH_PROTO_RPT_MODE,
		           BTA_SEC_AUTHENTICATE);
		nextState = WUD_STATE_SYNC_6;
	}

	return nextState;
}

static WUDSyncState __wudSyncRegisterDevice(void)
{
	WUDSyncState nextState;

	switch (_wudDiscWork.at_0x5b)
	{
	case 1:
		nextState = WUD_STATE_SYNC_VIRGIN_SIMPLE;
		break;

	case 0:
		nextState = WUD_STATE_SYNC_VIRGIN_STANDARD;
		break;

	case 5:
		nextState = WUD_STATE_SYNC_CHANGE_SIMPLE_TO_STANDARD;
		break;

	case 3:
		nextState = WUD_STATE_SYNC_COMPLETE;
		break;

	case 4:
		nextState = WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM;
		break;

	case 2:
		nextState = WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM;
		break;
	}

	/* ERRATA: nextState is undefined when 0 <= _wudDiscWork.at_0x5b <= 5
	 * does not hold
	 */
	return nextState;
}

static WUDSyncState __wudSyncVirginSimple(void)
{
	WUDDevInfo *p_info;

	if (__wudGetSmpDevNumber() == WUD_MAX_DEV_ENTRY_FOR_SMP)
	{
		p_info = __wudGetOldestSmpDevice();
		WUDiRemoveDevice(p_info->devAddr);
	}

	p_info = __wudGetNewDevInfo();

	if (!p_info)
		return WUD_STATE_ERROR;

	if (p_info->at_0x59 != 0)
		return WUD_STATE_ERROR;

	memcpy(p_info, &_wudDiscWork, sizeof *p_info);
	WUDiRegisterDevice(p_info->devAddr);
	WUDiMoveTopSmpDevInfoPtr(p_info);

	WUDiSetDevAddrForHandle(p_info->devHandle, p_info->devAddr);

	return WUD_STATE_SYNC_COMPLETE;
}

static WUDSyncState __wudSyncVirginStandard(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_CNT(_wudDiscWork.small.devName))
	{
		p_info = __wudGetWbcDevice();

		if (p_info && __wudGetStdDevNumber() == WUD_MAX_DEV_ENTRY_FOR_STD)
		{
			p_info = p_wcb->stdListTail->prev->devInfo;
			WUDiMoveBottomStdDevInfoPtr(p_info);
			WUDiRemoveDevice(p_info->devAddr);
		}
	}

	if (__wudGetStdDevNumber() == WUD_MAX_DEV_ENTRY_FOR_STD)
	{
		p_info = __wudGetOldestStdDevice();
		WUDiRemoveDevice(p_info->devAddr);
	}

	p_info = __wudGetNewDevInfo();

	if (!p_info)
		return WUD_STATE_ERROR;

	if (p_info->at_0x59 != 0)
		return WUD_STATE_ERROR;

	memcpy(p_info, &_wudDiscWork, sizeof *p_info);
	WUDiRegisterDevice(p_info->devAddr);
	WUDiMoveTopStdDevInfoPtr(p_info);

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(p_info->small.devName))
	{
		WUDiMoveTopOfUnusedStdDevice(p_info);

		memset(&_scArray.wbc, 0, sizeof _scArray.wbc);
		WUD_BDCPY(&_scArray.wbc.devAddr, p_info->devAddr);
		memcpy(&_scArray.wbc.small, p_info, sizeof _scArray.wbc.small);

		// Wait what
		memcpy(&_scArray.wbc.small.at_0x14, p_info->linkKey, LINK_KEY_LEN);
		__wudPrepareWBCDevInfo(p_info->devAddr, p_info->linkKey, p_info);
	}

	WUDiSetDevAddrForHandle(p_info->devHandle, p_info->devAddr);

	return WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM;
}

static WUDSyncState __wudSyncChangeSmp2Std(void)
{
	WUDiMoveBottomSmpDevInfoPtr(&_wudDiscWork);
	WUDiRemoveDevice(__rvl_wudcb.smpListTail->devInfo->devAddr);
	return __wudSyncVirginStandard();
}

static WUDSyncState __wudSyncStoredLinkKeyToE2prom(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (__wudIsBusyLinkKeyCmd())
		return WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM;

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(_wudDiscWork.small.devName))
		return WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND;

	WUDDevInfo *p_info = WUDiGetDevInfo(_wudDiscWork.devAddr);
	OSAssert_Line(1494, p_info != NULL);

	p_wcb->linkKeyState = WUD_STATE_LINK_KEY_WRITING;
	BTM_WriteStoredLinkKey(1, &p_info->devAddr, &p_info->linkKey,
	                       &__wudLinkKeyEventStackCallback);

	return WUD_STATE_SYNC_WAIT_FOR_STORING;
}

static WUDSyncState __wudSyncWaitForStoring(void)
{
	return !__wudIsBusyLinkKeyCmd() ? WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND
	                                : WUD_STATE_SYNC_WAIT_FOR_STORING;
}

static WUDSyncState __wudSyncStoredDevInfoToNand(void)
{
	struct WUDDevInfoList *infoList;
	u8 i;
	WUDSyncState nextState = WUD_STATE_SYNC_COMPLETE;

	if (__wudIsBusyScCmd())
		return WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND;

	memset(&_scArray.devices, 0,
	       sizeof _scArray.devices[i] * WUD_MAX_DEV_ENTRY_FOR_STD);
	_scArray.num = __wudGetStdDevNumber();

	infoList = __rvl_wudcb.stdListHead;
	i = 0;
	while (infoList)
	{
		WUD_BDCPY(_scArray.devices[i].devAddr, infoList->devInfo->devAddr);
		memcpy(&_scArray.devices[i].small, infoList->devInfo->small.devName,
		       sizeof _scArray.devices[i].small);

		i++;
		infoList = infoList->next;
	}

	BOOL scSuccess = SCSetBtDeviceInfoArray(&_scArray);
	if (!scSuccess)
		return WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND;

// What
#if defined(NDEBUG)
# define RETURN_VAR	i
#else
# define RETURN_VAR	nextState
#endif // defined(NDEBUG)

	RETURN_VAR = WUD_STATE_SYNC_SC_FLUSH;

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(_wudDiscWork.small.devName)
	    && SCGetProductGameRegion() == SC_PRD_GAME_REG_JP)
	{
		RETURN_VAR = WUD_STATE_WII_FIT_OPEN;
	}

	return RETURN_VAR;
}

static void __wudOpenWiiFitCallback(NANDResult result,
                                    NANDCommandBlock *cmdBlock
                                    __attribute__((unused)))
{
	if (__rvl_wudcb.syncState != WUD_STATE_START)
	{
		__rvl_wudcb.syncState = result == NAND_ESUCCESS
		                          ? WUD_STATE_WII_FIT_SEEK
		                          : WUD_STATE_SYNC_SC_FLUSH;
	}

	if (__rvl_wudcb.deleteState != WUD_STATE_START)
	{
		__rvl_wudcb.deleteState = result == NAND_ESUCCESS
		                            ? WUD_STATE_WII_FIT_SEEK
		                            : WUD_STATE_DELETE_CLEANUP_SETTING;
	}

	_wudNandLocked = FALSE;
}

static void __wudOpenWiiFitFile(void)
{
	const char *rpHealthFilePath = RP_HEALTH_FILE_PATH;

	if (_wudNandLocked)
		return;

	_wudNandLocked = TRUE;
	NANDOpenAsync(rpHealthFilePath, &_wudNandFileInfo, NAND_OPEN_WRITE,
	              &__wudOpenWiiFitCallback, &_wudNandBlock);
}

static void __wudSeekWiiFitCallback(NANDResult result,
                                    NANDCommandBlock *cmdBlock
                                    __attribute__((unused)))
{
	if (__rvl_wudcb.syncState != WUD_STATE_START)
	{
		__rvl_wudcb.syncState = result == RP_HEALTH_FILE_OFFSET
		                          ? WUD_STATE_WII_FIT_UPDATE
		                          : WUD_STATE_SYNC_SC_FLUSH;
	}

	if (__rvl_wudcb.deleteState != WUD_STATE_START)
	{
		__rvl_wudcb.deleteState = result == RP_HEALTH_FILE_OFFSET
		                            ? WUD_STATE_WII_FIT_UPDATE
		                            : WUD_STATE_DELETE_CLEANUP_SETTING;
	}

	_wudNandLocked = FALSE;
}

static void __wudSeekWiiFitFile(void)
{
	if (_wudNandLocked)
		return;

	_wudNandLocked = TRUE;
	NANDSeekAsync(&_wudNandFileInfo, RP_HEALTH_FILE_OFFSET, NAND_SEEK_SET,
	              &__wudSeekWiiFitCallback, &_wudNandBlock);
}

static void __wudUpdateWiiFitCallback(NANDResult result,
                                      NANDCommandBlock *cmdBlock
                                      __attribute__((unused)))
{
	if (__rvl_wudcb.syncState != WUD_STATE_START)
	{
		__rvl_wudcb.syncState = result == RP_HEALTH_FILE_WRITE_SIZE
		                          ? WUD_STATE_WII_FIT_CLOSE
		                          : WUD_STATE_SYNC_SC_FLUSH;
	}

	if (__rvl_wudcb.deleteState != WUD_STATE_START)
	{
		__rvl_wudcb.deleteState = result == RP_HEALTH_FILE_WRITE_SIZE
		                            ? WUD_STATE_WII_FIT_CLOSE
		                            : WUD_STATE_DELETE_CLEANUP_SETTING;
	}

	_wudNandLocked = FALSE;
}

static void __wudUpdateWiiFitFile(void)
{
	if (_wudNandLocked)
		return;

	_wudNandLocked = TRUE;
	NANDWriteAsync(&_wudNandFileInfo, &_wudNandWbcInfo,
	               RP_HEALTH_FILE_WRITE_SIZE, &__wudUpdateWiiFitCallback,
	               &_wudNandBlock);
}

static void __wudCloseWiiFitCallback(NANDResult result __attribute__((unused)),
                                     NANDCommandBlock *cmdBlock
                                     __attribute__((unused)))
{
	if (__rvl_wudcb.syncState != WUD_STATE_START)
		__rvl_wudcb.syncState = WUD_STATE_SYNC_SC_FLUSH;

	if (__rvl_wudcb.deleteState != WUD_STATE_START)
		__rvl_wudcb.deleteState = WUD_STATE_DELETE_CLEANUP_SETTING;

	_wudNandLocked = FALSE;
}

static void __wudCloseWiiFit(void)
{
	if (_wudNandLocked)
		return;

	_wudNandLocked = TRUE;
	NANDCloseAsync(&_wudNandFileInfo, &__wudCloseWiiFitCallback,
	               &_wudNandBlock);
}

static void __wudSyncScFlush(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	p_wcb->syncState = WUD_STATE_SYNC_13;

	OSRestoreInterrupts(intrStatus);

	SCFlushAsync(&__wudSyncFlushCallback);
}

static WUDSyncState __wudSyncWaitForReading(void)
{
	WUDSyncState nextState = WUD_STATE_SYNC_WAIT_FOR_READING;

	if (!__wudIsBusyLinkKeyCmd())
	{
		nextState = WUD_STATE_SYNC_VIRGIN_STANDARD;
		WUDiRemoveDevice(__rvl_wudcb.pairAddr);
	}

	return nextState;
}

static WUDSyncState __wudSyncComplete(void)
{
	__rvl_wudcb.syncedNum++;

	memset(&_wudDiscWork, 0, sizeof _wudDiscWork);
	return __rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD
	         ? WUD_STATE_SYNC_DONE
	         : WUD_STATE_SYNC_PREPARE_SEARCH;
}

static WUDSyncState __wudSyncError(void)
{
	memset(&_wudDiscWork, 0, sizeof _wudDiscWork);
	return __rvl_wudcb.syncType == WUD_SYNC_TYPE_STANDARD
	         ? WUD_STATE_SYNC_DONE
	         : WUD_STATE_SYNC_PREPARE_SEARCH;
}

static WUDSyncState __wudSyncDone(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDDevInfo *p_info;
	int i;
	if (p_wcb->syncSkipChecks)
	{
		for (i = 0; i < WUD_MAX_DEV_ENTRY; i++)
		{
			p_info = __wudGetDevInfoByIndex(i);
			if (p_info->at_0x59 == 8)
			{
				WUDSetSniffMode(p_info->devAddr, 8);
				return WUD_STATE_SYNC_DONE;
			}
		}
	}

	OSCancelAlarm(&p_wcb->alarm);

	if (!_wudAbortSync)
		WUDSetVisibility(FALSE, TRUE);

	WUDSyncDeviceCallback *syncCB = p_wcb->syncType == WUD_SYNC_TYPE_STANDARD
	                                  ? p_wcb->syncStdCB
	                                  : p_wcb->syncSmpCB;

	if (syncCB)
		(*syncCB)(1, p_wcb->syncedNum);

	return WUD_STATE_START;
}

static void __wudSyncHandler(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	switch (p_wcb->syncState)
	{
	case WUD_STATE_SYNC_PREPARE_SEARCH:
		p_wcb->syncState = __wudSyncPrepareSearch();
		break;

	case WUD_STATE_SYNC_WAIT_FOR_START_SEARCH:
		p_wcb->syncState = __wudSyncWaitForStartSearch();
		break;

	case WUD_STATE_SYNC_START_SEARCH:
		p_wcb->syncState = __wudSyncStartSearch();
		break;

	case WUD_STATE_SYNC_CHECK_SEARCH_RESULT:
		p_wcb->syncState = __wudSyncCheckSearchResult();
		break;

	case WUD_STATE_SYNC_IS_EXISTED_DEVICE:
		p_wcb->syncState = __wudSyncIsExistedDevice();
		break;

	case WUD_STATE_SYNC_PREPARE_FOR_EXISTED_DEVICE:
		p_wcb->syncState = __wudSyncPrepareForExistedDevice();
		break;

	case WUD_STATE_SYNC_PREPARE_FOR_UNKNOWN_DEVICE:
		p_wcb->syncState = __wudSyncPrepareForUnknownDevice();
		break;

	case WUD_STATE_SYNC_TRY_CONNECT:
		p_wcb->syncState = __wudSyncTryConnect();
		break;

	case WUD_STATE_SYNC_REGISTER_DEVICE:
		p_wcb->syncState = __wudSyncRegisterDevice();
		break;

	case WUD_STATE_SYNC_VIRGIN_SIMPLE:
		p_wcb->syncState = __wudSyncVirginSimple();
		break;

	case WUD_STATE_SYNC_VIRGIN_STANDARD:
		p_wcb->syncState = __wudSyncVirginStandard();
		break;

	case WUD_STATE_SYNC_CHANGE_SIMPLE_TO_STANDARD:
		p_wcb->syncState = __wudSyncChangeSmp2Std();
		break;

	case WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM:
		p_wcb->syncState = __wudSyncStoredLinkKeyToE2prom();
		break;

	case WUD_STATE_SYNC_WAIT_FOR_STORING:
		p_wcb->syncState = __wudSyncWaitForStoring();
		break;

	case WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND:
		p_wcb->syncState = __wudSyncStoredDevInfoToNand();
		break;

	case WUD_STATE_SYNC_SC_FLUSH:
		__wudSyncScFlush();
		break;

	case WUD_STATE_SYNC_WAIT_FOR_READING:
		p_wcb->syncState = __wudSyncWaitForReading();
		break;

	case WUD_STATE_SYNC_COMPLETE:
		p_wcb->syncState = __wudSyncComplete();
		break;

	case WUD_STATE_ERROR:
		p_wcb->syncState = __wudSyncError();
		break;

	case WUD_STATE_SYNC_DONE:
		p_wcb->syncState = __wudSyncDone();
		break;

	case WUD_STATE_SYNC_WAIT_FOR_SEARCH_RESULT:
		p_wcb->syncState = __wudSyncWaitForSearchResult();
		break;

	case WUD_STATE_SYNC_WAIT_FOR_INCOMING:
		p_wcb->syncState = __wudSyncWaitForIncoming();
		break;

	// Wii Fit states

	case WUD_STATE_WII_FIT_OPEN:
		__wudOpenWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_SEEK:
		__wudSeekWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_UPDATE:
		__wudUpdateWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_CLOSE:
		__wudCloseWiiFit();
		break;

	// Actionless states (?)

	case WUD_STATE_SYNC_11:
	case WUD_STATE_SYNC_12:
	case WUD_STATE_SYNC_26:
		break;
	}
}

static void __wudSyncHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx((register_t)alarm, (register_t)context, 0, 0,
	                &__wudSyncHandler,
	                &_wudHandlerStack[sizeof _wudHandlerStack]);
}

static void __wudDeleteFlushCallback(SCStatus result)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (p_wcb->deleteState != WUD_STATE_START)
	{
		// ?
		if (result == SC_STATUS_READY)
			p_wcb->deleteState = WUD_STATE_DELETE_DONE;
		else
			p_wcb->deleteState = WUD_STATE_DELETE_DONE;
	}
}

static WUDDeleteState __wudDeleteDisallowIncoming(void)
{
	// see notes about this prototype
	BTA_DmSetVisibility(FALSE, FALSE);

	return WUD_STATE_DELETE_DISCONNECT_ALL;
}

static WUDDeleteState __wudDeleteDisconnectAll(void)
{
	int i;

	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		p_info = &p_wcb->stdDevs[i];
		if (p_info->at_0x59 > 1)
			btm_remove_acl(p_info->devAddr);
	}

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		p_info = &p_wcb->smpDevs[i];
		if (p_info->at_0x59 > 1)
			btm_remove_acl(p_info->devAddr);
	}

	return WUD_STATE_DELETE_CLEANUP_DATABASE;
}

static WUDDeleteState __wudDeleteCleanupDatabase(void)
{
	int i;

	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	if (__wudGetLinkNumber() != 0)
		return WUD_STATE_DELETE_CLEANUP_DATABASE;

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		p_info = &p_wcb->stdDevs[i];
		if (p_info->at_0x59 == 1)
			WUDiRemoveDevice(p_info->devAddr);
	}

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		p_info = &p_wcb->smpDevs[i];
		if (p_info->at_0x59 == 1)
			WUDiRemoveDevice(p_info->devAddr);
	}

	if (WUDIsLinkedWBC())
	{
		if (SCGetProductGameRegion() == SC_PRD_GAME_REG_JP)
		{
			LINK_KEY link_key = {0};
			__wudPrepareWBCDevInfo(NULL, link_key, NULL);

			return WUD_STATE_WII_FIT_OPEN;
		}
		else
		{
			return WUD_STATE_DELETE_CLEANUP_SETTING;
		}
	}
	else
	{
		return WUD_STATE_DELETE_CLEANUP_SETTING;
	}
}

static void __wudDeleteCleanupSetting(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	BOOL success = FALSE;

	if (SCCheckStatus() == SC_STATUS_BUSY)
		return;

	memset(&_scArray, 0, sizeof _scArray);
	memset(&_spArray, 0, sizeof _spArray);

	success |= SCSetBtDeviceInfoArray(&_scArray);
	success |= SCSetBtCmpDevInfoArray(&_spArray);

	if (success)
	{
		p_wcb->deleteState = WUD_STATE_DELETE_6;
		SCFlushAsync(&__wudDeleteFlushCallback);
	}
	else
	{
		p_wcb->deleteState = WUD_STATE_DELETE_DONE;
	}
}

static WUDDeleteState __wudDeleteDone(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDSetVisibility(FALSE, WUDGetConnectable());
	OSCancelAlarm(&p_wcb->alarm);
	p_wcb->deleteState = WUD_STATE_START;

	if (p_wcb->clearDevCB)
		(*p_wcb->clearDevCB)(1);

	return WUD_STATE_START;
}

static void __wudDeleteHandler(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	p_wcb->syncState = WUD_STATE_START;

	switch (p_wcb->deleteState)
	{
	case WUD_STATE_DELETE_DISALLOW_INCOMING:
		p_wcb->deleteState = __wudDeleteDisallowIncoming();
		break;

	case WUD_STATE_DELETE_DISCONNECT_ALL:
		p_wcb->deleteState = __wudDeleteDisconnectAll();
		break;

	case WUD_STATE_DELETE_CLEANUP_DATABASE:
		p_wcb->deleteState = __wudDeleteCleanupDatabase();
		break;

	case WUD_STATE_DELETE_CLEANUP_SETTING:
		__wudDeleteCleanupSetting();
		break;

	case WUD_STATE_DELETE_DONE:
		p_wcb->deleteState = __wudDeleteDone();
		break;

	// Wii Fit states

	case WUD_STATE_WII_FIT_OPEN:
		__wudOpenWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_SEEK:
		__wudSeekWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_UPDATE:
		__wudUpdateWiiFitFile();
		break;

	case WUD_STATE_WII_FIT_CLOSE:
		__wudCloseWiiFit();
		break;

	// Actionless states (?)

	case WUD_STATE_DELETE_7:
		break;
	}
}

static void __wudDeleteHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx((register_t)alarm, (register_t)context, 0, 0,
	                &__wudDeleteHandler,
	                &_wudHandlerStack[sizeof _wudHandlerStack]);
}

static WUDStackState __wudStackGetStoredLinkKey(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	// see WUDiHidHostEventCallback, case BTA_HH_ENABLE_EVT
	if (p_wcb->hhFlags == 1)
	{
		p_wcb->linkKeyState = WUD_STATE_LINK_KEY_READING;
		BTM_ReadStoredLinkKey(NULL, &__wudLinkKeyEventStackCallback);
	}

	return WUD_STATE_STACK_CHECK_DEVICE_INFO;
}

static WUDStackState __wudStackCheckDeviceInfo(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	int i;
	if (p_wcb->linkKeyState == WUD_STATE_START)
	{
		for (i = 0; i < WUD_MAX_DEV_ENTRY; i++)
		{
			p_info = __wudGetDevInfoByIndex(i);
			if (!p_info->at_0x59)
				continue;

			if (p_info->at_0x5c == 1)
			{
				p_wcb->linkKeyState = WUD_STATE_LINK_KEY_DELETING;
				BTM_DeleteStoredLinkKey(p_info->devAddr,
				                        &__wudLinkKeyEventStackCallback);
				p_info->at_0x5c = 0;

				return WUD_STATE_STACK_CHECK_DEVICE_INFO;
			}

			if (p_info->at_0x5c != 3)
				__wudRemoveDevInfo(p_info->devAddr);
		}

		return WUD_STATE_STACK_DONE;
	}
	else
	{
		return WUD_STATE_STACK_CHECK_DEVICE_INFO;
	}
}

static WUDStackState __wudStackDone(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (p_wcb->linkKeyState == WUD_STATE_START)
	{
		OSCancelAlarm(&p_wcb->alarm);
		__wudCheckFirmwareVersion();

		return WUD_STATE_STACK_INITIALIZED;
	}
	else
	{
		return WUD_STATE_STACK_CHECK_DEVICE_INFO;
	}
}

static void __wudStackHandler(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	switch (p_wcb->stackState)
	{
	case WUD_STATE_STACK_GET_STORED_LINK_KEY:
		p_wcb->stackState = __wudStackGetStoredLinkKey();
		break;

	case WUD_STATE_STACK_CHECK_DEVICE_INFO:
		p_wcb->stackState = __wudStackCheckDeviceInfo();
		break;

	case WUD_STATE_STACK_DONE:
		p_wcb->stackState = __wudStackDone();
		break;
	}
}

static void __wudStackHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx((register_t)alarm, (register_t)context, 0, 0,
	                &__wudStackHandler,
	                &_wudHandlerStack[sizeof _wudHandlerStack]);
}

static void __wudInitFlushCallback(SCStatus result __attribute__((unused)))
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	p_wcb->initState = WUD_STATE_INIT_DONE;
}

static WUDInitState __wudInitWaitForDeviceUp(void)
{
	WUDInitState nextState = WUD_STATE_INIT_WAIT_FOR_DEVICE_UP;
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (--p_wcb->initWaitDeviceUpFrames < 0)
		WUDiShowFatalErrorMessage();

	if (BTA_DmIsDeviceUp())
		nextState = WUD_STATE_INIT_WAIT_FOR_INITIALIZATION;

	return nextState;
}

static WUDInitState __wudInitWaitForInitialization(void)
{
	s32 diff = 0;
	WUDInitState nextState = WUD_STATE_INIT_WAIT_FOR_INITIALIZATION;
	OSTime time = __OSGetSystemTime();

	diff = 500 - OSTicksToMilliseconds(OSDiffTick(time, __OSStartTime));

	if (diff < 0 && SCCheckStatus() != SC_STATUS_BUSY)
	{
		__wudClearControlBlock();

		nextState = WUD_STATE_INIT_GET_DEV_INFO;

		if (WUDIsLinkedWBC() && SCGetProductGameRegion() == SC_PRD_GAME_REG_JP)
		{
			nextState = WUD_STATE_INIT_GET_DEV_INFO_FROM_WII_FIT;

			_wudNandLocked = FALSE;
			_wudNandPhase = WUD_STATE_START;
		}
	}

	return nextState;
}

static BOOL __wudIsExistedDevice(BD_ADDR dev_addr)
{
	int i;
	for (i = 0; i < _scArray.num; i++)
		if (WUD_BDCMP(_scArray.devices[i].devAddr, dev_addr) == 0)
			return TRUE;

	return FALSE;
}

static WUDInitState __wudInitDevInfo(void)
{
	BD_ADDR dev_addr;

	memset(&_scArray, 0, sizeof _scArray);
	memset(&_spArray, 0, sizeof _spArray);
	memset(dev_addr, 0, BD_ADDR_LEN);

	SCGetBtDeviceInfoArray(&_scArray);
	SCGetBtCmpDevInfoArray(&_spArray);

	OSAssert_Line(2422, _scArray.num >= 0 && _scArray.num <= WUD_MAX_DEV_ENTRY_FOR_STD);
	OSAssert_Line(2423, _spArray.num >= 0 && _spArray.num <= WUD_MAX_DEV_ENTRY_FOR_SMP);

	__rvl_wudcb.syncType = WUD_SYNC_TYPE_STANDARD;
	int i, j;
	u32 arrayNum;
	u8 a;

	WUDDevInfo *p_info;
	for (i = 0, arrayNum = _scArray.num, a = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD;
	     i++)
	{
		if (!arrayNum)
			break;

		if (!WUD_DEV_NAME_IS_CNT(_scArray.devices[i].small.devName))
			memset(&_scArray.devices[i], 0, sizeof _scArray.devices[i]);

		if (WUD_BDCMP(_scArray.devices[i].devAddr, dev_addr) == 0)
		{
			if (i < WUD_MAX_DEV_ENTRY_FOR_STD - 1)
			{
				for (j = i + 1; j < WUD_MAX_DEV_ENTRY_FOR_STD; j++)
				{
					if (WUD_DEV_NAME_IS_CNT(_scArray.devices[j].small.devName))
					{
						memcpy(&_scArray.devices[i], &_scArray.devices[j],
						       sizeof _scArray.devices[i]);
						memset(&_scArray.devices[j], 0,
						       sizeof _scArray.devices[i]);

						goto there;
					}
				}
			}
		}
		else
		{
		// presumably what fucked over ghidra
		there:
			p_info = __wudGetNewDevInfo();
			if (p_info)
			{
				WUD_BDCPY(p_info->devAddr, _scArray.devices[i].devAddr);
				memcpy(&p_info->small, &_scArray.devices[i].small,
				       sizeof p_info->small);

				p_info->at_0x59 = 1;
				p_info->at_0x5b = 0;
				p_info->at_0x5c = 2;
				p_info->subclass = 2; // subclass 2 is marked as reserved
				p_info->hhAttrMask = 0x8074;
				p_info->appID = 3;

				a++;
				arrayNum--;
			}
		}
	}

	if (WUDIsLinkedWBC() && WUD_DEV_NAME_IS_WBC(_scArray.wbc.small.devName))
	{
		p_info = __wudGetNewDevInfo();
		if (!p_info)
		{
			p_info = __wudGetDevInfoByIndex(9);
			a--;
		}

		WUD_BDCPY(p_info->devAddr, _scArray.wbc.devAddr);
		memcpy(p_info->small.devName, _scArray.wbc.small.devName, 19); // ?
		memcpy(p_info->linkKey, _scArray.wbc.small.at_0x14, LINK_KEY_LEN);

		p_info->at_0x59 = 1;
		p_info->at_0x5b = 0;
		p_info->subclass = 2;
		p_info->hhAttrMask = 0x8074;
		p_info->appID = 3;
		p_info->at_0x5c = 3;

		memset(&_scArray.devices[a], 0, sizeof _scArray.devices[a]);
		WUD_BDCPY(_scArray.devices[a].devAddr, _scArray.wbc.devAddr);
		// sizeof == 19?
		memcpy(_scArray.devices[a].small.devName, _scArray.wbc.small.devName,
		       19);

		a++;
	}

	_scArray.num = a;
	__rvl_wudcb.syncType = WUD_SYNC_TYPE_SIMPLE;

	for (i = 5, arrayNum = _spArray.num; i >= 0; i--)
	{
		if (!arrayNum)
			break;

		if (WUD_BDCMP(_spArray.devices[i].devAddr, dev_addr) == 0)
			continue;

		if (__wudIsExistedDevice(_spArray.devices[i].devAddr))
			continue;

		p_info = __wudGetNewDevInfo();
		if (p_info)
		{
			WUD_BDCPY(p_info->devAddr, _spArray.devices[i].devAddr);
			memcpy(&p_info->small, &_spArray.devices[i].small,
			       sizeof p_info->small);
			memcpy(p_info->linkKey, _spArray.devices[i].linkKey, LINK_KEY_LEN);

			p_info->at_0x59 = 1;
			p_info->at_0x5b = 1;
			p_info->at_0x5c = 3;

			if (WUD_DEV_NAME_IS_CNT_01(p_info->small.devName))
			{
				p_info->subclass = 2;
				p_info->hhAttrMask = 0x8074;
				p_info->appID = 3;
			}

			WUDiMoveTopSmpDevInfoPtr(p_info);

			arrayNum--;
		}
	}

	__rvl_wudcb.syncType = WUD_SYNC_TYPE_STANDARD;
	__rvl_wudcb.initState = WUD_STATE_INIT_5;

	memset(&_spArray, 0, sizeof _spArray);
	SCSetBtDeviceInfoArray(&_scArray);
	SCSetBtCmpDevInfoArray(&_spArray);
	SCFlushAsync(&__wudInitFlushCallback);

	return WUD_STATE_INIT_DONE;
}

static WUDInitState __wudInitDone(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	OSCancelAlarm(&p_wcb->alarm);

	p_wcb->libStatus = WUD_LIB_STATUS_1;

	BTA_EnableBluetooth(&__wudSecurityEventStackCallback);

	return WUD_STATE_INIT_INITIALIZED;
}

static void __wudNandResultCallback(NANDResult result, NANDCommandBlock *block
                                    __attribute__((unused)))
{
	// ?
#if !defined(NDEBUG)
	// clang-format off
	const char *funcNames[6] __attribute__((unused)) =
	{
		"",
		"NANDOpen",
		"NANDSeek",
		"NANDRead",
		"",
		"NANDClose"
	};
	// clang-format on
#endif // !defined(NDEBUG)

	_wudNandLocked = FALSE;

	switch (_wudNandPhase)
	{
	case WUD_STATE_NAND_OPEN:
		_wudNandPhase =
			result == NAND_ESUCCESS ? _wudNandPhase + 1 : WUD_STATE_ERROR;
		break;

	case WUD_STATE_NAND_SEEK:
		_wudNandPhase = result == 0 ? _wudNandPhase + 1 : WUD_STATE_NAND_CLOSE;
		break;

	case WUD_STATE_NAND_READ:
		_wudNandPhase =
			result == 0x4b000 ? _wudNandPhase + 1 : WUD_STATE_NAND_CLOSE;
		break;

	default:
		_wudNandPhase = WUD_STATE_NAND_DONE;
		break;
	}
}

static void __wudNandFlushCallback(SCStatus result __attribute__((unused)))
{
	_wudNandLocked = FALSE;
	_wudNandPhase++;
}

static u32 __wudCalcWiiFitCrc1(void *data_, u32 length_)
{
	u16 *data = data_;
	u32 crcHi = 0;
	u16 crcLo = 0;

	u32 i;
	u32 length = length_ / sizeof *data;
	for (i = 0; i < length; ++i, ++data)
	{
		crcHi += *data;
		crcLo += ~*data;
	}

	return (u16)crcHi << 16 | crcLo;
}

static u32 __wudCalcWiiFitCrc2(void *data_, u32 length_, u32 crc)
{
	u16 *data = data_;
	u32 crcHi = (u16)(crc >> 16);
	u16 crcLo = (u16)crc;

	u32 i;
	u32 length = length_ / sizeof *data;
	for (i = 0; i < length; ++i, ++data)
	{
		crcHi += *data;
		crcLo += ~*data;
	}

	return (u16)crcHi << 16 | crcLo;
}

static WUDInitState __wudGetDevInfoFromWiiFit(void)
{
	const char *wfFilePath = RP_HEALTH_FILE_PATH;
	const char *wfTitleID = WII_FIT_TITLE_ID;
	byte_t zeroBuf[16] = {0};

	WUDInitState nextState = WUD_STATE_INIT_GET_DEV_INFO_FROM_WII_FIT;

	if (_wudNandLocked)
		return nextState;

	if (!_wudNandBufPtr || !IS_ALIGNED(_wudNandBufPtr, 0x20))
	{
		OSError_Line(2745, "Error: the workarea for synchronizing WBC pairing "
		                   "information is not allocated.\n");
	}

	NANDResult result;
	u32 wfDataCrc;
	u32 wfCalcCrc;
	switch (_wudNandPhase)
	{
	case WUD_STATE_START:
		result = NANDInit();
		_wudNandPhase =
			result == NAND_ESUCCESS ? WUD_STATE_NAND_OPEN : WUD_STATE_ERROR;
		break;

	case WUD_STATE_NAND_OPEN:
		if (SCGetProductGameRegion() == SC_PRD_GAME_REG_JP)
		{
			_wudNandLocked = TRUE;
			_wudNandWbcCrc = 0;

			result =
				NANDOpenAsync(wfFilePath, &_wudNandFileInfo, NAND_OPEN_READ,
			                  &__wudNandResultCallback, &_wudNandBlock);
		}
		else
		{
			_wudNandPhase = WUD_STATE_NAND_DONE;
		}

		break;

	case WUD_STATE_NAND_SEEK:
		_wudNandLocked = TRUE;

		result = NANDSeekAsync(&_wudNandFileInfo, 0, NAND_SEEK_SET,
		                       &__wudNandResultCallback, &_wudNandBlock);

		break;

	case WUD_STATE_NAND_READ:
		_wudNandLocked = TRUE;

		result = NANDReadAsync(&_wudNandFileInfo, _wudNandBufPtr, 0x4b000,
		                       &__wudNandResultCallback, &_wudNandBlock);

		break;

	case WUD_STATE_NAND_GET_DEV_INFO:
		memcpy(&_wudNandWbcInfo, _wudNandBufPtr + RP_HEALTH_FILE_OFFSET, 128);
		memcpy(&wfDataCrc, _wudNandBufPtr + RP_HEALTH_FILE_OFFSET + 0x80,
		       sizeof wfDataCrc);

		_wudNandWbcCrc =
			__wudCalcWiiFitCrc1(_wudNandBufPtr, RP_HEALTH_FILE_OFFSET);
		wfCalcCrc = __wudCalcWiiFitCrc2(_wudNandBufPtr + RP_HEALTH_FILE_OFFSET,
		                                128, _wudNandWbcCrc);
		if (wfDataCrc != wfCalcCrc)
		{
			_wudNandPhase = WUD_STATE_NAND_CLOSE;
			break;
		}

		if (WUD_BDCMP(_wudNandWbcInfo.scDevInfo.devAddr, zeroBuf) == 0)
		{
			_wudNandPhase = WUD_STATE_NAND_CLOSE;
			break;
		}

		if (memcmp(OSGetAppGamename(), wfTitleID, 4) != 0
		    && memcmp(_wudNandWbcInfo.scDevInfo.small.devName, zeroBuf, 16)
		           == 0)
		{
			_wudNandPhase = WUD_STATE_NAND_CLOSE;
			break;
		}

		memset(_wudNandBufPtr, 0, 0x4b000);

		memset(&_scArray, 0, sizeof _scArray);
		SCGetBtDeviceInfoArray(&_scArray);

		WUD_BDCPY(_scArray.wbc.devAddr, _wudNandWbcInfo.scDevInfo.devAddr);

		// TODO: what?
		memcpy(&_scArray.wbc.small, (void *)((u32)&_wudNandWbcInfo + 22),
		       sizeof _scArray.wbc.small);
		memcpy((void *)((u32)&_scArray.wbc + 26),
		       &_wudNandWbcInfo.scDevInfo.small.devName, 16);
		SCSetBtDeviceInfoArray(&_scArray);

		_wudNandLocked = TRUE;
		SCFlushAsync(__wudNandFlushCallback);

		break;

	case WUD_STATE_NAND_CLOSE:
		_wudNandLocked = TRUE;

		result = NANDCloseAsync(&_wudNandFileInfo, &__wudNandResultCallback,
		                        &_wudNandBlock);

		break;

	default:
	// case WUD_STATE_NAND_DONE:
		nextState = WUD_STATE_INIT_GET_DEV_INFO;
		break;
	}

	return nextState;
}

static void __wudInitHandler(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	switch (p_wcb->initState)
	{
	case WUD_STATE_INIT_WAIT_FOR_DEVICE_UP:
		p_wcb->initState = __wudInitWaitForDeviceUp();
		break;

	case WUD_STATE_INIT_WAIT_FOR_INITIALIZATION:
		p_wcb->initState = __wudInitWaitForInitialization();
		break;

	case WUD_STATE_INIT_GET_DEV_INFO:
		/* p_wcb->initState = */ __wudInitDevInfo(); // ?
		break;

	case WUD_STATE_INIT_DONE:
		p_wcb->initState = __wudInitDone();
		break;

	case WUD_STATE_INIT_GET_DEV_INFO_FROM_WII_FIT:
		p_wcb->initState = __wudGetDevInfoFromWiiFit();
		break;
	}
}

static void __wudInitHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx((register_t)alarm, (register_t)context, 0, 0,
	                &__wudInitHandler,
	                &_wudHandlerStack[sizeof _wudHandlerStack]);
}

static void __wudShutdownFlushCallback(SCStatus result __attribute__((unused)))
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	p_wcb->shutdownState = WUD_STATE_SHUTDOWN_DONE;
}

static void __wudShutdownStoreSetting(void)
{
	BOOL success = _wudReadNand;

	if (SCCheckStatus() == SC_STATUS_BUSY)
		return;

	success &= SCSetBtDeviceInfoArray(&_scArray);
	success &= SCSetBtCmpDevInfoArray(&_spArray);

	if (success)
	{
		__rvl_wudcb.shutdownState = WUD_STATE_SHUTDOWN_FLUSH_SETTINGS;

		SCFlushAsync(&__wudShutdownFlushCallback);
	}
	else
	{
		__rvl_wudcb.shutdownState = WUD_STATE_SHUTDOWN_DONE;
	}
}

static void __wudShutdownDone(void)
{
	OSCancelAlarm(&__rvl_wudcb.alarm);
	BTA_DisableBluetooth();
}

static void __wudShutdownHandler(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	switch (p_wcb->shutdownState)
	{
	case WUD_STATE_SHUTDOWN_STORE_SETTINGS:
		__wudShutdownStoreSetting();
		break;

	case WUD_STATE_SHUTDOWN_DONE:
		__wudShutdownDone();
		break;
	}
}

static void __wudShutdownHandler0(OSAlarm *alarm, OSContext *context)
{
	OSSwitchFiberEx((register_t)alarm, (register_t)context, 0, 0,
	                &__wudShutdownHandler,
	                &_wudHandlerStack[sizeof _wudHandlerStack]);
}

static void __wudClearControlBlock(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY; i++)
	{
		WUDiSetDevAddrForHandle(i, NULL);
		WUDiSetQueueSizeForHandle(i, 0);
		WUDiSetNotAckNumForHandle(i, 0);
	}

	p_wcb->smpListTail = &p_wcb->smpList[5];
	p_wcb->smpListHead = &p_wcb->smpList[0];

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		p_wcb->smpList[i].devInfo = &p_wcb->smpDevs[5 - i];
		p_wcb->smpList[i].prev = i == 0 ? NULL : &p_wcb->smpList[i - 1];
		p_wcb->smpList[i].next = i == 5 ? NULL : &p_wcb->smpList[i + 1];
	}

	p_wcb->stdListTail = &p_wcb->stdList[9];
	p_wcb->stdListHead = &p_wcb->stdList[0];

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		p_wcb->stdList[i].devInfo = &p_wcb->stdDevs[i];
		p_wcb->stdList[i].prev = i == 0 ? NULL : &p_wcb->stdList[i - 1];
		p_wcb->stdList[i].next = i == 9 ? NULL : &p_wcb->stdList[i + 1];
	}

	p_wcb->syncState = WUD_STATE_START;
	p_wcb->linkKeyState = WUD_STATE_START;
	p_wcb->deleteState = WUD_STATE_START;
	p_wcb->stackState = WUD_STATE_START;
	p_wcb->initState = WUD_STATE_START;
	p_wcb->shutdownState = WUD_STATE_START;

	p_wcb->syncSkipChecks = FALSE;
	p_wcb->syncType = WUD_SYNC_TYPE_STANDARD;
	p_wcb->syncLoopNum = 1;

	p_wcb->connectable = FALSE;
	p_wcb->discoverable = FALSE;

	p_wcb->libStatus = WUD_LIB_STATUS_0;
	p_wcb->pmID = 0;
	p_wcb->syncRssi = -65;

	memset(p_wcb->hostAddr, 0, BD_ADDR_LEN);
	memset(p_wcb->pairAddr, 0, BD_ADDR_LEN);

	p_wcb->bufferStatus0 = 0;
	p_wcb->bufferStatus1 = 10;

	__wudClearDevInfos();
}

BOOL WUDInit(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (_wudInitialized)
		return FALSE;

	OSAssertMessage_Line(3086, p_wcb->allocFunc && p_wcb->freeFunc,
	                     "No allocator is registered!\n"
	                     "Please register allocator before initialization.\n");

	BTA_Init();
	bta_sys_set_trace_level(__bte_trace_level);
	L2CA_SetTraceLevel(__bte_trace_level);
	SDP_SetTraceLevel(__bte_trace_level);

	p_wcb->syncStdCB = NULL;
	p_wcb->syncSmpCB = NULL;
	p_wcb->clearDevCB = NULL;

	p_wcb->hidConnCB = NULL;
	p_wcb->hidRecvCB = NULL;

	p_wcb->initState = WUD_STATE_INIT_WAIT_FOR_DEVICE_UP;
	p_wcb->initWaitDeviceUpFrames = 20;

	SCInit();

	if (_linkedWBC && _initWBC)
		(*_initWBC)();

	OSCreateAlarm(&p_wcb->alarm);
	OSSetPeriodicAlarm(&p_wcb->alarm, OSGetTime(), OSMillisecondsToTicks(10),
	                   &__wudInitHandler0);

	_wudInitialized = TRUE;
	_scFlush = FALSE;

	return TRUE;
}

void WUDRegisterAllocator(WUDAllocFunc *alloc, WUDFreeFunc *free)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	OSAssert_Line(3137, alloc != NULL && free != NULL);

	BOOL intrStatus = OSDisableInterrupts();

	p_wcb->allocFunc = alloc;
	p_wcb->freeFunc = free;

	OSRestoreInterrupts(intrStatus);
}

void WUDShutdown(BOOL saveSimpleDevs)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	if (WUDIsBusy())
		OSCancelAlarm(&p_wcb->alarm);

	memset(_scArray.devices, 0,
	       sizeof _scArray.devices[0] * WUD_MAX_DEV_ENTRY_FOR_STD);

	int i;
	struct WUDDevInfoList *infoList;

	i = 0;
	infoList = __rvl_wudcb.stdListHead;
	while (infoList)
	{
		WUD_BDCPY(_scArray.devices[i].devAddr, infoList->devInfo->devAddr);
		memcpy(&_scArray.devices[i].small, &infoList->devInfo->small,
		       sizeof _scArray.devices[i].small);

		infoList = infoList->next;
		i++;
	}

	_scArray.num = __wudGetStdDevNumber();

	memset(_spArray.devices, 0, sizeof _spArray.devices);

	if (saveSimpleDevs)
	{
		i = 0;
		infoList = __rvl_wudcb.smpListHead;
		while (infoList)
		{
			WUD_BDCPY(_spArray.devices[i].devAddr, infoList->devInfo->devAddr);
			memcpy(&_spArray.devices[i].small, &infoList->devInfo->small,
			       sizeof _spArray.devices[i].small);

			memcpy(&_spArray.devices[i].linkKey, &infoList->devInfo->linkKey,
			       LINK_KEY_LEN);

			infoList = infoList->next;
			i++;
		}

		_spArray.num = __wudGetSmpDevNumber();
	}
	else
	{
		_spArray.num = 0;
	}

	p_wcb->shutdownState = WUD_STATE_SHUTDOWN_STORE_SETTINGS;

	OSCreateAlarm(&p_wcb->alarm);
	OSSetPeriodicAlarm(&p_wcb->alarm, OSGetTime(), OSMillisecondsToTicks(10),
	                   &__wudShutdownHandler0);

	p_wcb->libStatus = WUD_LIB_STATUS_4;

	OSRestoreInterrupts(intrStatus);
}

WUDLibStatus WUDGetStatus(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	s8 libStatus = p_wcb->libStatus;

	OSRestoreInterrupts(intrStatus);

	return libStatus;
}

u8 WUDGetBufferStatus(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	u8 ret;
	BOOL intrStatus = OSDisableInterrupts();

	ret = p_wcb->bufferStatus1 - p_wcb->bufferStatus0;

	OSRestoreInterrupts(intrStatus);

	return ret;
}

void WUDSetSniffMode(BD_ADDR dev_addr, int interval)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	tBTM_PM_PWR_MD block;

	if (interval > 0)
		block.mode = BTM_PM_MD_SNIFF;
	else
		block.mode = BTM_PM_MD_ACTIVE;

	block.max = interval;
	block.min = interval;
	block.attempt = 1;
	block.timeout = 0;

	tBTM_STATUS status __attribute__((unused)) =
		BTM_SetPowerMode(p_wcb->pmID, dev_addr, &block);
}

WUDSyncDeviceCallback *WUDSetSyncSimpleCallback(WUDSyncDeviceCallback *cb)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDSyncDeviceCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wcb->syncSmpCB;
	p_wcb->syncSmpCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

static BOOL __wudStartSyncDevice(WUDSyncType syncType, s8 syncLoopNum,
                                 u8 target, signed param_4)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL ret = FALSE;
	BOOL intrStatus = OSDisableInterrupts();

	u32 libStatus = p_wcb->libStatus;

	OSRestoreInterrupts(intrStatus);

	if (libStatus == WUD_LIB_STATUS_3 && !WUDIsBusy())
	{
		intrStatus = OSDisableInterrupts();

		_wudTarget = target;

		p_wcb->syncState = WUD_STATE_SYNC_PREPARE_SEARCH;
		p_wcb->syncLoopNum = syncLoopNum;
		p_wcb->syncType = syncType;
		p_wcb->syncSkipChecks = param_4 ? 1 : 0;
		p_wcb->syncedNum = 0;
		p_wcb->waitStartSearchFrames = 50;
		p_wcb->waitIncomingFrames = 200;

		OSCreateAlarm(&p_wcb->alarm);
		OSSetPeriodicAlarm(&p_wcb->alarm, OSGetTime(),
		                   OSMillisecondsToTicks(20), &__wudSyncHandler0);

		OSRestoreInterrupts(intrStatus);

		ret = TRUE;
	}

	return ret;
}

static BOOL __wudStartSyncStandard(signed param_1)
{
	return __wudStartSyncDevice(WUD_SYNC_TYPE_STANDARD, 3, 0, param_1);
}

static BOOL __wudStartSyncSimple(signed param_1)
{
	return __wudStartSyncDevice(WUD_SYNC_TYPE_SIMPLE, -1, 0, param_1);
}

BOOL WUDStartSyncDevice(void)
{
	return __wudStartSyncStandard(0);
}

BOOL WUDStartFastSyncSimple(void)
{
	return __wudStartSyncSimple(1);
}

static BOOL __wudStopSyncDevice(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL success = FALSE;
	BOOL intrStatus = OSDisableInterrupts();

	if (p_wcb->libStatus == WUD_LIB_STATUS_3)
	{
		if (p_wcb->syncLoopNum)
		{
			if (p_wcb->syncState == WUD_STATE_SYNC_WAIT_FOR_SEARCH_RESULT)
				BTA_DmSearchCancel();

			p_wcb->syncLoopNum = 0;
		}

		success = TRUE;
	}

	OSRestoreInterrupts(intrStatus);

	return success;
}

BOOL WUDCancelSyncDevice(void)
{
	_wudAbortSync = TRUE;

	return __wudStopSyncDevice();
}

BOOL WUDStopSyncSimple(void)
{
	return __wudStopSyncDevice();
}

BOOL WUDStartClearDevice(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL success = FALSE;
	BOOL intrStatus = OSDisableInterrupts();

	u32 libStatus = p_wcb->libStatus;

	OSRestoreInterrupts(intrStatus);

	if (libStatus == WUD_LIB_STATUS_3 && !WUDIsBusy())
	{
		intrStatus = OSDisableInterrupts();

		p_wcb->deleteState = WUD_STATE_DELETE_DISALLOW_INCOMING;

		OSCreateAlarm(&p_wcb->alarm);
		OSSetPeriodicAlarm(&p_wcb->alarm, OSGetTime(),
		                   OSMillisecondsToTicks(20), &__wudDeleteHandler0);

		OSRestoreInterrupts(intrStatus);

		success = TRUE;
	}

	return success;
}

BOOL WUDSetDisableChannel(s8 afhChannel)
{
	int first = 0;
	int last = 0;

	BOOL success = FALSE;

	wud_cb_st *p_wcb = &__rvl_wudcb;

#if defined(NDEBUG)
	if ((u8)afhChannel < 0 || 13 < (u8)afhChannel)
#else
	if (afhChannel < 0 || 13 < afhChannel)
#endif
		return success;

	BOOL intrStatus = OSDisableInterrupts();

	u32 libStatus = p_wcb->libStatus;

	OSRestoreInterrupts(intrStatus);

	tBTM_STATUS result __attribute__((unused));
	if (libStatus == WUD_LIB_STATUS_3)
	{
		if (!afhChannel)
		{
			first = 255;
			last = 255;
		}
		else
		{
			first = (afhChannel + 1) * 5 - 14;
			last = (afhChannel + 1) * 5 + 14;

			if (first < 0)
				first = 0;

			if (last > 78)
				last = 78;
		}

		result = BTM_SetAfhChannels(first, last);

		success = TRUE;
	}

	return success;
}

WUDHidReceiveCallback *WUDSetHidRecvCallback(WUDHidReceiveCallback *cb)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDHidReceiveCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wcb->hidRecvCB;
	p_wcb->hidRecvCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

WUDHidConnectCallback *WUDSetHidConnCallback(WUDHidConnectCallback *cb)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDHidConnectCallback *old;
	BOOL intrStatus = OSDisableInterrupts();

	old = p_wcb->hidConnCB;
	p_wcb->hidConnCB = cb;

	OSRestoreInterrupts(intrStatus);

	return old;
}

void WUDSetVisibility(u8 discoverable, u8 connectable)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	p_wcb->discoverable = discoverable;
	p_wcb->connectable = connectable;

	OSRestoreInterrupts(intrStatus);

	// again, see notes about this prototype
	BTA_DmSetVisibility(discoverable, connectable);
}

u8 WUDGetConnectable(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	u8 connectable;
	BOOL intrStatus = OSDisableInterrupts();

	connectable = p_wcb->connectable;

	OSRestoreInterrupts(intrStatus);

	return connectable;
}

static void __wudModuleRebootCallback(void *p1 __attribute__((unused)))
{
	__wudInitSub();
}

static void __wudModuleReboot(void)
{
	BTM_DeviceReset(&__wudModuleRebootCallback);
}

static void __wudInstallPatchCallback(tBTM_VSC_CMPL *p1)
{
	if ((_wudPatchNum == _wudInstallNum && p1) || !p1)
		__wudModuleReboot();
	else
		__wudInstallPatch();
}

static void __wudInstallPatch(void)
{
	u8 num = MIN(_wudPatchNum - _wudInstallNum, INSTALL_PATCH_MAX_NUM);

	byte_t buf[INSTALL_PATCH_MAX_BUF];
	buf[offsetof(struct wud_patch_install_cmd_array, num)] = num;
	memcpy(&buf[offsetof(struct wud_patch_install_cmd_array, installCmds)],
	       _wudPatchInstallCmd.installCmds[_wudInstallNum],
	       INSTALL_PATCH_TOTAL_SIZE(num));

	_wudInstallNum += num;
	BTM_VendorSpecificCommand(BT_VSC_NINTENDO_INSTALL_PATCH,
	                          (u8)sizeof num + INSTALL_PATCH_TOTAL_SIZE(num),
	                          buf, &__wudInstallPatchCallback);
}

static void __wudWritePatchCallback(tBTM_VSC_CMPL *p1)
{
	if (p1)
	{
		if (_wudPatchSize == (u32)_wudPatchOffset)
		{
			_wudInstallNum = 0;
			_wudPatchNum = _wudPatchInstallCmd.num;
			__wudInstallPatch();
		}
		else
		{
			__wudWritePatch();
		}
	}
	else
	{
		__wudModuleReboot();
	}
}

// TODO on release (fine in __wudWritePatchCallback, not in __wudRemovePatchCallback)

static void __wudWritePatch(void)
{
	(void)_wudPatchOffset; // ok

	u8 length = MIN(_wudPatchSize - _wudPatchOffset, 255 - sizeof(u32));

	int i;
	byte_t buf[255];

	// stwbrx op
	for (i = 0; i < (int)sizeof(u32); i++)
		buf[i] = (_wudPatchAddress + _wudPatchOffset) >> (i * 8);

	for (i = 0; i < (s32)length; i++)
	{
		buf[(int)sizeof(u32) + i] =
			_wudPatchData[sizeof(_wudPatchSize) + sizeof(_wudPatchOffset)
		                  + _wudPatchOffset + i];
	}

	_wudPatchOffset += length;
	BTM_VendorSpecificCommand(BT_VSC_NINTENDO_WRITE_PATCH,
	                          (int)sizeof(u32) + length, buf,
	                          &__wudWritePatchCallback);
}

static void __wudRemovePatchCallback(tBTM_VSC_CMPL *p1)
{
	if (p1)
	{
		_wudPatchOffset = 0;
		__wudWritePatch();
	}
	else
	{
		__wudModuleReboot();
	}
}

static void __wudRemovePatch(void)
{
	BTM_VendorSpecificCommand(BT_VSC_NINTENDO_INSTALL_PATCH,
	                          sizeof _wudPatchRemoveCmd, &_wudPatchRemoveCmd,
	                          &__wudRemovePatchCallback);
}

static void __wudSuperPeekPokeCallback(tBTM_VSC_CMPL *p1
                                       __attribute__((unused)))
{
	__wudRemovePatch();
}

static void __wudSuperPeekPoke(void)
{
	BTM_VendorSpecificCommand(BT_VSC_NINTENDO_SUPER_PEEK_POKE,
	                          sizeof _wudSuperPeekPokeCmd, _wudSuperPeekPokeCmd,
	                          &__wudSuperPeekPokeCallback);
}

static void __wudAppendRuntimePatch(void)
{
	_wudPatchSize = 0;
	_wudPatchAddress = 0;

	int i;
	for (i = 0; i < (int)sizeof(u32); i++)
	{
		// lwbrx ops
		_wudPatchAddress <<= 8;
		_wudPatchAddress += _wudPatchData[3 - i];

		_wudPatchSize <<= 8;
		_wudPatchSize += _wudPatchData[7 - i];
	}

	if (__OSInIPL)
		__wudSuperPeekPoke();
	else
		__wudRemovePatch();
}

static void __wudCheckFirmwareVersion(void)
{
	tBTM_VERSION_INFO version;
	BTM_ReadLocalVersion(&version);

	if ((version.hci_revision & 0xfff) == 0xa7)
		__wudAppendRuntimePatch();
	else
		__wudInitSub();
}

static void __wudInitSub(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	char devName[] = "Wii";

	// [1]: 2.8 Class of Device (p. 45)
	DEV_CLASS devClass =
	{
		0x00, // No designated Major Service Classes
		0x04, // Major Device Class 4 (Audio/Video)
		0x48  // Minor Device Class 18 (Audio/Video -> Gaming/Toy)
	};

	BTA_DmSetDeviceName(devName);
	BTM_SetDeviceClass(devClass);
	BTM_RegisterForVSEvents(&__wudVendorSpecificEventStackCallback);
	BTM_RegisterForDeviceStatusNotif(&__wudDeviceStatusEventStackCallback);
	BTM_PmRegister(BTM_PM_REG_SET | BTM_PM_REG_NOTIF, &p_wcb->pmID,
	               &__wudPowerManageEventStackCallback);
	BTM_WritePageTimeout(0x8000);
	BTM_SetDefaultLinkPolicy(HCI_ENABLE_MASTER_SLAVE_SWITCH
	                         | HCI_ENABLE_SNIFF_MODE);
	BTM_SetDefaultLinkSuperTout(3200);

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
		if (p_wcb->stdDevs[i].at_0x59 == 1)
			WUDiRegisterDevice(p_wcb->stdDevs[i].devAddr);

	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
		if (p_wcb->smpDevs[i].at_0x59 == 1)
			WUDiRegisterDevice(p_wcb->smpDevs[i].devAddr);

	BOOL intrStatus = OSDisableInterrupts();

	p_wcb->libStatus = WUD_LIB_STATUS_3;
	_wudReadNand = TRUE;

	OSRestoreInterrupts(intrStatus);

	WUDSetVisibility(FALSE, TRUE);
}

static void __wudEnableStack(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BTA_HhEnable(BTA_SEC_AUTHENTICATE, &WUDiHidHostEventCallback);

	p_wcb->stackState = WUD_STATE_STACK_GET_STORED_LINK_KEY;

	OSCreateAlarm(&p_wcb->alarm);
	OSSetPeriodicAlarm(&p_wcb->alarm, OSGetTime(), OSMillisecondsToTicks(10),
	                   &__wudStackHandler0);
}

static void __wudProcSyncEvent(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (WUDIsBusy())
		return;

	WUDSyncDeviceCallback *cb;
	BOOL intrStatus = OSDisableInterrupts();

	cb = p_wcb->syncStdCB;

	OSRestoreInterrupts(intrStatus);

	if (cb)
		(*cb)(0, 0);
	else
		WUDStartSyncDevice();
}

static void __wudProcDeleteEvent(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDClearDeviceCallback *cb;
	signed arg;
	BOOL intrStatus = OSDisableInterrupts();

	cb = p_wcb->clearDevCB;
	arg = WUDIsBusy() ? -1 : 0;

	OSRestoreInterrupts(intrStatus);

	if (cb)
		(*cb)(arg);
	else
		WUDStartClearDevice();
}

void WUDiRegisterDevice(BD_ADDR dev_addr)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDDevInfo *p_info;
	BOOL intrStatus = OSDisableInterrupts();
	p_info = WUDiGetDevInfo(dev_addr);

	OSAssert_Line(4215, p_info != NULL);
	OSAssert_Line(4216, p_wcb->devNums <= WUD_MAX_DEV_ENTRY_FOR_STD);
	OSAssert_Line(4217, p_wcb->devSmpNums <= WUD_MAX_DEV_ENTRY_FOR_SMP);

	tBTA_STATUS status __attribute__((unused)) =
		BTA_DmAddDevice(p_info->devAddr, p_info->linkKey, 0, FALSE);

	if (WUD_DEV_NAME_IS_CNT(p_info->small.devName)
	    || (WUD_DEV_NAME_IS_WBC(p_info->small.devName) && WUDIsLinkedWBC()))
	{
		tBTA_HH_DEV_DESCR devDescInfo;
		devDescInfo.dl_len = sizeof _wudWiiRemoteDescriptor;
		devDescInfo.dsc_list = _wudWiiRemoteDescriptor;

		BTA_HhAddDev(p_info->devAddr, p_info->hhAttrMask, p_info->subclass,
		             p_info->appID, devDescInfo);
	}

	if (p_info->at_0x5b == 0 || p_info->at_0x5b == 4 || p_info->at_0x5b == 2
	    || p_info->at_0x5b == 5)
	{
		p_wcb->devNums++;
	}
	else
	{
		p_wcb->devSmpNums++;
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiRemoveDevice(BD_ADDR dev_addr)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;

	BOOL intrStatus = OSDisableInterrupts();
	p_info = WUDiGetDevInfo(dev_addr);
	if (!p_info)
		goto end;

	if (WUD_DEV_NAME_IS_CNT(p_info->small.devName)
	    || (WUD_DEV_NAME_IS_WBC(p_info->small.devName) && WUDIsLinkedWBC()))
	{
		BTA_HhRemoveDev(p_info->devHandle);
	}

	tBTM_STATUS status __attribute__((unused)) =
		BTA_DmRemoveDevice(p_info->devAddr);

	if (p_info->at_0x5b == 0 || p_info->at_0x5b == 2 || p_info->at_0x5b == 4
	    || p_info->at_0x5b == 5)
	{
		p_wcb->devNums--;
	}
	else
	{
		p_wcb->devSmpNums--;
	}

	memset(p_info, 0, sizeof *p_info);

end:
	OSRestoreInterrupts(intrStatus);
}

WUDDevInfo *WUDiGetDevInfo(BD_ADDR dev_addr)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info = NULL;

	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < (int)ARRAY_LENGTH(p_wcb->stdDevs); i++)
	{
		if (WUD_BDCMP(p_wcb->stdDevs[i].devAddr, dev_addr) == 0)
		{
			p_info = &p_wcb->stdDevs[i];
			break;
		}
	}

	if (!p_info)
	{
		for (i = 0; i < (int)ARRAY_LENGTH(p_wcb->smpDevs); i++)
		{
			if (WUD_BDCMP(p_wcb->smpDevs[i].devAddr, dev_addr) == 0)
			{
				p_info = &p_wcb->smpDevs[i];
				break;
			}
		}
	}

	OSRestoreInterrupts(intrStatus);

	return p_info;
}

static WUDDevInfo *__wudGetDevInfoByIndex(int index)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	OSAssert_Line(4374, index >= 0 && index <= WUD_MAX_DEV_ENTRY);

	BOOL intrStatus = OSDisableInterrupts();

	WUDDevInfo *p_info;

// idk
#if defined(NDEBUG)
	if (0 <= (u32)index && (u32)index <= 9)
#else
	if (0 <= index && index < 10)
#endif // defined(NDEBUG)
		p_info = &p_wcb->stdDevs[index];
	else
		p_info = &p_wcb->smpDevs[index - ARRAY_LENGTH(p_wcb->stdDevs)];

	OSRestoreInterrupts(intrStatus);

	return p_info;
}

static WUDDevInfo *__wudGetNewStdDevInfo(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info = NULL;

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		if (p_wcb->stdDevs[i].at_0x59 == 0)
		{
			p_info = &p_wcb->stdDevs[i];
			break;
		}
	}

	return p_info;
}

static WUDDevInfo *__wudGetNewSmpDevInfo(void)
{
	return __rvl_wudcb.smpListTail->devInfo;
}

static WUDDevInfo *__wudGetNewDevInfo(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	WUDDevInfo *p_info = NULL;
	BOOL intrStatus = OSDisableInterrupts();

	if (p_wcb->syncType == WUD_SYNC_TYPE_STANDARD)
		p_info = __wudGetNewStdDevInfo();
	else
		p_info = __wudGetNewSmpDevInfo();

	OSRestoreInterrupts(intrStatus);

	return p_info;
}

static void __wudRemoveDevInfo(BD_ADDR dev_addr)
{
	WUDDevInfo *p_info = WUDiGetDevInfo(dev_addr);
	if (!p_info)
		return;

	BOOL intrStatus = OSDisableInterrupts();

	memset(p_info, 0, sizeof *p_info);

	OSRestoreInterrupts(intrStatus);
}

static void __wudClearDevInfos(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	memset(p_wcb->stdDevs, 0, sizeof p_wcb->stdDevs);
	memset(p_wcb->smpDevs, 0, sizeof p_wcb->smpDevs);

	p_wcb->devNums = 0;
	p_wcb->devSmpNums = 0;

	p_wcb->connectedNum = 0;
	p_wcb->linkedNum = 0;
	p_wcb->syncedNum = 0;

	OSRestoreInterrupts(intrStatus);
}

static u8 __wudGetStdDevNumber(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	u8 num = p_wcb->devNums;

	OSRestoreInterrupts(intrStatus);

	return num;
}

static u8 __wudGetSmpDevNumber(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	u8 num = p_wcb->devSmpNums;

	OSRestoreInterrupts(intrStatus);

	return num;
}

static u8 __wudGetConnectionNumber(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	u8 num = p_wcb->connectedNum;

	OSRestoreInterrupts(intrStatus);

	return num;
}

static u8 __wudGetLinkNumber(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	u8 num = p_wcb->linkedNum;

	OSRestoreInterrupts(intrStatus);

	return num;
}

void WUDiMoveTopSmpDevInfoPtr(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		if (WUD_BDCMP(p_wcb->smpList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		if (WUD_BDCMP(p_wcb->smpListHead->devInfo->devAddr,
		              p_wcb->smpList[i].devInfo->devAddr)
		    == 0)
		{
			break;
		}

		p_wcb->smpList[i].prev->next = p_wcb->smpList[i].next;

		if (WUD_BDCMP(p_wcb->smpListTail->devInfo->devAddr,
		              p_wcb->smpList[i].devInfo->devAddr)
		    == 0)
		{
			p_wcb->smpListTail = p_wcb->smpList[i].prev;
		}
		else
		{
			p_wcb->smpList[i].next->prev = p_wcb->smpList[i].prev;
		}

		p_wcb->smpList[i].next = p_wcb->smpListHead;
		p_wcb->smpListHead->prev = &p_wcb->smpList[i];
		p_wcb->smpListHead = &p_wcb->smpList[i];

		p_wcb->smpList[i].prev = NULL;

		break;
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveBottomSmpDevInfoPtr(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		if (WUD_BDCMP(p_wcb->smpList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		if (WUD_BDCMP(p_wcb->smpListTail->devInfo->devAddr,
		              p_wcb->smpList[i].devInfo->devAddr)
		    == 0)
		{
			break;
		}

		p_wcb->smpList[i].next->prev = p_wcb->smpList[i].prev;

		if (WUD_BDCMP(p_wcb->smpListHead->devInfo->devAddr,
		              p_wcb->smpList[i].devInfo->devAddr)
		    == 0)
		{
			p_wcb->smpListHead = p_wcb->smpList[i].next;
		}
		else
		{
			p_wcb->smpList[i].prev->next = p_wcb->smpList[i].next;
		}

		p_wcb->smpList[i].prev = p_wcb->smpListTail;
		p_wcb->smpListTail->next = &p_wcb->smpList[i];
		p_wcb->smpListTail = &p_wcb->smpList[i];

		p_wcb->smpList[i].next = NULL;

		break;
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveTopOfDisconnectedSmpDevice(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	int i;

	BOOL intrStatus = OSDisableInterrupts();

	struct WUDDevInfoList *p_list;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
	{
		if (WUD_BDCMP(p_wcb->smpList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		for (p_list = p_wcb->smpListHead; p_list; p_list = p_list->next)
		{
			if (WUD_BDCMP(p_list->devInfo->devAddr, dev_info->devAddr) == 0)
				continue;

			if (p_list->devInfo->at_0x59 != 1 && p_list->devInfo->at_0x59 != 0)
				continue;

			if (WUD_BDCMP(p_wcb->smpListHead->devInfo->devAddr,
			              p_wcb->smpList[i].devInfo->devAddr)
			    == 0)
			{
				if (p_list == p_wcb->smpListHead->next)
					break;

				p_wcb->smpListHead = p_wcb->smpList[i].next;
			}
			else
			{
				p_wcb->smpList[i].prev->next = p_wcb->smpList[i].next;
			}

			p_wcb->smpList[i].next->prev = p_wcb->smpList[i].prev;

			if (p_list != p_wcb->smpListHead)
			{
				p_wcb->smpList[i].prev = p_list->prev;
				p_wcb->smpList[i].next = p_list;

				p_list->prev->next = &p_wcb->smpList[i];
				p_list->prev = &p_wcb->smpList[i];
			}
			else
			{
				p_wcb->smpList[i].prev = p_list;
				p_wcb->smpList[i].next = p_list->next;

				p_list->next->prev = &p_wcb->smpList[i];
				p_list->next = &p_wcb->smpList[i];
			}

			break;
		}
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveTopStdDevInfoPtr(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		if (WUD_BDCMP(p_wcb->stdList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		if (WUD_BDCMP(p_wcb->stdListHead->devInfo->devAddr,
		              p_wcb->stdList[i].devInfo->devAddr)
		    == 0)
		{
			break;
		}

		p_wcb->stdList[i].prev->next = p_wcb->stdList[i].next;

		if (WUD_BDCMP(p_wcb->stdListTail->devInfo->devAddr,
		              p_wcb->stdList[i].devInfo->devAddr)
		    == 0)
		{
			p_wcb->stdListTail = p_wcb->stdList[i].prev;
		}
		else
		{
			p_wcb->stdList[i].next->prev = p_wcb->stdList[i].prev;
		}

		p_wcb->stdList[i].next = p_wcb->stdListHead;
		p_wcb->stdListHead->prev = &p_wcb->stdList[i];
		p_wcb->stdListHead = &p_wcb->stdList[i];

		p_wcb->stdList[i].prev = NULL;

		break;
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveBottomStdDevInfoPtr(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	int i;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		if (WUD_BDCMP(p_wcb->stdList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		if (WUD_BDCMP(p_wcb->stdListTail->devInfo->devAddr,
		              p_wcb->stdList[i].devInfo->devAddr)
		    == 0)
		{
			break;
		}

		p_wcb->stdList[i].next->prev = p_wcb->stdList[i].prev;

		if (WUD_BDCMP(p_wcb->stdListHead->devInfo->devAddr,
		              p_wcb->stdList[i].devInfo->devAddr)
		    == 0)
		{
			p_wcb->stdListHead = p_wcb->stdList[i].next;
		}
		else
		{
			p_wcb->stdList[i].prev->next = p_wcb->stdList[i].next;
		}

		p_wcb->stdList[i].prev = p_wcb->stdListTail;
		p_wcb->stdListTail->next = &p_wcb->stdList[i];
		p_wcb->stdListTail = &p_wcb->stdList[i];

		p_wcb->stdList[i].next = NULL;

		break;
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveTopOfDisconnectedStdDevice(WUDDevInfo *devInfo)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	int i;

	BOOL intrStatus = OSDisableInterrupts();

	struct WUDDevInfoList *p_list;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		if (WUD_BDCMP(p_wcb->stdList[i].devInfo->devAddr, devInfo->devAddr)
		    != 0)
		{
			continue;
		}

		for (p_list = p_wcb->stdListHead; p_list; p_list = p_list->next)
		{
			if (WUD_BDCMP(p_list->devInfo->devAddr, devInfo->devAddr) == 0)
				continue;

			if (p_list->devInfo->at_0x59 != 1 && p_list->devInfo->at_0x59 != 0
			    && (WUD_DEV_NAME_IS_CNT(p_list->devInfo->small.devName)
			        || !WUDIsLinkedWBC()))
			{
				continue;
			}

			if (WUD_BDCMP(p_wcb->stdListHead->devInfo->devAddr,
			              p_wcb->stdList[i].devInfo->devAddr)
			    == 0)
			{
				if (p_list == p_wcb->stdListHead->next)
					break;

				p_wcb->stdListHead = p_wcb->stdList[i].next;
			}
			else
			{
				p_wcb->stdList[i].prev->next = p_wcb->stdList[i].next;
			}

			p_wcb->stdList[i].next->prev = p_wcb->stdList[i].prev;

			if (p_list != p_wcb->stdListHead)
			{
				p_wcb->stdList[i].prev = p_list->prev;
				p_wcb->stdList[i].next = p_list;

				p_list->prev->next = &p_wcb->stdList[i];
				p_list->prev = &p_wcb->stdList[i];
			}
			else
			{
				p_wcb->stdList[i].prev = p_list;
				p_wcb->stdList[i].next = p_list->next;

				p_list->next->prev = &p_wcb->stdList[i];
				p_list->next = &p_wcb->stdList[i];
			}

			break;
		}
	}

	OSRestoreInterrupts(intrStatus);
}

void WUDiMoveTopOfUnusedStdDevice(WUDDevInfo *dev_info)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	int i;

	BOOL intrStatus = OSDisableInterrupts();

	struct WUDDevInfoList *p_list;
	for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_STD; i++)
	{
		if (WUD_BDCMP(p_wcb->stdList[i].devInfo->devAddr, dev_info->devAddr)
		    != 0)
		{
			continue;
		}

		for (p_list = p_wcb->stdListHead; p_list; p_list = p_list->next)
		{
			if (WUD_BDCMP(p_list->devInfo->devAddr, dev_info->devAddr) == 0)
				continue;

			if (p_list->devInfo->at_0x59 != 0 && p_list != p_wcb->stdListTail)
				continue;

			if (WUD_BDCMP(p_wcb->stdListHead->devInfo->devAddr,
			              p_wcb->stdList[i].devInfo->devAddr)
			    == 0)
			{
				if (p_list == p_wcb->stdListHead->next)
					break;

				p_wcb->stdListHead = p_wcb->stdList[i].next;
			}
			else
			{
				p_wcb->stdList[i].prev->next = p_wcb->stdList[i].next;
			}

			p_wcb->stdList[i].next->prev = p_wcb->stdList[i].prev;

			if (p_list == p_wcb->stdListTail && p_list->devInfo->at_0x59 != 0)
			{
				p_wcb->stdList[i].prev = p_list;
				p_wcb->stdList[i].next = NULL;

				p_list->next = &p_wcb->stdList[i];

				p_wcb->stdListTail = &p_wcb->stdList[i];
			}
			else if (p_list != p_wcb->stdListHead)
			{
				p_wcb->stdList[i].prev = p_list->prev;
				p_wcb->stdList[i].next = p_list;

				p_list->prev->next = &p_wcb->stdList[i];
				p_list->prev = &p_wcb->stdList[i];
			}
			else
			{
				p_wcb->stdList[i].prev = p_list;
				p_wcb->stdList[i].next = p_list->next;

				p_list->next->prev = &p_wcb->stdList[i];
				p_list->next = &p_wcb->stdList[i];
			}

			break;
		}
	}

	OSRestoreInterrupts(intrStatus);
}

static WUDDevInfo *__wudGetOldestSmpDevice(void)
{
	return __rvl_wudcb.smpListTail->devInfo;
}

static WUDDevInfo *__wudGetOldestStdDevice(void)
{
	return __rvl_wudcb.stdListTail->devInfo;
}

BOOL WUDIsBusy(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	if (p_wcb->syncState == WUD_STATE_START
	    && p_wcb->deleteState == WUD_STATE_START
	    && p_wcb->stackState == WUD_STATE_STACK_INITIALIZED
	    && p_wcb->initState == WUD_STATE_INIT_INITIALIZED)
	{
		OSRestoreInterrupts(intrStatus);
		return FALSE;
	}
	else
	{
		OSRestoreInterrupts(intrStatus);
		return TRUE;
	}
}

static void __wudCleanupStackCallback(tBTA_STATUS status)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	if (status == BTA_SUCCESS)
	{
		_wudInitialized = FALSE;
		p_wcb->libStatus = WUD_LIB_STATUS_0;
	}
}

static void __wudSecurityEventStackCallback(tBTA_DM_SEC_EVT event,
                                            tBTA_DM_SEC *p_data)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;
	u8 i;

	tBTA_DM_ENABLE *dmEnable;
	tBTA_DM_LINK_UP *dmLinkUp;
	tBTA_DM_LINK_DOWN *dmLinkDown;
	tBTA_DM_PIN_REQ *dmPinReq;
	tBTA_DM_AUTH_CMPL *dmAuthCmpl;

	switch (event)
	{
	case BTA_DM_ENABLE_EVT:
		dmEnable = &p_data->enable;
		WUD_BDCPY(p_wcb->hostAddr, dmEnable->bd_addr);
		__wudEnableStack();

		p_wcb->libStatus = WUD_LIB_STATUS_2;

		break;

	case BTA_DM_DISABLE_EVT:
		BTA_CleanUp(__wudCleanupStackCallback);

		break;

	case BTA_DM_PIN_REQ_EVT:
		dmPinReq = &p_data->pin_req;
		__wudSetPinCode(dmPinReq->bd_addr);

		break;

	case BTA_DM_AUTH_CMPL_EVT:
		dmAuthCmpl = &p_data->auth_cmpl;

		if (dmAuthCmpl->key_type == HCI_LKEY_TYPE_COMBINATION)
			break;

		p_info = WUDiGetDevInfo(dmAuthCmpl->bd_addr);

		if (WUD_BDCMP(_wudDiscWork.devAddr, dmAuthCmpl->bd_addr) == 0)
		{
			_wudDiscWork.at_0x59 = 12;

			if (!p_info)
				p_info = &_wudDiscWork;
		}

		OSAssert_Line(5140, p_info != NULL);

		memcpy(p_info->linkKey, dmAuthCmpl->key, LINK_KEY_LEN);
		break;

	case BTA_DM_AUTHORIZE_EVT:
	{
		tBTA_DM_AUTHORIZE *dmAuthorize __attribute__((unused)) =
			&p_data->authorize;
	}
		break;

	case BTA_DM_LINK_UP_EVT:
		dmLinkUp = &p_data->link_up;

		p_info = WUDiGetDevInfo(dmLinkUp->bd_addr);

		if (!p_info && WUD_BDCMP(dmLinkUp->bd_addr, _wudDiscWork.devAddr) == 0)
			p_info = &_wudDiscWork;

		if (!p_info || __wudGetLinkNumber() == WUD_MAX_CHANNELS)
		{
			btm_remove_acl(dmLinkUp->bd_addr);
			break;
		}

		p_info->at_0x59 = p_info->at_0x59 == 2 ? 12 : 3;
		p_wcb->linkedNum++;

		break;

	case BTA_DM_LINK_DOWN_EVT:
		dmLinkDown = &p_data->link_down;

		p_info = WUDiGetDevInfo(dmLinkDown->bd_addr);
		if (p_info)
		{
			p_info->at_0x59 = 1;
			p_wcb->linkedNum--;

			if (WUD_BDCMP(_wudDiscWork.devAddr, dmLinkDown->bd_addr) == 0)
				p_wcb->syncState = WUD_STATE_ERROR;

			if (dmLinkDown->status == HCI_ERR_PEER_POWER_OFF)
			{
				for (i = 0; i < WUD_MAX_CHANNELS; i++)
				{
					if (WUD_BDCMP(_scArray.devices[10 + i].devAddr,
					              dmLinkDown->bd_addr)
					    == 0)
					{
						memset(&_scArray.devices[10 + i], 0,
						       sizeof _scArray.devices[10 + i]);
						_scFlush = TRUE;
					}
				}
			}
		}
		else if (WUD_BDCMP(_wudDiscWork.devAddr, dmLinkDown->bd_addr) == 0)
		{
			p_wcb->syncState = WUD_STATE_ERROR;
			p_wcb->linkedNum--;
		}

		if (p_wcb->linkedNum <= 255 && p_wcb->linkedNum >= 250)
		{
			OSReport("WARNING: link num count is reset.\n");
			p_wcb->linkedNum = 0;
		}
		break;

	case BTA_DM_SIG_STRENGTH_EVT:
	{
		tBTA_DM_SIG_STRENGTH *dmSigStrength __attribute__((unused)) =
			&p_data->sig_strength;
	}
		break;

	case BTA_DM_BUSY_LEVEL_EVT:
	{
		tBTA_DM_BUSY_LEVEL *dmBusyLevel __attribute__((unused)) =
			&p_data->busy_level;
	}
		break;
	}
}

static void __wudSearchEventStackCallback(tBTA_DM_SEARCH_EVT event,
                                          tBTA_DM_SEARCH *p_data)
{
	int timeout;

	switch (event)
	{
	case BTA_DM_INQ_RES_EVT:
	{
		tBTA_DM_INQ_RES *dmInqRes = &p_data->inq_res;

		_wudDiscRssi = dmInqRes->rssi;

		if (__rvl_wudcb.syncSkipChecks == 1
		    || (__rvl_wudcb.syncSkipChecks == 0 && __wudGetLinkNumber() < 3))
		{
			timeout = 0x1900;
		}
		else
		{
			timeout = 0x8000;
		}

		BTM_WritePageTimeout(timeout);
	}
		break;

	case BTA_DM_DISC_RES_EVT:
	{
		tBTA_DM_DISC_RES *dmDiscRes = &p_data->disc_res;

		WUD_BDCPY(_wudDiscResp.devAddr, dmDiscRes->bd_addr);
		memcpy(_wudDiscResp.at_0x006, dmDiscRes->bd_name,
		       sizeof _wudDiscResp.at_0x006);

		_wudDiscResp.services = dmDiscRes->services;
		_wudDiscNumResps++;
	}
		break;

	case BTA_DM_DISC_BLE_RES_EVT:
		__rvl_wudcb.syncState = WUD_STATE_SYNC_CHECK_SEARCH_RESULT;
		break;

	case BTA_DM_DISC_CMPL_EVT:
		__wudResetAuthFailCount();
		__wudClearDiscoverResult();

		__rvl_wudcb.syncState = WUD_STATE_SYNC_CHECK_SEARCH_RESULT;
		break;
	}
}

static void __wudVendorSpecificEventStackCallback(UINT8 len
                                                  __attribute__((unused)),
                                                  UINT8 *p)
{
	(void)len; // mhm

	u8 result = p[0];

	wud_cb_st *p_wcb = &__rvl_wudcb;

	switch (result)
	{
	case 8:
		__wudProcSyncEvent();
		break;

	case 9:
		__wudProcDeleteEvent();
		break;

	case 10:
		p_wcb->unk_0x709 = p[1];
		break;

	case 16:
		OSError_Line(5387, "MODULE FATAL ERROR\n");
	}
}

static void __wudDeviceStatusEventStackCallback(tBTM_DEV_STATUS status)
{
	if (status == BTM_DEV_STATUS_CMD_TOUT)
	{
		OSReport("---- WARNING: USB FATAL ERROR! ----\n"); // usb ???
		WUDiShowFatalErrorMessage();
	}
}

static void __wudLinkKeyEventStackCallback(void *p1)
{
	tBTM_BD_ADDR_LINK_KEY_PAIR *p_pair;

	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info;
	int i;

	tBTM_STORED_LINK_KEYS_EVT *data = p1;

	tBTM_READ_STORED_LINK_KEY_COMPLETE *p_r_cmpl __attribute__((unused));
	tBTM_WRITE_STORED_LINK_KEY_COMPLETE *p_w_cmpl;
	tBTM_DELETE_STORED_LINK_KEY_COMPLETE *p_d_cmpl;

	tBTM_RETURN_LINK_KEYS_EVT *p_ret_cmpl;

	switch (data->event)
	{
	case BTM_CB_EVT_RETURN_LINK_KEYS:
		p_ret_cmpl = p1;

		p_pair = (tBTM_BD_ADDR_LINK_KEY_PAIR *)(p_ret_cmpl + 1);
		i = 0;
		while (i < p_ret_cmpl->num_keys)
		{
			p_info = WUDiGetDevInfo(p_pair->bd_addr);
			if (!p_info)
			{
				p_info = __wudGetNewDevInfo();
				if (!p_info)
				{
					for (i = 0; i < WUD_MAX_DEV_ENTRY_FOR_SMP; i++)
					{
						if (p_wcb->smpDevs[i].at_0x59 == 0)
						{
							p_info = &p_wcb->smpDevs[i];
							break;
						}
					}
				}

				if (p_info)
				{
					p_info->at_0x5c = 1;
					p_info->at_0x59 = 1;

					WUD_BDCPY(p_info->devAddr, p_pair->bd_addr);
					memcpy(p_info->linkKey, p_pair->link_key, LINK_KEY_LEN);
				}
			}
			else
			{
				WUD_BDCPY(p_info->devAddr, p_pair->bd_addr);
				memcpy(p_info->linkKey, p_pair->link_key, LINK_KEY_LEN);

				if (p_info->at_0x5c == 2)
					p_info->at_0x5c = 3;

				WUD_BDCPY(p_wcb->pairAddr, p_pair->bd_addr);
			}

			p_pair++;
			i++;
		}

		break;

	case BTM_CB_EVT_READ_STORED_LINK_KEYS:
		p_r_cmpl = p1;

		p_wcb->linkKeyState = WUD_STATE_START;
		break;

	case BTM_CB_EVT_WRITE_STORED_LINK_KEYS:
		p_w_cmpl = p1;

		OSAssert_Line(5527, p_w_cmpl->num_keys != 0);
		p_wcb->linkKeyState = WUD_STATE_START;
		break;

	case BTM_CB_EVT_DELETE_STORED_LINK_KEYS:
		p_d_cmpl = p1;

		(void)!(u16)p_d_cmpl->num_keys; // What

		p_wcb->linkKeyState = WUD_STATE_START;
		break;

	default:
		OSError_Line(5544, "Unknown event\n");
	}
}

static void __wudPowerManageEventStackCallback(
	BD_ADDR p_bda, tBTM_PM_STATUS status, UINT16 value __attribute__((unused)),
	UINT8 hci_status __attribute__((unused)))
{
	wud_cb_st *p_wcb __attribute__((unused)) = &__rvl_wudcb;

	WUDDevInfo *p_info = WUDiGetDevInfo(p_bda);
	if (!p_info)
	{
		if (WUD_BDCMP(_wudDiscWork.devAddr, p_bda) == 0)
			p_info = &_wudDiscWork;
		else
			return;
	}

	OSAssert_Line(5584, p_info != NULL);

	switch (status)
	{
	case BTM_PM_STS_ACTIVE:
		p_info->at_0x59 = 8;
		break;

	case BTM_PM_STS_SNIFF:
		p_info->at_0x59 = 9;
		break;
	}
}

static void __wudResetAuthFailCount(void)
{
	BTM_VendorSpecificCommand(BT_VSC_NINTENDO_WRITE_PATCH,
	                          sizeof _wudResetAuthCountCmd,
	                          _wudResetAuthCountCmd, NULL);
}

static WUDDevInfo *__wudGetWbcDevice(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;
	WUDDevInfo *p_info = NULL;
	struct WUDDevInfoList *p_list;

	BOOL intrStatus = OSDisableInterrupts();

	for (p_list = p_wcb->stdListHead; p_list; p_list = p_list->next)
		if (WUD_DEV_NAME_IS_WBC(p_list->devInfo->small.devName))
			p_info = p_list->devInfo;

	OSRestoreInterrupts(intrStatus);

	return p_info;
}

BD_ADDR_PTR _WUDGetDevAddr(UINT8 dev_handle)
{
	BD_ADDR_PTR devAddr;

	BOOL intrStatus = OSDisableInterrupts();

	if (dev_handle < WUD_MAX_DEV_ENTRY)
		devAddr = WUDiGetDevAddrForHandle(dev_handle);
	else
		devAddr = NULL;

	OSRestoreInterrupts(intrStatus);

	return devAddr;
}

u16 _WUDGetQueuedSize(WUDDevHandle dev_handle)
{
	u16 queuedSize;

	BOOL intrStatus = OSDisableInterrupts();

	if (DEV_HANDLE_BOUNDS_CHECK(dev_handle))
		queuedSize = WUDiGetQueueSizeForHandle(dev_handle);
	else
		queuedSize = 0;

	OSRestoreInterrupts(intrStatus);

	return queuedSize;
}

u16 _WUDGetNotAckedSize(WUDDevHandle dev_handle)
{
	u16 notAckedSize;

	BOOL intrStatus = OSDisableInterrupts();

	if (DEV_HANDLE_BOUNDS_CHECK(dev_handle))
		notAckedSize = WUDiGetNotAckNumForHandle(dev_handle);
	else
		notAckedSize = 0;

	OSRestoreInterrupts(intrStatus);

	return notAckedSize;
}

u8 _WUDGetLinkNumber(void)
{
	wud_cb_st *p_wcb = &__rvl_wudcb;

	BOOL intrStatus = OSDisableInterrupts();

	u8 linkedNum = p_wcb->linkedNum;

	OSRestoreInterrupts(intrStatus);

	return linkedNum;
}

WUDDevInfo *WUDiGetDiscoverDevice(void)
{
	return &_wudDiscWork;
}

void WUDSetDeviceHistory(WUDChannel chan, BD_ADDR dev_addr)
{
	if (!dev_addr)
	{
		memset(&_scArray.devices[10 + chan], 0,
		       sizeof _scArray.devices[10 + chan]);
	}
	else
	{
		WUD_BDCPY(_scArray.devices[10 + chan].devAddr, dev_addr);
	}

	_scFlush = TRUE;
}

BOOL WUDIsLatestDevice(WUDChannel chan, BD_ADDR devAddr)
{
	if (!devAddr)
		return FALSE;

	if (WUD_BDCMP(_scArray.devices[10 + chan].devAddr, devAddr) == 0)
		return TRUE;
	else
		return FALSE;
}

void WUDUpdateSCSetting(void)
{
	if (!_scFlush)
		return;

	if (SCSetBtDeviceInfoArray(&_scArray))
	{
		SCFlushAsync(NULL);
		_scFlush = FALSE;
	}
}

void WUDiSetDevAddrForHandle(UINT8 dev_handle, BD_ADDR dev_addr)
{
	_dev_handle_to_bda[dev_handle] = dev_addr;
}

BD_ADDR_PTR WUDiGetDevAddrForHandle(UINT8 dev_handle)
{
	return _dev_handle_to_bda[dev_handle];
}

void WUDiSetQueueSizeForHandle(UINT8 dev_handle, u16 size)
{
	_dev_handle_queue_size[dev_handle] = size;
}

u16 WUDiGetQueueSizeForHandle(UINT8 dev_handle)
{
	return _dev_handle_queue_size[dev_handle];
}

void WUDiSetNotAckNumForHandle(UINT8 dev_handle, u16 count)
{
	_dev_handle_notack_num[dev_handle] = count;
}

u16 WUDiGetNotAckNumForHandle(UINT8 dev_handle)
{
	return _dev_handle_notack_num[dev_handle];
}

void WUDiShowFatalErrorMessage(void)
{
	return;
}
#endif
