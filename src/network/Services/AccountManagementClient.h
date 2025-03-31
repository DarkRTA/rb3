#pragma once
#include "Protocol/ProtocolCallContext.h"
#include "Services/ServiceClient.h"

namespace Quazal {
    class AccountManagementClient : public ServiceClient {
    public:
        AccountManagementClient();
        virtual ~AccountManagementClient();
        virtual bool RegisterProtocols();

        bool DeleteAccount(ProtocolCallContext *, unsigned int);
    };
}