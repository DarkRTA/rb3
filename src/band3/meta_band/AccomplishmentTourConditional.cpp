#include "meta_band/AccomplishmentTourConditional.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentProgress.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourGameRules.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

AccomplishmentTourConditional::AccomplishmentTourConditional(DataArray* arr, int i) : Accomplishment(arr, i) {
    Configure(arr);
}

AccomplishmentTourConditional::~AccomplishmentTourConditional(){

}

void AccomplishmentTourConditional::UpdateConditionOptionalData(AccomplishmentTourCondition& cond, DataArray* i_pConditionEntryArray){
    MILO_ASSERT(i_pConditionEntryArray->Size() >= 2, 0x1D);
    for(int i = 2; i < i_pConditionEntryArray->Size(); i++){
        DataArray* pEntry = i_pConditionEntryArray->Node(i).Array();
        MILO_ASSERT(pEntry, 0x26);
        MILO_ASSERT(pEntry->Size() == 2, 0x27);
        Symbol key = pEntry->Node(0).Sym();
        if(key == tour){
            cond.mTourDesc = pEntry->Node(1).Sym();
        }
        else if(key == game_type){
            cond.mGameType = (TourGameType)pEntry->Node(1).Int();
        }
        else MILO_ASSERT(false, 0x36);
    }
}

void AccomplishmentTourConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x3E);
    DataArray* pConditionArray = i_pConfig->FindArray(conditions, true);
    if(pConditionArray){
        MILO_ASSERT(pConditionArray->Size() > 1, 0x46);
        for(int i = 1; i < pConditionArray->Size(); i++){
            DataArray* pConditionEntryArray = pConditionArray->Node(i).Array();
            MILO_ASSERT(pConditionEntryArray, 0x4B);
            AccomplishmentTourCondition cond;
            cond.mTourDesc = "";
            cond.mCondition = pConditionEntryArray->Node(i).Sym();
            if(pConditionEntryArray->Size() < 2){
                MILO_WARN("Condition does not have a value associated with it!");
            }
            else {
                cond.mGameType = (TourGameType)pConditionEntryArray->Node(1).Int();
                UpdateConditionOptionalData(cond, pConditionEntryArray);
            }
            m_vConditions.push_back(cond);
        }
    }
}

AccomplishmentType AccomplishmentTourConditional::GetType() const { return kAccomplishmentTypeTourConditional; }

bool AccomplishmentTourConditional::IsFulfilled(BandProfile* profile) const {
    for(std::list<AccomplishmentTourCondition>::const_iterator it = m_vConditions.begin(); it != m_vConditions.end(); ++it){
        if(IsConditionMet(profile, *it)) return true;
    }
    return false;
}

bool AccomplishmentTourConditional::InqBestProgressValues(BandProfile* profile, int& i1, int& i2){
    float f1 = -1.0f;
    for(std::list<AccomplishmentTourCondition>::iterator it = m_vConditions.begin(); it != m_vConditions.end(); ++it){
        int i64 = 0;
        int iGoal = 0;
        InqConditionProgress(profile, *it, i64, iGoal);
        MILO_ASSERT(iGoal > 0, 0x8D);
        int div = ((float)i64 / (float)iGoal);
        if(div > f1){
            i1 = i64;
            i2 = iGoal;
            f1 = div;
        }
    }
    return true;
}

bool AccomplishmentTourConditional::InqProgressValues(BandProfile* profile, int& i1, int& i2){
    InqBestProgressValues(profile, i1, i2);
    return true;
}

bool AccomplishmentTourConditional::InqConditionProgress(BandProfile* profile, const AccomplishmentTourCondition& cond, int& i1, int& i2) const {
    i2 = cond.mValue;
    Symbol desc = cond.mTourDesc;
    Symbol symcond = cond.mCondition;
    TourGameType ty = cond.mGameType;
    if(!TheTour->HasTourDesc(desc)){
        MILO_WARN(MakeString("A Tour goal is referring to an invalid tour desc: %s", desc.Str()));
    }
    i1 = 0;
    if(profile){
        AccomplishmentProgress* prog = profile->GetAccomplishmentProgress();
        if(symcond == tour_total_played){
            if(desc != "") i1 = prog->GetToursPlayed(desc);
            else i1 = prog->GetToursPlayed();
        }
        else if(symcond == tour_most_stars){
            if(desc != "") i1 = prog->GetTourMostStars(desc);
            else MILO_WARN("Accomplishment for tour most stars is missing a tour desc.");
        }
        else if(symcond == tour_times_maxed_stars){
            if(desc != "") i1 = prog->GetToursGotAllStars(desc);
            else i1 = prog->GetToursGotAllStars();
        }
        else if(symcond == tour_quest_type_times_completed){
            if(ty != 0) i1 = prog->GetQuestCompletedCount(ty);
            else i1 = prog->GetQuestCompletedCount();
        }
        else {
            MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, symcond);
            return false;
        }
    }
    return true;
}

bool AccomplishmentTourConditional::IsConditionMet(BandProfile* profile, const AccomplishmentTourCondition& cond) const {
    int i4 = 0;
    int i8 = 0;
    InqConditionProgress(profile, cond, i4, i8);
    return i8 <= i4;
}

bool AccomplishmentTourConditional::CanBeLaunched() const { return true; }

Symbol AccomplishmentTourConditional::GetAssociatedTour() const {
    MILO_ASSERT(!m_vConditions.empty(), 0x10C);
    return m_vConditions.front().mTourDesc;
}

int AccomplishmentTourConditional::GetTourValue() const {
    MILO_ASSERT(!m_vConditions.empty(), 0x115);
    return m_vConditions.front().mValue;
}