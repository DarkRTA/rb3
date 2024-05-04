#ifndef SYNTH_SAMPLEDATA_H
#define SYNTH_SAMPLEDATA_H
#include "utl/Str.h"
#include <vector>

struct SampleMarker {
    SampleMarker() : str(), i(-1) {}

    String str;
    int i;
};

typedef void* (*SampleDataAllocFunc)(int, const char*);
typedef void (*SampleDataFreeFunc)(void*);

class SampleData {
public:
    enum Format {
        kPCM,
        kBigEndPCM,
        kVAG,
        kXMA,
        kATRAC,
        kMP3,
        kNintendoADPCM
    };

    SampleData();
    void Reset();
    void SetAllocator(SampleDataAllocFunc, SampleDataFreeFunc);

    static SampleDataAllocFunc sAlloc;
    static SampleDataFreeFunc sFree;
    
    int mNumSamples;
    int mSampleRate;
    int mSizeBytes;
    Format mFormat;
    void* mData;
    std::vector<SampleMarker> mMarkers;
};

#endif
