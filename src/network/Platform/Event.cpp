#include "Event.h"

namespace Quazal {
Event::Event(EventHandler* eh, unsigned int st, unsigned int et) : mHandler(eh), mStartTime(st), mEndTime(et) {}

Event::~Event() {}

void Event::Set() { mHandler->SetEvent(this); }

void Event::Reset() { mHandler->ResetEvent(this); }
}
