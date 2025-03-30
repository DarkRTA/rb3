#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class _DDL_BasicAccountInfo : public RootObject {
    public:
        _DDL_BasicAccountInfo() {}
        virtual ~_DDL_BasicAccountInfo() {}
    };

    class BasicAccountInfo : public _DDL_BasicAccountInfo {
    public:
        BasicAccountInfo() {}
        virtual ~BasicAccountInfo() {}
    };
}