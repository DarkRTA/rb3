/*
    Compile unit: C:\rockband2\system\src\utl\NetLoader_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061B274 -> 0x8061B5E0
*/
class NetLoaderWii : public NetLoader {
    // total size: 0x48
    int mHttpHandle; // offset 0x20, size 0x4
    enum State mState; // offset 0x24, size 0x4
    unsigned long long mLength; // offset 0x28, size 0x8
    unsigned long long mReceived; // offset 0x30, size 0x8
    void * mBuffer; // offset 0x38, size 0x4
    class String mURL; // offset 0x3C, size 0xC
};
// Range: 0x8061B274 -> 0x8061B2CC
unsigned char NetLoaderWii::SendRequest(class NetLoaderWii * const this /* r31 */) {
    // References
    // -> class HttpWii TheHttpWii;
}

// Range: 0x8061B2CC -> 0x8061B348
unsigned char NetLoaderWii::GetContentLength(class NetLoaderWii * const this /* r30 */) {
    // Local variables
    int result; // r0
    unsigned long size; // r1+0x8

    // References
    // -> class HttpWii TheHttpWii;
}

// Range: 0x8061B348 -> 0x8061B3D8
unsigned char NetLoaderWii::ReceiveResponse(class NetLoaderWii * const this /* r31 */) {
    // Local variables
    int result; // r0
    unsigned long size; // r1+0x8

    // References
    // -> class HttpWii TheHttpWii;
}

// Range: 0x8061B3D8 -> 0x8061B434
void NetLoaderWii::FinishTransaction(class NetLoaderWii * const this /* r31 */) {}

enum State {
    kSendRequest = 0,
    kGetContentLength = 1,
    kDispatchRequest = 2,
    kReceiveRequest = 3,
    kDone = 4,
    kFailure = 5,
    kFailureComplete = 6,
    kMax = 7,
    kNil = -1,
};
// Range: 0x8061B434 -> 0x8061B5BC
void NetLoaderWii::PollLoading(class NetLoaderWii * const this /* r31 */) {}

// Range: 0x8061B5BC -> 0x8061B5E0
unsigned char NetLoaderWii::HasFailed() {}

struct {
    // total size: 0x14
} __vt__12NetLoaderWii; // size: 0x14, address: 0x8092E44C
struct {
    // total size: 0x8
} __RTTI__12NetLoaderWii; // size: 0x8, address: 0x8092E480

