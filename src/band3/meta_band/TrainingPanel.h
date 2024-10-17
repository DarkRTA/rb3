#pragma once
#include "LessonProvider.h"
#include "meta_band/TrainerProvider.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "game/BandUser.h"

class TrainingPanel : public UIPanel {
public:
    enum TrainingState {
        kTrainingState_Invalid = 0,
        kTrainingState_MainMenu = 1,
        kTrainingState_DrumLessons = 2,
        kTrainingState_ProDrumLessons = 3,
        kTrainingState_ProGuitarLessons = 4,
        kTrainingState_ProKeyboardLessons = 5,
        kTrainingState_COUNT = 6
    };

    TrainingPanel();
    OBJ_CLASSNAME(TrainingPanel);
    OBJ_SET_TYPE(TrainingPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TrainingPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Load();
    virtual void Unload();

    void SetTrainingState(TrainingState);
    bool IsCorrectController(Symbol, LocalBandUser*) const;
    void GotoTrainer(Symbol);
    TrainingState GetStateFromTrainer(Symbol);
    void UpdateLessonsProvider(Symbol);
    void RefreshLessonsList();

    DataNode OnMsg(const ButtonDownMsg&);
    DataNode LeaveState();

    static TrainingState sBackStates[kTrainingState_COUNT];

    TrainingState mTrainingState; // 0x38
    int unk3c;
    TrainerProvider* mTrainerProvider; // 0x40
    LessonProvider* mLessonProvider; // 0x44
};