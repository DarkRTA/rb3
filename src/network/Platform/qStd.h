#pragma once
#include <vector>
#include <list>
#include "Platform/RootObject.h"
#include "utl/VectorSizeDefs.h"

namespace Quazal {

    template <class T VECTOR_SIZE_DFLT_PARAM>
    class qVector : public std::vector<T VECTOR_SIZE_ARG> {
    public:
    };

    template <class T>
    class qList : public std::list<T>, public RootObject {
    public:
    };

}