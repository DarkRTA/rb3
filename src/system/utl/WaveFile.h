#ifndef UTL_WAVEFILE_H
#define UTL_WAVEFILE_H
#include "utl/Chunks.h"
#include <vector>

class WaveFile {
public:
    WaveFile(BinStream&);
    ~WaveFile();
    void ReadFormat();
    void ReadMarkers();
    void ReadNumSamples();
    IListChunk& PrepareToProvideData();

    short mFormat;
    unsigned short mNumChannels;
    unsigned int mSamplesPerSec;
    unsigned int mAvgBytesPerSec;
    unsigned short mBlockAlign;
    unsigned short mBitsPerSample;
    int mNumSamples;
    std::vector<int> mMarkers;
    IListChunk mRiffList;
};

class WaveFileData : public IDataChunk {
public:
    WaveFileData(WaveFile&);
    virtual ~WaveFileData(){}

    WaveFile* mWaveFile;
};

#endif
