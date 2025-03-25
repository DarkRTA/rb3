#include "Protocol/Protocol.h"
#include "Core/SystemComponent.h"
#include "Protocol.h"

namespace Quazal {

    Protocol::Protocol(unsigned int ui)
        : SystemComponent(String("<unknown>")), unk18(0), unk24(ui) {
        unk20 = 0;
        unk28 = 0;
        unk1c = 0;
        unk2c = 0;
        unk30 = 0;
        unk34 = 0;
    }

    Protocol::~Protocol() {}

}