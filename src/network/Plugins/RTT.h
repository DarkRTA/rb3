#pragma once

#include "Platform/RootObject.h"
#include "types.h"

namespace Quazal {
    class RTT : RootObject {
        RTT(uint);
        ~RTT();
        void Adjust(uint);

        uint unk_0x0;
        uint unk_0x4;
        uint unk_0x8;
    };
}