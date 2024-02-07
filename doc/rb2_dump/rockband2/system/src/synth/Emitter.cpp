/*
    Compile unit: C:\rockband2\system\src\synth\Emitter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8056C894 -> 0x8056E10C
*/
class DataArray * types; // size: 0x4, address: 0x80A541A8
class Symbol name; // size: 0x4, address: 0x80A541B0
static class RndDir * gIconDir; // size: 0x4, address: 0x80A541B4
class SynthEmitter : public RndTransformable, public RndDrawable, public RndPollable {
    // total size: 0x170
    class ObjPtr mSfx; // offset 0xFC, size 0xC
    class ObjPtr mInst; // offset 0x108, size 0xC
    class ObjPtr mListener; // offset 0x114, size 0xC
    unsigned char mEnabled; // offset 0x120, size 0x1
    float mRadInner; // offset 0x124, size 0x4
    float mRadOuter; // offset 0x128, size 0x4
    float mVolInner; // offset 0x12C, size 0x4
    float mVolOuter; // offset 0x130, size 0x4
};
// Range: 0x8056C894 -> 0x8056C9F4
void SynthEmitter::Copy(class SynthEmitter * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class SynthEmitter * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12SynthEmitter;
}

static int kEmitterRev; // size: 0x4, address: 0x80A47660
// Range: 0x8056C9F4 -> 0x8056CA38
void SynthEmitter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8056CA38 -> 0x8056CB90
void SynthEmitter::Load(class SynthEmitter * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int kEmitterRev;
}

// Range: 0x8056CB90 -> 0x8056CC90
void SynthEmitter::DrawShowing(class SynthEmitter * const this /* r31 */) {
    // References
    // -> static class RndDir * gIconDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8056CC90 -> 0x8056CD34
class RndDrawable * SynthEmitter::CollideShowing(class SynthEmitter * const this /* r28 */, const class Segment & s /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {
    // References
    // -> static class RndDir * gIconDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8056CD34 -> 0x8056CD94
int SynthEmitter::CollidePlane(const class Plane & plane /* r31 */) {
    // References
    // -> static class RndDir * gIconDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8056CD94 -> 0x8056CEB4
void SynthEmitter::CheckLoadResources() {
    // Local variables
    class FilePath resFile; // r1+0x8
    class ObjectDir * d; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class RndDir * gIconDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8056CEB4 -> 0x8056D188
void SynthEmitter::Poll(class SynthEmitter * const this /* r29 */) {
    // Local variables
    class Transform invList; // r1+0x30
    class Vector3 v; // r1+0x20
    float r; // f0
    unsigned char isNew; // r0
    float vol; // f0
    float ang; // f1

    // References
    // -> struct [anonymous] __RTTI__7SeqInst;
    // -> struct [anonymous] __RTTI__7SfxInst;
}

// Range: 0x8056D188 -> 0x8056D34C
void * SynthEmitter::~SynthEmitter(class SynthEmitter * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7SfxInst,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__12SynthEmitter;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class SfxInst * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8056D34C -> 0x8056D530
void * SynthEmitter::SynthEmitter(class SynthEmitter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7SfxInst,9ObjectDir>;
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
    // -> struct [anonymous] __vt__12SynthEmitter;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8056D530 -> 0x8056DA50
class DataNode SynthEmitter::Handle(class SynthEmitter * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A541BC
static class Symbol _s; // size: 0x4, address: 0x80A541C4
static class Symbol _s; // size: 0x4, address: 0x80A541CC
static class Symbol _s; // size: 0x4, address: 0x80A541D4
static class Symbol _s; // size: 0x4, address: 0x80A541DC
static class Symbol _s; // size: 0x4, address: 0x80A541E4
static class Symbol _s; // size: 0x4, address: 0x80A541EC
// Range: 0x8056DA50 -> 0x8056E10C
unsigned char SynthEmitter::SyncProperty(class SynthEmitter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x128
} __vt__12SynthEmitter; // size: 0x128, address: 0x8091AFD0
struct {
    // total size: 0x8
} __RTTI__12SynthEmitter; // size: 0x8, address: 0x8091B140
struct {
    // total size: 0x18
} __vt__27ObjPtr<7SfxInst,9ObjectDir>; // size: 0x18, address: 0x8091B148
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7SfxInst,9ObjectDir>; // size: 0x8, address: 0x8091B188
struct {
    // total size: 0x8
} __RTTI__7SfxInst; // size: 0x8, address: 0x8091B200
struct {
    // total size: 0x8
} __RTTI__7SeqInst; // size: 0x8, address: 0x8091B258

