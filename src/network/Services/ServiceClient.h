#pragma once
#include "Platform/RootObject.h"
#include "Protocol/Protocol.h"

namespace Quazal {

    class ServiceClient : public RootObject {
    public:
        ServiceClient(unsigned int);
        virtual ~ServiceClient();
        virtual bool IsConnected() const;
        virtual void UseLocalLoopback(unsigned int, unsigned int);
        virtual void ConnectionStateHasChanged();
        virtual bool IsFaulty() const;
        virtual bool RegisterProtocols();

        bool RegisterExtraProtocol(Protocol *, unsigned char);
    };

}