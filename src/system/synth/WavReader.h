#pragma once
#include "StreamReader.h"
#include "system/os/File.h"
#include "system/utl/FileStream.h"
#include "system/utl/WaveFile.h"
#include "StandardStream.h"

class WavReader : public StreamReader {
public:
    WavReader(File *, bool, StandardStream *);
    ~WavReader();
    virtual void Poll(float);
    virtual void Seek(int);
    virtual void EnableReads(bool enable) { mEnableReads = enable; }
    virtual bool Done() { return mSamplesLeft == 0; }
    virtual bool Fail() { return false; }
    virtual void Init();
    virtual void ConsumeData(void **, int, int);
    virtual void EndData() {}

    int mNumChannels; // 0x4
    int mSampleRate; // 0x8
    File *mInFile; // 0xc
    FileStream *mInFileStream; // 0x10
    WaveFile *mInWaveFile; // 0x14
    WaveFileData *mInWaveFileData; // 0x18
    bool mEnableReads; // 0x1c
    int mSamplesLeft; // 0x20
    unsigned short *mRawInputBuffer; // 0x24
    unsigned short *mInputBuffers[2]; // 0x28
    int mBufNumSamples; // 0x30
    int mBufOffset; // 0x34
    int mTotalSamplesConsumed; // 0x38
    bool mInitted; // 0x3c
    StandardStream *mOutStream; // 0x40
};