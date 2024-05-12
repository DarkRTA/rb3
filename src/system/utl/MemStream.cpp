#include "MemStream.h"

MemStream::MemStream(bool b) : BinStream(b) {
    mBuffer.reserve(0x1000);

    // Initializer list wasn't used here for some reason
    mFail = false;
    mTell = 0;
}

void MemStream::ReadImpl(void* data, int bytes){
    int tell = mTell;
    unsigned int size = mBuffer.size();
    if(tell + bytes > size){
        mFail = true;
        bytes = size - tell;
    }
    memcpy(data, &mBuffer[mTell], bytes);
    mTell += bytes;
}

void MemStream::WriteImpl(const void* data, int bytes){
    int toReserve = mBuffer.capacity();
    while(mTell + bytes > toReserve) toReserve += toReserve;
    mBuffer.reserve(toReserve);
    if(mBuffer.size() > mTell + bytes){
        mBuffer.resize(toReserve);
    }
    memcpy(&mBuffer[mTell], data, bytes);
    mTell += bytes;
}

void MemStream::WriteStream(BinStream& bs, int bytes){
    int toReserve = mBuffer.capacity();
    while(mTell + bytes > toReserve) toReserve += toReserve;
    mBuffer.reserve(toReserve);
    if(mBuffer.size() > mTell + bytes){
        mBuffer.resize(toReserve);
    }
    bs.Read(&mBuffer[mTell], bytes);
    mTell += bytes;
}

void MemStream::SeekImpl(int offset, SeekType t){
    int pos;
    
    switch(t){
        case kSeekBegin:
            pos = offset;
            break;
        case kSeekCur:
            pos = mTell + offset;
            break;
        case kSeekEnd:
            pos = mBuffer.size() + offset;
            break;
        default:
            return;
    }
    
    if(pos < 0 || pos > mBuffer.size()){
        mFail = true;
    }
    else {
        mTell = pos;
    }

    // case 0: validate offset, mFail = true or mTell = offset
    // case 1: offset += mTell, then case 0's logic
    // case 2: offset += mSize, then case 0's logic
}

void MemStream::Compact(){
    mBuffer.erase(mBuffer.begin(), mBuffer.begin() + mTell);
    mTell = 0;
}

bool MemStream::Fail() { return mFail; }
void MemStream::Flush() {}
