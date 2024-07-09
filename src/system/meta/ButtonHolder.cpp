#include "meta/ButtonHolder.h"
#include "obj/Data.h"
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
        PressRec prec;
        mPresses.push_back(prec);
        mPresses[i].iUser = uservec[i];
        mPresses[i].unk4 = 0;
        mPresses[i].unk8 = 0;
        mPresses[i].unkc = 0;
        mPresses[i].unk10 = 0;
    }
}

// fn_80509E7C
PressRec& ActionRec::GetPressRec(int padnum){
    for(int i = 0; i < mPresses.size(); i++){
        if(mPresses[i].iUser->GetPadNum() == padnum) return mPresses[i];
    }
    MILO_FAIL("No PressRec exists for this padnum");
    return *mPresses.begin();
}

// fn_80509F10
ButtonHolder::ButtonHolder(Hmx::Object* obj, UserMgr* umgr){
    mCallback = obj;
    MILO_ASSERT(mCallback, 0x40);

    if(umgr) mUserMgr = umgr;
    else mUserMgr = TheUserMgr;
}

BEGIN_HANDLERS(ButtonHolder)
    HANDLE(set_hold_actions, OnSetHoldActions)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xE3)
END_HANDLERS