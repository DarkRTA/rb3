#pragma once
#include "Core/Operation.h"
#include "Core/StateMachine.h"
#include "ObjDup/DOOperation.h"

namespace Quazal {

    class DuplicatedObject : public StateMachine {
    public:
        DuplicatedObject();
        virtual ~DuplicatedObject();
        virtual bool HasGlobalDOProperty() const;
        virtual bool HasForcedNonGlobalProperty() const;
        virtual bool ApproveFaultRecovery();
        virtual bool ApproveEmigration(unsigned int);
        virtual void InitDO();
        virtual float ComputeDistance(DuplicatedObject *);
        virtual void CallOperationOnDatasets(DOOperation *, Operation::_Event);
        virtual bool ValidOperation(DOOperation *);
        virtual void OperationBegin(DOOperation *);
        virtual void OperationEnd(DOOperation *);
        virtual float GetWeight();
        virtual void Trace(unsigned int) const;
        virtual void CallOperationEndOnAdapters(DOOperation *);
        virtual void TestInvariants();
        virtual bool IsACoreDO() const = 0;
        virtual bool IsABootstrapDO() const;
        virtual void UpdateCellStats(int, int, int);

        unsigned int GetMasterID() const;
    };

}