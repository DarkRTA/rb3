#include "AccomplishmentTrainerCategoryConditional.h"
#include "os/Debug.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

AccomplishmentTrainerCategoryConditional::AccomplishmentTrainerCategoryConditional(DataArray* i_pConfig, int i) : AccomplishmentTrainerConditional(i_pConfig, i), mCategory(""), mNumLessons(0) {
    Configure(i_pConfig);
}

AccomplishmentTrainerCategoryConditional::~AccomplishmentTrainerCategoryConditional() {

}

void AccomplishmentTrainerCategoryConditional::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1E);
    i_pConfig->FindData(lesson_category, mCategory, true);
    i_pConfig->FindData(num_lessons, mNumLessons, true);
}

AccomplishmentType AccomplishmentTrainerCategoryConditional::GetType() const {
    return kAccomplishmentTypeTrainerCategoryConditional;
}

bool AccomplishmentTrainerCategoryConditional::IsFulfilled(BandProfile* profile) const {
    return mNumLessons <= GetNumCompletedLessons(profile);
}

int AccomplishmentTrainerCategoryConditional::GetNumCompletedLessons(BandProfile* profile) const {
    std::vector<Symbol> lessons;
    InqCompletedLessons(profile, lessons);
    int ret = lessons.size();
    if(ret >= mNumLessons) ret = mNumLessons;
    return ret;
}

bool AccomplishmentTrainerCategoryConditional::InqIncrementalSymbols(BandProfile* i_pProfile, std::vector<Symbol>& o_rSymbols) const {
    MILO_ASSERT(i_pProfile, 0x48);
    MILO_ASSERT(o_rSymbols.empty(), 0x49);
}

Symbol AccomplishmentTrainerCategoryConditional::GetFirstUnfinishedAccomplishmentEntry(BandProfile* i_pProfile) const {
    MILO_ASSERT(i_pProfile, 0x77);
}

int AccomplishmentTrainerCategoryConditional::GetTotalNumLessons() const { return mNumLessons; }

void AccomplishmentTrainerCategoryConditional::InqCompletedLessons(BandProfile*, std::vector<Symbol>&) const {}
