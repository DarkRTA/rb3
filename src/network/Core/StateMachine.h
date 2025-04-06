#pragma once
#include "Platform/RootObject.h"
#include "Platform/VirtualRootObject.h"

namespace Quazal {

    class StateMachine : public VirtualRootObject {
    public:
        class QEvent : public RootObject {
        public:
            QEvent() : m_bRepeatEvent(0) {}
            virtual ~QEvent() {}
            virtual unsigned short GetSignal() const = 0;

            bool m_bRepeatEvent; // 0x4
        };

        class QSimpleEvent : public QEvent {
        public:
            QSimpleEvent(unsigned short sig) : m_uiSignal(sig) {}
            virtual ~QSimpleEvent() {}
            virtual unsigned short GetSignal() const { return m_uiSignal; }

            unsigned short m_uiSignal; // 0x6
        };

        class TransitionPath {
        public:
        };

        typedef void (StateMachine::*StateMachineVoidFunc)(const QEvent &);
        typedef StateMachineVoidFunc (StateMachine::*StateMachineFPFunc)(const QEvent &);

        StateMachine(StateMachineVoidFunc);
        virtual ~StateMachine();

        StateMachineVoidFunc TopState(const QEvent &);
        void InitialTransition();
        void StaticStateTransition(TransitionPath *, StateMachineFPFunc);
        void DispatchEvent(const QEvent &);
        void TransitionPathSetup(TransitionPath *, StateMachineFPFunc);

        StateMachineVoidFunc Trigger(StateMachineFPFunc func, unsigned short us) {
            QSimpleEvent event(us);
            StateMachineVoidFunc ret = (this->*func)(event);
            return ret;
        }

        StateMachineFPFunc mCurrentState; // 0x4
        StateMachineVoidFunc mSourceState; // 0x10
    };

}