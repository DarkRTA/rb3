/*
    Compile unit: C:\rockband2\system\src\rndwii\screenshot.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8055E4B8 -> 0x8055EA74
*/
int g_connected; // size: 0x4, address: 0x80A540C8
int g_mail_waiting; // size: 0x4, address: 0x80A540CC
int g_hio2Initilized; // size: 0x4, address: 0x80A540D0
enum /* @enum$2171screenshot_c */ {
    HIO2_DEVICE_INVALID = -1,
    HIO2_DEVICE_EXI2USB_0 = 0,
    HIO2_DEVICE_EXI2USB_1 = 1,
    HIO2_DEVICE_MrEXI = 2,
};
enum /* @enum$2171screenshot_c */ {
    HIO2_DEVICE_INVALID = -1,
    HIO2_DEVICE_EXI2USB_0 = 0,
    HIO2_DEVICE_EXI2USB_1 = 1,
    HIO2_DEVICE_MrEXI = 2,
} g_usb_type; // size: 0x4, address: 0x80A475D8
long g_usb_handle; // size: 0x4, address: 0x80A475DC
static unsigned short s_ScreenEFBWidth; // size: 0x2, address: 0x80A475E0
static unsigned short s_ScreenEFBHeight; // size: 0x2, address: 0x80A475E2
static unsigned long s_ScreenEFBSize; // size: 0x4, address: 0x80A475E4
static unsigned short s_ScreenXFBWidth; // size: 0x2, address: 0x80A475E8
static unsigned short s_ScreenXFBHeight; // size: 0x2, address: 0x80A475EA
static unsigned long s_ScreenXFBSize; // size: 0x4, address: 0x80A475EC
// Range: 0x8055E4B8 -> 0x8055E4C4
static int HostIOEnumCallback() {
    // References
    // -> enum /* @enum$2171screenshot_c */ {
    HIO2_DEVICE_INVALID = -1,
    HIO2_DEVICE_EXI2USB_0 = 0,
    HIO2_DEVICE_EXI2USB_1 = 1,
    HIO2_DEVICE_MrEXI = 2,
} g_usb_type;
}

// Range: 0x8055E4C4 -> 0x8055E5C8
static void CopyoutPortionEFB(unsigned char * image_buffer /* r29 */, unsigned long width /* r30 */, unsigned long totalBytes /* r31 */) {
    // Local variables
    unsigned long color; // r1+0x8
    unsigned short x; // r28
    unsigned short y; // r27
    unsigned long component; // r26
    unsigned long count; // r25
}

// Range: 0x8055E5C8 -> 0x8055E64C
static void WriteScreenshotPortionEFBtoUSB(void * workingBuffer /* r30 */) {
    // Local variables
    unsigned long size; // r31

    // References
    // -> long g_usb_handle;
    // -> static unsigned short s_ScreenEFBWidth;
    // -> static unsigned long s_ScreenEFBSize;
}

enum /* @enum$2219screenshot_c */ {
    GRAB_NOT_TRANSFERRING = 0,
    GRAB_TRANSFERRING = 1,
};
// Range: 0x8055E64C -> 0x8055E7E8
static enum /* @enum$2219screenshot_c */ {
    GRAB_NOT_TRANSFERRING = 0,
    GRAB_TRANSFERRING = 1,
} GrabChunk(unsigned long mail /* r29 */) {
    // Local variables
    enum /* @enum$2219screenshot_c */ {
        GRAB_NOT_TRANSFERRING = 0,
        GRAB_TRANSFERRING = 1,
    } status; // r31
    unsigned long cmd; // r0
    unsigned long option; // r30
    void * buffer; // r31
    unsigned char * fb; // r0
    void * buffer; // r0
    unsigned short buf[16]; // r1+0x20

    // References
    // -> static unsigned short s_ScreenXFBHeight;
    // -> static unsigned short s_ScreenXFBWidth;
    // -> static unsigned short s_ScreenEFBHeight;
    // -> static unsigned short s_ScreenEFBWidth;
    // -> static unsigned long s_ScreenEFBSize;
    // -> static unsigned long s_ScreenXFBSize;
    // -> long g_usb_handle;
}

// Range: 0x8055E7E8 -> 0x8055E8C0
static void CheckMail(void * bufferXFB /* r27 */, void * workingBuffer /* r28 */) {
    // Local variables
    enum /* @enum$2219screenshot_c */ {
        GRAB_NOT_TRANSFERRING = 0,
        GRAB_TRANSFERRING = 1,
    } status; // r31
    long long escapeCount; // r30
    unsigned long mail; // r1+0x8

    // References
    // -> long g_usb_handle;
    // -> int g_mail_waiting;
}

// Range: 0x8055E8C0 -> 0x8055E8CC
static void ReceiveMailCallback() {
    // References
    // -> int g_mail_waiting;
}

// Range: 0x8055E8CC -> 0x8055E8D8
static void DisconnectCallback() {
    // References
    // -> int g_connected;
}

// Range: 0x8055E8D8 -> 0x8055E95C
static int ConnectToUSB() {
    // Local variables
    unsigned long temp; // r1+0x8

    // References
    // -> long g_usb_handle;
    // -> enum /* @enum$2171screenshot_c */ {
    HIO2_DEVICE_INVALID = -1,
    HIO2_DEVICE_EXI2USB_0 = 0,
    HIO2_DEVICE_EXI2USB_1 = 1,
    HIO2_DEVICE_MrEXI = 2,
} g_usb_type;
    // -> int g_connected;
}

// Range: 0x8055E95C -> 0x8055E978
void SCREENSHOTSetEFBSize() {
    // References
    // -> static unsigned long s_ScreenEFBSize;
    // -> static unsigned short s_ScreenEFBWidth;
    // -> static unsigned short s_ScreenEFBHeight;
}

// Range: 0x8055E978 -> 0x8055E990
void SCREENSHOTSetXFBSize() {
    // References
    // -> static unsigned long s_ScreenXFBSize;
    // -> static unsigned short s_ScreenXFBWidth;
    // -> static unsigned short s_ScreenXFBHeight;
}

enum /* @enum$22screenshot_c */ {
    VI_TVMODE_NTSC_INT = 0,
    VI_TVMODE_NTSC_DS = 1,
    VI_TVMODE_NTSC_PROG = 2,
    VI_TVMODE_PAL_INT = 4,
    VI_TVMODE_PAL_DS = 5,
    VI_TVMODE_EURGB60_INT = 20,
    VI_TVMODE_EURGB60_DS = 21,
    VI_TVMODE_EURGB60_PROG = 22,
    VI_TVMODE_MPAL_INT = 8,
    VI_TVMODE_MPAL_DS = 9,
    VI_TVMODE_MPAL_PROG = 10,
    VI_TVMODE_DEBUG_INT = 12,
    VI_TVMODE_DEBUG_PAL_INT = 16,
    VI_TVMODE_DEBUG_PAL_DS = 17,
};
enum /* @enum$23screenshot_c */ {
    VI_XFBMODE_SF = 0,
    VI_XFBMODE_DF = 1,
};
struct _GXRenderModeObj {
    // total size: 0x3C
    enum /* @enum$22screenshot_c */ {
        VI_TVMODE_NTSC_INT = 0,
        VI_TVMODE_NTSC_DS = 1,
        VI_TVMODE_NTSC_PROG = 2,
        VI_TVMODE_PAL_INT = 4,
        VI_TVMODE_PAL_DS = 5,
        VI_TVMODE_EURGB60_INT = 20,
        VI_TVMODE_EURGB60_DS = 21,
        VI_TVMODE_EURGB60_PROG = 22,
        VI_TVMODE_MPAL_INT = 8,
        VI_TVMODE_MPAL_DS = 9,
        VI_TVMODE_MPAL_PROG = 10,
        VI_TVMODE_DEBUG_INT = 12,
        VI_TVMODE_DEBUG_PAL_INT = 16,
        VI_TVMODE_DEBUG_PAL_DS = 17,
    } viTVmode; // offset 0x0, size 0x4
    unsigned short fbWidth; // offset 0x4, size 0x2
    unsigned short efbHeight; // offset 0x6, size 0x2
    unsigned short xfbHeight; // offset 0x8, size 0x2
    unsigned short viXOrigin; // offset 0xA, size 0x2
    unsigned short viYOrigin; // offset 0xC, size 0x2
    unsigned short viWidth; // offset 0xE, size 0x2
    unsigned short viHeight; // offset 0x10, size 0x2
    enum /* @enum$23screenshot_c */ {
        VI_XFBMODE_SF = 0,
        VI_XFBMODE_DF = 1,
    } xFBmode; // offset 0x14, size 0x4
    unsigned char field_rendering; // offset 0x18, size 0x1
    unsigned char aa; // offset 0x19, size 0x1
    unsigned char sample_pattern[12][2]; // offset 0x1A, size 0x18
    unsigned char vfilter[7]; // offset 0x32, size 0x7
};
// Range: 0x8055E990 -> 0x8055E9D0
void SCREENSHOTSetRenderModeObj(struct _GXRenderModeObj * obj /* r31 */) {}

// Range: 0x8055E9D0 -> 0x8055EA74
void SCREENSHOTService(void * bufferXFB /* r30 */, void * workingBuffer /* r31 */) {
    // References
    // -> int g_mail_waiting;
    // -> int g_connected;
    // -> int g_hio2Initilized;
}


