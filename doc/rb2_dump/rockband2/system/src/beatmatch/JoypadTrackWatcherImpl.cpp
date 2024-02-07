/*
    Compile unit: C:\rockband2\system\src\beatmatch\JoypadTrackWatcherImpl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802E46BC -> 0x802E4DD4
*/
class JoypadTrackWatcherImpl : public TrackWatcherImpl {
    // total size: 0xA4
    float mChordSlop; // offset 0x90, size 0x4
    int mChordGemInProgress; // offset 0x94, size 0x4
    int mChordSlotsInProgress; // offset 0x98, size 0x4
    int mChordLastSlot; // offset 0x9C, size 0x4
    float mChordTimeout; // offset 0xA0, size 0x4
};
// Range: 0x802E46BC -> 0x802E471C
void * JoypadTrackWatcherImpl::JoypadTrackWatcherImpl(class JoypadTrackWatcherImpl * const this /* r31 */, class DataArray * cfg /* r0 */) {
    // References
    // -> struct [anonymous] __vt__22JoypadTrackWatcherImpl;
}

// Range: 0x802E471C -> 0x802E4778
void * JoypadTrackWatcherImpl::~JoypadTrackWatcherImpl(class JoypadTrackWatcherImpl * const this /* r30 */) {}

// Range: 0x802E4778 -> 0x802E4B28
unsigned char JoypadTrackWatcherImpl::Swing(class JoypadTrackWatcherImpl * const this /* r27 */, int slot /* r28 */) {
    // Local variables
    float now; // f31
    int gem_id; // r29
    float nearest_chunk_ms; // f30
    float chunk_end_ms; // f0
    unsigned char ok; // r0
    class GameGem & gem; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E4B28 -> 0x802E4C6C
void JoypadTrackWatcherImpl::TryToCompleteChord(class JoypadTrackWatcherImpl * const this /* r30 */, float ms /* f31 */, int slot /* r31 */) {
    // Local variables
    int chord_slots; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E4C6C -> 0x802E4D4C
void JoypadTrackWatcherImpl::FretButtonUp(class JoypadTrackWatcherImpl * const this /* r28 */, int slot /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E4D4C -> 0x802E4D50
void JoypadTrackWatcherImpl::HitGemHook() {}

// Range: 0x802E4D50 -> 0x802E4D54
void JoypadTrackWatcherImpl::JumpHook() {}

// Range: 0x802E4D54 -> 0x802E4D58
void JoypadTrackWatcherImpl::PollHook() {}

// Range: 0x802E4D58 -> 0x802E4DB4
void JoypadTrackWatcherImpl::CheckForChordTimeout(class JoypadTrackWatcherImpl * const this /* r31 */) {}

// Range: 0x802E4DB4 -> 0x802E4DD4
void JoypadTrackWatcherImpl::ResetChordInProgress() {}

struct {
    // total size: 0x90
} __vt__22JoypadTrackWatcherImpl; // size: 0x90, address: 0x808CBA58
struct {
    // total size: 0x8
} __RTTI__22JoypadTrackWatcherImpl; // size: 0x8, address: 0x808CBB10

