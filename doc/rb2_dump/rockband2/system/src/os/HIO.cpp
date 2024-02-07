/*
    Compile unit: C:\rockband2\system\src\os\HIO.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CDDFC -> 0x805CE234
*/
static unsigned char gInitialized; // size: 0x1, address: 0x80A54E18
enum HIO2DeviceType {
    HIO2_DEVICE_INVALID = -1,
    HIO2_DEVICE_EXI2USB_0 = 0,
    HIO2_DEVICE_EXI2USB_1 = 1,
    HIO2_DEVICE_MrEXI = 2,
};
static enum HIO2DeviceType gDevice; // size: 0x4, address: 0x80A478E0
static long gHandle; // size: 0x4, address: 0x80A478E4
// Range: 0x805CDDFC -> 0x805CDE08
static int DeviceEnumCB() {
    // References
    // -> static enum HIO2DeviceType gDevice;
}

// Range: 0x805CDE08 -> 0x805CDE10
long HIOHandle() {
    // References
    // -> static long gHandle;
}

// Range: 0x805CDE10 -> 0x805CDEA4
void HIOInit() {
    // References
    // -> static long gHandle;
    // -> static enum HIO2DeviceType gDevice;
    // -> static unsigned char gInitialized;
}

// Range: 0x805CDEA4 -> 0x805CDECC
void HIOTerminate() {
    // References
    // -> static unsigned char gInitialized;
}

// Range: 0x805CDECC -> 0x805CDEFC
unsigned char HIOInitialized() {
    // References
    // -> static long gHandle;
    // -> static enum HIO2DeviceType gDevice;
    // -> static unsigned char gInitialized;
}

// Range: 0x805CDEFC -> 0x805CE088
int HIOReadSharedMemory(unsigned int addr /* r29 */, void * data /* r30 */, int bytes /* r1+0x20 */) {
    // Local variables
    int size; // r1+0x28
    int actual; // r31
    char buffer[4096]; // r1+0x40

    // References
    // -> static long gHandle;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CE088 -> 0x805CE234
int HIOWriteSharedMemory(unsigned int addr /* r29 */, void * data /* r30 */, int bytes /* r1+0x20 */) {
    // Local variables
    int size; // r1+0x28
    int actual; // r31
    char buffer[4096]; // r1+0x40

    // References
    // -> static long gHandle;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


