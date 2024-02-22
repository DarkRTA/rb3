#include "os/UsbMidiKeyboardMsgs.h"

KeyboardKeyPressedMsg::KeyboardKeyPressedMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}

KeyboardKeyReleasedMsg::KeyboardKeyReleasedMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardModMsg::KeyboardModMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardExpressionPedalMsg::KeyboardExpressionPedalMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardConnectedAccessoriesMsg::KeyboardConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardSustainMsg::KeyboardSustainMsg(bool i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardStompBoxMsg::KeyboardStompBoxMsg(bool i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeysAccelerometerMsg::KeysAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(),
        DataNode(i1),
        DataNode(i2),
        DataNode(i3),
        DataNode(i4)
    ) {
}

KeyboardLowHandPlacementMsg::KeyboardLowHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

KeyboardHighHandPlacementMsg::KeyboardHighHandPlacementMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}
