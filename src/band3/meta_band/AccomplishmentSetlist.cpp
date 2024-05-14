#include "AccomplishmentSetlist.h"

#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"

AccomplishmentSetlist::AccomplishmentSetlist(DataArray* i_pConfig, int i) : mAccomplishment(i_pConfig, i), mSetlist(""), mDifficulty(0), mInstrument(0), mMinStars(0) {
    Configure(i_pConfig);
}

AccomplishmentSetlist::~AccomplishmentSetlist() {
    
}

void AccomplishmentSetlist::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1f);

    i_pConfig->FindData(setlist, mSetlist, true);
    if (i_pConfig->FindData(difficulty, mDifficulty, false)) {
        mDifficulty = 0;
    }
    if (i_pConfig->FindData(instrument, mInstrument, false)) {
        mInstrument = 0;
    }
    i_pConfig->FindData(min_stars, mMinStars, false);
}

int AccomplishmentSetlist::GetType() const {
    return 10;
}

bool AccomplishmentSetlist::CanBeLaunched() const {
    return true;
}

bool AccomplishmentSetlist::HasSpecificSongsToLaunch() const {
    return true;
}

int AccomplishmentSetlist::GetRequiredDifficulty() const {
    return mDifficulty;
}

void AccomplishmentSetlist::InqRequiredScoreTypes(std::set<ScoreType>& o_rScoreTypes) const {
    MILO_ASSERT(o_rScoreTypes.empty(), 0x52);
}

bool AccomplishmentSetlist::CheckRequirements(ScoreType scoreType, Difficulty difficulty, int minStars) {
    if (difficulty < mDifficulty) {
        return false;
    }

    if (scoreType != mInstrument) {
        return false;
    }

    return mMinStars <= minStars;
}