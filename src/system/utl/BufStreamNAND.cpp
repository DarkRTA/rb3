#include "BufStreamNAND.h"
#include "math/SHA1.h"
#include "math/StreamChecksum.h"
#include "meta/FixedSizeSaveableStream.h"
#include "os/Debug.h"
#include "os/Memcard.h"
#include "revolution/nand/nand.h"
#include "rndwii/Rnd.h"
#include "utl/BinStream.h"
#include "utl/Symbol.h"

BufStreamNAND::BufStreamNAND(void *v1, int i1, char* buffer, bool b1) 
    : FixedSizeSaveableStream(v1, i1, b1), mBuffer(buffer), mChecksum(0), mBytesChecksummed(0), mSize(i1), mFilePath(), mFileOpen(0) {
    
}

BufStreamNAND::~BufStreamNAND() {

}

int BufStreamNAND::Tell() {
    return mRunningTell;
}

void BufStreamNAND::SetResult(MCResult result) {
    mResult = result;
}

int BufStreamNAND::GetResult() {
    return mResult;
}

bool BufStreamNAND::Fail() {
    return mFail;
}

EofType BufStreamNAND::Eof() {
    return (EofType)(mSize == mTell);
}

void BufStreamNAND::Clear() {
    mFail = mBuffer == 0;
    mTell = 0;
    mRunningTell = 0;
    mChunkSize = 0x40000;
    unk80 = 0;
    mResult = kMCNoError;
    MILO_ASSERT(fmod(mSize, 4.503601775116288e15 - 4.503601774854144e15), 0x39);
}

int BufStreamNAND::Open() {
    s32 file;
    MCResult result;
    SetGPHangDetectEnabled(0, "Open");
    if(!mFileOpen) {
        file = NANDOpen(mFilePath, mFileInfo, 3);
        result = HandleResultNAND(file);
        if(result) 
            mFail = 1;
        else
            mFileOpen = 1;
    }
    SetGPHangDetectEnabled(1, "Open");
    
    return file;
}

int BufStreamNAND::Close() {
    s32 file;
    MCResult result;
    SetGPHangDetectEnabled(0, "Close");
    if(mFileOpen) {
        //NANDGetLength(mFileInfo, u32 *) // stack variable epic
        file = NANDClose(mFileInfo);
        result = HandleResultNAND(file);
        if(result)
            mFail = 1;
        else
         mFileOpen = 1;
    }
    SetGPHangDetectEnabled(0, "Close");
    return result;
}

bool BufStreamNAND::FinishStream() {
    int result = Close();
    if(result) {
        mFail = 1;
    }
    return result;
}

void BufStreamNAND::ReadImpl(void *v1, int i1) {
    // v5 = ui2
    unsigned int temp;
    if(!mFail) {
        if((mTell + i1) > mChunkSize || !mRunningTell)
            LoadBufferFromNAND();
        
        if((mRunningTell + i1) > mSize || (mTell + i1) > mChunkSize) {
            temp = mSize - mTell;
            mFail = 1;
        }
        // init_proc(&mBuffer[mTell], temp)
        mRunningTell += temp;
        if(mChecksum) {
            if(!mFail) {
                mChecksum->Update((unsigned char*)v1, temp);
                mBytesChecksummed += temp;
            }
        }
    }
}

void BufStreamNAND::DeleteChecksum() {
    if(mChecksum) {
        delete(mChecksum);
    }
    mChecksum = 0;
}