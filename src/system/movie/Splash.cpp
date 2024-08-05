#include "Splash.h"
#include "movie/TexMovie.h"
#include "obj/Dir.h"
#include "obj/Task.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "os/Joypad_Wii.h"
#include "os/OSFuncs.h"
#include "os/System.h"
#include "os/PlatformMgr.h"
#include "revolution/os/OSThread.h"
#include "revolution/os/OSTime.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "utl/MemMgr.h"
#include <revolution/VI.h>

bool gSplashing = false;
Splash* TheSplasher;

const char* kSplashMovie = "splash.tmov";
const char* kSplashCam = "splash.cam";

int Splash::ThreadStart(void* spl) {
    ((Splash*)spl)->UpdateThread();
    return 0;
}

Splash::Splash() : mSplashTime(SystemConfig("ui")->FindArray("splash_time", true)->Float(1) * 1000),
    mWaitForSplash(SystemConfig("ui")->FindArray("wait_for_splash", true)->Int(1)), mLastSplash(NULL), 
    unk_0x4C(0), unk_0x50(0), unk_0x54(0), unk_0x58(-1), mSuspendCount(0), unk_0x64(1), unk_0x68(0), mState(0) {
    
}

Splash::~Splash() { 
    MILO_ASSERT(!gSplashing, 80);
}

void PollFunc() {
    TheSplasher->Poll();
}

void SuspendFunc() {
    TheSplasher->Suspend();
}

void ResumeFunc() {
    TheSplasher->Resume();
}


void Splash::BeginSplasher() {
    if (unk_0x64) {
        MILO_ASSERT(!gSplashing, 100);
        gSplashing = true;
        MILO_ASSERT(!mPreparedScreens.empty(), 102);

        MILO_ASSERT(SetMutableState(kResuming), 104);
        {
            MemDoTempAllocations mdta(true, false);
            void* stack = _MemAlloc(0x20000, 0x20);
            mThreadStack = stack;
            OSCreateThread(&mThread, (OSThreadFunc)Splash::ThreadStart, this, (char*)stack + 0x20000, 0x20000, 0x0F, 1);
            mThread.specific[0] = (void*)"SplashThread";
            OSResumeThread(&mThread);
        }
        WaitForState(kResumed);
    } else {
        SetMutableState(kResumed);
        Show();
        Draw();
    }
    TheSplasher = this;
    SetRndSplasherCallback(PollFunc, SuspendFunc, ResumeFunc);
    TheRnd->unk130 = true;
}

void Splash::EndSplasher() {
    if (TheSplasher != NULL) {
        if (unk_0x64) {
            MILO_ASSERT(mScreens.empty(), 167);
            MILO_ASSERT(gSplashing, 168);

            MILO_ASSERT(SetImmutableState(kTerminating), 170);
            WaitForState(kTerminated);
            gSplashing = false;
        } else {
            while (ShowNext());
            MILO_ASSERT(SetImmutableState(kTerminated), 183);
        }
        TheSplasher = NULL;
        SetRndSplasherCallback(NULL, NULL, NULL);
        TheRnd->unk130 = false;
        for (std::list<RndDir*>::iterator it = unk_0xF8.begin(); it != unk_0xF8.end(); it++) {
            delete *it;
        }
        Movie::Validate();
        _MemFree(mThreadStack);
    }
}

void Splash::Suspend() {
    MILO_ASSERT(MainThread(), 207);
    if (++mSuspendCount <= 1) {
        if (unk_0x64) {
            if (SetMutableState(s1)) {
                WaitForState(s2);
                if (unk_0x50 != NULL) {
                    unk_0x50->mShowing = true;
                    unk_0x50->mMovie.LockThread();
                }
                unk_0x5C = false;
                Draw();
            } else {
                MILO_ASSERT(mState == kWaitingForTerminating, 235);
                if (unk_0x50 != NULL) {
                    unk_0x50->mShowing = true;
                    unk_0x50->mMovie.LockThread();
                }
            }
        } else {
            SetMutableState(s2);
        }
        
        unk_0x100.Reset();
    }
}

void Splash::Resume() {
    MILO_ASSERT(MainThread(), 257); 
    if (--mSuspendCount <= 0) {
        MILO_ASSERT(mSuspendCount == 0, 264);
        if (unk_0x64 != 0) {
            if (SetMutableState(s3)) {
                if (unk_0x50 != NULL) {
                    unk_0x50->mShowing = false;
                    unk_0x50->mMovie.UnlockThread();
                }
                MILO_ASSERT(SetMutableState(kResuming), 279);
                WaitForState(kResumed);
            } else {
                MILO_ASSERT(mState == kWaitingForTerminating, 285);
                if (unk_0x50 != NULL) {
                    unk_0x50->mShowing = false;
                    unk_0x50->mMovie.UnlockThread();
                }
            }
        } else {
            if (SetMutableState(kResumed) == 0) return;
            unk_0x5C = 0;
            Draw();
        }
    }
}

int Splash::SetMutableState(Splash::SplashState state) {
    MILO_ASSERT(state <= kResumed, 310);
    CriticalSection* cs = &unk_0x6C;
    if (cs) cs->Enter(); // ???
    if (mState <= kResumed) {
        mState = state;
        if (MainThread()) unk_0xAC.Set(); else unk_0x88.Set();
        if (cs) cs->Exit();
        return 1;
    } else {
        if (cs) cs->Exit();
        return 0;
    }
}

int Splash::SetImmutableState(Splash::SplashState state) {
    MILO_ASSERT(state > kResumed, 331);
    CriticalSection* cs = &unk_0x6C;
    if (cs) cs->Enter(); // ???
    if (mState >= kResumed && state > mState) {
        mState = state;
        if (MainThread()) unk_0xAC.Set(); else unk_0x88.Set();
        if (cs) cs->Exit();
        return 1;
    } else if (state == kWaitingForTerminating && mState == kTerminating) {
        if (cs) cs->Exit();
        return 1;
    } else {
        if (cs) cs->Exit();
        return 0;
    }
}

void Splash::SetWaitForSplash(bool b) {
    MILO_ASSERT(!gSplashing, 361);
    mWaitForSplash = b;
}

void Splash::AddScreen(const char* s, int i) {
    MILO_ASSERT(!gSplashing, 368);
    CriticalSection* cs = &unk_0xD4;
    ScreenParams sp; sp.unk_0x0 = s; sp.unk_0x4 = i;
    if (cs) cs->Enter();
    mScreens.push_back(sp);
    if (cs) cs->Exit();
}

int Splash::PrepareNext() {

}

void Splash::PrepareRemaining() {
    while (PrepareNext());
}

void Splash::Poll() {
    static bool finished;
    if (!unk_0x64 || mSuspendCount != 0) {
        if (!finished) {
            if (!UpdateThreadLoop()) {
                finished = true;
                int i = 0;
                do {
                    TheRnd->BeginDrawing();
                    TheRnd->EndDrawing();
                    i++;
                } while (i != 2);
            }
        }
    }
}

bool Splash::UpdateThreadLoop() {
    if (unk_0x18.SplitMs() > 1 && !ShowNext()) return true;
    Draw();
    if (mState == kTerminating) {
        if (!mWaitForSplash|| mLastSplash == NULL) {
            while (ShowNext());
            return false;
        }
    }
    return true;
}

void Splash::WaitForState(Splash::SplashState ss) {
    if (!unk_0x64) MILO_FAIL("Can't WaitForState");
    while (mState != ss) {
        if (ss == kResumed) {
            if (mState > kResumed) return;
        }
        if (MainThread()) {
            unk_0x88.Wait(-1);
        } else {
            unk_0xAC.Wait(-1);
        }
    }
}

void Splash::CheckWorkerSuspend(bool b) {
    MILO_ASSERT((gMainThreadID != CurrentThreadId()), 512);
}

void Splash::UpdateThread() {
    MILO_ASSERT(!MainThread(), 571);
    unk_0x6C.Enter();
}

int Splash::ShowNext() {
    if (unk_0x50 != NULL) {
        unk_0x50->mShowing = false;
        unk_0x50->mMovie.SetPaused(true);
        unk_0x50 = NULL; // ????
    }
    if (mLastSplash != NULL) {
        mLastSplash->Exit();
        unk_0xF8.push_back(mLastSplash);
    }
    CriticalSection* cs = &unk_0xD4;
    if (cs) cs->Enter();
}

void Splash::Show() {
    CriticalSection* cs = &unk_0xD4;
    if (cs) cs->Enter();
    MILO_ASSERT(!mPreparedScreens.empty(), 684);
    RndDir* rd = (*mPreparedScreens.begin()).unk_0x0;
    if (cs) cs->Exit();
    mLastSplash = rd;
    mLastSplash->Enter();
    mLastSplash->Find<RndCam>(kSplashCam, false);
    mLastSplash->Find<TexMovie>(kSplashMovie, false);
}

void Splash::Draw() {
    VISetBlack(FALSE);
    VIFlush();
    if (unk_0x54 != 0) {
        TheTaskMgr.Poll();
        mLastSplash->Poll();
    }
    if (unk_0x50 != NULL) {
        if (MainThread()) {
            float f = unk_0x50->mMovie.MsPerFrame() - 1;
            if (unk_0x100.SplitMs() < f) return;
            unk_0x100.Restart();
        }

        if (!unk_0x50->mMovie.Poll()) {
            mSplashTime = 0;
            return;
        }
    } 

    TheRnd->BeginDrawing();
    if (mLastSplash != NULL) {
        mLastSplash->DrawShowing();
    }
    ThePlatformMgr.mHomeMenuWii->ShowBannedIcon();
    TheRnd->EndDrawing();
    if (MainThread()) return;
    int x = int(unk_0x18.SplitMs()) - mSplashTime;
    if (unk_0x50 != NULL) {
        int z = unk_0x50->mMovie.MsPerFrame() - 10;
        if (z >= x) return;
    } else {

    }

    OSSleepTicks(OSMillisecondsToTicks(x)); // ?????
}

void Splash::CheckHomeMenuButton() {
    if (JoypadPollWiiRemotes() == 0b1111) {
        if (!ThePlatformMgr.mHomeMenuWii->mBanIconActive)
            ThePlatformMgr.mHomeMenuWii->ActivateBanIcon(true);
    }
}
