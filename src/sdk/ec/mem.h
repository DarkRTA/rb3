#ifndef EC_MEM_H
#define EC_MEM_H

#include <MSL_C++/cstddef>
#include <MSL_C++/new>

#include <ec/result.h>
#include <ec/log.h>

typedef void *(*ECAllocFunc)(std::size_t size, std::size_t align);
typedef void (*ECFreeFunc)(void *);

namespace ec {

    struct ECBufHeapMeta {
        unsigned char *current;
        size_t remaining;
    };

    void dumpMemInfo();

    void *mallocAlign(std::size_t size, std::size_t align);
    void *malloc(std::size_t size);
    void free(void *ptr);

    ECResult registerAllocator(ECAllocFunc alloc, ECFreeFunc free);

    ECResult initBufHeap(ECBufHeapMeta &, void *, std::size_t);
    void *bufAlloc(ECBufHeapMeta &, std::size_t, std::size_t, std::size_t);

}

template <typename T>
class ECAllocator {
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef T *pointer;
    typedef const T *const_pointer;
    typedef void *void_pointer;
    typedef const void *const_void_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    template <typename U>
    class rebind {
        typedef ECAllocator<U> other;
    };

    pointer allocate(size_type n, const void *hint = 0) {
        size_type length = n * sizeof(T);
        ec::logmsg(
            ECLogLevel_Finest,
            "allocate %d elements of size %d = %d bytes\n",
            n,
            sizeof(T),
            length
        );

        void *ptr = ec::malloc(length);
        if (!ptr) {
            ec::logmsg(
                ECLogLevel_Error,
                "allocate failed for %d element(s) of size %d = %d bytes\n",
                n,
                sizeof(T),
                length
            );
            throw std::bad_alloc();
        }

        ec::logmsg(ECLogLevel_Finest, "allocated at 0x%x\n", ptr);
        return reinterpret_cast<pointer>(ptr);
    }

    void deallocate(T *p, size_type n) {
        ec::logmsg(
            ECLogLevel_Finest,
            "deallocate %d elements of size %d = %d bytes at 0x%x\n",
            n,
            sizeof(T),
            n * sizeof(T),
            p
        );
        ec::free(p);
    }

    void construct(pointer p, const_reference val) {
        ec::logmsg(ECLogLevel_Finest, "construct with placement\n");
        if (ptr) {
            new (p) T(val);
        }
    }

    void destroy(pointer p) {}
};

#endif
