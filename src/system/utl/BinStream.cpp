#include "utl/BinStream.h"
#include "decomp.h"
#include "math/Rand.h"
#include "types.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/Debug.h"
#include "os/Endian.h"

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

void BinStream::Read(void* data, int bytes){
    if(Fail()){
        MILO_NOTIFY_ONCE("Stream error: Can't read from %s", Name());
        memset(data, 0, bytes);
    }
    else {
        unsigned char* ptr = (unsigned char*)data;
        unsigned char* end;
        ReadImpl(data, bytes);
        if(mCrypto){
            end = ptr + bytes;
            while(ptr < end){
                *ptr++ ^= mCrypto->Int();
            }
        }
    }
}

void BinStream::Write(const void* void_data, int bytes){
    if(Fail()){
        MILO_LOG_ONCE("Stream error: Can't write to %s\n", Name());
    } else {
        const unsigned char* data = (u8*)void_data;
        if (!mCrypto) {
            WriteImpl(void_data, bytes);
        } else {
            u8 crypt[512];
            while (bytes > 0) {
                int x = Min(512,bytes);
                for (int i = 0; i < x; i++) {
                    u8 bastard = mCrypto->Int();
                    crypt[i] = data[i] ^ bastard;
                }
                WriteImpl(crypt, x);
                bytes -= 512;
                data += 512;
            }
        }
    }
}

void BinStream::Seek(int offset, SeekType type){
    MILO_ASSERT(!Fail(), 0xDF);
    MILO_ASSERT(!mCrypto, 0xE2);
    SeekImpl(offset, type);
}

inline void SwapData(const void *v1, void *v2, int num_bytes) {
    switch (num_bytes) {
        case 2:
            unsigned short *s1 = (unsigned short *)v1;
            short *s2 = (short *)v2;
            *s2 = EndianSwap(*s1);
            break;
        case 4:
            unsigned int *i1 = (unsigned int *)v1;
            int *i2 = (int *)v2;
            *i2 = EndianSwap(*i1);
            break;
        case 8:
            unsigned long long *l1 = (unsigned long long *)v1;
            long long *l2 = (long long *)v2;
            *l2 = EndianSwap(*l1);
            break;
        default:
            MILO_ASSERT(0, 0x6F);
            break;
    }
}

void BinStream::ReadEndian(void* data, int bytes){
    Read(data, bytes);
    if(mLittleEndian){
        SwapData(data, data, bytes);
    }
}

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

void BinStream::WriteEndian(const void* void_data, int bytes){
    char buf[16];
    if(mLittleEndian){
        SwapData((void*)void_data, buf, bytes);
        Write(buf, bytes);
    }
    else Write(void_data, bytes);
}

#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(BinStream, "BinStream::AddSharedInlined is a PC dev tool only !!")
#endif
//void BinStream::AddSharedInlined() {}
