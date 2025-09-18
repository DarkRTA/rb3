#include "net/WiiFriendMgr.h"
#include "os/ContentMgr_Wii.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/Joypad_Wii.h"
#include "os/CritSec.h"
#include "system/obj/Dir.h"
#include "system/utl/HttpWii.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "RevoEX/nhttp/nhttp.h"
#include "revolution/gx/GXTypes.h"
#include "revolution/os/OSReset.h"
#include "revolution/os/OSThread.h"
#include "revolution/sc/scapi.h"
#include "revolution/vi/vi.h"
#include <revolution/SC.h>
#include <revolution/MEM.h>
#include "DWC/dwc_common/dwc_init.h"
#include "DWC/dwc_common/dwc_error.h"
#include "DWC/dwcsec_prof/dwc_prof.h"
#include "utl/Locale.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

bool gDNSRunning;
char gReadBuf[256];
int gSeekSpot;
namespace PlatformMgrWii {
    CriticalSection gCrit;
}
CriticalSection gCrit2;
const char *gDNSRequest;
int gDNSError;
int gPowerCallback;
void *gSOHeapMem;
MEMiHeapHead *gSOHeapHandle;
int gSOTotalAlloc;
int gSOMaxTotalAlloc;

int gSOHeapSize = 0x20000;

#pragma push
#pragma pool_data off
void SOHeapInit() {
    if (!gSOHeapMem) {
        static int _x = MemFindHeap("main");
        MemPushHeap(_x);
        gSOHeapMem = _MemAlloc(gSOHeapSize, 0x20);
        gSOHeapHandle = MEMCreateExpHeapEx(gSOHeapMem, gSOHeapSize, 4);
        printf("SOHeap: Created heap of size %d.\n", gSOHeapSize);
        MemPopHeap();
    }
}
#pragma pop

DECOMP_FORCEACTIVE(
    PlatformMgr_Wii,
    "Warning: calling SOHeapDeinit but %d bytes are still allocated\n",
    "SOHeap: Used %d of %d total.\n"
)

void *SOAllocFunc(int i1, int i2) {
    if (i1 <= 0)
        return nullptr;
    else {
        gSOTotalAlloc += i1;
        if (gSOMaxTotalAlloc < gSOTotalAlloc) {
            gSOMaxTotalAlloc = gSOTotalAlloc;
        }
        MILO_ASSERT(gSOTotalAlloc < gSOHeapSize, 0x93);
        return MEMAllocFromExpHeapEx(gSOHeapHandle, i1, i2);
    }
}

void SOFreeFunc(void *v, unsigned long ul) {
    if (v) {
        MEMFreeToExpHeap(gSOHeapHandle, v);
        gSOTotalAlloc -= ul;
    }
}

void *_SOAlloc(unsigned long, long lll) { SOAllocFunc(lll, 0x20); }

void _SOFree(unsigned long, void *v, long lll) { SOFreeFunc(v, lll); }

// apparently already defined in revolution's DWC folder?
// void* DWCAllocFunc(DWCAllocType, unsigned long, int){

// }

void *DNSThread(void *) {}

PlatformMgr::PlatformMgr()
    : mSigninMask(0), mSigninChangeMask(0), mGuideShowing(0), mConnected(0), unk2a(0),
      mScreenSaver(0), mRegion(kRegionNone), mDiskError(kNoDiskError), mTimer(), unk6a(0),
      unk6d(0), unk70(0), unk68(0), unk69(0), unk6b(0), unk6c(0),
      mEthernetCableConnected(0), unk43a0(0), unk43a1(0), unk43a2(0), unk43a3(0),
      mCheckingProfanity(0), unkca11(0), mProfanityAllowed(1), unkca14(0),
      mHomeMenuDisabled(0), mNetworkPlay(0), unkce56(0), mIsRestarting(0),
      mPartyMicAllowed(0), mEnableSFX(0), unkce5a(0), mEnumerateFriendsCallback(0),
      mSendMsgCallback(0), mSignInUserCallback(0), mIsOnlineRestricted(1), unkce69(0),
      mIgnorePowerOperations(0) {
    mHomeMenuWii = new HomeMenu();
    mDiscErrorMgr = new DiscErrorMgrWii();
    mProfaneWord = 0;
    ClearNetError();
}

PlatformMgr::~PlatformMgr() { CloseNintendoConnection(false, false); }

void PlatformMgr::PreInit() {
    ThePlatformMgr.SystemInitPowerCallbacks();
    mDiscErrorMgr->Init();
    mHomeMenuWii->PreInit();
}

void PlatformMgr::RegionInit() {
    unsigned char regionId;
    int r = SCGetSimpleAddressRegionIdHi(&regionId);
    if (r != 0) {
        if ((u8)(regionId + 0xF8) <= 0x2C || regionId == 0x99 || regionId == 0xA8) {
            SetRegion(kRegionNA);
        } else if ((u8)(regionId + 0xC0) <= 0x30) {
            SetRegion(kRegionEurope);
        } else if (regionId == 0x01 || regionId == 0x80) {
            SetRegion(kRegionJapan);
        } else {
            SetRegion(kRegionNA);
        }
    } else {
        SetRegion(kRegionNA);
    }
}

void PlatformMgr::Init() {
    mHomeMenuWii->Init();
    SetName("platform_mgr", ObjectDir::sMainDir);
    JoypadSubscribe(this);
    SetScreenSaver(true);
    TheHttpWii.Init();
    UpdateSigninState();
    mIsOnlineRestricted = SCCheckPCMessageRestriction();
    TheContentMgr->RegisterCallback(this, false);
    SOHeapInit();
}

void PlatformMgr::SetNotifyUILocation(NotifyLocation) {}
bool PlatformMgr::IsEthernetCableConnected() { return mEthernetCableConnected; }

void PlatformMgr::UpdateSigninState() {
    if (mSigninChangeMask) {
        SigninChangedMsg msg(mSigninMask, mSigninChangeMask);
        Handle(msg, false);
        mSigninChangeMask = 0;
    }
    mSigninChangeMask = 0;
}

void PlatformMgr::SetUserSignedIn(int iii) {
    int mask = 1 << iii;
    if (iii >= 0) {
        mSigninMask |= mask;
        mSigninChangeMask |= mask;
        if (mSigninMask != 0)
            RunNetStartUtility();
    }
}

void PlatformMgr::SetUserSignedOut(int iii) {
    if (iii >= 0) {
        int mask = 1 << iii;
        if (mSigninMask & mask) {
            mSigninMask &= ~mask;
            mSigninChangeMask |= mask;
        }
    }
}

DataNode PlatformMgr::OnSignInUsers(const DataArray *a) {
    int u5 = 0;
    MILO_ASSERT((a->Size() > 4) && "Signing in needs User info on Wii - check for bad .dta merges using platform_mgr signin", 0x24E);
    if (a->Int(3))
        u5 = 2;
    if (mSignInUserCallback) {
        return mSignInUserCallback(a->Obj<User>(4), u5);
    } else
        return 0;
}

void PlatformMgr::SetPartyMicOptionsShowing(bool show) { mPartyMicAllowed = show; }

void PlatformMgr::RegisterEnumerateFriendsCallback(EnumerateFriendsCallbackFunc *func) {
    mEnumerateFriendsCallback = func;
}

void PlatformMgr::RegisterSendMsgCallback(SendMsgCallbackFunc *func) {
    mSendMsgCallback = func;
}

void PlatformMgr::RegisterSignInserCallback(SignInUserCallbackFunc *func) {
    mSignInUserCallback = func;
}

bool PlatformMgr::HasOnlinePrivilege(int pad) const {
    WiiProfile *p = TheWiiProfileMgr.GetProfileForPad(pad);
    if (p)
        return p->IsFlag(2);
    else
        return GetOwnerOfGuest(pad) != -1;
}

bool PlatformMgr::CanSeeUserCreatedContent(const OnlineID *user) const {
    WiiFriendList friendsList;
    int userpid = user->GetPrincipalID();
    TheWiiFriendMgr.GetCachedFriends(&friendsList);
    int max = friendsList.mFriends.size();
    int i = 0;
    while (i < max) {
        WiiFriend *myFriend = friendsList.GetFriendByIdx(i);
        WiiFriendProfile *friendProfile = myFriend->GetProfileByPrincipalID(userpid);
        if (friendProfile != NULL) {
            return true;
        }
        i++;
    }
    return false;
}

void PlatformMgr::GetOnlineID(int idx, OnlineID *id) const {
    WiiProfile *profile = TheWiiProfileMgr.GetProfileForPad(idx);
    if (profile != NULL) {
        id->SetPrincipalID(profile->mId);
    }
}

void PlatformMgr::SetScreenSaver(bool enable) {
    if (enable != mScreenSaver) {
        VIEnableDimming(enable);
        mScreenSaver = enable;
    }
}

bool PlatformMgr::IsUserAWiiGuest(const LocalUser *pUser) const {
    MILO_ASSERT(pUser, 0x2CD);
    int pad = pUser->GetPadNum();
    if (pad < 0)
        MILO_FAIL("PadNum = %d", pad);
    return TheWiiProfileMgr.IsPadAGuest(pad);
}

int PlatformMgr::InitNintendoConnection() {
    if (!mTimer.Running()) {
        InitSOLibrary(false);
        mTimer.Restart();
    }
    return 1;
}

void PlatformMgr::InitDWCLibrary() {
    if (!unk43a3) {
        if (!unk43a0) {
            unk43a0 = true;
            unk43a1 = false;
            OSCreateThread(
                &mThread, DWCStartupThreadFunc, 0, &mHasNetError, 0x4000, 0xF, 1
            );
            mThread.specific[0] = (void *)"DWCThread";
            OSResumeThread(&mThread);
        } else
            unk43a2 = false;
    }
}

void PlatformMgr::UpdateDWCLibrary() {
    if (unk43a0 && unk43a1) {
        unk43a0 = false;
        unk43a3 = true;
        if (unk43a2)
            TerminateDWCLibrary();
    }
}

void PlatformMgr::TerminateDWCLibrary() {
    if (unk43a3) {
        DWC_Shutdown();
        unk43a3 = false;
    } else if (unk43a0) {
        unk43a2 = true;
    }
}

void PlatformMgr::ClearDWCError() { DWC_ClearError(); }

bool PlatformMgr::StartDNSLookup(const char *cc) {
    if (gDNSRunning)
        return false;
    else {
        gDNSRequest = cc;
        if (!OSIsThreadTerminated(&mDNSThread))
            return false;
        else {
            OSCreateThread(
                &mDNSThread, DNSThread, &mDNSResult, &mDNSResult, 0x4000, 0xF, 1
            );
            mThread.specific[0] = (void *)"DNSThread";
            OSResumeThread(&mDNSThread);
            return true;
        }
    }
}

bool PlatformMgr::CheckDNSLookup(String &str) {
    if (gDNSRunning)
        return false;
    else {
        str = mDNSResult;
        return true;
    }
}

void PlatformMgr::KillDNSLookup() {
    if (gDNSRunning) {
        OSCancelThread(&mDNSThread);
        gDNSRunning = false;
    }
}

int PlatformMgr::GetLastDWCError() {
    bool noError = false;
    int ec = 0;
    DWCErrorType etype;
    DWCError r = (DWCError)DWC_GetLastErrorEx(&ec, (int *)&etype);
    MILO_LOG(
        "DWC_GetLastError \n-DWCError: %d\n-Error type: %d \n-Error Code: %d\n",
        r,
        etype,
        -ec
    );
    if (r == 0 && ec == 0) {
        noError = true;
    }
    if (noError) {
        ec = 0;
    } else {
        ec = -ec;
    }
    return ec;
}

void PlatformMgr::ClearNetError() {
    mNetError = "";
    mHasNetError = 0;
}

int PlatformMgr::GetLastNHTTPError() { return NHTTPGetError(); }

int PlatformMgr::GetLastDNSError() { return -gDNSError; }

void PlatformMgr::SetConnected(bool connected) { mConnected = connected; }

bool PlatformMgr::OnMsg(const ButtonDownMsg &msg) {
    if (msg.GetAction() == 4 && mDisabling) {
        DisableWiiJoypad(msg.GetUser()->GetPadNum());
    } else if (msg.GetAction() == 0xF) {
        if (mHomeMenuDisabled == 0)
            mHomeMenuWii->AllowHomeMenu(true);
        else
            mHomeMenuWii->AllowHomeMenu(false);
        mHomeMenuWii->ActivateHomeMenu();
        return true;
    }
    return false;
}

bool PlatformMgr::OnMsg(const ButtonUpMsg &msg) {
    if (msg.GetAction() == 0xF) {
        mHomeMenuWii->UnlockHomeMenu();
    }
    return false;
}

void PlatformMgr::SetDiskError(DiskError err) {
    if (mDiskError != kFailedChecksum && mDiskError != err) {
        mDiskError = err;
        if (err == kNoDiskError) {
            mDiscErrorMgr->SetDiscError(false);
            mDiscErrorMgr->mRetryError = false;
            mDiscErrorMgr->mMovieReadError = false;
        } else if (err == kDiskError) {
            mDiscErrorMgr->SetDiscError(true);
            mDiscErrorMgr->mRetryError = true;
        } else if (err == kWrongDisk) {
            mDiscErrorMgr->SetDiscError(true);
            mDiscErrorMgr->mRetryError = false;
        }
        if (err != kNoDiskError) {
            if (mNetworkPlay == false) {
            } else {
            }
        }
        if (mDiskError == kFailedChecksum) {
            TheDebug.Exit(1, true);
        }
    }
}

void WiiPowerCallback() { gPowerCallback = kQuitShutdown; }
void WiiResetCallback() { gPowerCallback = kQuitRestart; }

void PlatformMgr::SystemInitPowerCallbacks() {
    OSSetPowerCallback(WiiPowerCallback);
    OSSetResetCallback(WiiResetCallback);
}

void PlatformMgr::WiiPoll() {
    if (gPowerCallback != kQuitNone && mIgnorePowerOperations) {
        VISetBlack(true);
        VIFlush();
        VIWaitForRetrace();
    }
    if (gPowerCallback != kQuitNone && !mIgnorePowerOperations) {
        if (mHomeMenuWii->mHomeMenuActive) {
            mHomeMenuWii->ForceQuit();
        }
        WiiShutdown((QuitType)gPowerCallback);
    }
}

void PlatformMgr::SystemCheckShutdown() {
    if (gPowerCallback != kQuitNone) {
        if (gMainThreadID != NULL) {
            OSSuspendThread(gMainThreadID);
            gMainThreadID = NULL;
        }
        WiiShutdown((QuitType)gPowerCallback);
    }
}

bool PlatformMgr::IsSignedIntoLive(int pad) const {
    return TheWiiProfileMgr.IsPadRegistered(pad);
}

const char *PlatformMgr::GetName(int pad) const {
    bool signedin = IsSignedIn(pad);
    const char *name;
    if (signedin && (name = TheWiiProfileMgr.GetNameForPad(pad), name)) {
        return MakeString(name);
    } else
        return MakeString("%s %d", Localize(player, 0), pad + 1);
}

void PlatformMgr::EnumerateFriends(
    int iii, std::vector<Friend *> &friends, Hmx::Object *obj
) {
    if (mEnumerateFriendsCallback && mEnumerateFriendsCallback(iii, friends, obj))
        return;
    else if (obj)
        obj->Handle(PlatformMgrOpCompleteMsg(0), true);
}

void PlatformMgr::SendMsg(
    Friend *friendObj, const char *c1, const char *c2, MemStream &ms
) {
    if (mSendMsgCallback && mSendMsgCallback(friendObj, c1, c2, ms)) {
        return;
    }
}

void PlatformMgr::RunNetStartUtility() { InitNintendoConnection(); }

int PlatformMgr::GetOwnerOfGuest(int) const {
    int i = 0;
    do {
        int idx = TheWiiProfileMgr.GetIndexForPad(i);
        if (idx >= 0 && TheWiiProfileMgr.IsIndexValid(idx)
            && TheWiiProfileMgr.IsPadAGuest(i) == false
            && TheWiiProfileMgr.IsPadRegistered(i))
            return i;
        i++;
    } while (i < 4);
    return -1;
}

bool PlatformMgr::IsPadAGuest(int pad) const {
    if (GetOwnerOfGuest(pad) != -1) {
        return TheWiiProfileMgr.IsPadAGuest(pad);
    } else
        return false;
}

bool PlatformMgr::IsGuestOnlineID(const OnlineID *oid) const {
    return oid->GetPrincipalID() == 0;
}

bool PlatformMgr::StartProfanity(const char *cc, Hmx::Object *o) {
    MILO_LOG("CCS DEBUG: DWC Profanity check on: %s\n", cc);
    if (mCheckingProfanity)
        return false;
    else if (!mProfanityAllowed)
        return false;
    else {
        memset(mProfaneChars, 0, sizeof(mProfaneChars));
        UTF8toUTF16(mProfaneChars, cc);
        mProfaneWord = mProfaneChars;
        return StartProfanity(&mProfaneWord, 1, mProfaneResults, o);
    }
}

bool PlatformMgr::StartProfanity(
    const unsigned short **us, int iii, char *c, Hmx::Object *o
) {
    if (mConnected) {
        if (mCheckingProfanity)
            return false;
        else if (!mProfanityAllowed)
            return false;
        else {
            unkca11 = false;
            mProfaneWordCount = iii;
            if (!c)
                c = mProfaneResults;
            memset(c, 0, iii);
            unkca14 = o;
            CriticalSection *crit = &PlatformMgrWii::gCrit;
            if (crit != NULL)
                crit->Enter();
            int r = DWC_CheckProfanityAsync(us, iii, NULL, -1, c, &unkce38);
            if (r == 0) {
                MILO_LOG("CCS DEBUG: Profanity Check failed to initialize\n");
                if (crit != NULL)
                    crit->Exit();
                return false;
            } else {
                mCheckingProfanity = true;
                if (crit != NULL)
                    crit->Exit();
                return true;
            }
        }
    } else
        return false;
}

bool PlatformMgr::CheckProfanity(bool &done, bool &profane) {
    bool ret;
    int r = DWC_CheckProfanityProcess();
    switch (r) {
    case 1:
        return false;
    case 2:
        done = true;
        for (int i = 0; i < mProfaneWordCount; i++) {
            if (mProfaneResults[i] == true) {
                MILO_LOG("CCS DEBUG: Username is very un classy\n");
                profane = true;
                return true;
            }
        }
        profane = false;
        return true;
    case 0:
        MILO_ASSERT(0 && "Improper use of DWC profanity check - tell Ian S." && "", 2064);
    case 3:
        HandleDWCError();
        done = false;
        MILO_LOG("CCS DEBUG: DWC Check failed\n");
        return true;
    }
    return false;
}

void PlatformMgr::EnableProfanity(bool b) { mProfanityAllowed = b; }

void PlatformMgr::HandleNANDCorruptError() {
    const char *localized = Localize(wii_error_nand_worn, NULL);
    GXColor bg = { 0, 0, 0, 255 };
    GXColor fg = { 255, 255, 255, 255 };
    OSFatal(fg, bg, localized);
}

void PlatformMgr::SetHomeMenuEnabled(bool b) {
    if (b)
        mHomeMenuDisabled--;
    else
        mHomeMenuDisabled++;
    MILO_ASSERT(mHomeMenuDisabled >= 0, 0x84D);
}

void PlatformMgr::ContentStarted() { SetHomeMenuEnabled(false); }
void PlatformMgr::ContentDone() { SetHomeMenuEnabled(true); }
void PlatformMgr::ContentCancelled() { SetHomeMenuEnabled(true); }

bool PlatformMgr::IsShuttingDown() { return gPowerCallback != kQuitNone; }

void PlatformMgr::WiiShutdown(QuitType type) {
    VISetBlack(true);
    VIFlush();
    VIWaitForRetrace();
    switch (type) {
    case kQuitRestart:
        if (TheWiiContentMgr.mCNTSDInited) {
            TheWiiContentMgr.UnmountContents(Symbol(""));
        }
        OSRestart(0);
        break;
    case kQuitShutdown:
        if (TheWiiContentMgr.mCNTSDInited) {
            TheWiiContentMgr.UnmountContents(Symbol(""));
        }
        OSShutdownSystem();
        break;
    case kQuitMenu:
        if (TheWiiContentMgr.mCNTSDInited) {
            TheWiiContentMgr.UnmountContents(Symbol(""));
        }
        OSReturnToMenu();
        break;
    case kQuitDataManager:
        if (TheWiiContentMgr.mCNTSDInited) {
            TheWiiContentMgr.UnmountContents(Symbol(""));
        }
        OSReturnToDataManager();
        break;
    }
    OSPanic("PlatformMgr_Wii.cpp", 1845, "Exit");
}
