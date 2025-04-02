#pragma once
#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {
    class StreamBundling : public RootObject {
    public:
        StreamBundling();
        virtual ~StreamBundling();

        bool unk4;
        int unk8;
        Time unk10;
    };
}