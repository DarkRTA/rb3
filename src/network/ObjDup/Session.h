#pragma once
#include "Core/CallContext.h"
#include "Plugins/StationURL.h"
#include "SessionDDL.h"

namespace Quazal {
    class Session : public _DO_Session {
    public:
        Session();
        virtual ~Session();
        virtual void OperationBegin(DOOperation *);
        virtual void OperationEnd(DOOperation *);
        virtual void Trace(unsigned int) const;

        static bool JoinSessionImpl(CallContext *, const qList<Quazal::StationURL> &);
        static void RegisterWellKnownDOsFactory(void (*)(void));
        static Session *GetInstance();
    };
}