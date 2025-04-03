#pragma once
#include "Platform/Holder.h"
#include "Protocol/ProtocolCallContext.h"
#include "Services/Gathering.h"
#include "Services/ServiceClient.h"

namespace Quazal {
    class MatchMakingClient : public ServiceClient {
    public:
        MatchMakingClient();
        virtual ~MatchMakingClient();
        virtual bool RegisterProtocols();

        bool
        RegisterGathering(ProtocolCallContext *, const AnyObjectHolder<Gathering, String> &);
    };
}