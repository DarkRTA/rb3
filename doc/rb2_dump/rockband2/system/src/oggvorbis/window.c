/*
    Compile unit: C:\rockband2\system\src\oggvorbis\window.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8054CB00 -> 0x8054CC68
*/
static float vwin64[32]; // size: 0x80, address: 0x8090F470
static float vwin128[64]; // size: 0x100, address: 0x8090F4F0
static float vwin256[128]; // size: 0x200, address: 0x8090F5F0
static float vwin512[256]; // size: 0x400, address: 0x8090F7F0
static float vwin1024[512]; // size: 0x800, address: 0x8090FBF0
static float vwin2048[1024]; // size: 0x1000, address: 0x809103F0
static float vwin4096[2048]; // size: 0x2000, address: 0x809113F0
static float vwin8192[4096]; // size: 0x4000, address: 0x809133F0
static float * vwin[8]; // size: 0x20, address: 0x809173F0
// Range: 0x8054CB00 -> 0x8054CB14
float * _vorbis_window_get() {
    // References
    // -> static float * vwin[8];
}

// Range: 0x8054CB14 -> 0x8054CC68
void _vorbis_apply_window() {
    // Local variables
    float * windowLW; // r6
    float * windowNW; // r4
    long n; // r0
    long ln; // r7
    long rn; // r9
    long leftbegin; // r10
    long leftend; // r11
    long rightbegin; // r12
    long rightend; // r9
    int i; // r31
    int p; // r10

    // References
    // -> static float * vwin[8];
}


