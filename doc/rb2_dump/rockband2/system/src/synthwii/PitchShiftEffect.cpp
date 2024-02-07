/*
    Compile unit: C:\rockband2\system\src\synthwii\PitchShiftEffect.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80563F00 -> 0x80564210
*/
class PitchShiftEffect {
    // total size: 0x14
    class SoundTouch * mSoundTouch; // offset 0x0, size 0x4
    unsigned char mStarted; // offset 0x4, size 0x1
    float mPitch; // offset 0x8, size 0x4
    float mLastPitch; // offset 0xC, size 0x4
    int mFrameCount; // offset 0x10, size 0x4
};
// Range: 0x80563F00 -> 0x80563F74
void * PitchShiftEffect::PitchShiftEffect(class PitchShiftEffect * const this /* r31 */) {}

// Range: 0x80563F74 -> 0x80563FF4
void * PitchShiftEffect::~PitchShiftEffect(class PitchShiftEffect * const this /* r30 */) {}

// Range: 0x80563FF4 -> 0x80564044
void PitchShiftEffect::Reset(class PitchShiftEffect * const this /* r30 */) {}

// Range: 0x80564044 -> 0x805640BC
void PitchShiftEffect::SetParameter(class PitchShiftEffect * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805640BC -> 0x80564210
unsigned char PitchShiftEffect::Process(class PitchShiftEffect * const this /* r25 */, signed short * samps /* r26 */, int numSamps /* r27 */, signed short * write /* r28 */, int writeSamps /* r29 */, int numChans /* r30 */) {
    // Local variables
    unsigned char started; // r31
    unsigned int act; // r5
}


