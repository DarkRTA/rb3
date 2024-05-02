#include "synth/StreamReceiver.h"
#include "os/Debug.h"

StreamReceiver::StreamReceiver(int numBuffers, bool b){
    mSlipEnabled = b;
    unsigned char* ptr = &mBuffer[0];
    for(int i = 0; i < 0x3000; i++){
        *ptr++ = 0;
    }
    mNumBuffers = numBuffers;
    mState = kInit;
    mSendTarget = 0;
    mWantToSend = false;
    mSending = false;
    mBuffersSent = 0;
    mStarving = false;
    mEndData = false;
    mDoneBufferCounter = 0;
    mLastPlayCursor = 0;
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