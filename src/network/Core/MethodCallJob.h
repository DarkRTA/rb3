#pragma once
#include "Core/PeriodicJob.h"
#include "Core/Job.h"
#include "Platform/String.h"

namespace Quazal {
    template <class T1, class T2, class T3>
    class MethodCallJob : public T3 {
    public:
        typedef void (T1::*JobFunc)(T2);

        MethodCallJob(const String &str, T1 *obj, JobFunc func, T2 arg)
            : T3(DebugString()), m_pTargetObject(obj) {
            m_pMethod = func;
            m_arg = arg;
        }
        virtual ~MethodCallJob() {}
        virtual void Execute() {
            JobFunc func = m_pMethod;
            (m_pTargetObject->*func)(m_arg);
        }
        virtual String GetTraceInfo() const {}

        JobFunc m_pMethod;
        T1 *m_pTargetObject;
        T2 m_arg;
    };
}