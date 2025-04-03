#pragma once
#include "Platform/RootObject.h"
#include "Services/GatheringDDL.h"

namespace Quazal {
    class Gathering : public _DDL_Gathering {
    public:
        Gathering();
        virtual ~Gathering();
        virtual void Trace(unsigned int) const;
    };
}