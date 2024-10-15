#include "AccomplishmentOneShot.h"

#include "AccomplishmentConditional.h"
#include "game/Performer.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"
#include "Campaign.h"
#include "ProfileMgr.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

AccomplishmentOneShot::AccomplishmentOneShot(DataArray* i_pConfig, int i) : AccomplishmentConditional(i_pConfig, i), mOneShotSong(gNullStr), mOneShotPlayerMin(0) {
    AccomplishmentOneShot::Configure(i_pConfig);
}

AccomplishmentOneShot::~AccomplishmentOneShot() {
}

void AccomplishmentOneShot::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x23);

    i_pConfig->FindData(oneshot_song, mOneShotSong, false);
    i_pConfig->FindData(oneshot_playermin, mOneShotPlayerMin, false);
}

AccomplishmentType AccomplishmentOneShot::GetType() const {
    return kAccomplishmentTypeOneShot;
}

bool AccomplishmentOneShot::AreOneShotConditionsMet(ScoreType score, Difficulty diff, Performer* i_pPerformer, Symbol s, int i) {
    MILO_ASSERT(i_pPerformer, 0x3c);
    Stats& stats = i_pPerformer->mStats;
    for(std::vector<AccomplishmentCondition>::iterator it = m_lConditions.begin(); it != m_lConditions.end(); ++it){
        Symbol sym = it->mCondition;
        int iii = it->mValue;
        if((mOneShotSong == gNullStr || mOneShotSong == s) && i >= mOneShotPlayerMin && diff >= it->mDifficulty){
            if(sym == stars){
                if(it->mScoreType == score && i_pPerformer->GetNumStars() >= iii) return true;
            }
            else if(sym == unison_percent){
                if(stats.GetUnisonPhrasePercent() >= iii) return true;
            }
            else if(sym == unison_phrases){
                if(stats.mUnisonPhraseCount >= iii) return true;
            }
            else if(sym == upstrum_percent){
                if(it->mScoreType == score){
                    int i4 = stats.mHitCount + stats.m0x08;
                    if(i4 > 0) i4 = (float)stats.m0x28 * 100.0f / (float)i4;
                    else i4 = 0;
                    if(i4 >= iii) return true;
                }
            }
            else if(sym == times_revived){
                if(stats.mTimesSaved >= iii) return true;
            }
            else if(sym == saves){
                if(stats.mPlayersSaved >= iii) return true;
            }
            else if(sym == awesomes){
                if((score - 3 <= 1U) && it->mScoreType == score && stats.mHitCount >= iii) return true;
            }
            else if(sym == double_awesomes){
                if(it->mScoreType == score && stats.mDoubleHarmonyHit >= iii) return true;
            }
            else if(sym == all_double_awesomes){
                if(it->mScoreType == score && stats.mDoubleHarmonyHit >= stats.mDoubleHarmonyPhraseCount) return true;
            }
            else if(sym == triple_awesomes){
                if(it->mScoreType == score && stats.mTripleHarmonyHit >= iii) return true;
            }
            else if(sym == all_triple_awesomes){
                if(it->mScoreType == score && stats.mTripleHarmonyHit >= stats.mTripleHarmonyPhraseCount) return true;
            }
            else if(sym == full_combo){
                if(it->mScoreType == score && stats.m0xb4) return true;
            }
            else {
                MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, sym);
                return false;
            }
        }
    }
    return false;
}

void AccomplishmentOneShot::InitializeTrackerDesc(TrackerDesc& param_1) const {
    Accomplishment::InitializeTrackerDesc(param_1);
    MILO_ASSERT(!m_lConditions.empty(), 0xe6);
    AccomplishmentCondition condition = m_lConditions[0];
    MILO_ASSERT(TheCampaign, 0xe9);
    LocalUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0xeb);
    Profile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pProfile, 0xee);

    if (condition.mCondition == upstrum_percent) {

    } else if (condition.mCondition == stars) {

    } else if (condition.mCondition == unison_phrases) {

    }
}

bool AccomplishmentOneShot::HasSpecificSongsToLaunch() const {
    return mOneShotSong != gNullStr;
}

