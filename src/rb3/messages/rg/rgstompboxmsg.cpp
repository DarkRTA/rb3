#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_8031439C
RGStompBoxMsg::RGStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314428
Symbol RGStompBoxMsg::Type() {
    static Symbol t("rg_stomp_box");
    return t;
}