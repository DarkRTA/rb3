#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class EndPoint : public RootObject {
    public:
        void Close();
        void Open();
    };
}