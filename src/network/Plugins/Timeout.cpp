#include "Timeout.h"

namespace Quazal {
    Timeout::Timeout() {
        m_oAwaitedTime = 0;
        m_oExpirationTime = 0;
        m_oRTO = 0;
    }

    Timeout::~Timeout() {}

    void Timeout::SetExpirationTime(Time time) { m_oExpirationTime = time; }

    void Timeout::SetRelativeExpirationTime(int i1) {
        m_oExpirationTime = Time::GetTime() + i1;
    }

    void Timeout::SetRTO(unsigned int rto) { m_oRTO = rto; }

    void Timeout::Start() { m_oAwaitedTime = Time::GetTime() + m_oRTO; }

    Time Timeout::GetAwaitedTime() { return m_oAwaitedTime; }

}