#pragma once
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"

class BandStoreUIPanel : public UIPanel {
public:
    BandStoreUIPanel() {}
    OBJ_CLASSNAME(BandStoreUIPanel);
    OBJ_SET_TYPE(BandStoreUIPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~BandStoreUIPanel() {}

    DataNode FilterButtonMsg(const ButtonDownMsg &);
    NEW_OBJ(BandStoreUIPanel);
    static void Init() { REGISTER_OBJ_FACTORY(BandStoreUIPanel); }
};