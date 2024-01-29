#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_80313FFC
RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

// fn_80314114
RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803141EC
RGPitchBendMsg::RGPitchBendMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803142C4
RGMutingMsg::RGMutingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031439C
RGStompBoxMsg::RGStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314474
RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_8031454C
RGSwingMsg::RGSwingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314624
RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}

// fn_8031471C
RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}