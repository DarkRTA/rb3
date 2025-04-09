#pragma once
#include "obj/Msg.h"

DECLARE_MESSAGE(StringStrummedMsg, "string_strummed")
StringStrummedMsg(int, int, int, int);
int GetStringNum() const { return mData->Int(2); }
int GetFretNum() const { return mData->Int(3); }
int GetVelocity() const { return mData->Int(4); }
int GetPadNum() const { return mData->Int(5); }
END_MESSAGE

DECLARE_MESSAGE(StringStoppedMsg, "string_stopped")
StringStoppedMsg(int, int, int, int);
int GetStringNum() const { return mData->Int(2); }
int GetFretNum() const { return mData->Int(3); }
int GetVelocity() const { return mData->Int(4); }
int GetPadNum() const { return mData->Int(5); }
END_MESSAGE

DECLARE_MESSAGE(RGAccelerometerMsg, "rg_accelerometer")
RGAccelerometerMsg(int, int, int, int);
int GetNode2() const { return mData->Int(2); }
int GetNode3() const { return mData->Int(3); }
int GetNode4() const { return mData->Int(4); }
int GetPadNum() const { return mData->Int(5); }
END_MESSAGE

DECLARE_MESSAGE(RGConnectedAccessoriesMsg, "rg_connected_accessories")
RGConnectedAccessoriesMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(RGPitchBendMsg, "rg_pitch_bend")
RGPitchBendMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(RGMutingMsg, "rg_muting")
RGMutingMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(RGStompBoxMsg, "rg_stomp_box")
RGStompBoxMsg(bool, int);
END_MESSAGE

DECLARE_MESSAGE(RGProgramChangeMsg, "rg_program_change")
RGProgramChangeMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(RGSwingMsg, "rg_swing")
RGSwingMsg(int, int);
int GetNode2() const { return mData->Int(2); } // some sort of mask
int GetPadNum() const { return mData->Int(3); }
END_MESSAGE

DECLARE_MESSAGE(RGFretButtonDownMsg, "rg_fret_button_down")
RGFretButtonDownMsg(int, int, bool);
int GetNode2() const { return mData->Int(2); } // string
int GetPadNum() const { return mData->Int(3); }
int GetShifted() const { return mData->Int(4); }
END_MESSAGE

DECLARE_MESSAGE(RGFretButtonUpMsg, "rg_fret_button_up")
RGFretButtonUpMsg(int, int, bool);
int GetNode2() const { return mData->Int(2); } // string
int GetPadNum() const { return mData->Int(3); }
int GetShifted() const { return mData->Int(4); }
END_MESSAGE
