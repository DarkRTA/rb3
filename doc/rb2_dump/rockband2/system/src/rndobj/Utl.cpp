/*
    Compile unit: C:\rockband2\system\src\rndobj\Utl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8051B96C -> 0x8051EF7C
*/
// Range: 0x8051B96C -> 0x8051BA64
class RndGroup * GroupOwner(class Object * o /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x30
    class RndGroup * g; // r3

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x8051BA64 -> 0x8051BB1C
unsigned char GroupedUnder(class Object * o /* r31 */) {
    // Local variables
    class iterator i; // r1+0x18
    class RndGroup * ig; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x8051BB1C -> 0x8051BBEC
unsigned char AnimContains(const class RndAnimatable * anim /* r31 */) {
    // Local variables
    class list children; // r1+0x30
    struct _List_iterator it; // r1+0x18
}

// Range: 0x8051BBEC -> 0x8051BCB8
class RndAnimatable * AnimController(class Object * o /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class RndAnimatable * a; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

// Range: 0x8051BCB8 -> 0x8051BD38
class RndMat * GetMat() {
    // Local variables
    class list mats; // r1+0x20
}

// Range: 0x8051BD38 -> 0x8051BDE0
unsigned char SortDraws(class RndDrawable * a /* r29 */, class RndDrawable * b /* r30 */) {
    // Local variables
    class RndMat * mata; // r0
    class RndMat * matb; // r0
}

static class Symbol CharTransCopy; // size: 0x4, address: 0x80A53C54
// Range: 0x8051BDE0 -> 0x8051BEE8
unsigned char SortPolls(const class RndPollable * a /* r30 */, const class RndPollable * b /* r31 */) {
    // Local variables
    float aweight; // f0
    float bweight; // f0

    // References
    // -> static class Symbol CharTransCopy;
}

// Range: 0x8051BEE8 -> 0x8051C084
void CalcBox(class RndMesh * m /* r29 */, class Box & b /* r30 */) {
    // Local variables
    class Vert * v; // r31
    class Vector3 p; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8051C084 -> 0x8051C3C4
void CalcSphere(class RndTransAnim * ta /* r30 */, class Sphere & s /* r31 */) {
    // Local variables
    class RndTransformable * parent; // r29
    class Box b; // r1+0x40
    class Vector3 v; // r1+0x30
    class Key * i; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8051C3C4 -> 0x8051C534
void AddMotionSphere(class RndTransformable * o /* r30 */, class Sphere & s /* r31 */) {
    // Local variables
    class RndTransAnim * ta; // r0
    class Sphere s2; // r1+0x10

    // References
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x8051C534 -> 0x8051CAA8
void RandomPointOnMesh(const class RndMesh * mesh /* r28 */, class Vector3 & pos /* r29 */, class Vector3 & norm /* r30 */) {
    // Local variables
    class Vector3 p1; // r1+0x60
    class Vector3 p2; // r1+0x50
    class Vector3 p3; // r1+0x40
    class Vector3 n1; // r1+0x30
    class Vector3 n2; // r1+0x20
    class Vector3 n3; // r1+0x10
    float x; // f31
    float y; // f1
    float z; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8051CAA8 -> 0x8051CE7C
void UtilDrawSphere(const class Vector3 & center /* r25 */, float radius /* f29 */, const class Color & col /* r26 */, int numLat /* r27 */) {
    // Local variables
    class Vector3 points[37]; // r1+0x30
    int numLong; // r31
    int numLatPoints; // r30
    int i; // r29
    float pitch; // f28
    float sp; // f0
    float cp; // f0
    int j; // r28
    float heading; // f27
    float heading; // f27
    float sh; // f0
    float ch; // f0
    int j; // r28
    float pitch; // f27
    float cp; // f0
    float sp; // f0

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8051CE7C -> 0x8051D568
void UtilDrawCigar(float radius /* f27 */, float minLength /* f28 */, float maxLength /* f29 */, const class Color & col /* r29 */) {
    // Local variables
    class Vector3 bottom[3][6]; // r1+0x1D0
    class Vector3 top[3][6]; // r1+0xB0
    class Vector3 caps[2]; // r1+0x50
    class Transform b; // r1+0x70
    int i; // r24
    float pitch; // f26
    float cpr; // f31
    float spr; // f30
    int j; // r25
    float heading; // f25
    float sh; // f0
    float ch; // f0
    int i; // r24
    int i; // r31
    int lastLong; // r0
    int j; // r30

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8051D568 -> 0x8051D728
void UtilDrawCircle(const class Vector3 & base /* r28 */, float radius /* f31 */, const class Color & col /* r29 */, int numSegs /* r30 */) {
    // Local variables
    class Vector3 points[37]; // r1+0x20
    int i; // r31
    float h; // f29

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8051D728 -> 0x8051D7E8
void UtilDrawString(const char * string /* r30 */, const class Color & col /* r31 */) {
    // Local variables
    class Vector2 p; // r1+0x8
    float z; // f0

    // References
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
}

// Range: 0x8051D7E8 -> 0x8051DABC
void UtilDrawBox(const class Color & col /* r30 */, unsigned char zBuf /* r31 */) {
    // Local variables
    class Vector3 v[8]; // r1+0x10
    int i; // r5

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8051DABC -> 0x8051DC68
void UtilDrawAxes(const class Transform & t /* r30 */, float size /* f31 */, const class Color & col /* r31 */) {
    // Local variables
    class Vector3 tmp; // r1+0x40

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8051DC68 -> 0x8051DEE8
void SetLocalScale() {
    // Local variables
    class Matrix3 m; // r1+0x10
}

// Range: 0x8051DEE8 -> 0x8051E260
void TransformKeys(class RndTransAnim * ta /* r29 */, const class Transform & xfm /* r30 */) {
    // Local variables
    class Vector3 scale; // r1+0x20
    class Matrix3 m; // r1+0x30
    class Quat rot; // r1+0x10
    class Key * tk; // r31
    class Key * sk; // r31
    class Key * rk; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8051E260 -> 0x8051E2FC
char * MovieExtension(const char * ext /* r30 */, enum Platform plat /* r31 */) {}

// Range: 0x8051E2FC -> 0x8051E380
static class Loader * ResourceFactory(const class FilePath & file /* r29 */, enum LoaderPos pos /* r30 */) {}

enum CacheResourceResult {
    kCacheSuccessful = -1,
    kCacheUnnecessary = 0,
    kCacheUnknownExtension = 1,
    kCacheMissingFile = 2,
};
// Range: 0x8051E380 -> 0x8051E574
char * CacheResource(const char * file /* r27 */, class Object * obj /* r28 */) {
    // Local variables
    enum Platform plat; // r4
    enum CacheResourceResult result; // r1+0x8
    const char * ret; // r29

    // References
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> class Rnd & TheRnd;
}

static char ps3File[256]; // size: 0x100, address: 0x80981860
static char cacheFile[256]; // size: 0x100, address: 0x80981960
// Range: 0x8051E574 -> 0x8051E70C
char * CacheResource(const char * file /* r27 */, enum CacheResourceResult & result /* r30 */) {
    // Local variables
    char buffer[256]; // r1+0x10
    const char * ext; // r31
    const char * offset; // r0

    // References
    // -> class Archive * TheArchive;
    // -> static char cacheFile[256];
    // -> static char ps3File[256];
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8051E70C -> 0x8051E7E4
void RndUtlInit() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8051E7E4 -> 0x8051E838
float ConvertFov(float ratio /* f31 */) {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndGroup * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8051E838 -> 0x8051EBBC
void ListDrawGroups(class RndDrawable * d /* r1+0x8 */, class list & l /* r31 */) {
    // Local variables
    class ObjDirItr g; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8RndGroup>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8RndGroup>; // size: 0x8, address: 0x809043B0
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndGroup * _M_data; // offset 0x8, size 0x4
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
// Range: 0x8051EBBC -> 0x8051ECC8
void WordWrap(const char * msg /* r28 */, int wrap /* r29 */, char * tmp /* r30 */) {
    // Local variables
    const char * dstEnd; // r31
    const char * srcEnd; // r4
    char * dst; // [invalid]
    const char * src; // [invalid]
    const char * srcSpace; // r5
    char * dstSpace; // r6
    int lineLen; // r7
}

// Range: 0x8051ECC8 -> 0x8051ED8C
unsigned char TexUsesAlpha(class RndTex * tex /* r31 */) {
    // Local variables
    struct _List_iterator iter; // r1+0x18
    class RndMat * mat; // r0
    enum Blend blend; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x8051ED8C -> 0x8051EDB8
void PreMultiplyAlpha() {}

// Range: 0x8051EDB8 -> 0x8051EF7C
struct MatShaderOptions GetDefaultMatShaderOpts(struct MatShaderOptions * options /* r31 */, const class Object * o /* r28 */, class RndMat * mat /* r29 */) {
    // Local variables
    const class RndMesh * m; // r0
    const class RndMultiMesh * mm; // r0
    const class RndParticleSys * p; // r0
    const class RndFlare * f; // r0

    // References
    // -> struct [anonymous] __RTTI__8RndFlare;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}


