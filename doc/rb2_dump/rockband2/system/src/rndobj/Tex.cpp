/*
    Compile unit: C:\rockband2\system\src\rndobj\Tex.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804FE050 -> 0x805006CC
*/
class DataArray * types; // size: 0x4, address: 0x80A53930
class RndTex * textureTrackingList[1024]; // size: 0x1000, address: 0x80980718
int textureTrackingCount; // size: 0x4, address: 0x80A53938
unsigned char textureTrackingActive; // size: 0x1, address: 0x80A5393C
// Range: 0x804FE050 -> 0x804FE0D4
unsigned char UseBottomMip() {
    // Local variables
    class DataArray * use; // r31
}

// Range: 0x804FE0D4 -> 0x804FE168
void CopyBottomMip(class RndBitmap & dst /* r30 */, const class RndBitmap & src /* r31 */) {
    // Local variables
    const class RndBitmap * bm; // [invalid]

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804FE168 -> 0x804FE28C
void * RndTex::RndTex(class RndTex * const this /* r31 */) {
    // Local variables
    int x; // r5

    // References
    // -> int textureTrackingCount;
    // -> class RndTex * textureTrackingList[1024];
    // -> unsigned char textureTrackingActive;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__6RndTex;
}

// Range: 0x804FE28C -> 0x804FE380
void * RndTex::~RndTex(class RndTex * const this /* r30 */) {
    // Local variables
    int x; // r5

    // References
    // -> int textureTrackingCount;
    // -> class RndTex * textureTrackingList[1024];
    // -> struct [anonymous] __vt__6RndTex;
}

// Range: 0x804FE380 -> 0x804FE51C
void RndTex::PlatformBppOrder(int & bpp /* r31 */, int & order /* r27 */, unsigned char hasAlpha /* r28 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x804FE51C -> 0x804FE6E0
void RndTex::SetBitmap(class RndTex * const this /* r31 */, int width /* r25 */, int height /* r26 */, int bpp /* r27 */, enum Type type /* r30 */, unsigned char useMips /* r28 */, const char * path /* r29 */) {
    // Local variables
    int width; // r4
    int height; // r5
    const char * err; // r0
    int bpp; // r1+0x14
    int order; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> class Rnd & TheRnd;
    // -> class FilePath sRoot;
}

// Range: 0x804FE6E0 -> 0x804FE80C
void RndTex::SetBitmap(class RndTex * const this /* r29 */, const class RndBitmap & bm /* r30 */, const char * path /* r31 */) {
    // Local variables
    const char * err; // r0
    int bpp; // r1+0xC
    int order; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> class FilePath sRoot;
}

// Range: 0x804FE80C -> 0x804FEA14
void RndTex::SetBitmap(class RndTex * const this /* r31 */, class FileLoader * l /* r28 */) {
    // Local variables
    char * buffer; // r29
    class RndBitmap tmp; // r1+0x14

    // References
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x804FEA14 -> 0x804FEA74
void RndTex::SetBitmap(class RndTex * const this /* r31 */) {
    // Local variables
    class Loader * l; // r0

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x804FEA74 -> 0x804FEB40
static char * CheckDim() {
    // Local variables
    const char * err; // r7
}

// Range: 0x804FEB40 -> 0x804FEC6C
char * RndTex::CheckSize(int width /* r24 */, int height /* r25 */, int bpp /* r26 */, int numMips /* r27 */, enum Type type /* r28 */, unsigned char file /* r29 */) {
    // Local variables
    const char * err; // r30
    int bytes; // r29
}

// Range: 0x804FEC6C -> 0x804FECDC
unsigned char RndTex::PowerOf2() {}

// Range: 0x804FECDC -> 0x804FED4C
void RndTex::LockBitmap(class RndTex * const this /* r10 */) {}

static int TEX_REV; // size: 0x4, address: 0x80A47408
// Range: 0x804FED4C -> 0x804FED90
void RndTex::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804FED90 -> 0x804FEDEC
void RndTex::Load(class RndTex * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A53940
// Range: 0x804FEDEC -> 0x804FEF90
void RndTex::PreLoad(class RndTex * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int TEX_REV;
    // -> static int gRev;
}

// Range: 0x804FEF90 -> 0x804FF1F8
void RndTex::PostLoad(class RndTex * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int mipmapK; // r1+0x10
    enum Type types[5]; // r1+0x14
    int type; // r1+0xC
    unsigned char useMips; // r8
    class RndBitmap tmp; // r1+0x28

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> static int gRev;
}

// Range: 0x804FF1F8 -> 0x804FF304
void RndTex::Copy(class RndTex * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndTex * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
}

// Range: 0x804FF304 -> 0x804FF424
static class TextStream & __ls(class TextStream & d /* r31 */) {}

// Range: 0x804FF424 -> 0x804FF534
void RndTex::Print(class RndTex * const this /* r28 */) {
    // References
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A53948
static class Symbol _s; // size: 0x4, address: 0x80A53950
static class Symbol _s; // size: 0x4, address: 0x80A53958
static class Symbol _s; // size: 0x4, address: 0x80A53960
static class Symbol _s; // size: 0x4, address: 0x80A53968
static class Symbol _s; // size: 0x4, address: 0x80A53970
static class Symbol _s; // size: 0x4, address: 0x80A53978
// Range: 0x804FF534 -> 0x804FFF84
class DataNode RndTex::Handle(class RndTex * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804FFF84 -> 0x80500078
class DataNode RndTex::OnSaveBmp(class RndTex * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class RndBitmap bm; // r1+0x2C
    class RndBitmap bm2; // r1+0x8
}

// Range: 0x80500078 -> 0x805001C8
class DataNode RndTex::OnSetBitmap(class RndTex * const this /* r26 */, const class DataArray * a /* r27 */) {
    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805001C8 -> 0x8050026C
class DataNode RndTex::OnSetRendered(class RndTex * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A53980
static class Symbol _s; // size: 0x4, address: 0x80A53988
static class Symbol _s; // size: 0x4, address: 0x80A53990
static class Symbol _s; // size: 0x4, address: 0x80A53998
// Range: 0x8050026C -> 0x805006CC
unsigned char RndTex::SyncProperty(class RndTex * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x78
} __vt__6RndTex; // size: 0x78, address: 0x809013C8

