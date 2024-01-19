#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_803158C0
KeyboardLowHandPlacementMsg::KeyboardLowHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031594C
Symbol KeyboardLowHandPlacementMsg::Type() {
    static Symbol t("keyboard_low_hand_placement");
    return t;
}