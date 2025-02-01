#include "synth/BinkReader.h"
#include "lib/binkwii/binkread.h"
#include "utl/BinkIntegration.h"

int BinkReader::mPlaying;
int BinkReader::sHeap = 1;
int gTempLastDecodeSize = -1;
int gTempPrevFrameSize = -1;

void *BinkReaderHeapAlloc(int) {
    MILO_LOG("BinkReaderHeapAlloc: warning: fallback to normal malloc\n");
}

DECOMP_FORCEACTIVE(BinkReader, __FILE__, "gBinkReaderHeap[i].inUse")

void BinkReaderHeapFree(void *) {
    MILO_LOG("BinkReaderHeapAlloc: warning: fallback to normal free\n");
}

BinkReader::BinkReader(File *f, StandardStream *s)
    : mFile(f), mStream(s), mDecodeTrack(0), mSamplesReady(0), mSampleCurrent(0),
      mSamplesJump(0), mState(kOpenBink), mHeap(sHeap) {
    mPlaying++;
    BinkInit();
    BinkSetSoundTrack(0, 0);
    mBink = BinkOpen(f, 0x2804400);
    if (mBink) {
        mState = kOpenTracks;
        BinkSetVideoOnOff(mBink, 0);
    } else {
        MILO_WARN("Error opening Bink audio file: %s\n", BinkGetError());
        mState = kFailure;
    }
}

BinkReader::~BinkReader() {
    if (mState > kOpenTracks && mBink) {
        for (unsigned char i = 0; i < mBink->NumTracks; i++) {
            if (mBinkTracks[i]) {
                BinkCloseTrack(mBinkTracks[i]);
            }
            if (mPCMBuffers[i]) {
                MILO_LOG("BinkReader: 0x%08x free %d\n", this, i);
                BinkReaderHeapFree(mPCMBuffers[i]);
            }
        }
        BinkClose(mBink);
    }
    mPlaying--;
}

void BinkReader::PollOpenTracks() {
    MILO_ASSERT(mBink->NumTracks < BINK_AUDIO_CHANNEL_MAX, 0xA4);
    if (mBink->NumTracks == 0) {
        mState = kDone;
    }
    MemPushHeap(mHeap);
    for (unsigned char i = 0; i < mBink->NumTracks; i++) {
        BINKTRACK *hBinkTrack = BinkOpenTrack(mBink, i);
        mBinkTracks[i] = hBinkTrack;
        MILO_ASSERT(hBinkTrack->Bits == 16, 0xB9);
        MILO_ASSERT(hBinkTrack->Channels == 1, 0xBD);
        MILO_LOG("BinkReader: 0x%08x alloc %d %d\n", this, i, hBinkTrack->MaxSize);
        unsigned char *data = (unsigned char *)BinkReaderHeapAlloc(hBinkTrack->MaxSize);
        mPCMBuffers[i] = data;
        mPCMOffsets[i] = data;
    }
    MemPopHeap();
    mState = kInitStream;
}

void BinkReader::PollInitStream() {
    mState = kPlay;
    Init();
    gTempLastDecodeSize = -1;
}

void BinkReader::PollPlay() {}

void BinkReader::Poll(float) {}

void BinkReader::Init() {
    MILO_ASSERT(mStream, 0x1F9);
    mStream->InitInfo(mBink->NumTracks, mBinkTracks[0]->Frequency, false, -1);
}