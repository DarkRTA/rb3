#pragma once
#include "Platform/String.h"
#include "ObjDup/DataSet.h"
#include "Platform/RootObject.h"

namespace Quazal {
    class _DS_ChannelInfo : public RootObject {
    public:
        _DS_ChannelInfo() {}
        ~_DS_ChannelInfo() {}

        DataSet unk0;
        String unk4;
        unsigned short unk8;
    };
}