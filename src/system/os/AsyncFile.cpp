#include "os/AsyncFile.h"
#include "os/Debug.h"

static int gBufferSize;

AsyncFile::AsyncFile(const char* c, int i) : mMode(i), mFail(false), unk9(0), mFilename(c), mTell(0), mOffset(0), mBuffer(0), mData(0), mBytesLeft(0) {

}

int AsyncFile::Read(void* iBuf, int iBytes){
    ReadAsync(iBuf, iBytes);
    if(mFail) return 0;
    else while(!ReadDone(iBytes));
    return iBytes;
}

int AsyncFile::Write(const void* iBuf, int iBytes){
    WriteAsync((void*)iBuf, iBytes);
    if(mFail) return 0;
    else while(!WriteDone(iBytes));
    return iBytes;
}

bool AsyncFile::ReadAsync(void* iBuff, int iBytes){
    MILO_ASSERT(iBytes >= 0, 299);
    MILO_ASSERT(mMode & FILE_OPEN_READ, 0x12D);
    if(mFail) return false;
    else {
        if(!mBuffer){
            _WriteAsync(iBuff, iBytes);
        }
        else {
            if(mTell + iBytes > mSize){
                iBytes = mSize - mTell;
            }
            MILO_ASSERT(iBytes >= 0, 0x13F);
            mData = (char*)iBuff;
            mBytesLeft = iBytes;
            mBytesRead = 0;
            ReadDone(iBytes);
        }
        return mFail == 0;
    }
}