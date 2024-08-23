#ifndef UTL_STLHELPERS_H
#define UTL_STLHELPERS_H
#include <vector>

template <class T>
inline void DeleteInstance(const int& /* purpose not known yet */, T* t) {
    delete t;
}

template <class Iter>
inline void DeleteRange(Iter begin, Iter end, const int& asdf = int() /* purpose not known yet */) {
    for (; begin != end; begin++) {
        DeleteInstance(asdf, *begin);
    }
}

template <typename Container>
inline void DeleteAll(Container &container) {
    DeleteRange(container.begin(), container.end());
    container.clear();
}

template <class T1, class T2, class T3>
void VectorRemove(std::vector<T1,T2>& vec, const T3& obj){
    for(std::vector<T1,T2>::iterator it = vec.begin(); it != vec.end(); ++it){
        if(*it == obj){
            vec.erase(it);
            return;
        }
    }
}

// TODO: implement for RndTransformable.cpp
template <class T> void RemoveSwap(std::vector<T*>&, T*);

#endif
