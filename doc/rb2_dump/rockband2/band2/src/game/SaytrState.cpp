/*
    Compile unit: C:\rockband2\band2\src\game\SaytrState.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80082378 -> 0x800867E8
*/
// Range: 0x80082378 -> 0x80082434
void * SaytrState::SaytrState(class SaytrState * const this /* r29 */, int historyTime /* r30 */) {}

// Range: 0x80082434 -> 0x800824E8
void * SaytrState::~SaytrState(class SaytrState * const this /* r30 */) {}

// Range: 0x800824E8 -> 0x80082AB4
float SaytrState::CalculateScore(class SaytrState * const this /* r27 */, class SaytrState & eval /* r28 */, float similarScale /* f27 */, float timingScale /* f28 */) {
    // Local variables
    float totalScore; // f31
    float totalWeight; // f30
    int oldestTime; // r31
    int ecld; // r30
    float bestScore; // f29
    float weight; // f28
    int rcld; // r29
    float score; // f1
}

// Range: 0x80082AB4 -> 0x80083850
float SaytrState::CalculatePairScore(class SaytrState * const this /* r30 */, class SaytrState & eval /* r31 */, float similarScale /* f29 */, float timingScale /* f30 */) {
    // Local variables
    int oldestTime; // r29
    int ecld; // r28
    float bestScore; // f31
    int rcld; // r27
    int espl; // r26
    float etrans; // f0
    int rspl; // r25
    float match1; // f0
    float match2; // f0
    float match; // f0
    float rtrans; // f0
    float trans; // f0
    float transweight; // f28
    float score; // f0
}

class deque : protected _Deque_base {
    // total size: 0x28
};
// Range: 0x80083850 -> 0x80083DE0
float SaytrState::SequentialMatch(class SaytrState * const this /* r26 */, class SaytrState & eval /* r27 */, class deque & corresponds /* r28 */, int adjustments /* r29 */, float similarScale /* f29 */, float timingScale /* f30 */) {
    // Local variables
    float temperature; // f27
    float bestEnergy; // f31
    int ii; // r1+0x1C
    class deque partialEnergy; // r1+0x20
    int rcld; // r30
    int ii; // r31
    int rcld; // r30
    int ecld; // r25
    float newEnergy; // f0
    float finalScore; // f27
    int rcld; // r25
    int refTimeShift; // r30
    int evalTimeShift; // r0
}

// Range: 0x80083DE0 -> 0x8008478C
float SaytrState::SequenceEnergy(class SaytrState * const this /* r26 */, class SaytrState & eval /* r27 */, class deque & corresponds /* r28 */, int rcld /* r29 */, int ecld /* r30 */, float similarScale /* f31 */, float timingScale /* f30 */, unsigned char scoreSilence /* r31 */) {
    // Local variables
    float energy; // r1+0x8
}

// Range: 0x8008478C -> 0x800847F0
unsigned char SaytrState::SequenceMutateOracle() {}

// Range: 0x800847F0 -> 0x800851D0
float SaytrState::CalculateSequenceScore(class SaytrState * const this /* r28 */, class SaytrState & eval /* r29 */, class deque & corresponds /* r30 */, float similarScale /* f27 */, float timingScale /* f28 */) {
    // Local variables
    float score; // f31
    float count; // f30
    int rcld; // r31
    float score1; // f29
    float score2; // f0
}

// Range: 0x800851D0 -> 0x80085B4C
float SaytrState::CalculateTransitionScore(class SaytrState * const this /* r25 */, class SaytrState & eval /* r26 */, float timingScale /* f31 */) {
    // Local variables
    unsigned char voiced; // r0
    int oldestTime; // r30
    int rtrans; // r29
    unsigned char found; // r28
    int etrans; // r27
}

// Range: 0x80085B4C -> 0x80085CC8
int SaytrState::GetCount(class SaytrState * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80085CC8 -> 0x80085E04
int SaytrState::GetLastTime() {}

// Range: 0x80085E04 -> 0x80085E90
unsigned char SaytrState::GetLastVoiced() {}

// Range: 0x80085E90 -> 0x80085F88
int SaytrState::GetLastEnergyBytes(unsigned char * energies /* r28 */) {
    // Local variables
    class PhoneCloud * last; // r31
    struct SpeechAnalysis * analyses; // r30
    int ii; // r29
}

// Range: 0x80085F88 -> 0x800860DC
void * PhoneCloud::PhoneCloud() {
    // Local variables
    int ii; // r8
}

// Range: 0x800860DC -> 0x8008611C
void * PhoneCloud::~PhoneCloud(class PhoneCloud * const this /* r31 */) {}

// Range: 0x8008611C -> 0x8008628C
float PhoneCloud::CalculateWeightedMatch(class PhoneCloud * const this /* r28 */, class PhoneCloud & eval /* r29 */, float similarScale /* f28 */) {
    // Local variables
    float totalScore; // f31
    float totalDenom; // f30
    float distortionScale; // f29
    int ii; // r31
    int jj; // r30
    float score; // f0
}

// Range: 0x8008628C -> 0x800863B8
float PhoneCloud::CalculateSingleMatch(class PhoneCloud * const this /* r28 */, class PhoneCloud & eval /* r29 */, float similarScale /* f30 */, int espl /* r30 */, float unvoicedScore /* f31 */) {
    // Local variables
    float score; // f0
}

// Range: 0x800863B8 -> 0x800864A4
float PhoneCloud::CalculateSingleTransition() {
    // Local variables
    float etrPrev; // f2
    float etrCurr; // f1
}

// Range: 0x800864A4 -> 0x80086560
unsigned char PhoneCloud::IsVoiced(class PhoneCloud * const this /* r29 */) {
    // Local variables
    int voiced; // r31
    int ii; // r30
}

// Range: 0x80086560 -> 0x800865A0
int PhoneCloud::GetCount(class PhoneCloud * const this /* r31 */) {}

// Range: 0x800865A0 -> 0x800865E4
int PhoneCloud::GetSlopTime() {}

// Range: 0x800865E4 -> 0x80086660
float PhoneCloud::GetTransitionGamma(float timingScale /* f31 */) {}

// Range: 0x80086660 -> 0x800866DC
float PhoneCloud::GetWarpingPenalty(float timingScale /* f31 */) {}

// Range: 0x800866DC -> 0x80086758
float PhoneCloud::GetTransitionTiming(float timingScale /* f31 */) {}

// Range: 0x80086758 -> 0x80086764
float PhoneCloud::GetSimilarityBoost() {}

// Range: 0x80086764 -> 0x800867E8
float PhoneCloud::GetDistortionScale(float similarScale /* f31 */) {}

struct _Deque_iterator_base {
    // total size: 0x10
    float * _M_cur; // offset 0x0, size 0x4
    float * _M_first; // offset 0x4, size 0x4
    float * _M_last; // offset 0x8, size 0x4
    float * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PPf; // size: 0x8, address: 0x80879428
struct {
    // total size: 0x8
} __RTTI__PPi; // size: 0x8, address: 0x80879438
struct {
    // total size: 0x8
} __RTTI__PPPQ210SaytrState10PhoneCloud; // size: 0x8, address: 0x80879460
struct {
    // total size: 0x8
} __RTTI__PPQ210SaytrState10PhoneCloud; // size: 0x8, address: 0x80879488
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};

