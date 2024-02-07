/*
    Compile unit: C:\rockband2\system\src\world\Crowd.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804122EC -> 0x80418D74
*/
class DataArray * types; // size: 0x4, address: 0x80A52200
class Symbol name; // size: 0x4, address: 0x80A52208
class vector sPoints; // size: 0xC, address: 0x8097EE64
class vector : protected _Vector_base {
    // total size: 0xC
};
class vector sRemoveSet; // size: 0xC, address: 0x8097EE7C
static class RndCam * gImpostorCamera; // size: 0x4, address: 0x80A5220C
static class RndTex * gImpostorTextures[2]; // size: 0x8, address: 0x8097EE88
static class RndMat * gImpostorMat; // size: 0x4, address: 0x80A52210
static int gNumCrowd; // size: 0x4, address: 0x80A52214
// Range: 0x804122EC -> 0x80412758
void * WorldCrowd::WorldCrowd(class WorldCrowd * const this /* r31 */) {
    // Local variables
    int w; // r29
    int h; // r28
    int bpp; // r27
    int i; // r26

    // References
    // -> static class RndCam * gImpostorCamera;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> class Symbol name;
    // -> static class RndMat * gImpostorMat;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> static class RndTex * gImpostorTextures[2];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> static int gNumCrowd;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__10WorldCrowd;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80412758 -> 0x804127F4
void WorldCrowd::SetMatAndCameraLod(class WorldCrowd * const this /* r30 */) {
    // References
    // -> static class RndMat * gImpostorMat;
    // -> static class RndTex * gImpostorTextures[2];
    // -> static class RndCam * gImpostorCamera;
}

// Range: 0x804127F4 -> 0x80412BDC
void * WorldCrowd::~WorldCrowd(class WorldCrowd * const this /* r29 */) {
    // Local variables
    struct _List_iterator i; // r1+0x40
    int i; // r26

    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> static class RndMat * gImpostorMat;
    // -> static class RndCam * gImpostorCamera;
    // -> static class RndTex * gImpostorTextures[2];
    // -> static int gNumCrowd;
    // -> class vector sRemoveSet;
    // -> class vector sPoints;
    // -> struct [anonymous] __vt__10WorldCrowd;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct pair * _M_start; // offset 0x0, size 0x4
    struct pair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x80412BDC -> 0x80412D7C
void WorldCrowd::CreateMeshes(class WorldCrowd * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14
    class RndMesh * bb; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
    // -> class Symbol name;
}

// Range: 0x80412D7C -> 0x80412E5C
static float EnergyOf() {
    // Local variables
    const class Vector3 & pos; // r0
    struct _List_iterator itr; // r1+0x14
    float e; // f1
    int i; // r9
}

// Range: 0x80412E5C -> 0x80412EEC
static float TotalEnergy(class vector & members /* r30 */) {
    // Local variables
    float e; // f31
    int i; // r31
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80412EEC -> 0x80413DF0
class DataNode WorldCrowd::OnRebuild(class WorldCrowd * const this /* r29 */) {
    // Local variables
    float totalWeight; // f31
    float radius; // f30
    struct _List_iterator i; // r1+0x84
    class vector members; // r1+0xB0
    unsigned int numTries; // r30
    class Transform t; // r1+0xD0
    class Vector3 v1; // r1+0xA0
    class Vector3 v2; // r1+0x90
    float x; // f29
    float y; // f1
    unsigned char collided; // r5
    int j; // r6
    int cur; // r30
    float weight; // f29
    struct _List_iterator i; // r1+0x80
    int num; // r4
    float before; // f29
    int count; // r30
    int i; // r31
    int a; // r0
    int b; // r0
    float after; // f1
    struct _List_iterator i; // r1+0x7C
    int j; // r30
    class ObjDirItr shot; // r1+0xBC

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct CrowdMember {
    // total size: 0x50
    class Transform xfm; // offset 0x0, size 0x40
    struct _List_iterator itr; // offset 0x40, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct CrowdMember * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct CrowdMember * _M_start; // offset 0x0, size 0x4
    struct CrowdMember * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct pair {
    // total size: 0x50
    class Transform first; // offset 0x0, size 0x40
    int second; // offset 0x40, size 0x4
};
// Range: 0x80413DF0 -> 0x80413EA8
void WorldCrowd::CollideList(class WorldCrowd * const this /* r29 */, const class Segment & seg /* r30 */, class list & collisions /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> class LoadMgr TheLoadMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A52218
// Range: 0x80413EA8 -> 0x8041486C
void WorldCrowd::Set3DCharList(class WorldCrowd * const this /* r26 */, const class vector & chars /* r27 */, class Object * setter /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0xD0
    float oldFlat; // f31
    struct _List_iterator i; // r1+0xCC
    class RndMultiMesh * mmesh; // r3
    int kk; // r31
    struct _List_iterator k; // r1+0xC8
    unsigned int j; // r30
    int index; // r4
    unsigned int i; // r30
    int meshIdx; // r7
    struct _List_iterator j; // r1+0xC4
    int jj; // r4
    int xfmIdx; // r29
    struct _List_iterator k; // r1+0xC0
    int kk; // r4
    unsigned int i; // r27
    struct _List_iterator i; // r1+0xBC

    // References
    // -> class Debug TheDebug;
    // -> class vector sRemoveSet;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Timer * _t;
}

struct Sort3DChars {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x8041486C -> 0x80414894
void WorldCrowd::SetUseEnviron() {
    // References
    // -> static class RndMat * gImpostorMat;
}

// Range: 0x80414894 -> 0x80415BD0
void WorldCrowd::DrawShowing(class WorldCrowd * const this /* r24 */) {
    // Local variables
    class RndCam * sceneCam; // r27
    struct _List_iterator i; // r1+0xA4
    class RndMultiMesh * mmesh; // r26
    unsigned int j; // r25
    class Transform t; // r1+0x170
    class Transform tCam; // r1+0x130
    float halfHeight; // f31
    float halfWidth; // f30
    float length; // f29
    float fov; // f0
    class Transform tDude; // r1+0xF0
    float minY; // r1+0xA0
    float maxY; // r1+0x9C
    float minX; // r1+0x98
    float maxX; // r1+0x94
    unsigned int j; // r25
    class Vector2 screen; // r1+0xB0
    float centerX; // f3
    float centerY; // f2
    class Vector3 pos; // r1+0xE0
    class RndEnvironTracker _rndEnvironTracker; // r1+0xA8
    float hz0; // f2
    float hz1; // f1
    float hx0; // f3
    float hx1; // f4

    // References
    // -> const char * kAssertStr;
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class vector sPoints;
    // -> static class RndCam * gImpostorCamera;
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
}

// Range: 0x80415BD0 -> 0x80415F44
class RndMesh * WorldCrowd::BuildBillboard(float charHeight /* f30 */) {
    // Local variables
    float rad; // f0
    float hz; // f31
    float hx; // f30

    // References
    // -> static class RndCam * gImpostorCamera;
    // -> static class RndMat * gImpostorMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

// Range: 0x80415F44 -> 0x80415F64
void WorldCrowd::SetLod() {}

static class Timer * _t; // size: 0x4, address: 0x80A52220
// Range: 0x80415F64 -> 0x80416438
void WorldCrowd::SetFullness(class WorldCrowd * const this /* r28 */, float flat /* f30 */, float full /* f31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x90
    struct _List_iterator i; // r1+0x8C
    int totalSize; // r5
    int currSize; // r30
    int newSize; // r29
    struct _List_iterator j; // r1+0x88
    struct _List_iterator j; // r1+0x84

    // References
    // -> static class Timer * _t;
}

static int sRev; // size: 0x4, address: 0x80A52228
// Range: 0x80416438 -> 0x8041647C
void WorldCrowd::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8041647C -> 0x804166A4
void WorldCrowd::Load(class WorldCrowd * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x1C
    int seed; // r1+0x18
    struct _List_iterator i; // r1+0x14
    class list lst; // r1+0x38

    // References
    // -> static int sRev;
}

// Range: 0x804166A4 -> 0x8041676C
void WorldCrowd::OnSetPlacementMesh(class WorldCrowd * const this /* r30 */, class RndMesh * mesh /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8041676C -> 0x8041683C
void WorldCrowd::ListDrawChildren(class WorldCrowd * const this /* r29 */, class list & out /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>; // size: 0x8, address: 0x808E9E58
// Range: 0x8041683C -> 0x804168BC
void WorldCrowd::UpdateSphere(class WorldCrowd * const this /* r31 */) {
    // Local variables
    class Sphere s; // r1+0x10
}

// Range: 0x804168BC -> 0x804169D4
unsigned char WorldCrowd::MakeWorldSphere(class WorldCrowd * const this /* r30 */, class Sphere & s /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class RndMultiMesh * mmesh; // r3
    class Sphere s2; // r1+0x20
}

// Range: 0x804169D4 -> 0x80416AAC
void WorldCrowd::ListPollChildren(const class WorldCrowd * const this /* r29 */, class list & out /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80416AAC -> 0x80416B30
void WorldCrowd::Poll(class WorldCrowd * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x80416B30 -> 0x80416BBC
void WorldCrowd::Enter(class WorldCrowd * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x80416BBC -> 0x80416C3C
void WorldCrowd::Exit(class WorldCrowd * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x80416C3C -> 0x80416CF0
void WorldCrowd::Mats(class WorldCrowd * const this /* r30 */, class list & mats /* r31 */) {
    // Local variables
    struct MatShaderOptions opts; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class RndMat * gImpostorMat;
}

// Range: 0x80416CF0 -> 0x80416D5C
void * CharData::CharData(struct CharData * const this /* r31 */) {}

// Range: 0x80416D5C -> 0x80416D60
void CharData::Load() {}

// Range: 0x80416D60 -> 0x80416DB4
void * CharDef::CharDef() {
    // References
    // -> struct [anonymous] __vt__29ObjPtr<9Character,9ObjectDir>;
}

// Range: 0x80416DB4 -> 0x80416E30
void CharDef::Load(class CharDef * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> static int sRev;
}

static class Symbol _s; // size: 0x4, address: 0x80A52230
static class Symbol _s; // size: 0x4, address: 0x80A52238
static class Symbol _s; // size: 0x4, address: 0x80A52240
// Range: 0x80416E30 -> 0x80417718
class DataNode WorldCrowd::Handle(class WorldCrowd * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Timer * _t; // size: 0x4, address: 0x80A52244
// Range: 0x80417718 -> 0x80417A60
class DataNode WorldCrowd::OnIterateFrac(class WorldCrowd * const this /* r30 */, class DataArray * a /* r29 */) {
    // Local variables
    class AutoTimer _at; // r1+0x18
    class Character * chars[64]; // r1+0x28
    int num; // r31
    struct _List_iterator i; // r1+0x14
    int i; // r30
    float sum; // f31
    int i; // r27
    float frac; // f0
    float fTotal; // f30
    int total; // r30
    float isum; // f31
    int i; // r27

    // References
    // -> static class Timer * _t;
}

static class WorldCrowd * gParent; // size: 0x4, address: 0x80A5224C
static class Symbol _s; // size: 0x4, address: 0x80A52254
static class Symbol _s; // size: 0x4, address: 0x80A5225C
static class Symbol _s; // size: 0x4, address: 0x80A52264
static class Symbol _s; // size: 0x4, address: 0x80A5226C
// Range: 0x80417A60 -> 0x80417DF8
unsigned char PropSync(struct CharData & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A52274
static class Symbol _s; // size: 0x4, address: 0x80A5227C
static class Symbol _s; // size: 0x4, address: 0x80A52284
static class Symbol _s; // size: 0x4, address: 0x80A5228C
static class Symbol _s; // size: 0x4, address: 0x80A52294
static class Symbol _s; // size: 0x4, address: 0x80A5229C
// Range: 0x80417DF8 -> 0x80418294
unsigned char WorldCrowd::SyncProperty(class WorldCrowd * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class WorldCrowd * gParent;
}

// Range: 0x80418294 -> 0x80418BF4
unsigned char PropSync(class ObjList & v /* r26 */, class DataNode & n /* r30 */, class DataArray * prop /* r27 */, int i /* r28 */, enum PropOp op /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0xD8
    struct CharData tmp; // r1+0xF8

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18pair<9Transform,i>;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<Q210WorldCrowd8CharData>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__29ObjPtr<9Character,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std18pair<9Transform,i>; // size: 0x8, address: 0x808E9FF8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std35_List_node<Q210WorldCrowd8CharData>; // size: 0x8, address: 0x808EA030
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndDrawable * _M_data; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0xF0
} __vt__10WorldCrowd; // size: 0xF0, address: 0x808EA0A0
struct {
    // total size: 0x8
} __RTTI__P11CrowdMember; // size: 0x8, address: 0x808EA678
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std111pair<P12RndMultiMesh,Q211stlpmtx_std72_List_iterator<9Transform,Q211stlpmtx_std28_Nonconst_traits<9Transform>>>; // size: 0x8, address: 0x808EA6F8
// Range: 0x80418BF4 -> 0x80418C6C
static void __sinit_\Crowd_cpp() {
    // References
    // -> class vector sRemoveSet;
    // -> class vector sPoints;
}


