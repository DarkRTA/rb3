#include "os/JoypadMsgs.h"

ButtonDownMsg::ButtonDownMsg(LocalUser* user, JoypadButton butt, JoypadAction act, int i)
    : Message(Type(), DataNode(user), DataNode(butt), DataNode(act), DataNode(i)){
        
}

LocalUser* ButtonDownMsg::GetUser() const {
    return mData->Obj<LocalUser>(2);
}

ButtonUpMsg::ButtonUpMsg(LocalUser* user, JoypadButton butt, JoypadAction act, int i)
    : Message(Type(), DataNode(user), DataNode(butt), DataNode(act), DataNode(i)){
        
}

LocalUser* ButtonUpMsg::GetUser() const {
    return mData->Obj<LocalUser>(2);
}

JoypadConnectionMsg::JoypadConnectionMsg(LocalUser* user, bool b, int i)
    : Message(Type(), DataNode(user), DataNode(b), DataNode(i)){
        
}

LocalUser* JoypadConnectionMsg::GetUser() const {
    return mData->Obj<LocalUser>(2);
}
