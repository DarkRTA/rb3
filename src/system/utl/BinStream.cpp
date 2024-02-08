#include "string.hpp"
#include "textstream.hpp"
#include "BinStream.h"
#include "string.h"
#include "symbol.hpp"
#include "common.hpp"
#include "Random.h"

const char *BinStream::Name() const {
    return "<unnamed>";
}

// fn_80342AD8
BinStream &BinStream::operator<<(const char *c) {
    unsigned int size = strlen(c);
    *this << size;
    Write(c, size);
    return *this;
}

// fn_80342B38
BinStream &BinStream::operator<<(const Symbol &s) {
    char *str = s.m_string;
    unsigned int size = strlen(str);
    *this << size;
    Write(str, size);
    return *this;
}

// fn_80342B98
BinStream &BinStream::operator<<(const String &str) {
    unsigned int size = str.length();
    *this << size;
    Write(str.c_str(), size);
    return *this;
}


// fn_80342C00
void BinStream::ReadString(char *c, int i) {
    unsigned int a;
    *this >> a;
    Read(c, a);
    c[a] = 0;
}


// fn_80342C58
BinStream &BinStream::operator>>(Symbol &s) {
    char why[0x200];
    ReadString(why, 0x200);
    s = Symbol(why);
    return *this;
}

// fn_80342CB4
BinStream &BinStream::operator>>(String &s) {
    unsigned int a;
    *this >> a;
    s.resize(a);
    Read((char *)s.c_str(), a);
    return *this;
}

// fn_80342D18
// BinStream's ctor
BinStream::BinStream(bool b) : unk04(b), mCrypto(0) {
}

// fn_80342D34
// BinStream's dtor
BinStream::~BinStream() {
    delete mCrypto;
}

// fn_80342D98
void BinStream::EnableReadEncryption() {
    unsigned int a;
    *this >> a;
    mCrypto = new Rand2(a);
}

// fn_80342DE4
void BinStream::EnableWriteEncryption(int i) {
    unsigned int a = RandomInt();
    *this << a;
    mCrypto = new Rand2(a);
}

// fn_80342E44
void BinStream::DisableEncryption() {
    delete mCrypto;
    mCrypto = 0;
}

void BinStream::Read(void *v, int i) {
    void *temp_r31;
    unsigned char *var_r30;

    var_r30 = (unsigned char *)v;
    if (Fail() != 0) {
        Name();
        memset(var_r30, 0, i);
        return;
    }
    ReadImpl(var_r30, i);
    if (mCrypto != nullptr) {
        temp_r31 = var_r30 + i;
        while (var_r30 < temp_r31) {
            *var_r30++ ^= mCrypto->Int();
        }
    }
}

void BinStream::Write(const void *v, int i) {
    unsigned char sp8[512];
    if (Fail() != 0) {
        Name();
        return;
    }
    if (mCrypto == nullptr) {
        WriteImpl((void *)v, i);
        return;
    }
    while (i > 0) {
        int temp_r29 = Minimum(0x200, i);
        for (int j = 0; j < temp_r29; j++) {
            unsigned char x = (unsigned char)mCrypto->Int();
            sp8[j] = x ^ ((const char *)v)[j];
        }
        WriteImpl(&sp8, temp_r29);
        i -= 0x200;
        (char *)v += 0x200;
    }
}

// fn_80343058 - Seek
void BinStream::Seek(int i, SeekType s) {
    Fail();
    SeekImpl(i, s);
}

// fn_80343058
void BinStream::ReadEndian(void *v, int i) {
    Read(v, i);
    if (unk04 != 0) {
        SwapData(v, v, i);
    }
}

// fn_80343114
void SwapData(const void *v1, void *v2, int num_bytes) {
    switch (num_bytes) {
    case 2:
        unsigned short *s1 = (unsigned short *)v1;
        short *s2 = (short *)v2;
        *s2 = SwapDataHalfWord(*s1);
        break;
    case 4:
        int *i1 = (int *)v1;
        int *i2 = (int *)v2;
        *i2 = SwapDataWord(*i1);
        break;
    case 8:
        long long *l1 = (long long *)v1;
        long long *l2 = (long long *)v2;
        *l2 = SwapDataDoubleWord(*l1);
        break;
    default:
        break;
    }
}

void BinStream::WriteEndian(const void *v, int i) {
    char sp8;
    if (unk04 != 0) {
        SwapData((void *)v, &sp8, i);
        Write(&sp8, i);
    } else
        Write(v, i);
}
