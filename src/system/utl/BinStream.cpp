#include "utl/BinStream.h"
#include "math/Rand.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/Debug.h"
#include <string.h>
#include <list>

#define BIN_STREAM_BUF_SIZE 0x200U

namespace {
    bool AddToNotifies(const char* str, std::list<String>& list){
        if(list.size() > 0x10) return false;
        for(std::list<String>::iterator it = list.begin(); it != list.end(); it++){
            bool strFound = !strcmp(it->c_str(), str);
            if(strFound) return false;
        }
        list.push_back(str);
        return true;
    }
}

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
    unsigned char* ptr = (unsigned char*)data;
    unsigned char* end;
    if(Fail()){
        static DebugNotifyOncer _dw;
        const char* str = MakeString("Stream error: Can't read from %s", Name());
        if(AddToNotifies(str, _dw.mNotifies)){
            TheDebug.Notify(str);
        }
        memset(data, 0, bytes);
    }
    else {
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
    const unsigned char* data;
    char crypt[512];
    int buf_size, i;
    unsigned char c;
    if(Fail()){
        const char* str = MakeString("Stream error: Can't write to %s\n", Name());
//     pcVar3 = (char *)(**(code **)((int)this->vtable + 0x1c))(this);
//     pcVar3 = ::MakeString(s_Stream_error:_Can't_write_to_%s_80bba789,pcVar3);
//     iVar2 = strcmp(@LOCAL@Write__9BinStreamFPCvi@_dw,pcVar3);
//     if (iVar2 != 0) {
//       strcpy(@LOCAL@Write__9BinStreamFPCvi@_dw,pcVar3);
//       Debug::Print((Debug *)TheDebug,pcVar3);
//     }
    }
}

// void __thiscall BinStream::Write(BinStream *this,void *param_1,int param_2)

// {
//   byte bVar1;
//   int iVar2;
//   char *pcVar3;
//   byte bVar4;
//   int iVar5;
//   byte *pbVar6;
//   byte *pbVar7;
//   byte local_228 [524];
  
//   iVar2 = (**(code **)((int)this->vtable + 0x18))();
//   if (iVar2 == 0) {
//     if (this->mCrypto == (Rand2 *)0x0) {
//       (**(code **)((int)this->vtable + 0x2c))(this,param_1,param_2);
//     }
//     else {
//       for (; 0 < param_2; param_2 = param_2 + -0x200) {
//         iVar2 = 0x200;
//         if (param_2 < 0x200) {
//           iVar2 = param_2;
//         }
//         pbVar6 = local_228;
//         pbVar7 = (byte *)param_1;
//         for (iVar5 = 0; iVar5 < iVar2; iVar5 = iVar5 + 1) {
//           bVar4 = Rand2::Int(this->mCrypto);
//           bVar1 = *pbVar7;
//           pbVar7 = pbVar7 + 1;
//           *pbVar6 = bVar4 ^ bVar1;
//           pbVar6 = pbVar6 + 1;
//         }
//         (**(code **)((int)this->vtable + 0x2c))(this,local_228,iVar2);
//         param_1 = (void *)((int)param_1 + 0x200);
//       }
//     }
//   }
//   else {
//     pcVar3 = (char *)(**(code **)((int)this->vtable + 0x1c))(this);
//     pcVar3 = ::MakeString(s_Stream_error:_Can't_write_to_%s_80bba789,pcVar3);
//     iVar2 = strcmp(@LOCAL@Write__9BinStreamFPCvi@_dw,pcVar3);
//     if (iVar2 != 0) {
//       strcpy(@LOCAL@Write__9BinStreamFPCvi@_dw,pcVar3);
//       Debug::Print((Debug *)TheDebug,pcVar3);
//     }
//   }
//   return;
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

void BinStream::Seek(int offset, SeekType type){
    MILO_ASSERT(!Fail(), 0xDF);
    MILO_ASSERT(!mCrypto, 0xE2);
    SeekImpl(offset, type);
}

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
