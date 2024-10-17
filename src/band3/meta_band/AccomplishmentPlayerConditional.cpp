#include "meta_band/AccomplishmentPlayerConditional.h"
#include "AccomplishmentConditional.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

AccomplishmentPlayerConditional::AccomplishmentPlayerConditional(DataArray* arr, int i) : AccomplishmentConditional(arr, i), mLaunchPartDifficultySym("") {
    Configure(arr);
}

AccomplishmentPlayerConditional::~AccomplishmentPlayerConditional(){

}

void AccomplishmentPlayerConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x21);
    i_pConfig->FindData(launch_part_difficulty_sym, mLaunchPartDifficultySym, false);
    DataArray* pLaunchFilterArr = i_pConfig->FindArray(launch_filter, false);
    if(pLaunchFilterArr){
        for(int i = 1; i < pLaunchFilterArr->Size(); i++){
            DataArray* pEntry = pLaunchFilterArr->Array(i);
            MILO_ASSERT(pEntry, 0x2E);
            MILO_ASSERT(pEntry->Size() == 2, 0x2F);
            FilterType ty = (FilterType)pEntry->Int(0);
            Symbol sym = pEntry->Str(1);
            mLaunchFilter.AddFilter(ty, sym);
        }
    }
}

AccomplishmentType AccomplishmentPlayerConditional::GetType() const { return kAccomplishmentTypePlayerConditional; }
bool AccomplishmentPlayerConditional::IsRelevantForSong(Symbol) const { return true; }

bool AccomplishmentPlayerConditional::IsFulfilled(BandProfile* profile) const {
    for(std::vector<AccomplishmentCondition>::const_iterator it = m_lConditions.begin(); it != m_lConditions.end(); ++it){
        if(IsConditionMet(profile, *it)) return true;
    }
    return false;
}

bool AccomplishmentPlayerConditional::InqBestProgressValues(BandProfile* profile, int& i1, int& i2){
    float f1 = -1.0f;
    for(std::vector<AccomplishmentCondition>::iterator it = m_lConditions.begin(); it != m_lConditions.end(); ++it){
        int i64 = 0;
        int iGoal = 0;
        InqConditionProgress(profile, *it, i64, iGoal);
        MILO_ASSERT(iGoal > 0, 0x67);
        int div = (float)i64 / (float)iGoal;
        if(div > f1){
            i1 = i64;
            i2 = iGoal;
            f1 = div;
        }
    }
    return true;
}

bool AccomplishmentPlayerConditional::InqProgressValues(BandProfile* profile, int& i1, int& i2){
    InqBestProgressValues(profile, i1, i2);
    return true;
}

bool AccomplishmentPlayerConditional::InqConditionProgress(BandProfile* profile, const AccomplishmentCondition& cond, int& i1, int& i2) const {
    i2 = cond.mValue;
    Symbol sym = cond.mCondition;
    i1 = 0;
    if(profile){
        AccomplishmentProgress* prog = profile->GetAccomplishmentProgress();
        SongStatusMgr* mgr = profile->GetSongStatusMgr();
        if(sym == career_score){
            i1 = mgr->GetCachedTotalScore(cond.mScoreType);
        }
        else if(sym == career_score_capped){
            i1 = mgr->GetCachedTotalDiscScore(cond.mScoreType);
        }
        else if(sym == total_gems){
            i1 = prog->GetTotalGemsSmashed();
        }
        else if(sym == total_hopos){
            if(cond.mScoreType == kScoreGuitar) i1 = prog->GetTotalGuitarHopos();
            else if(cond.mScoreType == kScoreBass) i1 = prog->GetTotalBassHopos();
            else MILO_ASSERT(false, 0xC6);
        }
        else if(sym == total_upstrums){
            i1 = prog->GetTotalUpstrums();
        }
        else if(sym == total_times_revived){
            i1 = prog->GetTotalTimesRevived();
        }
        else if(sym == total_saves){
            i1 = prog->GetTotalSaves();
        }
        else if(sym == total_awesomes){
            i1 = prog->GetTotalAwesomes();
        }
        else if(sym == total_double_awesomes){
            i1 = prog->GetTotalDoubleAwesomes();
        }
        else if(sym == total_triple_awesomes){
            i1 = prog->GetTotalTripleAwesomes();
        }
        else if(sym == stars){
            i1 = prog->GetBestStarsAtMinDifficulty(cond.mScoreType, cond.mDifficulty);
        }
        else if(sym == best_solo){
            i1 = prog->GetBestSoloAtMinDifficulty(cond.mScoreType, cond.mDifficulty);
        }
        else if(sym == best_accuracy){
            i1 = prog->GetBestAccuracyAtMinDifficulty(cond.mScoreType, cond.mDifficulty);
        }
        else if(sym == best_streak){
            i1 = prog->GetBestStreak(cond.mScoreType);
        }
        else if(sym == total_overdrive_deploys){
            i1 = prog->GetTotalOverdriveDeploys(cond.mScoreType);
        }
        else if(sym == total_overdrive_time){
            i1 = prog->GetTotalOverdriveTime(cond.mScoreType);
        }
        else if(sym == total_overdrive_phrases){
            i1 = prog->GetTotalOverdrivePhrases(cond.mScoreType);
        }
        else if(sym == total_unison_phrases){
            i1 = prog->GetTotalUnisonPhrases(cond.mScoreType);
        }
        else if(sym == most_overdrive_deploys){
            i1 = prog->GetMostOverdriveDeploys(cond.mScoreType);
        }
        else if(sym == most_overdrive_time){
            i1 = prog->GetMostOverdriveTime(cond.mScoreType);
        }
        else if(sym == most_unison_phrases){
            i1 = prog->GetMostUnisonPhrases(cond.mScoreType);
        }
        else if(sym == total_bre_hits){
            i1 = prog->GetTotalBREsHit(cond.mScoreType);
        }
        else if(sym == total_songs_played){
            i1 = prog->GetTotalSongsPlayed();
        }
        else if(sym == tour_total_songs_played){
            i1 = prog->GetTourTotalSongsPlayed();
        }
        else if(sym == best_percussion_percent){
            i1 = prog->GetBestPercussionPercentAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == total_drumrolls){
            i1 = prog->GetTotalDrumRollCountAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == total_pro_drumrolls){
            i1 = prog->GetTotalProDrumRollCountAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == best_kick_percent){
            i1 = prog->GetBestKickPercentAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == best_pro_kick_percent){
            i1 = prog->GetBestProKickPercentAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == best_drumroll_percent){
            i1 = prog->GetBestDrumRollPercentAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == solo_button_percent){
            i1 = prog->GetBestSoloButtonPercentAtMinDifficulty(cond.mDifficulty);
        }
        else if(sym == best_hopos_percent){
            i1 = prog->GetBestHoposPercentAtMinDifficulty(cond.mScoreType, cond.mDifficulty);
        }
        else if(sym == career_fills){
            i1 = prog->GetCareerFills();
        }
        else if(sym == best_score){
            i1 = prog->GetBestScore(cond.mScoreType);
        }
        else if(sym == best_band_score){
            i1 = prog->GetBestBandScore();
        }
        else {
            MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, sym);
            return false;
        }
    }
    return true;
}

bool AccomplishmentPlayerConditional::IsConditionMet(BandProfile* profile, const AccomplishmentCondition& cond) const {
    int i4 = 0;
    int i8 = 0;
    InqConditionProgress(profile, cond, i4, i8);
    return i8 <= i4;
}

void AccomplishmentPlayerConditional::InitializeTrackerDesc(TrackerDesc& desc) const {
    Accomplishment::InitializeTrackerDesc(desc);
    MILO_ASSERT(!m_lConditions.empty(), 0x174);
    const AccomplishmentCondition& condition = m_lConditions[0];
    MILO_ASSERT(TheCampaign, 0x177);
    LocalBandUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0x179);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(pUser);
    MILO_ASSERT(pProfile, 0x17C);
    int i34 = 0;
    int i38 = 0;
    InqConditionProgress(pProfile, condition, i34, i38);
    Symbol key = condition.mCondition;
    if(key == best_streak){
        desc.mType = 0xF;
        desc.unk18.push_back(i38);
    }
    else if(key == most_overdrive_time){
        desc.mUser = 0;
        desc.mType = 9;
        desc.unk18.push_back(i38 * 1000.0f);
    }
    else if(key == most_overdrive_deploys){
        desc.mType = 8;
        desc.unk18.push_back(i38);
    }
    else if(key == total_overdrive_time){

    }
    else if(key == total_hopos){
        desc.mType = 5;
        desc.unk14 = i34;
        desc.unk18.push_back(i38);
    }
    else if(key == best_hopos_percent){
        desc.mType = 6;
        desc.unk18.push_back(i38);
    }
    else if(key == hopos_percent){
        desc.mType = 6;
        desc.unk18.push_back(i38 * 0.01f);
    }
    else if(key == best_accuracy){
        desc.mType = 1;
        desc.unk18.push_back(i38 * 0.01f);
    }
    else if(key == total_unison_phrases){
        desc.mType = 0x12;
        desc.unk14 = i34;
        desc.unk18.push_back(i38);
    }
    else if(key == solo_button_percent){
        desc.mType = 0xD;
        desc.unk18.push_back(i38);
    }
    else if(key == best_band_score){
        desc.mUser = 0;
        desc.mType = 0xC;
        desc.unk18.push_back(i38);
    }
    else if(key == best_score){
        desc.mType = 0xC;
        desc.unk18.push_back(i38);
    }
    else if(key == career_fills){
        desc.mType = 4;
        desc.unk14 = i34;
        desc.unk18.push_back(i38);
    }
    else if(key == stars){
        desc.unkc = 0;
    }
}