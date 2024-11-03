#pragma once
#include "ui/UIPanel.h"

class TrainerPanel : public UIPanel {
public:
    TrainerPanel();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TrainerPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
};

        // 80b848dc 80  15  e6  b0    addr       TrainerPanel::HandlePlayerDeleted
        // 80b848e0 00  00  00  00    addr       00000000
        // 80b848e4 80  20  0b  70    addr       TrainerPanel::SetLessonComplete
        // 80b848e8 80  20  11  30    addr       TrainerPanel::AllSectionsFinished
        // 80b848ec 80  20  11  70    addr       TrainerPanel::ShouldStartEarly
        // 80b848f0 80  20  01  20    addr       TrainerPanel::IsSongSectionComplete
        // 80b848f4 80  20  12  20    addr       TrainerPanel::UpdateProgressMeter
        // 80b848f8 80  20  12  70    addr       TrainerPanel::NewDifficulty
