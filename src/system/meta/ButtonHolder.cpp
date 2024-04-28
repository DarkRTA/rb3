#include "meta/ButtonHolder.h"
#include "obj/Data.h"

ProcessedButtonDownMsg::ProcessedButtonDownMsg(LocalUser* user, JoypadButton butt, JoypadAction act, int i, bool b)
    : Message(Type(), DataNode(user), DataNode(butt), DataNode(act), DataNode(i), DataNode(b)){

}

LocalUser* ProcessedButtonDownMsg::GetUser() const {
    return mData->Obj<LocalUser>(2);
}

ActionRec::ActionRec(JoypadAction act, float f, UserMgr* umgr) : mAction(act), mHoldTime(f), mPresses() {
    std::vector<LocalUser*> uservec;
    umgr->GetLocalUsers(uservec);

    for(int i = 0; i < uservec.size(); i++){
        PressRec prec;
        mPresses.push_back(prec);
        mPresses[i].a = 0;
        mPresses[i].iUser = 0;
        mPresses[i].c = 0;
        mPresses[i].d = 0;
        mPresses[i].e = 0;
    }
}

PressRec& ActionRec::GetPressRec(int padnum){
    for(int i = 0; i < mPresses.size(); i++){
        
    }
    MILO_FAIL("No PressRec exists for this padnum");
    return *mPresses.begin();
}

ButtonHolder::ButtonHolder(Hmx::Object* obj, UserMgr* umgr){
    mCallback = obj;
    MILO_ASSERT(mCallback, 0x40);

    if(umgr) mUserMgr = umgr;
    else mUserMgr = TheUserMgr;
}