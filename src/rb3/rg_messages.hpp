#ifndef RB3_RG_MESSAGES_HPP
#define RB3_RG_MESSAGES_HPP
#include "message.hpp"
#include "symbol.hpp"

class RGAccelerometerMsg : Message {
public:
    RGAccelerometerMsg(int, int, int, int); // fn_80313FFC
    virtual ~RGAccelerometerMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGConnectedAccessoriesMsg : Message {
public:
    RGConnectedAccessoriesMsg(int, int); // fn_80314114
    virtual ~RGConnectedAccessoriesMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGFretButtonDownMsg : Message {
public:
    RGFretButtonDownMsg(int, int, int); // fn_80314624
    virtual ~RGFretButtonDownMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGFretButtonUpMsg : Message {
public:
    RGFretButtonUpMsg(int, int, int); // fn_8031471C
    virtual ~RGFretButtonUpMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGMutingMsg : Message {
public:
    RGMutingMsg(int, int); // fn_803142C4
    virtual ~RGMutingMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGPitchBendMsg : Message {
public:
    RGPitchBendMsg(int, int); // fn_803141EC
    virtual ~RGPitchBendMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGProgramChangeMsg : Message {
public:
    RGProgramChangeMsg(int, int); // fn_80314474
    virtual ~RGProgramChangeMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGStompBoxMsg : Message {
public:
    RGStompBoxMsg(int, int); // fn_8031439C
    virtual ~RGStompBoxMsg(); // fn_800A7FF4
    static Symbol Type();
};

class RGSwingMsg : Message {
public:
    RGSwingMsg(int, int); // fn_8031454C
    virtual ~RGSwingMsg(); // fn_800A7FF4
    static Symbol Type();
};

#endif
