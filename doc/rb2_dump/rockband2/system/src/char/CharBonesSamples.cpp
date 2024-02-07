/*
    Compile unit: C:\rockband2\system\src\char\CharBonesSamples.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80322D70 -> 0x803266E8
*/
// Range: 0x80322D70 -> 0x80322DC8
void * CharBonesSamples::CharBonesSamples(class CharBonesSamples * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16CharBonesSamples;
}

// Range: 0x80322DC8 -> 0x80322EE0
void * CharBonesSamples::~CharBonesSamples(class CharBonesSamples * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16CharBonesSamples;
}

// Range: 0x80322EE0 -> 0x80322F48
void CharBonesSamples::Clone(class CharBonesSamples * const this /* r30 */, const class CharBonesSamples & b /* r31 */) {}

// Range: 0x80322F48 -> 0x80323038
void CharBonesSamples::Transfer(class CharBonesSamples * const this /* r29 */, class CharBonesSamples & b /* r30 */) {}

// Range: 0x80323038 -> 0x8032324C
void CharBonesSamples::InsertBones(class CharBonesSamples * const this /* r30 */, const class vector & bones /* r31 */) {
    // Local variables
    class CharBonesSamples tmp; // r1+0x38
    class vector bs; // r1+0x2C
    int i; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ29CharBones4Bone;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8032324C -> 0x80323410
void CharBonesSamples::RemoveBones(class CharBonesSamples * const this /* r29 */, const class vector & bones /* r30 */) {
    // Local variables
    class CharBonesSamples tmp; // r1+0x30
    const class vector & src; // r0
    class vector bs; // r1+0x24
    int i; // r31
    int j; // r7
}

// Range: 0x80323410 -> 0x80323420
int CharBonesSamples::AllocateSize() {}

// Range: 0x80323420 -> 0x80323654
int CharBonesSamples::FracToSample(float * frac /* r30 */) {
    // Local variables
    int lastSample; // r6
    int sample; // r29
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80323654 -> 0x80323E64
void CharBonesSamples::EvaluateChannel() {
    // Local variables
    const char * src; // r6
    const char * src2; // r7
    float & d; // r0
    class Quat a; // r1+0x60
    class Quat b; // r1+0x50
    class Quat a; // r1+0x40
    class Quat b; // r1+0x30
    class Vector3 a; // r1+0x20
    class Vector3 b; // r1+0x10
}

// Range: 0x80323E64 -> 0x80323E7C
void CharBonesSamples::RotateBy() {}

// Range: 0x80323E7C -> 0x80323F3C
void CharBonesSamples::RotateTo(class CharBonesSamples * const this /* r29 */, class CharBones & bones /* r30 */, float weight /* f30 */, int sample /* r31 */, float frac /* f31 */) {}

// Range: 0x80323F3C -> 0x80323FFC
void CharBonesSamples::ScaleAddSample(class CharBonesSamples * const this /* r29 */, class CharBones & bones /* r30 */, float weight /* f30 */, int sample /* r31 */, float frac /* f31 */) {}

// Range: 0x80323FFC -> 0x803250DC
void CharBonesSamples::Relativize(class CharBonesSamples * const this /* r26 */, class CharClip * clip /* r27 */) {
    // Local variables
    int i; // r31
    const struct Bone * bone; // r30
    struct ShortVector3 * sp; // [invalid]
    class Vector3 first; // r1+0x140
    class Vector3 v; // r1+0x130
    class Vector3 * p; // r29
    class Vector3 first; // r1+0x120
    struct ByteQuat * bq; // [invalid]
    class Quat first; // r1+0x110
    class Matrix3 firstMat; // r1+0x240
    class Quat q; // r1+0x100
    class Matrix3 m; // r1+0x210
    signed short * sa; // r29
    float first; // r1+0x38
    float a; // f1
    struct ShortQuat * sq; // [invalid]
    class Quat first; // r1+0xF0
    class Matrix3 firstMat; // r1+0x1E0
    class Quat q; // r1+0xE0
    class Matrix3 m; // r1+0x1B0
    signed short * sa; // r29
    float first; // r1+0x34
    float a; // f1
    class Quat * q; // r28
    class Quat first; // r1+0xD0
    class Matrix3 firstMat; // r1+0x180
    class Matrix3 m; // r1+0x150
    float * a; // r29
    float first; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803250DC -> 0x80325160
void CharBonesSamples::ChangeCompression(class CharBonesSamples * const this /* r30 */, enum CompressionType comp /* r31 */) {
    // Local variables
    class CharBonesSamples old; // r1+0x8
}

// Range: 0x80325160 -> 0x803251F0
void CharBonesSamples::DecimateKeyframes(class CharBonesSamples * const this /* r28 */, int num /* r29 */) {
    // Local variables
    int i; // r31
    int j; // r30
}

// Range: 0x803251F0 -> 0x8032551C
void CharBonesSamples::RemoveKeyframe(class CharBonesSamples * const this /* r30 */, int which /* r31 */) {
    // Local variables
    int i; // r4
    class CharBonesSamples old; // r1+0x18
    int i; // r29
    int last; // r6
    int next; // [invalid]
    int i; // r7
    int i; // r8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032551C -> 0x8032575C
void CharBonesSamples::Groom() {
    // Local variables
    int i; // r5
    class Quat * q; // r6
    float * a; // r7
}

// Range: 0x8032575C -> 0x8032577C
void CharBonesSamples::SetKeyFrame(int sample /* r6 */) {}

// Range: 0x8032577C -> 0x80325898
void CharBonesSamples::Print(class CharBonesSamples * const this /* r30 */) {
    // Local variables
    int i; // r31
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80325898 -> 0x80325A34
void CharBonesSamples::DeleteSamples(class CharBonesSamples * const this /* r30 */, int firstSample /* r31 */, int numSamples /* r26 */) {
    // Local variables
    char * oldData; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int gVer; // size: 0x4, address: 0x80A50A58
// Range: 0x80325A34 -> 0x80325A94
void CharBonesSamples::SetVer(int ver /* r31 */) {
    // References
    // -> static int gVer;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80325A94 -> 0x80325AD8
void CharBonesSamples::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80325AD8 -> 0x80325B8C
void CharBonesSamples::Load(class CharBonesSamples * const this /* r28 */, class BinStream & d /* r29 */, const char * dirName /* r30 */, const char * clipName /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gVer;
}

// Range: 0x80325B8C -> 0x80325C9C
void CharBonesSamples::ReadCounts(class CharBonesSamples * const this /* r28 */, class BinStream & d /* r29 */, int count /* r1+0x8 */) {
    // Local variables
    int i; // [invalid]
    int read; // r31
    int j; // r31
    int tmp; // r1+0xC
    int j; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80325C9C -> 0x80326054
void CharBonesSamples::LoadHeader(class CharBonesSamples * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int size; // r1+0x2C
    int i; // r31
    int count; // r28
    int tmp; // r1+0x28

    // References
    // -> static int gVer;
    // -> const char * gNullStr;
}

// Range: 0x80326054 -> 0x80326370
void CharBonesSamples::LoadData(class CharBonesSamples * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int i; // r1+0x10
    const struct ShortVector3 * send; // r29
    struct ShortVector3 * sp; // [invalid]
    const class Vector3 * send; // r29
    class Vector3 * p; // r28
    const struct ByteQuat * qend; // r28
    struct ByteQuat * bq; // r29
    const struct ShortQuat * qend; // r28
    struct ShortQuat * q; // r29
    const class Quat * qend; // r28
    class Quat * q; // r29
    const signed short * rend; // r28
    signed short * a; // r29
    const float * rend; // r28
    float * a; // r29

    // References
    // -> static int gVer;
}

// Range: 0x80326370 -> 0x803263A8
void CharBonesSamples::SetPreview() {}

static class Symbol _s; // size: 0x4, address: 0x80A50A60
static class Symbol _s; // size: 0x4, address: 0x80A50A68
static class Symbol _s; // size: 0x4, address: 0x80A50A70
static class Symbol _s; // size: 0x4, address: 0x80A50A78
static class Symbol _s; // size: 0x4, address: 0x80A50A80
// Range: 0x803263A8 -> 0x803266E8
unsigned char CharBonesSamples::SyncProperty(class CharBonesSamples * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class CharBones * gPropBones;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x20
} __vt__16CharBonesSamples; // size: 0x20, address: 0x808D1068
struct {
    // total size: 0x8
} __RTTI__16CharBonesSamples; // size: 0x8, address: 0x808D10A8

