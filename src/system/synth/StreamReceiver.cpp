#include "synth/StreamReceiver.h"
#include "os/Debug.h"

StreamReceiverFactoryFunc* StreamReceiver::sFactory;

StreamReceiver* StreamReceiver::New(int i1, int i2, bool b3, int i4){
    MILO_ASSERT(sFactory, 0x1C);
    return sFactory(i1, i2, b3, i4);
}

StreamReceiver::StreamReceiver(int numBuffers, bool slip) :
    mSlipEnabled(slip),
    mBuffer(),
    mNumBuffers(numBuffers),
    mState(kInit),
    mSendTarget(0),
    mWantToSend(false),
    mSending(false),
    mBuffersSent(0),
    mStarving(false),
    mEndData(false),
    mDoneBufferCounter(0),
    mLastPlayCursor(0)
{
    MILO_ASSERT(numBuffers > 0, 0x33);
    mRingFreeSpace = 0x18000;
    mRingReadPos = 0;
    mRingWritePos = 0;
    mRingSize = 0x18000;
    mRingWrittenSpace = 0;
}

StreamReceiver::~StreamReceiver(){

}

int StreamReceiver::BytesWriteable(){
    return mRingFreeSpace;
}