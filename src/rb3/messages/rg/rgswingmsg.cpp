#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_8031454C
RGSwingMsg::RGSwingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803145D8
Symbol RGSwingMsg::Type() {
    static Symbol t("rg_swing");
    return t;
}