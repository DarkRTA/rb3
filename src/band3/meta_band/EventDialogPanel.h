#pragma once
#include "obj/Data.h"
#include "ui/UIComponent.h"
#include "ui/UIPanel.h"
#include "obj/Msg.h"

DECLARE_MESSAGE(EventDialogStartMsg, "event_dialog_start");
EventDialogStartMsg(DataArray *a1, DataArray *a2)
    : Message(Type(), DataNode(a1, kDataArray), DataNode(a2, kDataArray)) {}
DataArray *EventType() const { return mData->Array(2); }
DataArray *Arr3() const { return mData->Array(3); }
END_MESSAGE

DECLARE_MESSAGE(EventDialogDismissMsg, "event_dialog_dismiss");
EventDialogDismissMsg() : Message(Type()) {}
END_MESSAGE

class EventDialogPanel : public UIPanel {
public:
    EventDialogPanel();
    OBJ_CLASSNAME(EventDialogPanel);
    OBJ_SET_TYPE(EventDialogPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~EventDialogPanel();
    virtual void Draw();

    DataNode OnMsg(const EventDialogStartMsg &);
    DataNode OnMsg(const EventDialogDismissMsg &);
    DataNode OnMsg(const UIComponentSelectDoneMsg &);
    NEW_OBJ(EventDialogPanel);
    static void Init() { REGISTER_OBJ_FACTORY(EventDialogPanel); }
};