#include "network/Platform/EventHandler.h"

namespace Quazal {
    EventHandler::EventHandler(unsigned short us)
        : m_csEventTable(0x40000000), unk20(us) {}
}