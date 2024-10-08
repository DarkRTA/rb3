#pragma once
#include "obj/Msg.h"

// move any of these out if they belong better somewhere else

BEGIN_MESSAGE(LocalUserLeftMsg, local_user_left, );
    MESSAGE_ARRAY_CTOR(LocalUserLeftMsg)
END_MESSAGE;

BEGIN_MESSAGE(UserLoginMsg, user_login, );
    MESSAGE_ARRAY_CTOR(UserLoginMsg)
END_MESSAGE;

BEGIN_MESSAGE(AddLocalUserResultMsg, add_local_user_result_msg, );
    MESSAGE_ARRAY_CTOR(AddLocalUserResultMsg)
END_MESSAGE;

#include "obj/Object.h"

class RockCentralOpCompleteMsg : public Message, public Hmx::Object {
public:
    RockCentralOpCompleteMsg();
    RockCentralOpCompleteMsg(DataArray* da) : Message(da) {}
    virtual ~RockCentralOpCompleteMsg(){}
    static Symbol Type(){ static Symbol t("rock_central_op_complete_msg"); return t; }
};