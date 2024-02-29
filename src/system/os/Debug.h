#ifndef OS_DEBUG_H
#define OS_DEBUG_H
#include "utl/TextStream.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
#include "utl/TextFileStream.h"
#include <list>

typedef void ModalCallbackFunc(bool&, char*, bool);
typedef void ExitCallbackFunc(void);

class Debug : public TextStream {
public:
    bool mDisabled;
    bool mExiting;
    bool mNoTry;
    bool mNoModal;
    bool unk8;
    int mTry;
    TextFileStream* mLog;
    bool mAlwaysFlush;
    TextStream* mReflect;
    ModalCallbackFunc* mModalCallback;
    std::list<ModalCallbackFunc*> mFailCallbacks;
    std::list<ExitCallbackFunc*> mExitCallbacks;
    unsigned int mFailThreadStack[50];
    const char* mFailThreadMsg;
    const char* mNotifyThreadMsg;

    Debug();
    virtual ~Debug();
    virtual void Print(const char*);

    void Poll();
    void SetDisabled(bool);
    void SetTry(bool);
    void RemoveExitCallback(ExitCallbackFunc*);
    void StartLog(const char*, bool);
    void StopLog();

    void Notify(const char* msg);
    void Fail(const char* msg);
    TextStream* SetReflect(TextStream* ts){
        TextStream* ret = mReflect;
        mReflect = ts;
        return ret;
    }
};

extern Debug TheDebug;
extern const char* kAssertStr;

#define MILO_ASSERT(cond, line) ((cond) || (TheDebug.Fail(MakeString(kAssertStr, __FILE__, line, #cond)), 0))
#define MILO_FAIL(...) TheDebug.Fail(MakeString(__VA_ARGS__))
#define MILO_WARN(...) TheDebug.Notify(MakeString(__VA_ARGS__))

class DebugNotifier {
public:
    DebugNotifier& operator<<(const char* c){ TheDebug.Notify(c); }
};

#endif
