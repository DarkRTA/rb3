#pragma once
#include "Platform/RefCountedObject.h"
#include "Platform/String.h"
#include "Platform/Time.h"
#include "Platform/UserContext.h"

namespace Quazal {
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
        virtual void DecoratedExecute() { Execute(); }
        virtual void Execute() = 0;
        virtual void TestSuspendedJobState() {}
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
        CompletionCallbackFunc *m_pfCompletionCallback; // 0x10
        UserContext m_oContext; // 0x14
        DebugString m_strJobDescription; // 0x18
        State m_eState; // 0x1c
        int unk20; // 0x20
        int unk24; // 0x24
        Time m_tDeadline; // 0x28
        bool unk30; // 0x30
        bool unk31; // 0x31
    };
}
