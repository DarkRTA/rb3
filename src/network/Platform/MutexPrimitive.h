#ifndef PLATFORM_MUTEXPRIMITIVE_H
#define PLATFORM_MUTEXPRIMITIVE_H
#include "Platform/MemoryManager.h"
#include "Platform/RootObject.h"
#include <revolution/OS.h>

namespace Quazal {
    class MutexPrimitive : public RootObject {
    public:
        MutexPrimitive();
        ~MutexPrimitive();
        void EnterImpl();
        void LeaveImpl();

        static bool s_bNoOp;

        OSMutex* m_hMutex;
    };
}

#endif
