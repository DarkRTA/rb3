#include "network/net/MessageBrokerDDL_Wii.h"

namespace Quazal {
    unsigned int _DO_MessageBroker::s_uiClassID;

    _DO_MessageBroker::_DO_MessageBroker() { m_dohMyself.SetDOClassID(s_uiClassID); }
}