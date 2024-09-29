#include "Timeout.h"

namespace Quazal {
    Timeout::Timeout() {}

    Timeout::~Timeout() {}

    void Timeout::SetExpirationTime(Time time) {
        m_oExpirationTime = time;
    }

    void Timeout::SetRTO(unsigned int rto) {
        m_oRTO = rto;
    }

}