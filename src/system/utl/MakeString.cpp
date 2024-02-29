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
static int gNum[1];
static OSThread* gThreadIds[1];
static int gCurThread;
static int gNumThreads;

static char* NextBuf(){
    int tID;
    int i2;
    if(!gLock){
        InitMakeString();
        TheDebug << MakeString("MakeString before InitMakeString!\n");
        MILO_FAIL("MakeString before InitMakeString!");
    }
    if(gLock){
        gLock->Enter();
    }
    if(gNumThreads == 0){
        *gThreadIds = OSGetCurrentThread();
        gNumThreads = 1;
        tID = gCurThread;
    }
    else {
        OSThread* tptr = gThreadIds[0];
        tID = gCurThread;
        if(gThreadIds[gCurThread] != OSGetCurrentThread()){
            tID = 0;
            for(; tID < gNumThreads && tptr != OSGetCurrentThread(); tptr++) tID++;
            if(tID == gNumThreads){
                tID = 0;
                if(0 < gNumThreads){
                    if(8 < gNumThreads){
                        bool b = false;
                        if((-1 < gNumThreads) && (gNumThreads < 0x7FFFFFFF)){
                            b = true;
                        }
                        unsigned int butt;
                        if(b && (butt = gNumThreads - 1U >> 3, 0 < gNumThreads - 8)){
                            while(butt != 0){
                                tID += 8;
                                butt -= 1;
                            }
                        }
                    }
                    i2 = gNumThreads - tID;
                    if(tID < gNumThreads){
                        do {
                            tID++;
                            i2--;
                        } while(i2 != 0);
                    }
                }
                if(tID == gNumThreads){
                    MILO_ASSERT(gNumThreads < MAX_BUF_THREADS, 0x5F);
                    gNumThreads++;
                    gThreadIds[tID] = OSGetCurrentThread();
                }
            }

        }
    }
    gCurThread = tID;
    tID = gCurThread;
    i2 = gNum[gCurThread] + 1;
    char* c5 = gBuf[gCurThread][gNum[gCurThread]];
    gNum[gCurThread] = i2;
    if(i2 == 10){
        gNum[tID] = 0;
    }
    if(gLock) gLock->Exit();
    return c5;
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
