/*
    Compile unit: C:\rockband2\system\src\world\Fireworks.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80425398 -> 0x804286B0
*/
class DataArray * types; // size: 0x4, address: 0x80A52398
class Symbol name; // size: 0x4, address: 0x80A523A0
class ExplosionParams {
    // total size: 0x20
public:
    class RndMat * mMat; // offset 0x0, size 0x4
    int mParticles; // offset 0x4, size 0x4
    class Vector2 mSpeedRange; // offset 0x8, size 0x8
    class Vector2 mLifeRange; // offset 0x10, size 0x8
    class Vector2 mSizeRange; // offset 0x18, size 0x8
};
static class ExplosionParams gExplosionParams[2]; // size: 0x40, address: 0x8097EEB0
static unsigned char gInitted; // size: 0x1, address: 0x80A523A4
static class RndParticleSys * gTrailPS; // size: 0x4, address: 0x80A523A8
static class Vector2 gLaunchAngleRange; // size: 0x8, address: 0x8097EEF0
static class Vector2 gLaunchSpeedRange; // size: 0x8, address: 0x8097EEF8
static class DataArray * gLaunchDirections; // size: 0x4, address: 0x80A523AC
static class Vector2 gExplodeTimeRange; // size: 0x8, address: 0x8097EF00
static class Vector3 gTrailForce; // size: 0x10, address: 0x8097EF10
static class Vector3 gExplosionForce; // size: 0x10, address: 0x8097EF20
static class RndMat * gFlareMat; // size: 0x4, address: 0x80A523B0
static float gFlareMaxSize; // size: 0x4, address: 0x80A523B4
static float gFlareGrowTime; // size: 0x4, address: 0x80A523B8
static float gFlareGrowTimeMult; // size: 0x4, address: 0x80A523BC
static float gFlareShrinkTime; // size: 0x4, address: 0x80A523C0
static float gFlareShrinkTimeMult; // size: 0x4, address: 0x80A523C4
static float gFlareEndTime; // size: 0x4, address: 0x80A523C8
static float gMaxRadius; // size: 0x4, address: 0x80A523CC
static class RndParticleSys * gFlarePS; // size: 0x4, address: 0x80A523D0
class list : public _List_base {
    // total size: 0x8
};
static class list gRockets; // size: 0x8, address: 0x8097EF40
class WorldFireworks : public RndDrawable, public RndTransformable, public RndPollable {
    // total size: 0x1B0
    class ObjDirPtr mResources; // offset 0x100, size 0xC
    class list mActive; // offset 0x10C, size 0x8
    class Color mStartColorLow; // offset 0x120, size 0x10
    class Color mStartColorHigh; // offset 0x130, size 0x10
    class Color mEndColorLow; // offset 0x140, size 0x10
    class Color mEndColorHigh; // offset 0x150, size 0x10
    class ObjPtr mLaunchSeq; // offset 0x160, size 0xC
    class ObjPtr mExplodeSeq; // offset 0x16C, size 0xC
};
// Range: 0x80425398 -> 0x80425734
void WorldFireworks::Copy(class WorldFireworks * const this /* r31 */, const class Object * src /* r25 */, enum CopyType type /* r24 */) {
    // Local variables
    const class WorldFireworks * rhs; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14WorldFireworks;
}

// Range: 0x80425734 -> 0x80425778
void WorldFireworks::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80425778 -> 0x804257D4
void WorldFireworks::Load(class WorldFireworks * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x804257D4 -> 0x804259E4
void WorldFireworks::PreLoad(class WorldFireworks * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8
    class ObjPtr explodeSfx; // r1+0xC

    // References
    // -> struct [anonymous] __vt__23ObjPtr<3Sfx,9ObjectDir>;
}

// Range: 0x804259E4 -> 0x80425B6C
void WorldFireworks::PostLoad(class WorldFireworks * const this /* r26 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80425B6C -> 0x80426588
void WorldFireworks::InitResources(class WorldFireworks * const this /* r27 */) {
    // Local variables
    const class DataArray * data; // r29
    const class DataArray * exp; // r22
    int i; // r28
    class ExplosionParams & p; // r21
    class Rocket & r; // r0
    int i; // r21
    const class ExplosionParams & p; // r22

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q214WorldFireworks6Rocket>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gRockets;
    // -> static class RndParticleSys * gFlarePS;
    // -> class Symbol name;
    // -> static float gFlareEndTime;
    // -> static float gFlareShrinkTimeMult;
    // -> static float gFlareGrowTimeMult;
    // -> static float gFlareShrinkTime;
    // -> static float gFlareGrowTime;
    // -> static float gFlareMaxSize;
    // -> static class ExplosionParams gExplosionParams[2];
    // -> static float gMaxRadius;
    // -> static class Vector3 gExplosionForce;
    // -> static class Vector3 gTrailForce;
    // -> static class Vector2 gExplodeTimeRange;
    // -> static class DataArray * gLaunchDirections;
    // -> static class Vector2 gLaunchSpeedRange;
    // -> static class Vector2 gLaunchAngleRange;
    // -> static class RndMat * gFlareMat;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> static class RndParticleSys * gTrailPS;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gInitted;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std37_List_node<Q214WorldFireworks6Rocket>; // size: 0x8, address: 0x808EBE38
// Range: 0x80426588 -> 0x80426784
void * WorldFireworks::WorldFireworks(class WorldFireworks * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8Sequence,9ObjectDir>;
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
    // -> struct [anonymous] __vt__14WorldFireworks;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

enum /* @enum$14560Fireworks_cpp */ {
    kLaunching = 0,
    kExploding = 1,
};
class Rocket {
    // total size: 0x30
public:
    class RndParticleSys * mTrailPS; // offset 0x0, size 0x4
    class RndParticleSys * mExplosionPS[2]; // offset 0x4, size 0x8
    class Vector3 mVelocity; // offset 0x10, size 0x10
    class RndParticle * mFlarePart; // offset 0x20, size 0x4
    float mExplodeTime; // offset 0x24, size 0x4
    enum /* @enum$14560Fireworks_cpp */ {
        kLaunching = 0,
        kExploding = 1,
    } mState; // offset 0x28, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x40
public:
    class Rocket _M_data; // offset 0x10, size 0x30
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
// Range: 0x80426784 -> 0x80426E84
void * WorldFireworks::~WorldFireworks(class WorldFireworks * const this /* r30 */) {
    // Local variables
    class FilePath file; // r1+0x14
    int j; // r27

    // References
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Sequence,9ObjectDir>;
    // -> static class RndParticleSys * gFlarePS;
    // -> static class list gRockets;
    // -> static unsigned char gInitted;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class FilePath sNull;
    // -> struct [anonymous] __vt__14WorldFireworks;
}

// Range: 0x80426E84 -> 0x80426F2C
class Rocket * WorldFireworks::AllocateRocket() {
    // References
    // -> static class list gRockets;
}

// Range: 0x80426F2C -> 0x80426F84
void WorldFireworks::FreeRocket() {
    // References
    // -> static class list gRockets;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80426F84 -> 0x80426FF8
void WorldFireworks::Enter(class WorldFireworks * const this /* r31 */) {
    // Local variables
    struct _List_iterator ri; // r1+0x14
}

// Range: 0x80426FF8 -> 0x8042745C
void WorldFireworks::Poll(class WorldFireworks * const this /* r28 */) {
    // Local variables
    float curTime; // f30
    float elapsed; // f0
    struct _List_iterator ri; // r1+0x20
    class Rocket & r; // r0
    unsigned char erase; // r30
    class Vector3 v; // r1+0x30
    int i; // r29
    float time; // f29
    int i; // r27
    struct _List_iterator o; // r1+0x1C

    // References
    // -> static float gFlareShrinkTimeMult;
    // -> static float gFlareEndTime;
    // -> static float gFlareGrowTimeMult;
    // -> static float gFlareGrowTime;
    // -> static class Vector3 gTrailForce;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8042745C -> 0x804274C8
unsigned char WorldFireworks::MakeWorldSphere(class WorldFireworks * const this /* r30 */, class Sphere & s /* r31 */) {
    // References
    // -> static float gMaxRadius;
}

// Range: 0x804274C8 -> 0x8042757C
void WorldFireworks::DrawShowing(class WorldFireworks * const this /* r29 */) {
    // Local variables
    struct _List_iterator ri; // r1+0x10
    class Rocket & r; // r0
    int i; // r30

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8042757C -> 0x80427598
void WorldFireworks::DrawClass() {
    // References
    // -> static class RndParticleSys * gFlarePS;
    // -> static unsigned char gInitted;
}

static class Symbol _s; // size: 0x4, address: 0x80A523D8
// Range: 0x80427598 -> 0x80427CC0
class DataNode WorldFireworks::Handle(class WorldFireworks * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A523E0
static class Symbol _s; // size: 0x4, address: 0x80A523E8
static class Symbol _s; // size: 0x4, address: 0x80A523F0
static class Symbol _s; // size: 0x4, address: 0x80A523F8
static class Symbol _s; // size: 0x4, address: 0x80A52400
static class Symbol _s; // size: 0x4, address: 0x80A52408
static class Symbol _s; // size: 0x4, address: 0x80A52410
// Range: 0x80427CC0 -> 0x8042849C
unsigned char WorldFireworks::SyncProperty(class WorldFireworks * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class FilePath sNull;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x128
} __vt__14WorldFireworks; // size: 0x128, address: 0x808EBFF8
struct {
    // total size: 0x8
} __RTTI__14WorldFireworks; // size: 0x8, address: 0x808EC168
// Range: 0x8042849C -> 0x8042851C
static void __sinit_\Fireworks_cpp() {
    // References
    // -> static class list gRockets;
    // -> static class ExplosionParams gExplosionParams[2];
}


