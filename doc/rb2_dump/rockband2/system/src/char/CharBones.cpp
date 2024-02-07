/*
    Compile unit: C:\rockband2\system\src\char\CharBones.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8031B7E8 -> 0x8031F2C0
*/
class DataArray * types; // size: 0x4, address: 0x80A50A00
// Range: 0x8031B7E8 -> 0x8031B83C
void * CharBones::CharBones() {
    // Local variables
    int i; // r5

    // References
    // -> struct [anonymous] __vt__9CharBones;
}

static char * suffixes[7]; // size: 0x1C, address: 0x808D03F4
// Range: 0x8031B83C -> 0x8031B8AC
char * CharBones::SuffixOf(enum Type t /* r30 */) {
    // References
    // -> static char * suffixes[7];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8031B8AC -> 0x8031B954
class Symbol CharBones::ChannelName(const char * name /* r31 */, enum Type t /* r30 */) {
    // Local variables
    char buffer[256]; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8031B954 -> 0x8031B9D8
int CharBones::CompareBones(class Symbol & a /* r29 */, class Symbol & b /* r30 */) {
    // Local variables
    int at; // r0
    int bt; // r0
}

// Range: 0x8031B9D8 -> 0x8031BAB4
void CharBones::ClearBones() {
    // Local variables
    int i; // r5
}

// Range: 0x8031BAB4 -> 0x8031BB04
unsigned char CharBones::BoneWeights() {
    // Local variables
    int i; // r5
}

// Range: 0x8031BB04 -> 0x8031BB3C
void CharBones::SetWeights() {
    // Local variables
    int i; // r5
}

// Range: 0x8031BB3C -> 0x8031BC4C
void CharBones::AddBoneInternal(class CharBones * const this /* r30 */, const struct Bone & bone /* r28 */) {
    // Local variables
    int t; // r31
    int i; // r29
    int delta; // r0
}

// Range: 0x8031BC4C -> 0x8031BCC0
void CharBones::AddBones(class CharBones * const this /* r29 */, const class vector & bones /* r30 */) {
    // Local variables
    const struct Bone * it; // r31
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8031BCC0 -> 0x8031BD4C
void CharBones::AddBones(class CharBones * const this /* r30 */, const class list & bones /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x18
}

// Range: 0x8031BD4C -> 0x8031BE18
void CharBones::ListBones(const class CharBones * const this /* r28 */, class list & bones /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<Q29CharBones4Bone>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8031BE18 -> 0x8031BE2C
void CharBones::Zero(class CharBones * const this /* r5 */) {}

// Range: 0x8031BE2C -> 0x8031BE9C
int CharBones::TypeSize() {}

// Range: 0x8031BE9C -> 0x8031BF58
int CharBones::FindOffset(const class CharBones * const this /* r28 */, class Symbol & name /* r29 */) {
    // Local variables
    int t; // r31
    int end; // r30
    int size; // r0
    int offset; // r5
    int i; // r6
}

// Range: 0x8031BF58 -> 0x8031C008
int CharBones::FindIndex(const class CharBones * const this /* r28 */, class Symbol & name /* r29 */) {
    // Local variables
    int t; // r31
    int end; // r30
    int i; // r3
}

// Range: 0x8031C008 -> 0x8031C058
void * CharBones::FindPtr(const class CharBones * const this /* r31 */) {
    // Local variables
    int offset; // r0
}

// Range: 0x8031C058 -> 0x8031C33C
void CharBones::ScaleDown() {
    // Local variables
    const struct Bone * name; // r5
    const struct Bone * endName; // r9
    const struct Bone * boneName; // r6
    class Vector3 * pos; // r10
    class Quat * quat; // r10
    float * ang; // r4
    class Vector3 * pos; // r10
    class Quat * quat; // r10
    float * ang; // r4
}

struct ShortVector3 {
    // total size: 0x6
    signed short x; // offset 0x0, size 0x2
    signed short y; // offset 0x2, size 0x2
    signed short z; // offset 0x4, size 0x2
};
// Range: 0x8031C33C -> 0x8031CB00
void CharBones::ScaleAdd() {
    // Local variables
    const struct Bone * name; // r5
    const struct Bone * endName; // r6
    struct Bone * boneName; // r7
    class Vector3 * pos; // r10
    const struct ShortVector3 * sp; // r11
    class Vector3 v; // r1+0x40
    const class Vector3 * p; // r11
    float fweight; // f0
    class Quat * quat; // r8
    float fqweight; // f3
    float qweight; // f4
    const struct ByteQuat * bq; // r11
    class Quat s; // r1+0x30
    float fqweight; // f3
    float qweight; // f4
    const struct ShortQuat * qs; // r11
    class Quat s; // r1+0x20
    const class Quat * q; // r11
    class Quat s; // r1+0x10
    float * ang; // r8
    float aweight; // f3
    const signed short * as; // r4
    const float * a; // r4
}

// Range: 0x8031CB00 -> 0x8031D118
void CharBones::RotateBy() {
    // Local variables
    const struct Bone * name; // r5
    const struct Bone * endName; // r6
    const struct Bone * boneName; // r7
    class Vector3 * pos; // r10
    const struct ShortVector3 * sp; // r11
    class Vector3 v; // r1+0x30
    const class Vector3 * p; // r11
    class Quat * quat; // r8
    const struct ByteQuat * bq; // r11
    class Quat s; // r1+0x20
    const struct ShortQuat * qs; // r11
    class Quat s; // r1+0x10
    const class Quat * q; // r11
    float * ang; // r8
    const signed short * as; // r4
    const float * a; // r4
}

// Range: 0x8031D118 -> 0x8031D864
void CharBones::RotateTo() {
    // Local variables
    const struct Bone * name; // r5
    const struct Bone * endName; // r6
    const struct Bone * boneName; // r7
    class Vector3 * pos; // r10
    const struct ShortVector3 * sp; // r11
    class Vector3 v; // r1+0x40
    const class Vector3 * p; // r11
    class Quat * quat; // r8
    const struct ByteQuat * bq; // r11
    class Quat s; // r1+0x30
    const struct ShortQuat * qs; // r11
    class Quat s; // r1+0x20
    const class Quat * q; // r11
    class Quat s; // r1+0x10
    float * ang; // r8
    float shortWeight; // f2
    const signed short * as; // r4
    const float * a; // r4
}

// Range: 0x8031D864 -> 0x8031D8B0
void CharBones::ScaleAddIdentity() {
    // Local variables
    const class Quat * end; // r5
    class Quat * q; // r3
}

// Range: 0x8031D8B0 -> 0x8031D950
void CharBones::RecomputeSizes(class CharBones * const this /* r31 */) {
    // Local variables
    int i; // r28
    int num; // r27
}

// Range: 0x8031D950 -> 0x8031D968
void CharBones::SetCompression() {}

static class Transform t; // size: 0x40, address: 0x8097DDF0
// Range: 0x8031D968 -> 0x8031DC00
static class Transform & LocalXfm() {
    // Local variables
    class RndTransformable * trans; // r0
    class CharBone * bone; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__8CharBone;
    // -> static class Transform t;
}

// Range: 0x8031DC00 -> 0x8031DF38
void CharBones::SetFromMeshes(class CharBones * const this /* r29 */, class ObjectDir * dir /* r30 */) {
    // Local variables
    const struct Bone * bone; // r31
    class Vector3 * p; // r28
    class Vector3 * s; // r27
    class Quat * q; // r28
    class Matrix3 mat; // r1+0x10
    float * a; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8031DF38 -> 0x8031EA5C
void CharBones::CopyInto(const class CharBones * const this /* r30 */, class CharBones & set /* r31 */) {
    // Local variables
    const struct Bone * bone; // r29
    const struct Bone * oldBone; // r28
    struct ShortVector3 * p; // r27
    const struct ShortVector3 * end; // r26
    struct ShortVector3 * oldP; // r22
    const struct ShortVector3 * oldEnd; // r23
    class Vector3 * oldP; // r22
    const class Vector3 * oldEnd; // r23
    class Vector3 * p; // r26
    const class Vector3 * end; // r27
    struct ShortVector3 * oldPos; // r25
    const struct ShortVector3 * oldEnd; // r24
    class Vector3 * oldPos; // r22
    const class Vector3 * oldEnd; // r23
    const struct Bone * bone; // r24
    int newSize; // r25
    char * q; // r26
    const char * end; // r27
    const struct Bone * oldBone; // r28
    int oldSize; // r0
    char * oldQ; // r23
    const char * oldEnd; // r22
    class Quat tempQuat; // r1+0x40
    struct ShortQuat * newQ; // r0
    class Quat * q; // r0
    const struct Bone * bone; // r22
    int newSize; // r23
    char * a; // r24
    const char * end; // r26
    const struct Bone * oldBone; // r27
    int oldSize; // r0
    char * oldA; // r28
    const char * oldEnd; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8031EA5C -> 0x8031EA78
void CharBones::ScaleAdd(class CharBones * const this /* r0 */) {}

// Range: 0x8031EA78 -> 0x8031EA88
void CharBones::StuffBones(class CharBones * const this /* r0 */) {}

// Range: 0x8031EA88 -> 0x8031EBB0
void * CharBonesAlloc::~CharBonesAlloc(class CharBonesAlloc * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14CharBonesAlloc;
}

// Range: 0x8031ECA0 -> 0x8031ECE8
void CharBonesAlloc::ReallocateInternal(class CharBonesAlloc * const this /* r31 */) {}

class CharBones * gPropBones; // size: 0x4, address: 0x80A50A08
static class Symbol _s; // size: 0x4, address: 0x80A50A10
static class Symbol _s; // size: 0x4, address: 0x80A50A18
static class Symbol _s; // size: 0x4, address: 0x80A50A20
// Range: 0x8031ECE8 -> 0x8031EFF8
unsigned char PropSync(struct Bone & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class CharBones * gPropBones;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A50A28
// Range: 0x8031EFF8 -> 0x8031F0C0
unsigned char CharBonesObject::SyncProperty(class CharBonesObject * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class CharBones * gPropBones;
}

// Range: 0x8031F0C0 -> 0x8031F2C0
unsigned char PropSync(class vector & v /* r30 */, class DataNode & n /* r31 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r28 */) {
    // Local variables
    struct Bone * it; // r29
    struct Bone tmp; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x7C
} __vt__14CharBonesAlloc; // size: 0x7C, address: 0x808D0610
struct {
    // total size: 0x7C
} __vt__15CharBonesObject; // size: 0x7C, address: 0x808D06C8
struct {
    // total size: 0x1C
} __vt__9CharBones; // size: 0x1C, address: 0x808D0780
struct {
    // total size: 0x8
} __RTTI__PQ29CharBones4Bone; // size: 0x8, address: 0x808D07F8

