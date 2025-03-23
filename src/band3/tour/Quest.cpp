#include "Quest.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "tour/TourCondition.h"
#include "tour/TourQuestGameRules.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

#include "decomp.h"

Quest::Quest(DataArray *da)
    : mName(""), mDisplayName(gNullStr), mDescription(gNullStr),
      mLongDescription(gNullStr), mIngameDesc(gNullStr), mIntroVignette(""),
      mOutroVignette(""), mSuccess(""), mTier(-1), mGroup(""), mIsSpecial(0), mWeight(1),
      mIsUGCAllowed(1) {
    Configure(da);
}

Quest::~Quest() {}

void Quest::Configure(DataArray *i_pConfig) {
    MILO_ASSERT(i_pConfig, 37);
    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(name_override, mDisplayName, false);
    i_pConfig->FindData(desc_override, mDescription, false);
    i_pConfig->FindData(ingamedesc_override, mIngameDesc, false);
    i_pConfig->FindData(longdesc_override, mLongDescription, false);
    i_pConfig->FindData(tier, mTier, false);
    i_pConfig->FindData(group, mGroup, true);
    i_pConfig->FindData(intro_vignette, mIntroVignette, false);
    i_pConfig->FindData(outro_vignette, mOutroVignette, false);
    i_pConfig->FindData(success_symbol, mSuccess, false);
    i_pConfig->FindData(is_special, mIsSpecial, false);
    i_pConfig->FindData(weight, mWeight, false);
    i_pConfig->FindData(allow_ugc, mIsUGCAllowed, false);
    mPrerequisites.Init(i_pConfig->FindArray(prereqs, false));
    mSuccessReward.Init(i_pConfig->FindArray(success_reward, false));
    mFailureReward.Init(i_pConfig->FindArray(failure_reward, false));
    mGameRules.Init(i_pConfig->FindArray(game_rules));
}

Symbol Quest::GetName() const { return mName; }

Symbol Quest::GetDisplayName() const {
    if (mDisplayName != gNullStr)
        return mDisplayName;
    else
        return mName;
}

Symbol Quest::GetLongDescription() const {
    if (mLongDescription != gNullStr)
        return mLongDescription;
    else
        return MakeString("%s_long_desc", mName);
}

Symbol Quest::GetDescription() const {
    if (mDescription != gNullStr)
        return mDescription;
    else
        return MakeString("%s_desc", mName);
}

DECOMP_FORCEACTIVE(Quest, "%s_ingame_desc") // it's so sad that GetIngameDesc died of
                                            // ligma (got deadstripped)

int Quest::GetTier() const { return mTier; }
float Quest::GetWeight() const { return mWeight; }
const TourCondition *Quest::GetPrereqs() const { return &mPrerequisites; }

static inline bool QuestEmptySymbolHack(const Symbol &s) { return s != ""; }

DECOMP_FORCEFUNC(Quest, Quest, HasCustomIntro())
DECOMP_FORCEFUNC(Quest, Quest, HasCustomOutro())

#pragma push
#pragma force_active on
inline bool Quest::HasCustomIntro() const { return QuestEmptySymbolHack(mIntroVignette); }

inline bool Quest::HasCustomOutro() const { return QuestEmptySymbolHack(mOutroVignette); }
#pragma pop

Symbol Quest::GetCustomIntro() const {
    MILO_ASSERT(HasCustomIntro(), 184);
    return mIntroVignette;
}

Symbol Quest::GetCustomOutro() const {
    MILO_ASSERT(HasCustomOutro(), 192);
    return mOutroVignette;
}

Symbol Quest::GetSuccessSymbol() const { return mSuccess; }
const TourQuestGameRules *Quest::GetGameRules() const { return &mGameRules; }
const TourReward *Quest::GetSuccessReward() const { return &mSuccessReward; }
const TourReward *Quest::GetFailureReward() const { return &mFailureReward; }
Symbol Quest::GetGroup() const { return mGroup; }
bool Quest::IsUGCAllowed() const { return mIsUGCAllowed; }
