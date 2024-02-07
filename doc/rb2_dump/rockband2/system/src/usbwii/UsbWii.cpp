/*
    Compile unit: C:\rockband2\system\src\usbwii\UsbWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8059D4E0 -> 0x8059E19C
*/
long callback; // size: 0x4, address: 0x80A54868
struct HIDDeviceDescriptor {
    // total size: 0x14
    unsigned char bLength; // offset 0x0, size 0x1
    unsigned char bDescriptorType; // offset 0x1, size 0x1
    unsigned short bcdUSB; // offset 0x2, size 0x2
    unsigned char bDeviceClass; // offset 0x4, size 0x1
    unsigned char bDeviceSubClass; // offset 0x5, size 0x1
    unsigned char bDeviceProtocol; // offset 0x6, size 0x1
    unsigned char bMaxPacketSize; // offset 0x7, size 0x1
    unsigned short idVendor; // offset 0x8, size 0x2
    unsigned short idProduct; // offset 0xA, size 0x2
    unsigned short bcdDevice; // offset 0xC, size 0x2
    unsigned char iManufacturer; // offset 0xE, size 0x1
    unsigned char iProduct; // offset 0xF, size 0x1
    unsigned char iSerialNumber; // offset 0x10, size 0x1
    unsigned char bNumConfigurations; // offset 0x11, size 0x1
    unsigned char pad[2]; // offset 0x12, size 0x2
};
struct HIDConfigurationDescriptor {
    // total size: 0xC
    unsigned char bLength; // offset 0x0, size 0x1
    unsigned char bDescriptorType; // offset 0x1, size 0x1
    unsigned short wTotalLength; // offset 0x2, size 0x2
    unsigned char bNumInterfaces; // offset 0x4, size 0x1
    unsigned char bConfigurationValue; // offset 0x5, size 0x1
    unsigned char iConfiguration; // offset 0x6, size 0x1
    unsigned char bmAttributes; // offset 0x7, size 0x1
    unsigned char bMaxPower; // offset 0x8, size 0x1
    unsigned char pad[3]; // offset 0x9, size 0x3
};
struct HIDInterfaceDescriptor {
    // total size: 0xC
    unsigned char bLength; // offset 0x0, size 0x1
    unsigned char bDescriptorType; // offset 0x1, size 0x1
    unsigned char bInterfaceNumber; // offset 0x2, size 0x1
    unsigned char bAlternateSetting; // offset 0x3, size 0x1
    unsigned char bNumEndpoints; // offset 0x4, size 0x1
    unsigned char bInterfaceClass; // offset 0x5, size 0x1
    unsigned char bInterfaceSubClass; // offset 0x6, size 0x1
    unsigned char bInterfaceProtocol; // offset 0x7, size 0x1
    unsigned char iInterface; // offset 0x8, size 0x1
    unsigned char pad[3]; // offset 0x9, size 0x3
};
struct HIDEndpointDescriptor {
    // total size: 0x8
    unsigned char bLength; // offset 0x0, size 0x1
    unsigned char bDescriptorType; // offset 0x1, size 0x1
    unsigned char bEndpointAddress; // offset 0x2, size 0x1
    unsigned char bmAttributes; // offset 0x3, size 0x1
    unsigned short wMaxPacketSize; // offset 0x4, size 0x2
    unsigned char bInterval; // offset 0x6, size 0x1
    unsigned char pad[1]; // offset 0x7, size 0x1
};
struct HIDDevice {
    // total size: 0x20
    long fd; // offset 0x0, size 0x4
    unsigned short vid; // offset 0x4, size 0x2
    unsigned short pid; // offset 0x6, size 0x2
    unsigned char iInterface; // offset 0x8, size 0x1
    unsigned char endpoint_address_in; // offset 0x9, size 0x1
    unsigned char endpoint_address_out; // offset 0xA, size 0x1
    unsigned char inst; // offset 0xB, size 0x1
    struct HIDDeviceDescriptor * p_hdd; // offset 0xC, size 0x4
    struct HIDConfigurationDescriptor * p_hcd; // offset 0x10, size 0x4
    struct HIDInterfaceDescriptor * p_hid; // offset 0x14, size 0x4
    struct HIDEndpointDescriptor * p_hed0; // offset 0x18, size 0x4
    struct HIDEndpointDescriptor * p_hed1; // offset 0x1C, size 0x4
};
enum UsbState {
    UsbInactive = 0,
    UsbInit = 1,
    UsbReady = 2,
    UsbReading = 3,
    UsbDone = 4,
};
struct UsbDevice {
    // total size: 0x80
    unsigned char packet[64]; // offset 0x0, size 0x40
    unsigned char output[8]; // offset 0x40, size 0x8
    struct HIDDevice * device; // offset 0x48, size 0x4
    enum UsbType type; // offset 0x4C, size 0x4
    enum UsbState state; // offset 0x50, size 0x4
    unsigned char ledSetup; // offset 0x54, size 0x1
    signed short ledNum; // offset 0x56, size 0x2
    unsigned char calbertSetup; // offset 0x58, size 0x1
    signed short calbertSetting; // offset 0x5A, size 0x2
    int buttonMask; // offset 0x5C, size 0x4
    int lstickX; // offset 0x60, size 0x4
    int lstickY; // offset 0x64, size 0x4
    int rstickX; // offset 0x68, size 0x4
    int rstickY; // offset 0x6C, size 0x4
    unsigned char pressures[4]; // offset 0x70, size 0x4
};
struct UsbDevice devices[4]; // size: 0x200, address: 0x80983CC0
// Range: 0x8059D4E0 -> 0x8059D4E8
static void UsbOpenCloseCallback() {
    // References
    // -> long callback;
}

enum UsbType {
    UsbNone = 0,
    UsbGuitar = 1,
    UsbGuitarRb2 = 2,
    UsbDrums = 3,
    UsbDrumsRb2 = 4,
};
// Range: 0x8059D4E8 -> 0x8059D4F0
static void UsbDetachHandler() {
    // References
    // -> long callback;
}

// Range: 0x8059D4F0 -> 0x8059D5FC
static void UsbReadCallback() {
    // References
    // -> struct UsbDevice devices[4];
}

static class Timer * _t; // size: 0x4, address: 0x80A5486C
// Range: 0x8059D5FC -> 0x8059D6EC
static void UsbLedCallback(long error /* r30 */, unsigned long user /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> static class Timer * _t;
}

struct _HIDClient {
    // total size: 0xC
    struct _HIDClient * next; // offset 0x0, size 0x4
    int (* attachHandler)(struct _HIDClient *, struct HIDDevice *, unsigned long); // offset 0x4, size 0x4
    unsigned long user; // offset 0x8, size 0x4
};
class UsbWii {
    // total size: 0x10
    struct _HIDClient client; // offset 0x0, size 0xC
    void * usbMem; // offset 0xC, size 0x4
};
// Range: 0x8059D6EC -> 0x8059D7A0
void * UsbWii::UsbWii(class UsbWii * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x8059D7A0 -> 0x8059D81C
void * UsbWii::~UsbWii(class UsbWii * const this /* r30 */) {
    // References
    // -> long callback;
}

// Range: 0x8059D81C -> 0x8059DA60
void UsbWii::Poll() {
    // Local variables
    long he; // r0
    int interrupts; // r31
    int i; // r30
    int j; // r5

    // References
    // -> struct UsbDevice devices[4];
}

static int _x; // size: 0x4, address: 0x80A54874
// Range: 0x8059DA60 -> 0x8059DB30
unsigned char UsbWii::OpenLib(class UsbWii * const this /* r31 */) {
    // Local variables
    long he; // r0

    // References
    // -> long callback;
    // -> static int _x;
}

// Range: 0x8059DB30 -> 0x8059DBB8
unsigned char UsbWii::CloseLib(class UsbWii * const this /* r31 */) {
    // Local variables
    long he; // r0

    // References
    // -> long callback;
}

// Range: 0x8059DBB8 -> 0x8059DBCC
long UsbWii::WaitForCallback() {
    // References
    // -> long callback;
}

// Range: 0x8059DBCC -> 0x8059DC90
enum UsbType UsbWii::GetType() {}

// Range: 0x8059DC90 -> 0x8059DD64
int UsbWii::AddDevice(struct HIDDevice * device /* r27 */, enum UsbType type /* r28 */) {
    // Local variables
    int i; // r5
    int i; // r29

    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059DD64 -> 0x8059DDF8
void UsbWii::ClearDevice(int num /* r31 */) {
    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059DDF8 -> 0x8059DE2C
unsigned char UsbWii::IsActive() {
    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059DE2C -> 0x8059E054
enum JoypadType UsbWii::ReadInstrument(int num /* r26 */, unsigned int * buttons /* r24 */, char * lstickx /* r25 */, char * lsticky /* r27 */, char * rstickx /* r28 */, char * rsticky /* r29 */, unsigned int * pressures /* r30 */) {
    // Local variables
    long he; // r0

    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059E054 -> 0x8059E0B8
enum JoypadType UsbWii::GetJoypadType() {
    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059E0B8 -> 0x8059E114
void UsbWii::SetLED(int num /* r30 */, int led /* r31 */) {
    // References
    // -> struct UsbDevice devices[4];
}

// Range: 0x8059E114 -> 0x8059E19C
void UsbWii::SetCalbert(int num /* r30 */, int calbertSetting /* r31 */) {
    // References
    // -> struct UsbDevice devices[4];
}


