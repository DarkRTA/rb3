#pragma once
#include "Core/Job.h"
#include "Platform/Time.h"

namespace Quazal {

    class StepSequenceJob : public Job {
    public:
        class Step {
        public:
            // one word and one ptr to member func
        };
        StepSequenceJob(const DebugString &);
        virtual ~StepSequenceJob();
        virtual void Execute();
        virtual void AddActivity(const char *);
        virtual String GetTraceInfo() const;
        virtual void CheckExceptions();

        Time unk38;
        int unk40;
        // ptr to member function unk44
        int unk54;
    };

}