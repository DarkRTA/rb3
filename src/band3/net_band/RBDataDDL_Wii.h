#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "network/Protocol/ClientProtocol.h"

namespace Quazal {

    class Message;

    class RBDataClient : public ClientProtocol {
    public:
        RBDataClient() : ClientProtocol(1) {}
        virtual ~RBDataClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);
    };
}