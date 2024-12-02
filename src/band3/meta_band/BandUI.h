#pragma once
#include "obj/Msg.h"
#include "ui/UI.h"
#include "ui/UIScreen.h"

class BandUI : public UIManager, public MsgSource {
public:
    BandUI();
    virtual DataNode Handle(DataArray*, bool);
    // fill out the rest...

    void GetCurrentScreenState(std::vector<UIScreen*>&);
    void WriteToVignetteOverlay(const char*);
};

extern BandUI TheBandUI;