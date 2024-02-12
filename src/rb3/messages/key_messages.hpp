#ifndef RB3_KEY_MESSAGES_HPP
#define RB3_KEY_MESSAGES_HPP
#include "Message.h"

class KeysAccelerometerMsg : public Message {
public:
    KeysAccelerometerMsg(int, int, int, int); // fn_803157A8
    virtual ~KeysAccelerometerMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keys_accelerometer");
        return t;
    }
};

class KeyboardConnectedAccessoriesMsg : public Message {
public:
    KeyboardConnectedAccessoriesMsg(int, int); // fn_80315520
    virtual ~KeyboardConnectedAccessoriesMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_connected_accessories");
        return t;
    }
};

class KeyboardExpressionPedalMsg : public Message {
public:
    KeyboardExpressionPedalMsg(int, int); // fn_80315448
    virtual ~KeyboardExpressionPedalMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_expression_pedal");
        return t;
    }
};

class KeyboardHighHandPlacementMsg : public Message {
public:
    KeyboardHighHandPlacementMsg(int, int); // fn_80315998
    virtual ~KeyboardHighHandPlacementMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_high_hand_placement");
        return t;
    }
};

class KeyboardKeyReleasedMsg : public Message {
public:
    KeyboardKeyReleasedMsg(int, int); // fn_80315298
    virtual ~KeyboardKeyReleasedMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_key_released");
        return t;
    }
};

class KeyboardLowHandPlacementMsg : public Message {
public:
    KeyboardLowHandPlacementMsg(int, int); // fn_803158C0
    virtual ~KeyboardLowHandPlacementMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_low_hand_placement");
        return t;
    }
};

class KeyboardModMsg : public Message {
public:
    KeyboardModMsg(int, int); // fn_80315370
    virtual ~KeyboardModMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_mod");
        return t;
    }
};

class KeyboardStompBoxMsg : public Message {
public:
    KeyboardStompBoxMsg(int, int); // fn_803156D0
    virtual ~KeyboardStompBoxMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_stomp_box");
        return t;
    }
};

class KeyboardSustainMsg : public Message {
public:
    KeyboardSustainMsg(int, int); // fn_803155F8
    virtual ~KeyboardSustainMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("keyboard_sustain");
        return t;
    }
};

#endif
