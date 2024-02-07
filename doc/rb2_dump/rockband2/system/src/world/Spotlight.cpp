/*
    Compile unit: C:\rockband2\system\src\world\Spotlight.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8044E570 -> 0x8045A12C
*/
class Symbol name; // size: 0x4, address: 0x80A52614
class DataArray * types; // size: 0x4, address: 0x80A52618
class Symbol name; // size: 0x4, address: 0x80A52620
class RndEnviron * sEnviron; // size: 0x4, address: 0x80A52624
class RndMesh * sDiskMesh; // size: 0x4, address: 0x80A52628
// Range: 0x8044E570 -> 0x8044E65C
void Spotlight::Init() {
    // References
    // -> class RndEnviron * sEnviron;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Symbol name;
    // -> class Symbol name;
}

// Range: 0x8044E65C -> 0x8044EA80
void * Spotlight::Spotlight(class Spotlight * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjOwnerPtr<9Spotlight,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndFlare;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__9Spotlight;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8044EA80 -> 0x8044EFB8
void * Spotlight::~Spotlight(class Spotlight * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__34ObjOwnerPtr<9Spotlight,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> class SpotlightDrawer * sCurrent;
    // -> struct [anonymous] __vt__9Spotlight;
}

// Range: 0x8044EFB8 -> 0x8044EFC0
void Spotlight::SetFlareEnabled() {}

// Range: 0x8044EFC0 -> 0x8044EFC8
void Spotlight::SetFlareIsBillboard() {}

// Range: 0x8044EFC8 -> 0x8044F024
void Spotlight::UpdateFlare() {}

static unsigned int gRev; // size: 0x4, address: 0x80A5262C
// Range: 0x8044F024 -> 0x8044F130
void Spotlight::ConvertGroupToMesh(class Spotlight * const this /* r26 */, class RndGroup * group /* r27 */) {
    // Local variables
    int numMeshes; // r29
    class RndDrawable * const * drawIter; // r28
    class RndDrawable * const * const drawEnd; // r0
    class RndMesh * trans; // r0

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

static class Symbol bone_pelvis; // size: 0x4, address: 0x80A52634
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
// Range: 0x8044F130 -> 0x8044FF4C
void Spotlight::Load(class Spotlight * const this /* r27 */, class BinStream & d /* r28 */) {
    // Local variables
    class ObjVector beams; // r1+0x48
    class ObjPtr group; // r1+0x3C
    char discShader[128]; // r1+0x1D8
    class ObjPtr mat; // r1+0x30
    char shader[128]; // r1+0x158
    int steps; // r1+0x2C
    char lensShader[128]; // r1+0xD8
    class Character * dude; // r0

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> static class Symbol bone_pelvis;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> static unsigned int gRev;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BeamDef * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BeamDef * _M_start; // offset 0x0, size 0x4
    struct BeamDef * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8044FF4C -> 0x80450060
void Spotlight::Replace(class Spotlight * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
}

// Range: 0x80450060 -> 0x804500A4
void Spotlight::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804500A4 -> 0x804502BC
void BeamDef::Load(struct BeamDef * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    char shader[128]; // r1+0x30
    class Color color; // r1+0x20

    // References
    // -> static unsigned int gRev;
}

// Range: 0x804502BC -> 0x804510A4
void Spotlight::Copy(class Spotlight * const this /* r29 */, const class Object * from /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class Spotlight * rhs; // r0

    // References
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
}

// Range: 0x804510A4 -> 0x804511C8
void Spotlight::ListDrawChildren(class Spotlight * const this /* r29 */, class list & out /* r31 */) {
    // Local variables
    class iterator it; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804511C8 -> 0x804512F8
class RndDrawable * Spotlight::CollideShowing(class Spotlight * const this /* r27 */, const class Segment & seg /* r28 */, float & dist /* r29 */, class Plane & plane /* r30 */) {
    // Local variables
    class Matrix3 ident; // r1+0x70
    class Matrix3 rot; // r1+0x40
    unsigned char collide; // r0
}

// Range: 0x804512F8 -> 0x80451420
int Spotlight::CollidePlane(class Spotlight * const this /* r29 */, const class Plane & plane /* r30 */) {
    // Local variables
    class Matrix3 ident; // r1+0x70
    class Matrix3 rot; // r1+0x40
    int collide; // r0
}

// Range: 0x80451420 -> 0x80451758
void Spotlight::Poll(class Spotlight * const this /* r31 */) {
    // Local variables
    class Matrix3 m; // r1+0x10
    class RndTransformable * target; // r30

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80451758 -> 0x804517D0
void Spotlight::CloseSlaves() {
    // Local variables
    class iterator slaveIter; // r1+0x20
    class iterator slaveEnd; // r1+0x1C
}

// Range: 0x804517D0 -> 0x80451A44
void Spotlight::UpdateSlaves(class Spotlight * const this /* r30 */) {
    // Local variables
    class iterator slaveIter; // r1+0x28
    class iterator slaveEnd; // r1+0x24
    class Transform slaveToParent; // r1+0x80
    class Transform worldToParent; // r1+0x40
}

// Range: 0x80451A44 -> 0x80451B8C
void Spotlight::UpdateSphere(class Spotlight * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x80451B8C -> 0x80451C40
unsigned char Spotlight::DoFloorSpot() {}

// Range: 0x80451C40 -> 0x80451E48
void Spotlight::SetColorIntensity(class Spotlight * const this /* r30 */, const class Color & c /* r31 */, float i /* f31 */) {
    // Local variables
    class Color newc; // r1+0x20
    class Color oldc; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80451E48 -> 0x80451F44
void Spotlight::SetColor(class Spotlight * const this /* r31 */) {
    // Local variables
    class Color c; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80451F44 -> 0x80451FC4
void Spotlight::SetIntensity(class Spotlight * const this /* r31 */, float i /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80451FC4 -> 0x80452004
void Spotlight::UpdateBounds(class Spotlight * const this /* r31 */) {}

static class Timer * _t; // size: 0x4, address: 0x80A52638
static class Matrix3 ident; // size: 0x30, address: 0x8097F040
static class Matrix3 rot; // size: 0x30, address: 0x8097F070
// Range: 0x80452004 -> 0x80452A7C
void Spotlight::UpdateTransforms(class Spotlight * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    class Vector3 o; // r1+0x150
    class Vector3 o; // r1+0x140
    class Matrix3 m; // r1+0x200
    const struct BeamDef & def; // r0
    class Vector3 o; // r1+0x130
    class Matrix3 m; // r1+0x1D0
    class Matrix3 mo; // r1+0x1A0
    class Vector3 o; // r1+0x120

    // References
    // -> static class Matrix3 rot;
    // -> static class Matrix3 ident;
    // -> static class Timer * _t;
}

// Range: 0x80452A7C -> 0x80452B18
void Spotlight::CheckFloorSpotTransform(class Spotlight * const this /* r30 */) {
    // Local variables
    float targetHeight; // f1
}

// Range: 0x80452B18 -> 0x80452EBC
void Spotlight::UpdateFloorSpotTransform(class Spotlight * const this /* r31 */, const class Transform & worldXfm /* r29 */) {
    // Local variables
    float targetHeight; // f30
    class Vector3 v; // r1+0x20
    float lenZ; // f0
    float lenHypot; // f2
    float scale; // f0
    float vz; // f0
    class Matrix3 m; // r1+0x70
    float t; // f29
}

static class Timer * _t; // size: 0x4, address: 0x80A52640
// Range: 0x80452EBC -> 0x804535E8
void Spotlight::DrawShowing(class Spotlight * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x28
    class Sphere boundingSphere; // r1+0x80
    class Color color; // r1+0x70
    class RndEnvironTracker environTracker; // r1+0x30
    class iterator it; // r1+0x24
    const struct BeamDef & def; // r0
    class Character * c; // r29
    class Vector3 on; // r1+0x60
    class Plane p; // r1+0x50

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9Character;
    // -> class RndMesh * sDiskMesh;
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> class RndEnviron * sEnviron;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
    // -> static class Timer * _t;
}

// Range: 0x804535E8 -> 0x804536B8
void Spotlight::Generate(class Spotlight * const this /* r31 */) {
    // References
    // -> class SpotlightDrawer * sCurrent;
}

// Range: 0x804536B8 -> 0x80453A74
void Spotlight::BuildBoard() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndMesh * sDiskMesh;
}

// Range: 0x80453A74 -> 0x80454324
void Spotlight::BuildNGCone(class Spotlight * const this /* r29 */, struct BeamDef & def /* r30 */, int numSegments /* r31 */) {
    // Local variables
    class Matrix3 ident; // r1+0xD0
    class Matrix3 rot; // r1+0xA0
    unsigned int kNumVerts; // r26
    unsigned int kNumTris; // r18
    unsigned int kTopCap; // r25
    unsigned int kBotCap; // r24
    unsigned int kTopCapCenter; // r26
    unsigned int kBotCapCenter; // r23
    float bottom; // f29
    class Vector2 radii; // r1+0x38
    float dy; // f28
    float fRadiusScaleFactor; // f1
    float topRad; // f27
    float bottomRad; // f26
    unsigned int winding; // r22
    unsigned int nextVert; // r21
    unsigned int nextFace; // r20
    float theta; // f25
    int iSegment; // r19
    float c; // f0
    float s; // f0
    float u; // f24
    float phi; // f23
    unsigned int iSection; // r18
    float section; // f22
    float sideSection; // f1
    float radius; // f2
    int iVert; // r0
    float cosphi; // f0
    float sinphi; // f0
    float x; // f2
    float z; // f0
    float y; // f1
    int iVert; // r0
    unsigned int iSection; // r3
    int iVert0; // r4
    int iVert1; // r5
    int iVert2; // r6
    int iVert3; // r7
    int iVertLast; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

static float midBow; // size: 0x4, address: 0x80A470A8
// Range: 0x80454324 -> 0x80454998
void Spotlight::BuildNGSheet(class Spotlight * const this /* r21 */, struct BeamDef & def /* r22 */) {
    // Local variables
    class Matrix3 ident; // r1+0xD0
    class Matrix3 rot; // r1+0xA0
    int kNumSecVerts; // r26
    int kNumSegVerts; // r25
    int kNumVerts; // r24
    int kNumFaces; // r23
    float kSectionLength; // f0
    class Vector2 radii; // r1+0x38
    float topRad; // f0
    float bottomRad; // f1
    int iVert; // r3
    int vSec; // r4
    float delY; // f11
    int vSeg; // r7
    float delX; // f3
    float y; // f5
    float tX; // f6
    float bX; // f2
    float x; // f6
    float z; // f2
    float intensity; // f12
    int iFace; // r4
    int iSec; // r5
    int iSeg; // r6
    int iBase; // r7
    int idx1; // r8
    int idx2; // r9
    int idx3; // r10

    // References
    // -> static float midBow;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

static int kSideVerts; // size: 0x4, address: 0x80A52648
// Range: 0x80454998 -> 0x80454F28
void Spotlight::BuildNGQuad(class Spotlight * const this /* r25 */, struct BeamDef & def /* r26 */, enum Constraint bboard /* r27 */) {
    // Local variables
    class Matrix3 rot; // r1+0x60
    int numSegs; // r3
    int kNumSegments; // r29
    int kNumFaces; // r28
    float halfHeight; // f9
    float halfWidth; // f10
    int iVert; // r7
    int iy; // r8
    float delY; // f11
    float y; // f12
    int ix; // r9
    float delX; // f13
    float x; // f0
    int iFace; // r4
    int jy; // r5
    int jx; // r6
    int iBase; // r7
    int idx1; // r8
    int idx2; // r9
    int idx3; // r10

    // References
    // -> static int kSideVerts;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

// Range: 0x80454F28 -> 0x80454F8C
void Spotlight::BuildNGShaft() {}

// Range: 0x80454F8C -> 0x80454FA0
void Spotlight::BuildShaft() {}

// Range: 0x80454FA0 -> 0x80455640
void Spotlight::BuildCone(class Spotlight * const this /* r25 */, struct BeamDef & def /* r26 */) {
    // Local variables
    float bb; // r1+0x1C
    float bottom; // f30
    float innerRad; // f29
    float intensity; // f28
    float theta; // f27
    float dy; // f26
    unsigned int i; // r29
    unsigned int i2; // r28
    unsigned int i3; // r27
    float c; // f0
    float s; // f0
    float u; // f4
    unsigned int i2; // r5
    unsigned int i3; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SpotlightDrawer * sCurrent;
}

// Range: 0x80455640 -> 0x80455EA4
void Spotlight::BuildBeam(class Spotlight * const this /* r30 */, struct BeamDef & def /* r31 */) {
    // Local variables
    float tsb; // f31
    float bsb; // f30
    float bb; // f29
    int totalSegments; // r26
    float topLen; // f0
    float r; // f1
    float df; // f4
    float ir; // f2
    float rdelta_t; // f5
    float rdelta_b; // f6
    float drt; // f2
    float drb; // f3
    unsigned int i; // r6
    unsigned int m; // r7
    unsigned int m2; // r8
    unsigned int m3; // r9
    unsigned int m4; // r10
    float a; // f4
    float z; // f8
    int n; // r4
    float v; // f9
    float side; // f7
    float ue; // f10
    unsigned int n; // r11
    unsigned int n2; // r12
    unsigned int n3; // r25
    unsigned int n4; // r24

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SpotlightDrawer * sCurrent;
}

// Range: 0x80455EA4 -> 0x80456070
void Spotlight::Mats(class Spotlight * const this /* r30 */, class list & mats /* r31 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0x18

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80456070 -> 0x80456148
void * BeamDef::BeamDef() {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
}

// Range: 0x80456148 -> 0x80456468
void * BeamDef::BeamDef(struct BeamDef * const this /* r28 */, const struct BeamDef & other /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
}

// Range: 0x80456468 -> 0x80456694
void * BeamDef::~BeamDef(struct BeamDef * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
}

// Range: 0x80456694 -> 0x80456710
void BeamDef::OnSetMat(struct BeamDef * const this /* r30 */, class RndMat * mat /* r31 */) {}

// Range: 0x80456710 -> 0x804567D8
class RndTransformable * Spotlight::ResolveTarget(class Spotlight * const this /* r30 */) {
    // Local variables
    class ObjectDir * dir; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> const char * gNullStr;
}

// Range: 0x804567D8 -> 0x80456844
void Spotlight::SetSubpart(class Spotlight * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80456844 -> 0x80456864
class RndTransformable * Spotlight::GetSubpart() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80456864 -> 0x80456B90
void Spotlight::PropogateToPresets(class Spotlight * const this /* r30 */, int type /* r31 */) {
    // Local variables
    class ObjDirItr preset; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11LightPreset;
}

static class Symbol _s; // size: 0x4, address: 0x80A52650
static class Symbol _s; // size: 0x4, address: 0x80A52658
static class Symbol _s; // size: 0x4, address: 0x80A52660
static class Symbol _s; // size: 0x4, address: 0x80A52668
static class Symbol _s; // size: 0x4, address: 0x80A52670
static class Symbol _s; // size: 0x4, address: 0x80A52678
static class Symbol _s; // size: 0x4, address: 0x80A52680
static class Symbol _s; // size: 0x4, address: 0x80A52688
static class Symbol _s; // size: 0x4, address: 0x80A52690
static class Symbol _s; // size: 0x4, address: 0x80A52698
static class Symbol _s; // size: 0x4, address: 0x80A526A0
static class Symbol _s; // size: 0x4, address: 0x80A526A8
static class Symbol _s; // size: 0x4, address: 0x80A526B0
static class Symbol _s; // size: 0x4, address: 0x80A526B8
static class Symbol _s; // size: 0x4, address: 0x80A526C0
static class Symbol _s; // size: 0x4, address: 0x80A526C8
static class Symbol _s; // size: 0x4, address: 0x80A526D0
static class Symbol _s; // size: 0x4, address: 0x80A526D8
static class Symbol _s; // size: 0x4, address: 0x80A526E0
static class Symbol _s; // size: 0x4, address: 0x80A526E8
static class Symbol _s; // size: 0x4, address: 0x80A526F0
static class Symbol _s; // size: 0x4, address: 0x80A526F8
static class Symbol _s; // size: 0x4, address: 0x80A52700
static class Symbol _s; // size: 0x4, address: 0x80A52708
static class Symbol _s; // size: 0x4, address: 0x80A52710
static class Symbol _s; // size: 0x4, address: 0x80A52718
static class Symbol _s; // size: 0x4, address: 0x80A52720
static class Symbol _s; // size: 0x4, address: 0x80A52728
static class Symbol _s; // size: 0x4, address: 0x80A52730
static class Symbol _s; // size: 0x4, address: 0x80A52738
static class Symbol _s; // size: 0x4, address: 0x80A52740
static class Symbol _s; // size: 0x4, address: 0x80A52748
static class Symbol _s; // size: 0x4, address: 0x80A52750
static class Symbol _s; // size: 0x4, address: 0x80A52758
static class Symbol _s; // size: 0x4, address: 0x80A52760
static class Symbol _s; // size: 0x4, address: 0x80A52768
static class Symbol _s; // size: 0x4, address: 0x80A52770
static class Symbol _s; // size: 0x4, address: 0x80A52778
static class Symbol _s; // size: 0x4, address: 0x80A52780
static class Symbol _s; // size: 0x4, address: 0x80A52788
static class Symbol _s; // size: 0x4, address: 0x80A52790
static class Symbol _s; // size: 0x4, address: 0x80A52798
static class Symbol _s; // size: 0x4, address: 0x80A527A0
static class Symbol _s; // size: 0x4, address: 0x80A527A8
static class Symbol _s; // size: 0x4, address: 0x80A527B0
static class Symbol _s; // size: 0x4, address: 0x80A527B8
// Range: 0x80456B90 -> 0x8045911C
unsigned char Spotlight::SyncProperty(class Spotlight * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__16RndTransformable;
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
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
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

// Range: 0x8045911C -> 0x804597D4
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class RndLight * obj; // r31
    class RndLight * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804597D4 -> 0x80459920
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A527C0
static class Symbol _s; // size: 0x4, address: 0x80A527C8
// Range: 0x80459920 -> 0x8045A12C
class DataNode Spotlight::Handle(class Spotlight * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x124
} __vt__9Spotlight; // size: 0x124, address: 0x808EEDE0
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8RndLight,9ObjectDir>; // size: 0x18, address: 0x808EEF98
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8RndLight,9ObjectDir>; // size: 0x8, address: 0x808EEFE0
struct {
    // total size: 0x18
} __vt__34ObjOwnerPtr<9Spotlight,9ObjectDir>; // size: 0x18, address: 0x808EEFE8
struct {
    // total size: 0x8
} __RTTI__34ObjOwnerPtr<9Spotlight,9ObjectDir>; // size: 0x8, address: 0x808EF030
struct {
    // total size: 0x8
} __RTTI__8RndFlare; // size: 0x8, address: 0x808EF160
struct {
    // total size: 0x8
} __RTTI__PQ29Spotlight7BeamDef; // size: 0x8, address: 0x808EF420

