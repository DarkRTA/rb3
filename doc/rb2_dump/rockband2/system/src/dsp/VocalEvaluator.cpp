/*
    Compile unit: C:\rockband2\system\src\dsp\VocalEvaluator.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BA818 -> 0x803BB7B8
*/
float gTotalPhonemeAccuracy; // size: 0x4, address: 0x80A51748
float gLogLookupTable[256]; // size: 0x400, address: 0x808DFB28
// Range: 0x803BA818 -> 0x803BA830
void * VocalEvaluator::VocalEvaluator() {}

// Range: 0x803BA830 -> 0x803BA8A8
void * VocalEvaluator::~VocalEvaluator(class VocalEvaluator * const this /* r30 */) {}

// Range: 0x803BA8A8 -> 0x803BAB70
unsigned char VocalEvaluator::UseReferenceFile(class VocalEvaluator * const this /* r31 */, const char * panFile /* r29 */, unsigned char frameRate /* r1+0x8 */) {
    // Local variables
    class FileStream fileStream; // r1+0x18
}

// Range: 0x803BAB70 -> 0x803BAD44
unsigned char VocalEvaluator::GetAnalyses(class VocalEvaluator * const this /* r29 */, float ms /* f31 */, struct SpeechAnalysis * outs /* r30 */, int * count /* r31 */) {}

// Range: 0x803BAD44 -> 0x803BAE6C
unsigned char VocalEvaluator::EvaluateFrame(class VocalInterpreter * interper /* r29 */, struct SpeechAnalysis & out /* r30 */, float & energy /* r31 */) {
    // Local variables
    struct ComplexSample fftHalf[128]; // r1+0x10
    float sequentialError; // r1+0x8
}

// Range: 0x803BAE6C -> 0x803BAF68
float VocalEvaluator::ScoreFrame(struct SpeechAnalysis & mic /* r30 */, struct SpeechAnalysis & ref /* r31 */) {
    // Local variables
    float peakScore; // f0
    float errorScore; // f3
    float score; // f1

    // References
    // -> float gTotalPhonemeAccuracy;
}

// Range: 0x803BAF68 -> 0x803BB014
float VocalEvaluator::ScorePeakMagnitudes(unsigned char * refMagnitudes /* r8 */, float distanceScale /* f31 */) {
    // Local variables
    int micLast; // r5
    int refLast; // r6
    float score; // f0
}

// Range: 0x803BB014 -> 0x803BB070
unsigned char VocalEvaluator::IsVoiced() {}

// Range: 0x803BB070 -> 0x803BB184
unsigned char VocalEvaluator::ReadHeader(class VocalEvaluator * const this /* r30 */, unsigned char & frameRate /* r31 */) {
    // Local variables
    unsigned char byte; // r1+0x8
}

// Range: 0x803BB184 -> 0x803BB290
unsigned char VocalEvaluator::WriteHeader(class VocalEvaluator * const this /* r31 */, unsigned char frameRate /* r1+0x8 */) {
    // Local variables
    unsigned char byte; // r1+0x9
}

// Range: 0x803BB290 -> 0x803BB55C
unsigned char VocalEvaluator::CollectOneFrame(class VocalEvaluator * const this /* r29 */, struct SpeechAnalysis * outs /* r30 */, int * count /* r31 */) {
    // Local variables
    unsigned char size; // r1+0xA
    int left; // r28
    unsigned char energy; // r1+0x9
    unsigned char size2; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BB55C -> 0x803BB644
unsigned char VocalEvaluator::AdvanceOneFrame(class VocalEvaluator * const this /* r31 */) {
    // Local variables
    unsigned char size; // r1+0x8
}

// Range: 0x803BB644 -> 0x803BB730
unsigned char VocalEvaluator::RetreatOneFrame(class VocalEvaluator * const this /* r31 */) {
    // Local variables
    unsigned char size; // r1+0x8
}

// Range: 0x803BB730 -> 0x803BB7B8
float VocalEvaluator::ComparePeakMagnitudes() {
    // Local variables
    float dsum; // f2
    int nn; // r10
    float term; // f0

    // References
    // -> float gLogLookupTable[256];
}


