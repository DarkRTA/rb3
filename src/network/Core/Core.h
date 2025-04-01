#pragma once
#include "Platform/RefCountedObject.h"

namespace Quazal {
    class Core : public RefCountedObject {
    public:
        Core();
        virtual ~Core();

        static bool s_bUsesThreads;
    };
}