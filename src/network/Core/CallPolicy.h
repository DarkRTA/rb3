#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class CallPolicy : public RootObject {
    public:
        CallPolicy() {}
        virtual ~CallPolicy() {}
        virtual void BeginCallImpl() = 0;
        virtual void EndCallImpl() = 0;
    };
}