/*
    Compile unit: C:\rockband2\system\src\beatmatch\BarFinder.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D085C -> 0x802D0AF8
*/
class BarFinder {
    // total size: 0x18
protected:
    class SongData * mSongData; // offset 0x0, size 0x4
    int mTrack; // offset 0x4, size 0x4
    int mRoundTicks; // offset 0x8, size 0x4
    class vector mBars; // offset 0xC, size 0xC
};
// Range: 0x802D085C -> 0x802D087C
void * BarFinder::BarFinder() {}

class StlNodeAlloc {
    // total size: 0x1
};
struct BarInfo {
    // total size: 0x10
    int start_gem; // offset 0x0, size 0x4
    int end_gem; // offset 0x4, size 0x4
    float start_ms; // offset 0x8, size 0x4
    float end_ms; // offset 0xC, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BarInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BarInfo * _M_start; // offset 0x0, size 0x4
    struct BarInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x802D087C -> 0x802D0A74
void BarFinder::Init(class BarFinder * const this /* r26 */) {
    // Local variables
    const class GameGemList & gems; // r31
    class TempoMap * tempo_map; // r30
    class MeasureMap * measure_map; // r29
    float last_ms; // f0
    int num_gems; // r28
    int measure; // r27
    int start_gem; // r22
    float start_ms; // f29
    int end_tick; // r0
    float end_ms; // f28
    float rounded_end_ms; // f0
    int end_gem; // r23
}

// Range: 0x802D0A74 -> 0x802D0AF8
int BarFinder::GetBarIndexWithGem(const class BarFinder * const this /* r31 */, int gem /* r1+0x8 */) {}

struct {
    // total size: 0x8
} __RTTI__P7BarInfo; // size: 0x8, address: 0x808C9EA8

