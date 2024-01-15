#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_803156D0
KeyboardStompBoxMsg::KeyboardStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031575C
Symbol KeyboardStompBoxMsg::Type() {
    static Symbol t("keyboard_stomp_box");
    return t;
}