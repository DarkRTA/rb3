/*
    Compile unit: C:\rockband2\system\src\rndobj\Morph.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804CB83C -> 0x804CD884
*/
class DataArray * types; // size: 0x4, address: 0x80A53278
class Symbol name; // size: 0x4, address: 0x80A53280
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class RndMorph : public RndAnimatable {
    // total size: 0x60
protected:
    class ObjVector mPoses; // offset 0x10, size 0x10
    class ObjPtr mTarget; // offset 0x20, size 0xC
    unsigned char mNormals; // offset 0x2C, size 0x1
    unsigned char mSpline; // offset 0x2D, size 0x1
    float mIntensity; // offset 0x30, size 0x4
};
// Range: 0x804CB83C -> 0x804CB920
void * RndMorph::RndMorph(class RndMorph * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__8RndMorph;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Pose * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Pose * _M_start; // offset 0x0, size 0x4
    struct Pose * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x804CB920 -> 0x804CBBE0
float RndMorph::InterpWeight(class RndMorph * const this /* r23 */, const class Keys & weightKeys /* r24 */, float frame /* f31 */) {
    // Local variables
    const float * prev; // r26
    const float * next; // r25
    float r; // f2
    float d; // f3
    float a; // f4
    float b; // f0
}

struct iterator {
    // total size: 0x1
};
class reverse_iterator : public iterator {
    // total size: 0x4
protected:
    struct Pose * current; // offset 0x0, size 0x4
};
// Range: 0x804CBBE0 -> 0x804CC0E4
void RndMorph::SetFrame(class RndMorph * const this /* r28 */, float frame /* f28 */, float blend /* f29 */) {
    // Local variables
    unsigned char init; // r30
    float refWeight; // f31
    float weight; // f30
    class Vert * in; // r29
    class Vert * out; // r26
    class Vert * in_end; // r0
    class Vert * out_end; // r0
    class reverse_iterator pose; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int MORPH_REV; // size: 0x4, address: 0x80A472C8
// Range: 0x804CC0E4 -> 0x804CC128
void RndMorph::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A53284
class Keys : public vector {
    // total size: 0xC
};
// Range: 0x804CC128 -> 0x804CC304
class BinStream & __rs(class BinStream & d /* r30 */, struct Pose & c /* r31 */) {
    // Local variables
    class Keys weightKeys; // r1+0x38
    class Key * in; // r4
    class Key * out; // r5

    // References
    // -> static int gRev;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x804CC304 -> 0x804CC464
void RndMorph::Load(class RndMorph * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int MORPH_REV;
    // -> static int gRev;
}

static class Symbol _s; // size: 0x4, address: 0x80A5328C
static class Symbol _s; // size: 0x4, address: 0x80A53294
static class Symbol _s; // size: 0x4, address: 0x80A5329C
static class Symbol _s; // size: 0x4, address: 0x80A532A4
static class Symbol _s; // size: 0x4, address: 0x80A532AC
static class Symbol _s; // size: 0x4, address: 0x80A532B4
// Range: 0x804CC464 -> 0x804CD260
class DataNode RndMorph::Handle(class RndMorph * const this /* r30 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r28 */) {
    // Local variables
    class Symbol _type; // r1+0x74
    class MessageTimer _mt; // r1+0xC8
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode _n; // r1+0x80
    class DataNode _n; // r1+0x78

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804CD260 -> 0x804CD2C4
class DataNode RndMorph::OnSetIntensity(class RndMorph * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804CD2C4 -> 0x804CD384
class DataNode RndMorph::OnSetTarget(class RndMorph * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x804CD384 -> 0x804CD69C
class DataNode RndMorph::OnSetPoseWeight(class RndMorph * const this /* r29 */, const class DataArray * a /* r27 */) {
    // Local variables
    class Keys & keys; // r29
    float frame; // f0
    float value; // f0
    class Key * i; // r3
}

// Range: 0x804CD69C -> 0x804CD71C
class DataNode RndMorph::OnPoseMesh(class RndMorph * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804CD71C -> 0x804CD804
class DataNode RndMorph::OnSetPoseMesh(class RndMorph * const this /* r29 */, const class DataArray * a /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x804CD804 -> 0x804CD884
unsigned char RndMorph::SyncProperty(class RndMorph * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA4
} __vt__8RndMorph; // size: 0xA4, address: 0x808FB88C
struct {
    // total size: 0x8
} __RTTI__8RndMorph; // size: 0x8, address: 0x808FB958
struct {
    // total size: 0x8
} __RTTI__PQ28RndMorph4Pose; // size: 0x8, address: 0x808FBB30
struct Weight {
    // total size: 0xC
    float weight; // offset 0x0, size 0x4
    float derivIn; // offset 0x4, size 0x4
    float derivOut; // offset 0x8, size 0x4
};
class Key {
    // total size: 0x10
public:
    struct Weight value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};
struct Pose {
    // total size: 0x18
    class ObjPtr mesh; // offset 0x0, size 0xC
    class Keys weightKeys; // offset 0xC, size 0xC
};
struct {
    // total size: 0x8
} __RTTI__P12Key<6Weight>; // size: 0x8, address: 0x808FBB48

