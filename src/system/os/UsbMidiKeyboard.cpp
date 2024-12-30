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

inline bool UsbMidiKeyboardExists(){ return true; }

UsbMidiKeyboard::UsbMidiKeyboard(){
    mPadNum = 0;
    mUsbMidiKeyboardExists = UsbMidiKeyboardExists();
    for(int i = 0; i < 4; i++){
        mSustain[i] = false;
        mStompPedal[i] = false;
        mModVal[i] = 0;
        mExpressionPedal[i] = 0;
        mConnectedAccessories[i] = 0;
        for(int j = 0; j < 128; j++){
            mKeyPressed[i][j] = false;
            mKeyVelocity[i][j] = 0;
        }
    }
}

UsbMidiKeyboard::~UsbMidiKeyboard(){
    CritSecTracker cst(StaticCriticalSection::Instance());
}

void UsbMidiKeyboard::Init(){
    MILO_ASSERT(TheKeyboard == NULL, 0x58);
    TheKeyboard = new UsbMidiKeyboard();
    TheDebug.AddExitCallback(UsbMidiKeyboard::Terminate);
    gUseMidiPort = SystemConfig(joypad)->FindInt(use_midi_mode);
    gForceDetectKeytar = false;
}

void UsbMidiKeyboard::Terminate(){
    MILO_ASSERT(TheKeyboard != NULL, 0x65);
    RELEASE(TheKeyboard);
}

void UsbMidiKeyboard::Poll(){
    if(!gUseMidiPort && TheKeyboard){
        for(int i = 0; i < 4; i++){
            JoypadType ty = JoypadGetPadData(i)->mType;
            if(ty == kJoypadXboxMidiBoxKeyboard || ty == kJoypadPs3MidiBoxKeyboard || ty == kJoypadWiiMidiBoxKeyboard ||
                ty == kJoypadXboxKeytar || ty == kJoypadPs3Keytar || ty == kJoypadWiiKeytar || gForceDetectKeytar){
                    // here, assign a pointer to padData's struct for pro keys data
                    ProKeysData* proData = &JoypadGetPadData(i)->mProKeysData;
                    // this loop sets keys as pressed or released
                    int ivar1 = 1;
                    for(int j = 0; j < 25; j++){
                        int u5 = proData->unk0[j];
                        if(u5 == TheKeyboard->GetKeyPressed(i, j)){
                            if(u5 != 0) ivar1++;
                        }
                        else {
                            if(u5 != 0){
                                int extVel = TheKeyboard->GetSlottedKeyVelocityFromExtended(ivar1++, proData->unk0);
                                TheKeyboard->SetKeyVelocity(i, j, extVel);
                                SendMessage(KeyboardKeyPressedMsg(j, TheKeyboard->GetKeyVelocity(i, j), i));
                            }
                            else {
                                TheKeyboard->SetKeyVelocity(i, j, 0);
                                SendMessage(KeyboardKeyReleasedMsg(j, i));
                            }
                            TheKeyboard->SetKeyPressed(i, j, u5);
                        }
                    }
                    bool sus = proData->mSustain;
                    if(sus != TheKeyboard->GetSustain(i)){
                        TheKeyboard->SetSustain(i, sus);
                        SendMessage(KeyboardSustainMsg(sus, i));
                    }
                    bool stomped = proData->mStompPedal;
                    if(stomped != TheKeyboard->GetStompPedal(i)){
                        TheKeyboard->SetStompPedal(i, stomped);
                        SendMessage(KeyboardStompBoxMsg(stomped, i));
                    }
                    int mod = proData->unkachar;
                    if(mod != TheKeyboard->GetModVal(i)){
                        TheKeyboard->SetModVal(i, mod);
                        SendMessage(KeyboardModMsg(mod, i));
                    }
                    int exp = proData->mExpressionPedal;
                    if(exp != TheKeyboard->GetExpressionPedal(i)){
                        TheKeyboard->SetExpressionPedal(i, exp);
                        SendMessage(KeyboardExpressionPedalMsg(exp, i));
                    }
                    int conn = proData->mConnectedAccessories;
                    if(conn != TheKeyboard->GetConnectedAccessory(i)){
                        TheKeyboard->SetConnectedAccessories(i, conn);
                        SendMessage(KeyboardConnectedAccessoriesMsg(conn, i));
                    }
                    int lowhand = proData->mLowHandPlacement;
                    if(lowhand != TheKeyboard->GetLowHandPlacement(i)){
                        TheKeyboard->SetLowHandPlacement(i, lowhand);
                        SendMessage(KeyboardLowHandPlacementMsg(lowhand, i));
                    }
                    int highhand = proData->unkbbool + (proData->unkcbool << 1) + (proData->unkdbool << 2) + (proData->unkemiddle << 3);
                    if(highhand != TheKeyboard->GetHighHandPlacement(i)){
                        TheKeyboard->SetHighHandPlacement(i, highhand);
                        SendMessage(KeyboardHighHandPlacementMsg(highhand, i));
                    }
                    int accelaxisval0 = proData->unkachar;
                    int accelaxisval1 = proData->unkbchar;
                    int accelaxisval2 = proData->unkcchar;
                    if(accelaxisval0 != TheKeyboard->GetAccelAxisVal(i, 0) ||
                        accelaxisval1 != TheKeyboard->GetAccelAxisVal(i, 1) ||
                        accelaxisval2 != TheKeyboard->GetAccelAxisVal(i, 2)){
                        TheKeyboard->SetAccelerometer(i, accelaxisval0, accelaxisval1, accelaxisval2);
                        SendMessage(KeysAccelerometerMsg(accelaxisval0, accelaxisval1, accelaxisval2, i));
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
