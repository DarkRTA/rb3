#ifndef UTL_WAVEFILE_H
#define UTL_WAVEFILE_H
#include "utl/Chunks.h"
#include "synth/SampleData.h"
#include <vector>

class WaveFile {
public:
    WaveFile(BinStream&);
    ~WaveFile();
    void ReadFormat();
    void ReadMarkers();
    void ReadNumSamples();
    IListChunk& PrepareToProvideData();

    short mFormat; // 0x0
    short mNumChannels; // 0x2
    unsigned int mSamplesPerSec; // 0x4
    unsigned int mAvgBytesPerSec; // 0x8
    unsigned short mBlockAlign; // 0xc
    unsigned short mBitsPerSample; // 0xe
    int mNumSamples; // 0x10
    std::vector<SampleMarker> mMarkers; // 0x14
    IListChunk mRiffList; // 0x1c
};

class WaveFileData : public IDataChunk {
public:
    WaveFileData(WaveFile&);
    virtual ~WaveFileData(){}

    WaveFile* mWaveFile;
};

#endif
