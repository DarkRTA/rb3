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

        // Type for a pointer to a member function that takes QEvent and returns void
        typedef void (StateMachine::*StateFunc)(const QEvent &);
        // Type for a pointer to a member function that takes QEvent
        // and returns another StateFunc
        typedef StateFunc (StateMachine::*StateFuncFactory)(const QEvent &);

        class TransitionPath {
        public:
            StateFuncFactory unk0;
        };

        StateMachine(StateFunc);
        virtual ~StateMachine();

        StateFunc TopState(const QEvent &);
        void InitialTransition();
        void StaticStateTransition(TransitionPath *, StateFuncFactory);
        void DispatchEvent(const QEvent &);
        void TransitionPathSetup(TransitionPath *, StateFuncFactory);

        StateFunc Trigger(StateFuncFactory func, unsigned short us) {
            QSimpleEvent event(us);
            StateFunc ret = (this->*func)(event);
            return ret;
        }

        StateFuncFactory mCurrentState; // 0x4
        StateFuncFactory mSourceState; // 0x10
    };

}