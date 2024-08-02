#pragma once

#include "obj/ObjMacros.h"
#include "ui/UIPanel.h"
#include "utl/DeJitter.h"

class DeJitterPanel : public UIPanel {
public:
    DeJitterPanel();
    virtual ~DeJitterPanel();
    OBJ_CLASSNAME(DeJitterPanel)
    OBJ_SET_TYPE(DeJitterPanel)
    virtual void Enter();
    virtual void Poll();

    Timer unk_0x38;
    DeJitter unk_0x68;
    bool unk_0x84;

    NEW_OBJ(DeJitterPanel)
};