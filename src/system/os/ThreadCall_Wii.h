#ifndef OS_THREADCALLWII_H
#define OS_THREADCALLWII_H

void ThreadCallPreInit();
void ThreadCallInit();
void ThreadCallTerminate();
void ThreadCall(int(*)(void), void (*)(int));
// void ThreadCall(ThreadCallback*);
void ThreadCallPoll();

#endif // OS_THREADCALLWII_H
