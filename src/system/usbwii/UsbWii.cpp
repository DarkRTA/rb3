#include "usbwii/UsbWii.h"
#include "utl/MemMgr.h"

UsbWii *gsTheUsbWii;

// static u32 UsbWii::sUSBOpenCloseResult = 0;

void UsbWii::ClearDevice(int num) {
    UsbDevice *device = &sDevices[num];
    memset(device, 0, sizeof(UsbDevice));
    device->state = 0;
    device->type = kUsbNone;
    device->ledNum = -1;
    device->unk6 = 0;
}

void UsbWii::DbgVerifyNoBufferOverrun(int unk) {}

void UsbWii::KeepAlive(int unk) {}

bool UsbWii::AddDevice(HIDDevice *device, UsbType type) {
    // check if we already have this device in our list
    for (int i = 0; i < 4; i++) {
        if (sDevices[i].dd == device) {
            sDevices[i].state = 0;
            return false;
        }
    }
    // if we don't, find a free spot and add the device
    for (int i = 0; i < 4; i++) {
        if (sDevices[i].dd == NULL) {
            sDevices[i].dd = device;
            sDevices[i].type = type;
            return true;
        }
    }
    // failed to add the device
    return false;
}

int UsbWii::UsbAttachHandler(_HIDClient *client, HIDDevice *device, unsigned long user) {
    if (!mDiscError) {
        if (user != NULL) {
            UsbType type = (UsbType)GetType(device);
            if (type != kUsbNone && (type > kUsbNone && type < kUsbTypeMax)) {
                return AddDevice(device, (UsbType)type);
            }
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            if (sDevices[i].dd == device) {
                ClearDevice(i);
            }
        }
    }
    return 0;
}

int UsbWii::GetType(HIDDevice *device) {
    // Harmonix Music Systems / Mad Catz vendor ID
    if (device->vid == 0x1BAD) {
        switch (device->pid) {
        // MIDI Pro Adapter, Drums
        case 0x3138:
            return kUsbMidiDrums;
        // RB1 Drums
        case 5:
            return kUsbDrums;
        // RB1 Guitar
        case 4:
            return kUsbGuitar;
        // RB2 Guitar
        case 0x3010:
            return kUsbGuitarRb2;
        // RB2 Drums
        case 0x3110:
            return kUsbDrumsRb2;
        // MIDI Pro Adapter, Keyboard
        case 0x3338:
            return kUsbMidiKeyboardMpa;
        // RB3 Keyboard
        case 0x3330:
            return kUsbMidiKeyboard;
        // RB3 Squire / MPA in Squire mode
        case 0x3538:
        case 0x3530:
            return kUsbMidiGuitarSquire;
        // RB3 Mustang / MPA in Mustang mode
        case 0x3438:
        case 0x3430:
            return kUsbMidiGuitarMustang;
        }
    }
#ifdef MILO_DEBUG
    // only in this build does the game check for PS3 instruments
    // Sony Computer Entertainment vendor ID
    if (device->vid != 0x12BA) {
        return kUsbNone;
    } else {
        // PS3 Drums
        if (device->pid == 0x210)
            return kUsbDrums;
        // PS3 Guitar
        else if (device->pid == 0x200)
            return kUsbGuitar;
        else
            return kUsbNone;
    }
#endif
}

bool UsbWii::HasUnifiedLEDCalbertMsg(UsbType type) {
    switch (type) {
    case kUsbGuitarRb2:
    case kUsbUnused:
        return true;
    }
    return false;
}

int UsbWii::GetJoypadType(int num) const {
    switch (sDevices[num].type) {
    case kUsbDrums:
        return kJoypadWiiHxDrums;
    case kUsbDrumsRb2:
        return kJoypadWiiHxDrumsRb2;
    case kUsbGuitar:
        return kJoypadWiiHxGuitar;
    case kUsbGuitarRb2:
        return kJoypadWiiHxGuitarRb2;
    case kUsbUnused:
        return kJoypadWiiCoreGuitar;
    case kUsbMidiKeyboardMpa:
        return kJoypadWiiMidiBoxKeyboard;
    case kUsbMidiDrums:
        return kJoypadWiiMidiBoxDrums;
    case kUsbMidiGuitarMustang:
        return kJoypadWiiButtonGuitar;
    case kUsbMidiGuitarSquire:
        return kJoypadWiiRealGuitar22Fret;
    case kUsbMidiKeyboard:
        return kJoypadWiiKeytar;
    }
    return 0;
}

inline bool UsbWii::IsDeviceActive(int num) {
    bool stateValid = false;
    bool deviceValid = false;
    if (num < 4 && sDevices[num].type != kUsbNone) {
        deviceValid = true;
    }
    if (deviceValid && sDevices[num].state >= 2) {
        stateValid = true;
    }
    if (stateValid && (sDevices[num].flags & kUsbFlagActive) == 0) {
        return false;
    }
    return true;
}

bool UsbWii::IsActive(int num) const { return IsDeviceActive(num); }

void UsbWii::UsbOpenCloseCallback(long result, unsigned long unk) {
    sUSBOpenCloseResult = result;
}

bool UsbWii::OpenLib() {
    static int _x = MemFindHeap("main");
    MemPushHeap(_x);
    usbMem = _MemAlloc(0x3AE0, 0x20);
    MemPopHeap();
    if (usbMem != NULL) {
        sUSBOpenCloseResult = OPENCLOSE_START_MAGIC;
        int r;
        do {
            r = HIDOpenAsync(usbMem, UsbOpenCloseCallback, 0);
            if (r == 0) {
                return WaitForUSBOpenCloseResult();
            }
        } while (r == -5);
    }
    return false;
}

void UsbWii::SetLED(int num, int led) {
    if (!IsDeviceActive(num)) {
        return;
    }
    sDevices[num].flags |= kUsbFlagHasLED;
    sDevices[num].ledNum = led;
}

void UsbWii::SetInactive(int num) {
    if (num >= 4)
        return;
    sDevices[num].flags = (sDevices[num].flags & ~kUsbFlagActive) | kUsbFlagInactive;
}

void UsbWii::UsbReadInstrCallback(
    HIDDevice *device, long result, u8 *bytes, unsigned long length, unsigned long user
) {
    // error during read
    if (result != 0) {
        if (sDevices[user].state == kUsbStateDone) {
            sDevices[user].state = kUsbStateReading;
            if ((sDevices[user].flags & kUsbFlagInactive) == 0) {
                sDevices[user].inactivity = 0;
            }
        }
        // fatal error / device disconnected?
        if (result == -4) {
            ClearDevice(user);
            return;
        }
        return;
    }
    // D-PAD correction
    if ((sDevices[user].packet[2] & 8) == 0) {
        switch (sDevices[user].packet[2]) {
        case 0:
            sDevices[user].packet[2] = 1;
            break;
        case 2:
            sDevices[user].packet[2] = 8;
            break;
        case 4:
            sDevices[user].packet[2] = 2;
            break;
        case 6:
            sDevices[user].packet[2] = 4;
            break;
        }
    } else {
        sDevices[user].packet[2] = 0;
    }
    // fill in the button mask
    sDevices[user].buttonMask = (sDevices[user].packet[2] << 16)
        | (sDevices[user].packet[1] << 8) | sDevices[user].packet[0];
    // fill in the stick values
    sDevices[user].lstickX = sDevices[user].packet[3];
    sDevices[user].lstickY = sDevices[user].packet[4];
    sDevices[user].rstickX = sDevices[user].packet[5];
    sDevices[user].rstickY = sDevices[user].packet[6];
    // fill in the pressure values
    sDevices[user].pressures[0] = sDevices[user].packet[11];
    sDevices[user].pressures[1] = sDevices[user].packet[12];
    sDevices[user].pressures[2] = sDevices[user].packet[13];
    sDevices[user].pressures[3] = sDevices[user].packet[14];
    // copy over the extra values
    for (int i = 0; i < 0x10; i++) {
        sDevices[user].extended[i] = sDevices[user].packet[5 + i];
    }
    // check if buttons are pressed for inactivity reading
    int buttonsPressed = sDevices[user].buttonMask;
    if (sDevices[user].type == kUsbGuitar || sDevices[user].type == kUsbGuitarRb2)
        buttonsPressed &= ~0x20;
    if (buttonsPressed == 0) {
        if ((sDevices[user].flags & kUsbFlagInactive) != 0)
            sDevices[user].inactivity += 1;
    } else if ((sDevices[user].flags & kUsbFlagInactive) == 0) {
        sDevices[user].flags |= kUsbFlagActive;
    } else {
        sDevices[user].inactivity = 0;
    }
    // send another request if we're done reading
    if (sDevices[user].state == kUsbStateDone) {
        sDevices[user].state = kUsbStateReading;
        RequestReadInstr(user, false);
        return;
    }
}

UsbWii::UsbWii() {
    usbMem = NULL;
    for (int i = 0; i < 4; i++)
        ClearDevice(i);
    OpenLib();
    HIDRegisterClient(&client, UsbAttachHandler);
    gsTheUsbWii = this;
}

UsbWii::~UsbWii() {
    gsTheUsbWii = NULL;
    sUSBOpenCloseResult = OPENCLOSE_START_MAGIC;
    HIDUnregisterClientAsync(&client, UsbDetachHandler, NULL);
    WaitForUSBOpenCloseResult();
    CloseLib();
}
