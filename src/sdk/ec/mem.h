#ifndef EC_MEM_H
#define EC_MEM_H

#include <MSL_C++/cstddef>
#include <MSL_C++/new>

#include <ec/result.h>

template <typename T>
class ECAllocator {
public:
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef void *void_pointer;
    typedef const void *const_void_pointer;

    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template <typename U>
    class rebind {
        typedef ECAllocator<U> other;
    };

    T *allocate(std::size_t count, const void *hint = 0);
    void deallocate(T *p, std::size_t n);

    void construct(T *p, const T &copy);
};

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
    void free(void *);

    ECResult registerAllocator(ECAllocFunc alloc, ECFreeFunc free);

    ECResult initBufHeap(ECBufHeapMeta &, void *, std::size_t);
    void *bufAlloc(ECBufHeapMeta &, std::size_t, std::size_t, std::size_t);

}

#endif
