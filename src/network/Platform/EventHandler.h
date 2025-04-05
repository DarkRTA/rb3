#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"

namespace Quazal {

    class Event;

    class EventHandler : public RootObject {
    public:
        EventHandler(unsigned short);
        ~EventHandler();

        void SetEvent(Event *);
        void ResetEvent(Event *);
        Event *CreateEventObject(unsigned int, unsigned int);

        CriticalSection m_csEventTable; // 0x0
        int unk14;
        int unk18;
        int unk1c;
        unsigned short unk20;
    };
}
