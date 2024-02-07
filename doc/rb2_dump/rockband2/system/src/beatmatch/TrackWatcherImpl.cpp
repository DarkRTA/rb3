/*
    Compile unit: C:\rockband2\system\src\beatmatch\TrackWatcherImpl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803044B4 -> 0x80306BA0
*/
static float kCheatCodaSwingFrequency; // size: 0x4, address: 0x80A56AE0
// Range: 0x803044B4 -> 0x8030471C
void * TrackWatcherImpl::TrackWatcherImpl(class TrackWatcherImpl * const this /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    class DataArray * accuracy_cfg; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__16TrackWatcherImpl;
}

// Range: 0x8030471C -> 0x803047B4
void * TrackWatcherImpl::~TrackWatcherImpl(class TrackWatcherImpl * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16TrackWatcherImpl;
}

// Range: 0x803047B4 -> 0x80304878
void TrackWatcherImpl::LoadState() {}

// Range: 0x80304878 -> 0x8030493C
void TrackWatcherImpl::SaveState() {}

// Range: 0x8030493C -> 0x803049AC
void TrackWatcherImpl::AddSink(class BeatMatchSink * sink /* r1+0x8 */) {}

// Range: 0x803049AC -> 0x80304A1C
void TrackWatcherImpl::SetCatcher(class TrackWatcherImpl * const this /* r30 */, class PhraseCatcher * catcher /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80304A1C -> 0x80304A24
void TrackWatcherImpl::SetIsCurrentTrack() {}

// Range: 0x80304A24 -> 0x80304B00
void TrackWatcherImpl::Poll(class TrackWatcherImpl * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    int tick; // r31
}

// Range: 0x80304B00 -> 0x80304BC0
void TrackWatcherImpl::Jump(class TrackWatcherImpl * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    int first_new_gem; // r3
    int last_old_gem; // r4
}

// Range: 0x80304BC0 -> 0x80304C5C
void TrackWatcherImpl::AutoCapture(class TrackWatcherImpl * const this /* r29 */, const struct PhraseInfo & info /* r30 */, unsigned char autocapture /* r31 */) {}

// Range: 0x80304C5C -> 0x80304CD0
void TrackWatcherImpl::SetAutoCaptureExtent(class TrackWatcherImpl * const this /* r30 */, int end_gem /* r31 */) {}

// Range: 0x80304CD0 -> 0x80304CD8
void TrackWatcherImpl::Enable() {}

// Range: 0x80304CD8 -> 0x80304CE0
unsigned char TrackWatcherImpl::IsCheating() {}

// Range: 0x80304CE0 -> 0x80304CE8
void TrackWatcherImpl::SetCheating() {}

// Range: 0x80304CE8 -> 0x80304CF0
void TrackWatcherImpl::SetAutoplayError() {}

// Range: 0x80304CF0 -> 0x80304CF8
void TrackWatcherImpl::SetAutoplayCoda() {}

// Range: 0x80304CF8 -> 0x80304D00
void TrackWatcherImpl::SetSyncOffset() {}

// Range: 0x80304D00 -> 0x80304D30
int TrackWatcherImpl::NextGemAfter() {}

// Range: 0x80304D30 -> 0x80304E28
int TrackWatcherImpl::ClosestUnplayedGem(class TrackWatcherImpl * const this /* r29 */) {
    // Local variables
    int gem_id; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80304E28 -> 0x80304E54
unsigned char TrackWatcherImpl::InSlopWindow() {}

// Range: 0x80304E54 -> 0x80304F18
void TrackWatcherImpl::SetGemsPlayedUntil(class TrackWatcherImpl * const this /* r28 */, int end_gem /* r29 */) {
    // Local variables
    int gem_id; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80304F18 -> 0x80304FD8
void TrackWatcherImpl::SetGemsUnplayed(class TrackWatcherImpl * const this /* r28 */, int end_gem /* r29 */) {
    // Local variables
    int gem_id; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80304FD8 -> 0x80304FE0
void TrackWatcherImpl::SetAllGemsUnplayed() {}

// Range: 0x80304FE0 -> 0x80304FE8
void TrackWatcherImpl::FakeHitGem() {}

// Range: 0x80304FE8 -> 0x803051D4
void TrackWatcherImpl::HitGem(class TrackWatcherImpl * const this /* r27 */, float ms /* f31 */, int gem_id /* r28 */, unsigned char hopo /* r29 */, unsigned char solo_button /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803051D4 -> 0x80305444
void TrackWatcherImpl::CheckForPasses(class TrackWatcherImpl * const this /* r31 */, float ms /* f30 */) {
    // Local variables
    int last_gem; // r28
    int next_gem; // r29
    float next_gem_ms; // f0
    float wait; // f0
    float timeout_ms; // r1+0xC
    int later_gem; // r4
    float later_gem_ms; // f0
    float midpoint_ms; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80305444 -> 0x80305464
void TrackWatcherImpl::CheckForSustainedNoteTimeout() {}

// Range: 0x80305464 -> 0x80305638
void TrackWatcherImpl::CheckForAutoplay(class TrackWatcherImpl * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    int current_tick; // r30
    int last_gem; // r29
    float next_gem_ms; // f0

    // References
    // -> static float kCheatCodaSwingFrequency;
}

// Range: 0x80305638 -> 0x803056F4
void TrackWatcherImpl::CheckForGemsSeen(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */) {
    // Local variables
    int last_gem; // r31
    int next_gem; // r30
    float next_gem_ms; // f0
}

// Range: 0x803056F4 -> 0x803058C4
void TrackWatcherImpl::CheckForPitchBend(class TrackWatcherImpl * const this /* r31 */, float ms /* f30 */) {
    // Local variables
    float whammy; // r1+0x8
    float new_whammy; // f31
    float bend_fraction; // f0
    float bend; // f1
}

// Range: 0x803058C4 -> 0x8030592C
void TrackWatcherImpl::CheckForCodaLanes(class TrackWatcherImpl * const this /* r31 */) {
    // Local variables
    unsigned char in_coda_lane; // r4
}

// Range: 0x8030592C -> 0x80305A28
int TrackWatcherImpl::SustainedGemToKill(class TrackWatcherImpl * const this /* r29 */, int slot /* r30 */) {
    // Local variables
    int num_frets_down; // r31
    int slots; // r0
    int i; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80305A28 -> 0x80305B38
void TrackWatcherImpl::KillSustain(class TrackWatcherImpl * const this /* r29 */, int gem_id /* r30 */) {
    // Local variables
    float correct_release_time; // f31
    float now; // f0
    float delta; // f2

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80305B38 -> 0x80305BEC
unsigned char TrackWatcherImpl::Playable(class TrackWatcherImpl * const this /* r29 */, int gem_id /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80305BEC -> 0x80305C44
void TrackWatcherImpl::EndSustainedNote(class TrackWatcherImpl * const this /* r31 */) {}

// Range: 0x80305C44 -> 0x80305E30
void TrackWatcherImpl::OnHit(class TrackWatcherImpl * const this /* r27 */, float ms /* f31 */, int slot /* r28 */, int gem_id /* r29 */, unsigned char hopo /* r30 */, unsigned char solo_button /* r31 */) {
    // Local variables
    int end_tick; // r1+0x8
    unsigned char is_fill_completion; // r25

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80305E30 -> 0x80305F70
unsigned char TrackWatcherImpl::IsFillCompletion(class TrackWatcherImpl * const this /* r29 */, float ms /* f30 */, int tick /* r30 */, int & solo_end_tick /* r31 */) {
    // Local variables
    struct FillExtent extent; // r1+0x8
    float extent_end_ms; // f31
}

// Range: 0x80305F70 -> 0x803061C8
void TrackWatcherImpl::OnMiss(class TrackWatcherImpl * const this /* r28 */, float ms /* f31 */, int slot /* r29 */, int gem_id /* r30 */) {
    // Local variables
    int tick; // r31
    int end_tick; // r1+0x8
}

// Range: 0x803061C8 -> 0x803062DC
void TrackWatcherImpl::OnPass(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803062DC -> 0x80306384
void TrackWatcherImpl::CodaSwing(class TrackWatcherImpl * const this /* r27 */, int tick /* r28 */, int slot /* r29 */) {
    // Local variables
    int lanes; // r0
    class BeatMatchSink * * it; // r30
}

// Range: 0x80306384 -> 0x80306480
void TrackWatcherImpl::SendHit(class TrackWatcherImpl * const this /* r27 */, float ms /* f31 */, int gem_id /* r28 */, unsigned char hopo /* r29 */, unsigned char solo_button /* r30 */) {
    // Local variables
    const char * str; // r0
    class BeatMatchSink * * it; // r31

    // References
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x80306480 -> 0x803065E0
void TrackWatcherImpl::SendMiss(class TrackWatcherImpl * const this /* r28 */, float ms /* f31 */, int slot /* r29 */, int gem_id /* r30 */) {
    // Local variables
    const char * str; // r0
    class BeatMatchSink * * it; // r31

    // References
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x803065E0 -> 0x803066DC
void TrackWatcherImpl::SendPass(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // Local variables
    const char * str; // r0
    class BeatMatchSink * * it; // r31

    // References
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x803066DC -> 0x8030675C
void TrackWatcherImpl::SendCapture(class TrackWatcherImpl * const this /* r28 */, const struct PhraseInfo & info /* r29 */, unsigned char autocapture /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x8030675C -> 0x803067CC
void TrackWatcherImpl::SendCapturing(class TrackWatcherImpl * const this /* r29 */, unsigned char state /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x803067CC -> 0x8030685C
void TrackWatcherImpl::SendReleaseGem(class TrackWatcherImpl * const this /* r29 */, float ms /* f30 */, int gem_id /* r30 */, float delta /* f31 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x8030685C -> 0x803069A4
void TrackWatcherImpl::SendSeen(class TrackWatcherImpl * const this /* r30 */, float ms /* f31 */, int gem_id /* r31 */) {
    // Local variables
    const char * str; // r0
    class BeatMatchSink * * it; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x803069A4 -> 0x80306A28
void TrackWatcherImpl::SendIgnore(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x80306A28 -> 0x80306AA0
void TrackWatcherImpl::SendWhammy(class TrackWatcherImpl * const this /* r30 */, float val /* f31 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x80306AA0 -> 0x80306B20
void TrackWatcherImpl::SendSwingAtHopo(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x80306B20 -> 0x80306BA0
void TrackWatcherImpl::SendHopo(class TrackWatcherImpl * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

struct {
    // total size: 0x90
} __vt__16TrackWatcherImpl; // size: 0x90, address: 0x808CE3B8

