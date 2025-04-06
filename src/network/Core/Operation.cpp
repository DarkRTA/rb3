#include "network/Core/Operation.h"
#include "Platform/UserContext.h"

namespace Quazal {
    Operation::Operation(unsigned int origin) : m_uUserData(0), m_uiOrigin(origin) {
        m_bOperationAborted = false;
    }

    UserContext Operation::GetUserData() {
        return *static_cast<UserContext *>(m_uUserData);
    }

    void Operation::SetUserData(UserContext ctx) {
        UserContext *myCtx = static_cast<UserContext *>(m_uUserData);
        myCtx = &ctx;
    }

    void Operation::Trace(unsigned int ui) const { TraceImpl((_Event)4, ui); }
}