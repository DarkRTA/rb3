#pragma once
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <list>
#include "utl/VectorSizeDefs.h" /* IWYU pragma: export */

// C++11 feature replacement macros
#if defined(__MWERKS__) && !defined(DECOMP_IDE_FLAG)                                     \
    && (!defined(__cplusplus) || __cplusplus < 201103L)
#define AUTO(name, val) __decltype__(val) name = val
#else
// hack to prevent errors in clangd
// clang-format off: really dropped the ball on this one lol
#define AUTO(name, val)                                                                  \
    _Pragma("clang diagnostic push")                                                     \
    _Pragma("clang diagnostic ignored \"-Wc++11-extensions\"")                           \
    auto name = val                                                                      \
    _Pragma("clang diagnostic pop")
// clang-format on
#endif

#define FOREACH_(it, container, inc)                                                     \
    for (AUTO(it, container.begin()); it != container.end(); inc)
#define FOREACH_PTR_(it, container, inc)                                                 \
    for (AUTO(it, container->begin()); it != container->end(); inc)

#define FOREACH(it, container) FOREACH_(it, container, ++it)
#define FOREACH_POST(it, container) FOREACH_(it, container, it++)
#define FOREACH_PTR(it, container) FOREACH_PTR_(it, container, ++it)
#define FOREACH_PTR_POST(it, container) FOREACH_PTR_(it, container, it++)

struct Delete {
    // not sure if this template is real, but it's required for
    // C++ standards compliance (can't delete a void*),
    // and `Delete` itself has no template based on Dance Central symbols
    template <typename T>
    void operator()(T *ptr) {
        delete ptr;
    }
};

template <typename Container>
inline void DeleteAll(Container &container) {
    std::for_each(container.begin(), container.end(), Delete());
    container.clear();
}

template <class T VECTOR_SIZE_PARAM, class T2>
void VectorRemove(std::vector<T VECTOR_SIZE_ARG> &vec, const T2 &obj) {
    for (typename std::vector<T VECTOR_SIZE_ARG>::iterator it = vec.begin();
         it != vec.end();
         ++it) {
        if (*it == obj) {
            vec.erase(it);
            return;
        }
    }
}

template <typename T VECTOR_SIZE_PARAM>
inline void TrimExcess(std::vector<T VECTOR_SIZE_ARG> &vec) {
    std::vector<T VECTOR_SIZE_ARG> copy(vec);
    vec.swap(copy);
}

template <typename T VECTOR_SIZE_PARAM>
inline void ClearAndShrink(std::vector<T VECTOR_SIZE_ARG> &vec) {
    std::vector<T VECTOR_SIZE_ARG> temp;
    temp.swap(vec);
}

template <class T>
void RemoveSwap(std::vector<T *> &vec, T *obj) {
    if (vec.size() == 0) {
        return;
    }

    if (vec.back() == obj) {
        vec.pop_back();
        return;
    }

    typename std::vector<T *>::iterator it = std::find(vec.begin(), vec.end(), obj);
    if (it != vec.end()) {
        *it = vec.back();
        vec.pop_back();
    }
}

template <class T VECTOR_SIZE_PARAM>
inline bool VectorFind(const std::vector<T VECTOR_SIZE_ARG> &vec, const T &key) {
    return std::find(vec.begin(), vec.end(), key) != vec.end();
}

template <class T>
inline bool ListFind(const std::list<T> &list, const T &key) {
    return std::find(list.begin(), list.end(), key) != list.end();
}

// T must be an std iterator type
// std::next before std::next was a thing
template <class T>
inline T NextItr(T it, int idx) {
    while (idx-- != 0)
        ++it;
    return it;
}

// not sure where else to put this
inline int atoi_s(char *str) {
    if (str)
        return atoi(str);
    else
        return 0;
}
