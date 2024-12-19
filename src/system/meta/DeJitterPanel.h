#pragma once
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

class DeJitterPanelTimer {
public:
    DeJitterPanelTimer(DeJitter& dj, Timer* t){
        secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
        delta_secs = TheTaskMgr.DeltaSeconds();
        float f2 = 0;
        float f18 = 0;
        float f1 = f2;
        // everything within here is currently wrong
        if(t){
            dj.Apply(t->SplitMs(), f18);
            f18 *= 0.001f;
            f2 = f18;
            f1 *= 0.001f;
        }
        TheTaskMgr.SetTimeAndDelta(kTaskSeconds, f1, f2);
    }
    ~DeJitterPanelTimer(){
        TheTaskMgr.SetTimeAndDelta(kTaskSeconds, secs, delta_secs);
    }

    float secs; // 0x0
    float delta_secs; // 0x4
};