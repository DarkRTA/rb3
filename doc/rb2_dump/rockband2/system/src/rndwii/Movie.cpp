/*
    Compile unit: C:\rockband2\system\src\rndwii\Movie.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8055310C -> 0x80553890
*/
class DataArray * types; // size: 0x4, address: 0x80A53F10
class Symbol name; // size: 0x4, address: 0x80A53F18
class WiiMovie : public RndMovie {
    // total size: 0x84
    class SIVideo mVideo; // offset 0x2C, size 0x14
    char * mBuffer; // offset 0x40, size 0x4
    int mMovieFrame; // offset 0x44, size 0x4
    class File * mStreamFile; // offset 0x48, size 0x4
    int mStreamOrigin; // offset 0x4C, size 0x4
    int mStreamOffset; // offset 0x50, size 0x4
    char * mStreamAddr; // offset 0x54, size 0x4
};
// Range: 0x8055310C -> 0x805531A4
void * WiiMovie::WiiMovie(class WiiMovie * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8WiiMovie;
}

// Range: 0x805531A4 -> 0x805532F4
void * WiiMovie::~WiiMovie(class WiiMovie * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__8WiiMovie;
}

// Range: 0x805532F4 -> 0x8055341C
void WiiMovie::SetTex(class WiiMovie * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Timer * _t; // size: 0x4, address: 0x80A53F1C
// Range: 0x8055341C -> 0x80553644
void WiiMovie::SetFrame(class WiiMovie * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    int df; // r3

    // References
    // -> static class Timer * _t;
}

// Range: 0x80553644 -> 0x805536A8
void WiiMovie::Update(class WiiMovie * const this /* r29 */) {
    // Local variables
    class WiiTex * tex; // r31
    int size; // r30
    void * ptr; // r0
}

// Range: 0x805536A8 -> 0x80553730
int WiiMovie::StreamChunkSize(class WiiMovie * const this /* r30 */) {}

// Range: 0x80553730 -> 0x80553778
void WiiMovie::StreamReadFinish(class WiiMovie * const this /* r31 */) {
    // Local variables
    int bytes; // r1+0x8
}

// Range: 0x80553778 -> 0x805537F0
void WiiMovie::StreamNextBuffer(class WiiMovie * const this /* r31 */) {}

// Range: 0x805537F0 -> 0x80553890
void WiiMovie::StreamRestart(class WiiMovie * const this /* r30 */, int f /* r31 */) {}

struct {
    // total size: 0xB4
} __vt__8WiiMovie; // size: 0xB4, address: 0x80917FD0
struct {
    // total size: 0x8
} __RTTI__8WiiMovie; // size: 0x8, address: 0x809180B8

