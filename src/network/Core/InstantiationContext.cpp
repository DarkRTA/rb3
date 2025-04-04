#include "network/Core/InstantiationContext.h"
#include "InstanceControl.h"
#include "Platform/SystemError.h"
#include <cstddef>

namespace Quazal {
    InstantiationContext::InstantiationContext() : m_IsValid(false) {
        InitContext();
        m_IsValid = true;
    }

    InstantiationContext::~InstantiationContext() { InitContext(); }

    bool InstantiationContext::AddInstance(InstanceControl *ic, unsigned int idx) {
        if (idx >= 11) {
            SystemError::SignalError(0, 0, 0xe0000003, 0);
            return false;
        } else if (m_icInstanceContext[idx]) {
            SystemError::SignalError(0, 0, 0xe000000f, 0);
            return false;
        } else {
            m_icInstanceContext[idx] = ic;
            return true;
        }
    }

    bool InstantiationContext::DelInstance(InstanceControl *ic, unsigned int idx) {
        if (idx >= 11) {
            SystemError::SignalError(0, 0, 0xe0000003, 0);
            return false;
        } else {
            m_icInstanceContext[idx] = nullptr;
            return true;
        }
    }

    unsigned int InstantiationContext::GetInstance(unsigned int idx) {
        if (idx >= 11) {
            SystemError::SignalError(0, 0, 0xe0000003, 0);
            return -1;
        } else {
            return (unsigned int)m_icInstanceContext[idx];
        }
    }
}