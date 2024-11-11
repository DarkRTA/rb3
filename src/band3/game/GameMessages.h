#pragma once
#include "obj/Msg.h"
#include "os/User.h"

// move any of these out if they belong better somewhere else

#include "obj/Object.h"

class RockCentralOpCompleteMsg : public Message, public Hmx::Object {
public:
    RockCentralOpCompleteMsg();
    RockCentralOpCompleteMsg(bool b, int i, DataNode n) : Message(Type(), b, i, n) {}
    RockCentralOpCompleteMsg(DataArray* da) : Message(da) {}
    virtual ~RockCentralOpCompleteMsg(){}
    static Symbol Type(){ static Symbol t("rock_central_op_complete_msg"); return t; }
};