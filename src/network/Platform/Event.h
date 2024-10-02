#pragma once

#include "Platform/RootObject.h"
#include "Platform/EventHandler.h"

namespace Quazal {
class Event : public Quazal::RootObject {
    Event(EventHandler*, unsigned int, unsigned int);
    ~Event();
    void Set();
    void Reset();

    EventHandler* mHandler; // 0x0
    uint mStartTime; // 0x4
    uint mEndTime; // 0x8
};
}
