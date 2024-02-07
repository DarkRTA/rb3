/*
    Compile unit: C:\rockband2\band2\src\game\BandPerformer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800433A8 -> 0x80043FE8
*/
// Range: 0x800433A8 -> 0x800433E4
void BandPerformer::Poll(class BandPerformer * const this /* r31 */) {}

// Range: 0x800433E4 -> 0x80043420
int BandPerformer::GetScore(const class BandPerformer * const this /* r31 */) {}

// Range: 0x80043420 -> 0x8004345C
int BandPerformer::GetGhostScore(const class BandPerformer * const this /* r31 */) {}

// Range: 0x8004345C -> 0x800434A0
int BandPerformer::GetAccumulatedScore(const class BandPerformer * const this /* r31 */) {
    // Local variables
    int song_score; // r0
}

// Range: 0x800434A0 -> 0x8004350C
int BandPerformer::GetNumStars(const class BandPerformer * const this /* r31 */) {
    // Local variables
    int max_base; // r1+0x10
    int bonus_base; // r1+0xC
    int instr_bitfield; // r1+0x8

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x8004350C -> 0x80043588
float BandPerformer::GetNumStarsFloat(const class BandPerformer * const this /* r30 */, unsigned char enforce_diff_restrictions /* r31 */) {
    // Local variables
    int max_base; // r1+0x10
    int bonus_base; // r1+0xC
    int instr_bitfield; // r1+0x8

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80043588 -> 0x800435D4
float BandPerformer::GetTotalStars() {}

// Range: 0x800435D4 -> 0x80043634
int BandPerformer::GetScoreForStars(int numStars /* r31 */) {
    // Local variables
    int max_base; // r1+0x10
    int bonus_base; // r1+0xC
    int instr_bitfield; // r1+0x8

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80043634 -> 0x800436AC
unsigned char BandPerformer::IsNet() {
    // Local variables
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x800436AC -> 0x80043774
void BandPerformer::ComputePoints(class BandPerformer * const this /* r27 */) {
    // Local variables
    int points; // r30
    int ghost_points; // r29
    const class vector & players; // r0
    class Player * const * it; // r28
}

// Range: 0x80043774 -> 0x800437EC
int BandPerformer::CodaScore() {
    // Local variables
    int score; // r30
    const class vector & players; // r0
    class Player * const * it; // r29
}

// Range: 0x800437EC -> 0x8004387C
void BandPerformer::ForceScore(int score /* r28 */) {
    // Local variables
    unsigned char has_set_score; // r30
    const class vector & players; // r0
    class Player * const * it; // r29
}

// Range: 0x8004387C -> 0x80043988
float BandPerformer::GetNotesHitFraction() {
    // Local variables
    int total; // r30
    int totalHit; // r29
    const class vector & players; // r0
    class Player * const * it; // r28

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80043988 -> 0x80043B48
float BandPerformer::WeightedCrowdLevel(const class BandPerformer * const this /* r27 */) {
    // Local variables
    int i; // r27
    const class vector & players; // r0
    int num_players; // r26
    class DataArray * weights; // r31
    class vector ratings; // r1+0x10
    float total; // f31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pf;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A49204
static class Symbol _s; // size: 0x4, address: 0x80A4920C
// Range: 0x80043B48 -> 0x80043FE8
class DataNode BandPerformer::Handle(class BandPerformer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xE0
} __vt__13BandPerformer; // size: 0xE0, address: 0x808720C0
struct {
    // total size: 0x8
} __RTTI__13BandPerformer; // size: 0x8, address: 0x808721D0
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Modifier * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Modifier * * _M_start; // offset 0x0, size 0x4
    class Modifier * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
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
class ModifierMgr : public Object, public ListProvider {
    // total size: 0x84
    class vector mModifiers; // offset 0x2C, size 0xC
    class set mActiveModifiers; // offset 0x38, size 0x18
    class set mFeatures; // offset 0x50, size 0x18
    class map mDisabledFeatures; // offset 0x68, size 0x18
    class RndMat * mCheckboxBgMat; // offset 0x80, size 0x4
};

