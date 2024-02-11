#ifndef RB3_RG_MESSAGES_HPP
#define RB3_RG_MESSAGES_HPP
#include "Message.h"
#include "Symbol.h"

class RGAccelerometerMsg : public Message {
public:
    RGAccelerometerMsg(int, int, int, int); // fn_80313FFC
    virtual ~RGAccelerometerMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_accelerometer");
        return t;
    }
};

class RGConnectedAccessoriesMsg : public Message {
public:
    RGConnectedAccessoriesMsg(int, int); // fn_80314114
    virtual ~RGConnectedAccessoriesMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_connected_accessories");
        return t;
    }
};

class RGFretButtonDownMsg : public Message {
public:
    RGFretButtonDownMsg(int, int, int); // fn_80314624
    virtual ~RGFretButtonDownMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_fret_button_down");
        return t;
    }
};

class RGFretButtonUpMsg : public Message {
public:
    RGFretButtonUpMsg(int, int, int); // fn_8031471C
    virtual ~RGFretButtonUpMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_fret_button_up");
        return t;
    }
};

class RGMutingMsg : public Message {
public:
    RGMutingMsg(int, int); // fn_803142C4
    virtual ~RGMutingMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_muting");
        return t;
    }
};

class RGPitchBendMsg : public Message {
public:
    RGPitchBendMsg(int, int); // fn_803141EC
    virtual ~RGPitchBendMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_pitch_bend");
        return t;
    }
};

class RGProgramChangeMsg : public Message {
public:
    RGProgramChangeMsg(int, int); // fn_80314474
    virtual ~RGProgramChangeMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_program_change");
        return t;
    }
};

class RGStompBoxMsg : public Message {
public:
    RGStompBoxMsg(int, int); // fn_8031439C
    virtual ~RGStompBoxMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_stomp_box");
        return t;
    }
};

class RGSwingMsg : public Message {
public:
    RGSwingMsg(int, int); // fn_8031454C
    virtual ~RGSwingMsg(){} // fn_800A7FF4
    static Symbol Type(){
        static Symbol t("rg_swing");
        return t;
    }
};

#endif
