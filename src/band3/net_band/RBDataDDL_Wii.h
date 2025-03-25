#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "network/Protocol/ClientProtocol.h"

namespace Quazal {

    class Message;

    class RBDataClient : public ClientProtocol {
    public:
        RBDataClient(unsigned int ui) : ClientProtocol(ui) {}
        virtual ~RBDataClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);
    };
}