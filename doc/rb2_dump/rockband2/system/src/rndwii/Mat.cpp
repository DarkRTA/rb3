/*
    Compile unit: C:\rockband2\system\src\rndwii\Mat.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8054DF0C -> 0x8054FD90
*/
class DataArray * types; // size: 0x4, address: 0x80A53E60
class Symbol name; // size: 0x4, address: 0x80A53E68
class WiiMat * sCurrent; // size: 0x4, address: 0x80A53E6C
enum _GXLightID sLightIds; // size: 0x4, address: 0x80A53E70
unsigned char sLightPoint; // size: 0x1, address: 0x80A53E74
const class Transform * sCurrentModelXfm; // size: 0x4, address: 0x80A53E78
unsigned char sCurrentZCompLoc; // size: 0x1, address: 0x80A47560
class RndTex * sGradientTex; // size: 0x4, address: 0x80A53E7C
unsigned char sOverrideAlphaWrite; // size: 0x1, address: 0x80A53E80
static enum _GXTevStageID op[16]; // size: 0x40, address: 0x808496D8
enum _GXTevStageID {
    GX_TEVSTAGE0 = 0,
    GX_TEVSTAGE1 = 1,
    GX_TEVSTAGE2 = 2,
    GX_TEVSTAGE3 = 3,
    GX_TEVSTAGE4 = 4,
    GX_TEVSTAGE5 = 5,
    GX_TEVSTAGE6 = 6,
    GX_TEVSTAGE7 = 7,
    GX_TEVSTAGE8 = 8,
    GX_TEVSTAGE9 = 9,
    GX_TEVSTAGE10 = 10,
    GX_TEVSTAGE11 = 11,
    GX_TEVSTAGE12 = 12,
    GX_TEVSTAGE13 = 13,
    GX_TEVSTAGE14 = 14,
    GX_TEVSTAGE15 = 15,
    GX_MAX_TEVSTAGE = 16,
};
// Range: 0x8054DF0C -> 0x8054DF90
static enum _GXTevStageID StageId(int i /* r31 */) {
    // References
    // -> static enum _GXTevStageID op[16];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static enum _GXTexCoordID op[8]; // size: 0x20, address: 0x80849718
// Range: 0x8054DF90 -> 0x8054E014
static enum _GXTexCoordID TexCoordId(int i /* r31 */) {
    // References
    // -> static enum _GXTexCoordID op[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static enum _GXTexMapID op[8]; // size: 0x20, address: 0x80849738
// Range: 0x8054E014 -> 0x8054E098
static enum _GXTexMapID TexMapId(int i /* r31 */) {
    // References
    // -> static enum _GXTexMapID op[8];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8054E098 -> 0x8054E204
void WiiMat::Init() {
    // Local variables
    const char * bitmapFile; // r31

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> class RndTex * sGradientTex;
    // -> class Symbol name;
}

static class Timer * _t; // size: 0x4, address: 0x80A53E84
static struct _GXColor white; // size: 0x4, address: 0x80A57940
// Range: 0x8054E204 -> 0x8054E7C8
void WiiMat::SelectParticles(class WiiMat * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x18
    enum _GXTevStageID id; // r29
    unsigned char localHasAlphaTexture; // r28
    class WiiTex * tex; // r27

    // References
    // -> static struct _GXColor white;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndEnviron * sCurrent;
    // -> static class Timer * _t;
    // -> class WiiMat * sCurrent;
}

static class Timer * _t; // size: 0x4, address: 0x80A53E8C
// Range: 0x8054E7C8 -> 0x8054ED18
class WiiMat * WiiMat::Select(class WiiMat * const this /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0x3C
    struct _GXColor clear; // r1+0x38
    class WiiEnviron * env; // r30
    int numLightChannels; // r29
    class Color ambCol; // r1+0x60
    struct _GXColor cMat; // r1+0x34
    struct _GXColor cAmb; // r1+0x30
    class Color diffuse_col; // r1+0x50
    enum _GXLightID lightIds; // r27
    enum Blend b; // r27
    int tex; // r1+0x2C
    int tev; // r1+0x28

    // References
    // -> unsigned char sOverrideAlphaWrite;
    // -> unsigned char sLightPoint;
    // -> enum _GXLightID sLightIds;
    // -> class WiiRnd TheWiiRnd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndCam * sCurrent;
    // -> class RndEnviron * sCurrent;
    // -> static class Timer * _t;
    // -> class NgStats * TheNgStats;
    // -> class WiiMat * sCurrent;
}

// Range: 0x8054ED18 -> 0x8054EDA8
void WiiMat::SetAlphaCutout(unsigned char enable /* r31 */) {
    // References
    // -> unsigned char sCurrentZCompLoc;
}

// Range: 0x8054EDA8 -> 0x8054EE28
void WiiMat::SetZBufferMode() {}

// Range: 0x8054EE28 -> 0x8054EF58
void WiiMat::SetFrameBlend() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8054EF58 -> 0x8054F21C
void WiiMat::SetFog(class RndEnviron * env /* r30 */, class RndCam * cam /* r31 */) {
    // Local variables
    struct _GXColor col; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8054F21C -> 0x8054F57C
void WiiMat::SetTexGen(class WiiMat * const this /* r30 */, enum _GXTexCoordID coord /* r31 */) {
    // Local variables
    class Transform t; // r1+0xC0
    class Transform t2; // r1+0x80
    float xfm[3][4]; // r1+0x50
    class Vector3 euler; // r1+0x10
    class Matrix3 m; // r1+0x20

    // References
    // -> const class Transform * sCurrentModelXfm;
}

enum _GXTevColorArg {
    GX_CC_CPREV = 0,
    GX_CC_APREV = 1,
    GX_CC_C0 = 2,
    GX_CC_A0 = 3,
    GX_CC_C1 = 4,
    GX_CC_A1 = 5,
    GX_CC_C2 = 6,
    GX_CC_A2 = 7,
    GX_CC_TEXC = 8,
    GX_CC_TEXA = 9,
    GX_CC_RASC = 10,
    GX_CC_RASA = 11,
    GX_CC_ONE = 12,
    GX_CC_HALF = 13,
    GX_CC_KONST = 14,
    GX_CC_ZERO = 15,
};
enum _GXTevAlphaArg {
    GX_CA_APREV = 0,
    GX_CA_A0 = 1,
    GX_CA_A1 = 2,
    GX_CA_A2 = 3,
    GX_CA_TEXA = 4,
    GX_CA_RASA = 5,
    GX_CA_KONST = 6,
    GX_CA_ZERO = 7,
};
// Range: 0x8054F57C -> 0x8054FA98
void WiiMat::SetStageState(class WiiMat * const this /* r21 */, int & tex /* r22 */, int & tev /* r23 */, int numLightChannels /* r24 */) {
    // Local variables
    enum _GXTevStageID id; // r24
    enum _GXTevColorArg prevColor; // r21
    enum _GXTevAlphaArg prevAlpha; // r22
    enum _GXTexMapID texmap; // r28
    enum _GXTexCoordID coord; // r27
    class WiiTex * pTex; // r26
    enum _GXTevColorArg prevColor; // r20
    enum _GXTevAlphaArg prevAlpha; // r19
    enum _GXTevColorArg texColor; // r25

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8054FA98 -> 0x8054FD90
void WiiMat::SetFade(int & tex /* r29 */, int & tev /* r26 */, class RndEnviron * env /* r27 */, class RndCam * cam /* r28 */) {
    // Local variables
    enum _GXTevStageID id; // r31
    enum _GXTexCoordID coord; // r30
    enum _GXTexMapID texmap; // r29
    float viewXfm[3][4]; // r1+0xA0
    float modelXfm[3][4]; // r1+0x70
    float mvXfm[3][4]; // r1+0x40
    float fade[3][4]; // r1+0x10
    struct _GXColor fademax; // r1+0xC

    // References
    // -> class RndTex * sGradientTex;
    // -> const class Transform * sCurrentModelXfm;
}

struct {
    // total size: 0x54
} __vt__6WiiMat; // size: 0x54, address: 0x809177D8
struct {
    // total size: 0x8
} __RTTI__6WiiMat; // size: 0x8, address: 0x80917850

