#pragma once
#include "Core/Job.h"

namespace Quazal {
    class PeriodicJob : public Job {
    public:
        PeriodicJob(const DebugString &);
        virtual ~PeriodicJob() {}
        virtual void SetDefaultPostExecutionState();
        virtual bool SkipWaitDelayAtTermination();

        int m_tiPeriod; // 0x34
    };
}
