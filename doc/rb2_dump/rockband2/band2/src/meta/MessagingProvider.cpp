/*
    Compile unit: C:\rockband2\band2\src\meta\MessagingProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8021269C -> 0x80213808
*/
class MessagingProvider * sMessagingProvider; // size: 0x4, address: 0x80A4EA18
class MessagingProvider : public ListProvider, public Object {
    // total size: 0x44
    class vector mMessages; // offset 0x2C, size 0xC
    class String mGid; // offset 0x38, size 0xC
};
// Range: 0x8021269C -> 0x802126D0
void MessagingProvider::Init() {
    // References
    // -> class MessagingProvider * sMessagingProvider;
}

// Range: 0x802126D0 -> 0x8021275C
void * MessagingProvider::MessagingProvider(class MessagingProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__17MessagingProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x8021275C -> 0x8021281C
void * MessagingProvider::~MessagingProvider(class MessagingProvider * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17MessagingProvider;
}

// Range: 0x8021281C -> 0x80212888
void MessagingProvider::CleanUp(class MessagingProvider * const this /* r30 */) {}

// Range: 0x80212888 -> 0x802128D8
void MessagingProvider::EnumerateMessages(class MessagingProvider * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x802128D8 -> 0x802128F4
void MessagingProvider::DeleteMessage() {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x802128F4 -> 0x802128FC
char * MessagingProvider::GetGID() {}

// Range: 0x802128FC -> 0x80212984
char * MessagingProvider::GetSenderID(class MessagingProvider * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80212984 -> 0x802129EC
char * MessagingProvider::GetSubject(class MessagingProvider * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802129EC -> 0x80212B44
class Symbol MessagingProvider::GetTextBody(class MessagingProvider * const this /* r26 */, int selectedPos /* r27 */) {
    // Local variables
    unsigned int message_length; // r30
    char * buffer; // r31
    class String gid; // r1+0x18
    class Symbol body; // r1+0x14

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80212B44 -> 0x80212BE8
char * MessagingProvider::Text(const class MessagingProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80212BE8 -> 0x80212BF0
class RndMat * MessagingProvider::Mat() {}

// Range: 0x80212BF0 -> 0x80212C08
int MessagingProvider::NumData() {}

// Range: 0x80212C08 -> 0x80212C1C
class DataNode MessagingProvider::OnMsg() {}

static class Symbol _s; // size: 0x4, address: 0x80A4EA20
static class Symbol _s; // size: 0x4, address: 0x80A4EA28
static class Symbol _s; // size: 0x4, address: 0x80A4EA30
static class Symbol _s; // size: 0x4, address: 0x80A4EA38
static class Symbol _s; // size: 0x4, address: 0x80A4EA40
static class Symbol _s; // size: 0x4, address: 0x80A4EA48
static class Symbol _s; // size: 0x4, address: 0x80A4EA50
static class Symbol _s; // size: 0x4, address: 0x80A4EA58
// Range: 0x80212C1C -> 0x80213808
class DataNode MessagingProvider::Handle(class MessagingProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__24PlatformMgrOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x9C
} __vt__17MessagingProvider; // size: 0x9C, address: 0x808AD720
struct {
    // total size: 0x8
} __RTTI__17MessagingProvider; // size: 0x8, address: 0x808AD7F0

