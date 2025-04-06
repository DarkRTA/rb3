#include "network/Core/StepSequenceJob.h"
#include "Core/SystemComponent.h"
#include "network/Platform/Callback.h"
#include "Core/CallContext.h"
#include "Core/Job.h"
#include "StepSequenceJob.h"

namespace Quazal {
    StepSequenceJob::StepSequenceJob(const DebugString &str) : Job(str) {
        unk40 = 0;
        unk54 = 0;
    }

    StepSequenceJob::~StepSequenceJob() {}

    void StepSequenceJob::Execute() {}

    void StepSequenceJob::ResumeOnCallCompletion(CallContext *ctx, Step *step) {
        AcquireRef();
        ctx->RegisterCompletionCallback(
            new (__FILE__, 0x38) Callback<StepSequenceJob, Step *>(
                this, &StepSequenceJob::ProcessCallResult, step
            ),
            false,
            true
        );
    }

    void StepSequenceJob::SetStep(const Step &step) {
        unk38 = Time::GetTime();
        unk44 = step;
    }

    void StepSequenceJob::ProcessCallResult(Step *step) {
        SetToReady();
        unk38 = Time::GetTime();
        unk44 = *step;
        delete step;
        ReleaseRef();
    }

    void StepSequenceJob::AddActivity(const char *) {}
    String StepSequenceJob::GetTraceInfo() const { return ""; }

    void
    StepSequenceJob::TerminateComponent(SystemComponent *component, const Step &step) {
        component->Terminate();
        if (component->mState != SystemComponent::Terminated) {
            SetToWaiting(0x32);
        } else {
            unk38 = Time::GetTime();
            unk44 = step;
        }
    }

}