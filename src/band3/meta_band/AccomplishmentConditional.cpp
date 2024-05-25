#include "AccomplishmentConditional.h"

AccomplishmentConditional::AccomplishmentConditional(DataArray* i_pConfig, int i) : Accomplishment(i_pConfig, i) {
    AccomplishmentConditional::Configure(i_pConfig);
}

AccomplishmentConditional::~AccomplishmentConditional() { 

}

void AccomplishmentConditional::
    UpdateConditionOptionalData(AccomplishmentCondition&, DataArray*) {
}

void AccomplishmentConditional::Configure(DataArray* i_pConfig) {

}

bool AccomplishmentConditional::CanBeLaunched() const {
    return true;
}

void AccomplishmentConditional::InqRequiredScoreTypes(std::set<ScoreType>&) const {

}

Difficulty AccomplishmentConditional::GetRequiredDifficulty() const {
    return Accomplishment::GetRequiredDifficulty();
}