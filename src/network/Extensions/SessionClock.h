#pragma once
#include "Platform/Time.h"
#include "SessionClockDDL.h"

namespace Quazal {
    class SessionClock : public _DO_SessionClock {
    public:
        SessionClock();
        virtual ~SessionClock();
        virtual void OperationEnd(DOOperation *);

        static Time GetTime();
    };
}