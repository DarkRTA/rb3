#ifndef OS_DEBUG_H
#define OS_DEBUG_H

#include "utl/TextStream.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
#include "utl/TextFileStream.h"

#include <list>
#include <string.h>
#include <setjmp.h>

typedef void ModalCallbackFunc(bool&, char*, bool);
typedef void ExitCallbackFunc(void);

class Debug : public TextStream {
public:

    bool mNoDebug; // 0x4
    bool mFailing; // 0x5
    bool mExiting; // 0x6
    bool mNoTry; // 0x7
    bool mNoModal; // 0x8
    int mTry; // 0xc
    TextFileStream* mLog; // 0x10
    bool mAlwaysFlush; // 0x14
    TextStream* mReflect; // 0x18
    ModalCallbackFunc* mModalCallback; // 0x1c
    std::list<ExitCallbackFunc*> mFailCallbacks; // 0x20
    std::list<ExitCallbackFunc*> mExitCallbacks; // 0x28
    unsigned int mFailThreadStack[50]; // starts at 0x30
    const char* mFailThreadMsg; // 0xf8
    const char* mNotifyThreadMsg; // 0xfc

    Debug();
    virtual ~Debug();
    virtual void Print(const char*);

    void Poll();
    void SetDisabled(bool);
    void SetTry(bool);
    void AddExitCallback(ExitCallbackFunc* func){
        mExitCallbacks.push_back(func);
    }
    void RemoveExitCallback(ExitCallbackFunc*);
    void StartLog(const char*, bool);
    void StopLog();
    void Init();
    void* SetModalCallback(ModalCallbackFunc*);
    void Exit(int, bool);
    void Modal(bool&, const char*);

    void Notify(const char* msg);
    void Fail(const char* msg);
    TextStream* SetReflect(TextStream* ts){
        TextStream* ret = mReflect;
        mReflect = ts;
        return ret;
    }
};

extern Debug TheDebug;
extern jmp_buf TheDebugJump;

extern const char* kAssertStr;
extern int* gpDbgFrameID;

#ifdef MILO_DEBUG
#  define MILO_ASSERT(cond, line) ((cond) || (TheDebugFailer << (MakeString(kAssertStr, __FILE__, line, #cond)), 0))
#  define MILO_ASSERT_FMT(cond, ...) ((cond) || (TheDebugFailer << (MakeString(__VA_ARGS__)), 0))
#  define MILO_FAIL(...) TheDebugFailer << MakeString(__VA_ARGS__)
#  define MILO_WARN(...) TheDebugNotifier << MakeString(__VA_ARGS__)
#  define MILO_LOG(...) TheDebug << MakeString(__VA_ARGS__)

// Usage:
// MILO_TRY(errMsg) {
//     // The code to try
// } MILO_CATCH {
//     // errMsg is valid here
// }
#  define MILO_TRY \
    TheDebug.SetTry(true); \
    /* Undefined behavior alert! \
     * The return of setjmp should only be used in control flow, \
     * but here it's used to propogate an error message. \
     */ \
    const char* _msg = (const char*)setjmp(TheDebugJump); \
    if (_msg == nullptr) { \
        do
#  define MILO_CATCH(msgName) \
        while (false); \
        TheDebug.SetTry(false); \
    } else if (const char* msgName = _msg)
#else
   // The actual conditions for asserts appear to still be evaluated in retail,
   // various random calls are left over from asserts that exist in debug
#  define MILO_ASSERT(cond, line) (void)(cond)
#  define MILO_ASSERT_FMT(cond, ...) (void)(cond)
#  define MILO_FAIL(...) ((void)0)
#  define MILO_WARN(...) (void)(__VA_ARGS__)
#  define MILO_LOG(...) (void)(__VA_ARGS__)

#  define MILO_TRY if (true)
#  define MILO_CATCH(msgName) else if (const char* msgName = nullptr)
#endif

class DebugNotifier {
public:
    DebugNotifier& operator<<(const char* c){
        TheDebug.Notify(c);
        return *this;
    }
};

extern DebugNotifier TheDebugNotifier;

class DebugFailer {
public:
    DebugFailer& operator<<(const char* cc){
        TheDebug.Fail(cc);
        return *this;
    }
};

extern DebugFailer TheDebugFailer;

namespace {
    bool AddToNotifies(const char* name, std::list<String>& notifies){
        if (notifies.size() > 16) {
            return false;
        }

        for (std::list<String>::iterator it = notifies.begin(); it != notifies.end(); it++){ \
            bool equal = !strcmp(it->c_str(), name);
            if (equal) {
                return false;
            }
        }

        notifies.push_back(name);
        return true;
    }
}

class DebugNotifyOncer {
public:
    std::list<String> mNotifies;
    DebugNotifyOncer(){}
    ~DebugNotifyOncer(){}

    DebugNotifyOncer& operator<<(const char* cc){
        if(AddToNotifies(cc, mNotifies)){
            TheDebugNotifier << cc;
        }
        return *this;
    }
};
#ifdef MILO_DEBUG
    #define MILO_NOTIFY_ONCE(...) { \
            static DebugNotifyOncer _dw; \
            _dw << MakeString(__VA_ARGS__); \
        }
#else
    #define MILO_NOTIFY_ONCE(...){}
#endif

#endif
