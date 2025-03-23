#include "os/Joypad.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "math/Utl.h"
#include "obj/Msg.h"
#include "obj/DataFunc.h"

namespace {
    static DataArray *gControllersCfg; // 0x0
    static DataArray *gButtonMeanings; // 0x4
    static unsigned int gPadsToKeepAlive; // 0x8
    static unsigned int gPadsToKeepAliveNext; // 0xc
    static int gKeepAliveCountdown; // 0x10
    static int gKeepaliveThresholdMs = -1; // 0x18
    static bool gExportMsgs = true;
    static bool gJoypadLibInitialized;
    static JoypadData gJoypadData[4];
    static unsigned int gHolmesPressed; // 0x288
    static bool gJoypadDisabled[4]; // 0x28c
    static MsgSource *gJoypadMsgSource; // 0x290

    static DataNode OnJoypadSetVibrate(DataArray *arr) {
        JoypadSetVibrate(arr->Int(1), arr->Int(2) != 0);
        return 1;
    }

    static DataNode OnJoypadVibrate(DataArray *arr) {
        return DataNode(JoypadVibrate(arr->Int(1)));
    }

    static DataNode OnJoypadControllerTypePadNum(DataArray *arr) {
        return DataNode(JoypadControllerTypePadNum(arr->Int(1)));
    }

    static DataNode OnJoypadIsConnectedPadNum(DataArray *arr) {
        return DataNode(JoypadIsConnectedPadNum(arr->Int(1)));
    }

    static DataNode OnJoypadIsButtonDownPadNum(DataArray *arr) {
        int pad = arr->Int(1);
        MILO_ASSERT_RANGE(pad, 0, kNumJoypads, 0x80);
        int ret = gJoypadData[pad].mButtons & 1 << arr->Int(2);
        return DataNode(ret != 0);
    }

    static DataNode OnJoypadIsCalbertGuitar(DataArray *arr) {
        return DataNode(JoypadIsCalbertGuitar(arr->Int(1)));
    }

#ifdef MILO_DEBUG
#pragma push
#pragma pool_data off
#endif
    bool IsJoypadDetectMatch(DataArray *detect_cfg, const JoypadData &data) {
        static Symbol type("type");
        static Symbol button("button");
        static Symbol stick("stick");
        static Symbol trigger("trigger");
        static Symbol X("X");
        static Symbol Y("Y");
        static Symbol OR("or");
        static Symbol AND("and");
        Symbol sym = detect_cfg->Sym(0);
        if (sym == type) {
            return detect_cfg->Int(1) == (int)data.mType;
        } else if (sym == button) {
            return data.IsButtonInMask(detect_cfg->Int(1));
        } else if (sym == stick) {
            int i4 = 0;
            Symbol axis_sym = detect_cfg->Sym(2);
            if (axis_sym == X) {
                i4 = 0;
            } else if (axis_sym == Y) {
                i4 = 1;
            } else
                MILO_FAIL("bad axis %s in controller detect array\n", axis_sym);
            int i3 = detect_cfg->Int(1);
            float f7 = detect_cfg->Float(3);
            return f7 == data.mSticks[i3][i4];
        } else if (sym == trigger) {
            return detect_cfg->Float(2) == data.mTriggers[detect_cfg->Int(1)];
        } else if (sym == OR) {
            for (int i = 1; i < detect_cfg->Size(); i++) {
                if (IsJoypadDetectMatch(detect_cfg->Array(i), data))
                    return true;
            }
            return false;
        } else if (sym == AND) {
            for (int i = 1; i < detect_cfg->Size(); i++) {
                if (!IsJoypadDetectMatch(detect_cfg->Array(i), data))
                    return false;
            }
            return true;
        } else {
            MILO_FAIL("Unknown keyword '%s' in joypad detect block", sym);
            return false;
        }
    }
#ifdef MILO_DEBUG
#pragma pop
#endif

    static DataNode DataJoypadReset(DataArray *arr) {
        JoypadReset();
        return 0;
    }

}

JoypadData::JoypadData()
    : mButtons(0), mUser(0), mConnected(false), mVibrateEnabled(true), unk66(false),
      unk67(false), unk68(false), mHasAnalogSticks(false), mTranslateSticks(false),
      mIgnoreButtonMask(0), mGreenCymbalMask(0), mYellowCymbalMask(0), mBlueCymbalMask(0),
      mSecondaryPedalMask(0), mCymbalMask(0), mIsDrum(false), mType(kJoypadNone),
      mControllerType(), mHasGreenCymbal(false), mHasYellowCymbal(false),
      mHasBlueCymbal(false), mHasSecondaryPedal(false) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mSticks[i][j] = 0;
        }
    }
    for (int i = 0; i < 2; i++) {
        mTriggers[i] = 0;
    }
}

#ifdef MILO_DEBUG
#pragma push
#pragma pool_data off
#endif
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
    if (axis == lx)
        return GetLX();
    else if (axis == ly)
        return GetLY();
    else if (axis == rx)
        return GetRX();
    else if (axis == ry)
        return GetRY();
    else if (axis == tl)
        return GetLT();
    else if (axis == tr)
        return GetRT();
    else if (axis == sx)
        return GetSX();
    else if (axis == sy)
        return GetSY();
    else if (axis == sz)
        return GetSZ();
    else
        MILO_FAIL("Bad axis %s in JoypadData::GetAxis()\n");
    return 0.0f;
}
#ifdef MILO_DEBUG
#pragma pop
#endif

int JoypadData::FloatToBucket(float f) const {
    if (f < 0.11f)
        return 0;
    if (f < 0.31f)
        return 6;
    if (f < 0.46f)
        return 5;
    if (f < 0.61f)
        return 4;
    if (f < 0.77f)
        return 3;
    if (f < 0.89f)
        return 2;
    return 1;
}

int JoypadData::GetVelocityBucket(Symbol axis) const {
    float ax = GetAxis(axis);
    if (ax < 0.0f)
        ax += 1.0f;
    return FloatToBucket(ax);
}

int JoypadData::GetPressureBucket(JoypadButton b) const {
    MILO_ASSERT(int(b) < kNumPressureButtons, 0x140);
    float val = mPressures[b];
    if (mType == kJoypadPs3RoDrums) {
        val = val * 255.0f;
        val = 1.0f - Clamp<float>(0.0f, 100.0f, val - 22.0f) / 100.0f;
    }
    return FloatToBucket(val);
}

int ButtonToVelocityBucket(JoypadData *data, JoypadButton btn) {
    switch (data->mType) {
    case kJoypadXboxDrumsRb2:
        switch (btn) {
        case kPad_Circle:
            return data->GetVelocityBucket(LX);
        case kPad_Tri:
            return data->GetVelocityBucket(LY);
        case kPad_Square:
            return data->GetVelocityBucket(RX);
        case kPad_X:
            return data->GetVelocityBucket(RY);
        default:
            return 0;
        }
        break;
    case kJoypadXboxDrums:
        switch (btn) {
        case kPad_Circle:
            return data->GetVelocityBucket(LY);
        case kPad_Tri:
            return data->GetVelocityBucket(RX);
        case kPad_Square:
            return data->GetVelocityBucket(RX);
        case kPad_X:
            return data->GetVelocityBucket(LY);
        default:
            return 0;
        }
        break;
    case kJoypadPs3HxDrums:
    case kJoypadPs3HxDrumsRb2:
    case kJoypadWiiHxDrumsRb2:
        switch (btn) {
        case kPad_Circle:
        case kPad_Tri:
        case kPad_Square:
        case kPad_X:
            return data->GetPressureBucket(btn);
        default:
            return 0;
        }
    default:
        return 0;
    }
}

void JoypadInitCommon(DataArray *joypad_config) {
    int i;
    gJoypadMsgSource = Hmx::Object::New<MsgSource>();
    float thresh;
    joypad_config->FindData("threshold", thresh, true);
    joypad_config->FindData("keepalive_ms", gKeepaliveThresholdMs, true);
    for (i = 0; i < 4; i++) {
        gJoypadData[i].mDistFromRest = thresh;
        gJoypadDisabled[i] = 0;
    }
    DataArray *ignores = joypad_config->FindArray("ignore");
    for (i = 1; i < ignores->Size(); i++) {
        int nodeInt = ignores->Int(i);
        if (nodeInt == 0 || nodeInt == 1 || nodeInt == 2 || nodeInt == 3) {
            gJoypadDisabled[nodeInt] = true;
        }
    }
    gControllersCfg = joypad_config->FindArray("controllers");
    gButtonMeanings = joypad_config->FindArray("button_meanings");
    DataRegisterFunc("joypad_reset", DataJoypadReset);
    DataRegisterFunc("joypad_vibrate", OnJoypadVibrate);
    DataRegisterFunc("joypad_set_vibrate", OnJoypadSetVibrate);
    DataRegisterFunc("joypad_controller_type_padnum", OnJoypadControllerTypePadNum);
    DataRegisterFunc("joypad_is_connected_padnum", OnJoypadIsConnectedPadNum);
    DataRegisterFunc("joypad_is_button_down", OnJoypadIsButtonDownPadNum);
    DataRegisterFunc("joypad_is_calbert_guitar", OnJoypadIsCalbertGuitar);
    gJoypadLibInitialized = true;
}

inline WaitInfo::WaitInfo(int pad) : mPadNum(pad), mButtons(gJoypadData[pad].mButtons) {}

unsigned int JoypadPollForButton(int pad) {
    if (!gJoypadLibInitialized)
        return 0;
    else {
        gExportMsgs = false;
        JoypadPoll();
        std::vector<WaitInfo> waitInfos;
        if (pad == -1) {
            for (int i = 0; i < 4; i++) {
                if (!gJoypadDisabled[i]) {
                    waitInfos.push_back(WaitInfo(i));
                }
            }
        } else {
            waitInfos.push_back(WaitInfo(pad));
        }
        std::vector<WaitInfo>::iterator it = waitInfos.begin();
        unsigned int retMask = 0;
        for (; it != waitInfos.end(); ++it) {
            retMask |= gJoypadData[it->mPadNum].mNewPressed;
        }
#ifdef MILO_DEBUG
        if (pad == -1) {
            retMask |= gHolmesPressed;
        }
#endif
        gExportMsgs = true;
        return retMask;
    }
}

void JoypadPollCommon() {
    if (!gJoypadLibInitialized) {
        MILO_WARN(" Can't call JoypadPoll before initialization...");
    }
    MILO_WARN("!(justDisconnected && justConnected)");
}

void JoypadKeepEverythingAlive() {
    for (int i = 0; i < 4; i++) {
        if (1 << i) {
            gJoypadData[i].unk98 = SystemMs();
        }
    }
}

void JoypadKeepAlive(int pad, bool alive) {
    if (pad == -1)
        return;
    if (alive) {
        int padmask = 1 << pad;
        gPadsToKeepAlive |= padmask;
        gPadsToKeepAliveNext |= padmask;
    } else {
        gPadsToKeepAliveNext &= ~(1 << pad);
    }
    gKeepAliveCountdown = 0;
}

inline void JoypadSendMsg(const Message &msg) {
    if (gExportMsgs) {
        gJoypadMsgSource->Handle(msg, false);
    }
}

JoypadData *JoypadGetPadData(int pad_num) {
    MILO_ASSERT(0 <= pad_num && pad_num < kNumJoypads, 0x5CC);
    return &gJoypadData[pad_num];
}

void JoypadSetVibrate(int pad, bool vibrate) {
    JoypadSetActuatorsImp(pad, 0, 0);
    JoypadGetPadData(pad)->mVibrateEnabled = vibrate;
}

inline bool JoypadVibrate(int pad) { return JoypadGetPadData(pad)->mVibrateEnabled; }

void JoypadSubscribe(Hmx::Object *obj) {
    if (gJoypadMsgSource)
        gJoypadMsgSource->AddSink(obj, Symbol(), Symbol(), MsgSource::kHandle);
}

void JoypadUnsubscribe(Hmx::Object *obj) {
    if (gJoypadMsgSource)
        gJoypadMsgSource->RemoveSink(obj, Symbol());
}

void JoypadPushThroughMsg(const Message &msg) { JoypadSendMsg(msg); }

void AssociateUserAndPad(LocalUser *iUser, int iPadNum) {
    MILO_ASSERT_RANGE(iPadNum, 0, kNumJoypads, 0x61C);
    gJoypadData[iPadNum].mUser = iUser;
}

void ResetAllUsersPads() {
    for (int i = 0; i < 4; i++)
        AssociateUserAndPad(0, i);
}

int GetUsersPadNum(LocalUser *user) {
    for (int i = 0; i < 4; i++) {
        if (!gJoypadDisabled[i] && gJoypadData[i].mUser == user)
            return i;
    }
    return -1;
}

LocalUser *JoypadGetUserFromPadNum(int iPadNum) {
    MILO_ASSERT_RANGE(iPadNum, 0, kNumJoypads, 0x633);
    return gJoypadData[iPadNum].mUser;
}

int JoypadGetUsersPadNum(LocalUser *user) { return GetUsersPadNum(user); }

bool JoypadIsControllerTypePadNum(int padNum, Symbol controller_type) {
    MILO_ASSERT(padNum != -1, 0x641);
    JoypadData *theData = &gJoypadData[padNum];
    MILO_ASSERT(gControllersCfg, 0x644);
    DataArray *type_cfg = gControllersCfg->FindArray(controller_type, false);
    if (!type_cfg)
        return false;
    DataArray *detect_cfg = type_cfg->FindArray("detect");
    if (detect_cfg->Size() == 1
        || IsJoypadDetectMatch(detect_cfg->Array(1), gJoypadData[padNum])) {
        theData->mControllerType = controller_type;
        theData->mHasAnalogSticks = type_cfg->FindInt("has_analog_sticks");
        theData->mTranslateSticks = type_cfg->FindInt("translate_sticks");
        theData->mIgnoreButtonMask = 0;
        DataArray *ignore_arr = type_cfg->FindArray("ignore_buttons", false);
        if (ignore_arr) {
            for (int i = 1; i < ignore_arr->Size(); i++) {
                theData->mIgnoreButtonMask |= (1 << ignore_arr->Int(i));
            }
        }
        theData->mIsDrum = type_cfg->FindInt("is_drum");
        theData->mCymbalMask = type_cfg->FindInt("cymbal_mask");
        theData->mGreenCymbalMask = type_cfg->FindInt("green_cymbal_mask");
        theData->mYellowCymbalMask = type_cfg->FindInt("yellow_cymbal_mask");
        theData->mBlueCymbalMask = type_cfg->FindInt("blue_cymbal_mask");
        theData->mSecondaryPedalMask = type_cfg->FindInt("secondary_pedal_mask");
        return true;
    }
    return false;
}

Symbol JoypadControllerTypePadNum(int padNum) {
    if (padNum == -1 || gJoypadDisabled[padNum] || !gJoypadData[padNum].mConnected)
        return none;
    JoypadData *theData = &gJoypadData[padNum];
    if (!theData->mControllerType.Null()) {
        return theData->mControllerType;
    } else {
        MILO_ASSERT(gControllersCfg, 0x67B);
        for (int i = 1; i < gControllersCfg->Size(); i++) {
            Symbol sym = gControllersCfg->Array(i)->Sym(0);
            if (JoypadIsControllerTypePadNum(padNum, sym))
                return sym;
        }
        return unknown;
    }
}

bool JoypadIsConnectedPadNum(int padNum) {
    if (padNum == -1)
        return false;
    else
        return gJoypadData[padNum].mConnected;
}

bool JoypadIsCalbertGuitar(int padNum) {
    JoypadType ty = gJoypadData[padNum].mType;
    if (ty == kJoypadXboxHxGuitarRb2 || ty == kJoypadXboxButtonGuitar
        || ty == kJoypadPs3HxGuitarRb2 || ty == kJoypadPs3ButtonGuitar
        || ty == kJoypadWiiHxGuitarRb2 || ty == kJoypadWiiButtonGuitar)
        return true;
    else
        return false;
}

bool UserHasController(LocalUser *user) { return GetUsersPadNum(user) != -1; }

bool UserHasGHDrums(LocalUser *user) {
    int padNum = GetUsersPadNum(user);
    if (padNum != -1) {
        JoypadType ty = gJoypadData[padNum].mType;
        return (ty == kJoypadXboxRoDrums || ty == kJoypadPs3RoDrums);
    } else
        return false;
}

bool UserHas22FretGuitar(LocalUser *user) {
    int padnum = GetUsersPadNum(user);
    if (padnum != -1) {
        bool ret = true;
        bool b1 = false;
        JoypadType jType = gJoypadData[padnum].mType;
        unsigned int u4 = jType - 31;
        // if jType >= 31 && jType <= 43 - the span of the realguitar22fret enums
        // kJoypadXboxRealGuitar22Fret = 31 = 0x1F = 00011111
        // kJoypadPs3RealGuitar22Fret = 37, = 0x25 = 00100101
        // kJoypadWiiRealGuitar22Fret = 43, = 0x2B = 00101011
        // 0x1041U = 0001000001000001
        // if your joypad type is a 22 fret guitar, one of the 1's will be in the
        // resulting AND operation
        if (u4 <= 12 && ((1 << u4) & 0x1041U))
            b1 = true;
        if (!b1) {
            b1 = false;
            if (DataVariable("auto_22_fret").Int(0)) {
                u4 = jType - 30;
                bool b2 = false;
                if (u4 <= 12 && ((1 << u4) & 0x1041U))
                    b2 = true;
                if (b2)
                    b1 = true;
            }
            if (!b1)
                ret = false;
        }
        return ret;
    } else
        return false;
}

bool UserHasButtonGuitar(LocalUser *user) {
    int padnum = GetUsersPadNum(user);
    if (padnum != -1) {
        return gJoypadData[padnum].mType - 0x1EU <= 0xC
            && ((1 << (gJoypadData[padnum].mType - 0x1EU)) & 0x1041U);
    } else
        return false;
}

bool JoypadTypeHasLeftyFlip(Symbol type) {
    DataArray *found = gControllersCfg->FindArray(type)->FindArray(lefty_flip);
    return found->Int(1) != 0;
}

int JoypadTypePadShiftButton(Symbol type) {
    DataArray *found = gControllersCfg->FindArray(type)->FindArray(pad_shift_button);
    return found->Int(1);
}

int JoypadTypeCymbalShiftButton(Symbol type) {
    DataArray *found = gControllersCfg->FindArray(type)->FindArray(cymbal_shift_button);
    return found->Int(1);
}

bool JoypadIsShiftButton(int padNum, JoypadButton btn) {
    DataArray *type_array =
        gControllersCfg->FindArray(JoypadControllerTypePadNum(padNum), false);
    MILO_ASSERT(type_array, 0x702);
    if (btn == (JoypadButton)type_array->FindArray(cymbal_shift_button)->Int(1)) {
        return true;
    } else if (btn == (JoypadButton)type_array->FindArray(pad_shift_button)->Int(1)) {
        return true;
    } else if (btn == (JoypadButton)type_array->FindArray(guitar_shift_button)->Int(1)) {
        return true;
    } else
        return false;
}

JoypadAction ButtonToAction(JoypadButton btn, Symbol sym) {
    JoypadAction ret = kAction_None;
    if (sym == none)
        return ret;
    else {
        DataArray *arr = gButtonMeanings->FindArray(sym, false);
        if (arr) {
            arr = arr->FindArray(btn, false);
            if (arr)
                ret = (JoypadAction)arr->Int(1);
        }
        return ret;
    }
}

const char *JoypadGetBreedString(int pad) {
    class String s1;
    return MakeString<JoypadType, class String>("%02x%s", gJoypadData[pad].mType, s1);
}
