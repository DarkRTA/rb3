#pragma once
#include "ui/UIPanel.h"

class ParentalControlPanel : public UIPanel {
public:
    ParentalControlPanel();
    OBJ_CLASSNAME(ParentalControlPanel);
    OBJ_SET_TYPE(ParentalControlPanel);
    virtual ~ParentalControlPanel() {}
    virtual void Enter();
    virtual void Poll();

    int unk38;
    bool unk3c;
};