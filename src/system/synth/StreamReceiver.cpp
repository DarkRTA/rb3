#include "synth/StreamReceiver.h"
#include "os/Debug.h"

StreamReceiverFactoryFunc *StreamReceiver::sFactory;

StreamReceiver *StreamReceiver::New(int i1, int i2, bool b3, int i4) {
    MILO_ASSERT(sFactory, 0x1C);
    return sFactory(i1, i2, b3, i4);
}

StreamReceiver::StreamReceiver(int numBuffers, bool slip)
    : mSlipEnabled(slip), mBuffer(), mNumBuffers(numBuffers), mState(kInit),
      mSendTarget(0), mWantToSend(false), mSending(false), mBuffersSent(0),
      mStarving(false), mEndData(false), mDoneBufferCounter(0), mLastPlayCursor(0) {
    MILO_ASSERT(numBuffers > 0, 0x33);
    mRingFreeSpace = 0x18000;
    mRingReadPos = 0;
    mRingWritePos = 0;
    mRingSize = 0x18000;
    mRingWrittenSpace = 0;
}

StreamReceiver::~StreamReceiver() {}

DECOMP_FORCEFUNC(StreamReceiver, StreamReceiver, BytesWriteable())

#pragma push
#pragma force_active on
inline int StreamReceiver::BytesWriteable() { return mRingFreeSpace; }
#pragma pop

void StreamReceiver::WriteData(const void *data, int bytes) {
    MILO_ASSERT(bytes > 0 && bytes <= BytesWriteable(), 0x55);
    int num = mRingSize - mRingWritePos;
    if (bytes <= num) {
        memcpy(mBuffer + mRingWritePos, data, bytes);
        mRingWritePos += bytes;
        if (mRingWritePos == mRingSize) {
            mRingWritePos = 0;
        }
    } else {
        memcpy(mBuffer + mRingWritePos, data, num);
        char *cData = (char *)data;
        memcpy(mBuffer, cData + num, bytes - num);
        mRingWritePos = bytes - num;
    }
    mRingFreeSpace -= bytes;
    mRingWrittenSpace += bytes;
}

void StreamReceiver::ClearAtEndData() {
    if (mRingFreeSpace != 0) {
        if (mRingWritePos + mRingFreeSpace <= mRingSize) {
            memset(mBuffer + mRingWritePos, 0, mRingFreeSpace);
            mRingWritePos += mRingFreeSpace;
            if (mRingWritePos == mRingSize) {
                mRingWritePos = 0;
            }
        } else {
            int firstWipeSize = mRingSize - mRingWritePos;
            int secondWipeSize = mRingFreeSpace - firstWipeSize;
            MILO_ASSERT(firstWipeSize > 0, 0x7D);
            MILO_ASSERT(secondWipeSize > 0, 0x7E);
            memset(mBuffer + mRingWritePos, 0, firstWipeSize);
            memset(mBuffer, 0, mRingFreeSpace - firstWipeSize);
            mRingWritePos = mRingFreeSpace - firstWipeSize;
        }
    }
}

DECOMP_FORCEFUNC(StreamReceiver, StreamReceiver, Ready())

#pragma push
#pragma force_active on
inline bool StreamReceiver::Ready() { return mState != kInit; }
#pragma pop

void StreamReceiver::Play() {
    MILO_ASSERT(Ready(), 0x91);
    switch (mState) {
    case kPlaying:
        break;
    case kStopped:
        PauseImpl(false);
        goto play;
        break;
    default:
        PlayImpl();
    play:
        mState = kPlaying;
        break;
    }
}

void StreamReceiver::Stop() {
    MILO_ASSERT(mState == kPlaying || mState == kStopped, 0xA6);
    if (mState == kPlaying) {
        PauseImpl(true);
        mState = kStopped;
    }
}

void StreamReceiver::Poll() {}

void StreamReceiver::EndData() {
    if (!mEndData) {
        if (mRingFreeSpace != 0) {
            ClearAtEndData();
            mRingFreeSpace = 0;
        }
        mEndData = true;
    }
}

int StreamReceiver::GetBytesPlayed() {}