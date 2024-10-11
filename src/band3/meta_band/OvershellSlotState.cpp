#include "meta_band/OvershellSlotState.h"
#include "meta_band/OvershellSlot.h"
#include "utl/Messages.h"

OvershellSlotState::OvershellSlotState(DataArray* da, OvershellSlot* slot) : mSlot(slot) {
    SetTypeDef(da);
    mStateID = (OvershellSlotStateID)da->Int(0);
}

OvershellSlotStateID OvershellSlotState::GetStateID() const { return mStateID; }

Symbol OvershellSlotState::GetView(){
    return HandleMsg(view_msg).Sym();
}

void OvershellSlotState::UpdateView(){
    HandleMsg(update_view_msg);
}

bool OvershellSlotState::UsesRemoteStatusView(){
    if(GetRemoteStatus() != gNullStr) return true;
    else return !InSongSettingsFlow();
}

Symbol OvershellSlotState::GetRemoteStatus(){
    DataNode handled = HandleMsg(remote_status_msg);
    if(handled.Type() != kDataUnhandled) return handled.Sym();
    else return gNullStr;
}

bool OvershellSlotState::AllowsInputToShell(){
    DataNode handled = HandleMsg(allows_input_to_shell_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::PreventsOverride(){
    DataNode handled = HandleMsg(prevents_override_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::RequiresOnlineSession(){
    DataNode handled = HandleMsg(requires_online_session_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::RequiresRemoteUsers(){
    DataNode handled = HandleMsg(requires_remote_users_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::AllowsHiding(){
    DataNode handled = HandleMsg(allows_hiding_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::RetractedPosition(){
    DataNode handled = HandleMsg(retracted_position_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::ShowsExtendedMicArrows(){
    DataNode handled = HandleMsg(shows_extended_mic_arrows_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::InSongSettingsFlow(){
    DataNode handled = HandleMsg(song_settings_flow_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::IsPartUnresolved(){
    if(!InSongSettingsFlow()) return false;
    else {
        DataNode handled = HandleMsg(part_unresolved_msg);
        bool ret = false;
        if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
        return ret;
    }
}

bool OvershellSlotState::InRegisterOnlineFlow(){
    DataNode handled = HandleMsg(register_online_flow_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::InChooseCharFlow(){
    DataNode handled = HandleMsg(choose_char_flow_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::InCharEditFlow(){
    DataNode handled = HandleMsg(char_edit_flow_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::IsRemoveUserPrompt(){
    DataNode handled = HandleMsg(remove_user_prompt_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

bool OvershellSlotState::IsReadyToPlay(){
    DataNode handled = HandleMsg(ready_to_play_msg);
    bool ret = false;
    if(handled.Type() != kDataUnhandled && handled.Int() != 0) ret = true;
    return ret;
}

DataNode OvershellSlotState::HandleMsg(const Message& msg){
    DataNode ret(kDataUnhandled, 0);
    bool b1 = false;
    DataArray* arr;
    if(TypeDef()){
        arr = TypeDef()->FindArray(msg.Type(), false);
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
        if(data->Type(n) == kDataArray){
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
