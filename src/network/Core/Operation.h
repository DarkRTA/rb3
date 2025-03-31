#pragma once
#include "Core/StateMachine.h"

namespace Quazal {

    class Operation : public StateMachine::QEvent {
    public:
        class _Event {
        public:
        };
        Operation(unsigned int);
        virtual ~Operation() {}
        virtual short GetSignal() const;
        // 4 pures
    };

}