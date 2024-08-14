#include <ec/mem.h>
#include <ec/log.h>
#include <ec/object.h>
#include <ec/internal/shr.h>

#include "macros.h"

namespace ec {

    ECAllocFunc ecAlloc;
    ECFreeFunc ecFree;
    _SHRMutex __memMutex;

    void dumpMemInfo() {}

    void *mallocAlign(std::size_t size, std::size_t align) {
        _SHR_mutex_lock(&__memMutex);
        void *ptr = ecAlloc(ROUND_UP(size, 32), align);
        _SHR_mutex_unlock(&__memMutex);
        return ptr;
    }

    // ??? it wants to inline malloc in ECObj::operator new
    // despite not being marked inline and the flags using -inline noauto
    DONT_INLINE void *malloc(std::size_t size) {
        _SHR_mutex_lock(&__memMutex);
        void *ptr = ecAlloc(ROUND_UP(size, 32), 32);
        _SHR_mutex_unlock(&__memMutex);
        return ptr;
    }

    void free(void *ptr) {
        try {
            if (ptr) {
                _SHR_mutex_lock(&__memMutex);
                ecFree(ptr);
                _SHR_mutex_unlock(&__memMutex);
            }
        } catch (std::bad_alloc &ex) {
            logmsg(
                ECLogLevel_Error,
                "Caught bad_alloc exception at  FILE: ec_mem.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:22 \n",
                0x56
            );
        } catch (...) {
            logmsg(
                ECLogLevel_Error,
                "Caught exception at  FILE: ec_mem.cpp  LINE: %d  COMPILED: Feb  8 2010  20:10:22 \n",
                0x56
            );
        }
    }

    ECResult registerAllocator(ECAllocFunc alloc, ECFreeFunc free) {
        _SHR_mutex_init(&__memMutex, 1, 0, 0);
        ecAlloc = alloc;
        ecFree = free;
        return ECResult_Success;
    }

}

void *ECObj::operator new(std::size_t size) {
    void *ptr = ec::malloc(size);
    if (!ptr) {
        ec::logmsg(ECLogLevel_Error, "new failed for size %u\n", size);
        throw std::bad_alloc();
    }

    ec::logmsg(ECLogLevel_Finest, "new %u bytes at %p\n", size, ptr);
    return ptr;
}

void ECObj::operator delete(void *ptr) {
    ec::logmsg(ECLogLevel_Finest, "delete %p\n", ptr);
    ec::free(ptr);
}

namespace ec {

    ECResult initBufHeap(ECBufHeapMeta &meta, void *heap, std::size_t heapSize) {
        if (heapSize != 0 && !heap) {
            return ECResult_InvalidBufHeap;
        }

        meta.current = (unsigned char *)ROUND_UP_PTR(heap, 4);

        unsigned char *end = (unsigned char *)heap + heapSize;
        if (end < meta.current) {
            meta.remaining = 0;
        } else {
            meta.remaining = (size_t)(end - meta.current) / 4;
        }

        return ECResult_Success;
    }

    void *bufAlloc(ECBufHeapMeta &meta, std::size_t a, std::size_t b, std::size_t c) {
        unsigned char *ptr = meta.current;
        if (!ptr || meta.remaining == 0) {
            return nullptr;
        }

        ptr = (unsigned char *)ROUND_UP_PTR(ptr, b);
        size_t allocated = ptr - meta.current;

        allocated = ((int)allocated / 4) + (allocated < 0 && (allocated & 3) != 0) + (size_t)ROUND_UP_PTR(a, c) / 4;
        if (allocated > meta.remaining) {
            return nullptr;
        }

        meta.current += allocated * 4;
        meta.remaining -= allocated;

        return ptr;
    }

}
