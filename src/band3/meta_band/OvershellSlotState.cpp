#include "meta_band/OvershellSlotState.h"
#include "utl/Messages.h"

OvershellSlotState::OvershellSlotState(DataArray* da, OvershellSlot* slot) : mSlot(slot) {
    SetTypeDef(da);
    mStateID = (OvershellSlotStateID)da->Int(0);
}

OvershellSlotStateID OvershellSlotState::GetStateID() const { return mStateID; }

Symbol OvershellSlotState::GetView(){
    return HandleMsg(view_msg).Sym(0);
}

void OvershellSlotState::UpdateView(){
    HandleMsg(update_view_msg);
}

DataNode OvershellSlotState::HandleMsg(const Message& msg){
    DataNode ret((Hmx::Object*)0);
    bool b1 = false;
    DataArray* arr = 0;
    if(TypeDef()){
        arr = TypeDef()->FindArray(msg->Sym(1), false);
        if(arr) b1 = true;
    }
    if(b1){
        ret = arr->ExecuteScript(1, mSlot, msg, 2);
    }
    return ret;
}

OvershellSlotStateMgr::OvershellSlotStateMgr(){}

void OvershellSlotStateMgr::Init(DataArray* data, OvershellSlot* slot){
    for(int n = 0; n < data->Size(); n++){
        const DataNode& node = data->Node(n);
        if(node.Type() == kDataArray){
            mStates.push_back(new OvershellSlotState(data->Array(n), slot));
        }
        else {
            MILO_ASSERT(n == 0 && data->Type(n) == kDataSymbol, 0xC4);
        }
    }
}

OvershellSlotStateMgr::~OvershellSlotStateMgr(){
    DeleteAll(mStates);
}

OvershellSlotState* OvershellSlotStateMgr::GetSlotState(OvershellSlotStateID id){
    for(int i = 0; i < mStates.size(); i++){
        if(id == mStates[i]->mStateID) return mStates[i];
    }
    MILO_FAIL("OvershellSlotState %d does not exist", id);
    return 0;
}