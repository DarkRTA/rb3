/*
    Compile unit: C:\rockband2\system\src\dsp\VocalInterpreter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BB7B8 -> 0x803BC6B8
*/
class Timer gAnalysisPartTimer; // size: 0x38, address: 0x8097E0B0
const char * gFFTOutputFile; // size: 0x4, address: 0x80A51750
class FileStream * gFFTOutputStream; // size: 0x4, address: 0x80A51754
// Range: 0x803BB7B8 -> 0x803BB850
void * VocalInterpreter::VocalInterpreter(class VocalInterpreter * const this /* r29 */, int inputRate /* r30 */, int afterRate /* r31 */) {}

// Range: 0x803BB850 -> 0x803BB890
void * VocalInterpreter::~VocalInterpreter(class VocalInterpreter * const this /* r31 */) {}

// Range: 0x803BB890 -> 0x803BB9B4
unsigned char VocalInterpreter::MakeLowpassFIRFilter(int passFreq /* r25 */, int sampleRate /* r26 */, signed short * buffer /* r27 */, int count /* r28 */, int shift /* r29 */) {
    // Local variables
    int ii; // r30
    float tt; // f31
    float vv; // f31
}

// Range: 0x803BB9B4 -> 0x803BBA20
unsigned char VocalInterpreter::AnalyzeFrame(class VocalInterpreter * const this /* r31 */) {}

// Range: 0x803BBA20 -> 0x803BBB98
unsigned char VocalInterpreter::CalculateFrameFFT(class VocalInterpreter * const this /* r30 */, struct ComplexSample * output /* r26 */) {
    // Local variables
    struct ComplexSample zz[256]; // r1+0x210
    signed short xx[256]; // r1+0x10
    signed short max; // r31
    int ii; // r27
    int ii; // r27
    unsigned char cx; // r1+0x8

    // References
    // -> class FileStream * gFFTOutputStream;
    // -> const char * gFFTOutputFile;
}

// Range: 0x803BBB98 -> 0x803BBC98
unsigned char VocalInterpreter::ConvertFFTToPeakMagnitude(unsigned char * peakMagnitudes /* r30 */, int size /* r31 */) {
    // Local variables
    struct ComplexSample fftMaxima[256]; // r1+0x208
    signed short fullMagnitudes[256]; // r1+0x8
    signed short maxPeak; // r27
    int ii; // r26
    int ii; // r4
}

// Range: 0x803BBC98 -> 0x803BBE00
unsigned char VocalInterpreter::CalculateSequentialError(struct ComplexSample * fftHalf /* r28 */, int fftHalfCount /* r29 */, float & error /* r30 */, float & energy /* r31 */) {
    // Local variables
    int ii; // r25
    struct ComplexSample diff; // r1+0x8
}

// Range: 0x803BBE00 -> 0x803BBFD8
unsigned char VocalInterpreter::DownSampleInto(class VocalInterpreter * const this /* r25 */, signed short * before /* r26 */, int count /* r27 */, signed short * after /* r28 */) {
    // Local variables
    int subsample; // r31
    int copied; // r30
    int start; // [invalid]
    int ii; // r29
}

// Range: 0x803BBFD8 -> 0x803BC060
unsigned char VocalInterpreter::PreemphasizeBuffer() {
    // Local variables
    int ii; // r7
}

// Range: 0x803BC060 -> 0x803BC0D4
unsigned char VocalInterpreter::WindowBuffer() {
    // Local variables
    int ii; // r8
}

// Range: 0x803BC0D4 -> 0x803BC1AC
unsigned char VocalInterpreter::MaximaDownSample(struct ComplexSample * fftHalf /* r24 */, int fftCount /* r25 */, int spacing /* r26 */, struct ComplexSample * fftMaxima /* r27 */) {
    // Local variables
    int ii; // r31
    int maxindex; // r30
    signed short maxmag; // r29
    int jj; // r28
}

// Range: 0x803BC1AC -> 0x803BC210
signed short VocalInterpreter::ComplexMagnitude() {}

// Range: 0x803BC210 -> 0x803BC22C
signed short VocalInterpreter::ComplexSqrMagnitude() {}

// Range: 0x803BC22C -> 0x803BC25C
struct ComplexSample VocalInterpreter::ComplexDiff() {
    // Local variables
    struct ComplexSample diff; // r1+0x8
}

// Range: 0x803BC25C -> 0x803BC2F4
void VocalInterpreter::ComplexFromReal(int nn /* r1+0x8 */, int mm /* r1+0xC */) {
    // Local variables
    int ii; // r6
    int ii; // r4
}

// Range: 0x803BC2F4 -> 0x803BC45C
void VocalInterpreter::Radix2FFT(struct ComplexSample * xx /* r29 */, struct ComplexSample * ww /* r30 */) {
    // Local variables
    int tempr; // r0
    int tempi; // r5
    int q; // r6
    int j; // r7
    int k; // r8
    int n1; // r4
    int n2; // r0
    int n3; // r25
    int L; // r9
    int kL; // r10
    int r; // r11
    int L2; // r12
    int t; // r31
}

// Range: 0x803BC45C -> 0x803BC5B4
void VocalInterpreter::Radix2Twiddles(struct ComplexSample * ww /* r27 */, int n /* r28 */) {
    // Local variables
    int L; // r31
    int k; // r30
    double theta; // f31
    int j; // r29
}

// Range: 0x803BC5B4 -> 0x803BC6AC
void VocalInterpreter::Radix2BitReverse() {
    // Local variables
    signed short * ri; // r0
    signed short tempr; // r12
    int nn; // r0
    int j; // r3
    int i; // r5
    int m; // r6
}

// Range: 0x803BC6AC -> 0x803BC6B8
static void __sinit_\VocalInterpreter_cpp() {
    // References
    // -> class Timer gAnalysisPartTimer;
}


