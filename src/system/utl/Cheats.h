#pragma once
#include "utl/Symbol.h"
#include "obj/Object.h"
#include "os/Timer.h"
#include "os/JoypadMsgs.h"
#include "os/Keyboard.h"

class DataArray;
class LocalUser;

struct QuickJoyCheat {
    int unk0;
    int unk4;
};

struct LongJoyCheat {

};

struct KeyCheat {

};

class CheatsManager : public Hmx::Object {
public:
    enum ShiftMode {
        kLeftShift = 0,
        kRightShift = 1
    };

    CheatsManager();
    virtual ~CheatsManager(){}
    virtual DataNode Handle(DataArray*, bool);

    void CallCheatScript(bool, DataArray*, LocalUser*, bool);
    bool OnMsg(const ButtonDownMsg&);
    
    DataNode OnMsg(const KeyboardKeyMsg&);

    std::vector<LongJoyCheat> mLongJoyCheats; // 0x1c
    std::vector<QuickJoyCheat> mQuickJoyCheats[2]; // 0x20
    std::vector<int> mKeyCheats; // 0x34
    Symbol mSymMode; // 0x3c
    std::vector<QuickJoyCheat*> mJoyCheatPtrsMode[2]; // 0x40
    std::vector<int> mKeyCheatPtrsMode; // 0x50
    Timer mLastButtonTime; // 0x58
    bool mKeyCheatsEnabled; // 0x88
    std::list<int> mBuffer; // 0x8c
    int mMaxBuffer; // 0x94
};

extern CheatsManager* gCheatsManager;

void EnableKeyCheats(bool);
bool GetEnabledKeyCheats();
void CallQuickCheat(DataArray*, LocalUser*);
bool CheatsInitialized();
Symbol GetCheatMode();
void AppendCheatsLog(char*);
void LogCheat(int, bool, DataArray*);