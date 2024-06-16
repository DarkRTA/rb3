#ifndef SYNTH_SAMPLEDATA_H
#define SYNTH_SAMPLEDATA_H
#include "utl/Str.h"
#include "utl/BinStream.h"
#include "utl/FilePath.h"
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
    void Load(BinStream&, const FilePath&);
    void LoadWAV(BinStream&, const FilePath&);
    int SizeAs(Format) const;
    int NumMarkers() const;
    const SampleMarker& GetMarker(int) const;

    static void SetAllocator(SampleDataAllocFunc, SampleDataFreeFunc);

    static SampleDataAllocFunc sAlloc;
    static SampleDataFreeFunc sFree;
    
    int mNumSamples; // 0x0
    int mSampleRate; // 0x4
    int mSizeBytes; // 0x8
    Format mFormat; // 0xc
    void* mData; // 0x10
    std::vector<SampleMarker> mMarkers; // 0x14
};

#endif
