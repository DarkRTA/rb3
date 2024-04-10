#ifndef OS_USBMIDIGUITARMSGS_H
#define OS_USBMIDIGUITARMSGS_H
#include "obj/Msg.h"

BEGIN_MESSAGE(StringStrummedMsg, string_strummed, int, int, int, int);
    int GetNode2() const { return mData->Int(2); }
    int GetNode3() const { return mData->Int(3); }
    int GetNode4() const { return mData->Int(4); }
    int GetNode5() const { return mData->Int(5); }
    MESSAGE_ARRAY_CTOR(StringStrummedMsg)
END_MESSAGE;

BEGIN_MESSAGE(StringStoppedMsg, string_stopped, int, int, int, int);
    MESSAGE_ARRAY_CTOR(StringStoppedMsg)
END_MESSAGE;

BEGIN_MESSAGE(RGAccelerometerMsg, rg_accelerometer, int, int, int, int);
    MESSAGE_ARRAY_CTOR(RGAccelerometerMsg)
    int GetNode2() const { return mData->Int(2); }
    int GetNode3() const { return mData->Int(3); }
    int GetNode4() const { return mData->Int(4); }
    int GetPadNum() const { return mData->Int(5); }
END_MESSAGE;

BEGIN_MESSAGE(RGConnectedAccessoriesMsg, rg_connected_accessories, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGPitchBendMsg, rg_pitch_bend, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGMutingMsg, rg_muting, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGStompBoxMsg, rg_stomp_box, bool, int);
END_MESSAGE;

BEGIN_MESSAGE(RGProgramChangeMsg, rg_program_change, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGSwingMsg, rg_swing, int, int);
    MESSAGE_ARRAY_CTOR(RGSwingMsg)
    int GetNode2() const { return mData->Int(2); }
    int GetPadNum() const { return mData->Int(3); }
END_MESSAGE;

BEGIN_MESSAGE(RGFretButtonDownMsg, rg_fret_button_down, int, int, bool);
    MESSAGE_ARRAY_CTOR(RGFretButtonDownMsg)
    int GetNode2() const { return mData->Int(2); }
    int GetPadNum() const { return mData->Int(3); }
    int GetShifted() const { return mData->Int(4); }
END_MESSAGE;

BEGIN_MESSAGE(RGFretButtonUpMsg, rg_fret_button_up, int, int, bool);
    MESSAGE_ARRAY_CTOR(RGFretButtonUpMsg)
    int GetNode2() const { return mData->Int(2); }
    int GetPadNum() const { return mData->Int(3); }
    int GetShifted() const { return mData->Int(4); }
END_MESSAGE;

#endif
