#pragma once
#include "utl/Symbol.h"
#include "obj/Object.h"
#include "os/Timer.h"
#include "os/JoypadMsgs.h"
#include "os/Keyboard.h"

class DataArray;
class LocalUser;

struct QuickJoyCheat {
    int unk0; // joypad button?
    DataArray* unk4; // a cheat script, in form of data array?
};

struct LongJoyCheat {
    LongJoyCheat() : unk8(0), unkc(0) {}
    std::vector<int> unk0;
    int unk8;
    DataArray* unkc;
};

struct KeyCheat {
    int unk0;
    bool unk4; // ctrl?
    bool unk5; // alt?
    DataArray* unk8;
};

struct CheatLog {
    bool unk0;
    int unk4;
    DataNode unk8;
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

    void AddQuickJoyCheat(const QuickJoyCheat& cheat, ShiftMode mode){
        mQuickJoyCheats[mode].push_back(cheat);
    }
    void AddLongJoyCheat(const LongJoyCheat& cheat){
        mLongJoyCheats.push_back(cheat);
    }
    void AddKeyCheat(const KeyCheat& cheat){
        mKeyCheats.push_back(cheat);
    }
    void RebuildKeyCheatsForMode();
    void Log(int, bool, DataArray*);
    void AppendLog(char*);

    std::vector<LongJoyCheat> mLongJoyCheats; // 0x1c
    std::vector<QuickJoyCheat> mQuickJoyCheats[2]; // 0x20
    std::vector<KeyCheat> mKeyCheats; // 0x34
    Symbol mSymMode; // 0x3c
    std::vector<QuickJoyCheat*> mJoyCheatPtrsMode[2]; // 0x40
    std::vector<KeyCheat*> mKeyCheatPtrsMode; // 0x50
    Timer mLastButtonTime; // 0x58
    bool mKeyCheatsEnabled; // 0x88
    std::list<CheatLog> mBuffer; // 0x8c
    int mMaxBuffer; // 0x94
};

extern CheatsManager* gCheatsManager;

void EnableKeyCheats(bool);
bool GetEnabledKeyCheats();
void CallQuickCheat(DataArray*, LocalUser*);
bool CheatsInitialized();
void SetCheatMode(Symbol);
Symbol GetCheatMode();
void AppendCheatsLog(char*);
void LogCheat(int, bool, DataArray*);