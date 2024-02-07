/*
    Compile unit: C:\rockband2\system\src\char\CharClipUtl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803427CC -> 0x803453F8
*/
class CharClipUtl {
    // total size: 0x1
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndTransAnim * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803427CC -> 0x80342BD0
void CharClipUtl::SetCharClipSamples(class CharClipSamples * clip /* r28 */, int numSamples /* r29 */, float startFrame /* f29 */, float endFrame /* f30 */) {
    // Local variables
    class CharClipSet * clips; // r31
    int i; // r30
    float frame; // f31
    class ObjDirItr ta; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Transform * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Transform * _M_start; // offset 0x0, size 0x4
    class Transform * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class CharUtlBoneSaver {
    // total size: 0x10
protected:
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class vector mXfms; // offset 0x4, size 0xC
};
// Range: 0x80342BD0 -> 0x8034309C
void CharClipUtl::Recenter(class CharClipSamples * clip /* r27 */) {
    // Local variables
    class CharClipSet * clips; // r30
    class CharUtlBoneSaver boneSaver; // r1+0x60
    class CharBonesSamples & full; // r29
    class vector offsets; // r1+0x50
    class iterator target; // r1+0x3C
    int i; // r28
    class Symbol channel; // r1+0x38
    class CharBonesMeshes bones; // r1+0x90
    class Vector3 center[2]; // r1+0x70
    int i; // r25
    int i; // r5
    float frac; // f0
    class Vector3 tmp; // r1+0x40
    int j; // r6

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x8034309C -> 0x803437FC
float CharClipUtl::GetCenterAndFacing(class ObjectDir * dir /* r25 */, class Vector3 & pos /* r30 */) {
    // Local variables
    float facing; // f31
    class RndTransformable * pelvis; // r31
    class RndTransformable * ltoe; // r28
    class RndTransformable * rtoe; // r27
    class RndTransformable * lankle; // r26
    class RndTransformable * rankle; // r27
    class Vector3 tmp; // r1+0x40
    class Vector3 tmp2; // r1+0x30
    class Vector3 tmp; // r1+0x20
    class Vector3 tmp2; // r1+0x10
    float pelvisWeight; // f0
    float pelvisFacing; // f4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803437FC -> 0x80343954
void CharClipUtl::GetCenter(class CharClipSet * clips /* r29 */, class Vector3 & center /* r30 */) {
    // Local variables
    class iterator bone; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80343954 -> 0x8034399C
void CharClipUtl::SetKeyFrame(class CharClipSamples * clip /* r30 */, int sample /* r31 */) {
    // Local variables
    class CharClipSet * clips; // r0
}

// Range: 0x8034399C -> 0x80343A38
static void OneRemove() {
    // Local variables
    struct Bone * it; // r6
}

class ClipCompressor {
    // total size: 0xD0
protected:
    class CharClipSet * mClips; // offset 0x0, size 0x4
    float mTolerance; // offset 0x4, size 0x4
    class vector mEnds; // offset 0x8, size 0xC
    class CharBonesMeshes mBones; // offset 0x14, size 0x98
    class CharClipSamples * mClip; // offset 0xAC, size 0x4
    class vector mSamples; // offset 0xB0, size 0xC
    class vector mFrames; // offset 0xBC, size 0xC
    int mSaved; // offset 0xC8, size 0x4
    int mTotal; // offset 0xCC, size 0x4
};
// Range: 0x80343A38 -> 0x80343C78
void CharClipUtl::KeyframeCompressClip(class CharClipSamples * c /* r31 */) {
    // Local variables
    class CharClipSet * clips; // r28
    class ClipCompressor cc; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct BoneDesc {
    // total size: 0x40
    class RndTransformable * bone; // offset 0x0, size 0x4
    class Vector3 offset; // offset 0x10, size 0x10
    float weight; // offset 0x20, size 0x4
protected:
    class Vector3 pos; // offset 0x30, size 0x10
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BoneDesc * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BoneDesc * _M_start; // offset 0x0, size 0x4
    struct BoneDesc * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80343C78 -> 0x8034455C
void CharClipUtl::CompressClip(class CharClipSamples * c /* r25 */, enum CompressionType comp /* r26 */) {
    // Local variables
    class CharBonesSamples & set; // r30
    class vector oneBones; // r1+0xD0
    char * start; // r0
    int i; // r27
    class Symbol bone; // r1+0x68
    int sample; // r29
    int offset; // r28
    const struct Bone * bone; // r27
    class Vector3 * p; // r24
    const class Vector3 * first; // r3
    class Vector3 tmp; // r1+0xC0
    class Quat * q; // r23
    class Matrix3 m; // r1+0x110
    class Matrix3 cur; // r1+0xE0
    class Vector3 euler; // r1+0xB0
    float * a; // r24
    class CharBonesSamples oldFull; // r1+0x140
    class vector newFullBones; // r1+0xA0
    int i; // r5
    struct Bone * it; // r6

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ29CharBones4Bone;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8034455C -> 0x803453F8
void CharClipUtl::AnalyzeDof(class CharClipSet * clips /* r28 */) {
    // Local variables
    class CharBones bones; // r1+0x1E0
    class vector quats; // r1+0xF8
    int start; // r31
    int end; // r30
    int i; // r5
    class vector poss; // r1+0xEC
    int i; // r5
    class ObjDirItr clip; // r1+0x104
    int samples; // r0
    int i; // r30
    int j; // r29
    int j; // r29
    class String s; // r1+0xE0
    int i; // r29
    int i; // r27

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharClipSamples;
    // -> const char * gNullStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class QuatDesc * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class QuatDesc * _M_start; // offset 0x0, size 0x4
    class QuatDesc * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PosDesc * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PosDesc * _M_start; // offset 0x0, size 0x4
    class PosDesc * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class PosDesc {
    // total size: 0x40
protected:
    class Symbol channel; // offset 0x0, size 0x4
    class Vector3 firstPos; // offset 0x10, size 0x10
    class Vector3 maxDelta; // offset 0x20, size 0x10
    unsigned char posType; // offset 0x30, size 0x1
};
class QuatDesc {
    // total size: 0x50
protected:
    class Symbol channel; // offset 0x0, size 0x4
    class Vector3 maxAxis; // offset 0x10, size 0x10
    class Vector3 maxDelta; // offset 0x20, size 0x10
    class Quat firstQuat; // offset 0x30, size 0x10
    enum Type rotType; // offset 0x40, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__P7PosDesc; // size: 0x8, address: 0x808D3EB0
struct {
    // total size: 0x8
} __RTTI__P8QuatDesc; // size: 0x8, address: 0x808D3EC8

