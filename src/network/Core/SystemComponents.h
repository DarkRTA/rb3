#pragma once
#include "Core/SystemComponentGroup.h"

namespace Quazal {
    class SystemComponents : public SystemComponentGroup {
    public:
        SystemComponents();
        virtual ~SystemComponents();

        int unk20;
        int unk24;
        int unk28;
        SystemComponentGroup *unk2c;
    };
}