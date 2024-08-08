#pragma once

#include "movie/TexMovie.h"
#include "os/CritSec.h"
#include "os/SynchronizationEvent.h"
#include "os/Timer.h"
#include "revolution/os/OSThread.h"
#include "rndobj/Dir.h"
#include <list>

class Splash {
public:
    enum SplashState {
        s0,
        s1,
        s2,
        s3,
        kResuming,
        kResumed, 
        kWaitingForTerminating,
        kTerminating,
        kTerminated
    };

    struct ScreenParams {
        const char* unk_0x0;
        int unk_0x4;
    };

    struct PreparedScreenParams {
        RndDir* unk_0x0;
        int unk_0x4;
    };

    Splash();
    virtual ~Splash();
    virtual void Draw();
    void BeginSplasher();
    void EndSplasher();
    void Suspend();
    void Resume();
    int SetMutableState(SplashState);
    int SetImmutableState(SplashState);
    void SetWaitForSplash(bool);
    void AddScreen(const char*, int);
    int PrepareNext();
    void PrepareRemaining();
    void Poll();
    bool UpdateThreadLoop();
    void WaitForState(SplashState);
    void CheckWorkerSuspend(bool);
    void UpdateThread();
    int ShowNext();
    void Show();
    void CheckHomeMenuButton();

    static int ThreadStart(void*);

    int mSplashTime; // 0x4
    bool mWaitForSplash; // 0x8
    std::list<ScreenParams> mScreens; // 0xC
    Timer unk_0x18;
    RndDir* mLastSplash; // 0x48
    int unk_0x4C;
    TexMovie* unk_0x50;
    int unk_0x54, unk_0x58;
    u8 unk_0x5C;
    int mSuspendCount; // 0x60
    bool unk_0x64;
    int unk_0x68;
    CriticalSection unk_0x6C;
    SynchronizationEvent unk_0x88;
    SynchronizationEvent unk_0xAC;
    int mState; // 0xD0
    CriticalSection unk_0xD4;
    std::list<PreparedScreenParams> mPreparedScreens; // 0xF0
    std::list<RndDir*> unk_0xF8;
    Timer unk_0x100;
    void* mThreadStack; // 0x130
    OSThread mThread; // 0x138
};

extern Splash* TheSplasher;

void PollFunc();
void SuspendFunc();
void ResumeFunc();
