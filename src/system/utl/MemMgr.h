#ifndef UTL_MEMMGR_H
#define UTL_MEMMGR_H
#include "utl/PoolAlloc.h"

void* operator new(unsigned long);
void operator delete(void*);
void* operator new[](unsigned long);
void operator delete[](void*);

void* _MemOrPoolAlloc(int, PoolType);
void _MemOrPoolFree(int, PoolType, void*);
void* _MemOrPoolAllocSTL(int, PoolType);
void _MemOrPoolFreeSTL(int, PoolType, void*);

#endif

// i took these from the old src's <new>
// #include <cstddef>
// #include <exception>

// // Not sure where these should go, leaving here for now
// enum PoolType {
//     MainPool,
//     FastPool
// };

// extern void *_MemAlloc(int size, int);
// extern void MemFree(void *ptr);

// extern void *_PoolAlloc(int size, int, PoolType pool);
// extern void _PoolFree(int size, PoolType pool, void *ptr);

// extern void *MemOrPoolAlloc(int size, PoolType pool);
// extern void MemOrPoolFree(int size, PoolType pool, void *ptr);

// extern void *_MemOrPoolAllocSTL(int size, PoolType pool);
// extern void _MemOrPoolFreeSTL(int size, PoolType pool, void *ptr);

// namespace std {
//     class bad_alloc : public exception {
//     public:
//         virtual ~bad_alloc() {
//         }
//         virtual const char *what() const {
//             return "bad_alloc";
//         }
//     };

//     struct nothrow_t {
//         explicit nothrow_t() {
//         }
//     };
//     extern const nothrow_t nothrow;

//     typedef void (*new_handler)();
//     new_handler set_new_handler(new_handler new_p) throw();
// }

// void *operator new(std::size_t size);
// void *operator new[](std::size_t size);
// void operator delete(void *ptr) throw();
// void operator delete[](void *ptr) throw();

// // Placement new/delete
// inline void *operator new(std::size_t size, void *place) throw() {
//     return place;
// }

// inline void *operator new[](std::size_t size, void *place) throw() {
//     return place;
// }

// inline void operator delete(void *ptr, void *place) throw() {
// }

// inline void operator delete[](void *ptr, void *place) throw() {
// }
