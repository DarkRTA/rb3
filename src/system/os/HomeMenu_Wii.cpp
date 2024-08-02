#include "HomeMenu_Wii.h"

HomeMenu::HomeMenu() : mAllowHomeMenu(false), mHomeMenuActive(false), mSoundActive(true), 
    mInGame(false), mForcedHomeMenu(false), unk_0x9(false), unk_0xA(false), unk_0xC(0), 
    unk_0x10(5), mBanIconActive(false), unk_0x15(0), unk_0x18(0), unk_0x1C(0), unk_0x20(0),
    unk_0x21(0), unk_0x22(0), unk_0x24(0), unk_0x28(0), unk_0x2C(0), unk_0x38(0), unk_0x44(1) { }

void HomeMenu::ActivateBanIcon(bool b) {
    mBanIconActive = b;
    if (!b) {
        b = 0;
    }
}

void HomeMenu::DiscErrorStart() {

}
