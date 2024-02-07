/*
    Compile unit: C:\rockband2\system\src\char\CharServoBone.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8038F180 -> 0x80390CBC
*/
class DataArray * types; // size: 0x4, address: 0x80A513A8
// Range: 0x8038F180 -> 0x8038F314
void * CharServoBone::CharServoBone(class CharServoBone * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharServoBone;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x8038F314 -> 0x8038F444
void * CharServoBone::~CharServoBone(class CharServoBone * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Waypoint,9ObjectDir>;
}

// Range: 0x8038F444 -> 0x8038F4A0
void CharServoBone::SetName(class CharServoBone * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9Character;
}

// Range: 0x8038F4A0 -> 0x8038F820
void CharServoBone::Poll(class CharServoBone * const this /* r31 */) {
    // Local variables
    class Transform world; // r1+0x130
    class Transform worldPelv; // r1+0xF0
    class Transform invPelv; // r1+0xB0
    class Transform worldPelv; // r1+0x70
    class Transform invPelv; // r1+0x30
}

// Range: 0x8038F820 -> 0x8038F898
void CharServoBone::Enter(class CharServoBone * const this /* r31 */) {}

// Range: 0x8038F898 -> 0x8038F8B0
void CharServoBone::Recenter() {}

// Range: 0x8038F8B0 -> 0x8038F8E4
void CharServoBone::ZeroDeltas() {}

// Range: 0x8038F8E4 -> 0x8038F900
void CharServoBone::SetMoveSelf() {}

// Range: 0x8038F900 -> 0x8038FB48
void CharServoBone::MoveToFacing(class CharServoBone * const this /* r30 */, class Transform & t /* r31 */) {}

// Range: 0x8038FB48 -> 0x8038FD74
void CharServoBone::MoveToDeltaFacing(class Transform & t /* r31 */) {
    // Local variables
    class Vector3 dPos; // r1+0x10
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class RndTransformable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class RndTransformable * * _M_start; // offset 0x0, size 0x4
    class RndTransformable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ClipBonePredict {
    // total size: 0x130
protected:
    class Transform mBaseXfm; // offset 0x0, size 0x40
    class Transform mXfm; // offset 0x40, size 0x40
    class CharBonesMeshes mBones; // offset 0x80, size 0x98
    class Vector3 * mFacingPos; // offset 0x118, size 0x4
    float * mFacingRot; // offset 0x11C, size 0x4
    class vector mMeshes; // offset 0x120, size 0xC
};
// Range: 0x8038FD74 -> 0x8038FF30
void CharServoBone::RegulateOverride(class CharServoBone * const this /* r28 */, class CharClip * c /* r29 */, float frame /* f31 */, class Waypoint * way /* r30 */, const char * bone /* r31 */) {
    // Local variables
    char * names[2]; // r1+0x18
    class ClipBonePredict pred; // r1+0x20
}

// Range: 0x8038FF30 -> 0x803901BC
void CharServoBone::Regulate(class CharServoBone * const this /* r26 */) {
    // Local variables
    class CharClipDriver * before; // r0
    class Waypoint * w; // r27
    class ClipPredict pred; // r1+0x40
    float rawDf; // f2
    float df; // f29
    float dt; // f31
    class Vector3 pos; // r1+0x30
    class Vector3 delta; // r1+0x20
    float dang; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803901BC -> 0x803901C8
void CharServoBone::PollDeps() {}

// Range: 0x803901C8 -> 0x80390220
void CharServoBone::Save(class CharServoBone * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A513B0
// Range: 0x80390220 -> 0x803902E0
void CharServoBone::Load(class CharServoBone * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803902E0 -> 0x8039034C
void CharServoBone::Copy(class CharServoBone * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class CharServoBone * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharServoBone;
}

static class Symbol _s; // size: 0x4, address: 0x80A513B8
// Range: 0x8039034C -> 0x803908C8
class DataNode CharServoBone::Handle(class CharServoBone * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A513C0
static class Symbol _s; // size: 0x4, address: 0x80A513C8
static class Symbol _s; // size: 0x4, address: 0x80A513D0
// Range: 0x803908C8 -> 0x80390B54
unsigned char CharServoBone::SyncProperty(class CharServoBone * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80390B54 -> 0x80390CBC
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xC4
} __vt__13CharServoBone; // size: 0xC4, address: 0x808DB6A0
struct {
    // total size: 0x18
} __vt__28ObjPtr<8Waypoint,9ObjectDir>; // size: 0x18, address: 0x808DB7C0
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8Waypoint,9ObjectDir>; // size: 0x8, address: 0x808DB800

