#include "meta/ButtonHolder.h"
#include "obj/Data.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

ProcessedButtonDownMsg::ProcessedButtonDownMsg(LocalUser* user, JoypadButton butt, JoypadAction act, int i, bool b)
    : Message(Type(), DataNode(user), DataNode(butt), DataNode(act), DataNode(i), DataNode(b)){

}

LocalUser* ProcessedButtonDownMsg::GetUser() const {
    return mData->Obj<LocalUser>(2);
}

// fn_805098A0
ActionRec::ActionRec(JoypadAction act, float f, UserMgr* umgr) : mAction(act), mHoldTime(f), mPresses() {
    std::vector<LocalUser*> uservec;
    umgr->GetLocalUsers(uservec);
    for(int i = 0; i < uservec.size(); i++){
        mPresses.push_back(PressRec());
        PressRec& curRec = mPresses[i];
        curRec.iUser = uservec[i];
        mPresses[i].iRawButton = kPad_L2;
        mPresses[i].iAction = kAction_None;
        mPresses[i].fPressTime = 0;
        mPresses[i].iPadNum = 0;
    }
}

// fn_80509E7C
PressRec& ActionRec::GetPressRec(int padnum){
    for(int i = 0; i < mPresses.size(); i++){
        if(mPresses[i].iUser->GetPadNum() == padnum) return mPresses[i];
    }
    MILO_FAIL("No PressRec exists for this padnum");
    return mPresses[0];
}

// fn_80509F10
ButtonHolder::ButtonHolder(Hmx::Object* obj, UserMgr* umgr){
    mCallback = obj;
    MILO_ASSERT(mCallback, 0x40);

    if(umgr) mUserMgr = umgr;
    else mUserMgr = TheUserMgr;
}

DataNode ButtonHolder::OnSetHoldActions(DataArray* da){
    std::vector<ActionRec> recs;
    DataArray* arr = da->Array(2);
    for(int i = 0; i < arr->Size(); i++){
        DataArray* innerArr = arr->Array(i);
        float innerFloat = innerArr->Float(1);
        if(innerFloat > 0){
            recs.push_back(ActionRec((JoypadAction)innerArr->Int(0), innerFloat, mUserMgr));
        }
    }
    SetHoldActions(recs);
    return 1;
}

void ButtonHolder::SetHoldActions(std::vector<ActionRec>& recs){
    mActionRecs.clear();
    mActionRecs = recs;
}

void ButtonHolder::ClearHeldButtons(){
    std::vector<ActionRec> recs;
    for(int i = 0; i < mActionRecs.size(); i++){
        recs.push_back(ActionRec(mActionRecs[i].mAction, mActionRecs[i].mHoldTime, mUserMgr));
    }
    SetHoldActions(recs);
}

DataNode ButtonHolder::OnMsg(const ButtonDownMsg& msg){
    std::vector<ActionRec>::iterator it = std::find(mActionRecs.begin(), mActionRecs.end(), msg.GetAction());
    if(it != mActionRecs.end()){
        PressRec& pressRec = it->GetPressRec(msg.GetUser()->GetPadNum());
        pressRec.iRawButton = msg.GetButton();
        pressRec.iAction = msg.GetAction();
        pressRec.fPressTime = TheTaskMgr.UISeconds();
        pressRec.iPadNum = msg.GetPadNum();
        return 1;
    }
    else return DataNode(kDataUnhandled, 0);
}

// void OnMsg__12ButtonHolderFRC13ButtonDownMsg(undefined4 out,int this,undefined4 msg)

// {
//   undefined4 uVar1;
//   int iVar2;
//   int iVar3;
//   double dVar4;
//   undefined4 local_18 [2];
  
//   local_18[0] = GetAction__13ButtonDownMsgCFv(msg);
//   uVar1 = end__Q211stlpmtx_std89vector<>Fv(this + 0x24);
//   iVar2 = fn_8050AC60(*(undefined4 *)(this + 0x24),uVar1,local_18);
//   iVar3 = end__Q211stlpmtx_std89vector<>Fv(this + 0x24);
//   if (iVar2 == iVar3) {
//     __ct__8DataNodeF8DataTypei(out,0,0);
//   }
//   else {
//     iVar3 = GetUser__13ButtonDownMsgCFv(msg);
//     uVar1 = (**(code **)(*(int *)(iVar3 + 4) + 0x10))();
//     iVar2 = GetPressRec__9ActionRecFi(iVar2,uVar1);
//     uVar1 = GetButton__13ButtonDownMsgCFv(msg);
//     *(undefined4 *)(iVar2 + 4) = uVar1;
//     uVar1 = GetAction__13ButtonDownMsgCFv(msg);
//     *(undefined4 *)(iVar2 + 8) = uVar1;
//     dVar4 = (double)UISeconds__7TaskMgrCFv(TheTaskMgr);
//     *(float *)(iVar2 + 0xc) = (float)dVar4;
//     uVar1 = GetPadNum__13ButtonDownMsgCFv(msg);
//     *(undefined4 *)(iVar2 + 0x10) = uVar1;
//     __ct__8DataNodeFi(out,1);
//   }
//   return;
// }

void ButtonHolder::Poll(){

}

BEGIN_HANDLERS(ButtonHolder)
    HANDLE(set_hold_actions, OnSetHoldActions)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xE3)
END_HANDLERS