#include "network/Core/InstanceTable.h"
#include "network/Core/InstantiationContext.h"
#include "network/Core/InstanceControl.h"

namespace Quazal {
    InstanceTable::InstanceTable() : m_pvContextVector(0) {}
    InstanceTable::~InstanceTable() {}

    unsigned int InstanceTable::GetHighestID() const {
        return !m_pvContextVector ? 0 : m_pvContextVector->size() - 1;
    }

    bool
    InstanceTable::AddInstance(InstanceControl *ic, unsigned int ui1, unsigned int ui2) {
        if (ui2 == 0) {
            if (!m_oDefaultContext.AddInstance(ic, ui1))
                return false;
        } else if (!AddInstanceToVector(ic, ui1, ui2)) {
            return false;
        }
        return true;
    }

    bool
    InstanceTable::DelInstance(InstanceControl *ic, unsigned int ui1, unsigned int ui2) {
        if (ui2 == 0) {
            return m_oDefaultContext.DelInstance(ic, ui1);
        } else
            return DelInstanceFromVector(ic, ui1, ui2);
    }
}