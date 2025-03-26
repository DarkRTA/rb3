#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "network/Protocol/ClientProtocol.h"

namespace Quazal {

    class Message;

    class RBTestClient : public ClientProtocol {
    public:
        RBTestClient() : ClientProtocol(1) {}
        virtual ~RBTestClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);
    };
}
