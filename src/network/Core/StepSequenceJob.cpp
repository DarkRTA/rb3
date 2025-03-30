#include "network/Core/StepSequenceJob.h"
#include "Core/Job.h"
#include "StepSequenceJob.h"

namespace Quazal {
    StepSequenceJob::StepSequenceJob(const DebugString &str)
        : Job(str), unk40(0), unk54(0) {}

    StepSequenceJob::~StepSequenceJob() {}

    void StepSequenceJob::SetStep(const Step &step) {
        Time time;
        time.GetTime();
        unk38 = time;
        unk44 = step;
    }

    void StepSequenceJob::ProcessCallResult(Step *step) {
        SetToReady();
        Time time;
        time.GetTime();
        unk38 = time;
        unk44 = *step;
        if (step)
            delete step;
        ReleaseRef();
    }

    void StepSequenceJob::AddActivity(const char *) {}
    String StepSequenceJob::GetTraceInfo() const { return ""; }

}