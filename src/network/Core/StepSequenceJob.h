#pragma once
#include "Core/Job.h"
#include "Platform/RootObject.h"
#include "Platform/Time.h"

class JobDeleteOrphanedProfiles;
typedef void (JobDeleteOrphanedProfiles::*JobStateFunc)(void);

namespace Quazal {

    class StepSequenceJob : public Job {
    public:
        class Step : public RootObject {
        public:
            Step(JobStateFunc func = 0, const char *cc = 0) : mState(0), mName(0) {}
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

        Time unk38;
        int unk40;
        Step unk44;
        int unk54;
    };

}