#ifndef SYNTH_BINKREADER_H
#define SYNTH_BINKREADER_H
#include "utl/BINK.h"
#include "os/File.h"
#include "synth/StandardStream.h"
#include "synth/StreamReader.h"

enum BinkReaderState {
    kOpenBink = 0,
    kOpenTracks = 1,
    kInitStream = 2,
    kPlay = 3,
    kDone = 4,
    kFailure = 5,
};

class BinkReader : public StreamReader {
public:
    BinkReader(File*, StandardStream*);
    virtual ~BinkReader();
    virtual void Poll(float);
    virtual void Seek(int);
    virtual void EnableReads(bool);
    virtual bool Done();
    virtual bool Fail();
    virtual void Init();

    static int sHeap;
    static int mPlaying;

    File* mFile; // 0x4
    StandardStream* mStream; // 0x8
    BINK* mBink; // 0xc
    BINKTRACK* mBinkTracks[16]; // 0x10
    unsigned char* mPCMBuffers[16]; // 0x50
    unsigned char* mPCMOffsets[16]; // 0x90
    unsigned char mDecodeTrack; // 0xd0
    int mSamplesReady; // 0xd4
    unsigned int mSampleCurrent; // 0xd8
    int mSamplesJump; // 0xdc
    BinkReaderState mState; // 0xe0
    int mHeap; // 0xe4
};

#endif