#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_80315448
KeyboardExpressionPedalMsg::KeyboardExpressionPedalMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803154D4
Symbol KeyboardExpressionPedalMsg::Type() {
    static Symbol t("keyboard_expression_pedal");
    return t;
}