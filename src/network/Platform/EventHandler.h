#pragma once

#include "Platform/CriticalSection.h"

namespace Quazal {

class Event;

class EventHandler : public CriticalSection {
    public:

    void SetEvent(Quazal::Event*);
    void ResetEvent(Quazal::Event*);
};
}
