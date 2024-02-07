/*
    Compile unit: C:\rockband2\system\src\char\ClipCompressor.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803A55FC -> 0x803A6754
*/
static int total; // size: 0x4, address: 0x80A51590
static int saved; // size: 0x4, address: 0x80A51594
// Range: 0x803A55FC -> 0x803A5AD8
void ClipCompressor::CompressAll(class ClipCompressor * const this /* r29 */) {
    // Local variables
    class CharClipSamples * maxClip; // r30
    float maxFrac; // f31
    class ObjDirItr clip; // r1+0x18
    int size; // r0
    int saved; // r0
    float frac; // f0

    // References
    // -> static int saved;
    // -> static int total;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharClipSamples;
    // -> class Debug TheDebug;
}

// Range: 0x803A5AD8 -> 0x803A5C64
void ClipCompressor::FillInFrames(class ClipCompressor * const this /* r31 */) {
    // Local variables
    int k; // r4
    int front; // r5
    int back; // r6
    int spacing; // r7
    int i; // r8
}

// Range: 0x803A5C64 -> 0x803A5DD8
void ClipCompressor::BackAdjust(class ClipCompressor * const this /* r31 */) {
    // Local variables
    int j; // r30
    int front; // r29
    int back; // r28
    int minMiddle; // r27
    float minErr; // f31
    float oldErr; // f0
    int middle; // r26
    float err; // r1+0xC
    float err2; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803A5DD8 -> 0x803A60CC
int ClipCompressor::CompressClip(class ClipCompressor * const this /* r28 */, class CharClipSamples * c /* r29 */, unsigned char finish /* r30 */) {
    // Local variables
    float avErr; // f31
    float maxErr; // f30
    float err; // r1+0x2C
    int b; // r25
    int saved; // r25
    int total; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803A60CC -> 0x803A61F4
void ClipCompressor::FinishClip(class ClipCompressor * const this /* r31 */) {
    // Local variables
    int last; // r5
    int i; // r29
    int index; // r28
    int gap; // r5
}

// Range: 0x803A61F4 -> 0x803A6264
void ClipCompressor::PoseSingle(class ClipCompressor * const this /* r30 */, int sample /* r31 */) {}

// Range: 0x803A6264 -> 0x803A63D4
void ClipCompressor::PoseDouble(class ClipCompressor * const this /* r29 */, float sample /* f31 */, int front /* r30 */, int back /* r31 */) {
    // Local variables
    float frac; // f31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803A63D4 -> 0x803A645C
int ClipCompressor::FindNextFrame(class ClipCompressor * const this /* r27 */, float & err /* r28 */) {
    // Local variables
    int numSamples; // r31
    int back; // r30
    int front; // r29
    float curErr; // f0
}

// Range: 0x803A645C -> 0x803A6528
float ClipCompressor::CompressError(class ClipCompressor * const this /* r28 */, int front /* r29 */, int back /* r30 */) {
    // Local variables
    float maxError; // f31
    int i; // r31
}

// Range: 0x803A6528 -> 0x803A65F8
void ClipCompressor::InitError(class ClipCompressor * const this /* r28 */) {
    // Local variables
    int j; // r29
}

// Range: 0x803A65F8 -> 0x803A6754
float ClipCompressor::GrabError(class ClipCompressor * const this /* r28 */) {
    // Local variables
    float maxError; // f31
    int i; // r29
    float d2; // f0
}

struct {
    // total size: 0x8
} __RTTI__PQ214ClipCompressor8BoneDesc; // size: 0x8, address: 0x808DE1E0

