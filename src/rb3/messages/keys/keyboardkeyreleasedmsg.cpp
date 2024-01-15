#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_80315298
KeyboardKeyReleasedMsg::KeyboardKeyReleasedMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315324
Symbol KeyboardKeyReleasedMsg::Type() {
    static Symbol t("keyboard_key_released");
    return t;
}