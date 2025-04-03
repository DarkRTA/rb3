#pragma once
#include "Platform/Holder.h"
#include "Plugins/Message.h"
#include "Protocol/ClientProtocol.h"
#include "Protocol/ProtocolCallContext.h"
#include "Services/Gathering.h"
#include "ddl/ResultRange.h"

namespace Quazal {
    class CustomMatchMakingClient : public ClientProtocol {
    public:
        CustomMatchMakingClient() : ClientProtocol(1) {}
        virtual ~CustomMatchMakingClient() {}
        virtual void ExtractCallSpecificResults(Message *, ProtocolCallContext *);

        void
        CallCustomFind(ProtocolCallContext *, const int &, const qList<int> &, const ResultRange &, qList<AnyObjectHolder<Gathering, String> > *);
    };
}