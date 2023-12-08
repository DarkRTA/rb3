#ifndef QUAZAL_MEMORYMANAGER_HPP
#define QUAZAL_MEMORYMANAGER_HPP
#include "rootobject.hpp"

namespace Quazal {
    class MemoryManager : RootObject {
    public:
        MemoryManager(char*);
        virtual ~MemoryManager();
        virtual void BeginProtection();
        virtual void EndProtection();

        int GetHeaderSize();
        
        char* unk4;
        int unk8, unkc, unk10, unk14, unk18;
    };
}

#endif