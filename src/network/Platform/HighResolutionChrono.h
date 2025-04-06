#pragma once
#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {
    class HighResolutionChrono : public RootObject {
    public:
        HighResolutionChrono();
        ~HighResolutionChrono();

        unsigned long long unk0;
        Time unk8;
    };
}