#include "MemStream.h"

MemStream::MemStream(bool b) : BinStream(b), mFail(0), mTell(0), mBuffer() {
    // mBuffer.reserve(0x1000); // TODO: fix reserve
}


bool MemStream::Fail() { return mFail; }
void MemStream::Flush() {}
