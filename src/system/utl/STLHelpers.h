#ifndef UTL_STLHELPERS_H
#define UTL_STLHELPERS_H
#include <algorithm>
#include <vector>
#include "utl/VectorSizeDefs.h" /* IWYU pragma: export */

struct Delete {
    // not sure if this template is real, but it's required for
    // C++ standards compliance (can't delete a void*),
    // and `Delete` itself has no template based on Dance Central symbols
    template <typename T>
    void operator()(T* ptr) {
        delete ptr;
    }
};

template <typename Container>
inline void DeleteAll(Container &container) {
    std::for_each(container.begin(), container.end(), Delete());
    container.clear();
}

template <class T VECTOR_SIZE_PARAM, class T2>
void VectorRemove(std::vector<T VECTOR_SIZE_ARG>& vec, const T2& obj){
    for(typename std::vector<T VECTOR_SIZE_ARG>::iterator it = vec.begin(); it != vec.end(); ++it){
        if(*it == obj){
            vec.erase(it);
            return;
        }
    }
}

template <typename T>
inline void ClearAndShrink(std::vector<T>& vec) {
    std::vector<T> temp;
    temp.swap(vec);
}

// TODO: implement for RndTransformable.cpp
template <class T> void RemoveSwap(std::vector<T*>&, T*);

#endif
