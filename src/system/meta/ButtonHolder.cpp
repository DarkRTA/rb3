#include "meta/ButtonHolder.h"
#include "obj/Data.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

ProcessedButtonDownMsg::ProcessedButtonDownMsg(
    LocalUser *user, JoypadButton butt, JoypadAction act, int i, bool b
)
    : Message(
          Type(), DataNode(user), DataNode(butt), DataNode(act), DataNode(i), DataNode(b)
      ) {}

LocalUser *ProcessedButtonDownMsg::GetUser() const { return mData->Obj<LocalUser>(2); }

// fn_805098A0
ActionRec::ActionRec(JoypadAction act, float f, UserMgr *umgr)
    : mAction(act), mHoldTime(f), mPresses() {
    std::vector<LocalUser *> uservec;
    umgr->GetLocalUsers(uservec);
    for (int i = 0; i < uservec.size(); i++) {
        mPresses.push_back(PressRec());
        PressRec &curRec = mPresses[i];
        curRec.iUser = uservec[i];
        mPresses[i].iRawButton = kPad_L2;
        mPresses[i].iAction = kAction_None;
        mPresses[i].fPressTime = 0;
        mPresses[i].iPadNum = 0;
    }
}

// fn_80509E7C
PressRec &ActionRec::GetPressRec(int padnum) {
    for (int i = 0; i < mPresses.size(); i++) {
        if (mPresses[i].iUser->GetPadNum() == padnum)
            return mPresses[i];
    }
    MILO_FAIL("No PressRec exists for this padnum");
    return mPresses[0];
}

// fn_80509F10
ButtonHolder::ButtonHolder(Hmx::Object *obj, UserMgr *umgr) {
    mCallback = obj;
    MILO_ASSERT(mCallback, 0x40);

    if (umgr)
        mUserMgr = umgr;
    else
        mUserMgr = TheUserMgr;
}

DataNode ButtonHolder::OnSetHoldActions(DataArray *da) {
    std::vector<ActionRec> recs;
    DataArray *arr = da->Array(2);
    for (int i = 0; i < arr->Size(); i++) {
        DataArray *innerArr = arr->Array(i);
        float innerFloat = innerArr->Float(1);
        if (innerFloat > 0) {
            recs.push_back(ActionRec((JoypadAction)innerArr->Int(0), innerFloat, mUserMgr)
            );
        }
    }
    SetHoldActions(recs);
    return 1;
}

void ButtonHolder::SetHoldActions(std::vector<ActionRec> &recs) {
    mActionRecs.clear();
    mActionRecs = recs;
}

void ButtonHolder::ClearHeldButtons() {
    std::vector<ActionRec> recs;
    for (int i = 0; i < mActionRecs.size(); i++) {
        recs.push_back(
            ActionRec(mActionRecs[i].mAction, mActionRecs[i].mHoldTime, mUserMgr)
        );
    }
    SetHoldActions(recs);
}

DataNode ButtonHolder::OnMsg(const ButtonDownMsg &msg) {
    std::vector<ActionRec>::iterator it =
        std::find(mActionRecs.begin(), mActionRecs.end(), msg.GetAction());
    if (it != mActionRecs.end()) {
        PressRec &pressRec = it->GetPressRec(msg.GetUser()->GetPadNum());
        pressRec.iRawButton = msg.GetButton();
        pressRec.iAction = msg.GetAction();
        pressRec.fPressTime = TheTaskMgr.UISeconds();
        pressRec.iPadNum = msg.GetPadNum();
        return 1;
    } else
        return DataNode(kDataUnhandled, 0);
}

void ButtonHolder::Poll() {
    std::vector<ActionRec> recs = mActionRecs;
    for (int i = 0; i < 4; i++) {
        if (JoypadIsConnectedPadNum(i)) {
            JoypadData *curPadData = JoypadGetPadData(i);
            for (std::vector<ActionRec>::iterator it = recs.begin();
                 curPadData && it != recs.end();
                 ++it) {
                static ProcessedButtonDownMsg msg(
                    nullptr, kPad_L2, kAction_None, 0, false
                );
                PressRec &pressRec = it->GetPressRec(i);
                if (curPadData->IsButtonInMask(pressRec.iRawButton)) {
                    if (pressRec.fPressTime > 0
                        && TheTaskMgr.UISeconds() - pressRec.fPressTime
                            >= it->mHoldTime) {
                        msg[0] = pressRec.iUser;
                        msg[1] = pressRec.iRawButton;
                        msg[2] = pressRec.iAction;
                        msg[3] = pressRec.iPadNum;
                        msg[4] = 1;
                        mCallback->Handle(msg, true);
                        pressRec.fPressTime = -TheTaskMgr.UISeconds();
                        goto out;
                    }
                } else {
                    if (pressRec.fPressTime > 0) {
                        msg[0] = pressRec.iUser;
                        msg[1] = pressRec.iRawButton;
                        msg[2] = pressRec.iAction;
                        msg[3] = pressRec.iPadNum;
                        msg[4] = 0;
                        mCallback->Handle(msg, true);
                        pressRec.fPressTime = 0;
                        goto out;
                    }
                    if (pressRec.fPressTime < 0)
                        pressRec.fPressTime = 0;
                }
            }
        }
    }
out:
    for (int i = 0; i < mActionRecs.size(); i++) {
        std::vector<ActionRec>::iterator it =
            std::find(recs.begin(), recs.end(), mActionRecs[i].mAction);
        if (it != recs.end()) {
            mActionRecs[i].mPresses = it->mPresses;
        }
    }
}

BEGIN_HANDLERS(ButtonHolder)
    HANDLE(set_hold_actions, OnSetHoldActions)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xE3)
END_HANDLERS