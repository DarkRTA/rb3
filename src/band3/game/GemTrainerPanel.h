#pragma once
#include "beatmatch/GameGem.h"
#include "game/Metronome.h"
#include "game/TrainerGemTab.h"
#include "game/TrainerPanel.h"

class GemTrainerPanel : public TrainerPanel {
public:
    GemTrainerPanel();
    OBJ_CLASSNAME(GemTrainerPanel);
    OBJ_SET_TYPE(GemTrainerPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~GemTrainerPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void HandlePlayerDeleted(Player*);
    virtual void StartSectionImpl();
    virtual bool ShouldStartEarly() const;
    virtual void UpdateProgressMeter();
    virtual void NewDifficulty(int, int);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual float GetLessonCompleteSpeed(int) const;
    virtual void HitNotify(int);
    virtual void MissNotify(int);
    virtual void Looped();
    virtual bool ShouldDrawTab() const;
    virtual void PostCopyGems();

    std::vector<GameGem> unk54;
    int unk5c;
    int unk60;
    int unk64;
    int unk68;
    int unk6c;
    int unk70;
    int unk74;
    int unk78;
    int unk7c;
    int unk80;
    int unk84;
    std::vector<GameGem> unk88[4];
    bool unka8;
    bool unka9;
    int unkac;
    int unkb0;
    TrainerGemTab* unkb4;
    Metronome* unkb8;
    float unkbc;
    float unkc0;
    int unkc4;
    bool unkc8;
    bool unkc9;
    int unkcc;
    bool unkd0;
};