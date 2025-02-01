#pragma once

class ThreadCallback {
public:
    ThreadCallback() {}
    virtual ~ThreadCallback() {}
    virtual int ThreadStart() = 0;
    virtual void ThreadDone(int) = 0;
};

enum ThreadCallDataType {
    kTCDT_None = 0,
    kTCDT_Func = 1,
    kTCDT_Class = 2,
};

struct ThreadCallData {
    ThreadCallDataType mType;
    int (*mFunc)();
    void (*mCallback)(int);
    ThreadCallback *mClass;
    int mArg;
};

void ThreadCallPreInit();
void ThreadCallInit();
void ThreadCallTerminate();
void ThreadCall(int (*)(void), void (*)(int));
void ThreadCall(ThreadCallback *);
void ThreadCallPoll();
