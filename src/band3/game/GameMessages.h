#pragma once
#include "obj/Msg.h"
#include "os/User.h"

// move any of these out if they belong better somewhere else

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