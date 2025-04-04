#include "Core/CallContext.h"
#include "Platform/Result.h"
#include "Scheduler.h"

namespace Quazal {

    CallContext::CallContext() : unkc((_State)0) {
        unk20 = qResult(0x80010001);
        unk8 = 0;
        unk40 = 0;
    }

    CallContext::~CallContext() { Scheduler::GetInstance(); }

}