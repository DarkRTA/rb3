#include "Data.h"
#include "Symbol.h"
#include "key_messages.hpp"

// fn_80315298
KeyboardKeyReleasedMsg::KeyboardKeyReleasedMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315370
KeyboardModMsg::KeyboardModMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315448
KeyboardExpressionPedalMsg::KeyboardExpressionPedalMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315520
KeyboardConnectedAccessoriesMsg::KeyboardConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803155F8
KeyboardSustainMsg::KeyboardSustainMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803156D0
KeyboardStompBoxMsg::KeyboardStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

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

// fn_803158C0
KeyboardLowHandPlacementMsg::KeyboardLowHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80315998
KeyboardHighHandPlacementMsg::KeyboardHighHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}
