#include "network/Core/InstanceControl.h"
#include "InstanceTable.h"
#include "network/Core/Scheduler.h"
#include "Platform/ScopedCS.h"

namespace Quazal {

    InstanceControl::InstanceControl(unsigned int ui1, unsigned int ui2) {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        unk10 = 0;
        if (!InstanceTable::s_oInstanceTable->AddInstance(this, ui1, ui2)) {
            return;
        } else {
            unk4 = ui2;
            unk8 = ui1;
            unkc = 0;
            unk10 = 1;
        }
    }

    InstanceControl::~InstanceControl() {}

}