#include "os/UsbMidiGuitarMsgs.h"

RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGPitchBendMsg::RGPitchBendMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGMutingMsg::RGMutingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGStompBoxMsg::RGStompBoxMsg(bool i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGSwingMsg::RGSwingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, bool i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}

RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, bool i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}
