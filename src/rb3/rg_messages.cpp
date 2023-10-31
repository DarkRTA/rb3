#include "data.hpp"
#include "symbol.hpp"
#include "stringstrummedmsg.hpp"
#include "rgaccelerometermsg.hpp"
#include "rgconnectedaccessoriesmsg.hpp"
#include "rgpitchbendmsg.hpp"
#include "rgmutingmsg.hpp"
#include "rgstompboxmsg.hpp"
#include "rgprogramchangemsg.hpp"
#include "rgswingmsg.hpp"
#include "rgfretbuttondownmsg.hpp"
#include "rgfretbuttonupmsg.hpp"

// fn_80313F64
Symbol GetStringStrummedSymbol(){
    static Symbol lbl_8091A254("string_strummed");
    return lbl_8091A254;
}

// fn_80313E98
StringStrummedMsg::StringStrummedMsg(int i1, int i2, int i3, int i4) : 
    Message(GetStringStrummedSymbol(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)) { }

// fn_80313FB0
Symbol GetStringStoppedSymbol(){
    static Symbol lbl_8091A258("string_stopped");
    return lbl_8091A258;
}

// fn_803140C8
Symbol GetRGAccelerometerSymbol(){
    static Symbol lbl_8091A25C("rg_accelerometer");
    return lbl_8091A25C;
}

// fn_80313FFC
RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4) : 
    Message(GetRGAccelerometerSymbol(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)) { }

// fn_803141A0
Symbol GetRGConnectedAccessoriesSymbol(){
    static Symbol lbl_8091A260("rg_connected_accessories");
    return lbl_8091A260;
}

// fn_80314114
RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2) : 
    Message(GetRGConnectedAccessoriesSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_80314278
Symbol GetRGPitchBendSymbol(){
    static Symbol lbl_8091A264("rg_pitch_bend");
    return lbl_8091A264;
}

// fn_803141EC
RGPitchBendMsg::RGPitchBendMsg(int i1, int i2) : 
    Message(GetRGPitchBendSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_80314350
Symbol GetRGMutingSymbol(){
    static Symbol lbl_8091A268("rg_muting");
    return lbl_8091A268;
}

// fn_803142C4
RGMutingMsg::RGMutingMsg(int i1, int i2) :
    Message(GetRGMutingSymbol(), DataNode(i1), DataNode(i2)) {}

// fn_80314428
Symbol GetRGStompBoxSymbol(){
    static Symbol lbl_8091A26C("rg_stomp_box");
    return lbl_8091A26C;
}

// fn_8031439C
RGStompBoxMsg::RGStompBoxMsg(int i1, int i2) :
    Message(GetRGStompBoxSymbol(), DataNode(i1), DataNode(i2)) {}

// fn_80314500
Symbol GetRGProgramChangeSymbol(){
    static Symbol lbl_8091A270("rg_program_change");
    return lbl_8091A270;
}

// fn_80314474
RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2) :
    Message(GetRGProgramChangeSymbol(), DataNode(i1), DataNode(i2)) {}

// fn_803145D8
Symbol GetRGSwingSymbol(){
    static Symbol lbl_8091A274("rg_swing");
    return lbl_8091A274;
}

// fn_8031454C
RGSwingMsg::RGSwingMsg(int i1, int i2) :
    Message(GetRGSwingSymbol(), DataNode(i1), DataNode(i2)) {}

// fn_803146D0
Symbol GetRGFretButtonDownSymbol(){
    static Symbol lbl_8091A278("rg_fret_button_down");
    return lbl_8091A278;
}

// fn_80314624
RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, int i3) :
    Message(GetRGFretButtonDownSymbol(), DataNode(i1), DataNode(i2), DataNode(i3)) {}

// fn_803147C8
Symbol GetRGFretButtonUpSymbol(){
    static Symbol lbl_8091A27C("rg_fret_button_up");
    return lbl_8091A27C;
}

// fn_8031471C
RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, int i3) :
    Message(GetRGFretButtonUpSymbol(), DataNode(i1), DataNode(i2), DataNode(i3)) {}
