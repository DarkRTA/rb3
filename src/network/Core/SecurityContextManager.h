#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class SecurityContextManager : public RootObject {
    public:
        SecurityContextManager();
        ~SecurityContextManager();
    };
}