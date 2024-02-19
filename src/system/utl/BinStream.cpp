#include "utl/BinStream.h"
#include "math/Random.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/Debug.h"
#include <string.h>

const char *BinStream::Name() const {
    return "<unnamed>";
}

BinStream& BinStream::operator<<(const char* str){
    ASSERT(str, 0x23);
    int size = strlen(str);
    WriteEndian(&size, 4);
    Write(str, size);
    return *this;
}

BinStream::BinStream(bool b) : mLittleEndian(b), mCrypto(0) {
}

BinStream::~BinStream() {
    delete mCrypto;
}
