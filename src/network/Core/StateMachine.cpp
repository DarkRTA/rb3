#include "network/Core/StateMachine.h"

namespace Quazal {

    StateMachine::StateMachine(StateMachineVoidFunc func)
        : mCurrentState(&StateMachine::TopState), mSourceState(func) {}

    StateMachine::~StateMachine() {}

    StateMachine::StateMachineVoidFunc StateMachine::TopState(const QEvent &) {
        return 0;
    }

    void StateMachine::InitialTransition() {
        QSimpleEvent event(0);
        (this->*mSourceState)(event);
        StateMachineFPFunc state = mCurrentState;

        Trigger(state, 2);
        while (!Trigger(state, 1)) {
            state = mCurrentState;
            Trigger(state, 2);
        }
    }

    void StateMachine::StaticStateTransition(TransitionPath *, StateMachineFPFunc) {}

    void StateMachine::TransitionPathSetup(TransitionPath *, StateMachineFPFunc) {}

}