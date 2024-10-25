#pragma once
#include "obj/MsgSource.h"
#include "ui/UI.h"

class BandUI : public UIManager, public MsgSource {
public:
    BandUI();
    virtual DataNode Handle(DataArray*, bool);
    // fill out the rest...

    void WriteToVignetteOverlay(const char*);
};

extern BandUI TheBandUI;