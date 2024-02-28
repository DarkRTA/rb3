#ifndef PLATFORM_MEMORYMANAGER_H
#define PLATFORM_MEMORYMANAGER_H
#include "Platform/RootObject.h"

namespace Quazal {

    // forward declarations
    class WaterMark;
    class MutexPrimitive; 

    class MemoryManager : public RootObject {
    public:
        static int s_uiHeaderSize;

        enum _InstructionType {
            _InstType0,
            _InstType1,
            _InstType2,
            _InstType3,
            _InstType4
        };

        MemoryManager(char *);
        virtual ~MemoryManager();
        virtual void BeginProtection();
        virtual void EndProtection();
        static MemoryManager *GetDefaultMemoryManager();
        static void *Allocate(
            MemoryManager *, unsigned long, const char *, unsigned int, _InstructionType
        );
        static void Free(MemoryManager *, void *, _InstructionType);

        int GetHeaderSize();

        char *unk4;
        int unk8, unkc, unk10;
        WaterMark *unk14;
        MutexPrimitive *unk18;
    };
}

#endif
