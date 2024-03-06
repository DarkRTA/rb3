#include "os/Debug.h"
#include "os/OSFuncs.h"
#include <vector>

Debug TheDebug;
std::vector<String> gNotifies;

// Temp strings needed for string pooling to match
const char* s0 = "%s";
const char* s1 = "no_try";
const char* s2 = "log";
const char* s3 = "no_modal";
const char* s4 = "no_notify";
const char* s5 = "Debug.cpp";
const char* s6 = "MainThread()";
const char* s7 = "TRY conditional not exited %d";
const char* s8idk = "\n\n-- Program ended --\n";
const char* s9 = "%s\n";
const char* s10 = "THREAD-NOTIFY not called in MainThread: %s\n";
const char* s11 = "NOTIFY: %s\n";
const char* s12 = "main";
const char* s13 = "THREAD-FAIL: %s\n";
const char* s14 = "FAIL-MSG: %s\n";
const char* s15 = "APP FAILED\n";
const char* s16idk = "n/a";
const char* s17 = "version";
const char* s18 = "<unknown>";
const char* s19 = "\n\nConsoleName: %s   %s   Plat: %s   ";
const char* s20 = "\nLang: %s   SystemConfig: %s";
const char* s21 = "true";
const char* s22 = "false";
const char* s23 = "\nUptime: %.2f hrs   UsingCD: %s   SDK: %s";
const char* s24 = "debug/fail";
const char* s25 = "msg";
const char* s26 = "callstack";
const char* s27 = "dataCallstack";
const char* s28 = "cheatsMsg";
const char* s29 = "FAIL: %s\n";
const char* s30 = "APP EXITED, EXIT CODE %d\n";
const char* s31 = "Debug::Print";

void Debug::Poll(){
    MILO_ASSERT(MainThread(), 0xC5);
    if(mTry != 0){
        int tmp = mTry;
        mTry = 0;
        MILO_FAIL("TRY conditional not exited %d", tmp);
    }
    if(mFailThreadMsg) Fail(mFailThreadMsg);
}

static void DebugModal(bool& fail, char* msg, bool wait){

}

void Debug::SetTry(bool b){
    MILO_ASSERT(MainThread(), 0x117);
    if(!mNoModal){
        if(b){
            mTry++;
        }
        else mTry--;
    }
}

void Debug::SetDisabled(bool b){
    mDisabled = b;
}

void Debug::Notify(const char* msg){
    if(!mDisabled){
        if(!MainThread())
            TheDebug << MakeString("THREAD-NOTIFY not called in MainThread: %s\n", msg);
        else TheDebug << MakeString("NOTIFY: %s\n", msg);
    }
}

void Debug::RemoveExitCallback(ExitCallbackFunc* func){
    if(!mNoTry) mExitCallbacks.remove(func);
}

void Debug::StartLog(const char* file, bool always_flush){
    delete mLog;
    mLog = 0;
    mLog = new TextFileStream(file, false);
    mAlwaysFlush = always_flush;
    if(mLog->mFile.Fail()){
        MILO_WARN("Couldn't open log %s", file);
        delete mLog;
        mLog = 0;
    }
}

void Debug::StopLog(){
    delete mLog;
    mLog = 0;
}

Debug::Debug() : mDisabled(0), mExiting(0), mNoTry(0), mNoModal(0), unk8(0), mTry(0), mLog(0), mReflect(0), mModalCallback(DebugModal), mFailThreadMsg(0), mNotifyThreadMsg(0) {

}

Debug::~Debug(){
    StopLog();
}

// Declared in stlport/_vector.h since it's not relevant anywhere else
void std_vec_range_assert(size_t value, size_t max, const char *func) {
    if (value > (max / 4)) {
        MILO_FAIL("std::vector::%s: index range exceeded (0x%08x > 0x%08x)\n", func, value, (max / 4));
    }
}

const char* kAssertStr = "File: %s Line: %d Error: %s\n";
