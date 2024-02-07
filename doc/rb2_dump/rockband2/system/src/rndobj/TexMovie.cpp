/*
    Compile unit: C:\rockband2\system\src\rndobj\TexMovie.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8050089C -> 0x805020EC
*/
class DataArray * types; // size: 0x4, address: 0x80A539A0
// Range: 0x8050089C -> 0x80500A0C
void * RndTexMovie::RndTexMovie(class RndTexMovie * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6WiiTex,9ObjectDir>;
    // -> struct [anonymous] __vt__11RndTexMovie;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80500A0C -> 0x80500B74
void * RndTexMovie::~RndTexMovie(class RndTexMovie * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6WiiTex,9ObjectDir>;
    // -> struct [anonymous] __vt__11RndTexMovie;
}

// Range: 0x80500B74 -> 0x80500C68
void RndTexMovie::Copy(class RndTexMovie * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndTexMovie * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndTexMovie;
}

// Range: 0x80500C68 -> 0x80500D48
void RndTexMovie::Replace(class RndTexMovie * const this /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6WiiTex,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
}

static int TexMovie_REV; // size: 0x4, address: 0x80A47418
// Range: 0x80500D48 -> 0x80500E2C
void RndTexMovie::Save(class RndTexMovie * const this /* r27 */, class BinStream & d /* r31 */) {
    // References
    // -> class FilePath sRoot;
    // -> static int TexMovie_REV;
}

// Range: 0x80500E2C -> 0x80500EF0
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjOwnerPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x80981728
// Range: 0x80500EF0 -> 0x805011EC
void RndTexMovie::Load(class RndTexMovie * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x18
    class DataNode ret; // r1+0x28

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int TexMovie_REV;
}

// Range: 0x805011EC -> 0x80501354
void RndTexMovie::BeginMovie(class RndTexMovie * const this /* r31 */) {
    // References
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80501354 -> 0x80501404
void RndTexMovie::DrawToTexture(class RndTexMovie * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80501404 -> 0x80501418
void RndTexMovie::DrawShowing() {}

// Range: 0x80501418 -> 0x80501470
void RndTexMovie::Poll(class RndTexMovie * const this /* r31 */) {}

// Range: 0x80501470 -> 0x805014B4
void RndTexMovie::Enter(class RndTexMovie * const this /* r31 */) {}

// Range: 0x805014B4 -> 0x805014F8
void RndTexMovie::Exit(class RndTexMovie * const this /* r31 */) {}

// Range: 0x805014F8 -> 0x80501548
void RndTexMovie::SetFile(class RndTexMovie * const this /* r30 */, const class FilePath & file /* r31 */) {}

// Range: 0x80501548 -> 0x80501568
void RndTexMovie::UpdatePreClearState() {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80501568 -> 0x80501A88
class DataNode RndTexMovie::Handle(class RndTexMovie * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A539A8
static class Symbol _s; // size: 0x4, address: 0x80A539B0
static class Symbol _s; // size: 0x4, address: 0x80A539B8
static class Symbol _s; // size: 0x4, address: 0x80A539C0
static class Symbol _s; // size: 0x4, address: 0x80A539C8
// Range: 0x80501A88 -> 0x80501FB8
unsigned char RndTexMovie::SyncProperty(class RndTexMovie * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80501FB8 -> 0x805020EC
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6WiiTex;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xF0
} __vt__11RndTexMovie; // size: 0xF0, address: 0x809016C8
struct {
    // total size: 0x8
} __RTTI__11RndTexMovie; // size: 0x8, address: 0x809017F0
struct {
    // total size: 0x18
} __vt__31ObjOwnerPtr<6WiiTex,9ObjectDir>; // size: 0x18, address: 0x809017F8
struct {
    // total size: 0x8
} __RTTI__31ObjOwnerPtr<6WiiTex,9ObjectDir>; // size: 0x8, address: 0x80901840
struct {
    // total size: 0x8
} __RTTI__6WiiTex; // size: 0x8, address: 0x80901878
struct {
    // total size: 0x8
} __RTTI__13WiiDrawTarget; // size: 0x8, address: 0x80901890

