#ifndef EC_MEM_H
#define EC_MEM_H

template <typename T>
class ECAllocator {
public:
    T* allocate(size_t count, const void *hint = 0);
    void deallocate(T* p, size_t n);
};

#endif
