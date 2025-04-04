#pragma once
#include "Platform/RootObject.h"
#include "Platform/VirtualRootObject.h"

namespace Quazal {

    class StateMachine : public VirtualRootObject {
    public:
        class QEvent : public RootObject {
        public:
            QEvent() : mRepeatEvent(0) {}
            virtual ~QEvent() {}
            virtual short GetSignal() const = 0;

            bool mRepeatEvent;
        };

        typedef void (StateMachine::*StateMachineFunc)(const QEvent &);

        StateMachine(StateMachineFunc);
        virtual ~StateMachine();

        void TopState(const QEvent &);

        StateMachineFunc mCurrentState; // 0x4
        StateMachineFunc mSourceState; // 0x10
    };

}