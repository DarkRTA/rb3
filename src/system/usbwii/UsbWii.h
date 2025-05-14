#pragma once
#include "RVL_SDK/revolution/usb/hid.h"
#include "os/Joypad.h"

#define OPENCLOSE_START_MAGIC 0x12341234

enum UsbFlags {
    kUsbFlagHasLED = 0x1,
    kUsbFlagActive = 0x10,
    kUsbFlagInactive = 0x20
};

enum UsbState {
    kUsbStateInactive = 0,
    kUsbStateInit = 1,
    kUsbStateReady = 2,
    kUsbStateUnk = 3,
    kUsbStateReading = 4,
    kUsbStateDone = 5
};

typedef struct _UsbDevice {
    HIDDevice *dd; // 0x0
    u32 type; // 0x4
    u32 state; // 0x8
    u32 flags; // 0xC
    u32 inactivity; // 0x10
    u8 unk_0x14[0x2]; // 0x14
    s16 ledNum; // 0x16
    u32 unk6; // 0x18
    u32 buttonMask; // 0x1C
    u16 lstickX; // 0x20
    u16 lstickY; // 0x22
    u16 rstickX; // 0x24
    u16 rstickY; // 0x26
    u8 pressures[4]; // 0x28
    u8 extended[0x10]; // 0x2C
    u8 unk_0x3C[0x4]; // 0x3C
    u8 packet[0x40]; // 0x40
    u8 unk_0x80[0x80]; // 0x80
} UsbDevice; // 0x100

enum UsbType {
    kUsbNone = 0,
    kUsbGuitar = 1,
    kUsbGuitarRb2 = 2,
    kUsbDrums = 3,
    kUsbDrumsRb2 = 4,
    kUsbMidiGuitarMustang = 5,
    kUsbMidiGuitarSquire = 6,
    kUsbMidiKeyboard = 7,
    kUsbUnused = 8,
    kUsbMidiKeyboardMpa = 9,
    kUsbMidiDrums = 10,
    kUsbTypeMax = 11,
};

class UsbWii {
public:
    UsbWii();
    ~UsbWii();

    static UsbDevice sDevices[4];
    static void ClearDevice(int num);
    static bool AddDevice(HIDDevice *device, UsbType type);
    static int GetType(HIDDevice *device);
    static void DbgVerifyNoBufferOverrun(int unk);
    static void KeepAlive(int unk);
    static bool HasUnifiedLEDCalbertMsg(UsbType type);
    static void RequestReadInstr(int num, bool unk);

    static inline bool IsDeviceActive(int num);

    static int
    UsbAttachHandler(_HIDClient *client, HIDDevice *device, unsigned long user);
    static int UsbDetachHandler(long result, unsigned long user);
    static void UsbOpenCloseCallback(long result, unsigned long unk);
    static void UsbReadInstrCallback(
        HIDDevice *device, long result, u8 *bytes, unsigned long length, unsigned long user
    );

    bool OpenLib();
    bool CloseLib();
    int GetJoypadType(int num) const;
    bool IsActive(int num) const;
    void SetInactive(int num);
    void SetLED(int num, int led);
    int WaitForUSBOpenCloseResult();

    _HIDClient client;
    void *usbMem;

    static bool mDiscError;
    static int sUSBOpenCloseResult;
};
