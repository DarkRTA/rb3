#pragma once
#include "Core/InstanceControl.h"

namespace Quazal {
    class PseudoSingleton : public InstanceControl {
    public:
        PseudoSingleton(unsigned int);
        virtual ~PseudoSingleton();

        bool SetContext(unsigned int);
        void SetContextIfRequired(unsigned int);
        bool UsingInstantiationContext();

        static int GetCurrentContext();
        static bool s_bUseInstantiationContext;
    };
}
