#pragma once
#include "Platform/CriticalSection.h"
#include "network/Platform/qMemAllocator.h"
#include "Platform/RootObject.h"
#include "utl/VectorSizeDefs.h"
#include <vector>
#include <list>
#include <map>

namespace Quazal {

    template <class T VECTOR_SIZE_DFLT_PARAM>
    class qVector : public std::vector<T VECTOR_SIZE_ARG, MemAllocator<T> > {
    public:
    };

    template <class T>
    class qList : public std::list<T, MemAllocator<T> >, public RootObject {
    public:
    };

    template <class T1, class T2>
    class qMap
        : public std::map<T1, T2, std::less<T1>, MemAllocator<std::pair<const T1, T2> > >,
          public RootObject {
    public:
    };

    template <class T>
    class qProtectedList : public RootObject {
    public:
        qProtectedList() : mCSList(0) {}
        CriticalSection mCSList;
        qList<T> mOList;
    };

}