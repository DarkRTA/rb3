#ifndef PLATFORM_MEMORYMANAGER_H
#define PLATFORM_MEMORYMANAGER_H
#include "Platform/RootObject.h"
#include "types.h"

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
            _InstType4,
            _InstType5,
            _InstType6,
            _InstType7,
            _InstType8,
            _InstType9
        };

        MemoryManager(char *);
        virtual ~MemoryManager();
        virtual void BeginProtection();
        virtual void EndProtection();
        static MemoryManager *GetDefaultMemoryManager();
        static void *
        Allocate(MemoryManager *, u32 size, const char *file, uint line, _InstructionType);
        static void Free(MemoryManager *, void *, _InstructionType);

        static void *Allocate(unsigned long size, _InstructionType inst) {
            MemoryManager *memMgr = MemoryManager::GetDefaultMemoryManager();
            return Allocate(memMgr, size, "Unknown", 0, inst);
        }

        int GetHeaderSize();

        char *unk4;
        int unk8, unkc, unk10;
        WaterMark *unk14;
        MutexPrimitive *unk18;
    };
}

#define QUAZAL_DEFAULT_ALLOC(size, line, instType)                                       \
    Quazal::MemoryManager::Allocate(                                                     \
        Quazal::MemoryManager::GetDefaultMemoryManager(),                                \
        size,                                                                            \
        __FILE__,                                                                        \
        line,                                                                            \
        Quazal::MemoryManager::instType                                                  \
    );

#define QUAZAL_DEFAULT_FREE(memToFree, instType)                                         \
    Quazal::MemoryManager::Free(                                                         \
        Quazal::MemoryManager::GetDefaultMemoryManager(),                                \
        memToFree,                                                                       \
        Quazal::MemoryManager::instType                                                  \
    );

#endif
