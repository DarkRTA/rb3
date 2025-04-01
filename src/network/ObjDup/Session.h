#pragma once
#include "SessionDDL.h"

namespace Quazal {
    class Session : public _DO_Session {
    public:
        Session();
        virtual ~Session();
        virtual void OperationBegin(DOOperation *);
        virtual void OperationEnd(DOOperation *);
        virtual void Trace(unsigned int) const;

        static Session *GetInstance();
    };
}