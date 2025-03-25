#pragma once
#include "obj/Msg.h"
#include "obj/Object.h"

class RockCentralOpCompleteMsg : public Message, public Hmx::Object {
public:
    RockCentralOpCompleteMsg();
    RockCentralOpCompleteMsg(bool b, int i, DataNode n) : Message(Type(), b, i, n) {}
    RockCentralOpCompleteMsg(DataArray *da) : Message(da) {}
    virtual ~RockCentralOpCompleteMsg() {}
    static Symbol Type() {
        static Symbol t("rock_central_op_complete_msg");
        return t;
    }
    bool Success() const { return mData->Int(2); }
    int Arg1() const { return mData->Int(3); }
    DataNode Arg2() const;
};