#include "utl/BufStream.h"
#include "os/Debug.h"
#include <string.h>

BufStream::BufStream(void * buffer, int size, bool lilEndian) : BinStream(lilEndian), mChecksum(0), mBytesChecksummed() {
    mBuffer = (char*)buffer;
    mFail = (buffer == 0);
    mTell = 0;
    mSize = size;
}

BufStream::~BufStream(){
    DeleteChecksum();
}

void BufStream::DeleteChecksum(){
    delete mChecksum;
    mChecksum = 0;
    mBytesChecksummed = 0;
}

void BufStream::StartChecksum(const char* name){
    DeleteChecksum();
    mChecksum = new StreamChecksumValidator();
    if(!mChecksum->Begin(name, false)) DeleteChecksum();
}

bool BufStream::ValidateChecksum(){
    if(!mChecksum) return false;
    else {
        mChecksum->End();
        MILO_ASSERT(mBytesChecksummed == mTell, 0x3A);
        bool ret = false;
        if(mBytesChecksummed == mTell && mChecksum->Validate()){
            ret = true;
        }
        return ret;
    }
}

void BufStream::ReadImpl(void* data, int bytes){
    int tell = mTell;
    int size = mSize;
    if(tell + bytes > size){
        mFail = true;
        bytes = size - tell;
    }

    memcpy(data, &mBuffer[mTell], bytes);
    mTell += bytes;
    if(mChecksum && !mFail){
        mChecksum->Update((const unsigned char*)data, bytes);
        mBytesChecksummed += bytes;
    }
}

void BufStream::WriteImpl(const void* data, int bytes){
    int tell = mTell;
    int size = mSize;
    if(tell + bytes > size){
        mFail = true;
        bytes = size - tell;
    }
    memcpy(&mBuffer[mTell], data, bytes);
    mTell += bytes;
}

void BufStream::SeekImpl(int offset, SeekType t){
    int pos;

    switch(t){
        case kSeekBegin:
            pos = offset;
            break;
        case kSeekCur:
            pos = mTell + offset;
            break;
        case kSeekEnd:
            pos = mSize + offset;
            break;
        default:
            return;
    }

    if(pos < 0 || pos > mSize){
        mFail = true;
    }
    else {
        mTell = pos;
    }

    // case 0: validate offset, mFail = true or mTell = offset
    // case 1: offset += mTell, then case 0's logic
    // case 2: offset += mSize, then case 0's logic
}

const char* BufStream::Name() const {
    if(mName.empty()) return BinStream::Name();
    else return mName.c_str();
}

void BufStream::SetName(const char* name) {
    mName = name;
}
