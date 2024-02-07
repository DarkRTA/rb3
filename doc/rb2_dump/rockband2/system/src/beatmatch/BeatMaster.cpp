/*
    Compile unit: C:\rockband2\system\src\beatmatch\BeatMaster.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D1880 -> 0x802D2540
*/
// Range: 0x802D1880 -> 0x802D1994
void * BeatMaster::~BeatMaster(class BeatMaster * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10BeatMaster;
}

// Range: 0x802D1994 -> 0x802D1A04
void BeatMaster::RegisterSink(class BeatMasterSink & sink /* r1+0x8 */) {}

struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP12MidiReceiver; // size: 0x8, address: 0x808CA0A0
// Range: 0x802D1A04 -> 0x802D1A84
void BeatMaster::LoaderPoll(class BeatMaster * const this /* r31 */) {}

class BeatMasterLoader : public Loader {
    // total size: 0x18
protected:
    class BeatMaster * mBeatMaster; // offset 0x14, size 0x4
};
// Range: 0x802D1A84 -> 0x802D1AE0
void * BeatMasterLoader::~BeatMasterLoader(class BeatMasterLoader * const this /* r30 */) {}

// Range: 0x802D1AE0 -> 0x802D1AE8
unsigned char BeatMaster::IsLoaded() {}

// Range: 0x802D1AE8 -> 0x802D1B54
void BeatMaster::AddTrack() {}

// Range: 0x802D1B54 -> 0x802D1C6C
void BeatMaster::Poll(class BeatMaster * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    int i; // r31
    float ftick; // f0
    int tick; // r31

    // References
    // -> class Playback TheBeatMatchPlayback;
}

// Range: 0x802D1C6C -> 0x802D1D38
void BeatMaster::Jump(class BeatMaster * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    float ftick; // f0

    // References
    // -> class Playback TheBeatMatchPlayback;
}

static class Symbol reset; // size: 0x4, address: 0x80A5056C
// Range: 0x802D1D38 -> 0x802D1E4C
void BeatMaster::Reset(class BeatMaster * const this /* r31 */) {
    // Local variables
    int i; // r6

    // References
    // -> static class Symbol reset;
    // -> class Playback TheBeatMatchPlayback;
    // -> class LogFile TheBeatMatchOutput;
}

// Range: 0x802D1E4C -> 0x802D1E9C
void BeatMaster::ResetAudio(class BeatMaster * const this /* r31 */) {}

static class Symbol symBeat; // size: 0x4, address: 0x80A50574
static class Symbol symDownBeat; // size: 0x4, address: 0x80A5057C
static class Symbol symEighthNote; // size: 0x4, address: 0x80A50584
static class Symbol symSixteenthNote; // size: 0x4, address: 0x80A5058C
static class DataNode & beat; // size: 0x4, address: 0x80A50594
static class DataNode & measure; // size: 0x4, address: 0x80A5059C
// Range: 0x802D1E9C -> 0x802D21B8
void BeatMaster::CheckBeat(class BeatMaster * const this /* r30 */) {
    // Local variables
    int old_beat; // r0
    int new_beat; // r29
    int i; // r29

    // References
    // -> static class DataNode & measure;
    // -> static class DataNode & beat;
    // -> static class Symbol symSixteenthNote;
    // -> static class Symbol symEighthNote;
    // -> static class Symbol symDownBeat;
    // -> static class Symbol symBeat;
}

// Range: 0x802D21B8 -> 0x802D2290
void BeatMaster::ExportInitialSubmixes(class BeatMaster * const this /* r30 */) {
    // Local variables
    int t; // r31
    const class TickedInfoCollection * submixes; // r0
    const char * str; // r29
    int i; // r28
}

// Range: 0x802D2290 -> 0x802D2394
void BeatMaster::CheckSubmixes(class BeatMaster * const this /* r27 */, int tick /* r28 */) {
    // Local variables
    int t; // r29
    const class TickedInfoCollection * submixes; // r0
    int idx; // r4
    const char * str; // r26
    int i; // r25
}

// Range: 0x802D2394 -> 0x802D249C
void BeatMaster::CheckActivePlayer(class BeatMaster * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    const class vector & gems; // r0
    int players; // r29
    int i; // r28
}

// Range: 0x802D249C -> 0x802D2530
void BeatMaster::HandleBeatCallback() {
    // Local variables
    class DataArray * handler; // r4
}

// Range: 0x802D2530 -> 0x802D2538
void BeatMasterLoader::PollLoading() {}

// Range: 0x802D2538 -> 0x802D2540
unsigned char BeatMasterLoader::IsLoaded() {}

struct {
    // total size: 0x14
} __vt__16BeatMasterLoader; // size: 0x14, address: 0x808CA0E8
struct {
    // total size: 0x8
} __RTTI__16BeatMasterLoader; // size: 0x8, address: 0x808CA120
struct {
    // total size: 0x1C
} __vt__10BeatMaster; // size: 0x1C, address: 0x808CA128
struct {
    // total size: 0x8
} __RTTI__10BeatMaster; // size: 0x8, address: 0x808CA160
struct {
    // total size: 0x8
} __RTTI__PP14BeatMasterSink; // size: 0x8, address: 0x808CA238
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class Playback {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class map mPlayerSinks; // offset 0x4, size 0x18
    class DataArray * mCommands; // offset 0x1C, size 0x4
    int mCommandIndex; // offset 0x20, size 0x4
    float mTime; // offset 0x24, size 0x4
};

