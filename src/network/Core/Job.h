#pragma once
#include "Platform/RefCountedObject.h"
#include "Platform/String.h"
#include "Platform/Time.h"

namespace Quazal {
    // forward decl cause i can't find the bastard
    class UserContext;
    class Job;

    typedef void CompletionCallbackFunc(Job *, UserContext *);

    class Job : public RefCountedObject {
    public:
        enum State {
            Initial = 0,
            Waiting = 1,
            Suspended = 2,
            Ready = 3,
            Running = 4,
            Complete = 5
        };
        Job(const DebugString &);
        virtual ~Job();
        virtual void DecoratedExecute();
        virtual void Execute() = 0;
        virtual void TestSuspendedJobState();
        virtual void AddActivity(const char *);
        virtual String GetTraceInfo() const;
        virtual void SetDefaultPostExecutionState();
        virtual bool SkipWaitDelayAtTermination() { return false; }

        void PerformExecution(const Time &);
        void ValidateTransition(State, State);
        void Resume();
        void SetToWaiting(int);
        void SetToSuspended();
        void SetToReady();
        void SetToRunning();
        void SetToComplete();
        void SetToCancel();
        void SetToInitial();

        int unk8;
        int unkc;
        CompletionCallbackFunc *unk10; // funcptr
        UserContext *unk14;
        int unk18;
        State unk1c; // 0x1c
        int unk20;
        int unk24;
        Time unk28;
        bool unk30;
        bool unk31;
    };
}
