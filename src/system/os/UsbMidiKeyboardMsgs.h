#ifndef OS_USBMIDIKEYBOARDMSGS_H
#define OS_USBMIDIKEYBOARDMSGS_H
#include "obj/Msg.h"

BEGIN_MESSAGE(KeyboardKeyPressedMsg, keyboard_key_pressed, int, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardKeyReleasedMsg, keyboard_key_released, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardModMsg, keyboard_mod, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardExpressionPedalMsg, keyboard_expression_pedal, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardConnectedAccessoriesMsg, keyboard_connected_accessories, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardSustainMsg, keyboard_sustain, bool, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardStompBoxMsg, keyboard_stomp_box, bool, int);
END_MESSAGE;

BEGIN_MESSAGE(KeysAccelerometerMsg, keys_accelerometer, int, int, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardLowHandPlacementMsg, keyboard_low_hand_placement, int, int);
END_MESSAGE;

BEGIN_MESSAGE(KeyboardHighHandPlacementMsg, keyboard_high_hand_placement, int, int);
END_MESSAGE;

#endif
