#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_80315520
KeyboardConnectedAccessoriesMsg::KeyboardConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803155AC
Symbol KeyboardConnectedAccessoriesMsg::Type() {
    static Symbol t("keyboard_connected_accessories");
    return t;
}