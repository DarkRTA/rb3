#ifndef EC_VECTOR_H
#define EC_VECTOR_H

#include <MSL_C++/vector>
#include <ec/mem.h>

template <typename T>
class ECVector : public std::vector<T, ECAllocator<T> > {
public:
    ECVector() {}
    ~ECVector() {}
};

#endif
