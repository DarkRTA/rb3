/*
    Compile unit: C:\rockband2\system\src\bandobj\WorldMapDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802CD85C -> 0x802CFFF4
*/
class DataArray * types; // size: 0x4, address: 0x80A504F8
class Symbol name; // size: 0x4, address: 0x80A50500
class DataArray * sTownList; // size: 0x4, address: 0x80A50504
static char kOccludingEarthName[21]; // size: 0x15, address: 0x808488D8
class WorldMapDir : public PanelDir {
    // total size: 0x300
    class vector mTownGroups; // offset 0x24C, size 0xC
    class ObjPtr mOccludingEarth; // offset 0x258, size 0xC
    float mFocusScale; // offset 0x264, size 0x4
    class ObjPtr mPostProc; // offset 0x268, size 0xC
    float mFocalDistance; // offset 0x274, size 0x4
    float mBlurDepth; // offset 0x278, size 0x4
    float mMinBlur; // offset 0x27C, size 0x4
    float mMaxBlur; // offset 0x280, size 0x4
    unsigned char mDoCulling; // offset 0x284, size 0x1
    class Quat mTargetRot; // offset 0x290, size 0x10
    class ObjPtr mVenueGroup; // offset 0x2A0, size 0xC
    class ObjPtr mTownGroup; // offset 0x2AC, size 0xC
    class Symbol mTown; // offset 0x2B8, size 0x4
    class Symbol mVenue; // offset 0x2BC, size 0x4
    unsigned char mFirstPoll; // offset 0x2C0, size 0x1
    unsigned char mZoomed; // offset 0x2C1, size 0x1
};
// Range: 0x802CD85C -> 0x802CDA4C
void WorldMapDir::Init() {
    // Local variables
    class DataArray * root; // r30
    class DataArray * tour; // r30
    class DataArray * data; // r29
    int i; // r28
    class Symbol townname; // r1+0x20

    // References
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataArray * sTownList;
}

// Range: 0x802CDA4C -> 0x802CDC8C
void * WorldMapDir::WorldMapDir(class WorldMapDir * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPostProc,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__11WorldMapDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndPostProc * mPtr; // offset 0x8, size 0x4
};
// Range: 0x802CDC8C -> 0x802CDE14
void * WorldMapDir::~WorldMapDir(class WorldMapDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPostProc,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
}

// Range: 0x802CDE14 -> 0x802CDE58
void WorldMapDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802CDE58 -> 0x802CDF70
void WorldMapDir::PreLoad(class WorldMapDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int version; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
}

// Range: 0x802CDF70 -> 0x802CE0B4
void WorldMapDir::PostLoad(class WorldMapDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class Symbol town; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> class list sRevs;
}

// Range: 0x802CE0B4 -> 0x802CE1B4
void WorldMapDir::Copy(class WorldMapDir * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class WorldMapDir * p; // r0

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11WorldMapDir;
}

// Range: 0x802CE1B4 -> 0x802CE3F8
void WorldMapDir::DrawShowing(class WorldMapDir * const this /* r28 */) {
    // Local variables
    class Sphere earthSphere; // r1+0x60
    class RndCam * camera; // r30
    class Vector3 cameraPosition; // r1+0x30
    class Vector3 toEarthCenter; // r1+0x20
    float sqDistanceToEarthCenter; // f0
    float fudge; // f1
    float sqDistanceToHorizon; // f31
    class RndDrawable * * iter; // r30
    class RndDrawable * townGroup; // r29
    class Sphere townSphere; // r1+0x40
    class Vector3 toTownCenter; // r1+0x10
    float sqDistanceToTownCenter; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndCam * sCurrent;
}

// Range: 0x802CE3F8 -> 0x802CE530
void WorldMapDir::Poll(class WorldMapDir * const this /* r30 */) {
    // Local variables
    class Quat current; // r1+0x10
    class Matrix3 mtx; // r1+0x20

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x802CE530 -> 0x802CE7BC
void WorldMapDir::Enter(class WorldMapDir * const this /* r31 */) {
    // Local variables
    int i; // r28
    class Symbol town; // r1+0x34
    const char * townGroupName; // r30
    class RndDrawable * townGroup; // r1+0x30

    // References
    // -> static char kOccludingEarthName[21];
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> class DataArray * sTownList;
    // -> const char * gNullStr;
    // -> class LoadMgr TheLoadMgr;
}

class DOFProc : public Object {
    // total size: 0x28
};
// Range: 0x802CE7BC -> 0x802CE840
void WorldMapDir::Exit(class WorldMapDir * const this /* r30 */) {}

// Range: 0x802CE840 -> 0x802CE874
void WorldMapDir::SetDoCulling() {
    // Local variables
    class RndDrawable * * iter; // r5
}

// Range: 0x802CE874 -> 0x802CE8E8
void WorldMapDir::SetPostProc(class WorldMapDir * const this /* r30 */, class RndPostProc * postproc /* r31 */) {}

// Range: 0x802CE8E8 -> 0x802CE8F0
class DataArray * WorldMapDir::GetTownList() {
    // References
    // -> class DataArray * sTownList;
}

// Range: 0x802CE8F0 -> 0x802CEE00
void WorldMapDir::SetTown(class WorldMapDir * const this /* r30 */, class Symbol & town /* r23 */, unsigned char snap /* r24 */, unsigned char close /* r31 */) {
    // Local variables
    const char * targName; // r26
    class RndTransformable * targ; // r25
    const char * newName; // r0
    class Transform t; // r1+0x70
    class Quat townFrame; // r1+0x30
    class Matrix3 mtx; // r1+0x40

    // References
    // -> const char * kNotObjectMsg;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol loop; // size: 0x4, address: 0x80A5050C
static class Symbol dest; // size: 0x4, address: 0x80A50514
// Range: 0x802CEE00 -> 0x802CEF58
void WorldMapDir::HighlightGroup(class RndGroup * grp /* r30 */, unsigned char h /* r31 */) {
    // Local variables
    float end; // f31

    // References
    // -> static class Symbol dest;
    // -> const char * gNullStr;
    // -> static class Symbol loop;
}

// Range: 0x802CEF58 -> 0x802CF390
void WorldMapDir::Sync(class WorldMapDir * const this /* r27 */, class Symbol & town /* r28 */, class Symbol & venue /* r29 */, unsigned char zoomed /* r30 */) {
    // Local variables
    const char * groupName; // r0

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

static class Symbol _s; // size: 0x4, address: 0x80A5051C
static class Symbol _s; // size: 0x4, address: 0x80A50524
// Range: 0x802CF390 -> 0x802CF87C
class DataNode WorldMapDir::Handle(class WorldMapDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A5052C
static class Symbol _s; // size: 0x4, address: 0x80A50534
static class Symbol _s; // size: 0x4, address: 0x80A5053C
static class Symbol _s; // size: 0x4, address: 0x80A50544
static class Symbol _s; // size: 0x4, address: 0x80A5054C
static class Symbol _s; // size: 0x4, address: 0x80A50554
static class Symbol _s; // size: 0x4, address: 0x80A5055C
static class Symbol _s; // size: 0x4, address: 0x80A50564
// Range: 0x802CF87C -> 0x802CFFF4
unsigned char WorldMapDir::SyncProperty(class WorldMapDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPostProc;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x234
} __vt__11WorldMapDir; // size: 0x234, address: 0x808C9694
struct {
    // total size: 0x8
} __RTTI__11WorldMapDir; // size: 0x8, address: 0x808C9930
struct {
    // total size: 0x18
} __vt__32ObjPtr<11RndPostProc,9ObjectDir>; // size: 0x18, address: 0x808C9980
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11RndPostProc,9ObjectDir>; // size: 0x8, address: 0x808C99C8

