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
        static void *Allocate(
            MemoryManager *, unsigned long, const char *, unsigned int, _InstructionType
        );
        static void Free(MemoryManager *, void *, _InstructionType);

        static void *Allocate(unsigned long size, _InstructionType inst) {
            MemoryManager* memMgr = MemoryManager::GetDefaultMemoryManager();
            return Allocate(memMgr, size, "Unknown", 0, inst);
        }

        int GetHeaderSize();

        char *unk4;
        int unk8, unkc, unk10;
        WaterMark *unk14;
        MutexPrimitive *unk18;
    };
}

#define QUAZAL_DEFAULT_ALLOC(ul, ui, instType) \
    MemoryManager::Allocate(MemoryManager::GetDefaultMemoryManager(), ul, __FILE__, ui, MemoryManager::instType);

#define QUAZAL_DEFAULT_FREE(memToFree, instType) \
    MemoryManager::Free(MemoryManager::GetDefaultMemoryManager(), memToFree, MemoryManager::instType);

#endif
