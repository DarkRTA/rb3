#include "AsyncFileHolmes.h"
#include "os/AsyncFile.h"
#include "os/Debug.h"
#include "os/HolmesClient.h"

AsyncFileHolmes::AsyncFileHolmes(const char* c, int i) : AsyncFile(c, i), mHolmesHandle(-1) {}

void AsyncFileHolmes::_OpenAsync() {
    uint siz;
    mFail = !HolmesClientOpen(mFilename.c_str(), mMode, siz, mHolmesHandle);
    if (mFail) siz = 0;
    mSize = siz;
}

bool AsyncFileHolmes::_OpenDone() { return true; }

void AsyncFileHolmes::_WriteAsync(const void* buf, int bytes) {
    MILO_ASSERT(mOffset == bytes, 38);
    HolmesClientWrite(mHolmesHandle, mTell - mOffset, bytes, buf);
}

bool AsyncFileHolmes::_WriteDone() { return true; }

void AsyncFileHolmes::_SeekToTell() {
    while (_ReadDone() == 0);
}

void AsyncFileHolmes::_ReadAsync(void* buf, int bytes) {
    HolmesClientRead(mHolmesHandle, mTell, bytes, buf, this);
}

bool AsyncFileHolmes::_ReadDone() { return HolmesClientReadDone(this); }

void AsyncFileHolmes::_Close() { 
    if (mFail) return; 
    HolmesClientClose(this, mHolmesHandle); 
}

int AsyncFileHolmes::Truncate(int i) { 
    HolmesClientTruncate(mHolmesHandle, i); 
    return 1; 
}

int AsyncFileHolmes::GetFileHandle(DVDFileInfo*&) { return 0; }