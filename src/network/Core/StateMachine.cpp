#include "network/Core/StateMachine.h"

namespace Quazal {

    StateMachine::StateMachine(StateFunc func)
        : mCurrentState(&StateMachine::TopState),
          // this reinterpret cast feels so wrong i'm ngl
          mSourceState(reinterpret_cast<StateFuncFactory>(func)) {}

    StateMachine::~StateMachine() {}

    StateMachine::StateFunc StateMachine::TopState(const QEvent &) { return 0; }

    void StateMachine::InitialTransition() {
        QSimpleEvent event(0);
        (this->*mSourceState)(event);
        StateFuncFactory state = mCurrentState;

        Trigger(state, 2);
        while (!Trigger(state, 1)) {
            state = mCurrentState;
            Trigger(state, 2);
        }
    }

    void
    StateMachine::StaticStateTransition(TransitionPath *path, StateFuncFactory func) {
        StateFuncFactory state = mCurrentState;
        while (state != mSourceState) {
            StateFunc ret = (this->*state)(QSimpleEvent(3));
            if (!ret) {
            } else {
            }
        }
    }

    void StateMachine::DispatchEvent(const QEvent &event) {
        do {
            const_cast<QEvent &>(event).m_bRepeatEvent = false;
            mSourceState = mCurrentState;
            do {
                StateFunc func = (this->*mSourceState)(event);
                mSourceState = reinterpret_cast<StateFuncFactory>(func);
            } while (mSourceState);
        } while (event.m_bRepeatEvent);
    }

    void StateMachine::TransitionPathSetup(TransitionPath *, StateFuncFactory) {}

}