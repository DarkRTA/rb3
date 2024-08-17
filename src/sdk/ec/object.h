#ifndef EC_OBJECT_H
#define EC_OBJECT_H

#include <MSL_C++/cstddef>

class ECObj {
    void *operator new(std::size_t);
    void operator delete(void*);
};

#endif
