#include "net/NetSession.h"
#include "NetMessage.h"
#include "SessionMessages.h"
#include "os/Debug.h"

NetMessage* JoinRequestMsg::NewNetMessage(){ return new JoinRequestMsg(); }
NetMessage* JoinResponseMsg::NewNetMessage(){ return new JoinResponseMsg(kSuccess, 0); }
NetMessage* NewUserMsg::NewNetMessage(){ return new NewUserMsg(); }
NetMessage* UserLeftMsg::NewNetMessage(){ return new UserLeftMsg(); }
NetMessage* AddUserRequestMsg::NewNetMessage(){ return new AddUserRequestMsg(); }
NetMessage* AddUserResponseMsg::NewNetMessage(){ return new AddUserResponseMsg(); }
NetMessage* UpdateUserDataMsg::NewNetMessage(){ return new UpdateUserDataMsg(); }
NetMessage* BeginArbitrationMsg::NewNetMessage(){ return new BeginArbitrationMsg(); }
NetMessage* FinishedArbitrationMsg::NewNetMessage(){ return new FinishedArbitrationMsg(); }
NetMessage* StartGameOnTimeMsg::NewNetMessage(){ return new StartGameOnTimeMsg(); }
NetMessage* EndGameMsg::NewNetMessage(){ return new EndGameMsg(); }
NetMessage* VoiceDataMsg::NewNetMessage(){ return new VoiceDataMsg(); }
NetMessage* DataArrayMsg::NewNetMessage(){ return new DataArrayMsg(); }

namespace {
    void RegisterSessionMessages(){
        JoinRequestMsg::Register();
        JoinResponseMsg::Register();
        NewUserMsg::Register();
        AddUserRequestMsg::Register();
        AddUserResponseMsg::Register();
        UserLeftMsg::Register();
        UpdateUserDataMsg::Register();
        BeginArbitrationMsg::Register();
        FinishedArbitrationMsg::Register();
        StartGameOnTimeMsg::Register();
        EndGameMsg::Register();
        VoiceDataMsg::Register();
        DataArrayMsg::Register();
    }

    void DisconnectOnFail(){}
}

NetSession::NetSession(){
    RegisterSessionMessages();
    TheDebug.AddExitCallback(DisconnectOnFail);
    MILO_ASSERT(!TheNetSession, 0x5B);
    TheNetSession = this;
}