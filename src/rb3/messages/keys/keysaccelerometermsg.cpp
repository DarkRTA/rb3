#include "data.hpp"
#include "symbol.hpp"
#include "key_messages.hpp"

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