#include "os/PlatformMgr.h"
#include "os/Joypad_Wii.h"
#include "meta/Profile.h"
#include <revolution/SC.h>

PlatformMgr::PlatformMgr() : mSigninMask(0), mSigninChangeMask(0), mGuideShowing(0), mConnected(0), unk2a(0), mScreenSaver(0), mRegion(kRegionNone), mDiskError(kNoDiskError), 
    mTimer(), unk6a(0), unk6d(0), unk70(0), unk68(0), unk69(0), unk6b(0), unk6c(0), mEthernetCableConnected(0), unk43a0(0), unk43a1(0), unk43a2(0), unk43a3(0),
    mCheckingProfanity(0), unkca11(0), unkca12(1), unkca14(0), unkce4c(0), mNetworkPlay(0), unkce56(0), mIsRestarting(0), mPartyMicAllowed(0), mEnableSFX(0), unkce5a(0),
    mEnumerateFriendsCallback(0), mSendMsgCallback(0), mSignInUserCallback(0), mIsOnlineRestricted(1), unkce69(0), unkce6a(0) {
    mHomeMenuWii = new HomeMenu();
    mDiscErrorMgr = new DiscErrorMgrWii();
    unkca18 = 0;
    ClearNetError();
}

PlatformMgr::~PlatformMgr(){
    CloseNintendoConnection(false, false);
}

void PlatformMgr::PreInit(){
    ThePlatformMgr.SystemInitPowerCallbacks();
    mDiscErrorMgr->Init();
    mHomeMenuWii->PreInit();
}

void PlatformMgr::RegionInit(){

}

bool PlatformMgr::IsEthernetCableConnected(){ return mEthernetCableConnected; }

void PlatformMgr::UpdateSigninState(){
    if(mSigninChangeMask){
        SigninChangedMsg msg(mSigninMask, mSigninChangeMask);
        Handle(msg, false);
        mSigninChangeMask = 0;
    }
    mSigninChangeMask = 0;
}

void PlatformMgr::SetUserSignedIn(int iii){
    int mask = 1 << iii;
    if(iii >= 0){
        mSigninMask |= mask;
        mSigninChangeMask |= mask;
        if(mSigninMask != 0) RunNetStartUtility();
    }
}

void PlatformMgr::SetUserSignedOut(int iii){
    if(iii >= 0){
        int mask = 1 << iii;
        if(mSigninMask & mask){
            mSigninMask &= ~mask;
            mSigninChangeMask |= mask;
        }
    }
}

DataNode PlatformMgr::OnSignInUsers(const DataArray* a){
    int u5 = 0;
    MILO_ASSERT((a->Size() > 4) && "Signing in needs User info on Wii - check for bad .dta merges using platform_mgr signin", 0x24E);
    if(a->Int(3)) u5 = 2;
    if(mSignInUserCallback){
        return mSignInUserCallback(a->Obj<User>(4), u5);
    }
    else return 0;
}

void PlatformMgr::SetPartyMicOptionsShowing(bool show){
    mPartyMicAllowed = show;
}

void PlatformMgr::RegisterEnumerateFriendsCallback(EnumerateFriendsCallbackFunc* func){
    mEnumerateFriendsCallback = func;
}

void PlatformMgr::RegisterSendMsgCallback(SendMsgCallbackFunc* func){
    mSendMsgCallback = func;
}

void PlatformMgr::RegisterSignInserCallback(SignInUserCallbackFunc* func){
    mSignInUserCallback = func;
}

bool PlatformMgr::OnMsg(const ButtonDownMsg& msg){
    if(msg.GetAction() == 4 && mDisabling){
        DisableWiiJoypad(msg.GetUser()->GetPadNum());
    }
    else if(msg.GetAction() == 0xF){
        if(unkce4c == 0) mHomeMenuWii->AllowHomeMenu(true);
        else mHomeMenuWii->AllowHomeMenu(false);
        mHomeMenuWii->ActivateHomeMenu();
        return true;
    }
    return false;
}

bool PlatformMgr::OnMsg(const ButtonUpMsg& msg){
    if(msg.GetAction() == 0xF){
        mHomeMenuWii->UnlockHomeMenu();
    }
    return false;
}

void PlatformMgr::SetDiskError(DiskError err){
    
}