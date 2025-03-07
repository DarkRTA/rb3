#pragma once
#include "os/Timer.h"
#include "ui/UIPanel.h"

class GameTimePanel : public UIPanel {
public:
    GameTimePanel();
    OBJ_CLASSNAME(GameTimePanel);
    OBJ_SET_TYPE(GameTimePanel);
    virtual ~GameTimePanel() {}
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    NEW_OBJ(GameTimePanel);
    static void Init() { REGISTER_OBJ_FACTORY(GameTimePanel); }

    Timer mTimer; // 0x38
    float mTempo; // 0x68
    float mPeriod; // 0x6c
};