#pragma once
#include "os/DiscErrorMgr_Wii.h"
#include "types.h"
#include <revolution/TPL.h>
#include <list>

class HomeMenu : public DiscErrorMgrWii::Callback {
public:
    class Callback {
    public:
        virtual void HomeMenuOpen(bool){}
        virtual void HomeMenuClose(bool){}
        virtual void HomeMenuDraw(){}
        virtual void HomeMenuBannedDraw(short, void*){}
        virtual void SDIconDraw(short, void*){}
    };

    HomeMenu();
    virtual void DiscErrorStart();
    virtual void DiscErrorEnd();
    void ShowBannedIcon();
    void ActivateBanIcon(bool);
    void* ReadDvdFile(const char*, unsigned long*);
    void PreInit();
    void Init();
    void Begin();
    void InitHomeMenuButtonInfo();
    void End();
    void AllowHomeMenu(bool);
    void ActivateSDIcon(bool);
    void SetHomeMenuActive(bool);
    void UnlockHomeMenu();
    void RegisterCallback(Callback*);
    void NotifyCallbacksOpen();
    void NotifyCallbacksClose();
    void NotifyCallbacksDraw();
    void NotifyCallbacksBannedDraw(short);
    void NotifyCallbacksSDDraw(short);
    void DrawBannedIcon(unsigned char);
    void DrawSDIcon(unsigned char);
    void ActivateHomeMenu();

    bool mAllowHomeMenu; // 0x4
    bool mHomeMenuActive; // 0x5
    bool mSoundActive; // 0x6
    bool mInGame; // 0x7
    bool mForcedHomeMenu; // 0x8
    bool unk_0x9;
    bool unk_0xA;
    int mHomeMenuLocked; // 0xc
    u32 unk_0x10;
    bool mBanIconActive; // 0x14
    char mBanIconMode; // 0x15
    unsigned long mBanIconTime; // 0x18
    TPLPalette* mIconTpl; // 0x1c
    unsigned char mBanIconAlpha; // 0x20
    bool mSDIconActive; // 0x21
    char mSDIconMode; // 0x22
    unsigned long mSDIconTime; // 0x24
    TPLPalette* mSDIconTpl; // 0x28
    unsigned char mSDIconAlpha; // 0x2c
    void* unk30; // 0x30
    TPLPalette* unk34; // 0x34
    u8 unk_0x38;
    std::list<Callback*> mCallbacks; // 0x3c
    int unk_0x44;
};