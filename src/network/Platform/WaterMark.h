#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class WaterMark : public RootObject {
    public:
        WaterMark(const char *, bool, unsigned int);
        ~WaterMark();
    };
}