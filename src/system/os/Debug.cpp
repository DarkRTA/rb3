#include "os/Debug.h"
#include "os/HolmesClient.h"
#include "os/OSFuncs.h"
#include "utl/MakeString.h"
#include "utl/Option.h"
#include "utl/MemMgr.h"
#include "os/System.h"
#include "os/Timer.h"
#include <revolution/os.h>
#include <cstdlib>
#include <vector>

#include "decomp.h"

Debug TheDebug;
std::vector<String> gNotifies;
static int* gpDbgFrameID;

const GXColor DebugTextColor = { 255, 255, 255, 255 };
const GXColor DebugBGColor = { 0x80, 0, 0, 255 };

DECOMP_FORCEACTIVE(Debug,
    "%s",
    "no_try",
    "log",
    "no_modal",
    "no_notify",
    __FILE__,
    "MainThread()",

    // Temp strings needed for string pooling to match
    "TRY conditional not exited %d",
    "\n\n-- Program ended --\n",
    "%s\n",
    "THREAD-NOTIFY not called in MainThread: %s\n",
    "NOTIFY: %s\n",
    "main",
    "THREAD-FAIL: %s\n",
    "FAIL-MSG: %s\n",
    "APP FAILED\n",
    "n/a",
    "version",
    "<unknown>",
    "\n\nConsoleName: %s   %s   Plat: %s   ",
    "\nLang: %s   SystemConfig: %s",
    "true",
    "false",
    "\nUptime: %.2f hrs   UsingCD: %s   SDK: %s",
    "debug/fail",
    "msg",
    "callstack",
    "dataCallstack",
    "cheatsMsg",
    "FAIL: %s\n",
    "APP EXITED, EXIT CODE %d\n",
    "Debug::Print"
)

int DbgGetFrameID() {
    if (gpDbgFrameID) return *gpDbgFrameID;
    else return 0;
}

void* Debug::SetModalCallback(ModalCallbackFunc* func){
    if(mNoModal) return 0;
    ModalCallbackFunc* oldFunc = mModalCallback;
    mModalCallback = func;
    if(!gNotifies.empty()){
        for(int i = 0; i < gNotifies.size(); i++){
            MILO_WARN("%s", gNotifies[i].c_str());
        }
    }
    return oldFunc;
}

void Debug::Init(){
    mNoTry = OptionBool("no_try", false);
    const char* logStr = OptionStr("log", 0);
    if(logStr) StartLog(logStr, true);
    if(OptionBool("no_modal", false)){
        SetModalCallback(0);
        mNoModal = true;
    }
    if(OptionBool("no_notify", false)){
        SetDisabled(true);
    }
    const char* logStr2 = OptionStr("log", 0);
    if(logStr2) StartLog(logStr2, true);
}

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
    if(fail) strcat(msg, "\n\n-- Program ended --\n");
    else {
        String str(msg);
        gNotifies.push_back(str);
    }
    TheDebug << MakeString("%s\n", msg);
    if(wait && fail){
        OSFatal(DebugTextColor, DebugBGColor, msg);
    }
}

void Debug::SetTry(bool b){
    MILO_ASSERT(MainThread(), 0x117);
    if(!mNoTry){
        if(b){
            mTry++;
        }
        else mTry--;
    }
}

void Debug::SetDisabled(bool b){
    mNoDebug = b;
}

void Debug::Notify(const char* msg){
    if(!mNoDebug){
        if(!MainThread())
            TheDebug << MakeString("THREAD-NOTIFY not called in MainThread: %s\n", msg);
        else TheDebug << MakeString("NOTIFY: %s\n", msg);
    }
}

void Debug::Fail(const char* msg){
    static int x = MemFindHeap("main");
    MemPushHeap(x);
    if(mNoDebug) MemPopHeap();
    else {
        if(!MainThread()){
            CaptureStackTrace(0x32, mFailThreadStack);
            mFailThreadMsg = msg;
            TheDebug << MakeString("THREAD-FAIL: %s\n", msg);
            do {
                Timer::Sleep(200);
                PlatformDebugBreak();
            } while(true);
        }
        if(mTry != 0){
            mTry--;
            // jump happens here
        }
        if(mFailing) MemPopHeap();
        else {
            mFailing = true;
            for(std::list<ModalCallbackFunc*>::iterator it = mFailCallbacks.begin(); it != mFailCallbacks.end(); it++){
                bool b;
                (*it)(b, 0, 0);
            }
            mFailCallbacks.clear();
            bool asdf = true;
            Modal(asdf, msg);
            if(!asdf) mFailing = false;
            else PlatformDebugBreak();
            MemPopHeap();
        }
    }
}

void Debug::Exit(int status, bool actually_exit) {
    mExiting = true;
    for(std::list<ExitCallbackFunc*>::iterator it = mExitCallbacks.begin(); it != mExitCallbacks.end(); it++){
        (*it)();
    }
    mExitCallbacks.clear();
    TheDebug << MakeString("APP EXITED, EXIT CODE %d\n", status);
    StopLog();
    HolmesClientTerminate();
    if (actually_exit) exit(status);
}

void Debug::RemoveExitCallback(ExitCallbackFunc* func){
    if(!mExiting) mExitCallbacks.remove(func);
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

Debug::Debug() : mNoDebug(0), mFailing(0), mExiting(0), mNoTry(0), mNoModal(0), mTry(0), mLog(0), mReflect(0), mModalCallback(DebugModal), mFailThreadMsg(0), mNotifyThreadMsg(0) {

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
