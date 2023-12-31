#ifndef RB3_KEY_MESSAGES_HPP
#define RB3_KEY_MESSAGES_HPP
#include "message.hpp"

class KeysAccelerometerMsg : Message {
public:
    KeysAccelerometerMsg(int, int, int, int); // fn_803157A8
    virtual ~KeysAccelerometerMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardConnectedAccessoriesMsg : Message {
public:
    KeyboardConnectedAccessoriesMsg(int, int); // fn_80315520
    virtual ~KeyboardConnectedAccessoriesMsg(); // fn_800A7FF4
    virtual void Unk1() = 0;
    static Symbol Type();
};

class KeyboardExpressionPedalMsg : Message {
public:
    KeyboardExpressionPedalMsg(int, int); // fn_80315448
    virtual ~KeyboardExpressionPedalMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardHighHandPlacementMsg : Message {
public:
    KeyboardHighHandPlacementMsg(int, int); // fn_80315998
    virtual ~KeyboardHighHandPlacementMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardKeyReleasedMsg : Message {
public:
    KeyboardKeyReleasedMsg(int, int); // fn_80315298
    virtual ~KeyboardKeyReleasedMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardLowHandPlacementMsg : Message {
public:
    KeyboardLowHandPlacementMsg(int, int); // fn_803158C0
    virtual ~KeyboardLowHandPlacementMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardModMsg : Message {
public:
    KeyboardModMsg(int, int); // fn_80315370
    virtual ~KeyboardModMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardStompBoxMsg : Message {
public:
    KeyboardStompBoxMsg(int, int); // fn_803156D0
    virtual ~KeyboardStompBoxMsg(); // fn_800A7FF4
    static Symbol Type();
};

class KeyboardSustainMsg : Message {
public:
    KeyboardSustainMsg(int, int); // fn_803155F8
    virtual ~KeyboardSustainMsg(); // fn_800A7FF4
    static Symbol Type();
};

#endif
