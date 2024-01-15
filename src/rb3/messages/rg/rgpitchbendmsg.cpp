#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_803141EC
RGPitchBendMsg::RGPitchBendMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314278
Symbol RGPitchBendMsg::Type() {
    static Symbol t("rg_pitch_bend");
    return t;
}