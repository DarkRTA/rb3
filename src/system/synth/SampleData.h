#ifndef SYNTH_SAMPLEDATA_H
#define SYNTH_SAMPLEDATA_H
#include "utl/Str.h"
#include <vector>

struct SampleMarker {
    SampleMarker() : name(""), sample(-1) {}

    String name;
    int sample;
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
    ~SampleData();
    void Reset();
    void SetAllocator(SampleDataAllocFunc, SampleDataFreeFunc);
    void Load(BinStream&, const FilePath&);
    void LoadWAV(BinStream&, const FilePath&);
    int NumMarkers() const;
    SampleMarker& GetMarker(int) const;
    int SizeAs(Format) const;

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
