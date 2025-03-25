#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "network/Protocol/ClientProtocol.h"

namespace Quazal {

    class Message;

    class RBBinaryDataClient : public ClientProtocol {
    public:
        RBBinaryDataClient(unsigned int ui) : ClientProtocol(ui) {}
        virtual ~RBBinaryDataClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);
    };
}
