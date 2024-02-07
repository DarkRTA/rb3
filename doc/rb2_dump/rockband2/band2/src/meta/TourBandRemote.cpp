/*
    Compile unit: C:\rockband2\band2\src\meta\TourBandRemote.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801B693C -> 0x801B71D0
*/
// Range: 0x801B693C -> 0x801B6BA4
void * TourBandRemote::TourBandRemote(class TourBandRemote * const this /* r30 */, class TourWorld & w /* r25 */, class TourChallenge & c /* r26 */, const class SongMgr & sm /* r27 */, class BandUserMgr & bum /* r28 */, const class RemoteBandData * band /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14TourBandRemote;
}

// Range: 0x801B6BA4 -> 0x801B6CA8
void * TourBandRemote::~TourBandRemote(class TourBandRemote * const this /* r28 */) {
    // References
    // -> struct [anonymous] __vt__14TourBandRemote;
}

// Range: 0x801B6CA8 -> 0x801B6D08
void TourBandRemote::LoadMoment(class TourBandRemote * const this /* r30 */, class TourMoment * * moment /* r31 */) {
    // Local variables
    class Symbol moment_name; // r1+0xC

    // References
    // -> const char * gNullStr;
}

// Range: 0x801B6D08 -> 0x801B6D10
class TourMoment * TourBandRemote::NextMoment() {}

// Range: 0x801B6D10 -> 0x801B6D18
char * TourBandRemote::BandName() {}

// Range: 0x801B6D18 -> 0x801B6D20
char * TourBandRemote::GetMotto() {}

// Range: 0x801B6D20 -> 0x801B6F14
void TourBandRemote::GetRoster(const class TourBandRemote * const this /* r29 */, class vector & members /* r30 */) {
    // Local variables
    int i; // r31
    struct BandMember rosterMember; // r1+0x20
}

// Range: 0x801B6F14 -> 0x801B6F1C
char * TourBandRemote::OwnerName() {}

// Range: 0x801B6F1C -> 0x801B6F90
class String TourBandRemote::GetLogoPatchDir(const class TourBandRemote * const this /* r31 */) {
    // References
    // -> class String sDefaultLogo;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x801B6F90 -> 0x801B6FB4
int TourBandRemote::Fans() {}

// Range: 0x801B6FB4 -> 0x801B6FD8
int TourBandRemote::TourScore() {}

// Range: 0x801B6FD8 -> 0x801B6FFC
int TourBandRemote::WorldFame() {}

// Range: 0x801B6FFC -> 0x801B7020
void TourBandRemote::GetTopSongs() {}

// Range: 0x801B7020 -> 0x801B7048
int TourBandRemote::StarRating() {}

// Range: 0x801B7048 -> 0x801B7070
enum Difficulty TourBandRemote::DifficultyRating() {}

static class Symbol update_tour_display; // size: 0x4, address: 0x80A4D7BC
// Range: 0x801B7070 -> 0x801B71D0
void TourBandRemote::OnSynchronized(class TourBandRemote * const this /* r31 */) {
    // Local variables
    class DataArrayPtr update; // r1+0x20

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol update_tour_display;
    // -> class ProfileMgr TheProfileMgr;
}

struct {
    // total size: 0x1C0
} __vt__14TourBandRemote; // size: 0x1C0, address: 0x808A0AF0

