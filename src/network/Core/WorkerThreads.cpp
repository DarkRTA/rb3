#include "network/Core/WorkerThreads.h"
#include "Platform/ObjectThread.h"
#include "Platform/ScopedCS.h"
#include "Platform/String.h"

namespace Quazal {
    WorkerThreads::WorkerThreads() : m_csState(0x40000000) { m_eState = 2; }
    WorkerThreads::~WorkerThreads() { Stop(); }

    bool WorkerThreads::Start(unsigned int ui) {
        ScopedCS cs(m_csState);
        if (m_eState != 2)
            return false;
        else {
            m_eState = 0;
            for (int i = 0; i < ui; i++) {
                String str;
                str.Format("WorkerThread ID %d", i + 1);
                ObjectThread<WorkerThreads, int> *thread =
                    new (__FILE__, 0x29) ObjectThread<WorkerThreads, int>(str);
                thread->Update(this, &WorkerThreads::Run, 0, 1);

                m_vecThreads.push_back(thread);
            }
            return true;
        }
    }

    bool WorkerThreads::Stop() {
        ScopedCS cs(m_csState);
        if (m_eState != 0)
            return false;
        else {
            m_eState = 1;
            for (int i = 0; i < m_vecThreads.size(); i++) {
                m_vecThreads[i]->Wait(-1);
                delete m_vecThreads[i];
            }
            return true;
        }
    }

    unsigned int WorkerThreads::GetNbWorkers() const { return m_vecThreads.size(); }

    void WorkerThreads::Run(int i1) {
        Initialize();
        while (m_eState == 0) {
            Work();
        }
        Teardown();
    }
}