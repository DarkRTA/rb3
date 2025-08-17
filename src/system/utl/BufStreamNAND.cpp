#include "BufStreamNAND.h"
#include "meta/MemcardMgr_Wii.h"
#include "rndwii/Rnd.h"


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
    SetGPHangDetectEnabled(false, "Open");
    if(!mFileOpen) {
        file = NANDOpen(mFilePath, mFileInfo, 3);
        result = HandleResultNAND(file);
        if(result) 
            mFail = true;
        else
            mFileOpen = true;
    }
    SetGPHangDetectEnabled(true, "Open");
    
    return file;
}

int BufStreamNAND::Close() {
    s32 file;
    MCResult result;
    SetGPHangDetectEnabled(false, "Close");
    if(mFileOpen) {
        //NANDGetLength(mFileInfo, u32 *) // stack variable epic
        file = NANDClose(mFileInfo);
        result = HandleResultNAND(file);
        if(result)
            mFail = true;
        else
         mFileOpen = true;
    }
    SetGPHangDetectEnabled(true, "Close");
    return result;
}

bool BufStreamNAND::FinishStream() {
    int result = Close();
    if(result) {
        mFail = true;
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
            mFail = true;
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

int BufStreamNAND::Pad(int size) {
    MILO_ASSERT(size > mSize, 0x170);
    int result = 0;

    while(size > mRunningTell) {
        mTell = size - mRunningTell;

        if(mTell > mChunkSize)
            mTell = mChunkSize;
        mRunningTell += mTell;

        result = SaveBufferToNAND(0);
        if(result) {
            mFail = true;
            return result;
        }
    }
    return result;
}

int BufStreamNAND::PadToEnd() {
    return Pad(mSize);
}

void BufStreamNAND::DeleteChecksum() {
    if(mChecksum) {
        delete(mChecksum);
    }
    mChecksum = 0;
}

int BufStreamNAND::LoadBufferFromNAND() {
    SetGPHangDetectEnabled(false, "LoadBufferFromNAND");
    s32 file = Open();
    DoSeek(0, kSeekCur);
    int v3 = mChunkSize;
    int v4 = mRunningTell;
    int v5 = mSize;

    if(v4 + v3 > v5)
        v3 = v5 - v4;
    s32 res = NANDRead(mFileInfo, mBuffer, v3);

    if(res == v3) {
        mTell = 0;
        SetGPHangDetectEnabled(true, "LoadBufferFromNAND");
        return file;
    }
    else {
        mFail = true;
        MCResult result = HandleResultNAND(res);
        SetGPHangDetectEnabled(true, "LoadBufferFromNAND");
        return result;
    }
}

int BufStreamNAND::SaveBufferToNAND(bool b1) {
    SetGPHangDetectEnabled(false, "SaveBufferToNAND");
    s32 file = Open();
    s32 write = NANDWrite(mFileInfo, mBuffer, mTell);
    if(write == mTell) {
        memset(mBuffer, 0, mChunkSize);
        mTell = 0;
        if(b1 && mRunningTell == mSize && (file = Close()) != 0) {
            mFail = true;
            SetGPHangDetectEnabled(true, "SaveBufferToNAND");
            return file;
        }
        else {
            SetGPHangDetectEnabled(true, "SaveBufferToNAND");
            return file;
        }
    }
    else {
        mFail = true;
        MCResult result = HandleResultNAND(write);
        SetGPHangDetectEnabled(true, "SaveBufferToNAND");
        return result;
    }
}

bool BufStreamNAND::FinishWrite() {
    bool result = SaveBufferToNAND(false);
    if(result)
        mFail = true;
    return result;
}

int BufStreamNAND::DoSeek(int i1, BinStream::SeekType seekType) {

}

void BufStreamNAND::SeekImpl(int i1, BinStream::SeekType seekType) {
    if(TheMemcardMgr.IsWriteMode() && SaveBufferToNAND(false) != 0)
        mFail = true;
    else {
        DoSeek(i1, seekType);
        if(!TheMemcardMgr.IsWriteMode() && LoadBufferFromNAND()) {
            mFail = true;
        }
    }
     
}