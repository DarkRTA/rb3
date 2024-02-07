/*
    Compile unit: C:\rockband2\system\src\char\CharacterTest.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80391F9C -> 0x803938B8
*/
unsigned char sEnablePose; // size: 0x1, address: 0x80A46E50
static float kOutfitCycleWait; // size: 0x4, address: 0x80A56EA0
static class Symbol none; // size: 0x4, address: 0x80A51404
class Array2d {
    // total size: 0xC
protected:
    int mWidth; // offset 0x0, size 0x4
    int mHeight; // offset 0x4, size 0x4
    float * mData; // offset 0x8, size 0x4
};
struct Node {
    // total size: 0xC
    float a; // offset 0x0, size 0x4
    float b; // offset 0x4, size 0x4
    float err; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Node * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Node * _M_start; // offset 0x0, size 0x4
    struct Node * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ClipDistMap {
    // total size: 0x50
protected:
    class CharClip * mClipA; // offset 0x0, size 0x4
    class CharClip * mClipB; // offset 0x4, size 0x4
    class CharClipSet * mClips; // offset 0x8, size 0x4
    const class DataArray * mWeightData; // offset 0xC, size 0x4
    float mAStart; // offset 0x10, size 0x4
    float mAEnd; // offset 0x14, size 0x4
    float mBStart; // offset 0x18, size 0x4
    float mBEnd; // offset 0x1C, size 0x4
    float mDFrame; // offset 0x20, size 0x4
    float mWorstErr; // offset 0x24, size 0x4
    float mLastMinErr; // offset 0x28, size 0x4
    float mBeatAlign; // offset 0x2C, size 0x4
    int mBeatAlignOffset; // offset 0x30, size 0x4
    int mBeatAlignPeriod; // offset 0x34, size 0x4
    class Array2d mDists; // offset 0x38, size 0xC
    class vector mNodes; // offset 0x44, size 0xC
};
// Range: 0x80391F9C -> 0x803921D8
void * CharacterTest::CharacterTest(class CharacterTest * const this /* r31 */) {
    // References
    // -> static class Symbol none;
    // -> static float kOutfitCycleWait;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__32ObjPtrList<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13CharClipGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10CharDriver,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharacterTest;
}

struct Node {
    // total size: 0xC
    class Waypoint * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x803921D8 -> 0x8039254C
void * CharacterTest::~CharacterTest(class CharacterTest * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10CharDriver,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13CharClipGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Waypoint,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__32ObjPtrList<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __vt__13CharacterTest;
}

// Range: 0x8039254C -> 0x80392568
class CharClipSet * CharacterTest::Clips() {}

// Range: 0x80392568 -> 0x80392BB4
void CharacterTest::GrabLoadPose(class CharacterTest * const this /* r27 */) {
    // Local variables
    class ObjDirItr bone; // r1+0x30

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> unsigned char sEnablePose;
}

// Range: 0x80392BB4 -> 0x80392C88
void CharacterTest::GrabLoadPose() {
    // Local variables
    int i; // r7
}

static int gRev; // size: 0x4, address: 0x80A51408
// Range: 0x80392C88 -> 0x80392E3C
void CharacterTest::Save(class CharacterTest * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80392E3C -> 0x80392F18
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtrList & c /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80392F18 -> 0x80392FB0
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80392FB0 -> 0x803935E8
void CharacterTest::Load(class CharacterTest * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class ObjPtr tmp; // r1+0x14
    char buffer[256]; // r1+0x120

    // References
    // -> static float kOutfitCycleWait;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> static int gRev;
}

static class Symbol _s; // size: 0x4, address: 0x80A51410
// Range: 0x803935E8 -> 0x803938B8
class DataNode CharacterTest::Handle(class CharacterTest * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__13CharacterTest;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x14
} __vt__13CharacterTest; // size: 0x14, address: 0x808DBF08
struct {
    // total size: 0x8
} __RTTI__13CharacterTest; // size: 0x8, address: 0x808DBF38
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8Waypoint,9ObjectDir>; // size: 0x18, address: 0x808DBF40
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8Waypoint,9ObjectDir>; // size: 0x8, address: 0x808DBF88
struct {
    // total size: 0x18
} __vt__34ObjPtr<13CharClipGroup,9ObjectDir>; // size: 0x18, address: 0x808DBF90
struct {
    // total size: 0x8
} __RTTI__34ObjPtr<13CharClipGroup,9ObjectDir>; // size: 0x8, address: 0x808DBFD8
struct {
    // total size: 0x18
} __vt__31ObjPtr<10CharDriver,9ObjectDir>; // size: 0x18, address: 0x808DBFE0
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10CharDriver,9ObjectDir>; // size: 0x8, address: 0x808DC028
struct {
    // total size: 0x8
} __RTTI__PQ213CharacterTest7BoneXfm; // size: 0x8, address: 0x808DC050

