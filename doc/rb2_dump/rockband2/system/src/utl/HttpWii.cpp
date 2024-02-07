/*
    Compile unit: C:\rockband2\system\src\utl\HttpWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8060BE4C -> 0x8060C8C4
*/
class HttpWii TheHttpWii; // size: 0x290, address: 0x80989C08
static char * const table[16]; // size: 0x40, address: 0x8084FF88
// Range: 0x8060BE4C -> 0x8060BEBC
char * HttpWii::GetNHTTPErrorString() {
    // Local variables
    const char * system_error; // r0

    // References
    // -> static char * const table[16];
}

// Range: 0x8060BEBC -> 0x8060BF0C
void * HttpWii::HttpWii(class HttpWii * const this /* r30 */) {}

// Range: 0x8060BF0C -> 0x8060BF4C
void * HttpWii::~HttpWii(class HttpWii * const this /* r31 */) {}

static class Symbol default_server; // size: 0x4, address: 0x80A5543C
// Range: 0x8060BF4C -> 0x8060C2DC
void HttpWii::Init(class HttpWii * const this /* r31 */) {
    // Local variables
    class Symbol servertype; // r1+0x2C
    class DataArray * netcache; // r0
    class String serverSSLPath1; // r1+0x54
    class String serverSSLPath2; // r1+0x48
    class File * f; // r27
    class File * f2; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> static class Symbol default_server;
}

// Range: 0x8060C2DC -> 0x8060C320
void HttpWii::Terminate(class HttpWii * const this /* r31 */) {}

// Range: 0x8060C320 -> 0x8060C4C8
int HttpWii::GetFileAsync(class HttpWii * const this /* r25 */, const char * path /* r26 */, void * buffer /* r27 */, int bufSize /* r28 */) {
    // Local variables
    int retVal; // r0
    int next; // r31

    // References
    // -> class Debug TheDebug;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8060C4C8 -> 0x8060C7FC
int HttpWii::CompleteAsync(class HttpWii * const this /* r28 */, int num /* r29 */, unsigned long & size /* r31 */) {
    // Local variables
    void * handle; // r24
    unsigned long received; // r1+0x10
    unsigned long contentLength; // r1+0xC
    enum NHTTPConnectionStatus status; // r23
    enum NHTTPError error; // r22
    int code; // r0
    int ssl; // r0
    float percentage; // f0

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
}

// Range: 0x8060C7FC -> 0x8060C87C
unsigned char HttpWii::CancelAsync() {
    // Local variables
    enum NHTTPError error; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060C87C -> 0x8060C8C4
static void __sinit_\HttpWii_cpp() {
    // References
    // -> class HttpWii TheHttpWii;
}


