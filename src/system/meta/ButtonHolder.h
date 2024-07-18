#ifndef META_BUTTONHOLDER_H
#define META_BUTTONHOLDER_H
#include "obj/Msg.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include <vector>

BEGIN_MESSAGE(ProcessedButtonDownMsg, processed_button_down, LocalUser*, JoypadButton, JoypadAction, int, bool);
    MESSAGE_ARRAY_CTOR(ProcessedButtonDownMsg)
    LocalUser* GetUser() const;
    JoypadButton GetButton() const { return (JoypadButton)mData->Int(3); }
    JoypadAction GetAction() const { return (JoypadAction)mData->Int(4); }
    int GetPadNum() const { return mData->Int(5); }
    bool IsHeldDown() const { return mData->Int(6) != 0; }
END_MESSAGE;

struct PressRec {
    // PressRec(){}

    LocalUser* iUser;
    int unk4;
    int unk8;
    float unkc;
    int unk10;
};

// // RB2
// struct PressRec {
//     // total size: 0x18
//     int iUserNum; // offset 0x0, size 0x4
//     class User * iUser; // offset 0x4, size 0x4
//     enum JoypadButton iRawButton; // offset 0x8, size 0x4
//     enum JoypadAction iAction; // offset 0xC, size 0x4
//     float fPressTime; // offset 0x10, size 0x4
//     int iPadNum; // offset 0x14, size 0x4
// };

class ActionRec {
public:
    ActionRec(JoypadAction, float, UserMgr*);
    PressRec& GetPressRec(int);

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

#endif