#include "utl/MakeString.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "os/CritSec.h"
#include "utl/PoolAlloc.h"
#include "utl/MemMgr.h"
#include <revolution/OS.h>
#include <new>

#define MAX_BUF_THREADS 6

static CriticalSection* gLock;
static char*** gBuf;
static int gNum[MAX_BUF_THREADS];
static OSThread* gThreadIds[MAX_BUF_THREADS];
static int gCurThread;
static int gNumThreads;

static char* NextBuf(){
    if(!gLock){
        InitMakeString();
        TheDebug << MakeString("MakeString before InitMakeString!\n");
        MILO_FAIL("MakeString before InitMakeString!");
    }

    CritSecTracker tracker(gLock);

    int i2;
    if(gNumThreads == 0){
        gThreadIds[0] = OSGetCurrentThread();
        gNumThreads = 1;
    }
    else {
        int tID;
        OSThread* curThread = OSGetCurrentThread();
        OSThread** tptr = &gThreadIds[0];
        if(gThreadIds[gCurThread] != curThread){
            for (tID = 0; tID < gNumThreads; tID++) {
                if (gThreadIds[tID] == OSGetCurrentThread()) {
                    break;
                }
            }

            if(tID == gNumThreads){
                for (tID = 0; tID < gNumThreads; tID++) {
                }

                if(tID == gNumThreads){
                    MILO_ASSERT(gNumThreads < MAX_BUF_THREADS, 0x5F);
                    gThreadIds[tID] = OSGetCurrentThread();
                    gNumThreads++;
                }
            }

            gCurThread = tID;
        }
    }

    char* buf = gBuf[gCurThread][gNum[gCurThread]];
    if(++gNum[gCurThread] == 10){
        gNum[gCurThread] = 0;
    }

    return buf;
}

void InitMakeString(){
    if(gLock == 0){
        gLock = new (_PoolAlloc(0x1C, 0x1C, FastPool)) CriticalSection();
        gBuf = (char***)_MemAlloc(0x18, 0);
        for(int i3 = 0, i5 = 0; i3 < 6; i3++, i5++){
            gBuf[i5] = (char**)_MemAlloc(0x28, 0);
            for(int i2 = 0, i4 = 0; i2 < 10; i2++, i4++){
                gBuf[i5][i4] = (char*)_MemAlloc(0x800, 0);
            }
        }
    }
}

bool MakeStringInitted(){
    return gLock != 0;
}

void TerminateMakeString(){}

FormatString::FormatString(){
    mBuf = NextBuf();
    mBufSize = 2048;
    mFmtEnd = 0;
}

FormatString::FormatString(const char* str){
    mBuf = NextBuf();
    mBufSize = 2048;
    mFmtEnd = 0;
    InitializeWithFmt(str, true);
}

void FormatString::InitializeWithFmt(const char* fmt, bool b){
    MILO_ASSERT(fmt, 0xA4);
    if(!StrNCopy(mFmtBuf, fmt, 2048)){
        MILO_WARN("Increase mFmtBuf size to %d", strlen(fmt));
    }
    mFmt = mFmtBuf;
    if(b) UpdateType();
}

void FormatString::UpdateType(){
    if(mFmtEnd != 0){
        mFmt = mFmtEnd;
        mFmtEnd = 0;
    }

    int val = 0;
    char* ptr = mFmt;
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
        MILO_WARN("FormatString: unable to identify %s", mFmt);
    }
    if(val == 0) mType = kNone;
    mFmtEnd = ptr;
}

FormatString& FormatString::operator<<(void* v){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, v);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0xDF);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned int ui){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, ui);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0xE5);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned long ul){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, ul);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0xEB);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(long l){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, l);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0xF1);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(unsigned long long ull){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, ull);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0xF8);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(int i){
    if(mType != kInt) MILO_WARN("FormatString: '%s' doesn't start with kInt.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, i);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x105);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const DataNode& node){
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';

    int n;
    if(mType == kInt){
        n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, node.LiteralInt(0));
    }
    else if(mType == kFloat){
        n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, node.LiteralFloat(0));
    }
    else if(mType == kStr){
        n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, node.LiteralStr(0));
    }
    else{
        MILO_WARN("FormatString: Couldn't convert DataNode to '%s'", mFmt);
        n = 0;
    }

    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x11B);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const char* cc){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mFmt, mFmtBuf);
    MILO_ASSERT_FMT(cc < mBuf || cc >= mBuf + sizeof(mFmtBuf), "FormatString: arg in buffer");
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + sizeof(mFmtBuf) - mBufSize, mBufSize, mFmt, cc);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x12A);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(float f){
    if(mType != kFloat) MILO_WARN("FormatString: '%s' doesn't start with kFloat.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, f);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x130);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(double d){
    if(mType != kFloat) MILO_WARN("FormatString: '%s' doesn't start with kFloat.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, d);
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x136);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(const String& str){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, str.c_str());
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x13C);
    mBufSize -= n;
    UpdateType();
    return *this;
}

FormatString& FormatString::operator<<(Symbol sym){
    if(mType != kStr) MILO_WARN("FormatString: '%s' doesn't start with kStr.  Format: '%s'", mFmt, mFmtBuf);
    char tmp = *mFmtEnd;
    *mFmtEnd = '\0';
    int n = snprintf(mBuf + 2048 - mBufSize, mBufSize, mFmt, sym.Str());
    *mFmtEnd = tmp;
    MILO_ASSERT(n >= 0, 0x142);
    mBufSize -= n;
    UpdateType();
    return *this;
}

const char* FormatString::Str(){
    if(mType != kNone) MILO_WARN("FormatString: '%s' doesn't start with kNone.  Format: '%s'", mFmt, mFmtBuf);
    if(*mFmt != '\0'){
        MILO_ASSERT(mFmtEnd - mFmt < mBufSize, 0x14B);
        strcpy(mBuf + 2048 - mBufSize, mFmt);
    }
    return mBuf;
}
