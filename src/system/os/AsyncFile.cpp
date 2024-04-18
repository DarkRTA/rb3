#include "os/AsyncFile.h"

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