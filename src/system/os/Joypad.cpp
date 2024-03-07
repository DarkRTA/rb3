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

    static DataNode OnJoypadIsCalbertGuitar(DataArray* arr){
        return DataNode(JoypadIsCalbertGuitar(arr->Int(1)));
    }

    bool IsJoypadDetectMatch(DataArray* detect_cfg, const JoypadData& data){
        static Symbol type("type");
        static Symbol button("button");
        static Symbol stick("stick");
        static Symbol trigger("trigger");
        static Symbol X("X");
        static Symbol Y("Y");
        static Symbol OR("or");
        static Symbol AND("and");
        Symbol axis_sym = detect_cfg->Sym(0);
        if(axis_sym == type){
            return detect_cfg->Int(1) == (int)data.mType;
            // iVar2 = DataArray::Int(param_1,1);
            // uVar1 = countLeadingZeros(iVar2 - *(int *)(param_2 + 0x88));
            // uVar1 = uVar1 >> 5;
        }
        else if(axis_sym == button){
            return data.mButtons & 1 << detect_cfg->Int(1);
            // uVar3 = DataArray::Int(param_1,1);
            // uVar1 = fn_80182C98(param_2,uVar3);

            // side note:
            // bool fn_80182C98(uint *param_1,int param_2)

            // {
            // return (*param_1 & 1 << param_2) != 0;
            // }
        }
        else if(axis_sym == stick){
            // iVar4 = 0;
            // local_38 = DataArray::Sym(param_1,2);
            // Symbol::operator=(aSStack_30,(Symbol *)&local_38);
            // iVar2 = Symbol::operator==(aSStack_30,(Symbol *)X);
            // if (iVar2 == 0) {
                // iVar2 = Symbol::operator==(aSStack_30,(Symbol *)Y);
                // if (iVar2 != 0) {
                //     iVar4 = 1;
                // }
            // }
            // else {
                // iVar4 = 0;
            // }
            // iVar2 = DataArray::Int(param_1,1);
            // dVar6 = (double)*(float *)(param_2 + iVar2 * 8 + iVar4 * 4 + 0xc);
            // dVar5 = (double)DataArray::Float(param_1,3);
            // uVar1 = ((uint)(byte)((dVar5 == dVar6) << 1) << 0x1c) >> 0x1d;
        }
        else if(axis_sym == trigger){
            // iVar2 = DataArray::Int(param_1,1);
            // dVar6 = (double)*(float *)(param_2 + iVar2 * 4 + 0x1c);
            // dVar5 = (double)DataArray::Float(param_1,2);
            // uVar1 = ((uint)(byte)((dVar5 == dVar6) << 1) << 0x1c) >> 0x1d;
        }
        else if(axis_sym == OR){
            // for (iVar2 = 1; iVar4 = DataArray::Size(param_1), iVar2 < iVar4; iVar2 = iVar2 + 1) {
            //     uVar3 = DataArray::Array(param_1,iVar2);
            //     iVar4 = fn_80301190(uVar3,param_2);
            //     if (iVar4 != 0) {
            //         return 1;
            //     }
            // }
            // uVar1 = 0;
        }
        else if(axis_sym == AND){
            // for (iVar2 = 1; iVar4 = DataArray::Size(param_1), iVar2 < iVar4; iVar2 = iVar2 + 1) {
            //     uVar3 = DataArray::Array(param_1,iVar2);
            //     iVar4 = fn_80301190(uVar3,param_2);
            //     if (iVar4 == 0) {
            //       return 0;
            //     }
            // }
            // uVar1 = 1;
        }
        else {
            MILO_FAIL("Unknown keyword '%s' in joypad detect block", axis_sym);
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
