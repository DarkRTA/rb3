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

// fn_80315370
KeyboardModMsg::KeyboardModMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803153FC
Symbol KeyboardModMsg::Type() {
    static Symbol t("keyboard_mod");
    return t;
}

// fn_80315448
KeyboardExpressionPedalMsg::KeyboardExpressionPedalMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803154D4
Symbol KeyboardExpressionPedalMsg::Type() {
    static Symbol t("keyboard_expression_pedal");
    return t;
}

// fn_80315520
KeyboardConnectedAccessoriesMsg::KeyboardConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803155AC
Symbol KeyboardConnectedAccessoriesMsg::Type() {
    static Symbol t("keyboard_connected_accessories");
    return t;
}

// fn_803155F8
KeyboardSustainMsg::KeyboardSustainMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315684
Symbol KeyboardSustainMsg::Type() {
    static Symbol t("keyboard_sustain");
    return t;
}

// fn_803156D0
KeyboardStompBoxMsg::KeyboardStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031575C
Symbol KeyboardStompBoxMsg::Type() {
    static Symbol t("keyboard_stomp_box");
    return t;
}

// fn_803157A8
KeysAccelerometerMsg::KeysAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(),
        DataNode(i1),
        DataNode(i2),
        DataNode(i3),
        DataNode(i4)
    ) {
}

// fn_80315874
Symbol KeysAccelerometerMsg::Type() {
    static Symbol t("keys_accelerometer");
    return t;
}

// fn_803158C0
KeyboardLowHandPlacementMsg::KeyboardLowHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031594C
Symbol KeyboardLowHandPlacementMsg::Type() {
    static Symbol t("keyboard_low_hand_placement");
    return t;
}

// fn_80315998
KeyboardHighHandPlacementMsg::KeyboardHighHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315A24
Symbol KeyboardHighHandPlacementMsg::Type() {
    static Symbol t("keyboard_high_hand_placement");
    return t;
}