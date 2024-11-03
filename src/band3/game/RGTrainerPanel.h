#pragma once
#include "ProTrainerPanel.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/RGGemMatcher.h"
#include "game/FretHand.h"
#include "game/RGTutor.h"

class RGTrainerPanel : public ProTrainerPanel {
public:
    class FingerStep {
    public:
        int mFinger; // 0x0
        int mFret; // 0x4
        int mLowString; // 0x8
        int mHighString; // 0xc
        bool unk10; // 0x10
    };

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

    void SetupIsBass();
    void SetLegendModeImpl(bool);
    void HandleChordLegend(bool);
    void StrumString(int);
    void SetFret(int, int);
    void FretButtonDown(int);
    void SetLegendMode(bool);
    bool GetLegendMode() const;
    void SetLegendGemID(int);
    void PickFretboardView(const GameGem&);
    void InitFretSteps(const GameGem&);
    void UpdateStepText(int, FingerStep&);
    Symbol RGStringToken(int, bool);

    std::vector<FingerStep> mFingerSteps; // 0xdc
    bool mLegendMode; // 0xe4
    bool unke5; // 0xe5
    int mLegendGemID; // 0xe8
    float unkec; // 0xec
    bool mLefty; // 0xf0
    RGGemMatcher mMatcher; // 0xf4
    RGTutor mTutor; // 0x1fc
    RndDir* mChordLegend; // 0x218
    FretHand mFretHand; // 0x21c
    bool mIsBass; // 0x24c
};

extern RGTrainerPanel* TheRGTrainerPanel;