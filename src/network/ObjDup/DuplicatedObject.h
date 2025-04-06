#pragma once
#include "Core/Operation.h"
#include "Core/StateMachine.h"
#include "DOHandle.h"
#include "ObjDup/MasterStationRef.h"
#include "ObjDup/DOOperation.h"
#include "Platform/CriticalSection.h"
#include "Platform/ScopedCS.h"
#include "Selection.h"

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
        virtual float GetWeight() { return 0; }
        virtual void Trace(unsigned int) const;
        virtual void CallOperationEndOnAdapters(DOOperation *);
        virtual void TestInvariants();
        virtual bool IsACoreDO() const = 0;
        virtual bool IsABootstrapDO() const { return false; }
        virtual void UpdateCellStats(int, int, int) {}

        unsigned int GetMasterID() const;
        bool IsADuplicationMaster() const;
        void SetStationSpecialRelevance();

        void SetInitialState(const QEvent &);
        StateMachineVoidFunc ValidState(const QEvent &);

        void AcquireMainReference() {
            volatile ScopedCS cs(s_csRefCount);
            m_uiRefCount++;
        }

        static CriticalSection s_csRefCount;

        unsigned short m_uiRefCount; // 0x1c
        unsigned short m_uiRelevanceCount; // 0x1e
        MasterStationRef m_refMasterStation; // 0x20
        unsigned short m_uiFlags; // 0x2c
        Selection m_setDuplicationSet; // 0x30
        DOHandle m_dohMyself; // 0x50
        Selection m_setCachedDuplicationSet; // 0x54
    };

}