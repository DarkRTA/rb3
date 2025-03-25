#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "network/Protocol/ClientProtocol.h"

namespace Quazal {

    class Message;

    class RBTestClient : public ClientProtocol {
    public:
        RBTestClient(unsigned int ui) : ClientProtocol(ui) {}
        virtual ~RBTestClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);
    };
}
