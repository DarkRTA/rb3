#include "network/Core/PeriodicJob.h"
#include "Platform/String.h"

namespace Quazal {
    PeriodicJob::PeriodicJob(const DebugString &str) : Job(str), m_tiPeriod(0) {
        SetToWaiting(unk20);
    }

    void PeriodicJob::SetDefaultPostExecutionState() {
        if (m_tiPeriod > 0) {
            SetToWaiting(m_tiPeriod);
        } else
            SetToComplete();
    }

    bool PeriodicJob::SkipWaitDelayAtTermination() { return m_tiPeriod == 0; }
}