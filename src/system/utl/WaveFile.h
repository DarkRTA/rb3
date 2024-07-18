#ifndef UTL_WAVEFILE_H
#define UTL_WAVEFILE_H
#include "utl/Chunks.h"
#include "synth/SampleData.h"
#include <vector>

class WaveFileMarker {
public:
    WaveFileMarker(int frame, int id, const String& name) : mFrame(frame), mID(id), mName(name) {}
    // total size: 0x14
    int mFrame; // offset 0x0, size 0x4
    int mID; // offset 0x4, size 0x4
    class String mName; // offset 0x8, size 0xC
};

class WaveFile {
public:
    WaveFile(BinStream&);
    ~WaveFile();
    void ReadFormat();
    void ReadMarkers();
    void ReadNumSamples();
    IListChunk& PrepareToProvideData();
    short NumChannels() const { return mNumChannels; }
    short BitsPerSample() const { return mBitsPerSample; }
    int SamplesPerSec() const { return mSamplesPerSec; }
    int NumSamples() const { return mNumSamples; }
    short Format() const { return mFormat; }
    int NumMarkers() const { return mMarkers.size(); }

    short mFormat; // 0x0
    unsigned short mNumChannels; // 0x2
    unsigned int mSamplesPerSec; // 0x4
    unsigned int mAvgBytesPerSec; // 0x8
    unsigned short mBlockAlign; // 0xc
    unsigned short mBitsPerSample; // 0xe
    int mNumSamples; // 0x10
    std::vector<WaveFileMarker> mMarkers;
    IListChunk mRiffList; // 0x1c
};

class WaveFileData : public IDataChunk {
public:
    WaveFileData(WaveFile&);
    virtual ~WaveFileData();

    WaveFile* mWaveFile;
};

#endif
