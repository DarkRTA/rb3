#include "network/Core/SingleThreadCallPolicy.h"
#include "Platform/ObjectThread.h"

namespace Quazal {
    SingleThreadCallPolicy::SingleThreadCallPolicy()
        : m_uiCurrentRecursionLevel(0), m_uiCurrentThread(0),
          m_uiMaximumRecursionLevel(1), m_uiValidThread(0) {}

    void SingleThreadCallPolicy::SetMaximumRecursionLevel(unsigned int level) {
        m_uiMaximumRecursionLevel = level;
    }

    void SingleThreadCallPolicy::BeginCallImpl() {
        if (m_uiCurrentRecursionLevel == 0) {
            m_uiCurrentThread = ObjectThreadRoot::GetCurrentThreadID();
        }
        m_uiCurrentRecursionLevel++;
    }

    void SingleThreadCallPolicy::EndCallImpl() {
        if (m_uiCurrentRecursionLevel == 1) {
            m_uiCurrentThread = 0;
        }
        m_uiCurrentRecursionLevel--;
    }

    bool SingleThreadCallPolicy::CurrentThreadIsDispatchingJobs() const {
        return ObjectThreadRoot::GetCurrentThreadID() == m_uiCurrentThread;
    }

}