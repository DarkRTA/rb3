/*
    Compile unit: C:\rockband2\system\src\world\Video.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8044BC90 -> 0x8044D248
*/
class DataArray * types; // size: 0x4, address: 0x80A52598
class Symbol name; // size: 0x4, address: 0x80A525A0
class VideoScreen : public virtual Object, public RndPollable {
    // total size: 0x9C
protected:
    class RndTex * mTargetTex; // offset 0xC, size 0x4
    class ObjPtr mScreenMat; // offset 0x10, size 0xC
    class ObjPtr mSnowMovie; // offset 0x1C, size 0xC
    class ObjPtr mMovie; // offset 0x28, size 0xC
    class ObjPtr mTarget; // offset 0x34, size 0xC
    class ObjPtr mTargetPart; // offset 0x40, size 0xC
    class ObjPtr mOverrideTex; // offset 0x4C, size 0xC
    float mTargetMinSize; // offset 0x58, size 0x4
    float mTargetScale; // offset 0x5C, size 0x4
    float mTargetMaxExpand; // offset 0x60, size 0x4
    float mSnowBlend; // offset 0x64, size 0x4
    float mSecondsOffset; // offset 0x68, size 0x4
    class RndMat * mSnowMat; // offset 0x6C, size 0x4
};
// Range: 0x8044BC90 -> 0x8044BFDC
void * VideoScreen::VideoScreen(class VideoScreen * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> class TaskMgr TheTaskMgr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndMovie,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__11VideoScreen;
    // -> struct [anonymous] __vt__11RndPollable;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndTex * mPtr; // offset 0x8, size 0x4
};
class RndMovie : public RndAnimatable {
    // total size: 0x58
protected:
    class FilePath mFile; // offset 0x10, size 0xC
    unsigned char mStream; // offset 0x1C, size 0x1
    unsigned char mLoop; // offset 0x1D, size 0x1
    class ObjOwnerPtr mTex; // offset 0x20, size 0xC
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndMovie * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8044BFDC -> 0x8044C1B8
void * VideoScreen::~VideoScreen(class VideoScreen * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndMovie,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__11VideoScreen;
}

// Range: 0x8044C1B8 -> 0x8044C380
void VideoScreen::Copy(class VideoScreen * const this /* r29 */, const class Object * from /* r30 */) {
    // Local variables
    const class VideoScreen * rhs; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11VideoScreen;
}

// Range: 0x8044C380 -> 0x8044CA44
void VideoScreen::Poll(class VideoScreen * const this /* r30 */) {
    // Local variables
    class RndTransformable * target; // r31
    class Vector3 toTarget; // r1+0x20
    float size; // f31
    class Sphere s; // r1+0x30
    float origSize; // f30
    class Vector2 center; // r1+0x10
    float y_ratio; // f29
    float x_ratio; // f2
    class Transform xfm; // r1+0x50

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
}

// Range: 0x8044CA44 -> 0x8044CB80
void VideoScreen::SetupMaterials(class VideoScreen * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A525A8
static class Symbol _s; // size: 0x4, address: 0x80A525B0
static class Symbol _s; // size: 0x4, address: 0x80A525B8
static class Symbol _s; // size: 0x4, address: 0x80A525C0
static class Symbol _s; // size: 0x4, address: 0x80A525C8
static class Symbol _s; // size: 0x4, address: 0x80A525D0
static class Symbol _s; // size: 0x4, address: 0x80A525D8
static class Symbol _s; // size: 0x4, address: 0x80A525E0
static class Symbol _s; // size: 0x4, address: 0x80A525E8
static class Symbol _s; // size: 0x4, address: 0x80A525F0
// Range: 0x8044CB80 -> 0x8044D248
unsigned char VideoScreen::SyncProperty(class VideoScreen * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
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
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8C
} __vt__11VideoScreen; // size: 0x8C, address: 0x808EE0F4
struct {
    // total size: 0x8
} __RTTI__11VideoScreen; // size: 0x8, address: 0x808EE1A8
struct {
    // total size: 0x18
} __vt__28ObjPtr<8RndMovie,9ObjectDir>; // size: 0x18, address: 0x808EE1F8
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8RndMovie,9ObjectDir>; // size: 0x8, address: 0x808EE238
struct {
    // total size: 0x8
} __RTTI__8RndMovie; // size: 0x8, address: 0x808EE268

