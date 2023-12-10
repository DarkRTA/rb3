#ifndef QUAZAL_MEMORYMANAGER_HPP
#define QUAZAL_MEMORYMANAGER_HPP
#include "rootobject.hpp"
#include "watermark.hpp"
#include "mutexprimitive.hpp"

namespace Quazal {
    class MemoryManager : RootObject {
    public:
        static int s_uiHeaderSize;

        MemoryManager(char*);
        virtual ~MemoryManager();
        virtual void BeginProtection();
        virtual void EndProtection();

        int GetHeaderSize();
        
        char* unk4;
        int unk8, unkc, unk10;
        WaterMark* unk14;
        MutexPrimitive* unk18;
    };
}

#endif