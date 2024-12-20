#pragma once
#include "obj/Msg.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include <vector>

DECLARE_MESSAGE(ProcessedButtonDownMsg, "processed_button_down")
    ProcessedButtonDownMsg(LocalUser*, JoypadButton, JoypadAction, int, bool);
    LocalUser* GetUser() const;
    JoypadButton GetButton() const { return (JoypadButton)mData->Int(3); }
    JoypadAction GetAction() const { return (JoypadAction)mData->Int(4); }
    int GetPadNum() const { return mData->Int(5); }
    bool IsHeldDown() const { return mData->Int(6) != 0; }
END_MESSAGE;

struct PressRec {
    LocalUser* iUser; // 0x0
    JoypadButton iRawButton; // 0x4
    JoypadAction iAction; // 0x8
    float fPressTime; // 0xc
    int iPadNum; // 0x10
};

class ActionRec {
public:
    ActionRec(JoypadAction, float, UserMgr*);
    PressRec& GetPressRec(int);
    bool operator==(const JoypadAction& a){ return a == mAction; }

    JoypadAction mAction; // 0x0
    float mHoldTime; // 0x4
    std::vector<PressRec> mPresses; // 0x8
};

class ButtonHolder : public Hmx::Object {
public:
    ButtonHolder(Hmx::Object*, UserMgr*);
    virtual ~ButtonHolder(){}
    virtual DataNode Handle(DataArray*, bool);

    void Poll();
    void ClearHeldButtons();
    void SetHoldActions(std::vector<ActionRec>&);
    DataNode OnSetHoldActions(DataArray*);
    DataNode OnMsg(const ButtonDownMsg&);

    Hmx::Object* mCallback; // 0x1c
    UserMgr* mUserMgr; // 0x20
    std::vector<ActionRec> mActionRecs; // 0x24
};
