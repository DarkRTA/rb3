#include "os/Keyboard.h"
#include "os/HolmesClient.h"
#include "RVL_SDK/revolution/kbd/kbd.h"

u8 __kbd_mem[0xCC0];

int TranslateKey(_KBDKeyEvent *event) {
    unsigned int key = event->hid;
    if (0xB >= (key - 0x3A)) {
        return key + 0x157;
    } else {
        switch (key) {
        case 0x39:
            return 0x122;
        case 0x53:
            return 0x123;
        case 0x47:
            return 0x124;
        case 0x46:
            return 0x12c;
        case 0x48:
            return 0x12d;
        case 0x28:
            return 0xa;
        case 0x2a:
            return 0x8;
        case 0x2b:
            return 0x9;
        case 0x29:
            return 0x12e;
        case 0x49:
            return 0x136;
        case 0x4c:
            return 0x137;
        case 0x4a:
            return 0x138;
        case 0x4d:
            return 0x139;
        case 0x4b:
            return 0x13a;
        case 0x4e:
            return 0x13b;
        case 0x50:
            return 0x140;
        case 0x4f:
            return 0x141;
        case 0x52:
            return 0x142;
        case 0x51:
            return 0x143;
        }
        return event->unicode;
    }
}

void kbdAppAttach(_KBDDevEvent *event) {
    KBDSetCountry(event->channel, 0x11);
    KBDSetModState(event->channel, 0x100);
    KBDSetLedsRetry(event->channel, 1);
}

void kbdAppDetach(_KBDDevEvent *event) {}

void kbdAppKeyEvent(_KBDKeyEvent *event) {
    if ((event->mode & KBD_KM_REPEAT) == 0 && (event->mode & KBD_KM_DOWN) != 0) {
        if (event->hid == 0x39 || event->hid == 0x53 || event->unicode == 0xF021) {
            int modState;
            KBDGetModState(event->channel, &modState);
            KBDSetLedsRetry(event->channel, (modState >> 8) & 7);
        }
        if (0x1f < (u16)(event->unicode + 0x1000)) {
            int modState = event->modState;
            int key = TranslateKey(event);
            KeyboardSendMsg(
                key, modState & KBD_MS_SHIFT, modState & KBD_MS_CTRL, modState & KBD_MS_ALT
            );
        }
    }
}

void KeyboardInit() {
    KeyboardInitCommon();
    KBDInit(__kbd_mem, kbdAppAttach, kbdAppDetach, 0);
    KBDInitRegionUS();
    KBDInitRegionJP();
    KBDInitRegionEU();
}

void KeyboardTerminate() { KeyboardTerminateCommon(); }

void KeyboardPoll() {
    int cStatus;
    _KBDKeyEvent event;
    unsigned int i = 0;
    do {
        KBDGetChannelStatus(i, &cStatus);
        if (cStatus == 0) {
        check_key:
            if (KBDGetKey(i, &event) == 0) {
                if (event.hid != 0xFF) {
                    if (event.hid == 0)
                        goto next_chan;
                    kbdAppKeyEvent(&event);
                }
                goto check_key;
            }
        }
    next_chan:
        i++;
        if (i >= 4) {
            HolmesClientPollKeyboard();
            return;
        }
    } while (true);
}
