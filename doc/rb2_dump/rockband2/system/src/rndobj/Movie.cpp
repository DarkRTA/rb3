/*
    Compile unit: C:\rockband2\system\src\rndobj\Movie.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804D0078 -> 0x804D0DFC
*/
class DataArray * types; // size: 0x4, address: 0x80A532B8
class Symbol name; // size: 0x4, address: 0x80A532C0
// Range: 0x804D0078 -> 0x804D0158
void * RndMovie::RndMovie(class RndMovie * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__8RndMovie;
}

static int MOVIE_REV; // size: 0x4, address: 0x80A472D0
// Range: 0x804D0158 -> 0x804D019C
void RndMovie::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804D019C -> 0x804D01F8
void RndMovie::Load(class RndMovie * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A532C4
// Range: 0x804D01F8 -> 0x804D0370
void RndMovie::PreLoad(class RndMovie * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int MOVIE_REV;
    // -> static int gRev;
}

// Range: 0x804D0370 -> 0x804D03FC
void RndMovie::PostLoad(class RndMovie * const this /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x804D03FC -> 0x804D0514
void RndMovie::Copy(class RndMovie * const this /* r28 */, const class Object * o /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndMovie * t; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndMovie;
}

// Range: 0x804D0514 -> 0x804D0580
void RndMovie::Replace(class RndMovie * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
}

// Range: 0x804D0580 -> 0x804D05E8
void RndMovie::SetTex(class RndMovie * const this /* r30 */, class RndTex * tex /* r31 */) {}

// Range: 0x804D05E8 -> 0x804D09D4
class DataNode RndMovie::Handle(class RndMovie * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A532CC
static class Symbol _s; // size: 0x4, address: 0x80A532D4
static class Symbol _s; // size: 0x4, address: 0x80A532DC
static class Symbol _s; // size: 0x4, address: 0x80A532E4
// Range: 0x804D09D4 -> 0x804D0DFC
unsigned char RndMovie::SyncProperty(class RndMovie * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB4
} __vt__8RndMovie; // size: 0xB4, address: 0x808FBC5C
struct {
    // total size: 0x18
} __vt__31ObjOwnerPtr<6RndTex,9ObjectDir>; // size: 0x18, address: 0x808FBD40
struct {
    // total size: 0x8
} __RTTI__31ObjOwnerPtr<6RndTex,9ObjectDir>; // size: 0x8, address: 0x808FBD88

