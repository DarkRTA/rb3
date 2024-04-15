#include "MemStream.h"

MemStream::MemStream(bool b) : BinStream(b) {
    mBuffer.reserve(0x1000);

    // Initializer list wasn't used here for some reason
    mFail = false;
    mTell = 0;
}


bool MemStream::Fail() { return mFail; }
void MemStream::Flush() {}
