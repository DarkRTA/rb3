#ifndef OS_USBMIDIGUITARMSGS_H
#define OS_USBMIDIGUITARMSGS_H
#include "obj/Msg.h"

BEGIN_MESSAGE(RGAccelerometerMsg, rg_accelerometer, int, int, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGConnectedAccessoriesMsg, rg_connected_accessories, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGFretButtonDownMsg, rg_fret_button_down, int, int, bool);
END_MESSAGE;

BEGIN_MESSAGE(RGFretButtonUpMsg, rg_fret_button_up, int, int, bool);
END_MESSAGE;

BEGIN_MESSAGE(RGMutingMsg, rg_muting, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGPitchBendMsg, rg_pitch_bend, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGProgramChangeMsg, rg_program_change, int, int);
END_MESSAGE;

BEGIN_MESSAGE(RGStompBoxMsg, rg_stomp_box, bool, int);
END_MESSAGE;

BEGIN_MESSAGE(RGSwingMsg, rg_swing, int, int);
END_MESSAGE;

#endif
