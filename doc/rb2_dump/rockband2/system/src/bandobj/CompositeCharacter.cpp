/*
    Compile unit: C:\rockband2\system\src\bandobj\CompositeCharacter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8026AB54 -> 0x802762FC
*/
class DataArray * types; // size: 0x4, address: 0x80A4F430
class Symbol name; // size: 0x4, address: 0x80A4F438
class Symbol name; // size: 0x4, address: 0x80A4F440
enum WalkState {
    kStateNone = 0,
    kStateGoing = 1,
    kStateStopping = 2,
};
struct WalkClip {
    // total size: 0xC
    class CharClip * clip; // offset 0x0, size 0x4
    float frame; // offset 0x4, size 0x4
    float prevFrame; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct WalkClip * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct WalkClip * _M_start; // offset 0x0, size 0x4
    struct WalkClip * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct PlanPoint {
    // total size: 0xC
    int node; // offset 0x0, size 0x4
    float frame; // offset 0x4, size 0x4
    float dist; // offset 0x8, size 0x4
};
class ClipPredict {
    // total size: 0x50
protected:
    class CharClipSamples * mClip; // offset 0x0, size 0x4
    void * mAngChannel; // offset 0x4, size 0x4
    void * mPosChannel; // offset 0x8, size 0x4
    class Vector3 mPos; // offset 0x10, size 0x10
    float mAng; // offset 0x20, size 0x4
    class Vector3 mLastPos; // offset 0x30, size 0x10
    float mLastAng; // offset 0x40, size 0x4
};
class CharWalk : public CharPollable {
    // total size: 0xCB0
protected:
    float mPathRadius; // offset 0x8, size 0x4
    class vector mWaypoints; // offset 0xC, size 0xC
    class Waypoint * mFinalWay; // offset 0x18, size 0x4
    float mDestFacing; // offset 0x1C, size 0x4
    float mStopRadius; // offset 0x20, size 0x4
    class Vector3 mDestPos; // offset 0x30, size 0x10
    class Vector3 mUnitDir; // offset 0x40, size 0x10
    enum WalkState mState; // offset 0x50, size 0x4
    int mCurNode; // offset 0x54, size 0x4
    int mCurWaypoint; // offset 0x58, size 0x4
    class vector mClips; // offset 0x5C, size 0xC
    int mCurPoint; // offset 0x68, size 0x4
    int mLastPoint; // offset 0x6C, size 0x4
    struct PlanPoint mPoints[256]; // offset 0x70, size 0xC00
    float mOffsetSpeed; // offset 0xC70, size 0x4
    float mBr; // offset 0xC74, size 0x4
    class Character * mMe; // offset 0xC78, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Waypoint * mPtr; // offset 0x8, size 0x4
};
class CharServoBone : public CharPollable, public CharBonesMeshes {
    // total size: 0x100
protected:
    class RndTransformable * mPelvis; // offset 0x74, size 0x4
    float * mFacingRotDelta; // offset 0x78, size 0x4
    class Vector3 * mFacingPosDelta; // offset 0x7C, size 0x4
    float * mFacingRot; // offset 0x80, size 0x4
    class Vector3 * mFacingPos; // offset 0x84, size 0x4
    unsigned char mMoveSelf; // offset 0x88, size 0x1
    unsigned char mDeltaChanged; // offset 0x89, size 0x1
    class Character * mMe; // offset 0x8C, size 0x4
    class ObjPtr mWay; // offset 0x90, size 0xC
    class ObjPtr mOverrideClip; // offset 0x9C, size 0xC
    float mOverrideFrame; // offset 0xA8, size 0x4
    class ObjPtr mOverrideWay; // offset 0xAC, size 0xC
    class Vector3 mOverridePos; // offset 0xC0, size 0x10
};
struct Node {
    // total size: 0xC
    class CharHair * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
struct Node {
    // total size: 0xC
    class RndMesh * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x8026AB54 -> 0x8026B23C
void * CompositeCharacter::~CompositeCharacter(class CompositeCharacter * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__39ObjPtr<18CompositeCharacter,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12ColorPalette,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8CharHair,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__18CompositeCharacter;
}

// Range: 0x8026B23C -> 0x8026B2D0
void CompositeCharacter::RemovingObject(class CompositeCharacter * const this /* r30 */, class Object * obj /* r31 */) {}

static class Symbol clip_flags; // size: 0x4, address: 0x80A4F448
// Range: 0x8026B2D0 -> 0x8026B5A0
void CompositeCharacter::Enter(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    class Message msg; // r1+0x20
    class DataNode n; // r1+0x18
    class CharClip * his; // r4

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol clip_flags;
}

// Range: 0x8026B5A0 -> 0x8026B5DC
void CompositeCharacter::Exit(class CompositeCharacter * const this /* r31 */) {}

static class DebugWarner _dw; // size: 0x100, address: 0x8097CE78
static class DebugWarner _dw; // size: 0x100, address: 0x8097CF78
// Range: 0x8026B5DC -> 0x8026B890
class CharClipDriver * CompositeCharacter::PlayMainClip(class CompositeCharacter * const this /* r30 */, int pf /* r31 */) {
    // Local variables
    int flags; // r26
    class CharClip * clip; // r28
    class DataNode & warn; // r0
    class CharClipDriver * cd; // r26

    // References
    // -> static class DebugWarner _dw;
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x8026B890 -> 0x8026B948
void CompositeCharacter::MakeMRU(class CompositeCharacter * who /* r30 */, class CharClip * clip /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Timer * _t; // size: 0x4, address: 0x80A4F44C
static class Symbol drum; // size: 0x4, address: 0x80A4F454
static class Symbol symBoneHiHat; // size: 0x4, address: 0x80A4F45C
// Range: 0x8026B948 -> 0x8026BBD0
void CompositeCharacter::Poll(class CompositeCharacter * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x20
    class CharClip * c; // r0
    class Vector3 * pos; // r0

    // References
    // -> static class Symbol symBoneHiHat;
    // -> const char * gNullStr;
    // -> static class Symbol drum;
    // -> static class Timer * _t;
}

static char buffer[256]; // size: 0x100, address: 0x8097D078
struct FlagPair {
    // total size: 0x8
    int flag; // offset 0x0, size 0x4
    const char * name; // offset 0x4, size 0x4
};
static struct FlagPair pairs[19]; // size: 0x98, address: 0x808B8C30
// Range: 0x8026BBD0 -> 0x8026BCB8
char * CompositeCharacter::FlagString(int flags /* r29 */) {
    // Local variables
    int i; // r31

    // References
    // -> static struct FlagPair pairs[19];
    // -> static char buffer[256];
}

// Range: 0x8026BCB8 -> 0x8026BD04
void CompositeCharacter::SetH2hLocation() {}

// Range: 0x8026BD04 -> 0x8026BD24
void CompositeCharacter::SetH2h() {}

// Range: 0x8026BD24 -> 0x8026BE4C
void CompositeCharacter::PlayFaceClip(class CompositeCharacter * const this /* r28 */, unsigned char first /* r29 */) {
    // Local variables
    int flags; // r30
    class CharClip * c; // r4

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x8026BE4C -> 0x8026BE68
static char * SafeName() {}

static class DataNode & guitarist_debug; // size: 0x4, address: 0x80A4F464
// Range: 0x8026BE68 -> 0x8026C0AC
void CompositeCharacter::UpdateOverlay(class CompositeCharacter * const this /* r30 */) {
    // Local variables
    class CharClipDriver * d; // r0

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class DataNode & guitarist_debug;
}

static class Message msg; // size: 0x8, address: 0x8097D188
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndMat * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndTexRenderer * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharHair * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8026C0AC -> 0x8026D2C8
void CompositeCharacter::SyncObjects(class CompositeCharacter * const this /* r29 */) {
    // Local variables
    class ObjDirItr m; // r1+0xA8
    class ObjDirItr m; // r1+0x94
    class ObjDirItr hair; // r1+0x80

    // References
    // -> struct [anonymous] __RTTI__8CharHair;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> struct [anonymous] __RTTI__13RndScreenMask;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x8026D2C8 -> 0x8026D59C
void CompositeCharacter::FixSocks(class CompositeCharacter * const this /* r26 */) {
    // Local variables
    class Object * feet; // r30
    class Object * footSkin; // r29
    class Object * legs; // r28
    class Object * lskin; // r27
    class Object * sockMat; // r0
    class Object * lskin; // r22
    class RndMat * footMat; // r0

    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

static int gRev; // size: 0x4, address: 0x80A4F46C
// Range: 0x8026D59C -> 0x8026D700
void CompositeCharacter::Save(class CompositeCharacter * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8026D700 -> 0x8026D790
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8026D790 -> 0x8026D878
void CompositeCharacter::PreLoad(class CompositeCharacter * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int hashSize; // r31

    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

static class Symbol weight; // size: 0x4, address: 0x80A4F474
static class Symbol height; // size: 0x4, address: 0x80A4F47C
// Range: 0x8026D878 -> 0x8026E210
void CompositeCharacter::PostLoad(class CompositeCharacter * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    const class DataNode * node; // r0
    int mode; // r1+0x34
    int tempMode; // r1+0x30
    int attitude; // r1+0x2C
    class Symbol prefabName; // r1+0x28
    float h; // r1+0x24
    float w; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ColorPalette;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> static class Symbol height;
    // -> static class Symbol weight;
    // -> static int gRev;
}

// Range: 0x8026E210 -> 0x8026E3AC
void CompositeCharacter::Copy(class CompositeCharacter * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CompositeCharacter * cc; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x8026E3AC -> 0x8026F550
class DataArray * CompositeCharacter::MakeConfig(class CompositeCharacter * const this /* r24 */) {
    // Local variables
    class DataArrayPtr gender; // r1+0x1B0
    class DataArrayPtr instrument; // r1+0x1A8
    class DataArrayPtr attitude; // r1+0x1A0
    class DataArrayPtr weight; // r1+0x198
    class DataArrayPtr height; // r1+0x190
    class DataArrayPtr skin; // r1+0x188
    class DataArrayPtr eye; // r1+0x180
    class DataArrayPtr eyebrow; // r1+0x178
    class ObjDirItr ol; // r1+0x1B8
    class vector & cats; // r0
    class DataArray * outs; // r26
    struct Category * c; // r25
    class Symbol selected; // r1+0x84
    const char * base_name; // r0
    class DataArray * cfg; // r23

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__12OutfitConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x8026F550 -> 0x8026F5D0
class DataNode CompositeCharacter::WriteConfig() {
    // Local variables
    class DataArray * data; // r31
}

// Range: 0x8026F5D0 -> 0x8026F7FC
class DataNode CompositeCharacter::ListPrefabs(class CompositeCharacter * const this /* r27 */) {
    // Local variables
    class DataArray * arr; // r30
    class DataArrayPtr a; // r1+0x38
    int currentItem; // r29
    int i; // r28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x8026F7FC -> 0x8026F970
class DataNode CompositeCharacter::OnLoadPrefab(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    class DataArray * arr; // r4

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> const char * gNullStr;
}

// Range: 0x8026F970 -> 0x8026FA10
void CompositeCharacter::LoadPrefabArray(class CompositeCharacter * const this /* r30 */, class DataArray * prefabArr /* r31 */) {}

// Range: 0x8026FA10 -> 0x8026FA20
float CompositeCharacter::DeformFrame() {}

// Range: 0x8026FA20 -> 0x8026FA8C
class OutfitConfig * CompositeCharacter::FindOutfitConfig(class CompositeCharacter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitConfig;
}

// Range: 0x8026FA8C -> 0x8026FB44
void CompositeCharacter::SetOutfitColor(class CompositeCharacter * const this /* r28 */, class Symbol & category /* r29 */, int option_index /* r30 */, int color_index /* r31 */) {
    // Local variables
    class OutfitConfig * oc; // r0
}

static class Symbol skin_proxy; // size: 0x4, address: 0x80A4F484
static class Symbol color; // size: 0x4, address: 0x80A4F48C
static class Symbol tattoo_overlay_color; // size: 0x4, address: 0x80A4F494
// Range: 0x8026FB44 -> 0x8027002C
void CompositeCharacter::SetSkinColor(class CompositeCharacter * const this /* r28 */, int idx /* r26 */, unsigned char redoTexRenders /* r29 */) {
    // Local variables
    class Color col; // r1+0x60
    class RndMat * * m; // r4
    class RndTexRenderer * * s; // r29
    class Message msg; // r1+0x50

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> static class Symbol tattoo_overlay_color;
    // -> static class Symbol color;
    // -> const char * gNullStr;
    // -> static class Symbol skin_proxy;
}

// Range: 0x8027002C -> 0x80270118
void CompositeCharacter::SetEyeColor(class CompositeCharacter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x80270118 -> 0x80270260
void CompositeCharacter::SetEyebrowColor(class CompositeCharacter * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__12ColorPalette;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x80270260 -> 0x802703C4
void CompositeCharacter::SetTattooPrefab(class CompositeCharacter * const this /* r28 */) {
    // Local variables
    class FilePath tattoo_path; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> struct [anonymous] __vt__8FilePath;
}

static class DataNode & d; // size: 0x4, address: 0x80A4F49C
// Range: 0x802703C4 -> 0x80270524
void CompositeCharacter::DrawShowing(class CompositeCharacter * const this /* r30 */) {
    // Local variables
    int i; // r31
    class Vector3 p; // r1+0x40
    class Vector3 p2; // r1+0x30

    // References
    // -> class Rnd & TheRnd;
    // -> static class DataNode & d;
}

// Range: 0x80270524 -> 0x802708DC
void CompositeCharacter::Mats(class list & mats /* r31 */) {
    // Local variables
    class ObjDirItr m; // r1+0x20
    struct MatShaderOptions opts; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>; // size: 0x8, address: 0x808B9178
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<P6RndTex>; // size: 0x8, address: 0x808B91B8
static class DataArray * req; // size: 0x4, address: 0x80A4F4A0
// Range: 0x802708DC -> 0x80270A94
unsigned char CompositeCharacter::AddDircut(class CompositeCharacter * const this /* r30 */, const char * group /* r31 */) {
    // Local variables
    int i; // r28
    int i; // r28

    // References
    // -> static class DataArray * req;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80270A94 -> 0x80270C24
char * CompositeCharacter::DircutFile(class CompositeCharacter * const this /* r28 */) {
    // Local variables
    int index; // r29

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x80270C24 -> 0x8027113C
void CompositeCharacter::UncompressTextures(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    class ObjDirItr l; // r1+0x34
    class ObjDirItr m; // r1+0x20

    // References
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

// Range: 0x8027113C -> 0x802711D8
void CompositeCharacter::SetAttitude(class CompositeCharacter * const this /* r29 */, int flags /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802711D8 -> 0x802711E4
int CompositeCharacter::GetAttitude() {}

// Range: 0x802711E4 -> 0x80271200
void CompositeCharacter::SetHeight() {}

// Range: 0x80271200 -> 0x8027121C
void CompositeCharacter::SetWeight() {}

// Range: 0x8027121C -> 0x8027146C
void CompositeCharacter::LoadClips(class CompositeCharacter * const this /* r26 */, unsigned char async /* r27 */) {
    // References
    // -> struct [anonymous] __RTTI__10CharDriver;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

static class Symbol tempo; // size: 0x4, address: 0x80A4F4A8
static class Symbol realtime; // size: 0x4, address: 0x80A4F4B0
static class Symbol finale; // size: 0x4, address: 0x80A4F4B8
static class Symbol shell; // size: 0x4, address: 0x80A4F4C0
static class Symbol tempo_only; // size: 0x4, address: 0x80A4F4C8
static class Symbol none; // size: 0x4, address: 0x80A4F4D0
// Range: 0x8027146C -> 0x80271838
void CompositeCharacter::SyncClipLoader(class CompositeCharacter * const this /* r29 */, class OutfitLoader * l /* r30 */) {
    // Local variables
    unsigned char add; // r0
    unsigned char drum_hand; // r0
    class Symbol as; // r1+0x54
    int i; // r4

    // References
    // -> static class Symbol none;
    // -> static class Symbol tempo_only;
    // -> static class Symbol shell;
    // -> static class Symbol finale;
    // -> static class Symbol realtime;
    // -> static class Symbol tempo;
}

// Range: 0x80271838 -> 0x80271928
unsigned char CompositeCharacter::ClipsLoading() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

// Range: 0x80271928 -> 0x802719A0
void CompositeCharacter::SetTempo(class CompositeCharacter * const this /* r30 */, int flags /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802719A0 -> 0x802719AC
int CompositeCharacter::GetTempo() {}

// Range: 0x802719AC -> 0x80271A44
void CompositeCharacter::SetGuitarFlags(class CompositeCharacter * const this /* r30 */, int flags /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80271A44 -> 0x80271A6C
unsigned char CompositeCharacter::HasAddDriver() {}

// Range: 0x80271A6C -> 0x80271AA8
void CompositeCharacter::SetAbsRegulate() {}

// Range: 0x80271AA8 -> 0x80271C60
void CompositeCharacter::ChangeGroup(class CompositeCharacter * const this /* r28 */, float offset /* f31 */, enum TaskUnits units /* r30 */, class Symbol & ev /* r31 */) {
    // Local variables
    class CharClipDriver * d; // r0
    class CharClip * c; // r0
    int i; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

static class DataNode & composite_character_demand_load; // size: 0x4, address: 0x80A4F4D8
static class Symbol dircut; // size: 0x4, address: 0x80A4F4E0
// Range: 0x80271C60 -> 0x8027209C
class CharClipDriver * CompositeCharacter::SetState(class CompositeCharacter * const this /* r24 */, const char * groupName /* r21 */, int playFlags /* r25 */, int flags /* r26 */, unsigned char force /* r27 */) {
    // Local variables
    class CharDriver * oldDriver; // r21
    class CharClip * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol dircut;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
    // -> class LoadMgr TheLoadMgr;
    // -> static class DataNode & composite_character_demand_load;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

static class Symbol none; // size: 0x4, address: 0x80A4F4E8
static int sCount; // size: 0x4, address: 0x80A4F4EC
// Range: 0x8027209C -> 0x802723E8
class Symbol CompositeCharacter::ValidInstrument(class CompositeCharacter * const this /* r26 */, class Symbol & category /* r29 */) {
    // Local variables
    class ObjDirItr ol; // r1+0x24
    struct Category * cat; // r0
    int num; // r27
    int i; // r26

    // References
    // -> const char * gNullStr;
    // -> static int sCount;
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
    // -> static class Symbol none;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjOwnerPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjOwnerPtr * _M_start; // offset 0x0, size 0x4
    class ObjOwnerPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CharBonesMeshes : public CharBonesAlloc {
    // total size: 0x98
protected:
    class ObjVector mMeshes; // offset 0x58, size 0x10
    class RndTransformable * mDummyMesh; // offset 0x68, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class Object * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharIKScale * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802723E8 -> 0x8027316C
void CompositeCharacter::Deform(class CompositeCharacter * const this /* r27 */) {
    // Local variables
    class CharBonesMeshes bones; // r1+0x128
    class iterator it; // r1+0x98
    class Symbol ikScale; // r1+0x94
    class Symbol ikHand; // r1+0x90
    class Symbol foretwist; // r1+0x8C
    class Symbol collide; // r1+0x88
    class list ikScales; // r1+0xF8
    class list ikHands; // r1+0xF0
    class list foretwists; // r1+0xE8
    class list collides; // r1+0xE0
    class ObjDirItr o; // r1+0x114
    struct _List_iterator it; // r1+0x84
    class ObjDirItr s; // r1+0x100
    int i; // r26
    struct _List_iterator it; // r1+0x80
    struct _List_iterator it; // r1+0x7C
    struct _List_iterator it; // r1+0x78
    struct _List_iterator it; // r1+0x74

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11CharCollide>;
    // -> struct [anonymous] __RTTI__11CharCollide;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13CharForeTwist>;
    // -> struct [anonymous] __RTTI__13CharForeTwist;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std25_List_node<P10CharIKHand>;
    // -> struct [anonymous] __RTTI__10CharIKHand;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11CharIKScale>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__11CharIKScale;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjOwnerPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjOwnerPtr * _M_start; // offset 0x0, size 0x4
    class ObjOwnerPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class Waypoint : public RndDrawable, public RndTransformable {
    // total size: 0x160
    int mFlags; // offset 0xF8, size 0x4
    float mRadius; // offset 0xFC, size 0x4
    float mYRadius; // offset 0x100, size 0x4
    float mAngRadius; // offset 0x104, size 0x4
    int mSearchID; // offset 0x108, size 0x4
    float mAbsAngDelta; // offset 0x10C, size 0x4
    float mAbsRadiusDelta; // offset 0x110, size 0x4
    class ObjVector mConnections; // offset 0x114, size 0x10
};
class CharIKScale : public CharWeightable, public CharPollable {
    // total size: 0x7C
protected:
    class ObjPtr mDest; // offset 0x20, size 0xC
    float mScale; // offset 0x2C, size 0x4
    class ObjPtrList mSecondaryTargets; // offset 0x30, size 0x14
    float mBottomHeight; // offset 0x44, size 0x4
    float mTopHeight; // offset 0x48, size 0x4
    unsigned char mAutoWeight; // offset 0x4C, size 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharIKScale * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class CharIKHand : public RndHighlightable, public CharWeightable, public CharPollable {
    // total size: 0xB0
protected:
    class ObjPtr mHand; // offset 0x28, size 0xC
    class ObjPtr mFinger; // offset 0x34, size 0xC
    class ObjPtrList mTargets; // offset 0x40, size 0x14
    unsigned char mOrientation; // offset 0x54, size 0x1
    unsigned char mStretch; // offset 0x55, size 0x1
    unsigned char mScalable; // offset 0x56, size 0x1
    unsigned char mMoveElbow; // offset 0x57, size 0x1
    float mElbowSwing; // offset 0x58, size 0x4
    unsigned char mAlwaysIK; // offset 0x5C, size 0x1
    unsigned char mHandChanged; // offset 0x5D, size 0x1
    class Vector3 mWorldDst; // offset 0x60, size 0x10
    float mInv2ab; // offset 0x70, size 0x4
    float mAAPlusBB; // offset 0x74, size 0x4
    unsigned char mConstrainWrist; // offset 0x78, size 0x1
    float mWristRadians; // offset 0x7C, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharIKHand * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class CharForeTwist : public CharPollable {
    // total size: 0x54
protected:
    class ObjPtr mHand; // offset 0x8, size 0xC
    class ObjPtr mTwist2; // offset 0x14, size 0xC
    float mOffset; // offset 0x20, size 0x4
    float mLengthScale; // offset 0x24, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharForeTwist * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CharCollide * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11CharIKScale>; // size: 0x8, address: 0x808B9410
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std25_List_node<P10CharIKHand>; // size: 0x8, address: 0x808B9440
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<P13CharForeTwist>; // size: 0x8, address: 0x808B9478
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11CharCollide>; // size: 0x8, address: 0x808B94B0
struct BoneDesc {
    // total size: 0x90
    class ObjPtr bone; // offset 0x0, size 0xC
    class Transform offset; // offset 0x10, size 0x40
    class Transform parent; // offset 0x50, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
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
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class SyncMeshCB {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RndMeshDeform : public Object {
    // total size: 0xA0
protected:
    float * mWeights; // offset 0x28, size 0x4
    int mNumVerts; // offset 0x2C, size 0x4
    class ObjOwnerPtr mMesh; // offset 0x30, size 0xC
    class Transform mMeshInverse; // offset 0x40, size 0x40
    class ObjVector mBones; // offset 0x80, size 0x10
    unsigned char mSkipInverse; // offset 0x90, size 0x1
    unsigned char mDeformed; // offset 0x91, size 0x1
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndMeshDeform * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndMesh * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8027316C -> 0x80273C2C
void CompositeCharacter::ClearRam(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    unsigned char char_edit_mode; // r0
    class ObjDirItr rt; // r1+0x88
    class ObjDirItr md; // r1+0x74
    class ObjDirItr m; // r1+0x60

    // References
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> struct [anonymous] __RTTI__13RndMeshDeform;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
}

// Range: 0x80273C2C -> 0x80273F7C
void CompositeCharacter::Finalize(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    unsigned char char_edit_mode; // r0
    class ObjDirItr mat; // r1+0x1C

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F4F4
static class Symbol _s; // size: 0x4, address: 0x80A4F4FC
static class Symbol _s; // size: 0x4, address: 0x80A4F504
static class Symbol _s; // size: 0x4, address: 0x80A4F50C
static class Symbol _s; // size: 0x4, address: 0x80A4F514
static class Symbol _s; // size: 0x4, address: 0x80A4F51C
static class Symbol _s; // size: 0x4, address: 0x80A4F524
static class Symbol _s; // size: 0x4, address: 0x80A4F52C
static class Symbol _s; // size: 0x4, address: 0x80A4F534
static class Symbol _s; // size: 0x4, address: 0x80A4F53C
static class Symbol _s; // size: 0x4, address: 0x80A4F544
static class Symbol _s; // size: 0x4, address: 0x80A4F54C
static class Symbol _s; // size: 0x4, address: 0x80A4F554
static class Symbol _s; // size: 0x4, address: 0x80A4F55C
static class Symbol _s; // size: 0x4, address: 0x80A4F564
static class Symbol _s; // size: 0x4, address: 0x80A4F56C
static class Symbol _s; // size: 0x4, address: 0x80A4F574
static class Symbol _s; // size: 0x4, address: 0x80A4F57C
// Range: 0x80273F7C -> 0x80274C84
unsigned char CompositeCharacter::SyncProperty(class CompositeCharacter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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

// Range: 0x80274C84 -> 0x80274DD4
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F584
static class Symbol _s; // size: 0x4, address: 0x80A4F58C
static class Symbol _s; // size: 0x4, address: 0x80A4F594
static class Symbol _s; // size: 0x4, address: 0x80A4F59C
static class Symbol _s; // size: 0x4, address: 0x80A4F5A4
static class Symbol _s; // size: 0x4, address: 0x80A4F5AC
static class Symbol _s; // size: 0x4, address: 0x80A4F5B4
static class Symbol _s; // size: 0x4, address: 0x80A4F5BC
static class Symbol _s; // size: 0x4, address: 0x80A4F5C4
static class Symbol _s; // size: 0x4, address: 0x80A4F5CC
static class Symbol _s; // size: 0x4, address: 0x80A4F5D4
static class Symbol _s; // size: 0x4, address: 0x80A4F5DC
static class Symbol _s; // size: 0x4, address: 0x80A4F5E4
static class Symbol _s; // size: 0x4, address: 0x80A4F5EC
static class Symbol _s; // size: 0x4, address: 0x80A4F5F4
static class Symbol _s; // size: 0x4, address: 0x80A4F5FC
static class Symbol _s; // size: 0x4, address: 0x80A4F604
static class Symbol _s; // size: 0x4, address: 0x80A4F60C
static class Symbol _s; // size: 0x4, address: 0x80A4F614
static class Symbol _s; // size: 0x4, address: 0x80A4F61C
static class Symbol _s; // size: 0x4, address: 0x80A4F624
static class Symbol _s; // size: 0x4, address: 0x80A4F62C
static class Symbol _s; // size: 0x4, address: 0x80A4F634
static class Symbol _s; // size: 0x4, address: 0x80A4F63C
static class Symbol _s; // size: 0x4, address: 0x80A4F644
static class Symbol _s; // size: 0x4, address: 0x80A4F64C
static class Symbol _s; // size: 0x4, address: 0x80A4F654
static class Symbol _s; // size: 0x4, address: 0x80A4F65C
static class Symbol _s; // size: 0x4, address: 0x80A4F664
static class Symbol _s; // size: 0x4, address: 0x80A4F66C
static class Symbol _s; // size: 0x4, address: 0x80A4F674
static class Symbol _s; // size: 0x4, address: 0x80A4F67C
// Range: 0x80274DD4 -> 0x80275DA4
class DataNode CompositeCharacter::Handle(class CompositeCharacter * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x1C
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80275DA4 -> 0x80275E2C
class DataNode CompositeCharacter::OnClearGroup(class CompositeCharacter * const this /* r31 */) {}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x80275E2C -> 0x80275E84
class DataNode CompositeCharacter::OnResetHair() {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x80275E84 -> 0x80275FD4
class DataNode CompositeCharacter::OnSyncWaypoint(class CompositeCharacter * const this /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x80275FD4 -> 0x8027609C
class DataNode CompositeCharacter::OnChangeFaceGroup(class CompositeCharacter * const this /* r30 */, class DataArray * msg /* r31 */) {}

// Range: 0x8027609C -> 0x8027620C
class DataNode CompositeCharacter::OnChangeGroup(class CompositeCharacter * const this /* r25 */, class DataArray * msg /* r26 */) {
    // Local variables
    unsigned char forceGroup; // r28
    unsigned char blend; // r30
    float forward; // f31
    enum TaskUnits units; // r27
    class Symbol ev; // r1+0x14

    // References
    // -> const char * gNullStr;
}

// Range: 0x8027620C -> 0x80276290
class DataNode CompositeCharacter::OnSetPlay(class CompositeCharacter * const this /* r30 */, class DataArray * msg /* r31 */) {}

// Range: 0x80276290 -> 0x802762FC
class DataNode CompositeCharacter::OnGroupOverride(class CompositeCharacter * const this /* r30 */, class DataArray * msg /* r31 */) {}

struct {
    // total size: 0x8
} __RTTI__13RndScreenMask; // size: 0x8, address: 0x808B97A0
struct {
    // total size: 0x8
} __RTTI__13CharForeTwist; // size: 0x8, address: 0x808B97E0
struct {
    // total size: 0x8
} __RTTI__13RndMeshDeform; // size: 0x8, address: 0x808B9810
struct {
    // total size: 0x8
} __RTTI__11CharIKScale; // size: 0x8, address: 0x808B9850
struct {
    // total size: 0x8
} __RTTI__8Waypoint; // size: 0x8, address: 0x808B9890
struct {
    // total size: 0x8
} __RTTI__10CharIKHand; // size: 0x8, address: 0x808B98D8
struct {
    // total size: 0x8
} __RTTI__10CharDriver; // size: 0x8, address: 0x808B9920
struct {
    // total size: 0x8
} __RTTI__14CharWeightable; // size: 0x8, address: 0x808B9950
struct {
    // total size: 0x220
} __vt__18CompositeCharacter; // size: 0x220, address: 0x808B9958
struct {
    // total size: 0x18
} __vt__31ObjPtrList<7RndMesh,9ObjectDir>; // size: 0x18, address: 0x808B9BF0
struct {
    // total size: 0x8
} __RTTI__31ObjPtrList<7RndMesh,9ObjectDir>; // size: 0x8, address: 0x808B9C38
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8CharHair,9ObjectDir>; // size: 0x18, address: 0x808B9C40
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8CharHair,9ObjectDir>; // size: 0x8, address: 0x808B9C88
struct {
    // total size: 0x8
} __RTTI__14RndTexRenderer; // size: 0x8, address: 0x808B9D28
struct {
    // total size: 0x8
} __RTTI__8CharHair; // size: 0x8, address: 0x808B9E88
struct {
    // total size: 0x8
} __RTTI__11CharCollide; // size: 0x8, address: 0x808B9EC0
struct {
    // total size: 0x8
} __RTTI__12CharPollable; // size: 0x8, address: 0x808B9EF8
struct {
    // total size: 0x8
} __RTTI__13CharClipGroup; // size: 0x8, address: 0x808B9F70
struct {
    // total size: 0x8
} __RTTI__8CharClip; // size: 0x8, address: 0x808B9F98
struct {
    // total size: 0x18
} __vt__26ObjPtr<6RndTex,9ObjectDir>; // size: 0x18, address: 0x808BA178
struct {
    // total size: 0x8
} __RTTI__26ObjPtr<6RndTex,9ObjectDir>; // size: 0x8, address: 0x808BA1B8
struct {
    // total size: 0x8
} __RTTI__PP14RndTexRenderer; // size: 0x8, address: 0x808BA458

