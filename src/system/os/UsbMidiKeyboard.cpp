#include "os/UsbMidiKeyboard.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "os/Joypad.h"
#include "os/UsbMidiKeyboardMsgs.h"

UsbMidiKeyboard* TheKeyboard;
bool UsbMidiKeyboard::mUsbMidiKeyboardExists = false;

namespace {
    bool gUseMidiPort = false;
    bool gForceDetectKeytar = false;
}

StaticCriticalSection* StaticCriticalSection::Instance(){
    static StaticCriticalSection gCrit;
    return &gCrit;
}

StaticCriticalSection::~StaticCriticalSection(){

}

StaticCriticalSection::StaticCriticalSection(){

}

UsbMidiKeyboard::UsbMidiKeyboard(){
    mPadNum = 0;
    mUsbMidiKeyboardExists = true;
    for(int i = 0; i < 4; i++){
        mSustain[i] = false;
        mStompPedal[i] = false;
        mModVal[i] = 0;
        mExpressionPedal[i] = 0;
        mConnectedAccessories[i] = 0;
        for(int j = 0; j < 16; j++){
            int mult = j * 8;
            mKeyPressed[i][mult] = false;
            mKeyVelocity[i][mult] = 0;
            mKeyPressed[i][mult + 1] = false;
            mKeyVelocity[i][mult + 1] = 0;
            mKeyPressed[i][mult + 2] = false;
            mKeyVelocity[i][mult + 2] = 0;
            mKeyPressed[i][mult + 3] = false;
            mKeyVelocity[i][mult + 3] = 0;
            mKeyPressed[i][mult + 4] = false;
            mKeyVelocity[i][mult + 4] = 0;
            mKeyPressed[i][mult + 5] = false;
            mKeyVelocity[i][mult + 5] = 0;
            mKeyPressed[i][mult + 6] = false;
            mKeyVelocity[i][mult + 6] = 0;
            mKeyPressed[i][mult + 7] = false;
            mKeyVelocity[i][mult + 7] = 0;
        }
    }
}

UsbMidiKeyboard::~UsbMidiKeyboard(){
    CritSecTracker cst(StaticCriticalSection::Instance());
}

void UsbMidiKeyboard::Init(){
    MILO_ASSERT(TheKeyboard == NULL, 0x58);
    TheKeyboard = new UsbMidiKeyboard();
    DataArray* joypad_cfg = SystemConfig(joypad);
    DataArray* midi_mode = joypad_cfg->FindArray(use_midi_mode, true);
    int usemidi = midi_mode->Int(1);
    gForceDetectKeytar = false;
    gUseMidiPort = usemidi != 0;
}

void UsbMidiKeyboard::Terminate(){
    MILO_ASSERT(TheKeyboard != NULL, 0x65);
    delete TheKeyboard;
    TheKeyboard = 0;   
}

void UsbMidiKeyboard::Poll(){
    if(!gUseMidiPort && TheKeyboard){
        for(int i = 0; i < 4; i++){
            JoypadData* thePadData = JoypadGetPadData(i);
            JoypadType ty = thePadData->mType;
            if(ty == kJoypadXboxMidiBoxKeyboard || ty == kJoypadPs3MidiBoxKeyboard || ty == kJoypadWiiMidiBoxKeyboard ||
                ty == kJoypadXboxKeytar || ty == kJoypadPs3Keytar || ty == kJoypadWiiKeytar || gForceDetectKeytar){
                    JoypadData* padData = JoypadGetPadData(i);
                    // here, assign a pointer to padData's struct for pro keys data
                    ProKeysData* proData = &padData->mProData.keysData;
                    // this loop sets keys as pressed or released
                    for(int j = 0; j < 25; j++){

                    }
                    bool sus = proData->mSustain;
                    if(sus != TheKeyboard->mSustain[i]){
                        TheKeyboard->SetSustain(i, sus);
                        JoypadPushThroughMsg(KeyboardSustainMsg(sus, i));
                    }
                    bool stomped = proData->mStompPedal;
                    if(stomped != TheKeyboard->mStompPedal[i]){
                        TheKeyboard->SetStompPedal(i, stomped);
                        JoypadPushThroughMsg(KeyboardStompBoxMsg(stomped, i));
                    }
                    int mod = proData->unkachar;
                    if(mod != TheKeyboard->mModVal[i]){
                        TheKeyboard->SetModVal(i, mod);
                        JoypadPushThroughMsg(KeyboardModMsg(mod, i));
                    }
                    int exp = proData->mExpressionPedal;
                    if(exp != TheKeyboard->mExpressionPedal[i]){
                        TheKeyboard->SetExpressionPedal(i, exp);
                        JoypadPushThroughMsg(KeyboardExpressionPedalMsg(exp, i));
                    }
                    int conn = proData->mConnectedAccessories;
                    if(conn != TheKeyboard->mConnectedAccessories[i]){
                        TheKeyboard->SetConnectedAccessories(i, conn);
                        JoypadPushThroughMsg(KeyboardConnectedAccessoriesMsg(conn, i));
                    }
                    int lowhand = proData->mLowHandPlacement;
                    if(lowhand != TheKeyboard->mLowHandPlacement[i]){
                        TheKeyboard->SetLowHandPlacement(i, lowhand);
                        JoypadPushThroughMsg(KeyboardLowHandPlacementMsg(lowhand, i));
                    }
                    // like in the case of pro guitar's poll, I think this is a bunch of bits concatenated together
                    int highhand = proData->unkebool + proData->unkdbool + proData->unkbbool + proData->unkcbool;
                    if(highhand != TheKeyboard->mHighHandPlacement[i]){
                        TheKeyboard->SetHighHandPlacement(i, highhand);
                        JoypadPushThroughMsg(KeyboardHighHandPlacementMsg(highhand, i));
                    }
                    int accelaxisval0 = proData->unkachar;
                    int accelaxisval1 = proData->unkbchar;
                    int accelaxisval2 = proData->unkcchar;
                    if(accelaxisval0 != TheKeyboard->GetAccelAxisVal(i, 0) ||
                        accelaxisval1 != TheKeyboard->GetAccelAxisVal(i, 1) ||
                        accelaxisval2 != TheKeyboard->GetAccelAxisVal(i, 2)){
                        TheKeyboard->SetAccelerometer(i, accelaxisval0, accelaxisval1, accelaxisval2);
                        JoypadPushThroughMsg(KeysAccelerometerMsg(accelaxisval0, accelaxisval1, accelaxisval2, i));
                    }
                }
        }
    }
}

int UsbMidiKeyboard::GetSlottedKeyVelocityFromExtended(int i, unsigned char* uc){
    if(gUseMidiPort) return 0;
    if(i - 1U <= 4){
        switch(i){
            case 1: return uc[3] & 0x7F;
            case 2: return uc[4] & 0x7F;
            case 3: return uc[5] & 0x7F;
            case 4: return uc[6] & 0x7F;
            case 5: return uc[7] & 0x7F;
        }
    }
    return 0;
}

int UsbMidiKeyboard::GetAccelAxisVal(int pad, int axis){
    if(0 <= axis && (unsigned int)axis < 4){
        return mAccelerometer[pad][axis];
    }
    return 0;
}

bool UsbMidiKeyboard::GetKeyPressed(int pad, int key){
    if((unsigned int)key <= 0x7F){
        return mKeyPressed[pad][key];
    }
    return 0;
}

int UsbMidiKeyboard::GetKeyVelocity(int pad, int vel){
    if((unsigned int)vel <= 0x7F){
        return mKeyVelocity[pad][vel];
    }
    return 0;
}

void UsbMidiKeyboard::SetAccelerometer(int pad, int a1, int a2, int a3){
    mAccelerometer[pad][0] = a1;
    mAccelerometer[pad][1] = a2;
    mAccelerometer[pad][2] = a3;
}

void UsbMidiKeyboard::SetSustain(int pad, bool sus){
    mSustain[pad] = sus;
}

void UsbMidiKeyboard::SetStompPedal(int pad, bool stomp){
    mStompPedal[pad] = stomp;
}

void UsbMidiKeyboard::SetModVal(int pad, int mod){
    mModVal[pad] = mod;
}

void UsbMidiKeyboard::SetExpressionPedal(int pad, int exp){
    mExpressionPedal[pad] = exp;
}

void UsbMidiKeyboard::SetConnectedAccessories(int pad, int conn){
    mConnectedAccessories[pad] = conn;
}

void UsbMidiKeyboard::SetLowHandPlacement(int pad, int lh){
    mLowHandPlacement[pad] = lh;
}

void UsbMidiKeyboard::SetHighHandPlacement(int pad, int hh){
    mHighHandPlacement[pad] = hh;
}

void UsbMidiKeyboard::SetKeyPressed(int pad, int key, bool pressed){
    if(0x7F < (unsigned int)key) return;
    mKeyPressed[pad][key] = pressed;
}

void UsbMidiKeyboard::SetKeyVelocity(int pad, int key, int vel){
    if(0x7F < (unsigned int)key) return;
    mKeyVelocity[pad][key] = vel;
}
