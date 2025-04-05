#include "network/Core/SystemComponents.h"
#include "Core/SystemComponentGroup.h"

namespace Quazal {
    SystemComponents::SystemComponents()
        : SystemComponentGroup("System Components"), unk20(0), unk24(0), unk28(0),
          unk2c(new(__FILE__, 0x18) SystemComponentGroup("Core")) {
        RegisterComponent(unk2c);
    }

    SystemComponents::~SystemComponents() {}
}