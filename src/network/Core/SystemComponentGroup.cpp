#include "network/Core/SystemComponentGroup.h"
#include "Core/SystemComponent.h"

namespace Quazal {
    SystemComponentGroup::SystemComponentGroup(const String &str)
        : SystemComponent(str) {}

    SystemComponentGroup::~SystemComponentGroup() {}
}