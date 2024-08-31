#ifndef TOUR_QUEST_H
#define TOUR_QUEST_H

#include "obj/Data.h"
#include "tour/TourCondition.h"
#include "tour/TourQuestGameRules.h"
#include "tour/TourReward.h"
#include "types.h"
#include "utl/Symbol.h"

class Quest {
    public:
    Quest(DataArray*);
    virtual ~Quest();
    virtual void Configure(DataArray*);

    Symbol GetSuccessSymbol() const;

    Symbol mName; Symbol GetName() const;
    Symbol mDisplayName; Symbol GetDisplayName() const;
    Symbol mDescription; Symbol GetDescription() const;
    Symbol mLongDescription; Symbol GetLongDescription() const;
    Symbol mIngameDesc;
    Symbol mIntroVignette; bool HasCustomIntro() const; Symbol GetCustomIntro() const;
    Symbol mOutroVignette; bool HasCustomOutro() const; Symbol GetCustomOutro() const;
    Symbol mSuccess;
    int mTier; int GetTier() const;
    Symbol mGroup; Symbol GetGroup() const;
    bool mIsSpecial;
    f32 mWeight; float GetWeight() const;
    bool mIsUGCAllowed; bool IsUGCAllowed() const;
    TourCondition mPrerequisites; const TourCondition* GetPrereqs() const;
    TourReward mSuccessReward; const TourReward* GetSuccessReward() const;
    TourReward mFailureReward; const TourReward* GetFailureReward() const;
    TourQuestGameRules mGameRules; const TourQuestGameRules* GetGameRules() const;
};

#endif // TOUR_QUEST_H
