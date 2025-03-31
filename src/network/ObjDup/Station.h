#pragma once
#include "StationDDL.h"

namespace Quazal {

    class Station : public _DO_Station {
    public:
        Station();
        virtual ~Station();
        virtual bool ApproveFaultRecovery();
        virtual bool ApproveEmigration(unsigned int);
        virtual bool ValidOperation(DOOperation *);
        virtual void OperationEnd(DOOperation *);
        virtual void Trace(unsigned int) const;
        virtual void TestInvariants();

        int GetStationID() const;

        static Station *GetLocalInstance();
    };
}