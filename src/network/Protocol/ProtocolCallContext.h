#pragma once
#include "Core/CallContext.h"
#include "Platform/qStd.h"

namespace Quazal {

    class ProtocolCallContext : public CallContext {
    public:
        ProtocolCallContext();
        virtual ~ProtocolCallContext();
        virtual void BeginTransition(_State, qResult, bool);

        qVector<int> unk48;
        int unk50;
        int unk54;
    };

}