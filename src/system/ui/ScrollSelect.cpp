#include "ScrollSelect.h"
#include "obj/Object.h"
#include "os/User.h"
#include "ui/Utl.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

ScrollSelect::ScrollSelect() : mSelectToScroll(0) { Reset(); }

void ScrollSelect::Store() { mSelectedAux = SelectedAux(); }

void ScrollSelect::Reset() { mSelectedAux = -1; }

bool ScrollSelect::SelectScrollSelect(UIComponent *comp, LocalUser *user) {
    if (mSelectToScroll) {
        if (mSelectedAux == -1)
            Store();
        else
            Reset();
        SendScrollSelected(comp, user);
        return true;
    } else
        return false;
}

bool ScrollSelect::RevertScrollSelect(
    UIComponent *comp, LocalUser *user, Hmx::Object *obj
) {
    int oldAux = mSelectedAux;
    if (oldAux != -1) {
        int selAux = SelectedAux();
        bool somenum = oldAux != selAux;
        SetSelectedAux(oldAux);
        mSelectedAux = -1;
        DataNode node(kDataUnhandled, 0);
        if (somenum && obj) {
            node = obj->Handle(UIComponentScrollMsg(comp, user), false);
        }
        if (node.Type() == kDataUnhandled) {
            node = SendScrollSelected(comp, user);
        }
        if (somenum) {
            if (node.Type() == kDataUnhandled) {
                TheUI.Handle(UIComponentScrollMsg(comp, user), false);
            }
        }
        return true;
    } else
        return false;
}

bool ScrollSelect::CanScroll() const {
    bool ret = false;
    if (!mSelectToScroll || mSelectedAux != -1)
        ret = true;
    return ret;
}

UIComponent::State ScrollSelect::DrawState(UIComponent *comp) const {
    bool ret = false;
    if (!mSelectToScroll || mSelectedAux == -1)
        ret = true;
    if (ret)
        return comp->GetState();
    return UIComponent::kSelected;
}

bool ScrollSelect::CatchNavAction(JoypadAction act) const {
    bool ret = false;
    if (mSelectedAux != -1 && IsNavAction(act))
        ret = true;
    return ret;
}

#pragma push
#pragma pool_data off
DataNode ScrollSelect::SendScrollSelected(UIComponent *comp, LocalUser *user) {
    static UIComponentScrollSelectMsg scroll_select_msg(0, 0, 0);
    scroll_select_msg->Node(2) = comp;
    scroll_select_msg->Node(3) = user;
    scroll_select_msg->Node(4) = mSelectedAux != -1;
    return TheUI.Handle(scroll_select_msg, false);
}
#pragma pop

DataNode ScrollSelect::Handle(DataArray *_msg, bool _warn) {
    Symbol sym = _msg->Sym(1);
#ifdef MILO_DEBUG
    MessageTimer timer(
        (MessageTimer::Active()) ? dynamic_cast<Hmx::Object *>(this) : 0, sym
    );
#endif
    HANDLE_EXPR(is_scroll_selected, IsScrollSelected())
    HANDLE_ACTION(reset, Reset())
    if (_warn)
        MILO_WARN(
            "%s(%d): %s unhandled msg: %s",
            __FILE__,
            0x85,
            PathName(dynamic_cast<Hmx::Object *>(this)),
            sym
        );
    return DataNode(kDataUnhandled, 0);
}

BEGIN_PROPSYNCS(ScrollSelect)
    SYNC_PROP(select_to_scroll, mSelectToScroll)
END_PROPSYNCS
