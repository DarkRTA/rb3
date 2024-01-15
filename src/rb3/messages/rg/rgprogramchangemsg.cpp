#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_80314474
RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314500
Symbol RGProgramChangeMsg::Type() {
    static Symbol t("rg_program_change");
    return t;
}