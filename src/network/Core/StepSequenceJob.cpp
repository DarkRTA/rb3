#include "network/Core/StepSequenceJob.h"
#include "Core/Job.h"

namespace Quazal {
    StepSequenceJob::StepSequenceJob(const DebugString &str) : Job(str), unk40(0) {}

    StepSequenceJob::~StepSequenceJob() {}
}