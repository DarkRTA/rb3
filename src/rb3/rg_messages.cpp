#include "data.hpp"
#include "symbol.hpp"
#include "stringstrummedmsg.hpp"
#include "stringstoppedmsg.hpp"
#include "rg_messages.hpp"

// fn_80313F64
Symbol StringStrummedMsg::Type() {
    static Symbol t("string_strummed");
    return t;
}

// fn_80313E98
StringStrummedMsg::StringStrummedMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

// fn_80313FB0
Symbol StringStoppedMsg::Type() {
    static Symbol t("string_stopped");
    return t;
}

// fn_803140C8
Symbol RGAccelerometerMsg::Type() {
    static Symbol t("rg_accelerometer");
    return t;
}

// fn_80313FFC
RGAccelerometerMsg::RGAccelerometerMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

// fn_803141A0
Symbol RGConnectedAccessoriesMsg::Type() {
    static Symbol t("rg_connected_accessories");
    return t;
}

// fn_80314114
RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314278
Symbol RGPitchBendMsg::Type() {
    static Symbol lbl_8091A264("rg_pitch_bend");
    return lbl_8091A264;
}

// fn_803141EC
RGPitchBendMsg::RGPitchBendMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314350
Symbol RGMutingMsg::Type() {
    static Symbol t("rg_muting");
    return t;
}

// fn_803142C4
RGMutingMsg::RGMutingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314428
Symbol RGStompBoxMsg::Type() {
    static Symbol t("rg_stomp_box");
    return t;
}

// fn_8031439C
RGStompBoxMsg::RGStompBoxMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_80314500
Symbol RGProgramChangeMsg::Type() {
    static Symbol t("rg_program_change");
    return t;
}

// fn_80314474
RGProgramChangeMsg::RGProgramChangeMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803145D8
Symbol RGSwingMsg::Type() {
    static Symbol t("rg_swing");
    return t;
}

// fn_8031454C
RGSwingMsg::RGSwingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}

// fn_803146D0
Symbol RGFretButtonDownMsg::Type() {
    static Symbol t("rg_fret_button_down");
    return t;
}

// fn_80314624
RGFretButtonDownMsg::RGFretButtonDownMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}

// fn_803147C8
Symbol RGFretButtonUpMsg::Type() {
    static Symbol t("rg_fret_button_up");
    return t;
}

// fn_8031471C
RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}
