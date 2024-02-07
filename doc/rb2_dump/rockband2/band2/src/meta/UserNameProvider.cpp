/*
    Compile unit: C:\rockband2\band2\src\meta\UserNameProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801EE9D4 -> 0x801EF00C
*/
// Range: 0x801EE9D4 -> 0x801EEA48
void * UserNameProvider::UserNameProvider(class UserNameProvider * const this /* r30 */, class MatchmakingSlot * pSlot /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16UserNameProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x801EEA48 -> 0x801EEB3C
void * UserNameProvider::~UserNameProvider(class UserNameProvider * const this /* r30 */) {}

// Range: 0x801EEB3C -> 0x801EEB5C
unsigned char UserNamePadCmp() {}

static class Symbol slot; // size: 0x4, address: 0x80A4E32C
// Range: 0x801EEB5C -> 0x801EEE34
void UserNameProvider::Reload(class UserNameProvider * const this /* r30 */) {
    // Local variables
    class vector fakeUsers; // r1+0x50
    struct FakeBandUser * it; // r28
    int padNum; // r27
    struct UserName userName; // r1+0x40

    // References
    // -> static class Symbol slot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801EEE34 -> 0x801EEE38
void UserNameProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4E334
static class Symbol pad; // size: 0x4, address: 0x80A4E33C
static class Symbol matchmaker_gamertag_pad_num_fmt; // size: 0x4, address: 0x80A4E344
// Range: 0x801EEE38 -> 0x801EEFB8
char * UserNameProvider::Text(const class UserNameProvider * const this /* r30 */, int data /* r27 */, class Symbol & slot /* r28 */) {
    // Local variables
    int visibleOffset; // r29
    int iUser; // r4
    int padNum; // r29

    // References
    // -> static class Symbol matchmaker_gamertag_pad_num_fmt;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> static class Symbol pad;
    // -> static class Symbol name;
}

// Range: 0x801EEFB8 -> 0x801EF004
class RndMat * UserNameProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801EF004 -> 0x801EF00C
int UserNameProvider::NumData() {}

struct {
    // total size: 0x98
} __vt__16UserNameProvider; // size: 0x98, address: 0x808A79F8
struct {
    // total size: 0x8
} __RTTI__16UserNameProvider; // size: 0x8, address: 0x808A7AC0
struct {
    // total size: 0x8
} __RTTI__PQ216UserNameProvider8UserName; // size: 0x8, address: 0x808A7B30

