#include "netmessage.hpp"
#include "syncobjmsg.hpp"
#include "syncusermsg.hpp"
#include "syncallmsg.hpp"
#include "string.hpp"
#include "data.hpp"

#pragma dont_inline on
// fn_800AAE9C
NetMessage::NetMessage() {
}
#pragma dont_inline reset

// fn_800AAE1C
void SyncObjMsg::NewNetMessage() {
    // *this = *(new SyncObjMsg());
    SyncObjMsg *lol = new SyncObjMsg();
}

// fn_800AAE4C
SyncObjMsg::SyncObjMsg() : unk14(false) {
}

// fn_800AAEAC
void SyncUserMsg::NewNetMessage() {
    *this = *(new SyncUserMsg());
}

// fn_800AAEDC
SyncUserMsg::SyncUserMsg() {
}

// fn_800AAF50
void SyncAllMsg::NewNetMessage() {
    *this = *(new SyncAllMsg());
}

// fn_800AAF80
SyncAllMsg::SyncAllMsg() {
}

DataNode::DataNode(DataType ty, void* v){
    type = ty;
    value.miscVal = v;
}