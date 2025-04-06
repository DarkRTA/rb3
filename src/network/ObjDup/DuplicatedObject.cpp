#include "network/ObjDup/DuplicatedObject.h"
#include "Core/Scheduler.h"
#include "Core/StateMachine.h"
#include "Platform/CriticalSection.h"
#include "Platform/ScopedCS.h"

namespace Quazal {

    CriticalSection DuplicatedObject::s_csRefCount(0x40000000);

    DuplicatedObject::DuplicatedObject()
        : StateMachine(static_cast<StateFunc>(&DuplicatedObject::SetInitialState)),
          m_setDuplicationSet(3), m_setCachedDuplicationSet(0) {
        m_uiRefCount = 0;
        m_uiRelevanceCount = 0;
        m_uiFlags = 0;
        {
            ScopedCS cs(Scheduler::GetInstance()->unk38);
            AcquireMainReference();
            m_uiFlags |= 1;
        }
        InitialTransition();
    }

    DuplicatedObject::~DuplicatedObject() {}

    void DuplicatedObject::SetStationSpecialRelevance() {
        m_refMasterStation.SetSoft();
        m_setDuplicationSet.SetFlags(1);
    }

    void DuplicatedObject::SetInitialState(const QEvent &) {
        mCurrentState = static_cast<StateFuncFactory>(&DuplicatedObject::ValidState);
    }

}