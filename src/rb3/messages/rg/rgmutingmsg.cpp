#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_803142C4
RGMutingMsg::RGMutingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314350
Symbol RGMutingMsg::Type() {
    static Symbol t("rg_muting");
    return t;
}