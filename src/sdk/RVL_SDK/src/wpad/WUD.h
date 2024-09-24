#ifndef RVL_SDK_WPAD_INTERNAL_WUD_H
#define RVL_SDK_WPAD_INTERNAL_WUD_H

#include <revolution/wpad/WUD.h>

/*******************************************************************************
 * headers
 */

#include <string.h>

#include <types.h>

#include <revolution/bte/context_bte.h>
#include <revolution/os/OSAlarm.h>

/*******************************************************************************
 * macros
 */

#define WUD_BDCMP(lhs_, rhs_)				memcmp(lhs_, rhs_, BD_ADDR_LEN)
#define WUD_BDCPY(dst_, src_)				memcpy(dst_, src_, BD_ADDR_LEN)

#define WUD_DEV_NAME_IS(devName_, str_)		(memcmp(devName_, str_, sizeof (str_) - 1) == 0)

#define WUD_DEV_NAME_IS_CNT(devName_)		WUD_DEV_NAME_IS(devName_, "Nintendo RVL-CNT")
#define WUD_DEV_NAME_IS_CNT_01(devName_)	WUD_DEV_NAME_IS(devName_, "Nintendo RVL-CNT-01")
#define WUD_DEV_NAME_IS_WBC(devName_)		WUD_DEV_NAME_IS(devName_, "Nintendo RVL-WBC")

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

typedef u8 WUDState;
enum WUDState_et
{
	WUD_STATE_START								= 0,

	WUD_STATE_WII_FIT_OPEN						= 100,
	WUD_STATE_WII_FIT_SEEK						= 101,
	WUD_STATE_WII_FIT_UPDATE					= 102,
	WUD_STATE_WII_FIT_CLOSE						= 103,

	WUD_STATE_ERROR								= 255
};

typedef WUDState WUDSyncState;
enum WUDSyncState_et
{
	WUD_STATE_SYNC_PREPARE_SEARCH				=  1,
	WUD_STATE_SYNC_START_SEARCH					=  2,
	WUD_STATE_SYNC_WAIT_FOR_SEARCH_RESULT		=  3,
	WUD_STATE_SYNC_CHECK_SEARCH_RESULT			=  4,
	WUD_STATE_SYNC_IS_EXISTED_DEVICE			=  5,
	WUD_STATE_SYNC_6							=  6,
	WUD_STATE_SYNC_STORED_LINK_KEY_TO_EEPROM	=  7,
	WUD_STATE_SYNC_WAIT_FOR_STORING				=  8,
//	WUD_STATE_SYNC_9							=  9,
	WUD_STATE_SYNC_WAIT_FOR_READING				= 10,
	WUD_STATE_SYNC_11							= 11,
	WUD_STATE_SYNC_12							= 12,
	WUD_STATE_SYNC_13							= 13,
//	WUD_STATE_SYNC_DONE is at the end
	WUD_STATE_SYNC_TRY_CONNECT					= 15,
	WUD_STATE_SYNC_PREPARE_FOR_EXISTED_DEVICE	= 16,
	WUD_STATE_SYNC_PREPARE_FOR_UNKNOWN_DEVICE	= 17,
	WUD_STATE_SYNC_REGISTER_DEVICE				= 18,
	WUD_STATE_SYNC_VIRGIN_SIMPLE				= 19,
	WUD_STATE_SYNC_VIRGIN_STANDARD				= 20,
	WUD_STATE_SYNC_CHANGE_SIMPLE_TO_STANDARD	= 21,
	WUD_STATE_SYNC_STORED_DEV_INFO_TO_NAND		= 22,
	WUD_STATE_SYNC_COMPLETE						= 23,
	WUD_STATE_SYNC_WAIT_FOR_INCOMING			= 24,
	WUD_STATE_SYNC_SC_FLUSH						= 25,
	WUD_STATE_SYNC_26							= 26,
//	WUD_STATE_SYNC_27							= 27,
//	WUD_STATE_SYNC_28							= 28,
	WUD_STATE_SYNC_WAIT_FOR_START_SEARCH		= 29,

	WUD_STATE_SYNC_DONE							= 14
};

typedef WUDState WUDDeleteState;
enum WUDDeleteState_et
{
	WUD_STATE_DELETE_DISALLOW_INCOMING			= 1,
	WUD_STATE_DELETE_DISCONNECT_ALL				= 2,
	WUD_STATE_DELETE_CLEANUP_DATABASE			= 3,
//	WUD_STATE_DELETE_4							= 4,
	WUD_STATE_DELETE_CLEANUP_SETTING			= 5,
	WUD_STATE_DELETE_6							= 6,
	WUD_STATE_DELETE_7							= 7,

	WUD_STATE_DELETE_DONE						= 8
};

typedef WUDState WUDLinkKeyState;
enum WUDLinkKeyState_et
{
	WUD_STATE_LINK_KEY_READING					= 1,
	WUD_STATE_LINK_KEY_WRITING					= 2,
	WUD_STATE_LINK_KEY_DELETING					= 3,
};

typedef WUDState WUDStackState;
enum WUDStackState_et
{
	WUD_STATE_STACK_GET_STORED_LINK_KEY			= 1,
	WUD_STATE_STACK_CHECK_DEVICE_INFO			= 2,

	WUD_STATE_STACK_DONE						= 3,
	WUD_STATE_STACK_INITIALIZED					= 4	// see __wudStackDone and WUDIsBusy
};

typedef WUDState WUDInitState;
enum WUDInitState_et
{
	WUD_STATE_INIT_WAIT_FOR_DEVICE_UP			= 1,
	WUD_STATE_INIT_WAIT_FOR_INITIALIZATION		= 2,
	WUD_STATE_INIT_GET_DEV_INFO_FROM_WII_FIT	= 3,
	WUD_STATE_INIT_GET_DEV_INFO					= 4,
	WUD_STATE_INIT_5							= 5,

	WUD_STATE_INIT_DONE							= 6,
	WUD_STATE_INIT_INITIALIZED					= 7	// see __wudInitDone and WUDIsBusy
};

typedef WUDState WUDShutdownState;
enum WUDShutdownState_et
{
	WUD_STATE_SHUTDOWN_STORE_SETTINGS			= 1,
	WUD_STATE_SHUTDOWN_FLUSH_SETTINGS			= 2,

	WUD_STATE_SHUTDOWN_DONE						= 3
};

struct WUDDevInfoList
{
	WUDDevInfo				*devInfo;	// size 0x04, offset 0x00
	struct WUDDevInfoList	*prev;		// size 0x04, offset 0x04
	struct WUDDevInfoList	*next;		// size 0x04, offset 0x08
}; // size 0x0c

typedef struct /* possibly untagged, like kpad */
{
	WUDSyncDeviceCallback	*syncStdCB;							// size 0x004, offset 0x000
	WUDSyncDeviceCallback	*syncSmpCB;							// size 0x004, offset 0x004
	WUDClearDeviceCallback	*clearDevCB;						// size 0x004, offset 0x008

	WUDSyncState			syncState;							// size 0x001, offset 0x00c
	WUDDeleteState			deleteState;						// size 0x001, offset 0x00d
	WUDLinkKeyState			linkKeyState;						// size 0x001, offset 0x00e
	WUDStackState			stackState;							// size 0x001, offset 0x00f
	WUDInitState			initState;							// size 0x001, offset 0x010
	WUDShutdownState		shutdownState;						// size 0x001, offset 0x011

	u8						devNums;							// size 0x001, offset 0x012 /* name known from asserts */
	u8						devSmpNums;							// size 0x001, offset 0x013 /* name known from asserts */

	struct WUDDevInfoList	*smpListHead;						// size 0x004, offset 0x014
	struct WUDDevInfoList	*smpListTail;						// size 0x004, offset 0x018
	struct WUDDevInfoList	smpList[WUD_MAX_DEV_ENTRY_FOR_SMP];	// size 0x048, offset 0x01c

	struct WUDDevInfoList	*stdListHead;						// size 0x004, offset 0x064
	struct WUDDevInfoList	*stdListTail;						// size 0x004, offset 0x068
	struct WUDDevInfoList	stdList[WUD_MAX_DEV_ENTRY_FOR_STD];	// size 0x048, offset 0x06c

	WUDDevInfo				stdDevs[WUD_MAX_DEV_ENTRY_FOR_STD];	// size 0x3c0, offset 0x0e4
	WUDDevInfo				smpDevs[WUD_MAX_DEV_ENTRY_FOR_SMP];	// size 0x240, offset 0x4a4

	u8						connectedNum;						// size 0x001, offset 0x6e4
	u8						linkedNum;							// size 0x001, offset 0x6e5
	u8						syncedNum;							// size 0x001, offset 0x6e6

	u8						syncSkipChecks;						// size 0x001, offset 0x6e7	// maybe? it also adds some checks though???
	s8						syncLoopNum;						// size 0x001, offset 0x6e8	// implied by usage (see __wudSyncPrepareSearch) and location of stripped symbol WUDSetSyncLoopNum near other members
	WUDSyncType				syncType;							// size 0x001, offset 0x6e9

	u8						connectable;						// size 0x001, offset 0x6ea
	u8						discoverable;						// size 0x001, offset 0x6eb	// implied by usage and WUDGetDiscoverable being right before WUDGetConnectable

	WUDHidReceiveCallback	*hidRecvCB;							// size 0x004, offset 0x6ec
	WUDHidConnectCallback	*hidConnCB;							// size 0x004, offset 0x6f0

	WUDAllocFunc			*allocFunc;							// size 0x004, offset 0x6f4
	WUDFreeFunc				*freeFunc;							// size 0x004, offset 0x6f8

	BD_ADDR					pairAddr;							// size 0x006, offset 0x6fc
	BD_ADDR					hostAddr;							// size 0x006, offset 0x702	// name comes from stripped symbol _WUDGetHostAddr

	s8						libStatus;							// size 0x001, offset 0x708

	char unsigned			unk_0x709;							// size 0x001, offset 0x709	/* unknown */
	UINT8					pmID;								// size 0x001, offset 0x70a
	s8						syncRssi;							// size 0x001, offset 0x70b	// implied by usage and stripped symbols _WUD[GS]etSyncRssi
	byte_t					__pad0[4]; // alignment?
	OSAlarm					alarm;								// size 0x030, offset 0x710
	u32						hhFlags;							// size 0x004, offset 0x740	// some flags maybe?

	// see WUDGetBufferStatus
	u16						bufferStatus0;						// size 0x002, offset 0x744
	u16						bufferStatus1;						// size 0x002, offset 0x746

	s8						initWaitDeviceUpFrames;				// size 0x001, offset 0x748
	s8						waitStartSearchFrames;				// size 0x001, offset 0x749
	s16						waitIncomingFrames;					// size 0x002, offset 0x74a
	byte_t					__pad1[4]; // alignment?
} wud_cb_st; // size 0x750

/*******************************************************************************
 * external globals
 */

extern wud_cb_st __rvl_wudcb;

/*******************************************************************************
 * functions
 */

void WUDiRegisterDevice(BD_ADDR dev_addr);
void WUDiRemoveDevice(BD_ADDR dev_addr);
WUDDevInfo *WUDiGetDevInfo(BD_ADDR dev_addr);

void WUDiMoveTopSmpDevInfoPtr(WUDDevInfo *dev_info);
void WUDiMoveBottomSmpDevInfoPtr(WUDDevInfo *dev_info);
void WUDiMoveTopOfDisconnectedSmpDevice(WUDDevInfo *dev_info);
void WUDiMoveTopStdDevInfoPtr(WUDDevInfo *dev_info);
void WUDiMoveBottomStdDevInfoPtr(WUDDevInfo *dev_info);
void WUDiMoveTopOfDisconnectedStdDevice(WUDDevInfo *dev_info);
void WUDiMoveTopOfUnusedStdDevice(WUDDevInfo *dev_info);

BD_ADDR_PTR _WUDGetDevAddr(UINT8 dev_handle);
u16 _WUDGetQueuedSize(WUDDevHandle dev_handle);
u16 _WUDGetNotAckedSize(WUDDevHandle dev_handle);
u8 _WUDGetLinkNumber(void);

WUDDevInfo *WUDiGetDiscoverDevice(void);

void WUDiSetDevAddrForHandle(UINT8 dev_handle, BD_ADDR dev_addr);
BD_ADDR_PTR WUDiGetDevAddrForHandle(UINT8 dev_handle);
void WUDiSetQueueSizeForHandle(UINT8 dev_handle, u16 size);
u16 WUDiGetQueueSizeForHandle(UINT8 dev_handle);
void WUDiSetNotAckNumForHandle(UINT8 dev_handle, u16 count);
u16 WUDiGetNotAckNumForHandle(UINT8 dev_handle);
void WUDiShowFatalErrorMessage(void);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_WUD_H
