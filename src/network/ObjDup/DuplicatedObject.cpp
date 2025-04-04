#include "network/ObjDup/DuplicatedObject.h"
#include "Core/StateMachine.h"

namespace Quazal {

    DuplicatedObject::DuplicatedObject()
        : StateMachine(static_cast<StateMachineFunc>(&DuplicatedObject::SetInitialState)),
          m_setDuplicationSet(3), m_setCachedDuplicationSet(0) {}

}