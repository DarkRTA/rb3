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
        mCurrentState = reinterpret_cast<StateFuncFactory>(&DuplicatedObject::ValidState);
    }

    StateMachine::StateFuncFactory DuplicatedObject::InvalidState(const QEvent &e) {
        return static_cast<StateFuncFactory>(&StateMachine::TopState);
    }

    StateMachine::StateFuncFactory DuplicatedObject::ValidState(const QEvent &e) {
        if ((int)e.GetSignal() == 1) {
            mCurrentState =
                reinterpret_cast<StateFuncFactory>(&DuplicatedObject::ValidState);
            return 0;
        } else if ((e.GetSignal() & 0xFFFF) - 4 >= 0) {
            static_cast<const Operation &>(e).Trace(1);
            Trace(1);
            static TransitionPath t_;
            StaticStateTransition(
                &t_, reinterpret_cast<StateFuncFactory>(&DuplicatedObject::InvalidState)
            );
            return 0;
        } else {
            return static_cast<StateFuncFactory>(&StateMachine::TopState);
        }
    }

}