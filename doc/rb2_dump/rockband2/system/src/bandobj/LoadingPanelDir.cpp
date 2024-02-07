/*
    Compile unit: C:\rockband2\system\src\bandobj\LoadingPanelDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8028AA78 -> 0x8028C4D0
*/
class DataArray * types; // size: 0x4, address: 0x80A4F8E0
// Range: 0x8028AA78 -> 0x8028AB20
void LoadingPanelDir::PreLoad(class LoadingPanelDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
}

// Range: 0x8028AB20 -> 0x8028AC6C
void LoadingPanelDir::PostLoad(class LoadingPanelDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class FilePath sNull;
    // -> class FilePath sRoot;
    // -> class list sRevs;
}

// Range: 0x8028AC6C -> 0x8028B2CC
void LoadingPanelDir::Copy(class LoadingPanelDir * const this /* r30 */, const class Object * o /* r24 */) {
    // Local variables
    const class LoadingPanelDir * p; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15LoadingPanelDir;
}

// Range: 0x8028B2CC -> 0x8028B300
void LoadingPanelDir::Exit(class LoadingPanelDir * const this /* r31 */) {}

// Range: 0x8028B300 -> 0x8028B838
void LoadingPanelDir::SetPoses(class LoadingPanelDir * const this /* r29 */) {
    // Local variables
    class CompositeCharacter * vocalist; // r27
    class CompositeCharacter * guitarist; // r26
    class CompositeCharacter * bassist; // r25
    class CompositeCharacter * drummer; // r24
    class String t1; // r1+0x74
    class CompositeCharacter * h2h0; // r31
    class String t2; // r1+0x68
    class CompositeCharacter * h2h1; // r30
    class ObjDirItr cc; // r1+0x80

    // References
    // -> class LoadMgr TheLoadMgr;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndTransformable * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class CharBonesSamples : public CharBones {
    // total size: 0x6C
protected:
    int mNumSamples; // offset 0x54, size 0x4
    int mPreviewSample; // offset 0x58, size 0x4
    char * mRawData; // offset 0x5C, size 0x4
    class vector mFrames; // offset 0x60, size 0xC
};
struct FacingBones : public CharBones {
    // total size: 0x80
    class Vector3 mDeltaPos; // offset 0x60, size 0x10
    float mDeltaAng; // offset 0x70, size 0x4
};
struct FacingSet {
    // total size: 0x10
    int mFullRot; // offset 0x0, size 0x4
    int mFullPos; // offset 0x4, size 0x4
    struct FacingBones * mFacingBones; // offset 0x8, size 0x4
    float mWeight; // offset 0xC, size 0x4
};
class CharClipSamples : public CharClip {
    // total size: 0x164
protected:
    class CharBonesSamples mFull; // offset 0x50, size 0x6C
    class CharBonesSamples mOne; // offset 0xBC, size 0x6C
    struct FacingSet mFacing; // offset 0x128, size 0x10
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndDrawable * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8028B838 -> 0x8028BA88
class CharClip * LoadingPanelDir::GetEditClip(class LoadingPanelDir * const this /* r31 */) {
    // Local variables
    class String h2h0; // r1+0x2C
    class String h2h1; // r1+0x20
}

static class Symbol _s; // size: 0x4, address: 0x80A4F8E8
static class Symbol _s; // size: 0x4, address: 0x80A4F8F0
static class Symbol _s; // size: 0x4, address: 0x80A4F8F8
// Range: 0x8028BA88 -> 0x8028C0D4
class DataNode LoadingPanelDir::Handle(class LoadingPanelDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
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

static class Symbol _s; // size: 0x4, address: 0x80A4F900
static class Symbol _s; // size: 0x4, address: 0x80A4F908
static class Symbol _s; // size: 0x4, address: 0x80A4F910
static class Symbol _s; // size: 0x4, address: 0x80A4F918
// Range: 0x8028C0D4 -> 0x8028C374
unsigned char LoadingPanelDir::SyncProperty(class LoadingPanelDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8028C374 -> 0x8028C4D0
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__15CharClipSamples; // size: 0x8, address: 0x808BD5F0
struct {
    // total size: 0x234
} __vt__15LoadingPanelDir; // size: 0x234, address: 0x808BD5F8
struct {
    // total size: 0x8
} __RTTI__15LoadingPanelDir; // size: 0x8, address: 0x808BD8A8
struct {
    // total size: 0x18
} __vt__32ObjPtr<11CharClipSet,9ObjectDir>; // size: 0x18, address: 0x808BD8F8
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11CharClipSet,9ObjectDir>; // size: 0x8, address: 0x808BD940
struct {
    // total size: 0x18
} __vt__28ObjPtr<8CharClip,9ObjectDir>; // size: 0x18, address: 0x808BDB70
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8CharClip,9ObjectDir>; // size: 0x8, address: 0x808BDBB0

