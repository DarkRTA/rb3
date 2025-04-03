#pragma once
#include "Plugins/StationURL.h"
#include "Protocol/ProtocolCallContext.h"
#include "Services/ServiceClient.h"

namespace Quazal {
    class SecureConnectionClient : public ServiceClient {
    public:
        SecureConnectionClient();
        virtual ~SecureConnectionClient();
        virtual bool IsFaulty() const;
        virtual bool RegisterProtocols();

        bool RequestURLs(ProtocolCallContext *, unsigned int, qList<StationURL> *);
    };
}