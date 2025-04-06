#pragma once
#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {
    class DataSet : public RootObject {
    public:
        DataSet();
        ~DataSet();
        bool Refresh(const Time &);
    };
}