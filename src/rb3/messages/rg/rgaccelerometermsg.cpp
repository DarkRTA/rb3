#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_80313FFC
RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

// fn_803140C8
Symbol RGAccelerometerMsg::Type() {
    static Symbol t("rg_accelerometer");
    return t;
}