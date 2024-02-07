/*
    Compile unit: C:\rockband2\system\src\rndobj\SIVideo.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804FDD84 -> 0x804FE050
*/
class SIVideo {
    // total size: 0x14
    unsigned int mWidth; // offset 0x0, size 0x4
    unsigned int mHeight; // offset 0x4, size 0x4
    unsigned int mNumFrames; // offset 0x8, size 0x4
    unsigned int mOrder; // offset 0xC, size 0x4
    char * mData; // offset 0x10, size 0x4
};
// Range: 0x804FDD84 -> 0x804FDDDC
void SIVideo::Reset(class SIVideo * const this /* r30 */) {}

// Range: 0x804FDDDC -> 0x804FDFA0
void SIVideo::Load(class SIVideo * const this /* r29 */, class BinStream & d /* r30 */, unsigned char stream /* r31 */) {
    // Local variables
    unsigned int sig; // r1+0x14
    unsigned int frameSize; // r1+0x10
    unsigned int pad; // r1+0xC
    unsigned int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804FDFA0 -> 0x804FDFB8
int SIVideo::Bpp() {}

// Range: 0x804FDFB8 -> 0x804FDFF8
int SIVideo::FrameSize(const class SIVideo * const this /* r31 */) {}

// Range: 0x804FDFF8 -> 0x804FE050
char * SIVideo::Frame(class SIVideo * const this /* r30 */, int i /* r31 */) {}


