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
        bool Participate(ProtocolCallContext *, unsigned int, const String &);
        bool LaunchSession(ProtocolCallContext *, unsigned int, const char *);
        void CancelParticipation(ProtocolCallContext *, unsigned int, const String &);
        void UnregisterGathering(ProtocolCallContext *, unsigned int);
        void
        UpdateGathering(ProtocolCallContext *, const AnyObjectHolder<Gathering, String> &);
        void SetState(ProtocolCallContext *, unsigned int, unsigned int);
        bool
        FindByID(ProtocolCallContext *, unsigned int, AnyObjectHolder<Gathering, String> *);
    };
}