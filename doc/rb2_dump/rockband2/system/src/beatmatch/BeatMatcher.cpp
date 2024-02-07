/*
    Compile unit: C:\rockband2\system\src\beatmatch\BeatMatcher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D3264 -> 0x802D44F0
*/
class DrumPlayer {
    // total size: 0xC
    float mAttenuation; // offset 0x0, size 0x4
    class DataArray * mSoloCfg; // offset 0x4, size 0x4
    class DataArray * mOverrideList; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BeatMatchSink * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BeatMatchSink * * _M_start; // offset 0x0, size 0x4
    class BeatMatchSink * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PhraseCatcher {
    // total size: 0x2C
    int mTrack; // offset 0x0, size 0x4
    class TrackWatcher * mWatcher; // offset 0x4, size 0x4
    class PhraseFinder * mFinder; // offset 0x8, size 0x4
    class PhraseCapturer * mCapturer; // offset 0xC, size 0x4
    class BeatMatchSink * mSink; // offset 0x10, size 0x4
    struct PhraseInfo mCurrentPhrase; // offset 0x14, size 0x18
};
class TrackWatcher {
    // total size: 0x34
    class TrackWatcherImpl * mImpl; // offset 0x0, size 0x4
    class vector mSinks; // offset 0x4, size 0xC
    int mTrack; // offset 0x10, size 0x4
    unsigned char mIndependentSlots; // offset 0x14, size 0x1
    int mPlayerNum; // offset 0x18, size 0x4
    int mPlayerSlot; // offset 0x1C, size 0x4
    class Symbol mControllerType; // offset 0x20, size 0x4
    class SongData * mSongData; // offset 0x24, size 0x4
    class TrackWatcherParent * mParent; // offset 0x28, size 0x4
    class DataArray * mCfg; // offset 0x2C, size 0x4
    class DataArray * mSongCfg; // offset 0x30, size 0x4
};
// Range: 0x802D3264 -> 0x802D35F0
void * BeatMatcher::~BeatMatcher(class BeatMatcher * const this /* r29 */) {
    // Local variables
    class TrackWatcher * * wit; // r28
    class PhraseCatcher * * cit; // r28
    class BarFinder * * bfit; // r31
    class PhraseFinder * * pfit; // r28
    class PhraseCapturer * * pcit; // r28

    // References
    // -> struct [anonymous] __vt__11BeatMatcher;
}

class MercurySwitchFilter {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x802D35F0 -> 0x802D3640
void BeatMatcher::PostLoad(class BeatMatcher * const this /* r30 */) {
    // Local variables
    class BarFinder * * bfit; // r31
}

// Range: 0x802D3640 -> 0x802D36A8
unsigned char BeatMatcher::IsReady(class BeatMatcher * const this /* r31 */) {}

// Range: 0x802D36A8 -> 0x802D36B0
void BeatMatcher::RegisterSink() {}

// Range: 0x802D36B0 -> 0x802D3768
void BeatMatcher::Poll(class BeatMatcher * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
    class PhraseCatcher * * cit; // r31
}

// Range: 0x802D3768 -> 0x802D3840
void BeatMatcher::Jump(class BeatMatcher * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
    class PhraseCatcher * * cit; // r31
}

// Range: 0x802D3840 -> 0x802D38C4
void BeatMatcher::ResetGemStates(class BeatMatcher * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
    class PhraseCatcher * * cit; // r31
}

// Range: 0x802D38C4 -> 0x802D38D0
void BeatMatcher::ReleaseSwing() {}

// Range: 0x802D38D0 -> 0x802D3938
void BeatMatcher::ChangeTrack(class BeatMatcher * const this /* r31 */) {}

// Range: 0x802D3938 -> 0x802D3A3C
void BeatMatcher::SetTrack(class BeatMatcher * const this /* r29 */, int new_track /* r30 */) {
    // Local variables
    const char * str; // r0

    // References
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x802D3A3C -> 0x802D3AC4
void BeatMatcher::UpdateMercurySwitch(class BeatMatcher * const this /* r30 */) {
    // Local variables
    unsigned char on; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D3AC4 -> 0x802D3B48
int BeatMatcher::GetVirtualSlot(class BeatMatcher * const this /* r30 */, int slot /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D3B48 -> 0x802D3B8C
void BeatMatcher::PlayDrum() {}

// Range: 0x802D3B8C -> 0x802D3B94
void BeatMatcher::ResetDrumSamples() {}

// Range: 0x802D3B94 -> 0x802D3C1C
float BeatMatcher::GetWhammyBar(const class BeatMatcher * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D3C1C -> 0x802D3C24
unsigned char BeatMatcher::IsAutoplay() {}

// Range: 0x802D3C24 -> 0x802D3C88
void BeatMatcher::SetAutoplay(class BeatMatcher * const this /* r29 */, unsigned char autoplay /* r30 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D3C88 -> 0x802D3CE8
void BeatMatcher::AutoplayCoda(class BeatMatcher * const this /* r29 */, unsigned char val /* r30 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D3CE8 -> 0x802D3D48
void BeatMatcher::SetAutoplayError(class BeatMatcher * const this /* r29 */, int error /* r30 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D3D48 -> 0x802D3D50
void BeatMatcher::DrivePitchBendExternally() {}

// Range: 0x802D3D50 -> 0x802D3DC8
void BeatMatcher::SetPitchBend(class BeatMatcher * const this /* r30 */, int track /* r31 */) {}

// Range: 0x802D3DC8 -> 0x802D3E04
void BeatMatcher::ResetPitchBend() {}

// Range: 0x802D3E04 -> 0x802D3E44
unsigned char BeatMatcher::InFillNow() {}

// Range: 0x802D3E44 -> 0x802D3F30
unsigned char BeatMatcher::InFill(class BeatMatcher * const this /* r28 */, int tick /* r29 */, unsigned char include_end /* r30 */) {
    // Local variables
    enum BeatmatchTrackType type; // r31
}

// Range: 0x802D3F30 -> 0x802D3F74
unsigned char BeatMatcher::InSolo(class BeatMatcher * const this /* r5 */, int tick /* r31 */) {}

// Range: 0x802D3F74 -> 0x802D3F98
unsigned char BeatMatcher::InCoda() {}

// Range: 0x802D3F98 -> 0x802D4024
unsigned char BeatMatcher::InCodaFreestyle(class BeatMatcher * const this /* r28 */, int tick /* r29 */, unsigned char include_end /* r30 */) {}

// Range: 0x802D4024 -> 0x802D402C
void BeatMatcher::SetCodaStartTick() {}

// Range: 0x802D402C -> 0x802D4034
void BeatMatcher::EnterCoda() {}

// Range: 0x802D4034 -> 0x802D405C
void BeatMatcher::SetButtonMashingMode() {}

// Range: 0x802D405C -> 0x802D40DC
void BeatMatcher::Enable(class BeatMatcher * const this /* r29 */, unsigned char enabled /* r30 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D40DC -> 0x802D4164
void BeatMatcher::EnableController(class BeatMatcher * const this /* r30 */, unsigned char enabled /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D4164 -> 0x802D41A0
unsigned char BeatMatcher::FillsEnabled() {}

// Range: 0x802D41A0 -> 0x802D41BC
void BeatMatcher::SetFillsEnabled() {}

// Range: 0x802D41BC -> 0x802D4258
void BeatMatcher::SetFillsEnabled(class BeatMatcher * const this /* r29 */, int startTick /* r30 */) {
    // Local variables
    struct FillExtent e; // r1+0x8
}

// Range: 0x802D4258 -> 0x802D4260
void BeatMatcher::ForceFill() {}

// Range: 0x802D4260 -> 0x802D42C4
void BeatMatcher::SetSyncOffset(class BeatMatcher * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D42C4 -> 0x802D4344
void BeatMatcher::SetControllerType(class BeatMatcher * const this /* r29 */, class Symbol & controller_type /* r30 */) {
    // Local variables
    class TrackWatcher * * wit; // r31
}

// Range: 0x802D4344 -> 0x802D4398
unsigned char BeatMatcher::UsingAlternateButtons() {}

// Range: 0x802D4398 -> 0x802D43A0
void BeatMatcher::EnableWhammy() {}

// Range: 0x802D43A0 -> 0x802D4408
unsigned char BeatMatcher::UsesPhrases(const class BeatMatcher * const this /* r31 */) {
    // Local variables
    class DataArray * phrases_array; // r0
}

// Range: 0x802D4408 -> 0x802D447C
void BeatMatcher::CheckMercurySwitch(class BeatMatcher * const this /* r31 */) {
    // Local variables
    unsigned char new_state; // r0
}

// Range: 0x802D447C -> 0x802D44F0
void BeatMatcher::SetNow(class BeatMatcher * const this /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__11BeatMatcher; // size: 0xA8, address: 0x808CA5F0
struct {
    // total size: 0x8
} __RTTI__11BeatMatcher; // size: 0x8, address: 0x808CA6B8
struct {
    // total size: 0x48
} __vt__18TrackWatcherParent; // size: 0x48, address: 0x808CA6C0
struct {
    // total size: 0x8
} __RTTI__18TrackWatcherParent; // size: 0x8, address: 0x808CA720
struct {
    // total size: 0x8
} __RTTI__P18BeatmatchTrackType; // size: 0x8, address: 0x808CA798
struct {
    // total size: 0x8
} __RTTI__PP14PhraseCapturer; // size: 0x8, address: 0x808CA7B8
struct {
    // total size: 0x8
} __RTTI__PP12PhraseFinder; // size: 0x8, address: 0x808CA7D0
struct {
    // total size: 0x8
} __RTTI__PP13PhraseCatcher; // size: 0x8, address: 0x808CA7F0
struct {
    // total size: 0x8
} __RTTI__PP12TrackWatcher; // size: 0x8, address: 0x808CA808
struct {
    // total size: 0x8
} __RTTI__PP9BarFinder; // size: 0x8, address: 0x808CA820

