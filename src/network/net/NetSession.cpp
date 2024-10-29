#include "net/NetSession.h"
#include "NetMessage.h"
#include "os/Debug.h"

NetMessage* JoinResponseMsg::NewNetMessage(){ return new JoinResponseMsg(kSuccess, 0); }

namespace {
    void RegisterSessionMessages(){
        JoinResponseMsg::Register();
    }

    void DisconnectOnFail(){}
}

NetSession::NetSession(){
    RegisterSessionMessages();
    TheDebug.AddExitCallback(DisconnectOnFail);
    MILO_ASSERT(!TheNetSession, 0x5B);
    TheNetSession = this;
}