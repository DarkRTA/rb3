#ifndef OS_HOMEMENU_WII_H
#define OS_HOMEMENU_WII_H
#include "os/DiscErrorMgr_Wii.h"
#include "types.h"
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

    bool mAllowHomeMenu; // 0x4
    bool mHomeMenuActive; // 0x5
    bool mSoundActive; // 0x6
    bool mInGame; // 0x7
    bool mForcedHomeMenu; // 0x8
    bool unk_0x9;
    bool unk_0xA;
    u32 unk_0xC, unk_0x10;
    bool mBanIconActive; // 0x14
    u8 unk_0x15;
    int unk_0x18;
    int unk_0x1C;
    u8 unk_0x20, unk_0x21, unk_0x22;
    int unk_0x24, unk_0x28;
    u8 unk_0x2C;

    int pad[2];

    u8 unk_0x38;
    std::list<int> unk_0x3C;
    int unk_0x44;
};

#endif
