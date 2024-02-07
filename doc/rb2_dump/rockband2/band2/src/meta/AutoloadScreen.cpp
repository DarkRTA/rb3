/*
    Compile unit: C:\rockband2\band2\src\meta\AutoloadScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800AF930 -> 0x800B160C
*/
class Symbol t; // size: 0x4, address: 0x80A4A4C4
class Symbol t; // size: 0x4, address: 0x80A4A4CC
class Symbol t; // size: 0x4, address: 0x80A4A4D4
class Symbol t; // size: 0x4, address: 0x80A4A4DC
class DataArray * types; // size: 0x4, address: 0x80A4A4E0
class Symbol name; // size: 0x4, address: 0x80A4A4E8
class UITransitionCompleteMsg : public Message {
    // total size: 0x8
};
class SaveLoadAllCompleteMsg : public Message {
    // total size: 0x8
};
class AutoloadScreen : public BandScreen {
    // total size: 0x4C
    unsigned char mProcessButton; // offset 0x3A, size 0x1
    unsigned char mHasSavedButton; // offset 0x3B, size 0x1
    int mPadNum; // offset 0x3C, size 0x4
    int mUserNum; // offset 0x40, size 0x4
    enum JoypadAction mAction; // offset 0x44, size 0x4
    enum JoypadButton mRawButton; // offset 0x48, size 0x4
};
// Range: 0x800AF930 -> 0x800AF988
void * AutoloadScreen::AutoloadScreen(class AutoloadScreen * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14AutoloadScreen;
}

// Range: 0x800AF9FC -> 0x800AFA74
void * AutoloadScreen::~AutoloadScreen(class AutoloadScreen * const this /* r30 */) {}

// Range: 0x800AFA74 -> 0x800AFA80
void AutoloadScreen::ClearButtonPress() {}

static class Symbol is_active; // size: 0x4, address: 0x80A4A4F0
static class Message msg; // size: 0x8, address: 0x80977BB8
static class Symbol mode; // size: 0x4, address: 0x80A4A4F8
// Range: 0x800AFA80 -> 0x800AFEAC
void AutoloadScreen::AttemptToAutoload(class AutoloadScreen * const this /* r29 */) {
    // Local variables
    unsigned char isActive; // r0

    // References
    // -> static class Symbol mode;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class MemcardMgr TheMemcardMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
    // -> static class Symbol is_active;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10SaveScreen;
    // -> class ObjectDir * sMainDir;
    // -> class ProfileMgr TheProfileMgr;
    // -> class NetSession * TheNetSession;
    // -> class UIManager TheUI;
    // -> class NetSync * TheNetSync;
}

// Range: 0x800AFEAC -> 0x800B007C
void AutoloadScreen::AttemptToProcessButtonMessage(class AutoloadScreen * const this /* r29 */) {
    // Local variables
    class BandUser * pUser; // r31
    class Profile * pProfile; // r30
    class ButtonDownMsg msg; // r1+0x10

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class NetSync * TheNetSync;
    // -> class BandUI * TheBandUI;
    // -> class NetSession * TheNetSession;
    // -> class UIManager TheUI;
}

// Range: 0x800B007C -> 0x800B0110
void AutoloadScreen::Enter(class AutoloadScreen * const this /* r30 */, class UIScreen * from /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> class Symbol t;
}

// Range: 0x800B0110 -> 0x800B0198
void AutoloadScreen::Exit(class AutoloadScreen * const this /* r30 */, class UIScreen * to /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Symbol t;
}

// Range: 0x800B0198 -> 0x800B019C
void AutoloadScreen::Poll() {}

// Range: 0x800B019C -> 0x800B0254
class DataNode AutoloadScreen::OnRegisterButtonPress(class AutoloadScreen * const this /* r27 */, class DataArray * pData /* r28 */) {}

// Range: 0x800B0254 -> 0x800B0338
class DataNode AutoloadScreen::OnRegisterUserConfirm(class AutoloadScreen * const this /* r29 */, class DataArray * pData /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
}

static class Message ignore; // size: 0x8, address: 0x80977BD0
class ProfileActivatedMsg : public Message {
    // total size: 0x8
};
// Range: 0x800B0338 -> 0x800B05E0
class DataNode AutoloadScreen::OnMsg(class AutoloadScreen * const this /* r30 */, const class ProfileActivatedMsg & msg /* r31 */) {
    // Local variables
    class DataNode ret; // r1+0x20

    // References
    // -> static class Message ignore;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800B05E0 -> 0x800B0620
class DataNode AutoloadScreen::OnMsg() {}

// Range: 0x800B0620 -> 0x800B06CC
class DataNode AutoloadScreen::OnMsg(class AutoloadScreen * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> class BandUI * TheBandUI;
}

// Range: 0x800B06CC -> 0x800B0764
class DataNode AutoloadScreen::OnMsg(class AutoloadScreen * const this /* r31 */) {
    // References
    // -> class MemcardMgr TheMemcardMgr;
    // -> class Symbol t;
}

// Range: 0x800B0764 -> 0x800B07D8
class DataNode AutoloadScreen::OnDismissEvent(class AutoloadScreen * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A500
static class Symbol _s; // size: 0x4, address: 0x80A4A508
static class Symbol _s; // size: 0x4, address: 0x80A4A510
static class Symbol _s; // size: 0x4, address: 0x80A4A518
// Range: 0x800B07D8 -> 0x800B160C
class DataNode AutoloadScreen::Handle(class AutoloadScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode _n; // r1+0x78

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__22SaveLoadAllCompleteMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__23UITransitionCompleteMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__16SigninChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__19ProfileActivatedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class UIComponentSelectMsg : public Message {
    // total size: 0x8
};
class UIComponentSelectDoneMsg : public Message {
    // total size: 0x8
};
class UIComponentFocusChangeMsg : public Message {
    // total size: 0x8
};
class BandScreen : public UIScreen {
    // total size: 0x3C
};
enum SaveScreenMode {
    kMeta_SaveAutoload = 0,
    kMeta_SaveAutosave = 1,
    kMeta_SaveManualSave = 2,
    kMeta_SaveManualLoad = 3,
};
enum State {
    kS_None = 0,
    kS_Startup = 1,
    kS_AutoloadInit = 2,
    kS_AutoloadFindNext = 3,
    kS_AutoloadSearch = 4,
    kS_AutoloadNoSaveFound = 5,
    kS_AutoloadMultipleSavesFound = 6,
    kS_AutoloadChooseDeviceNone = 7,
    kS_AutoloadChooseDeviceMulti = 8,
    kS_AutoloadStartLoad = 9,
    kS_AutoloadDeviceMissing = 10,
    kS_AutoloadChooseDeviceMissing = 11,
    kS_AutoloadCorrupt = 12,
    kS_AutoloadObsolete = 13,
    kS_AutoloadFuture = 14,
    kS_AutoloadAllDone = 15,
    kS_AutoloadSaveGlobal = 16,
    kS_SongCacheCreateSearch = 17,
    kS_SongCacheCreateNotFound = 18,
    kS_SongCacheCreateMissing = 19,
    kS_SongCacheCreateChoose = 20,
    kS_SongCacheCreateChooseWaitOnGuide = 21,
    kS_SongCacheCreateMountRead = 22,
    kS_SongCacheCreateCorrupt = 23,
    kS_SongCacheCreateMountDelete = 24,
    kS_SongCacheCreateFileSize = 25,
    kS_SongCacheCreateRead = 26,
    kS_SongCacheCreateMountWrite = 27,
    kS_SongCacheCreateWrite = 28,
    kS_SongCacheCreateUnmount = 29,
    kS_SongCacheCreateUnmountWrite = 30,
    kS_SongCacheCreateError = 31,
    kS_SongCacheCreateDone = 32,
    kS_GlobalCreateSearch = 33,
    kS_GlobalCreateNotFound = 34,
    kS_GlobalCreateMissing = 35,
    kS_GlobalCreateChoose = 36,
    kS_GlobalCreateChooseWaitOnGuide = 37,
    kS_GlobalCreateMountRead = 38,
    kS_GlobalCreateCorrupt = 39,
    kS_GlobalCreateMountDelete = 40,
    kS_GlobalCreateMountWrite = 41,
    kS_GlobalCreateRead = 42,
    kS_GlobalCreateWrite = 43,
    kS_GlobalCreateUnmount = 44,
    kS_GlobalCreateUnmountWrite = 45,
    kS_GlobalCreateError = 46,
    kS_GlobalCreateDone = 47,
    kS_GlobalOptionsMissing = 48,
    kS_GlobalOptionsChoose = 49,
    kS_GlobalOptionsChooseWaitOnGuide = 50,
    kS_GlobalOptionsAutoMount = 51,
    kS_GlobalOptionsAutoWrite = 52,
    kS_GlobalOptionsAutoUnmountWrite = 53,
    kS_GlobalOptionsError = 54,
    kS_GlobalOptionsDone = 55,
    kS_AutoloadAutosaveWarning = 56,
    kS_CheckMemoryWii = 57,
    kS_NewFilePrompt = 58,
    kS_SaveLoadNoSaveWii = 59,
    kS_SaveLoadConfirmNoSaveWii = 60,
    kS_SaveLoadReturnToHomeWii = 61,
    kS_AutoloadPreSaveCheckWii = 62,
    kS_SaveLoadSystemCorrupt = 63,
    kS_CheckSDToggle = 64,
    kS_MaxBlocksFiles = 65,
    kS_StartLoadCountdown = 66,
    kS_AutoStartLoadDeferred = 67,
    kS_ManualStartLoadDeferred = 68,
    kS_StartAutoLoadCountdown = 69,
    kS_StartManualLoadCountdown = 70,
    kS_StartSaveDeferred = 71,
    kS_StartSaveCountdown = 72,
    kS_UploadShowMessageDelay = 73,
    kS_UploadActualWii = 74,
    kS_SaveLoadError = 75,
    kS_SaveLoadSilentError = 76,
    kS_SaveLoadSuccess = 77,
    kS_SaveLoadUnchanged = 78,
    kS_SaveLookForFile = 79,
    kS_SaveOverwrite = 80,
    kS_SaveNoOverwrite = 81,
    kS_SaveConfirmOverwrite = 82,
    kS_SaveNotEnoughSpace = 83,
    kS_SaveNotEnoughSpaceWii = 84,
    kS_SaveNotEnoughInodesWii = 85,
    kS_SaveNotEnoughSpacePS3 = 86,
    kS_SaveDeleteSavesPS3 = 87,
    kS_SaveDeviceInvalid = 88,
    kS_SaveChooseDeviceInvalid = 89,
    kS_SaveFailed = 90,
    kS_SaveDisabledByCheat = 91,
    kS_LoadFailed = 92,
    kS_AutosaveInit = 93,
    kS_AutosaveSongCache = 94,
    kS_AutosaveGlobal = 95,
    kS_AutosaveFindNext = 96,
    kS_AutosaveAllDone = 97,
    kS_UploadInit = 98,
    kS_UploadFindNext = 99,
    kS_Upload = 100,
    kS_UploadErrorStart = 101,
    kS_UploadErrorView = 102,
    kS_UploadErrorPrev = 103,
    kS_UploadErrorNext = 104,
    kS_UploadErrorDone = 105,
    kS_UploadDone = 106,
    kS_ManualSaveInit = 107,
    kS_ManualSaveChooseDevice = 108,
    kS_ManualSaveNoDevice = 109,
    kS_ManualSaveDone = 110,
    kS_ManualLoadInit = 111,
    kS_ManualLoadConfirmUnsaved = 112,
    kS_ManualLoadConfirm = 113,
    kS_ManualLoadChooseDevice = 114,
    kS_ManualLoadNoDevice = 115,
    kS_ManualLoadMissing = 116,
    kS_ManualLoadStartLoad = 117,
    kS_ManualLoadNoFile = 118,
    kS_ManualLoadCorrupt = 119,
    kS_ManualSaveCorrupt = 120,
    kS_ManualLoadDone = 121,
    kS_Abort = 122,
    kS_Done = 123,
    kS_Exiting = 124,
};
class CacheID {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
enum OpType {
    kOpNone = 0,
    kOpDirectory = 1,
    kOpFileSize = 2,
    kOpRead = 3,
    kOpWrite = 4,
    kOpDelete = 5,
};
enum CacheResult {
    kCache_NoError = 0,
    kCache_ErrorBusy = 1,
    kCache_ErrorBadParam = 2,
    kCache_ErrorUnsupported = 3,
    kCache_ErrorUserCancel = 4,
    kCache_ErrorNoStorageDevice = 5,
    kCache_ErrorCacheNotFound = 6,
    kCache_ErrorCorrupt = 7,
    kCache_ErrorStorageDeviceMissing = 8,
    kCache_ErrorNotEnoughSpace = 9,
    kCache_Error360GuideAlreadyOut = 10,
    kCache_ErrorUnknown = -1,
};
class CacheDirEntry {
    // total size: 0x18
public:
    class String mStrRemotePath; // offset 0x0, size 0xC
    struct DateTime mTimeLastAccess; // offset 0xC, size 0x6
    unsigned int mFileSize; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CacheDirEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CacheDirEntry * _M_start; // offset 0x0, size 0x4
    class CacheDirEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Cache {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    enum OpType mOpCur; // offset 0x4, size 0x4
    enum CacheResult mLastResult; // offset 0x8, size 0x4
};
enum MCResult {
    kMCNoError = 0,
    kMCNoCard = 1,
    kMCNotFormatted = 2,
    kMCDifferentCard = 3,
    kMCReadWriteFailed = 4,
    kMCCorrupt = 5,
    kMCNotEnoughSpace = 6,
    kMCFileExists = 7,
    kMCFileNotFound = 8,
    kMCMultipleFilesFound = 9,
    kMCObsoleteVersion = 10,
    kMCNewerVersion = 11,
    kMCGeneralError = 12,
    kMCUnsupported = 13,
    kMCAlreadyFormatted = 14,
    kMCInsufficientInodes = 15,
    kMCSystemCorrupt = 16,
    kMCAccessError = 17,
    kMCMaxedSysMem = 18,
    kMCMax = 19,
};
class DeviceChosenMsg : public Message {
    // total size: 0x8
};
class NoDeviceChosenMsg : public Message {
    // total size: 0x8
};
class MCResultMsg : public Message {
    // total size: 0x8
};
class StorageChangedMsg : public Message {
    // total size: 0x8
};
class SaveScreen : public BandScreen {
    // total size: 0x188
    enum SaveScreenMode mMode; // offset 0x3C, size 0x4
    enum State mState; // offset 0x40, size 0x4
    enum State mStateAtSelectStart; // offset 0x44, size 0x4
    enum State mPreviousState; // offset 0x48, size 0x4
    unsigned char mFirstTimeSDToggle; // offset 0x4C, size 0x1
    class BandUser * mBandUser; // offset 0x50, size 0x4
    unsigned char mIsLockedToBandUser; // offset 0x54, size 0x1
    class BandUser * mSavedBandUser; // offset 0x58, size 0x4
    class Timer mTimerStateChange; // offset 0x60, size 0x38
    class Timer mTimerWrite; // offset 0x98, size 0x38
    int mPlayerNumCur; // offset 0xD0, size 0x4
    class vector mUploadProfiles; // offset 0xD4, size 0xC
    class DataArrayPtr mUploadArg2; // offset 0xE0, size 0x8
    int mUploadErrorCur; // offset 0xE8, size 0x4
    class String mSongCacheName; // offset 0xEC, size 0xC
    unsigned int mSongCacheSize; // offset 0xF8, size 0x4
    unsigned char mHasAutoloaded; // offset 0xFC, size 0x1
    unsigned char mFirstTime; // offset 0xFD, size 0x1
    unsigned char mShowFirstTimeDrum; // offset 0xFE, size 0x1
    unsigned char mShowFirstTimeGuitar; // offset 0xFF, size 0x1
    unsigned char mShowFirstTimeVocals; // offset 0x100, size 0x1
    unsigned char mShowFirstTimeCalibrate; // offset 0x101, size 0x1
    class CacheID * mCacheID; // offset 0x104, size 0x4
    class Cache * mCache; // offset 0x108, size 0x4
    void * mData; // offset 0x10C, size 0x4
    unsigned char mSongCacheWriteDisabled; // offset 0x110, size 0x1
    unsigned char mWaiting; // offset 0x111, size 0x1
    enum MCResult mLastMCResult; // offset 0x114, size 0x4
    unsigned char mIsLongSave; // offset 0x118, size 0x1
    unsigned char mSaveOverwrite; // offset 0x119, size 0x1
    int mLockCountdown; // offset 0x11C, size 0x4
    int mLoadCountdown; // offset 0x120, size 0x4
    int mSaveCountdown; // offset 0x124, size 0x4
    int mUploadCountdown; // offset 0x128, size 0x4
    char mTitleString[64]; // offset 0x12C, size 0x40
    unsigned char mIsCacheMgrDone; // offset 0x16C, size 0x1
    enum CacheResult mLastCacheResult; // offset 0x170, size 0x4
    unsigned char mConnected; // offset 0x174, size 0x1
    unsigned char mDisplayJoypadConnection; // offset 0x175, size 0x1
    class InviteAcceptedMsg * mInviteAcceptedMsg; // offset 0x178, size 0x4
    unsigned char mIsMessageRunning; // offset 0x17C, size 0x1
    class Symbol mSymLongMessage; // offset 0x180, size 0x4
    unsigned char mWaitOnSessionDisable; // offset 0x184, size 0x1
};
struct {
    // total size: 0x80
} __vt__14AutoloadScreen; // size: 0x80, address: 0x8087DB18
struct {
    // total size: 0x8
} __RTTI__14AutoloadScreen; // size: 0x8, address: 0x8087DBD0
struct {
    // total size: 0x8
} __RTTI__10SaveScreen; // size: 0x8, address: 0x8087DC08
struct {
    // total size: 0xC
} __vt__22SaveLoadAllCompleteMsg; // size: 0xC, address: 0x8087DC70
struct {
    // total size: 0x8
} __RTTI__22SaveLoadAllCompleteMsg; // size: 0x8, address: 0x8087DCA0
struct {
    // total size: 0xC
} __vt__19ProfileActivatedMsg; // size: 0xC, address: 0x8087DCA8
struct {
    // total size: 0x8
} __RTTI__19ProfileActivatedMsg; // size: 0x8, address: 0x8087DCD8
struct {
    // total size: 0xC
} __vt__23UITransitionCompleteMsg; // size: 0xC, address: 0x8087DCE0
struct {
    // total size: 0x8
} __RTTI__23UITransitionCompleteMsg; // size: 0x8, address: 0x8087DD18
struct {
    // total size: 0xC
} __vt__16SigninChangedMsg; // size: 0xC, address: 0x8087DD48
struct {
    // total size: 0x8
} __RTTI__16SigninChangedMsg; // size: 0x8, address: 0x8087DD78
class ThreadCallback {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
struct ContainerId {
    // total size: 0x8
    int port; // offset 0x0, size 0x4
    int slot; // offset 0x4, size 0x4
};
enum SeekType {
    kOsSeekBegin = 0,
    kOsSeekCur = 1,
    kOsSeekEnd = 2,
};
class MCFile {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class MCContainer * mpContainer; // offset 0x4, size 0x4
};
class MCContainer {
    // total size: 0x10
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    struct ContainerId mCid; // offset 0x4, size 0x8
    unsigned char mIsMounted; // offset 0xC, size 0x1
};
enum State {
    kS_None = 0,
    kS_Search = 1,
    kS_CheckForSaveContainer = 2,
    kS_SaveGame = 3,
    kS_LoadGame = 4,
    kS_DeleteSaves = 5,
};
enum NHTTPError {
    NHTTP_ERROR_SYSTEM = -1,
    NHTTP_ERROR_NONE = 0,
    NHTTP_ERROR_ALLOC = 1,
    NHTTP_ERROR_TOOMANYREQ = 2,
    NHTTP_ERROR_SOCKET = 3,
    NHTTP_ERROR_DNS = 4,
    NHTTP_ERROR_CONNECT = 5,
    NHTTP_ERROR_BUFFULL = 6,
    NHTTP_ERROR_HTTPPARSE = 7,
    NHTTP_ERROR_CANCELED = 8,
    NHTTP_ERROR_REVOLUTIONSDK = 9,
    NHTTP_ERROR_REVOLUTIONWIFI = 10,
    NHTTP_ERROR_UNKNOWN = 11,
    NHTTP_ERROR_DNS_PROXY = 12,
    NHTTP_ERROR_CONNECT_PROXY = 13,
    NHTTP_ERROR_SSL = 14,
    NHTTP_ERROR_BUSY = 15,
    NHTTP_ERROR_SSL_ROOTCA = 16,
    NHTTP_ERROR_SSL_CLIENTCERT = 17,
    NHTTP_ERROR_MAX = 18,
};
enum NHTTPConnectionStatus {
    NHTTP_STATUS_ERROR = -1,
    NHTTP_STATUS_IDLE = 0,
    NHTTP_STATUS_CONNECTING = 1,
    NHTTP_STATUS_SENDING = 2,
    NHTTP_STATUS_RECEIVING_HEADER = 3,
    NHTTP_STATUS_RECEIVING_BODY = 4,
    NHTTP_STATUS_COMPLETE = 5,
    NHTTP_STATUS_MAX = 6,
};
class HttpWii {
    // total size: 0x290
    unsigned char mServerVerifySSL; // offset 0x0, size 0x1
    unsigned char bUseSSL; // offset 0x1, size 0x1
    unsigned char bUseFileLoad; // offset 0x2, size 0x1
    char * mRootCA; // offset 0x4, size 0x4
    unsigned long certSize; // offset 0x8, size 0x4
    class DataArray * mServerInfo; // offset 0xC, size 0x4
    void * mHandles[10]; // offset 0x10, size 0x28
    unsigned int mLastReceived[10]; // offset 0x38, size 0x28
    class Timer mTimeout[10]; // offset 0x60, size 0x230
};
class MCContainerWii : public MCContainer {
    // total size: 0x10
};
class UIChangedMsg : public Message {
    // total size: 0x8
};
class MemcardMgr : public MsgSource, public ThreadCallback {
    // total size: 0x24C0
    struct ContainerId mCidTbl[1]; // offset 0x20, size 0x8
    class MCContainer * mPContainerTbl[1]; // offset 0x28, size 0x4
    unsigned char mIsDeviceValid[1]; // offset 0x2C, size 0x1
    unsigned char mSelectDeviceWaiting; // offset 0x2D, size 0x1
    unsigned char mSelectDeviceForceShow; // offset 0x2E, size 0x1
    class Object * mSelectDeviceCallBackObj; // offset 0x30, size 0x4
    int mPadNum; // offset 0x34, size 0x4
    int mPlayerNum; // offset 0x38, size 0x4
    char * mPBuffer; // offset 0x3C, size 0x4
    int mCbSave; // offset 0x40, size 0x4
    int mForceOverwrite; // offset 0x44, size 0x4
    enum State mState; // offset 0x48, size 0x4
    unsigned char mSaving; // offset 0x4C, size 0x1
    unsigned char mFormating; // offset 0x4D, size 0x1
    char mSaveFilename[64]; // offset 0x4E, size 0x40
    char mBanFilename[64]; // offset 0x8E, size 0x40
    char mSongsFilename[64]; // offset 0xCE, size 0x40
    char mSongsDir[64]; // offset 0x10E, size 0x40
    unsigned char mChangeHMBPerm; // offset 0x14E, size 0x1
    struct OSThread mSaveLoadThread; // offset 0x150, size 0x318
    unsigned char mSaveLoadThreadStack[8192]; // offset 0x480, size 0x2000
    class HttpWii * mWiiHttp; // offset 0x2480, size 0x4
    void * mSongsDtaBuffer; // offset 0x2484, size 0x4
};
class UIComponentScrollMsg : public Message {
    // total size: 0x8
};

