#pragma once
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Platform/Time.h"

namespace Quazal {
    class TimedSignal : public RootObject {
    public:
        enum Signal {
            OFF,
            ON,
            ONCE,
            PULSE
        };
        TimedSignal();
        virtual ~TimedSignal();

        void SetOn(int);
        void SetPulse(int);
        bool IsSignaled();
        void Reset();

        bool IsDeadline() {
            Time cur = Time::GetTime();
            return m_oTime + m_oTimeInterval < cur;
        }

        void SetSignal(int interval, Signal s) {
            Reset();
            m_oTime = Time::GetTime();
            m_eSignal = s;
            m_oTimeInterval = interval;
        }

        int m_oTimeInterval; // 0x4
        Time m_oTime; // 0x8
        Signal m_eSignal; // 0x10
        String m_strName; // 0x14
    };
}