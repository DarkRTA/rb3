#ifndef PLUGINS_TIMEOUT_H
#define PLUGINS_TIMEOUT_H

#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {
    class Timeout : public RootObject {
    public:
        Timeout();
        ~Timeout();
        void SetExpirationTime(Time);
        void SetRelativeExpirationTime(int);
        bool IsExpired() const;
        bool IsAwaited() const;
        void SetRTO(unsigned int);
        void Start();
        unsigned int GetAwaitedTime();

    private:
        int m_oRTO;
        class Time m_oAwaitedTime;
        class Time m_oExpirationTime;
    };
}

#endif // PLUGINS_TIMEOUT_H