#include "meta_band/EventDialogPanel.h"
#include "meta_band/InputMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

EventDialogPanel::EventDialogPanel() {
    TheUIEventMgr->AddSink(this, EventDialogStartMsg::Type());
    TheUIEventMgr->AddSink(this, EventDialogDismissMsg::Type());
    TheInputMgr->AddSink(this, "input_limit_changed");
}

EventDialogPanel::~EventDialogPanel() { TheUIEventMgr->RemoveSink(this); }

void EventDialogPanel::Draw() {
    if (GetState() != kUp) {
        Enter();
    } else
        UIPanel::Draw();
}

DataNode EventDialogPanel::OnMsg(const EventDialogStartMsg &msg) {
    MILO_ASSERT(msg.EventType(), 0x31);
    SetTypeDef(msg.EventType());
    HandleType(msg.Arr3());
    mFocusName = gNullStr;
    return 1;
}

DataNode EventDialogPanel::OnMsg(const EventDialogDismissMsg &msg) {
    SetTypeDef(nullptr);
    if (GetState() != kDown) {
        Exit();
    }
    return 1;
}

DataNode EventDialogPanel::OnMsg(const UIComponentSelectDoneMsg &msg) {
    UIComponent *c = msg.GetComponent();
    if (!c)
        return DataNode(kDataUnhandled, 0);
    else if (c == DataDir()->Find<UIComponent>(c->Name(), false)) {
        return DataNode(kDataUnhandled, 0);
    } else
        return 1;
}

BEGIN_HANDLERS(EventDialogPanel)
    HANDLE_MESSAGE(EventDialogStartMsg)
    HANDLE_MESSAGE(EventDialogDismissMsg)
    HANDLE_MESSAGE(UIComponentSelectDoneMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x67)
END_HANDLERS