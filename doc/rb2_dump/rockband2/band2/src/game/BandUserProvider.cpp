/*
    Compile unit: C:\rockband2\band2\src\game\BandUserProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80048FB0 -> 0x80049B8C
*/
// Range: 0x80048FB0 -> 0x80049048
void * BandUserProvider::~BandUserProvider(class BandUserProvider * const this /* r30 */) {}

// Range: 0x80049048 -> 0x80049050
void BandUserProvider::SetState() {}

// Range: 0x80049050 -> 0x80049054
void BandUserProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4935C
static class Symbol pad; // size: 0x4, address: 0x80A49364
static class Symbol count; // size: 0x4, address: 0x80A4936C
static class Symbol symMax; // size: 0x4, address: 0x80A49374
static class Symbol slash; // size: 0x4, address: 0x80A4937C
static class Symbol band_user_provider_empty; // size: 0x4, address: 0x80A49384
// Range: 0x80049054 -> 0x80049338
char * BandUserProvider::Text(const class BandUserProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    class Profile * pProfile; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol band_user_provider_empty;
    // -> static class Symbol slash;
    // -> static class Symbol symMax;
    // -> static class Symbol count;
    // -> static class Symbol pad;
    // -> static class Symbol name;
}

// Range: 0x80049338 -> 0x80049340
class RndMat * BandUserProvider::Mat() {}

// Range: 0x80049340 -> 0x80049368
int BandUserProvider::NumData() {
    // Local variables
    int c; // r0
}

// Range: 0x80049368 -> 0x800494B4
unsigned char BandUserProvider::IsActive(const class BandUserProvider * const this /* r28 */) {
    // Local variables
    class BandUser * pUser; // r29
    class Profile * pProfile; // r29

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800494B4 -> 0x8004958C
void BandUserProvider::OnSetState(class BandUserProvider * const this /* r29 */, class DataArray * pData /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004958C -> 0x80049610
int BandUserProvider::GetFirstActive(class BandUserProvider * const this /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol _s; // size: 0x4, address: 0x80A4938C
static class Symbol _s; // size: 0x4, address: 0x80A49394
static class Symbol _s; // size: 0x4, address: 0x80A4939C
// Range: 0x80049610 -> 0x80049B8C
class DataNode BandUserProvider::Handle(class BandUserProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x9C
} __vt__16BandUserProvider; // size: 0x9C, address: 0x80872E18
struct {
    // total size: 0x8
} __RTTI__16BandUserProvider; // size: 0x8, address: 0x80872EE8
struct {
    // total size: 0x8
} __RTTI__12ListProvider; // size: 0x8, address: 0x80872F00

