#pragma once
#include "Platform/RootObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class StreamTable : public RootObject {
    public:
        StreamTable();
        virtual ~StreamTable();

        qList<int> unk4;
    };
}