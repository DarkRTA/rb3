#include "decomp.h"
#include "network/Core/StepSequenceJob.h"

namespace Quazal {
    DECOMP_FORCEFUNC(PollForCompletionJob, StepSequenceJob, CheckExceptions())
    DECOMP_FORCEBLOCK(PollForCompletionJob,(void), Job* ssj; dynamic_cast<StepSequenceJob*>(ssj););
}