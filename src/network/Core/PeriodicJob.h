#pragma once

#include "Core/Job.h"

namespace Quazal {
class PeriodicJob : public Job {
    PeriodicJob(const DebugString&);
    virtual ~PeriodicJob() {}
};
}
