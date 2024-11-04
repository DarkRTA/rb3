#pragma once
#include "game/Defines.h"
#include "game/Player.h"
#include "game/TrainerProgressMeter.h"
#include "meta_band/BandProfile.h"
#include "midi/DataEvent.h"
#include "obj/Object.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

class TrainerChallenge : public Hmx::Object {
public:
    TrainerChallenge(){}
    virtual ~TrainerChallenge(){}
    OBJ_CLASSNAME(TrainerChallenge);
    OBJ_SET_TYPE(TrainerChallenge);

    void Enter();
    void Exit();
    bool Success();
    Symbol GetRestrictionToken();
};

class TrainerSection {
public:
    TrainerSection();
    int GetStartTick() const;
    void SetStartTick(int);
    int GetEndTick() const;
    void SetEndTick(int);
    Symbol GetName() const;
    void SetName(const Symbol&);
    void SetChallengeName(const Symbol&);
    void SetStartEarly(bool);
    bool SanityCheck();

    Symbol mName; // 0x0
    int mStartTick; // 0x4
    int mEndTick; // 0x8
    Symbol mChallengeName; // 0xc
    TrainerChallenge* mChallenge; // 0x10
    bool mStartEarly; // 0x14
};

class TrainerPanel : public UIPanel {
public:
    TrainerPanel();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TrainerPanel();
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual void HandlePlayerDeleted(Player*);
    virtual void StartSectionImpl() = 0;
    virtual void SetLessonComplete(int);
    virtual bool AllSectionsFinished() const;
    virtual bool ShouldStartEarly() const;
    virtual bool IsSongSectionComplete(BandProfile*, int, Difficulty, int);
    virtual void UpdateProgressMeter();
    virtual void NewDifficulty(int, int);

    void InitSections();
    void StartSection(int);
    void RestartSection();
    int GetCurrentStartTick() const;
    int GetCurrentEndTick() const;
    int GetLoopTicks(int) const;
    void ClearSections();
    void AddSection(const TrainerSection&);
    TrainerSection& GetSection(int);
    const TrainerSection& GetSection(int) const;
    int GetCurrSection() const;
    int GetNumSections() const;
    void SetCurrentProgressSection(int);
    int GetTick() const;
    int GetSectionTicks(int) const;
    int GetSectionLoopStart(int) const;
    int FixupTick(int) const;
    int GetSectionLoopEnd(int) const;
    void ResetChallenge();
    Symbol GetChallengeRestriction(int);
    void SetProgressMeterShowing(bool);
    void InternalInitSections(const DataEventList*);
    void OnSuccess(int);
    Symbol GetNameForSection(int) const;
    BandProfile* GetBandProfile() const;
    int ModSectionNum(int) const;
    void SetCurrSection(int);

    bool HasChallenge(int idx) const {
        return mSections[idx].mChallenge;
    }

    TrainerProgressMeter* mProgressMeter; // 0x38
    std::vector<TrainerSection> mSections; // 0x3c
    int mCurrSection; // 0x44
    bool mShowProgressMeter; // 0x48
    std::vector<int> unk4c; // 0x4c
};

extern TrainerPanel* TheTrainerPanel;