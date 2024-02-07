/*
    Compile unit: C:\rockband2\system\src\rndwii\Env.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8054D644 -> 0x8054D7CC
*/
class DataArray * types; // size: 0x4, address: 0x80A53E38
class Symbol name; // size: 0x4, address: 0x80A53E40
static enum _GXLightID lightId[8]; // size: 0x20, address: 0x80917520
enum _GXLightID {
    GX_LIGHT0 = 1,
    GX_LIGHT1 = 2,
    GX_LIGHT2 = 4,
    GX_LIGHT3 = 8,
    GX_LIGHT4 = 16,
    GX_LIGHT5 = 32,
    GX_LIGHT6 = 64,
    GX_LIGHT7 = 128,
    GX_MAX_LIGHT = 256,
    GX_LIGHT_NULL = 0,
};
// Range: 0x8054D644 -> 0x8054D658
static enum _GXLightID LightId() {
    // References
    // -> static enum _GXLightID lightId[8];
}

// Range: 0x8054D658 -> 0x8054D690
void WiiEnviron::Select(class WiiEnviron * const this /* r31 */) {}

// Range: 0x8054D690 -> 0x8054D7CC
void WiiEnviron::UpdateLights(class WiiEnviron * const this /* r28 */) {
    // Local variables
    enum _GXLightID lightIds; // [invalid]
    unsigned char pointLight; // r31
    class RndLight * light; // r29
    enum _GXLightID id; // r30
    int numDirLightsFound; // r29
    class iterator it; // r1+0x18
    enum Type type; // r0
    enum _GXLightID id; // r28

    // References
    // -> class WiiMat * sCurrent;
    // -> unsigned char sLightPoint;
    // -> enum _GXLightID sLightIds;
    // -> class NgStats * TheNgStats;
}

struct VColTex {
    // total size: 0x8
    unsigned int col; // offset 0x0, size 0x4
    signed short tex[2]; // offset 0x4, size 0x4
};
struct VPosNrm {
    // total size: 0x10
    float pos[3]; // offset 0x0, size 0xC
    signed char nrm[3]; // offset 0xC, size 0x3
};
enum _GXAttrType {
    GX_NONE = 0,
    GX_DIRECT = 1,
    GX_INDEX8 = 2,
    GX_INDEX16 = 3,
};
enum _GXPrimitive {
    GX_POINTS = 184,
    GX_LINES = 168,
    GX_LINESTRIP = 176,
    GX_TRIANGLES = 144,
    GX_TRIANGLESTRIP = 152,
    GX_TRIANGLEFAN = 160,
    GX_QUADS = 128,
};
enum _GXVtxFmt {
    GX_VTXFMT0 = 0,
    GX_VTXFMT1 = 1,
    GX_VTXFMT2 = 2,
    GX_VTXFMT3 = 3,
    GX_VTXFMT4 = 4,
    GX_VTXFMT5 = 5,
    GX_VTXFMT6 = 6,
    GX_VTXFMT7 = 7,
    GX_MAX_VTXFMT = 8,
};
class DisplayList {
    // total size: 0xC
    char * mData; // offset 0x0, size 0x4
    int mSize; // offset 0x4, size 0x4
    int mNumMeshVerts; // offset 0x8, size 0x4
};
class WiiMesh : public RndMesh {
    // total size: 0x1B0
    struct VColTex * mCTVtxs; // offset 0x14C, size 0x4
    struct VPosNrm * mPNVtxs; // offset 0x150, size 0x4
    float * mWeights; // offset 0x154, size 0x4
    unsigned char mSetVertexBuffersFailed; // offset 0x158, size 0x1
    unsigned short mNumVerts; // offset 0x15A, size 0x2
    unsigned short mNumFaces; // offset 0x15C, size 0x2
    class DisplayList mDList; // offset 0x160, size 0xC
    unsigned short mNumBones; // offset 0x16C, size 0x2
};
struct _GXLightObj {
    // total size: 0x40
    unsigned long dummy[16]; // offset 0x0, size 0x40
};
class WiiLight : public RndLight {
    // total size: 0x190
    struct _GXLightObj mLight; // offset 0x114, size 0x40
    unsigned char mLitDirty; // offset 0x154, size 0x1
};
struct {
    // total size: 0x64
} __vt__10WiiEnviron; // size: 0x64, address: 0x80917540
struct {
    // total size: 0x8
} __RTTI__10WiiEnviron; // size: 0x8, address: 0x809175D0
enum _GXTexCoordID {
    GX_TEXCOORD0 = 0,
    GX_TEXCOORD1 = 1,
    GX_TEXCOORD2 = 2,
    GX_TEXCOORD3 = 3,
    GX_TEXCOORD4 = 4,
    GX_TEXCOORD5 = 5,
    GX_TEXCOORD6 = 6,
    GX_TEXCOORD7 = 7,
    GX_MAX_TEXCOORD = 8,
    GX_TEXCOORD_NULL = 255,
};
class WiiMat : public RndMat {
    // total size: 0x120
};

