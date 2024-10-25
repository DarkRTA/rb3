#pragma once
#include "meta/DeJitterPanel.h"

class InterstitialPanel : public DeJitterPanel {
public:
    InterstitialPanel();
    OBJ_CLASSNAME(InterstitialPanel);
    OBJ_SET_TYPE(InterstitialPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~InterstitialPanel(){}
    virtual void Draw();
    virtual void Enter();    
    virtual bool Exiting() const;
    virtual void Load();
    virtual void Unload();

    void SetCamshotDone();
    
    bool unk85; // 0x85
    int unk88; // 0x88
    bool unk8c; // 0x8c
};