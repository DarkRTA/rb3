#include "AccomplishmentSongConditional.h"
#include "AccomplishmentConditional.h"
#include "SongStatusMgr.h"
#include "game/Defines.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AppLabel.h"
#include "meta_band/BandSongMgr.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

AccomplishmentSongConditional::AccomplishmentSongConditional(DataArray* i_pConfig, int index) : AccomplishmentConditional(i_pConfig, index) {

}

AccomplishmentSongConditional::~AccomplishmentSongConditional() {

}

bool AccomplishmentSongConditional::CheckStarsCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    int id = TheSongMgr->GetSongIDFromShortName(s, true);
    return cond.mValue <= mgr->GetBestStars(id, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckScoreCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    int id = TheSongMgr->GetSongIDFromShortName(s, true);
    return cond.mValue <= mgr->GetScore(id, cond.mScoreType);
}

bool AccomplishmentSongConditional::CheckAccuracyCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    int id = TheSongMgr->GetSongIDFromShortName(s, true);
    return cond.mValue <= mgr->GetBestAccuracy(id, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckStreakCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    int id = TheSongMgr->GetSongIDFromShortName(s, true);
    return cond.mValue <= mgr->GetBestStreak(id, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckHoposPercentCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(cond.mScoreType == kScoreVocals || cond.mScoreType == kScoreHarmony){
        MILO_WARN("hopos percent condition can not be used with vocals or harmony!");
        return false;
    }
    else {
        int id = TheSongMgr->GetSongIDFromShortName(s, true);
        return cond.mValue <= mgr->GetBestHOPOPercent(id, cond.mScoreType, cond.mDifficulty);
    }
}

bool AccomplishmentSongConditional::CheckSoloPercentCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(cond.mScoreType == kScoreVocals || cond.mScoreType == kScoreHarmony){
        MILO_WARN("solo percent condition can not be used with vocals or harmony!");
        return false;
    }
    else {
        int id = TheSongMgr->GetSongIDFromShortName(s, true);
        return cond.mValue <= mgr->GetBestSoloPercent(id, cond.mScoreType, cond.mDifficulty);
    }
}

bool AccomplishmentSongConditional::CheckAwesomesCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(cond.mScoreType != kScoreVocals && cond.mScoreType != kScoreHarmony){
        MILO_WARN("awesome condition can only be used with vocals or harmony!");
        return false;
    }
    else {
        int id = TheSongMgr->GetSongIDFromShortName(s, true);
        return cond.mValue <= mgr->GetBestAwesomes(id, cond.mScoreType, cond.mDifficulty);
    }
}

bool AccomplishmentSongConditional::CheckDoubleAwesomesCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(cond.mScoreType != kScoreVocals && cond.mScoreType != kScoreHarmony){
        MILO_WARN("double_awesome condition can only be used with vocals or harmony!");
        return false;
    }
    else {
        int id = TheSongMgr->GetSongIDFromShortName(s, true);
        return cond.mValue <= mgr->GetBestDoubleAwesomes(id, cond.mScoreType, cond.mDifficulty);
    }
}

bool AccomplishmentSongConditional::CheckTripleAwesomesCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(cond.mScoreType != kScoreVocals && cond.mScoreType != kScoreHarmony){
        MILO_WARN("triple awesome condition can only be used with vocals or harmony!");
        return false;
    }
    else {
        int id = TheSongMgr->GetSongIDFromShortName(s, true);
        return cond.mValue <= mgr->GetBestTripleAwesomes(id, cond.mScoreType, cond.mDifficulty);
    }
}

bool AccomplishmentSongConditional::CheckHitBRECondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    return cond.mValue <= mgr->GetBestSongStatusFlag(s, kSongStatusFlag_HitBRE, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckAllDoubleAwesomesCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    return cond.mValue <= mgr->GetBestSongStatusFlag(s, kSongStatusFlag_AllDoubleAwesomes, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckAllTripleAwesomesCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    return cond.mValue <= mgr->GetBestSongStatusFlag(s, kSongStatusFlag_AllTripleAwesomes, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckPerfectDrumRollsCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    return cond.mValue <= mgr->GetBestSongStatusFlag(s, kSongStatusFlag_PerfectDrumRolls, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckFullComboCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    return cond.mValue <= mgr->GetBestSongStatusFlag(s, kSongStatusFlag_FullCombo, cond.mScoreType, cond.mDifficulty);
}

bool AccomplishmentSongConditional::CheckConditionsForSong(SongStatusMgr* mgr, Symbol s) const {
    if(!TheSongMgr->HasSong(s, false)) return false;
    else {
        for(std::vector<AccomplishmentCondition>::const_iterator it = m_lConditions.begin(); it != m_lConditions.end(); ++it){
            Symbol key = it->mCondition;
            if(key == stars){
                if(CheckStarsCondition(mgr, s, *it)) return true;
            }
            else if(key == score){
                if(CheckScoreCondition(mgr, s, *it)) return true;
            }
            else if(key == accuracy){
                if(CheckAccuracyCondition(mgr, s, *it)) return true;
            }
            else if(key == streak){
                if(CheckStreakCondition(mgr, s, *it)) return true;
            }
            else if(key == hopos_percent){
                if(CheckHoposPercentCondition(mgr, s, *it)) return true;
            }
            else if(key == solo_percent){
                if(CheckSoloPercentCondition(mgr, s, *it)) return true;
            }
            else if(key == awesomes){
                if(CheckAwesomesCondition(mgr, s, *it)) return true;
            }
            else if(key == double_awesomes){
                if(CheckDoubleAwesomesCondition(mgr, s, *it)) return true;
            }
            else if(key == all_double_awesomes){
                if(CheckAllDoubleAwesomesCondition(mgr, s, *it)) return true;
            }
            else if(key == triple_awesomes){
                if(CheckTripleAwesomesCondition(mgr, s, *it)) return true;
            }
            else if(key == all_triple_awesomes){
                if(CheckAllTripleAwesomesCondition(mgr, s, *it)) return true;
            }
            else if(key == hit_bre){
                if(CheckHitBRECondition(mgr, s, *it)) return true;
            }
            else if(key == perfect_drum_rolls){
                if(CheckPerfectDrumRollsCondition(mgr, s, *it)) return true;
            }
            else if(key == full_combo){
                if(CheckFullComboCondition(mgr, s, *it)) return true;
            }
            else {
                MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, key);
                return false;
            }
        }
    }
    return false;
}

void AccomplishmentSongConditional::UpdateIncrementalEntryName(UILabel* label, Symbol s){
    AppLabel* pAppLabel = dynamic_cast<AppLabel*>(label);
    MILO_ASSERT(pAppLabel, 0x14E);
    pAppLabel->SetSongName(s, false);
}

bool AccomplishmentSongConditional::InqProgressValues(BandProfile* profile, int& i1, int& i2){
    i2 = GetTotalNumSongs();
    i1 = 0;
    if(profile){
        i1 = GetNumCompletedSongs(profile);
    }
    return true;
}

bool AccomplishmentSongConditional::IsSymbolEntryFulfilled(BandProfile* profile, Symbol s) const {
    if(!profile) return false;
    else {
        SongStatusMgr* pSongStatusMgr = profile->GetSongStatusMgr();
        MILO_ASSERT(pSongStatusMgr, 0x16B);
        return CheckConditionsForSong(pSongStatusMgr, s);
    }
}

bool AccomplishmentSongConditional::ShowBestAfterEarn() const { return false; }

void AccomplishmentSongConditional::InitializeTrackerDesc(TrackerDesc& desc) const {
    Accomplishment::InitializeTrackerDesc(desc);
    MILO_ASSERT(!m_lConditions.empty(), 0x18B);
    const AccomplishmentCondition& condition = m_lConditions[0];
    Symbol cond = condition.mCondition;
    if(cond == streak){
        desc.mType = 0xF;
        desc.unk18.push_back(condition.mValue);
    }
    else if(cond == accuracy){
        desc.mType = 1;
        desc.unk18.push_back(condition.mValue * 0.01f);
    }
    else if(cond == unison_phrases){
        desc.mType = 0x12;
        desc.unk18.push_back(condition.mValue);
    }
    else if(cond == hopos_percent){
        desc.mType = 6;
        desc.unk18.push_back(condition.mValue * 0.01f);
    }
    else if(cond == stars){
        desc.unkc = 0;
    }
}