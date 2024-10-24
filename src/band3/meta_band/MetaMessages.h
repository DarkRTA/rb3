#pragma once
#include "obj/Msg.h"

class CharacterFinishedLoadingMsg : public Message {
public:
    CharacterFinishedLoadingMsg() : Message(Type()) {}
    CharacterFinishedLoadingMsg(DataArray *da) : Message(da) {}
    virtual ~CharacterFinishedLoadingMsg() {}
    static Symbol Type() {
        static Symbol t("character_finished_loading_msg");
        return t;
    }
};

class FinalizedColorsMsg : public Message {
public:
    FinalizedColorsMsg() : Message(Type()) {}
    FinalizedColorsMsg(DataArray *da) : Message(da) {}
    virtual ~FinalizedColorsMsg() {}
    static Symbol Type() {
        static Symbol t("finalized_colors_msg");
        return t;
    }
};

class InputStatusChangedMsg : public Message {
public:
    InputStatusChangedMsg() : Message(Type()) {}
    InputStatusChangedMsg(DataArray *da) : Message(da) {}
    virtual ~InputStatusChangedMsg() {}
    static Symbol Type() {
        static Symbol t("input_status_changed");
        return t;
    }
};

class InputUserLeftMsg : public Message {
public:
    InputUserLeftMsg() : Message(Type()) {}
    InputUserLeftMsg(DataArray *da) : Message(da) {}
    virtual ~InputUserLeftMsg() {}
    static Symbol Type() {
        static Symbol t("input_user_left");
        return t;
    }
};

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