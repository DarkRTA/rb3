#ifndef OS_THREADCALL_H
#define OS_THREADCALL_H

class ThreadCallback {
    public:
    ThreadCallback() {}
    virtual ~ThreadCallback() {}
    virtual void ThreadStart() = 0;
    virtual void ThreadDone(int) = 0;
};

void ThreadCallPreInit();
void ThreadCallInit();
void ThreadCallTerminate();
void ThreadCall(int(*)(void), void (*)(int));
void ThreadCall(ThreadCallback*);
void ThreadCallPoll();

#endif // OS_THREADCALL_H
