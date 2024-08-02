#include "DeJitterPanel.h"
#include "obj/Task.h"
#include "ui/UIPanel.h"

DeJitterPanel::DeJitterPanel() : unk_0x84(true) { }

DeJitterPanel::~DeJitterPanel() { }

void DeJitterPanel::Enter() {
    float f[2];
    unk_0x68.Reset();
    unk_0x84 = true;
    f[0] = TheTaskMgr.Seconds(TaskMgr::b);
    f[1] = TheTaskMgr.DeltaSeconds();
    TheTaskMgr.SetTimeAndDelta(kTaskSeconds, 0, 0);
    UIPanel::Enter();
    TheTaskMgr.SetTimeAndDelta(kTaskSeconds, f[0], f[1]);
}

void DeJitterPanel::Poll() {
    if (unk_0x84) {
        unk_0x38.Restart();
        float f;
        unk_0x68.Apply(0, f);
    }
    Timer* t = unk_0x84 ? &unk_0x38 : NULL;
    float f[2];
    f[0] = TheTaskMgr.Seconds(TaskMgr::b);
    f[1] = TheTaskMgr.DeltaSeconds();
    if (t != NULL) {

    }

    UIPanel::Poll();
    TheTaskMgr.SetTimeAndDelta(kTaskSeconds, f[0], f[1]);
    unk_0x84 = false;
}
