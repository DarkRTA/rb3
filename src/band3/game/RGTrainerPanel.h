#pragma once
#include "ProTrainerPanel.h"
#include "beatmatch/RGGemMatcher.h"
#include "game/FretHand.h"
#include "game/RGTutor.h"

class RGTrainerPanel : public ProTrainerPanel {
public:
    RGTrainerPanel();
    OBJ_CLASSNAME(RGTrainerPanel);
    OBJ_SET_TYPE(RGTrainerPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~RGTrainerPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void StartSectionImpl();
    virtual bool IsSongSectionComplete(BandProfile*, int, Difficulty, int);
    virtual void NewDifficulty(int, int);
    virtual void HitNotify(int);
    virtual void MissNotify(int);
    virtual void Looped();
    virtual bool ShouldDrawTab() const;
    virtual void PostCopyGems();
    virtual void SetSongSectionComplete(BandProfile*, int, Difficulty, int);

    std::vector<int> unkdc; // 0xdc
    bool unke4;
    bool unke5;
    int unke8;
    float unkec;
    bool unkf0;
    RGGemMatcher unkf4;
    RGTutor unk1fc;
    int unk218;
    FretHand unk21c;
    bool unk24c;
};