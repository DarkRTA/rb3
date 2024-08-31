#include "RTT.h"

namespace Quazal {
    RTT::RTT(uint i) : unk_0x0(i * 8), unk_0x4(0), unk_0x8(i) {}

    RTT::~RTT() {}

    void RTT::Adjust(uint i) {
        int r8 = i - unk_0x0/8;
        unk_0x8 = i;
        unk_0x0 += r8;
    }
}