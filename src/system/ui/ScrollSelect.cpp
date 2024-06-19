#include "ScrollSelect.h"
#include "obj/Object.h"
#include "os/User.h"
#include "ui/Utl.h"
#include "ui/UI.h"
#include "ui/UIMessages.h"
#include "utl/Symbols.h"

ScrollSelect::ScrollSelect() : unk_0x4(0) { Reset(); }

void ScrollSelect::Store() { unk_0x8 = SelectedAux(); }

void ScrollSelect::Reset() { unk_0x8 = -1; }

bool ScrollSelect::SelectScrollSelect(UIComponent* comp, LocalUser* user){
    if(unk_0x4){
        if(unk_0x8 == -1) Store();
        else Reset();
        SendScrollSelected(comp, user);
        return true;
    }
    else return false;
}

bool ScrollSelect::RevertScrollSelect(UIComponent* comp, LocalUser* user, Hmx::Object* obj){
    if(unk_0x8 != -1){
        int aux = SelectedAux();
        bool somenum = aux - unk_0x8 | unk_0x8 - aux;
        SetSelectedAux(unk_0x8);
        unk_0x8 = -1;
        DataNode node(kDataUnhandled, 0);
        if(somenum && obj){
            node = obj->Handle(UIComponentScrollMsg(comp, user), false);
        }
        if(node.Type() == kDataUnhandled){
            node = SendScrollSelected(comp, user);
        }
        if(somenum){
            if(node.Type() == kDataUnhandled){
                TheUI->Handle(UIComponentScrollMsg(comp, user), false);
            }
        }
        return true;
    }
    else return false;
}

bool ScrollSelect::CanScroll() const {
    bool ret = false;
    if(!unk_0x4 || unk_0x8 != -1) ret = true;
    return ret;
}

UIComponent::State ScrollSelect::DrawState(UIComponent* comp) const {
    bool ret = false;
    if(!unk_0x4 || unk_0x8 == -1) ret = true;
    if(ret) return (UIComponent::State)comp->mState;
    return UIComponent::kSelected;
}

bool ScrollSelect::CatchNavAction(JoypadAction act) const {
    bool ret = false;
    if(unk_0x8 != -1 && IsNavAction(act)) ret = true;
    return ret;
}

#pragma push
#pragma pool_data off
DataNode ScrollSelect::SendScrollSelected(UIComponent* comp, LocalUser* user){
    static UIComponentScrollSelectMsg scroll_select_msg(0, 0, 0);
    scroll_select_msg->Node(2) = DataNode(comp);
    scroll_select_msg->Node(3) = DataNode(user);
    scroll_select_msg->Node(4) = DataNode(unk_0x8 != -1);
    return TheUI->Handle(scroll_select_msg, false);
}
#pragma pop

DataNode ScrollSelect::Handle(DataArray* _msg, bool _warn){ 
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? dynamic_cast<Hmx::Object*>(this) : 0, sym);
    HANDLE_EXPR(is_scroll_selected, unk_0x8 != -1)
    HANDLE_ACTION(reset, Reset())
    if(_warn)
        TheDebugNotifier << MakeString("%s(%d): %s unhandled msg: %s", __FILE__, 0x85, PathName(dynamic_cast<Hmx::Object*>(this)), sym);
    return DataNode(kDataUnhandled, 0);
}

BEGIN_PROPSYNCS(ScrollSelect)
    SYNC_PROP(select_to_scroll, unk_0x4)
END_PROPSYNCS

