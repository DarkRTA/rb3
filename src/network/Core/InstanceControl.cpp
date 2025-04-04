#include "network/Core/InstanceControl.h"
#include "InstanceTable.h"
#include "network/Core/Scheduler.h"
#include "Platform/ScopedCS.h"

namespace Quazal {

    InstanceTable InstanceControl::s_oInstanceTable;

    InstanceControl::InstanceControl(unsigned int ui1, unsigned int ui2) {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        m_bIsValid = false;
        if (!s_oInstanceTable.AddInstance(this, ui1, ui2)) {
            return;
        } else {
            m_icInstanceContext = ui2;
            m_icInstanceType = ui1;
            m_pDelegatorInstance = nullptr;
            m_bIsValid = true;
        }
    }

    InstanceControl::~InstanceControl() {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        if (m_bIsValid) {
            s_oInstanceTable.DelInstance(this, m_icInstanceType, m_icInstanceContext);
        }
    }

    void InstanceControl::SetDelegatorInstance(void *v) {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        m_pDelegatorInstance = v;
    }

    unsigned int InstanceControl::GetHighestID() {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        return s_oInstanceTable.GetHighestID();
    }

    bool InstanceControl::ContextIsValid(unsigned int ui) {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        return s_oInstanceTable.ContextIsValid(ui);
    }

}