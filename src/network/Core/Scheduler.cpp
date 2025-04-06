#include "network/Core/Scheduler.h"
#include "Core/PseudoSingleton.h"
#include "Platform/CriticalSection.h"
#include "Scheduler.h"

namespace Quazal {
    CriticalSection Scheduler::s_csGlobalSystemLock(2);

    Scheduler::Scheduler(unsigned char uc, SchedulerWorkerThread *swt)
        : unk4(0), unk8(0), unk10(1), unk38(uc), unk4c(0x10),
          unkac("Scheduler Jobs", true, 60000), unkdc("Scheduler Busy Ratio", true, 2000),
          unk110("JobProcessing", 0), unk158(0), unk160(0),
          unk180("SchedulerDispatch", 0), unk1d8(0), unk1d9(0) {
        unk158 = 0;
        unk160 = 0;
        unka8 = false;
        unk34 = unk10.CreateEventObject(0, 0);
        if (swt)
            m_pWorkerThreads = swt;
        else
            m_pWorkerThreads = new (__FILE__, 0x4D) SchedulerWorkerThread();
        m_pWorkerThreads->m_pScheduler = this;
        unk168 = PseudoSingleton::GetCurrentContext();
    }

    Scheduler::~Scheduler() {
        m_pWorkerThreads->Stop();
        delete m_pWorkerThreads;
    }

}