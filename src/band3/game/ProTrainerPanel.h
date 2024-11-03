#pragma once
#include "game/GemTrainerPanel.h"

class ProTrainerPanel : public GemTrainerPanel {
public:
    ProTrainerPanel(){}
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ProTrainerPanel(){}
    virtual void Enter();
    virtual void SetLessonComplete(int);
    virtual bool AllSectionsFinished() const;
    virtual void NewDifficulty(int, int);
    virtual float GetLessonCompleteSpeed(int) const;
    virtual void SetSongSectionComplete(BandProfile*, int, Difficulty, int) = 0;

    std::vector<float> mSpeedCompleted; // 0xd4
};