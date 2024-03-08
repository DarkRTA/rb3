#include "MemStream.h"

MemStream::MemStream(bool b) : BinStream(b) {
    
}


bool MemStream::Fail() { return mFail; }
void MemStream::Flush() {}
