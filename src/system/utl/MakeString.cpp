#include "utl/MakeString.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "os/CritSec.h"
#include "utl/PoolAlloc.h"
#include <new>

static CriticalSection* gLock;
static char*** gBuf;

static char* NextBuf(){

}

void InitMakeString(){
    if(gLock == 0){
        gLock = new (_PoolAlloc(0x1C, 0x1C, FastPool)) CriticalSection();
    }
}

// void InitMakeString(void)

// {
//   CriticalSection *this;
//   undefined4 uVar1;
//   int iVar2;
//   int iVar3;
//   int iVar4;
//   int iVar5;
  
//   if (gLock == (CriticalSection *)0x0) {
//     this = (CriticalSection *)_PoolAlloc(0x1c,0x1c,1);
//     if (this != (CriticalSection *)0x0) {
//       this = (CriticalSection *)CriticalSection::CriticalSection(this);
//     }
//     gLock = this;
//     gBuf = _MemAlloc(0x18,0);
//     iVar3 = 0;
//     iVar5 = 0;
//     do {
//       uVar1 = _MemAlloc(0x28,0);
//       iVar2 = 0;
//       iVar4 = 0;
//       *(undefined4 *)(gBuf + iVar5) = uVar1;
//       do {
//         uVar1 = _MemAlloc(0x800,0);
//         iVar2 = iVar2 + 1;
//         *(undefined4 *)(*(int *)(iVar5 + gBuf) + iVar4) = uVar1;
//         iVar4 = iVar4 + 4;
//       } while (iVar2 < 10);
//       iVar3 = iVar3 + 1;
//       iVar5 = iVar5 + 4;
//     } while (iVar3 < 6);
//   }
//   return;
// }

bool MakeStringInitted(){
    return gLock != 0;
}

void TerminateMakeString(){}

FormatString::FormatString(){
    mNextBuf = NextBuf();
    mBufSize = 2048;
    mFmt = 0;
}

FormatString::FormatString(const char* str){
    mNextBuf = NextBuf();
    mBufSize = 2048;
    mFmt = 0;
    InitializeWithFmt(str, true);
}

void FormatString::InitializeWithFmt(const char* fmt, bool b){
    MILO_ASSERT(fmt, 0xA4);
    if(!StrNCopy(mFmtBuf, fmt, 2048)){
        MILO_WARN("Increase mFmtBuf size to %d", strlen(fmt));
    }
    mBuf = mFmtBuf;
    if(b) UpdateType();
}

void FormatString::UpdateType(){
    if(mFmt != 0){
        mBuf = mFmt;
        mFmt = 0;
    }

    int val = 0;
    char* ptr = mBuf;
    for(; *ptr != '\0'; ptr++){
        if (*ptr == '%') {
            if (ptr[1] == '%')
                ptr++; // '%' escape
            else if (val != 0)
                break;
            else
                val = 1;
        } else if (val == 1) {
            if (*ptr < 'A' || *ptr > 'z')
                continue;
            if (*ptr == 'f' || *ptr == 'g') {
                mType = kFloat;
            } else if (*ptr == 's') {
                mType = kStr;
            } else {
                mType = kInt;
            }
            val = 2;
        }
    }
    if(val == 1){
        MILO_WARN("FormatString: unable to identify %s", mBuf);
    }
    if(val == 0) mType = kNone;
    mFmt = ptr;
}

FormatString& FormatString::operator<<(void* v){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, v);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0xDF);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned int ui){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, ui);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0xE5);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned long ul){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, ul);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0xEB);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(long l){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, l);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0xF1);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned long long ull){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, ull);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0xF8);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(int i){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, i);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x105);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const DataNode& node){
    char tmp = *mFmt;
    *mFmt = '\0';

    int n;
    if(mType == kInt){
        n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, node.LiteralInt(0));
    }
    else if(mType == kFloat){
        n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, node.LiteralFloat(0));
    }
    else if(mType == kStr){
        n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, node.LiteralStr(0));
    }
    else{
        MILO_WARN("FormatString: Couldn't convert DataNode to '%s'", mBuf);
        n = 0;
    }

    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x11B);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const char* cc){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mBuf, mFmtBuf);
    bool b = true;
    if(cc >= mNextBuf && cc < mNextBuf + 2048) b = false;
    if(!b) MILO_FAIL("FormatString: arg in buffer");
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, cc);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x12A);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(float f){
    if(mType != kFloat) MILO_WARN("FormatString: '%s' doesn't start with kFloat.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, f);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x130);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(double d){
    if(mType != kFloat) MILO_WARN("FormatString: '%s' doesn't start with kFloat.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, d);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x136);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const String& str){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, str.c_str());
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x13C);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(Symbol sym){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mBuf, mFmtBuf);
    char tmp = *mFmt;
    *mFmt = '\0';
    int n = snprintf(mNextBuf + 2048 - mBufSize, mBufSize, mBuf, sym.mStr);
    *mFmt = tmp;
    MILO_ASSERT(n >= 0, 0x142);
    mBufSize -= n;
    UpdateType();
    return *this;
}

const char* FormatString::Str(){
    if(mType != kNone) MILO_WARN("FormatString: '%s' doesn't start with kNone.  Format: '%s'", mBuf, mFmtBuf);
    if(*mBuf != '\0'){
        MILO_ASSERT(mFmtEnd - mFmt < mBufSize, 0x14B);
        strcpy(mNextBuf + 2048 - mBufSize, mBuf);
    }
    return mNextBuf;
}
