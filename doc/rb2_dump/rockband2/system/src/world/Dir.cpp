/*
    Compile unit: C:\rockband2\system\src\world\Dir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8041C1CC -> 0x80421298
*/
class DataArray * types; // size: 0x4, address: 0x80A522A0
class Symbol name; // size: 0x4, address: 0x80A522A8
class WorldDir * TheWorld; // size: 0x4, address: 0x80A522AC
// Range: 0x8041C1CC -> 0x8041C6D4
void * WorldDir::WorldDir(class WorldDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__35ObjPtrList<10WorldCrowd,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtrList<7CamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__8WorldDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class _List_node : public _List_node_base {
    // total size: 0x20
public:
    struct PresetOverride _M_data; // offset 0x8, size 0x18
};
class _List_node : public _List_node_base {
    // total size: 0x20
public:
    struct BitmapOverride _M_data; // offset 0x8, size 0x18
};
class _List_node : public _List_node_base {
    // total size: 0x2C
public:
    struct MatOverride _M_data; // offset 0x8, size 0x24
};
struct Node {
    // total size: 0xC
    class CamShot * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
struct Node {
    // total size: 0xC
    class WorldCrowd * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
static class DataNode & world; // size: 0x4, address: 0x80A522B4
// Range: 0x8041C6D4 -> 0x8041C7AC
void WorldDir::Init() {
    // References
    // -> class WorldDir * TheWorld;
    // -> static class DataNode & world;
    // -> class Symbol name;
}

static class DataNode & world; // size: 0x4, address: 0x80A522BC
// Range: 0x8041C7AC -> 0x8041D11C
void * WorldDir::~WorldDir(class WorldDir * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtrList<7CamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__35ObjPtrList<10WorldCrowd,9ObjectDir>;
    // -> static class DataNode & world;
    // -> class WorldDir * TheWorld;
    // -> class SpotlightDrawer * sCurrent;
    // -> struct [anonymous] __vt__8WorldDir;
}

// Range: 0x8041D11C -> 0x8041D180
void WorldDir::Enter(class WorldDir * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8041D180 -> 0x8041D1A8
void WorldDir::ClearDeltas() {
    // Local variables
    int i; // r5
}

// Range: 0x8041D1A8 -> 0x8041D22C
void WorldDir::SaveDeltas(class WorldDir * const this /* r28 */, float * deltaSaves /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8041D22C -> 0x8041D28C
void WorldDir::ExtendDeltas(class WorldDir * const this /* r30 */) {
    // Local variables
    int j; // r31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8041D28C -> 0x8041D300
void WorldDir::RestoreDeltas(class WorldDir * const this /* r29 */, float * deltaSaves /* r30 */) {
    // Local variables
    int j; // r31

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A522C0
static class Timer * _t; // size: 0x4, address: 0x80A522C8
// Range: 0x8041D300 -> 0x8041D4FC
void WorldDir::Poll(class WorldDir * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    class AutoTimer _at; // r1+0x10
    float deltaSaves[4]; // r1+0x18

    // References
    // -> class Rnd & TheRnd;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

// Range: 0x8041D4FC -> 0x8041D540
void WorldDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8041D540 -> 0x8041D694
void WorldDir::Copy(class WorldDir * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class WorldDir * w; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8WorldDir;
}

class SpotDrawParams {
    // total size: 0x50
public:
    float mIntensity; // offset 0x0, size 0x4
    class Color mColor; // offset 0x10, size 0x10
    float mBaseIntensity; // offset 0x20, size 0x4
    float mSmokeIntensity; // offset 0x24, size 0x4
    float mHalfDistance; // offset 0x28, size 0x4
    class ObjPtr mTexture; // offset 0x2C, size 0xC
    class ObjPtr mProxy; // offset 0x38, size 0xC
    class SpotlightDrawer * mOwner; // offset 0x44, size 0x4
};
class SpotMeshEntry {
    // total size: 0x50
public:
    class RndMesh * mMesh; // offset 0x0, size 0x4
    class RndEnviron * mEnv; // offset 0x4, size 0x4
    class Spotlight * mLight; // offset 0x8, size 0x4
    unsigned int mPACKING; // offset 0xC, size 0x4
    class Transform mXfm; // offset 0x10, size 0x40
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SpotMeshEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SpotMeshEntry * _M_start; // offset 0x0, size 0x4
    class SpotMeshEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SpotlightEntry {
    // total size: 0x8
public:
    unsigned int mPackedColor; // offset 0x0, size 0x4
    class Spotlight * mLight; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class SpotlightEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SpotlightEntry * _M_start; // offset 0x0, size 0x4
    class SpotlightEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SpotlightDrawer : public RndDrawable, public PostProcessor {
    // total size: 0xD0
protected:
    class SpotDrawParams mParams; // offset 0x40, size 0x50
};
static class vector gOldChars; // size: 0xC, address: 0x8097EE9C
static class ObjectDir * gOldTexDir; // size: 0x4, address: 0x80A522D0
// Range: 0x8041D6C4 -> 0x8041D9AC
class BinStream & __rs(class BinStream & d /* r29 */, struct BitmapOverride & c /* r30 */) {
    // Local variables
    class FilePath bitmap; // r1+0x18
    const char * name; // r31

    // References
    // -> const char * kAssertStr;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class ObjectDir * gOldTexDir;
}

// Range: 0x8041D9AC -> 0x8041DBD4
void WorldDir::PreLoad(class WorldDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC
    class ObjPtr cam; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> static class vector gOldChars;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> class Debug TheDebug;
}

// Range: 0x8041DBD4 -> 0x8041E590
void WorldDir::PostLoad(class WorldDir * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    class ObjPtr cam; // r1+0x4C
    int i; // r30
    class Symbol className; // r1+0x48
    class RndDir * p; // r27
    char name[128]; // r1+0x120
    unsigned char showing; // r0
    float drawOrder; // r1+0x44
    class Transform xfm; // r1+0x60

    // References
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> static class ObjectDir * gOldTexDir;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> static class vector gOldChars;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> class list sRevs;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static class DataNode & world; // size: 0x4, address: 0x80A522D8
// Range: 0x8041E590 -> 0x8041EB9C
void WorldDir::SyncObjects(class WorldDir * const this /* r30 */) {
    // Local variables
    class ObjDirItr crowds; // r1+0x30

    // References
    // -> class WorldDir * TheWorld;
    // -> static class DataNode & world;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10WorldCrowd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8041EB9C -> 0x8041EC68
void WorldDir::SetCrowd() {
    // Local variables
    unsigned char found; // r6
    class iterator it; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8041EC68 -> 0x8041ECDC
void WorldDir::StartBlur(class WorldDir * const this /* r31 */, float duration /* f30 */, float fadeTime /* f31 */) {
    // Local variables
    float time; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A522DC
static class Timer * _t; // size: 0x4, address: 0x80A522E4
static class Timer * worldTimer; // size: 0x4, address: 0x80A522EC
// Range: 0x8041ECDC -> 0x8041F294
void WorldDir::DrawShowing(class WorldDir * const this /* r26 */) {
    // Local variables
    class AutoTimer _at; // r1+0x48
    class AutoTimer _at; // r1+0x44
    enum ProcessCmd currentProcCmds; // r0
    class RndCam * cam; // r27
    class iterator i; // r1+0x40
    float current; // f2
    float last; // f0
    class Rect screenRect; // r1+0x60
    class Color c; // r1+0x50
    class iterator i; // r1+0x3C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Timer * worldTimer;
    // -> class UIManager TheUI;
    // -> class RndCam * sCurrent;
    // -> class CamShot * sCurrent;
    // -> class Rnd & TheRnd;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

// Range: 0x8041F294 -> 0x8041F298
void WorldDir::DrawBlur() {}

// Range: 0x8041F298 -> 0x8041F358
void WorldDir::SyncHUD(class WorldDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x8041F358 -> 0x8041F3AC
void WorldDir::SyncHides() {
    // Local variables
    class iterator i; // r1+0x18
}

// Range: 0x8041F3AC -> 0x8041F420
void WorldDir::SyncBitmaps(class WorldDir * const this /* r30 */, unsigned char post /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x8041F420 -> 0x8041F494
void WorldDir::SyncMats(class WorldDir * const this /* r30 */, unsigned char post /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x8041F494 -> 0x8041F508
void WorldDir::SyncPresets(class WorldDir * const this /* r30 */, unsigned char post /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8041F508 -> 0x8041F55C
void WorldDir::SyncCamShots() {
    // Local variables
    class iterator i; // r1+0x18
}

// Range: 0x8041F55C -> 0x8041F6E0
void BitmapOverride::Sync(struct BitmapOverride * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x3C
    class ObjRef * o; // r30
    struct _List_iterator i; // r1+0x38
    class ObjRef * o; // r30
}

// Range: 0x8041F6E0 -> 0x8041F790
void MatOverride::Sync(struct MatOverride * const this /* r30 */) {}

// Range: 0x8041F790 -> 0x8041F7B8
void PresetOverride::Sync() {}

static class Symbol _s; // size: 0x4, address: 0x80A522F4
// Range: 0x8041F7B8 -> 0x8041FE60
class DataNode WorldDir::Handle(class WorldDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A522FC
static class Symbol _s; // size: 0x4, address: 0x80A52304
// Range: 0x8041FE60 -> 0x8041FFE8
unsigned char PropSync(struct PresetOverride & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8041FFE8 -> 0x80420138
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8LightHue;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A5230C
static class Symbol _s; // size: 0x4, address: 0x80A52314
// Range: 0x80420138 -> 0x804202C4
unsigned char PropSync(struct BitmapOverride & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A5231C
static class Symbol _s; // size: 0x4, address: 0x80A52324
// Range: 0x804202C4 -> 0x8042044C
unsigned char PropSync(struct MatOverride & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A5232C
static class Symbol _s; // size: 0x4, address: 0x80A52334
static class Symbol _s; // size: 0x4, address: 0x80A5233C
static class Symbol _s; // size: 0x4, address: 0x80A52344
static class Symbol _s; // size: 0x4, address: 0x80A5234C
static class Symbol _s; // size: 0x4, address: 0x80A52354
static class Symbol _s; // size: 0x4, address: 0x80A5235C
static class Symbol _s; // size: 0x4, address: 0x80A52364
static class Symbol _s; // size: 0x4, address: 0x80A5236C
static class Symbol _s; // size: 0x4, address: 0x80A52374
static class Symbol _s; // size: 0x4, address: 0x80A5237C
static class Symbol _s; // size: 0x4, address: 0x80A52384
// Range: 0x8042044C -> 0x80420BC8
unsigned char WorldDir::SyncProperty(class WorldDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x80420BC8 -> 0x8042126C
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class CamShot * obj; // r31
    class CamShot * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std39_List_node<Q28WorldDir14PresetOverride>; // size: 0x8, address: 0x808EAC18
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std36_List_node<Q28WorldDir11MatOverride>; // size: 0x8, address: 0x808EAC58
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std39_List_node<Q28WorldDir14BitmapOverride>; // size: 0x8, address: 0x808EAC98
struct {
    // total size: 0x234
} __vt__8WorldDir; // size: 0x234, address: 0x808EACA0
struct {
    // total size: 0x18
} __vt__35ObjPtrList<10WorldCrowd,9ObjectDir>; // size: 0x18, address: 0x808EAF48
struct {
    // total size: 0x8
} __RTTI__35ObjPtrList<10WorldCrowd,9ObjectDir>; // size: 0x8, address: 0x808EAF90
struct {
    // total size: 0x18
} __vt__31ObjPtrList<7CamShot,9ObjectDir>; // size: 0x18, address: 0x808EAF98
struct {
    // total size: 0x8
} __RTTI__31ObjPtrList<7CamShot,9ObjectDir>; // size: 0x8, address: 0x808EAFE0
struct {
    // total size: 0x18
} __vt__28ObjPtr<8LightHue,9ObjectDir>; // size: 0x18, address: 0x808EAFE8
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8LightHue,9ObjectDir>; // size: 0x8, address: 0x808EB028
struct {
    // total size: 0x18
} __vt__32ObjPtr<11LightPreset,9ObjectDir>; // size: 0x18, address: 0x808EB030
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11LightPreset,9ObjectDir>; // size: 0x8, address: 0x808EB078
struct {
    // total size: 0x8
} __RTTI__8LightHue; // size: 0x8, address: 0x808EB0A0
struct {
    // total size: 0x8
} __RTTI__11LightPreset; // size: 0x8, address: 0x808EB0D0
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8042126C -> 0x80421298
static void __sinit_\Dir_cpp() {
    // References
    // -> static class vector gOldChars;
}


