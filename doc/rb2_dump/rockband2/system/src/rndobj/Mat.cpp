/*
    Compile unit: C:\rockband2\system\src\rndobj\Mat.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804AD320 -> 0x804B10FC
*/
class DataArray * types; // size: 0x4, address: 0x80A530A8
class RndMat * materialTrackingList[1024]; // size: 0x1000, address: 0x8097F2A0
int materialTrackingCount; // size: 0x4, address: 0x80A530B0
unsigned char materialTrackingActive; // size: 0x1, address: 0x80A530B4
// Range: 0x804AD320 -> 0x804AD330
void * MatShaderOptions::MatShaderOptions() {}

// Range: 0x804AD330 -> 0x804AD4B8
class RndMat * LookupOrCreateMat(const char * shader /* r26 */, class ObjectDir * dir /* r27 */) {
    // Local variables
    const char * matName; // r29
    class RndMat * mat; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Symbol name;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x804AD4B8 -> 0x804AD6C4
void * RndMat::RndMat(class RndMat * const this /* r31 */) {
    // Local variables
    int x; // r5

    // References
    // -> int materialTrackingCount;
    // -> class RndMat * materialTrackingList[1024];
    // -> unsigned char materialTrackingActive;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__6RndMat;
}

// Range: 0x804AD6C4 -> 0x804AD7F8
void * RndMat::~RndMat(class RndMat * const this /* r30 */) {
    // Local variables
    int x; // r6

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> int materialTrackingCount;
    // -> class RndMat * materialTrackingList[1024];
}

static int MAT_REV; // size: 0x4, address: 0x80A47248
// Range: 0x804AD7F8 -> 0x804AD83C
void RndMat::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A530B8
// Range: 0x804AD83C -> 0x804AD860
void RndMat::MakeWhite() {}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndCubeTex * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndFur * mPtr; // offset 0x8, size 0x4
};
// Range: 0x804AD860 -> 0x804AE180
void RndMat::Load(class RndMat * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    float mEmissiveMultiplier; // r1+0x48
    class Color mSpecular; // r1+0xB0
    class ObjPtr mNormalMap; // r1+0xA0
    class ObjPtr mEmissiveMap; // r1+0x94
    class ObjPtr mSpecularMap; // r1+0x88
    class ObjPtr mEnvironMap; // r1+0x7C
    class ObjPtr mFur; // r1+0x70
    float mDeNormal; // r1+0x44
    float mAnisotropy; // r1+0x40
    float mNormDetailTile; // r1+0x3C
    float mNormDetailStrength; // r1+0x38
    float mNormDetail; // r1+0x34
    class Symbol customShader; // r1+0x30
    float temp_float; // r1+0x2C
    class Color temp_color; // r1+0x60
    class ObjPtr temp; // r1+0x4C
    int temp; // r1+0x28

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static int MAT_REV;
    // -> static int gRev;
    // -> struct [anonymous] __vt__26ObjPtr<6RndFur,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndCubeTex,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
}

// Range: 0x804AE180 -> 0x804AE4F4
void RndMat::Copy(class RndMat * const this /* r30 */, const class Object * o /* r28 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndMat * m; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x804AE4F4 -> 0x804AE8EC
void RndMat::CompositeTwoColor(class RndMat * const this /* r27 */) {
    // Local variables
    class RndBitmap base_bmp; // r1+0x78
    class RndBitmap mask_bmp; // r1+0x54
    float mask_scale_x; // f3
    float mask_scale_y; // f31
    class RndBitmap composite_bmp; // r1+0x30
    int bpp; // r1+0x14
    int order; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804AE8EC -> 0x804AEAA0
void RndMat::FinalizeTwoColor(class RndMat * const this /* r30 */) {
    // Local variables
    class RndBitmap diffuse_bmp; // r1+0x44
    class RndBitmap diffuse_dxt; // r1+0x20
}

static class Symbol _s; // size: 0x4, address: 0x80A530C0
static class Symbol _s; // size: 0x4, address: 0x80A530C8
// Range: 0x804AEAA0 -> 0x804AEFF4
class DataNode RndMat::Handle(class RndMat * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804AEFF4 -> 0x804AF4FC
class DataNode RndMat::OnAllowedNextPass(class RndMat * const this /* r30 */) {
    // Local variables
    class DataArrayPtr da; // r1+0x30
    int n; // r31
    class ObjDirItr it; // r1+0x38
    unsigned char allow; // r3
    class RndMat * p; // r4

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndTex * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x804AF4FC -> 0x804AF9BC
class DataNode RndMat::OnAllowedNormalMap(class RndMat * const this /* r29 */) {
    // Local variables
    class DataArrayPtr da; // r1+0x28
    int n; // r31
    class ObjDirItr it; // r1+0x3C
    class FilePath p; // r1+0x30

    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class Symbol _s; // size: 0x4, address: 0x80A530D0
static class Symbol _s; // size: 0x4, address: 0x80A530D8
static class Symbol _s; // size: 0x4, address: 0x80A530E0
static class Symbol _s; // size: 0x4, address: 0x80A530E8
static class Symbol _s; // size: 0x4, address: 0x80A530F0
static class Symbol _s; // size: 0x4, address: 0x80A530F8
static class Symbol _s; // size: 0x4, address: 0x80A53100
static class Symbol _s; // size: 0x4, address: 0x80A53108
static class Symbol _s; // size: 0x4, address: 0x80A53110
static class Symbol _s; // size: 0x4, address: 0x80A53118
static class Symbol _s; // size: 0x4, address: 0x80A53120
static class Symbol _s; // size: 0x4, address: 0x80A53128
static class Symbol _s; // size: 0x4, address: 0x80A53130
static class Symbol _s; // size: 0x4, address: 0x80A53138
static class Symbol _s; // size: 0x4, address: 0x80A53140
static class Symbol _s; // size: 0x4, address: 0x80A53148
static class Symbol _s; // size: 0x4, address: 0x80A53150
static class Symbol _s; // size: 0x4, address: 0x80A53158
static class Symbol _s; // size: 0x4, address: 0x80A53160
static class Symbol _s; // size: 0x4, address: 0x80A53168
static class Symbol _s; // size: 0x4, address: 0x80A53170
static class Symbol _s; // size: 0x4, address: 0x80A53178
static class Symbol _s; // size: 0x4, address: 0x80A53180
static class Symbol _s; // size: 0x4, address: 0x80A53188
static class Symbol _s; // size: 0x4, address: 0x80A53190
static class Symbol _s; // size: 0x4, address: 0x80A53198
// Range: 0x804AF9BC -> 0x804B10FC
unsigned char RndMat::SyncProperty(class RndMat * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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

struct {
    // total size: 0x18
} __vt__26ObjPtr<6RndFur,9ObjectDir>; // size: 0x18, address: 0x808F9888
struct {
    // total size: 0x8
} __RTTI__26ObjPtr<6RndFur,9ObjectDir>; // size: 0x8, address: 0x808F98C8
struct {
    // total size: 0x18
} __vt__31ObjPtr<10RndCubeTex,9ObjectDir>; // size: 0x18, address: 0x808F98D0
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10RndCubeTex,9ObjectDir>; // size: 0x8, address: 0x808F9918
struct {
    // total size: 0x54
} __vt__6RndMat; // size: 0x54, address: 0x808F9920

