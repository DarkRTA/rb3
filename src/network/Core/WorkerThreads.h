#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/ObjectThread.h"
#include "Platform/RootObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class WorkerThreads : public RootObject {
    public:
        enum State {
            Running = 0,
            Stopping = 1,
            Stopped = 2
        };
        WorkerThreads();
        virtual ~WorkerThreads();
        virtual void Initialize() {}
        virtual void Teardown() {}
        virtual void Work() = 0;

        void Run(int);
        bool Start(unsigned int);
        bool Stop();
        unsigned int GetNbWorkers() const;

        CriticalSection m_csState; // 0x4
        State m_eState; // 0x18
        qVector<ObjectThread<WorkerThreads, int> *> m_vecThreads; // 0x1c
    };
}