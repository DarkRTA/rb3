#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

// fn_803155F8
KeyboardSustainMsg::KeyboardSustainMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315684
Symbol KeyboardSustainMsg::Type() {
    static Symbol t("keyboard_sustain");
    return t;
}