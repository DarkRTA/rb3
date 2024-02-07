/*
    Compile unit: C:\rockband2\system\src\os\DiscErrorMgr_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B5E0C -> 0x805B6454
*/
struct TPLPalette * gEjectErrorImg; // size: 0x4, address: 0x80A549D8
struct TPLPalette * gRetryErrorImg; // size: 0x4, address: 0x80A549DC
// Range: 0x805B5E0C -> 0x805B5E24
void * DiscErrorMgrWii::DiscErrorMgrWii() {}

// Range: 0x805B5E24 -> 0x805B5E64
void * DiscErrorMgrWii::~DiscErrorMgrWii(class DiscErrorMgrWii * const this /* r31 */) {}

// Range: 0x805B5E64 -> 0x805B5F04
void DiscErrorMgrWii::Init(class DiscErrorMgrWii * const this /* r31 */) {
    // References
    // -> struct TPLPalette * gRetryErrorImg;
    // -> class Debug TheDebug;
    // -> struct TPLPalette * gEjectErrorImg;
}

// Range: 0x805B5F04 -> 0x805B5F5C
void DiscErrorMgrWii::Terminate(class DiscErrorMgrWii * const this /* r31 */) {}

// Range: 0x805B5F5C -> 0x805B5F70
void DiscErrorMgrWii::SetDiscError() {}

// Range: 0x805B5F70 -> 0x805B6108
void DiscErrorMgrWii::LoopUntilNoDiscError(class DiscErrorMgrWii * const this /* r28 */, struct DVDFileInfo * fileInfo /* r29 */, unsigned char detectBusy /* r30 */) {
    // Local variables
    int status; // r0
    int status; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class SynthWii * TheWiiSynth;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805B6108 -> 0x805B6170
void DiscErrorMgrWii::DrawDiscErrorMsg(class DiscErrorMgrWii * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805B6170 -> 0x805B6454
void DiscErrorMgrWii::DrawSplashDiscErrorMsg(class DiscErrorMgrWii * const this /* r31 */) {
    // Local variables
    struct _GXTexObj texObj; // r1+0x10
    signed short x1; // r29
    signed short y1; // r30
    signed short x2; // r28
    signed short y2; // r27

    // References
    // -> class WiiRnd TheWiiRnd;
}


