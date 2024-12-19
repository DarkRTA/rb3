#include "DeJitterPanel.h"
#include "obj/Task.h"
#include "ui/UIPanel.h"

DeJitterPanel::DeJitterPanel() : unk_0x84(true) { }

DeJitterPanel::~DeJitterPanel() { }

void DeJitterPanel::Enter() {
    float f[2];
    unk_0x68.Reset();
    unk_0x84 = true;
    DeJitterPanelTimer timer(unk_0x68, 0);
    UIPanel::Enter();
}

void DeJitterPanel::Poll() {
    if (unk_0x84) {
        unk_0x38.Restart();
        float f;
        unk_0x68.Apply(0, f);
    }
    {
        DeJitterPanelTimer timer(unk_0x68, unk_0x84 ? NULL : &unk_0x38);
        UIPanel::Poll();
    }
    unk_0x84 = false;
}
