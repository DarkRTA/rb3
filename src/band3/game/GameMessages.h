#pragma once
#include "obj/Msg.h"
#include "os/User.h"

// move any of these out if they belong better somewhere else

BEGIN_MESSAGE(ModeChangedMsg, mode_changed, );
    MESSAGE_ARRAY_CTOR(ModeChangedMsg)
END_MESSAGE;
inline ModeChangedMsg::ModeChangedMsg() : Message(ModeChangedMsg::Type()) {}

BEGIN_MESSAGE(ProcessedJoinRequestMsg, processed_join_request, bool);
    MESSAGE_ARRAY_CTOR(ProcessedJoinRequestMsg)
    bool GetProcessed() const { return mData->Int(2); }
END_MESSAGE;
inline ProcessedJoinRequestMsg::ProcessedJoinRequestMsg(bool b) : Message(Type(), b) {}

BEGIN_MESSAGE(SessionDisconnectedMsg, session_disconnected, );
    MESSAGE_ARRAY_CTOR(SessionDisconnectedMsg)
END_MESSAGE;
inline SessionDisconnectedMsg::SessionDisconnectedMsg() : Message(Type()) {}

BEGIN_MESSAGE(SessionBusyMsg, session_busy, );
    MESSAGE_ARRAY_CTOR(SessionBusyMsg)
END_MESSAGE;

BEGIN_MESSAGE(SessionReadyMsg, session_ready, int);
    MESSAGE_ARRAY_CTOR(SessionReadyMsg)
END_MESSAGE;
inline SessionReadyMsg::SessionReadyMsg(int i) : Message(SessionReadyMsg::Type(), i) {}

BEGIN_MESSAGE(JoinResultMsg, join_result, );
    MESSAGE_ARRAY_CTOR(JoinResultMsg)
END_MESSAGE;

BEGIN_MESSAGE(SyncStartGameMsg, sync_start_game, );
    MESSAGE_ARRAY_CTOR(SyncStartGameMsg)
END_MESSAGE;
inline SyncStartGameMsg::SyncStartGameMsg() : Message(SyncStartGameMsg::Type()) {}

BEGIN_MESSAGE(SettingsChangedMsg, settings_changed, );
    MESSAGE_ARRAY_CTOR(SettingsChangedMsg)
END_MESSAGE;
inline SettingsChangedMsg::SettingsChangedMsg() : Message(SettingsChangedMsg::Type()) {}

BEGIN_MESSAGE(InviteAcceptedMsg, invite_accepted, );
    MESSAGE_ARRAY_CTOR(InviteAcceptedMsg)
END_MESSAGE;

#include "obj/Object.h"

class RockCentralOpCompleteMsg : public Message, public Hmx::Object {
public:
    RockCentralOpCompleteMsg();
    RockCentralOpCompleteMsg(bool b, int i, DataNode n) : Message(Type(), b, i, n) {}
    RockCentralOpCompleteMsg(DataArray* da) : Message(da) {}
    virtual ~RockCentralOpCompleteMsg(){}
    static Symbol Type(){ static Symbol t("rock_central_op_complete_msg"); return t; }
};