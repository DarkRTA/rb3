#pragma once
#include "Core/StateMachine.h"
#include "Platform/UserContext.h"

namespace Quazal {

    class Operation : public StateMachine::QEvent {
    public:
        enum _Event {
        };
        Operation(unsigned int);
        virtual ~Operation() {}
        virtual unsigned short GetSignal() const { return GetType(); }
        virtual int GetType() const = 0;
        virtual const char *GetClassNameString() const = 0;
        virtual void ForceImplOperationCommonMethodsMacro() = 0;
        virtual void TraceImpl(_Event, unsigned int) const = 0;

        void Trace(unsigned int) const;
        void SetUserData(UserContext);
        UserContext GetUserData();

        bool m_bOperationAborted; // 0x5
        void *m_uUserData; // 0x8
        unsigned int m_uiOrigin; // 0xc
    };

}