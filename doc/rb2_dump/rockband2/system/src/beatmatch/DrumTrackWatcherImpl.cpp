/*
    Compile unit: C:\rockband2\system\src\beatmatch\DrumTrackWatcherImpl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802DAE78 -> 0x802DBBE0
*/
unsigned char gKickAutoplay; // size: 0x1, address: 0x80A505C8
// Range: 0x802DAE78 -> 0x802DAEC4
void * DrumTrackWatcherImpl::DrumTrackWatcherImpl(class DrumTrackWatcherImpl * const this /* r31 */, class DataArray * cfg /* r0 */) {
    // References
    // -> struct [anonymous] __vt__20DrumTrackWatcherImpl;
}

// Range: 0x802DAEC4 -> 0x802DAF20
void * DrumTrackWatcherImpl::~DrumTrackWatcherImpl(class DrumTrackWatcherImpl * const this /* r30 */) {}

// Range: 0x802DAF20 -> 0x802DB25C
int DrumTrackWatcherImpl::RelevantGem(class DrumTrackWatcherImpl * const this /* r23 */, int first_gem_id /* r24 */, int last_gem_id /* r25 */, int slot /* r26 */) {
    // Local variables
    int g; // r30
    int num_unplayed; // r29
    class GameGem & gem; // r0
    unsigned char choose_any; // r29
    int closest_gem; // r28
    int closest_gem_distance; // r27
    class GameGem & gem; // r0
    int distance; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802DB25C -> 0x802DB618
unsigned char DrumTrackWatcherImpl::Swing(class DrumTrackWatcherImpl * const this /* r28 */, int slot /* r29 */, unsigned char provisional /* r30 */) {
    // Local variables
    float simul_slop_ms; // f30
    float now; // f29
    int first_gem_id; // r26
    float gem_ms; // f0
    int last_gem_id; // r27
    int gem_id; // r31
    unsigned char ok; // r0
    class GameGem & gem; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802DB618 -> 0x802DB61C
void DrumTrackWatcherImpl::PollHook() {}

// Range: 0x802DB61C -> 0x802DB678
void DrumTrackWatcherImpl::JumpHook(class DrumTrackWatcherImpl * const this /* r31 */) {
    // Local variables
    int first_new_gem; // r3
}

// Range: 0x802DB678 -> 0x802DB8A4
void DrumTrackWatcherImpl::CheckForKickAutoplay(class DrumTrackWatcherImpl * const this /* r29 */, float ms /* f29 */) {
    // Local variables
    float now; // f30
    int last_gem; // r30
    float next_gem_ms; // f0
    class GameGem & gem; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> unsigned char gKickAutoplay;
}

// Range: 0x802DB8A4 -> 0x802DBBE0
int DrumTrackWatcherImpl::NextGemAfter(class DrumTrackWatcherImpl * const this /* r23 */, int gem_id /* r24 */, unsigned char timeout /* r25 */) {
    // Local variables
    int group_tick; // r28
    int group; // r27
    int gem; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x90
} __vt__20DrumTrackWatcherImpl; // size: 0x90, address: 0x808CAEA0

