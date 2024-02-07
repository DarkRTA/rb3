/*
    Compile unit: C:\rockband2\system\src\beatmatch\GuitarTrackWatcherImpl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802E220C -> 0x802E36D0
*/
class GuitarTrackWatcherImpl : public TrackWatcherImpl {
    // total size: 0xB8
    int mFretButtonsDown; // offset 0x90, size 0x4
    int mLastNoStrumGemHit; // offset 0x94, size 0x4
    int mLastNoStrumGemSwung; // offset 0x98, size 0x4
    float mLastLateGemHit; // offset 0x9C, size 0x4
    float mMostRecentHit; // offset 0xA0, size 0x4
    int mGemNotFretted; // offset 0xA4, size 0x4
    int mFretWhenStrummed; // offset 0xA8, size 0x4
    float mFretWaitTimeout; // offset 0xAC, size 0x4
    unsigned char mHarmlessSwing; // offset 0xB0, size 0x1
    float mFretSlop; // offset 0xB4, size 0x4
};
// Range: 0x802E220C -> 0x802E228C
void * GuitarTrackWatcherImpl::GuitarTrackWatcherImpl(class GuitarTrackWatcherImpl * const this /* r31 */, class DataArray * cfg /* r0 */) {
    // References
    // -> struct [anonymous] __vt__22GuitarTrackWatcherImpl;
}

// Range: 0x802E228C -> 0x802E22E8
void * GuitarTrackWatcherImpl::~GuitarTrackWatcherImpl(class GuitarTrackWatcherImpl * const this /* r30 */) {}

// Range: 0x802E22E8 -> 0x802E232C
void GuitarTrackWatcherImpl::PollHook(class GuitarTrackWatcherImpl * const this /* r31 */, float ms /* f31 */) {}

// Range: 0x802E232C -> 0x802E236C
void GuitarTrackWatcherImpl::JumpHook(class GuitarTrackWatcherImpl * const this /* r31 */) {}

// Range: 0x802E236C -> 0x802E2A54
unsigned char GuitarTrackWatcherImpl::Swing(class GuitarTrackWatcherImpl * const this /* r24 */, int slot /* r25 */, unsigned char guitar /* r26 */, unsigned char provisional /* r27 */) {
    // Local variables
    float now; // f31
    int now_tick; // r29
    unsigned char in_coda_freestyle; // r0
    int closest_gem_id; // r30
    int gem_id; // r28
    float nearest_chunk_ms; // f0
    unsigned char in_window; // r0
    float delta; // f0
    class GameGem & gem; // r0
    unsigned char ok; // r23

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E2A54 -> 0x802E2AB8
void GuitarTrackWatcherImpl::NonStrumSwing(class GuitarTrackWatcherImpl * const this /* r29 */, int slot /* r30 */, unsigned char button_down /* r31 */) {
    // Local variables
    float now; // f0
}

// Range: 0x802E2AB8 -> 0x802E2B54
void GuitarTrackWatcherImpl::FretButtonDown(class GuitarTrackWatcherImpl * const this /* r30 */, int slot /* r31 */) {
    // Local variables
    float now; // f0
    int gem_id; // r4
}

// Range: 0x802E2B54 -> 0x802E2C5C
void GuitarTrackWatcherImpl::FretButtonUp(class GuitarTrackWatcherImpl * const this /* r31 */) {
    // Local variables
    int gem_slots; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E2C5C -> 0x802E2C60
void GuitarTrackWatcherImpl::AutoCaptureHook() {}

// Range: 0x802E2C60 -> 0x802E2C74
void GuitarTrackWatcherImpl::HitGemHook() {}

// Range: 0x802E2C74 -> 0x802E2C8C
unsigned char GuitarTrackWatcherImpl::GemCanBePassed() {}

// Range: 0x802E2C8C -> 0x802E2CDC
float GuitarTrackWatcherImpl::Slop(class GuitarTrackWatcherImpl * const this /* r31 */) {}

// Range: 0x802E2CDC -> 0x802E2CFC
void GuitarTrackWatcherImpl::ResetGemNotFretted() {}

// Range: 0x802E2CFC -> 0x802E2F90
void GuitarTrackWatcherImpl::TryToFinishSwing(class GuitarTrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int slot /* r30 */) {
    // Local variables
    class GameGem & gem; // r0
    unsigned char ok; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E2F90 -> 0x802E32E0
void GuitarTrackWatcherImpl::TryToHopo(class GuitarTrackWatcherImpl * const this /* r27 */, float ms /* f30 */, int slot /* r28 */, unsigned char button_down /* r29 */) {
    // Local variables
    int gem_id; // r30
    float nearest_chunk_ms; // f0
    float chunk_end_ms; // f0
    float delta; // f2
    int tick; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E32E0 -> 0x802E3348
void GuitarTrackWatcherImpl::CheckForFretTimeout(class GuitarTrackWatcherImpl * const this /* r31 */) {}

// Range: 0x802E3348 -> 0x802E343C
void GuitarTrackWatcherImpl::CheckForHopoTimeout(class GuitarTrackWatcherImpl * const this /* r29 */, float ms /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E343C -> 0x802E35A4
unsigned char GuitarTrackWatcherImpl::CanHopo(const class GuitarTrackWatcherImpl * const this /* r29 */, int gem_id /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802E35A4 -> 0x802E36D0
unsigned char GuitarTrackWatcherImpl::HarmlessFretDown(const class GuitarTrackWatcherImpl * const this /* r31 */, int gem_id /* r29 */) {
    // Local variables
    int slot_bit; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x90
} __vt__22GuitarTrackWatcherImpl; // size: 0x90, address: 0x808CB618
struct {
    // total size: 0x8
} __RTTI__22GuitarTrackWatcherImpl; // size: 0x8, address: 0x808CB6D0

