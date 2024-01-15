#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_80315998
KeyboardHighHandPlacementMsg::KeyboardHighHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315A24
Symbol KeyboardHighHandPlacementMsg::Type() {
    static Symbol t("keyboard_high_hand_placement");
    return t;
}