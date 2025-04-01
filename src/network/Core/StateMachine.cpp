#include "network/Core/StateMachine.h"

namespace Quazal {

    StateMachine::StateMachine(StateMachineFunc func)
        : mCurrentState(&StateMachine::TopState), mSourceState(func) {}

    StateMachine::~StateMachine() {}

}