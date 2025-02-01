#include "os/ContentMgr_Wii.h"

WiiContent::WiiContent(
    Symbol s, unsigned long long ux, unsigned int ui, bool b1, bool b2
) {
    mName = s;
    mTitleId = ux;
    mContentId = ui;
    unk2c = b1;
    unk20 = 3;
    unk24 = 0;
    unk31 = 0;
    unk32 = 0;
    unk8 = b2;
    unk30 = 0;
    unk1c = 0;
}

WiiContent::~WiiContent() {
    int oldState = unk8;
    // switch/case for unk8
    if (oldState > 1 && oldState - 9U > 1) {
        if (oldState == 2 || oldState == 4) {
            Unmount();
            while (unk8 == 2) {
                Timer::Sleep(2);
                Poll();
            }
        } else if (oldState != 5) {
            MILO_LOG("Unknown state: %d", oldState);
        }
    }
}

WiiContentMgr::WiiContentMgr() {}