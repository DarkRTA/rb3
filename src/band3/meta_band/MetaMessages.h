#pragma once
#include "obj/Msg.h"

class SigninChangedMsg : public Message {
public:
    SigninChangedMsg() : Message(Type()) {}
    SigninChangedMsg(DataArray *da) : Message(da) {}
    virtual ~SigninChangedMsg() {}
    static Symbol Type() {
        static Symbol t("signin_changed");
        return t;
    }
};

class ConnectionStatusChangedMsg : public Message {
public:
    ConnectionStatusChangedMsg() : Message(Type()) {}
    ConnectionStatusChangedMsg(DataArray *da) : Message(da) {}
    virtual ~ConnectionStatusChangedMsg() {}
    static Symbol Type() {
        static Symbol t("connection_status_changed");
        return t;
    }
};