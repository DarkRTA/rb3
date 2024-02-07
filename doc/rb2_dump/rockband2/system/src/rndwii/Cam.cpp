/*
    Compile unit: C:\rockband2\system\src\rndwii\Cam.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8054CE1C -> 0x8054D3B4
*/
class DataArray * types; // size: 0x4, address: 0x80A53E28
class Symbol name; // size: 0x4, address: 0x80A53E30
class Transform sWiiXfm; // size: 0x40, address: 0x809821E0
class WiiCam : public RndCam {
    // total size: 0x370
    class Transform mViewXfm; // offset 0x2F0, size 0x40
    unsigned char mAlleyRender; // offset 0x330, size 0x1
};
// Range: 0x8054CE1C -> 0x8054CEF8
void * WiiCam::WiiCam(class WiiCam * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__6WiiCam;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class WiiEnviron : public RndEnviron {
    // total size: 0x160
};
// Range: 0x8054CEF8 -> 0x8054D1E4
void WiiCam::Select(class WiiCam * const this /* r30 */) {
    // Local variables
    class WiiDrawTarget * target; // r31
    int targetWidth; // r28
    int targetHeight; // r29
    int leftOffset; // r27
    float m[4][4]; // r1+0x8
    float q; // f2
    float vpLeft; // f31
    float vpWidth; // f30
    float vpTop; // f29
    float vpHeight; // f28
    class WiiEnviron * env; // r3

    // References
    // -> class RndEnviron * sCurrent;
    // -> class Transform sWiiXfm;
    // -> class WiiRnd TheWiiRnd;
    // -> class NgStats * TheNgStats;
}

// Range: 0x8054D1E4 -> 0x8054D21C
unsigned int WiiCam::ProjectZ() {
    // Local variables
    float q; // f3
}

struct {
    // total size: 0xA4
} __vt__6WiiCam; // size: 0xA4, address: 0x80917410
struct {
    // total size: 0x8
} __RTTI__6WiiCam; // size: 0x8, address: 0x809174E8
// Range: 0x8054D21C -> 0x8054D2C4
static void __sinit_\Cam_cpp() {
    // References
    // -> class Transform sWiiXfm;
}


