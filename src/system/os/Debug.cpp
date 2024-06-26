#include "os/Debug.h"
#include "os/AppChild.h"
#include "os/HolmesClient.h"
#include "os/OSFuncs.h"
#include "obj/DataUtl.h"
#include "utl/Cheats.h"
#include "utl/DataPointMgr.h"
#include "utl/MakeString.h"
#include "utl/Option.h"
#include "utl/MemMgr.h"
#include "utl/Loader.h"
#include "os/NetworkSocket.h"
#include "os/System.h"
#include "os/Timer.h"

#include <revolution/os.h>
#include <cstdlib>
#include <vector>

#include "decomp.h"

Debug TheDebug;
jmp_buf TheDebugJump;

static int* gpDbgFrameID;
std::vector<String> gNotifies;

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
        gNotifies.clear();
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

#pragma push
#pragma pool_data off
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
            longjmp(&TheDebugJump, (int)msg);
        }
        if(mFailing) MemPopHeap();
        else {
            mFailing = true;
            for(std::list<ExitCallbackFunc*>::iterator it = mFailCallbacks.begin(); it != mFailCallbacks.end(); it++){
                (*it)();
            }
            mFailCallbacks.clear();
            bool fail = true;
            Modal(fail, msg);
            if(!fail) mFailing = false;
            else PlatformDebugBreak();
            MemPopHeap();
        }
    }
}
#pragma pop

void Debug::Modal(bool& fail, const char* msg) {
    char modalMsg[4096];
    strcpy(modalMsg, msg);

    if (fail) {
        TheDebug << MakeString("FAIL-MSG: %s\n", msg);

        char shortMsg[256];
        int msgLen = strlen(msg);
        int shortMsgLen = sizeof(shortMsg) - 1;
        strcpy(shortMsg, gNullStr);
        strncat(shortMsg, msg, MINEQ(msgLen, shortMsgLen));

        char cheatsMsg[256];
        char dataCallstack[512];
        char callstack[2048];
        strcpy(cheatsMsg, gNullStr);
        strcpy(dataCallstack, gNullStr);
        strcpy(callstack, gNullStr);

        FormatString format("APP FAILED\n");
        TheDebug << format.Str();

        if (mModalCallback) {
            mModalCallback(fail, modalMsg, false);
        }

        if (mFailThreadMsg) {
            AppendThreadStackTrace(modalMsg, mFailThreadStack);
        } else {
            String sdk;
            sdk = "n/a";

            String config;
            String version;
            if (SystemConfig()) {
                config = SystemConfig()->File();
                SystemConfig()->FindData("version", version, false);
            } else {
                config = "<unknown>";
            }

            strcat(modalMsg, MakeString("\n\nConsoleName: %s   %s   Plat: %s   ",
                NetworkSocket::GetHostName(),
                version,
                PlatformSymbol(TheLoadMgr.GetPlatform())
            ));
            strcat(modalMsg, MakeString("\nLang: %s   SystemConfig: %s",
                SystemLanguage(),
                config
            ));
            strcat(modalMsg, MakeString("\nUptime: %.2f hrs   UsingCD: %s   SDK: %s",
                SystemMs() * (1 / 3600000.0),
                UsingCD() ? "true" : "false",
                sdk
            ));

            DataAppendStackTrace(dataCallstack);
            strncat(modalMsg, dataCallstack, sizeof(dataCallstack));
            AppendStackTrace(callstack);
            strncat(modalMsg, callstack, sizeof(callstack));
            AppendCheatsLog(cheatsMsg);
            strncat(modalMsg, cheatsMsg, sizeof(cheatsMsg));
        }

        if (TheAppChild) {
            TheAppChild->Sync(2);
        }

        if (UsingCD()) {
            SendDataPoint("debug/fail",
                "msg", shortMsg,
                "callstack", callstack,
                "dataCallstack", dataCallstack,
                "cheatsMsg", cheatsMsg
            );
        }
    }

    if (mModalCallback) {
        mModalCallback(fail, modalMsg, true);
    } else {
        if (fail)  {
            TheDebug << MakeString("FAIL: %s\n", modalMsg);
        } else {
            if (!mNoDebug) {
                TheDebug << MakeString("NOTIFY: %s\n", modalMsg);
            }
        }
    }

    if (fail) {
        if (mModalCallback) {
            PlatformDebugBreak();
        }
        Exit(1, true);
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

void Debug::Print(const char* msg) {
    AutoSlowFrame asf("Debug::Print");

    if (mLog && !mLog->mFile.Fail()) {
        mLog->Print(msg);
        if (mAlwaysFlush) {
            mLog->mFile.Flush();
        }
    }

    if (MainThread() && mReflect) {
        mReflect->Print(msg);
    }

    if (!UsingCD()) {
        HolmesClientPrint(msg);
    }

    char msgChunk[256];
    size_t msglen = strlen(msg);
    const char* msgEnd = msg + msglen;
    for (; msg + ARRAY_LENGTH(msgChunk) < msgEnd; msg += ARRAY_LENGTH(msgChunk)) {
        strncpy(msgChunk, msg, ARRAY_LENGTH(msgChunk));
        msgChunk[ARRAY_LENGTH(msgChunk) - 1] = 0;
        OSReport("%s", msgChunk);
    }
    OSReport("%s", msg);
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
