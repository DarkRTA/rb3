#include "HomeMenu_Wii.h"
#include "os/File.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"

DECOMP_FORCEACTIVE(HomeMenu_Wii, "_unresolved func.\n")

void unresolved_hmbModule(){
    OSReport("\nError: call hmbModule unlinked function.\n");
}

void HmbRsoInit(){
    MILO_WARN("hmbrso_r.rso");
}

void HmbRsoTerminate(){

}

HomeMenu::HomeMenu() : mAllowHomeMenu(false), mHomeMenuActive(false), mSoundActive(true), 
    mInGame(false), mForcedHomeMenu(false), unk_0x9(false), unk_0xA(false), mHomeMenuLocked(0), 
    unk_0x10(5), mBanIconActive(false), mBanIconMode(0), mBanIconTime(0), mIconTpl(0), mBanIconAlpha(0),
    mSDIconActive(0), mSDIconMode(0), mSDIconTime(0), mSDIconTpl(0), mSDIconAlpha(0), unk_0x38(0), unk_0x44(1) { }

void HomeMenu::PreInit(){
    if(!mIconTpl){
        mIconTpl = (TPLPalette*)ReadDvdFile(MakeString("%s/HomeMenu/homeBtnIcon.tpl", FileSystemRoot()), 0);
        MILO_ASSERT(mIconTpl, 0x9E);
        TPLBind(mIconTpl);
    }
}

void HomeMenu::Init(){
    MILO_ASSERT(!mSDIconTpl, 0xA5);
    PreInit();
    mSDIconTpl = (TPLPalette*)ReadDvdFile(MakeString("%s/HomeMenu/SdCard.tpl", FileSystemRoot()), 0);
    MILO_ASSERT(mSDIconTpl, 0xAA);
    TPLBind(mSDIconTpl);
}

void HomeMenu::Begin(){
    MILO_ASSERT(mIconTpl, 0xB2);
    unk_0x38 = false;
    ThePlatformMgr.GetDiscErrorMgrWii()->RegisterCallback(this);
    HmbRsoInit();
    unk34 = (TPLPalette*)ReadDvdFile(MakeString("%s/HomeMenu/HomeButton%d/HomeButtonSe.arc", FileSystemRoot(), 2), 0);
    unk30 = _MemAlloc(0x18700, 0x20);
    InitHomeMenuButtonInfo();
    ThePlatformMgr.GetDiscErrorMgrWii()->UnregisterCallback(this);
}

void HomeMenu::End(){

}

void HomeMenu::AllowHomeMenu(bool allow){
    if(mHomeMenuLocked == 0) mAllowHomeMenu = allow;
    else mAllowHomeMenu = false;
}

void HomeMenu::ActivateBanIcon(bool ban) {
    mBanIconActive = ban;
    char mode = 3;
    if(ban) mode = 0;
    mBanIconMode = mode;
    mBanIconTime = 0;
    mBanIconAlpha = 0;
}

void HomeMenu::ActivateSDIcon(bool act){
    mSDIconActive = act;
    char mode = 3;
    if(act) mode = 0;
    mSDIconMode = mode;
    mSDIconTime = 0;
    mSDIconAlpha = 0;
}

void HomeMenu::SetHomeMenuActive(bool act){
    if(act && !mBanIconActive){
        mHomeMenuActive = true;
        Begin();
    }
}

void HomeMenu::UnlockHomeMenu(){
    if(mHomeMenuLocked > 0) mHomeMenuLocked--;
}

void HomeMenu::DiscErrorStart(){ unk_0x38 = 1; }
void HomeMenu::DiscErrorEnd(){ unk_0x38 = 1; }
void HomeMenu::DrawBannedIcon(unsigned char s){ NotifyCallbacksBannedDraw(s); }
void HomeMenu::DrawSDIcon(unsigned char s){ NotifyCallbacksSDDraw(s); }

void HomeMenu::RegisterCallback(HomeMenu::Callback* cb){
    mCallbacks.push_back(cb);
}

void HomeMenu::NotifyCallbacksOpen(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->HomeMenuOpen(mInGame);
    }
}

void HomeMenu::NotifyCallbacksClose(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->HomeMenuClose(mInGame);
    }
}

void HomeMenu::NotifyCallbacksDraw(){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->HomeMenuDraw();
    }
}

void HomeMenu::NotifyCallbacksBannedDraw(short s){
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->HomeMenuBannedDraw(s, mIconTpl);
    }
}

void HomeMenu::NotifyCallbacksSDDraw(short s){
    MILO_ASSERT(mSDIconTpl, 0x354);
    for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
        (*it)->SDIconDraw(s, mSDIconTpl);
    }
}