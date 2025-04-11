#pragma once
#include "obj/Msg.h"

DECLARE_MESSAGE(KeyboardKeyPressedMsg, "keyboard_key_pressed");
KeyboardKeyPressedMsg(int, int, int);
int GetMidiNote() const { return mData->Int(2); }
int GetNode3() const {
    return mData->Int(3);
} // fret button? but this is keys what frets are there
int GetPadNum() const { return mData->Int(4); }
END_MESSAGE

DECLARE_MESSAGE(KeyboardKeyReleasedMsg, "keyboard_key_released")
KeyboardKeyReleasedMsg(int, int);
int GetMidiNote() const { return mData->Int(2); }
int GetPadNum() const { return mData->Int(3); }
END_MESSAGE

DECLARE_MESSAGE(KeyboardModMsg, "keyboard_mod")
KeyboardModMsg(int, int);
int GetNode2() const { return mData->Int(2); } // pitch/velocity?
int GetPadNum() const { return mData->Int(3); }
END_MESSAGE

DECLARE_MESSAGE(KeyboardExpressionPedalMsg, "keyboard_expression_pedal")
KeyboardExpressionPedalMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(KeyboardConnectedAccessoriesMsg, "keyboard_connected_accessories")
KeyboardConnectedAccessoriesMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(KeyboardSustainMsg, "keyboard_sustain")
KeyboardSustainMsg(bool, int);
int GetNode2() const { return mData->Int(2); }
int GetPadNum() const { return mData->Int(3); }
END_MESSAGE

DECLARE_MESSAGE(KeyboardStompBoxMsg, "keyboard_stomp_box")
KeyboardStompBoxMsg(bool, int);
END_MESSAGE

DECLARE_MESSAGE(KeysAccelerometerMsg, "keys_accelerometer")
KeysAccelerometerMsg(int, int, int, int);
END_MESSAGE

DECLARE_MESSAGE(KeyboardLowHandPlacementMsg, "keyboard_low_hand_placement")
KeyboardLowHandPlacementMsg(int, int);
END_MESSAGE

DECLARE_MESSAGE(KeyboardHighHandPlacementMsg, "keyboard_high_hand_placement")
KeyboardHighHandPlacementMsg(int, int);
END_MESSAGE