/*
    Compile unit: C:\rockband2\system\src\rndobj\Part.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804D7CB8 -> 0x804DFA04
*/
class DataArray * types; // size: 0x4, address: 0x80A53390
class ParticleCommonPool * gParticlePool; // size: 0x4, address: 0x80A53398
// Range: 0x804D7CB8 -> 0x804D7CFC
void InitParticleSystem() {
    // References
    // -> class ParticleCommonPool * gParticlePool;
}

class ParticleCommonPool {
    // total size: 0x8
public:
    class RndParticle * mParticles; // offset 0x0, size 0x4
    class RndParticle * mFreeParticles; // offset 0x4, size 0x4
};
// Range: 0x804D7CFC -> 0x804D7DBC
void ParticleCommonPool::InitPool(class ParticleCommonPool * const this /* r31 */) {
    // Local variables
    int x; // r6
}

// Range: 0x804D7DC0 -> 0x804D7DE8
class RndParticle * ParticleCommonPool::AllocateParticle() {
    // Local variables
    class RndParticle * p; // r5
}

// Range: 0x804D7DE8 -> 0x804D7E18
class RndParticle * ParticleCommonPool::FreeParticle(class ParticleCommonPool * const this /* r5 */) {
    // Local variables
    class RndParticle * next; // r0
}

// Range: 0x804D7E18 -> 0x804D7F54
void RndParticleSys::SetPool(class RndParticleSys * const this /* r29 */, int n /* r30 */, enum Type t /* r31 */) {
    // Local variables
    class RndParticle * p; // r4

    // References
    // -> class Debug TheDebug;
    // -> class Rnd & TheRnd;
}

// Range: 0x804D7F54 -> 0x804D8480
void RndParticleSys::Copy(class RndParticleSys * const this /* r28 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndParticleSys * f; // r31
    class RndParticle * p; // r30
    class RndParticle * a; // r0
    class RndParticle * next; // r5
    class RndParticle * prev; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
}

static int PART_REV; // size: 0x4, address: 0x80A47338
// Range: 0x804D8480 -> 0x804D84C4
void RndParticleSys::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A5339C
// Range: 0x804D84C4 -> 0x804D8F44
void RndParticleSys::Load(class RndParticleSys * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    float mGrowRatio; // r1+0x48
    float mShrinkRatio; // r1+0x44
    float mMidColorRatio; // r1+0x40
    class Color mMidColorLow; // r1+0x80
    class Color mMidColorHigh; // r1+0x70
    int type; // r1+0x3C
    int num; // r1+0x38
    float lineLength; // r1+0x34
    class Vector2 mBubblePeriod; // r1+0x58
    class Vector2 mBubbleSize; // r1+0x50
    float mDrag; // r1+0x30
    float mStretchScale; // r1+0x2C
    class String particlesOwner; // r1+0x60
    int emitSteps; // r1+0x28
    int active; // r1+0x24
    int i; // r29
    class RndParticle * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> static int PART_REV;
    // -> static int gRev;
}

// Range: 0x804D8F44 -> 0x804D8FB0
class RndParticle * RndParticleSys::AllocParticle(class RndParticleSys * const this /* r31 */) {
    // Local variables
    class RndParticle * p; // r3

    // References
    // -> class ParticleCommonPool * gParticlePool;
}

// Range: 0x804D8FB0 -> 0x804D93C8
void RndParticleSys::InitParticle(class RndParticleSys * const this /* r28 */, class RndParticle * p /* r29 */, const class Transform * locToRel /* r30 */) {
    // Local variables
    float pitch; // f30
    float yaw; // f29
    float cosPitch; // f0
    float speed; // f0
    float t; // f31
    class Transform xfm; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804D93C8 -> 0x804D9498
class RndParticle * RndParticleSys::FreeParticle(class RndParticleSys * const this /* r30 */, class RndParticle * p /* r31 */) {
    // Local variables
    class RndParticle * next; // r0

    // References
    // -> class ParticleCommonPool * gParticlePool;
    // -> class Debug TheDebug;
}

// Range: 0x804D9498 -> 0x804D95A4
void RndParticleSys::SetSubSamples(class RndParticleSys * const this /* r31 */) {}

// Range: 0x804D95A4 -> 0x804D9834
void RndParticleSys::SetRelativeMotion(class RndParticleSys * const this /* r30 */, float r /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804D9834 -> 0x804D98A8
void RndParticleSys::DrawShowing(class RndParticleSys * const this /* r31 */) {}

// Range: 0x804D98A8 -> 0x804D99F0
void RndParticleSys::UpdateSphere(class RndParticleSys * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x804D99F0 -> 0x804D9B60
unsigned char RndParticleSys::MakeWorldSphere(class RndParticleSys * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class RndParticle * p; // r31
    class Sphere s2; // r1+0x10
}

// Range: 0x804D9B60 -> 0x804D9B8C
void RndParticleSys::SetFrameDrive() {}

// Range: 0x804D9B8C -> 0x804D9B9C
void RndParticleSys::SetPauseOffscreen() {}

// Range: 0x804D9B9C -> 0x804D9BF8
void RndParticleSys::SetFrame(class RndParticleSys * const this /* r31 */, float frame /* f31 */) {}

// Range: 0x804D9BF8 -> 0x804D9C1C
float RndParticleSys::EndFrame() {}

static class Timer * _t; // size: 0x4, address: 0x80A533A0
// Range: 0x804D9C1C -> 0x804D9E7C
void RndParticleSys::Poll(class RndParticleSys * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    float frame; // f31
    class RndParticle * p; // r4

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

// Range: 0x804D9E7C -> 0x804D9FF8
void RndParticleSys::MakeLocToRel(class RndParticleSys * const this /* r30 */, class Transform & xfm /* r31 */) {}

// Range: 0x804D9FF8 -> 0x804DA144
void RndParticleSys::CreateParticles(class RndParticleSys * const this /* r30 */, float frame /* f30 */, float deltaFrame /* f31 */, const class Transform & xfm /* r31 */) {
    // Local variables
    class RndParticle * p; // r4
}

// Range: 0x804DA144 -> 0x804DA990
void RndParticleSys::UpdateRelativeXfm(class RndParticleSys * const this /* r30 */) {
    // Local variables
    class Quat q; // r1+0x80

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804DA990 -> 0x804DA9D8
float RndParticleSys::CalcFrame() {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x804DA9D8 -> 0x804DAECC
void RndParticleSys::UpdateParticles(class RndParticleSys * const this /* r31 */) {
    // Local variables
    float frame; // f31
    float deltaFrame; // f30
    class Transform xfm; // r1+0x20
    class Vector3 lastPos; // r1+0x10
    float pitch; // f29
    float yaw; // f26
    float speed; // f0
    float cosPitch; // f0
    int steps; // r30
}

// Range: 0x804DAECC -> 0x804DAF64
void RndParticleSys::Enter(class RndParticleSys * const this /* r31 */) {
    // Local variables
    class RndParticle * p; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804DAF64 -> 0x804DB0E4
void RndParticleSys::RunFastForward(class RndParticleSys * const this /* r31 */) {
    // Local variables
    float particlesPerFrame; // f1
    float framesPerParticle; // r1+0x18
    float framesToMaxParticles; // r1+0x14
    float timeToSimulate; // f30
    float deltaFrame; // f29
    float upToFrame; // f0
    class Transform xfm; // r1+0x20
    float frame; // f30
}

// Range: 0x804DB0E4 -> 0x804DB19C
void RndParticleSys::ExplicitParticles(class RndParticleSys * const this /* r29 */, int cnt /* r30 */) {
    // Local variables
    float frame; // f31
    class Transform xfm; // r1+0x10
    int i; // r31
    class RndParticle * p; // r4
}

// Range: 0x804DB19C -> 0x804DB1DC
unsigned char Burst::Set() {}

// Range: 0x804DB1DC -> 0x804DB24C
float Burst::Emit() {
    // Local variables
    float x; // f2
}

// Range: 0x804DB24C -> 0x804DB454
float RndParticleSys::CheckBursts(class RndParticleSys * const this /* r31 */, float deltaFrame /* f31 */) {
    // Local variables
    float emission; // f30
    class Burst * bIter; // r30
    float emitAdd; // f0
    class Burst burst; // r1+0x20
}

// Range: 0x804DB454 -> 0x804DB82C
void RndParticleSys::MoveParticles(class RndParticleSys * const this /* r28 */, float frame /* f30 */, float deltaFrame /* f31 */) {
    // Local variables
    float rotDrag; // f0
    class Vector3 deltaForce; // r1+0x40
    unsigned char bounce; // r0
    class Plane bouncePlane; // r1+0x30
    class RndParticle * p; // r4
    float velDot; // f0
    class Vector3 plane; // r1+0x20
    float dt; // f0
    class Color c; // r1+0x10
}

// Range: 0x804DB82C -> 0x804DBAB8
void * RndParticleSys::~RndParticleSys(class RndParticleSys * const this /* r30 */) {
    // Local variables
    class RndParticle * p; // r4

    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__14RndParticleSys;
}

// Range: 0x804DBAB8 -> 0x804DBE38
void * RndParticleSys::RndParticleSys(class RndParticleSys * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__14RndParticleSys;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x804DBE38 -> 0x804DBECC
void RndParticleSys::Replace(class RndParticleSys * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x804DBECC -> 0x804DBF34
void RndParticleSys::SetMat(class RndParticleSys * const this /* r30 */, class RndMat * m /* r31 */) {}

// Range: 0x804DBF34 -> 0x804DC00C
void RndParticleSys::SetMesh(class RndParticleSys * const this /* r30 */, class RndMesh * m /* r31 */) {}

// Range: 0x804DC00C -> 0x804DC0C0
void RndParticleSys::Mats(class RndParticleSys * const this /* r31 */, class list & mats /* r30 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A533A8
static class Symbol _s; // size: 0x4, address: 0x80A533B0
static class Symbol _s; // size: 0x4, address: 0x80A533B8
static class Symbol _s; // size: 0x4, address: 0x80A533C0
static class Symbol _s; // size: 0x4, address: 0x80A533C8
static class Symbol _s; // size: 0x4, address: 0x80A533D0
static class Symbol _s; // size: 0x4, address: 0x80A533D8
static class Symbol _s; // size: 0x4, address: 0x80A533E0
static class Symbol _s; // size: 0x4, address: 0x80A533E8
static class Symbol _s; // size: 0x4, address: 0x80A533F0
static class Symbol _s; // size: 0x4, address: 0x80A533F8
static class Symbol _s; // size: 0x4, address: 0x80A53400
static class Symbol _s; // size: 0x4, address: 0x80A53408
static class Symbol _s; // size: 0x4, address: 0x80A53410
static class Symbol _s; // size: 0x4, address: 0x80A53418
static class Symbol _s; // size: 0x4, address: 0x80A53420
static class Symbol _s; // size: 0x4, address: 0x80A53428
static class Symbol _s; // size: 0x4, address: 0x80A53430
static class Symbol _s; // size: 0x4, address: 0x80A53438
static class Symbol _s; // size: 0x4, address: 0x80A53440
static class Symbol _s; // size: 0x4, address: 0x80A53448
static class Symbol _s; // size: 0x4, address: 0x80A53450
static class Symbol _s; // size: 0x4, address: 0x80A53458
// Range: 0x804DC0C0 -> 0x804DCFC8
class DataNode RndParticleSys::Handle(class RndParticleSys * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x14
    class MessageTimer _mt; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28
    class DataNode _n; // r1+0x20
    class DataNode _n; // r1+0x18

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
}

// Range: 0x804DCFC8 -> 0x804DD1AC
class DataNode RndParticleSys::OnSetStartColor(class RndParticleSys * const this /* r29 */, const class DataArray * a /* r30 */) {}

// Range: 0x804DD1AC -> 0x804DD380
class DataNode RndParticleSys::OnSetStartColorInt(class RndParticleSys * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class Color rgb_low; // r1+0x20
    class Color rgb_hi; // r1+0x10
}

// Range: 0x804DD380 -> 0x804DD564
class DataNode RndParticleSys::OnSetEndColor(class RndParticleSys * const this /* r29 */, const class DataArray * a /* r30 */) {}

// Range: 0x804DD564 -> 0x804DD738
class DataNode RndParticleSys::OnSetEndColorInt(class RndParticleSys * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class Color rgb_low; // r1+0x20
    class Color rgb_hi; // r1+0x10
}

// Range: 0x804DD738 -> 0x804DD7C0
class DataNode RndParticleSys::OnSetEmitRate(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DD7C0 -> 0x804DD8A4
class DataNode RndParticleSys::OnAddEmitRate(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    float add; // f0
}

// Range: 0x804DD8A4 -> 0x804DD944
class DataNode RndParticleSys::OnSetBurstInterval(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DD944 -> 0x804DD9CC
class DataNode RndParticleSys::OnSetBurstPeak(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DD9CC -> 0x804DDA54
class DataNode RndParticleSys::OnSetBurstLength(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDA54 -> 0x804DDA98
class DataNode RndParticleSys::OnExplicitPart() {}

// Range: 0x804DDA98 -> 0x804DDB40
class DataNode RndParticleSys::OnExplicitParts(class RndParticleSys * const this /* r29 */, const class DataArray * a /* r30 */) {}

// Range: 0x804DDB40 -> 0x804DDBC8
class DataNode RndParticleSys::OnSetLife(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDBC8 -> 0x804DDC50
class DataNode RndParticleSys::OnSetSpeed(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDC50 -> 0x804DDD14
class DataNode RndParticleSys::OnSetRotate(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDD14 -> 0x804DDDD0
class DataNode RndParticleSys::OnSetSwingArm(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDDD0 -> 0x804DDE58
class DataNode RndParticleSys::OnSetStartSize(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DDE58 -> 0x804DDEE0
class DataNode RndParticleSys::OnSetMat(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x804DDEE0 -> 0x804DE034
class DataNode RndParticleSys::OnSetPos(class RndParticleSys * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804DE034 -> 0x804DE054
class DataNode RndParticleSys::OnActiveParticles() {}

// Range: 0x804DE054 -> 0x804DE118
class BinStream & __rs(class BinStream & d /* r30 */, class RndParticle & c /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A53460
static class Symbol _s; // size: 0x4, address: 0x80A53468
// Range: 0x804DE118 -> 0x804DE2F0
static unsigned char AngleVectorSync(class Vector2 & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A53470
static class Symbol _s; // size: 0x4, address: 0x80A53478
static class Symbol _s; // size: 0x4, address: 0x80A53480
static class Symbol _s; // size: 0x4, address: 0x80A53488
static class Symbol _s; // size: 0x4, address: 0x80A53490
static class Symbol _s; // size: 0x4, address: 0x80A53498
static class Symbol _s; // size: 0x4, address: 0x80A534A0
static class Symbol _s; // size: 0x4, address: 0x80A534A8
static class Symbol _s; // size: 0x4, address: 0x80A534B0
static class Symbol _s; // size: 0x4, address: 0x80A534B8
static class Symbol _s; // size: 0x4, address: 0x80A534C0
static class Symbol _s; // size: 0x4, address: 0x80A534C8
static class Symbol _s; // size: 0x4, address: 0x80A534D0
static class Symbol _s; // size: 0x4, address: 0x80A534D8
static class Symbol _s; // size: 0x4, address: 0x80A534E0
static class Symbol _s; // size: 0x4, address: 0x80A534E8
static class Symbol _s; // size: 0x4, address: 0x80A534F0
static class Symbol _s; // size: 0x4, address: 0x80A534F8
static class Symbol _s; // size: 0x4, address: 0x80A53500
static class Symbol _s; // size: 0x4, address: 0x80A53508
static class Symbol _s; // size: 0x4, address: 0x80A53510
static class Symbol _s; // size: 0x4, address: 0x80A53518
static class Symbol _s; // size: 0x4, address: 0x80A53520
static class Symbol _s; // size: 0x4, address: 0x80A53528
static class Symbol _s; // size: 0x4, address: 0x80A53530
static class Symbol _s; // size: 0x4, address: 0x80A53538
static class Symbol _s; // size: 0x4, address: 0x80A53540
static class Symbol _s; // size: 0x4, address: 0x80A53548
static class Symbol _s; // size: 0x4, address: 0x80A53550
static class Symbol _s; // size: 0x4, address: 0x80A53558
static class Symbol _s; // size: 0x4, address: 0x80A53560
static class Symbol _s; // size: 0x4, address: 0x80A53568
static class Symbol _s; // size: 0x4, address: 0x80A53570
static class Symbol _s; // size: 0x4, address: 0x80A53578
static class Symbol _s; // size: 0x4, address: 0x80A53580
static class Symbol _s; // size: 0x4, address: 0x80A53588
static class Symbol _s; // size: 0x4, address: 0x80A53590
static class Symbol _s; // size: 0x4, address: 0x80A53598
static class Symbol _s; // size: 0x4, address: 0x80A535A0
static class Symbol _s; // size: 0x4, address: 0x80A535A8
// Range: 0x804DE2F0 -> 0x804DFA04
unsigned char RndParticleSys::SyncProperty(class RndParticleSys * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x18C
} __vt__14RndParticleSys; // size: 0x18C, address: 0x808FCF48
struct {
    // total size: 0x8
} __RTTI__PQ214RndParticleSys5Burst; // size: 0x8, address: 0x808FD480

