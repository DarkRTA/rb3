#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_80315370
KeyboardModMsg::KeyboardModMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803153FC
Symbol KeyboardModMsg::Type() {
    static Symbol t("keyboard_mod");
    return t;
}