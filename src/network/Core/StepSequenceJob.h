#pragma once
#include "Core/CallContext.h"
#include "Core/Job.h"
#include "Core/SystemComponent.h"
#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {

    class StepSequenceJob : public Job {
    public:
        typedef void (StepSequenceJob::*JobStateFunc)(void);

        class Step : public RootObject {
        public:
            Step() : mState(0), mName(0) {}
            Step(JobStateFunc func, const char *cc) : mState(func), mName(cc) {}
            ~Step() {}

            JobStateFunc mState; // 0x0
            const char *mName; // 0xc
        };
        StepSequenceJob(const DebugString &);
        virtual ~StepSequenceJob();
        virtual void Execute();
        virtual void AddActivity(const char *);
        virtual String GetTraceInfo() const;
        virtual void CheckExceptions();

        void SetStep(const Step &);
        void ProcessCallResult(Step *);
        void ResumeOnCallCompletion(CallContext *, Step *);
        void TerminateComponent(SystemComponent *, const Step &);

        Time unk38;
        int unk40;
        Step unk44;
        int unk54;
    };

}