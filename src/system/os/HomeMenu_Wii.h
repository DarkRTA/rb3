#ifndef OS_HOMEMENU_WII_H
#define OS_HOMEMENU_WII_H
#include "os/DiscErrorMgr_Wii.h"

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

    bool mAllowHomeMenu;
    bool mHomeMenuActive;
    bool mSoundActive;
    bool mInGame;
    bool mForcedHomeMenu;
    // there's more members, I just wanted enough for PlatformMgr for now lol

};

#endif
