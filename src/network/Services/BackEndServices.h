#pragma once
#include "Platform/RootObject.h"
#include "Platform/String.h"

namespace Quazal {

    class BackEndServices : public RootObject {
    public:
        BackEndServices();
        virtual ~BackEndServices();
        virtual void PostLogoutCleanup();
        virtual int GetAccountManagementClient() const; // fix ret type

        static String FormatQErrorCodeString(const String &, unsigned int);
    };

}