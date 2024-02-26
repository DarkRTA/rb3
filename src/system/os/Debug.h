#ifndef OS_DEBUG_H
#define OS_DEBUG_H
#include "utl/TextStream.h"
#include "utl/Str.h"
#include "utl/MakeString.h"

class Debug : public TextStream {
public:
    bool mFailing;
    bool mExiting;
    bool mNoTry;
    bool mNoModal;
    int mTry;

    virtual ~Debug();
    virtual void Print(const char*);

    void Notify(const char* msg);
    void Fail(const char* msg);
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

// class Debug : public TextStream {
//     // total size: 0xFC
//     unsigned char mFailing; // offset 0x4, size 0x1
//     unsigned char mExiting; // offset 0x5, size 0x1
//     unsigned char mNoTry; // offset 0x6, size 0x1
//     unsigned char mNoModal; // offset 0x7, size 0x1
//     int mTry; // offset 0x8, size 0x4
//     class TextFileStream * mLog; // offset 0xC, size 0x4
//     unsigned char mAlwaysFlush; // offset 0x10, size 0x1
//     class TextStream * mReflect; // offset 0x14, size 0x4
//     void (* mModalCallback)(unsigned char &, char *, unsigned char); // offset 0x18, size 0x4
//     class list mFailCallbacks; // offset 0x1C, size 0x8
//     class list mExitCallbacks; // offset 0x24, size 0x8
//     unsigned int mFailThreadStack[50]; // offset 0x2C, size 0xC8
//     const char * mFailThreadMsg; // offset 0xF4, size 0x4
//     const char * mNotifyThreadMsg; // offset 0xF8, size 0x4
// };
