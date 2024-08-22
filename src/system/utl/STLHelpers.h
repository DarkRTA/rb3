#ifndef UTL_STLHELPERS_H
#define UTL_STLHELPERS_H
#include <vector>

template <class T1, class T2>
inline void VectorClear(std::vector<T1, T2>& vec){
    DeleteRange(vec.begin(), vec.end());
    vec.clear();
}

template <class Iter>
inline void DeleteRange(Iter begin, Iter end) {
    for (; begin != end; begin++) {
        delete *begin;
    }
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