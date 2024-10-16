#include "AccomplishmentTrainerConditional.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "utl/Symbols2.h"

AccomplishmentTrainerConditional::AccomplishmentTrainerConditional(DataArray* i_pConfig, int i) : Accomplishment(i_pConfig, i){
    Configure(i_pConfig);
}

AccomplishmentTrainerConditional::~AccomplishmentTrainerConditional() {

}

void AccomplishmentTrainerConditional::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1c);

    DataArray* pConditionArray = i_pConfig->FindArray(conditions, true);
    MILO_ASSERT(pConditionArray->Size() > 1, 0x23);

    for (int i = 1; i < pConditionArray->Size(); i++) {
        DataArray* pConditionEntryArray = pConditionArray->Node(i).Array();
        MILO_ASSERT(pConditionEntryArray, 0x28);

        TrainerCondition condition;

        condition.mCondition = pConditionEntryArray->Node(0).Sym();
        if (pConditionEntryArray->Size() > 1) {
            condition.mValue = pConditionEntryArray->Node(1).Float();
        } else {
            condition.mValue = 0.0;
        }

        mConditions.push_back(condition);
    }
}

bool AccomplishmentTrainerConditional::CheckLessonCompleteCondition(BandProfile* profile, Symbol param_2, float param_3) const {
    if (profile != NULL) {
        return profile->IsLessonComplete(param_2, param_3);
    }
    return false;
}

bool AccomplishmentTrainerConditional::CheckConditionsForLesson(BandProfile* profile, Symbol param_2) const {
    for (std::list<TrainerCondition>::const_iterator it = mConditions.begin(); it != mConditions.end(); it++) {
        TrainerCondition condition = *it;
        if (condition.mCondition == complete_lesson) {
            bool result = CheckLessonCompleteCondition(profile, param_2, condition.mValue);
            if (result) {
                return true;
            }
        } else {
            MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, condition.mCondition);
            return false;
        }
    }

    return false;
}

void AccomplishmentTrainerConditional::UpdateIncrementalEntryName(UILabel* label, Symbol text) {
    label->SetTextToken(text);
}

bool AccomplishmentTrainerConditional::InqProgressValues(BandProfile* profile, int& i1, int& i2) {
    i2 = GetTotalNumLessons();
    i1 = 0;
    if(profile){
        i1 = GetNumCompletedLessons(profile);
    }
    return true;
}

bool AccomplishmentTrainerConditional::IsSymbolEntryFulfilled(BandProfile* profile, Symbol param_2) const {
    if (profile == NULL) {
        return false;
    }

    return CheckConditionsForLesson(profile, param_2);
}

bool AccomplishmentTrainerConditional::ShowBestAfterEarn() const {
    return false;
}

bool AccomplishmentTrainerConditional::CanBeLaunched() const {
    return true;
}