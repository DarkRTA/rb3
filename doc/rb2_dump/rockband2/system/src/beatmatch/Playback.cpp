/*
    Compile unit: C:\rockband2\system\src\beatmatch\Playback.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F6B38 -> 0x802F74E4
*/
class Playback TheBeatMatchPlayback; // size: 0x28, address: 0x8097DD50
// Range: 0x802F6B38 -> 0x802F6BA0
void * Playback::Playback() {
    // References
    // -> struct [anonymous] __vt__8Playback;
}

struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    class BeatMatchControllerSink * second; // offset 0x4, size 0x4
};
// Range: 0x802F6BA0 -> 0x802F6C6C
void * Playback::~Playback(class Playback * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__8Playback;
}

// Range: 0x802F6C6C -> 0x802F6DCC
void Playback::Poll(class Playback * const this /* r29 */, float ms /* f30 */) {
    // Local variables
    int arraySize; // r0
    class DataArray * commandArray; // r31
    float commandTime; // f31
    class DataNode & timeNode; // r0
    class DataNode & timeNode; // r0
}

static class Symbol SWING; // size: 0x4, address: 0x80A50764
static class Symbol UP; // size: 0x4, address: 0x80A5076C
static class Symbol DOWN; // size: 0x4, address: 0x80A50774
static class Symbol TRACK; // size: 0x4, address: 0x80A5077C
static class Symbol HOPO; // size: 0x4, address: 0x80A50784
static class Symbol FLIP; // size: 0x4, address: 0x80A5078C
static class Symbol FFLIP; // size: 0x4, address: 0x80A50794
// Range: 0x802F6DCC -> 0x802F7248
void Playback::DoCommand(class Playback * const this /* r30 */, class DataArray * commandArray /* r29 */) {
    // Local variables
    int player; // r0
    class BeatMatchControllerSink * sink; // r30

    // References
    // -> static class Symbol FFLIP;
    // -> static class Symbol FLIP;
    // -> static class Symbol HOPO;
    // -> static class Symbol TRACK;
    // -> static class Symbol DOWN;
    // -> static class Symbol UP;
    // -> static class Symbol SWING;
}

// Range: 0x802F7248 -> 0x802F72D0
unsigned char Playback::LoadFile(class Playback * const this /* r30 */, const class String & inFilename /* r31 */) {}

// Range: 0x802F72D0 -> 0x802F73B4
void Playback::SetPlayerSink(class Playback * const this /* r7 */, class BeatMatchControllerSink * sink /* r31 */) {}

// Range: 0x802F73B4 -> 0x802F749C
void Playback::Jump(class Playback * const this /* r29 */, float ms /* f31 */) {
    // Local variables
    int i; // r30
    class DataNode & timeNode; // r0
}

struct {
    // total size: 0xC
} __vt__8Playback; // size: 0xC, address: 0x808CD1F0
struct {
    // total size: 0x8
} __RTTI__8Playback; // size: 0x8, address: 0x808CD208
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std67_Rb_tree_node<Q211stlpmtx_std35pair<Ci,P23BeatMatchControllerSink>>; // size: 0x8, address: 0x808CD268
// Range: 0x802F749C -> 0x802F74E4
static void __sinit_\Playback_cpp() {
    // References
    // -> class Playback TheBeatMatchPlayback;
}


