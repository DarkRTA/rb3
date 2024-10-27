#pragma once
#include "obj/Msg.h"
#include "os/User.h"

// move any of these out if they belong better somewhere else

BEGIN_MESSAGE(LocalUserLeftMsg, local_user_left, LocalUser*);
    MESSAGE_ARRAY_CTOR(LocalUserLeftMsg)
    LocalUser* GetUser() const { return mData->Obj<LocalUser>(2); }
END_MESSAGE;

BEGIN_MESSAGE(RemoteUserLeftMsg, remote_user_left, RemoteUser*);
    MESSAGE_ARRAY_CTOR(RemoteUserLeftMsg)
    RemoteUser* GetUser() const { return mData->Obj<RemoteUser>(2); }
END_MESSAGE;

BEGIN_MESSAGE(UserLoginMsg, user_login, );
    MESSAGE_ARRAY_CTOR(UserLoginMsg)
END_MESSAGE;

BEGIN_MESSAGE(AddLocalUserResultMsg, add_local_user_result_msg, int, LocalUser*);
    MESSAGE_ARRAY_CTOR(AddLocalUserResultMsg)
    int GetResult() const { return mData->Int(2); }
END_MESSAGE;

BEGIN_MESSAGE(ModeChangedMsg, mode_changed, );
    MESSAGE_ARRAY_CTOR(ModeChangedMsg)
END_MESSAGE;

BEGIN_MESSAGE(ProcessedJoinRequestMsg, processed_join_request, bool);
    MESSAGE_ARRAY_CTOR(ProcessedJoinRequestMsg)
    bool GetProcessed() const { return mData->Int(2); }
END_MESSAGE;

BEGIN_MESSAGE(SessionDisconnectedMsg, session_disconnected, );
    MESSAGE_ARRAY_CTOR(SessionDisconnectedMsg)
END_MESSAGE;

BEGIN_MESSAGE(SessionBusyMsg, session_busy, );
    MESSAGE_ARRAY_CTOR(SessionBusyMsg)
END_MESSAGE;

BEGIN_MESSAGE(JoinResultMsg, join_result, );
    MESSAGE_ARRAY_CTOR(JoinResultMsg)
END_MESSAGE;

inline ModeChangedMsg::ModeChangedMsg() : Message(ModeChangedMsg::Type()) {}
inline ProcessedJoinRequestMsg::ProcessedJoinRequestMsg(bool b) : Message(Type(), b) {}

#include "obj/Object.h"

class RockCentralOpCompleteMsg : public Message, public Hmx::Object {
public:
    RockCentralOpCompleteMsg();
    RockCentralOpCompleteMsg(DataArray* da) : Message(da) {}
    virtual ~RockCentralOpCompleteMsg(){}
    static Symbol Type(){ static Symbol t("rock_central_op_complete_msg"); return t; }
};