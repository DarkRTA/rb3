#include "os/UsbMidiGuitarMsgs.h"

StringStrummedMsg::StringStrummedMsg(int i1, int i2, int i3, int i4)
    : Message(Type(), i1, i2, i3, i4) {}

RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(Type(), i1, i2, i3, i4) {}

RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), i1, i2) {}

RGPitchBendMsg::RGPitchBendMsg(int i1, int i2) : Message(Type(), i1, i2) {}

RGMutingMsg::RGMutingMsg(int i1, int i2) : Message(Type(), i1, i2) {}

RGStompBoxMsg::RGStompBoxMsg(bool i1, int i2) : Message(Type(), i1, i2) {}

RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2) : Message(Type(), i1, i2) {}

RGSwingMsg::RGSwingMsg(int i1, int i2) : Message(Type(), i1, i2) {}

RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, bool i3)
    : Message(Type(), i1, i2, i3) {}

RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, bool i3)
    : Message(Type(), i1, i2, i3) {}

StringStoppedMsg::StringStoppedMsg(int i1, int i2, int i3, int i4)
    : Message(Type(), i1, i2, i3, i4) {}
