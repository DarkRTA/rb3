#ifndef PLATFORM_MEMORYMANAGER_H
#define PLATFORM_MEMORYMANAGER_H
#include "Platform/RootObject.h"
#include "types.h"
#include <stdlib.h>

typedef void *AllocFunc(unsigned long);
typedef void FreeFunc(void *);

namespace Quazal {

    // forward declarations
    class WaterMark;
    class MutexPrimitive;

    class MemoryManager : public RootObject {
    public:
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
            _InstType9,
            _InstType10
        };

        MemoryManager(char *name);
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

        static void *GenericMalloc(unsigned long size) {
            if (s_fcnMalloc)
                return s_fcnMalloc(size);
            else
                return malloc(size);
        }
        static void GenericFree(void *mem) {
            if (s_fcnFree)
                s_fcnFree(mem);
            else
                free(mem);
        }
        static unsigned int GetHeaderSize() {
            if (s_uiHeaderSize == 0)
                s_uiHeaderSize = 4;
            return s_uiHeaderSize;
        }

        static AllocFunc *s_fcnMalloc;
        static FreeFunc *s_fcnFree;
        static bool s_bIsMemoryFunctionSet;
        static unsigned int s_uiHeaderSize;
        static unsigned int s_eShutDownState;
        static MemoryManager *s_poDefaultMemoryManager;

        char *m_szName; // 0x4
        int unk8, unkc, unk10;
        WaterMark *m_pMemoryWaterMark; // 0x14
        MutexPrimitive *m_pMutex; // 0x18
    };
}

void *QuazalUserThread(void *);
void *QuazalMemAlloc(unsigned long);
void QuazalMemFree(void *);

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
