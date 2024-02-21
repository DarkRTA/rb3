#include "utl/BinStream.h"
#include "math/Random.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/Debug.h"
#include <string.h>

#define BIN_STREAM_BUF_SIZE 0x200U

const char *BinStream::Name() const {
    return "<unnamed>";
}

BinStream& BinStream::operator<<(const char* str){
    MILO_ASSERT(str, 0x23);
    int size = strlen(str);
    *this << size;
    Write(str, size);
    return *this;
}

BinStream &BinStream::operator<<(const Symbol &s) {
    const char *str = s.mStr;
    int len = strlen(str);
    MILO_ASSERT(len < BIN_STREAM_BUF_SIZE, 0x2F);
    *this << len;
    Write(str, len);
    return *this;
}

BinStream &BinStream::operator<<(const String &str) {
    int size = str.length();
    *this << size;
    Write(str.c_str(), size);
    return *this;
}

void BinStream::ReadString(char *c, int i) {
    int a;
    *this >> a;
    if((unsigned int)a >= i) MILO_FAIL("String chars %d > %d", (unsigned int)(a + 1), i);
    Read(c, a);
    c[a] = 0;
}

BinStream &BinStream::operator>>(Symbol &s) {
    char why[0x200];
    ReadString(why, 0x200);
    s = Symbol(why);
    return *this;
}

BinStream &BinStream::operator>>(String &s) {
    int a;
    *this >> a;
    s.resize(a);
    Read((char *)s.c_str(), a);
    return *this;
}

BinStream::BinStream(bool b) : mLittleEndian(b), mCrypto(0) {
}

BinStream::~BinStream() {
    delete mCrypto;
}

void BinStream::EnableReadEncryption() {
    MILO_ASSERT(!mCrypto, 0x81);
    int a;
    *this >> a;
    mCrypto = new Rand2(a);
}

void BinStream::EnableWriteEncryption() {
    MILO_ASSERT(!mCrypto, 0x89);
    int a = RandomInt();
    *this << a;
    mCrypto = new Rand2(a);
}

void BinStream::DisableEncryption() {
    MILO_ASSERT(mCrypto, 0x9D);
    delete mCrypto;
    mCrypto = 0;
}

// void BinStream::Read(void *v, int i) {
//     void *temp_r31;
//     unsigned char *var_r30;

//     var_r30 = (unsigned char *)v;
//     if (Fail() != 0) {
//         Name();
//         memset(var_r30, 0, i);
//         return;
//     }
//     ReadImpl(var_r30, i);
//     if (mCrypto != nullptr) {
//         temp_r31 = var_r30 + i;
//         while (var_r30 < temp_r31) {
//             *var_r30++ ^= mCrypto->Int();
//         }
//     }
// }

// void BinStream::Write(const void *v, int i) {
//     unsigned char sp8[512];
//     if (Fail() != 0) {
//         Name();
//         return;
//     }
//     if (mCrypto == nullptr) {
//         WriteImpl((void *)v, i);
//         return;
//     }
//     while (i > 0) {
//         int temp_r29 = Minimum(0x200, i);
//         for (int j = 0; j < temp_r29; j++) {
//             unsigned char x = (unsigned char)mCrypto->Int();
//             sp8[j] = x ^ ((const char *)v)[j];
//         }
//         WriteImpl(&sp8, temp_r29);
//         i -= 0x200;
//         (char *)v += 0x200;
//     }
// }

// // fn_80343058 - Seek
// void BinStream::Seek(int i, SeekType s) {
//     Fail();
//     SeekImpl(i, s);
// }

// // fn_80343058
// void BinStream::ReadEndian(void *v, int i) {
//     Read(v, i);
//     if (mLittleEndian != 0) {
//         SwapData(v, v, i);
//     }
// }

// // fn_80343114
// void SwapData(const void *v1, void *v2, int num_bytes) {
//     switch (num_bytes) {
//     case 2:
//         unsigned short *s1 = (unsigned short *)v1;
//         short *s2 = (short *)v2;
//         *s2 = SwapDataHalfWord(*s1);
//         break;
//     case 4:
//         int *i1 = (int *)v1;
//         int *i2 = (int *)v2;
//         *i2 = SwapDataWord(*i1);
//         break;
//     case 8:
//         long long *l1 = (long long *)v1;
//         long long *l2 = (long long *)v2;
//         *l2 = SwapDataDoubleWord(*l1);
//         break;
//     default:
//         break;
//     }
// }

// void BinStream::WriteEndian(const void *v, int i) {
//     char sp8;
//     if (mLittleEndian != 0) {
//         SwapData((void *)v, &sp8, i);
//         Write(&sp8, i);
//     } else
//         Write(v, i);
// }
