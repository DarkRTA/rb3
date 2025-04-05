#include "network/Core/PeriodicJob.h"
#include "Platform/String.h"

namespace Quazal {
    PeriodicJob::PeriodicJob(const DebugString &str) : Job(str), unk34(0) {
        SetToWaiting(unk20);
    }

    void PeriodicJob::SetDefaultPostExecutionState() {
        if (unk34 > 0) {
            SetToWaiting(unk34);
        } else
            SetToComplete();
    }

    bool PeriodicJob::SkipWaitDelayAtTermination() { return unk34 == 0; }
}