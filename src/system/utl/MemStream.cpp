#include "MemStream.h"

MemStream::MemStream(bool b) : BinStream(b), b(0), c(0) {
    // mem.reserve(0x1000);
}


bool MemStream::Fail() { return mFail; }
void MemStream::Flush() {}
