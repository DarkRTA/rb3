#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class DOHandle : public RootObject {
    public:
        DOHandle(unsigned int val = 0) : mValue(val) {}
        ~DOHandle() {}

        void SetDOClassID(unsigned int);

        unsigned int mValue; // 0x0
    };
}