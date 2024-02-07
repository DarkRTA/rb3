/*
    Compile unit: C:\rockband2\band2\src\meta\JukeboxPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E9058 -> 0x800EA0E8
*/
class DataArray * types; // size: 0x4, address: 0x80A4AFB8
class Symbol name; // size: 0x4, address: 0x80A4AFC0
class JukeboxPanel * TheJukeboxPanel; // size: 0x4, address: 0x80A4AFC4
class JukeboxBandProvider * TheJukeboxBandProvider; // size: 0x4, address: 0x80A4AFC8
// Range: 0x800E9058 -> 0x800E90CC
void * JukeboxBandProvider::JukeboxBandProvider(class JukeboxBandProvider * const this /* r31 */) {
    // References
    // -> class JukeboxBandProvider * TheJukeboxBandProvider;
    // -> struct [anonymous] __vt__19JukeboxBandProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800E90CC -> 0x800E9130
void * JukeboxBandProvider::~JukeboxBandProvider(class JukeboxBandProvider * const this /* r30 */) {
    // References
    // -> class JukeboxBandProvider * TheJukeboxBandProvider;
}

// Range: 0x800E9130 -> 0x800E9134
void JukeboxBandProvider::InitData() {}

static class Symbol name; // size: 0x4, address: 0x80A4AFD0
// Range: 0x800E9134 -> 0x800E91E0
char * JukeboxBandProvider::Text(const class JukeboxBandProvider * const this /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> static class Symbol name;
}

static class Symbol rating; // size: 0x4, address: 0x80A4AFD8
// Range: 0x800E91E0 -> 0x800E9344
void JukeboxBandProvider::Custom(int data /* r28 */, class Symbol & slot /* r30 */, class Object * o /* r29 */) {
    // Local variables
    class PlayerDiffIcon * pdi; // r30
    class BandUser * user; // r0
    class Profile * profile; // r0
    class TourBandLocal * band; // r29

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14PlayerDiffIcon;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol rating;
}

// Range: 0x800E9344 -> 0x800E934C
class RndMat * JukeboxBandProvider::Mat() {}

// Range: 0x800E934C -> 0x800E93A4
int JukeboxBandProvider::NumData() {
    // Local variables
    class BandUser * user; // r0
    class Profile * profile; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x800E93A4 -> 0x800E93AC
unsigned char JukeboxBandProvider::IsActive() {}

// Range: 0x800E93AC -> 0x800E93CC
class DataNode JukeboxBandProvider::OnGetJukeboxBandProvider() {
    // References
    // -> class JukeboxBandProvider * TheJukeboxBandProvider;
}

// Range: 0x800E93CC -> 0x800E9440
char * JukeboxBandProvider::GetBandName(int index /* r31 */) {
    // Local variables
    class BandUser * user; // r0
    class Profile * profile; // r0
    class TourBandLocal * band; // r0

    // References
    // -> const char * gNullStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SessionMgr * TheSessionMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AFE0
// Range: 0x800E9440 -> 0x800E9800
class DataNode JukeboxBandProvider::Handle(class JukeboxBandProvider * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

// Range: 0x800E9800 -> 0x800E98AC
void * JukeboxPanel::JukeboxPanel(class JukeboxPanel * const this /* r30 */) {
    // References
    // -> class JukeboxPanel * TheJukeboxPanel;
    // -> struct [anonymous] __vt__12JukeboxPanel;
}

// Range: 0x800E98AC -> 0x800E997C
void * JukeboxPanel::~JukeboxPanel(class JukeboxPanel * const this /* r29 */) {
    // References
    // -> class JukeboxPanel * TheJukeboxPanel;
    // -> struct [anonymous] __vt__12JukeboxPanel;
}

// Range: 0x800E997C -> 0x800E99B4
void JukeboxPanel::Enter(class JukeboxPanel * const this /* r31 */) {}

// Range: 0x800E99B4 -> 0x800E99EC
void JukeboxPanel::Exit(class JukeboxPanel * const this /* r31 */) {}

// Range: 0x800E99EC -> 0x800E99F4
int JukeboxPanel::GetBand() {}

// Range: 0x800E99F4 -> 0x800E99FC
void JukeboxPanel::SetBand() {}

// Range: 0x800E99FC -> 0x800E9AEC
void JukeboxPanel::SetAutoplay(unsigned char on /* r29 */) {
    // Local variables
    class vector users; // r1+0xC
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AFE8
static class Symbol _s; // size: 0x4, address: 0x80A4AFF0
// Range: 0x800E9AEC -> 0x800EA0E8
class DataNode JukeboxPanel::Handle(class JukeboxPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__12JukeboxPanel; // size: 0xAC, address: 0x808860C8
struct {
    // total size: 0x8
} __RTTI__12JukeboxPanel; // size: 0x8, address: 0x808861A0
struct {
    // total size: 0x9C
} __vt__19JukeboxBandProvider; // size: 0x9C, address: 0x808861A8
struct {
    // total size: 0x8
} __RTTI__19JukeboxBandProvider; // size: 0x8, address: 0x80886278

