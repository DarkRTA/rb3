#include "os/Joypad.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "math/MathFuncs.h"
#include "obj/MsgSource.h"
#include "obj/DataFunc.h"

namespace {
    static DataArray* gControllersCfg; // 0x0
    static DataArray* gButtonMeanings; // 0x4
    static int gPadsToKeepAlive; // prolly not an int
    static int gPadsToKeepAliveNext; // also prolly not an int
    static int gKeepAliveCountdown;
    static int gKeepaliveThresholdMs = -1; // 0x18
    static bool gExportMsgs;
    static bool gJoypadLibInitialized;
    static JoypadData gJoypadData[4];
    static bool gJoypadDisabled[4]; // 0x28c
    static MsgSource* gJoypadMsgSource; // 0x290

    static DataNode OnJoypadSetVibrate(DataArray* arr){
        JoypadSetVibrate(arr->Int(1), arr->Int(2) != 0);
        return DataNode(1);
    }

    static DataNode OnJoypadVibrate(DataArray* arr){
        return DataNode(JoypadGetPadData(arr->Int(1))->mVibrateEnabled);
    }

    static DataNode OnJoypadControllerTypePadNum(DataArray* arr){
        return DataNode(JoypadControllerTypePadNum(arr->Int(1)));
    }

    static DataNode OnJoypadIsConnectedPadNum(DataArray* arr){
        return DataNode(JoypadIsConnectedPadNum(arr->Int(1)));
    }

    static DataNode OnJoypadIsButtonDownPadNum(DataArray* arr){
        int pad = arr->Int(1);
        MILO_ASSERT(( 0) <= (pad) && (pad) < ( kNumJoypads), 0x80);
        int ret = gJoypadData[pad].mButtons & 1 << arr->Int(2);
        return DataNode(ret != 0);
    }

    static DataNode OnJoypadIsCalbertGuitar(DataArray* arr){
        return DataNode(JoypadIsCalbertGuitar(arr->Int(1)));
    }

    #pragma pool_data off

    bool IsJoypadDetectMatch(DataArray* detect_cfg, const JoypadData& data){
        static Symbol type("type");
        static Symbol button("button");
        static Symbol stick("stick");
        static Symbol trigger("trigger");
        static Symbol X("X");
        static Symbol Y("Y");
        static Symbol OR("or");
        static Symbol AND("and");
        Symbol sym = detect_cfg->Sym(0);
        if(sym == type){
            return detect_cfg->Int(1) == (int)data.mType;
        }
        else if(sym == button){
            return data.mButtons & 1 << detect_cfg->Int(1);
        }
        else if(sym == stick){
            int i4 = 0;
            Symbol axis_sym = detect_cfg->Sym(2);
            if(axis_sym == X){
                i4 = 0;
            }
            else if(axis_sym == Y){
                i4 = 1;
            }
            else MILO_FAIL("bad axis %s in controller detect array\n", axis_sym);
            int i3 = detect_cfg->Int(1);
            float f7 = detect_cfg->Float(3);
            return f7 == data.mSticks[i3][i4];
        }
        else if(sym == trigger){
            return detect_cfg->Float(2) == data.mTriggers[detect_cfg->Int(1)];
        }
        else if(sym == OR){
            for(int i = 1; i < detect_cfg->Size(); i++){
                if(IsJoypadDetectMatch(detect_cfg->Array(i), data)) return true;
            }
            return false;
        }
        else if(sym == AND){
            for(int i = 1; i < detect_cfg->Size(); i++){
                if(!IsJoypadDetectMatch(detect_cfg->Array(i), data)) return false;
            }
            return true;
        }
        else {
            MILO_FAIL("Unknown keyword '%s' in joypad detect block", sym);
            return false;
        }
    }

    static DataNode DataJoypadReset(DataArray* arr){
        JoypadReset();
        return DataNode(0);
    }

}

JoypadData::JoypadData() : mControllerType() {
    
}

float JoypadData::GetAxis(Symbol axis) const {
    static Symbol lx("LX");
    static Symbol ly("LY");
    static Symbol rx("RX");
    static Symbol ry("RY");
    static Symbol tl("TL");
    static Symbol tr("TR");
    static Symbol sx("SX");
    static Symbol sy("SY");
    static Symbol sz("SZ");
    if(axis == lx) return mSticks[0][0];
    else if(axis == ly) return mSticks[0][1];
    else if(axis == rx) return mSticks[1][0];
    else if(axis == ry) return mSticks[1][1];
    else if(axis == tl) return mTriggers[0];
    else if(axis == tr) return mTriggers[1];
    else if(axis == sx) return mSensors[0];
    else if(axis == sy) return mSensors[1];
    else if(axis == sz) return mSensors[2];
    else TheDebug.Fail(MakeString("Bad axis %s in JoypadData::GetAxis()\n"));
    return 0.0f;
}

#pragma pool_data on

int JoypadData::FloatToBucket(float f) const {
    if(f < 0.11f) return 0;
    if(f < 0.31f) return 6;
    if(f < 0.46f) return 5;
    if(f < 0.61f) return 4;
    if(f < 0.77f) return 3;
    if(f < 0.89f) return 2;
    return 1;
}

int JoypadData::GetVelocityBucket(Symbol axis) const {
    float ax = GetAxis(axis);
    if(ax < 0.0f) ax += 1.0f;
    return FloatToBucket(ax);
}

int JoypadData::GetPressureBucket(JoypadButton b) const {
    MILO_ASSERT(int(b) < kNumPressureButtons, 0x140);
    float val = mPressures[b];
    if(mType == kJoypadPs3RoDrums){
        val = val * 255.0f;
        val = 1.0f - Clamp<float>(0.0f, 100.0f, val - 22.0f) / 100.0f;
    }
    return FloatToBucket(val);
}

int ButtonToVelocityBucket(JoypadData* data, JoypadButton btn){
    switch(data->mType){
        case kJoypadXboxDrumsRb2:
            switch(btn){
                case kPad_Circle: return data->GetVelocityBucket(LX);
                case kPad_Tri: return data->GetVelocityBucket(LY);
                case kPad_Square: return data->GetVelocityBucket(RX);
                case kPad_X: return data->GetVelocityBucket(RY);
                default: return 0;
            }
            break;
        case kJoypadXboxDrums:
            switch(btn){
                case kPad_Circle: return data->GetVelocityBucket(LY);
                case kPad_Tri: return data->GetVelocityBucket(RX);
                case kPad_Square: return data->GetVelocityBucket(RX);
                case kPad_X: return data->GetVelocityBucket(LY);
                default: return 0;
            }
            break;
        case kJoypadPs3HxDrums:
        case kJoypadPs3HxDrumsRb2:
        case kJoypadWiiHxDrumsRb2:
            switch(btn){
                case kPad_Circle: case kPad_Tri: case kPad_Square: case kPad_X:
                    return data->GetPressureBucket(btn);
                default: return 0;
            }
        default: return 0;
    }
}

void JoypadInitCommon(DataArray* joypad_config){
    gJoypadMsgSource = Hmx::Object::New<MsgSource>();
    float thresh;
    joypad_config->FindData("threshold", thresh, true);
    joypad_config->FindData("keepalive_ms", gKeepaliveThresholdMs, true);
    gJoypadDisabled[0] = 0;
    gJoypadDisabled[1] = 0;
    gJoypadDisabled[2] = 0;
    gJoypadDisabled[3] = 0;
    DataArray* ignores = joypad_config->FindArray("ignore", true);
    for(int i = 1; i < ignores->Size(); i++){
        int nodeInt = ignores->Int(i);
        if(nodeInt <= 3U){
            gJoypadDisabled[nodeInt] = true;
        }
    }
    gControllersCfg = joypad_config->FindArray("controllers", true);
    gButtonMeanings = joypad_config->FindArray("button_meanings", true);
    DataRegisterFunc("joypad_reset", DataJoypadReset);
    DataRegisterFunc("joypad_vibrate", OnJoypadVibrate);
    DataRegisterFunc("joypad_set_vibrate", OnJoypadSetVibrate);
    DataRegisterFunc("joypad_controller_type_padnum", OnJoypadControllerTypePadNum);
    DataRegisterFunc("joypad_is_connected_padnum", OnJoypadIsConnectedPadNum);
    DataRegisterFunc("joypad_is_button_down", OnJoypadIsButtonDownPadNum);
    DataRegisterFunc("joypad_is_calbert_guitar", OnJoypadIsCalbertGuitar);
    gJoypadLibInitialized = true;
}

JoypadData* JoypadGetPadData(int pad_num){
    MILO_ASSERT(0 <= pad_num && pad_num < kNumJoypads, 0x5CC);
    return &gJoypadData[pad_num];
}

void JoypadSubscribe(Hmx::Object* obj){
    if(gJoypadMsgSource)
        gJoypadMsgSource->AddSink(obj, Symbol(), Symbol(), MsgSource::kHandle);
}

void JoypadUnsubscribe(Hmx::Object* obj){
    if(gJoypadMsgSource)
        gJoypadMsgSource->RemoveSink(obj, Symbol());
}

void JoypadPushThroughMsg(const Message& msg){
    if(gExportMsgs){
        gJoypadMsgSource->Handle(msg.Data(), false);
    }
}

void AssociateUserAndPad(LocalUser* iUser, int iPadNum){
    MILO_ASSERT(( 0) <= (iPadNum) && (iPadNum) < ( kNumJoypads), 0x61C);
    gJoypadData[iPadNum].mUser = iUser;
}

void ResetAllUsersPads(){
    for(int i = 0; i < 4; i++) AssociateUserAndPad(0, i);
}

int GetUsersPadNum(LocalUser* user){
    bool* disabled = gJoypadDisabled;
    JoypadData* data = gJoypadData;
    if(!disabled[0] && data[0].mUser == user) return 0;
    else if(!disabled[1] && data[1].mUser == user) return 1;
    else if(!disabled[2] && data[2].mUser == user) return 2;
    else if(!disabled[3] && data[3].mUser == user) return 3;
    else return -1;
}

LocalUser* JoypadGetUserFromPadNum(int iPadNum){
    MILO_ASSERT(( 0) <= (iPadNum) && (iPadNum) < ( kNumJoypads), 0x633);
    return gJoypadData[iPadNum].mUser;
}

int JoypadGetUsersPadNum(LocalUser* user){ return GetUsersPadNum(user); }

bool JoypadIsControllerTypePadNum(int padNum, Symbol controller_type){
    MILO_ASSERT(padNum != -1, 0x641);
    MILO_ASSERT(gControllersCfg, 0x644);
    DataArray* type_cfg = gControllersCfg->FindArray(controller_type, false);
    if(type_cfg){
        JoypadData* theData = &gJoypadData[padNum];
        DataArray* detect_cfg = type_cfg->FindArray("detect", true);
        if(detect_cfg->Size() != 1){
            if(IsJoypadDetectMatch(detect_cfg->Array(1), gJoypadData[padNum])){
                theData->mControllerType = controller_type;
                Symbol analogsticks("has_analog_sticks");
                DataArray* analog_sticks_arr = type_cfg->FindArray(analogsticks, true);
                theData->mHasAnalogSticks = analog_sticks_arr->Int(1) != 0;

                Symbol transsticks("translate_sticks");
                DataArray* translate_sticks_arr = type_cfg->FindArray(transsticks, true);
                theData->mTranslateSticks = translate_sticks_arr->Int(1) != 0;

                theData->mIgnoreButtonMask = 0;
                DataArray* ignore_arr = type_cfg->FindArray("ignore_buttons", false);
                if(ignore_arr){
                    for(int i = 1; i < ignore_arr->Size(); i++){
                        theData->mIgnoreButtonMask |= (1 << ignore_arr->Int(i));
                    }
                }

                Symbol isdrumsym("is_drum");
                DataArray* drum_arr = type_cfg->FindArray(isdrumsym, true);
                theData->mIsDrum = drum_arr->Int(1) != 0;

                Symbol cymbal("cymbal_mask");
                DataArray* cymbal_mask_arr = type_cfg->FindArray(cymbal, true);
                theData->mCymbalMask = cymbal_mask_arr->Int(1);

                Symbol green("green_cymbal_mask");
                DataArray* green_cymbal_mask_arr = type_cfg->FindArray(green, true);
                theData->mGreenCymbalMask = green_cymbal_mask_arr->Int(1);

                Symbol yellow("yellow_cymbal_mask");
                DataArray* yellow_mask_arr = type_cfg->FindArray(yellow, true);
                theData->mYellowCymbalMask = yellow_mask_arr->Int(1);

                Symbol blue("blue_cymbal_mask");
                DataArray* blue_cymbal_mask_arr = type_cfg->FindArray(blue, true);
                theData->mBlueCymbalMask = blue_cymbal_mask_arr->Int(1);

                Symbol mask("secondary_pedal_mask");
                DataArray* secondary_arr = type_cfg->FindArray(mask, true);
                theData->mSecondaryPedalMask = secondary_arr->Int(1);
                return true;
            }
        }
    }
    else return false;
}

Symbol JoypadControllerTypePadNum(int padNum){
    Symbol ret = none;
    if(padNum != -1 && !gJoypadDisabled[padNum] && !gJoypadData[padNum].mConnected){
        if(!gJoypadData[padNum].mControllerType.IsNull()){
            return gJoypadData[padNum].mControllerType;
        }
        else {
            MILO_ASSERT(gControllersCfg, 0x67B);
            for(int i = 1; i < gControllersCfg->Size(); i++){
                Symbol sym = gControllersCfg->Array(i)->Sym(0);
                if(JoypadIsControllerTypePadNum(padNum, sym)) return sym;
            }
            return unknown;
        }
    }
}

bool JoypadIsConnectedPadNum(int padNum){
    if(padNum == -1) return false;
    else return gJoypadData[padNum].mConnected;
}

bool JoypadIsCalbertGuitar(int padNum){
    JoypadType ty = gJoypadData[padNum].mType;
    if(ty == kJoypadXboxHxGuitarRb2 || ty == kJoypadXboxButtonGuitar || 
        ty == kJoypadPs3HxGuitarRb2 || ty == kJoypadPs3ButtonGuitar || 
        ty == kJoypadWiiHxGuitarRb2 || ty == kJoypadWiiButtonGuitar) 
        return true;
    else return false;
}

bool UserHasController(LocalUser* user){
    return GetUsersPadNum(user) != -1;
}

bool UserHasGHDrums(LocalUser* user){
    int padNum = GetUsersPadNum(user);
    if(padNum != -1){
        JoypadType ty = gJoypadData[padNum].mType;
        return (ty == kJoypadXboxRoDrums || ty == kJoypadPs3RoDrums);
    }
    else return false;
}

bool UserHas22FretGuitar(LocalUser*);

bool UserHasButtonGuitar(LocalUser*);

bool JoypadTypeHasLeftyFlip(Symbol type){
    DataArray* found = gControllersCfg->FindArray(type, true)->FindArray(lefty_flip, true);
    return found->Int(1) != 0;
}

int JoypadTypePadShiftButton(Symbol type){
    DataArray* found = gControllersCfg->FindArray(type, true)->FindArray(pad_shift_button, true);
    return found->Int(1);
}

int JoypadTypeCymbalShiftButton(Symbol type){
    DataArray* found = gControllersCfg->FindArray(type, true)->FindArray(cymbal_shift_button, true);
    return found->Int(1);
}

bool JoypadIsShiftButton(int padNum, JoypadButton btn){
    DataArray* type_array = gControllersCfg->FindArray(JoypadControllerTypePadNum(padNum), false);
    MILO_ASSERT(type_array, 0x702);
    if(btn == (JoypadButton)type_array->FindArray(cymbal_shift_button, true)->Int(1)){
        return true;
    }
    else if(btn == (JoypadButton)type_array->FindArray(pad_shift_button, true)->Int(1)){
        return true;
    }
    else if(btn == (JoypadButton)type_array->FindArray(guitar_shift_button, true)->Int(1)){
        return true;
    }
    else return false;
}

JoypadAction ButtonToAction(JoypadButton btn, Symbol sym){
    if(sym == none) return kAction_None;
    else {
        DataArray* arr = gButtonMeanings->FindArray(sym, false);
        if(arr){
            arr = arr->FindArray(btn, false);
            if(arr) return (JoypadAction)arr->Int(1);
        }
    }
}
