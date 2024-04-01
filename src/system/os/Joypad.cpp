#include "os/Joypad.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

namespace {
    JoypadData gJoypadData[4];
    DataArray* gControllersCfg;

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
    return FloatToBucket(val);
}

JoypadData* JoypadGetPadData(int pad_num){
    MILO_ASSERT(0 <= pad_num && pad_num < kNumJoypads, 0x5CC);
    return &gJoypadData[pad_num];
}

bool JoypadIsControllerTypePadNum(int padNum, Symbol controller_type){
    MILO_ASSERT(padNum != -1, 0x641);
    MILO_ASSERT(gControllersCfg, 0x644);
    DataArray* type_cfg = gControllersCfg->FindArray(controller_type, false);
    if(!type_cfg) return false;
    else {
        DataArray* detect_cfg = type_cfg->FindArray("detect", true);
        if(detect_cfg->Size() != 1){
            if(!IsJoypadDetectMatch(detect_cfg->Array(1), gJoypadData[padNum])){
                return false;
            }
        }
    }
}

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
