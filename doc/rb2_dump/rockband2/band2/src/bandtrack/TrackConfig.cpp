/*
    Compile unit: C:\rockband2\band2\src\bandtrack\TrackConfig.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80026584 -> 0x80026758
*/
// Range: 0x80026584 -> 0x800265C8
void * TrackConfig::TrackConfig() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800265C8 -> 0x800265D0
int TrackConfig::Player() {}

// Range: 0x800265D0 -> 0x800265D8
int TrackConfig::TrackNum() {}

// Range: 0x800265D8 -> 0x800265E0
class Symbol TrackConfig::Type() {}

// Range: 0x800265E0 -> 0x800265E8
unsigned char TrackConfig::IsLefty() {}

// Range: 0x800265E8 -> 0x800265F0
unsigned char TrackConfig::UseLeftyGems() {}

static class Symbol drum; // size: 0x4, address: 0x80A4906C
// Range: 0x800265F0 -> 0x80026650
unsigned char TrackConfig::IsDrumTrack(const class TrackConfig * const this /* r31 */) {
    // References
    // -> static class Symbol drum;
}

// Range: 0x80026650 -> 0x80026748
char * TrackConfig::GetSlotColor(const class TrackConfig * const this /* r28 */, int slot /* r29 */) {
    // Local variables
    class DataArray * colors; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80026748 -> 0x80026750
void TrackConfig::SetLefty() {}

// Range: 0x80026750 -> 0x80026758
void TrackConfig::SetTrackNum() {}


