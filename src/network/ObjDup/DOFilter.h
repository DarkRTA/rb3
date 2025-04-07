#pragma once
#include "DOHandle.h"
#include "Platform/RefCountedObject.h"

namespace Quazal {
    class DOFilter : public RefCountedObject {
        DOFilter();
        virtual ~DOFilter();
        virtual DOHandle GetMinimumValidHandle(); // these both return a struct
        virtual DOHandle GetMaximumValidHandle();
    };
}
