/*
    Compile unit: C:\rockband2\system\src\char\CharClipSamples.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80333080 -> 0x80334F64
*/
class DataArray * types; // size: 0x4, address: 0x80A50C18
class Symbol name; // size: 0x4, address: 0x80A50C20
struct FacingBones mFacingPos; // size: 0x80, address: 0x8097DE80
struct FacingBones mFacingRotAndPos; // size: 0x80, address: 0x8097DF10
// Range: 0x80333080 -> 0x803330DC
void CharClipSamples::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x803330DC -> 0x80333130
void CharClipSamples::ListBones(class CharClipSamples * const this /* r30 */, class list & b /* r31 */) {}

// Range: 0x80333130 -> 0x80333190
int CharClipSamples::AllocSize(class CharClipSamples * const this /* r29 */) {
    // Local variables
    int graph; // r0
}

// Range: 0x80333190 -> 0x803331CC
void * FacingBones::FacingBones(struct FacingBones * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q315CharClipSamples9FacingSet11FacingBones;
}

// Range: 0x803331CC -> 0x80333344
void FacingBones::Set(struct FacingBones * const this /* r31 */, unsigned char rotAndPos /* r29 */) {
    // Local variables
    class list bones; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80333344 -> 0x80333350
void FacingBones::ReallocateInternal() {}

// Range: 0x80333350 -> 0x8033338C
void FacingSet::Init() {
    // References
    // -> struct FacingBones mFacingRotAndPos;
    // -> struct FacingBones mFacingPos;
}

// Range: 0x8033338C -> 0x803333AC
void * FacingSet::FacingSet() {}

// Range: 0x803333AC -> 0x80333400
void FacingSet::ListBones(struct FacingSet * const this /* r30 */, class list & b /* r31 */) {}

// Range: 0x80333400 -> 0x80333414
void FacingSet::ScaleDown() {}

// Range: 0x80333414 -> 0x80333600
void FacingSet::ScaleAdd(struct FacingSet * const this /* r27 */, class CharBonesSamples & full /* r28 */, class CharBones & bones /* r29 */, float weight /* f31 */, int sample /* r30 */, float frac /* f30 */, int lastSample /* r31 */, float lastFrac /* f29 */) {
    // Local variables
    class Vector3 curPos; // r1+0x20
    float curAng; // r1+0x14
    float lastAng; // r1+0x10
}

// Range: 0x80333600 -> 0x80333694
void * CharClipSamples::CharClipSamples(class CharClipSamples * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15CharClipSamples;
}

// Range: 0x80333694 -> 0x8033373C
void * CharClipSamples::~CharClipSamples(class CharClipSamples * const this /* r29 */) {}

// Range: 0x8033373C -> 0x8033376C
int CharClipSamples::FrameToSample() {}

// Range: 0x8033376C -> 0x80333798
int CharClipSamples::NumSamples() {}

// Range: 0x80333798 -> 0x8033399C
void CharClipSamples::FreezeBones(class CharClipSamples * const this /* r30 */, const class vector & bones /* r31 */) {
    // Local variables
    class vector bs; // r1+0x3C
    int i; // r29
    int index; // r0
}

// Range: 0x8033399C -> 0x80333A24
void * CharClipSamples::GetChannel(class CharClipSamples * const this /* r30 */, class Symbol & name /* r31 */) {
    // Local variables
    int d; // r0
}

// Range: 0x80333A24 -> 0x80333AB8
unsigned char CharClipSamples::EvaluateChannel() {
    // Local variables
    int offset; // r7

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80333AB8 -> 0x80333B18
unsigned char CharClipSamples::EvaluateChannel(class CharClipSamples * const this /* r29 */, void * dst /* r30 */, void * data /* r31 */) {
    // Local variables
    float frac; // r1+0x8
    int sample; // r0
}

// Range: 0x80333B18 -> 0x80333B64
void CharClipSamples::SetWeights(class CharClipSamples * const this /* r31 */, float w /* f31 */) {}

// Range: 0x80333B64 -> 0x80333BCC
void CharClipSamples::ScaleDown(class CharClipSamples * const this /* r30 */, class CharBones & bones /* r31 */, float scale /* f31 */) {}

// Range: 0x80333BCC -> 0x80333C70
void CharClipSamples::RotateBy(class CharClipSamples * const this /* r29 */, class CharBones & bones /* r30 */) {
    // Local variables
    float frac; // r1+0x8
    int sample; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80333C70 -> 0x80333CF4
void CharClipSamples::RotateTo(class CharClipSamples * const this /* r30 */, class CharBones & bones /* r31 */, float weight /* f31 */) {
    // Local variables
    float frac; // r1+0x8
    int sample; // r0
}

// Range: 0x80333CF4 -> 0x80333DAC
void CharClipSamples::ScaleAdd(class CharClipSamples * const this /* r29 */, class CharBones & bones /* r30 */, float weight /* f29 */, float frame /* f30 */, float dframe /* f31 */) {
    // Local variables
    float frac; // r1+0xC
    float lastFrac; // r1+0x8
    int sample; // r31
    int lastSample; // r0
}

// Range: 0x80333DAC -> 0x80333E78
void CharClipSamples::ScaleAdd(class CharClipSamples * const this /* r28 */, class CharBones & bones /* r29 */, float weight /* f29 */, int sample /* r30 */, float frac /* f30 */, int lastSample /* r31 */, float lastFrac /* f31 */) {}

// Range: 0x80333E78 -> 0x80333ED4
unsigned char CharClipSamples::BoneWeights(class CharClipSamples * const this /* r30 */) {}

// Range: 0x80333ED4 -> 0x80333F94
void CharClipSamples::Relativize(class CharClipSamples * const this /* r30 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80333F94 -> 0x80334058
void CharClipSamples::SetRelative(class CharClipSamples * const this /* r30 */, class CharClip * clip /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80334058 -> 0x803340AC
float CharClipSamples::SamplesPerFrame() {
    // Local variables
    float length; // f0
}

// Range: 0x803340AC -> 0x80334100
void CharClipSamples::ChangeCompression(class CharClipSamples * const this /* r30 */, enum CompressionType comp /* r31 */) {}

// Range: 0x80334100 -> 0x80334108
void CharClipSamples::DecimateKeyframes() {}

// Range: 0x80334108 -> 0x803341E4
void CharClipSamples::Print(class CharClipSamples * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A50C24
// Range: 0x803341E4 -> 0x80334274
void CharClipSamples::Save(class CharClipSamples * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80334274 -> 0x80334470
void CharClipSamples::Load(class CharClipSamples * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class CharBonesSamples delta; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80334470 -> 0x803344F8
void CharClipSamples::Copy(class CharClipSamples * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class CharClipSamples * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharClipSamples;
}

static class Symbol _s; // size: 0x4, address: 0x80A50C2C
static class Symbol _s; // size: 0x4, address: 0x80A50C34
static class Symbol _s; // size: 0x4, address: 0x80A50C3C
// Range: 0x803344F8 -> 0x80334AFC
class DataNode CharClipSamples::Handle(class CharClipSamples * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80334AFC -> 0x80334C68
class DataNode CharClipSamples::OnFreezeBones(class CharClipSamples * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    class vector s; // r1+0x2C
    class DataArray * arr; // r31
    int i; // r30
}

static class Symbol _s; // size: 0x4, address: 0x80A50C44
static class Symbol _s; // size: 0x4, address: 0x80A50C4C
static class Symbol _s; // size: 0x4, address: 0x80A50C54
// Range: 0x80334C68 -> 0x80334E34
unsigned char CharClipSamples::SyncProperty(class CharClipSamples * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB4
} __vt__15CharClipSamples; // size: 0xB4, address: 0x808D2330
struct {
    // total size: 0x1C
} __vt__Q315CharClipSamples9FacingSet11FacingBones; // size: 0x1C, address: 0x808D2420
struct {
    // total size: 0x8
} __RTTI__Q315CharClipSamples9FacingSet11FacingBones; // size: 0x8, address: 0x808D2478
// Range: 0x80334E34 -> 0x80334E9C
static void __sinit_\CharClipSamples_cpp() {
    // References
    // -> struct FacingBones mFacingRotAndPos;
    // -> struct FacingBones mFacingPos;
}


