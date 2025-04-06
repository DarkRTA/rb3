#include "network/Core/TimedSignals.h"

namespace Quazal {
    TimedSignal::TimedSignal()
        : m_oTimeInterval(0), m_eSignal(OFF), m_strName("TimedSignal") {
        m_oTime = Time::GetTime();
    }

    TimedSignal::~TimedSignal() {}

    inline static const char *EmptyStrName() { return ""; }

    inline void TimedSignal::Reset() {
        m_eSignal = OFF;
        m_oTimeInterval = 0;
        m_strName = EmptyStrName();
        m_oTime = 0;
    }

    void TimedSignal::SetOn(int i1) { SetSignal(i1, ON); }
    void TimedSignal::SetPulse(int i1) { SetSignal(i1, PULSE); }

    bool TimedSignal::IsSignaled() {
        if (!IsDeadline() || m_eSignal == OFF) {
            return false;
        } else {
            switch (m_eSignal) {
            case ON:
                break;
            case ONCE:
                Reset();
                break;
            case PULSE:
                SetSignal(m_oTimeInterval, PULSE);
                break;
            default:
                break;
            }
            return true;
        }
    }
}