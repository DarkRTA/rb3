#pragma once
#include "Core.h"
#include "Core/Job.h"
#include "Platform/CriticalSection.h"
#include "Platform/EventHandler.h"
#include "Platform/HighResolutionChrono.h"
#include "Platform/ProfilingUnit.h"
#include "Platform/RootObject.h"
#include "Platform/WaterMark.h"
#include "Platform/qChain.h"
#include "SingleThreadCallPolicy.h"
#include "WorkerThreads.h"

namespace Quazal {
    class Scheduler : public RootObject {
    public:
        class SchedulerWorkerThread : public WorkerThreads {
        public:
            SchedulerWorkerThread() : m_pScheduler(0) {}
            virtual ~SchedulerWorkerThread() {}
            virtual void Initialize() {}
            virtual void Work() { m_pScheduler->Dispatch(0x64, 1); }

            Scheduler *m_pScheduler; // 0x24
        };

        Scheduler(unsigned char, SchedulerWorkerThread *);
        virtual ~Scheduler();

        void StartDispatcherThread();
        void Dispatch(unsigned int, unsigned int);

        static bool CurrentThreadCanWaitForJob();
        static CriticalSection s_csGlobalSystemLock;
        static Scheduler *GetInstance() {
            Core *inst = Core::GetInstance();
            return !inst ? nullptr : inst->m_pScheduler;
            if (!inst)
                return nullptr;
            else
                return inst->m_pScheduler;
        }

        int unk4; // 0x4
        bool unk8; // 0x8
        SchedulerWorkerThread *m_pWorkerThreads; // 0xc
        EventHandler unk10; // 0x10
        Event *unk34; // 0x34
        CriticalSection unk38;
        CriticalSection unk4c;
        qChain<Job *> unk60;
        qChain<Job *> unk70;
        qChain<Job *> unk80;
        qMap<Time, Job *> unk90;
        bool unka8;
        WaterMark unkac;
        WaterMark unkdc;
        ProfilingUnit unk110;
        Time unk158;
        Time unk160;
        unsigned int unk168;
        SingleThreadCallPolicy unk16c;
        ProfilingUnit unk180;
        HighResolutionChrono unk1c8;
        bool unk1d8;
        bool unk1d9;
    };
}
