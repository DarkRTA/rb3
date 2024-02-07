/*
    Compile unit: C:\rockband2\band2\src\meta\TourChallengeDetailsPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801C0888 -> 0x801C15B0
*/
class DataArray * types; // size: 0x4, address: 0x80A4D980
class Symbol disabled; // size: 0x4, address: 0x80A4D988
class Symbol track; // size: 0x4, address: 0x80A4D990
class Symbol song; // size: 0x4, address: 0x80A4D998
class Symbol artist; // size: 0x4, address: 0x80A4D9A0
class Symbol score; // size: 0x4, address: 0x80A4D9A8
class Symbol completed; // size: 0x4, address: 0x80A4D9B0
// Range: 0x801C0888 -> 0x801C0964
void * TourChallengeDetailsPanel::TourChallengeDetailsPanel(class TourChallengeDetailsPanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__25TourChallengeDetailsPanel;
    // -> struct [anonymous] __vt__12TexLoadPanel;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
}

// Range: 0x801C0964 -> 0x801C0AB0
void TourChallengeDetailsPanel::Load(class TourChallengeDetailsPanel * const this /* r28 */) {
    // Local variables
    class TourBand * b; // r31
    class TourChallengeEvent * e; // r31
    class String back_art; // r1+0x14
    const char * path; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
}

// Range: 0x801C0AB0 -> 0x801C0C38
void TourChallengeDetailsPanel::FinishLoad(class TourChallengeDetailsPanel * const this /* r28 */) {
    // Local variables
    class TourBand * b; // r29
    class TourChallengeEvent * e; // r0

    // References
    // -> struct [anonymous] __vt__21ChallengeSongProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
}

// Range: 0x801C0C38 -> 0x801C0C90
void TourChallengeDetailsPanel::Unload(class TourChallengeDetailsPanel * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4D9B8
static class Symbol _s; // size: 0x4, address: 0x80A4D9C0
// Range: 0x801C0CF0 -> 0x801C1178
class DataNode TourChallengeDetailsPanel::Handle(class TourChallengeDetailsPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class ChallengeSongProvider : public ListProvider, public Object {
    // total size: 0x34
    const class TourBand * mBand; // offset 0x2C, size 0x4
    class TourChallengeEvent * mEvent; // offset 0x30, size 0x4
};
// Range: 0x801C1178 -> 0x801C1268
class Symbol ChallengeSongProvider::State(const class ChallengeSongProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> class Symbol disabled;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801C1268 -> 0x801C12D0
int ChallengeSongProvider::NumData(const class ChallengeSongProvider * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801C12D0 -> 0x801C131C
class RndMat * ChallengeSongProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801C131C -> 0x801C15B0
char * ChallengeSongProvider::Text(const class ChallengeSongProvider * const this /* r28 */, int showing /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    int score; // r0

    // References
    // -> const char * gNullStr;
    // -> class SongMgr & TheSongMgr;
    // -> class Symbol completed;
    // -> class Symbol score;
    // -> class Symbol artist;
    // -> class Symbol song;
    // -> class Symbol track;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x98
} __vt__21ChallengeSongProvider; // size: 0x98, address: 0x808A1D70
struct {
    // total size: 0x8
} __RTTI__21ChallengeSongProvider; // size: 0x8, address: 0x808A1E40
struct {
    // total size: 0xF4
} __vt__25TourChallengeDetailsPanel; // size: 0xF4, address: 0x808A1E60
struct {
    // total size: 0x8
} __RTTI__25TourChallengeDetailsPanel; // size: 0x8, address: 0x808A1FA0

