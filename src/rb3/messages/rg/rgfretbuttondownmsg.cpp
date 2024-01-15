#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_80314624
RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}

// fn_803146D0
Symbol RGFretButtonDownMsg::Type() {
    static Symbol t("rg_fret_button_down");
    return t;
}