#include "network/Core/PseudoSingleton.h"
#include "Core/InstanceControl.h"
#include "network/Platform/SystemError.h"

namespace Quazal {

    bool PseudoSingleton::s_bUseInstantiationContext;

    PseudoSingleton::PseudoSingleton(unsigned int ui) : InstanceControl(ui, 0) {}
    PseudoSingleton::~PseudoSingleton() {}

    bool PseudoSingleton::SetContext(unsigned int ui) {
        if (!s_bUseInstantiationContext) {
            SystemError::SignalError(0, 0, 0xe000000e, 0);
            return false;
        } else
            return true;
    }

    void PseudoSingleton::SetContextIfRequired(unsigned int) {}
    unsigned int PseudoSingleton::GetCurrentContext() { return 0; }

    bool PseudoSingleton::UsingInstantiationContext() {
        return s_bUseInstantiationContext;
    }

}