#include "AccomplishmentTrainerCategoryConditional.h"

AccomplishmentTrainerCategoryConditional::AccomplishmentTrainerCategoryConditional(DataArray* i_pConfig, int i) : AccomplishmentTrainerConditional(i_pConfig, i), m0x7c(""), m0x80(0) {
    Configure(i_pConfig);
}

AccomplishmentTrainerCategoryConditional::~AccomplishmentTrainerCategoryConditional() {

}

void AccomplishmentTrainerCategoryConditional::Configure(DataArray* i_pConfig) {

}

AccomplishmentType AccomplishmentTrainerCategoryConditional::GetType() const {
    return kAccomplishmentTypeTrainerCategoryConditional;
}

bool AccomplishmentTrainerCategoryConditional::IsFulfilled(BandProfile*) const {

}

void AccomplishmentTrainerCategoryConditional::GetNumCompletedLessons(BandProfile*) const {

}

bool AccomplishmentTrainerCategoryConditional::InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const {}
Symbol AccomplishmentTrainerCategoryConditional::GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const {}
int AccomplishmentTrainerCategoryConditional::GetTotalNumLessons() const {
}
void AccomplishmentTrainerCategoryConditional::InqCompletedLessons(BandProfile*, std::vector<Symbol>&) const {}
