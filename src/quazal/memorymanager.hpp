#ifndef QUAZAL_MEMORYMANAGER_HPP
#define QUAZAL_MEMORYMANAGER_HPP
#include "rootobject.hpp"
#include "watermark.hpp"
#include "mutexprimitive.hpp"

namespace Quazal {
    class MemoryManager : RootObject {
    public:
        static int s_uiHeaderSize;

        enum _InstructionType {
            _InstType0, _InstType1, _InstType2, _InstType3, _InstType4
        };

        MemoryManager(char*);
        virtual ~MemoryManager();
        virtual void BeginProtection();
        virtual void EndProtection();
        static MemoryManager* GetDefaultMemoryManager();
        static void* Allocate(MemoryManager*, unsigned long, const char*, unsigned int, _InstructionType);
        static void Free(MemoryManager*, void*, _InstructionType);

        int GetHeaderSize();
        
        char* unk4;
        int unk8, unkc, unk10;
        WaterMark* unk14;
        MutexPrimitive* unk18;
    };
}

#endif