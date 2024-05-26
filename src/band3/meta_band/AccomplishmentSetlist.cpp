#include "AccomplishmentSetlist.h"

#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"

AccomplishmentSetlist::AccomplishmentSetlist(DataArray* i_pConfig, int i) : Accomplishment(i_pConfig, i), mSetlist(""), mInstrument((ScoreType)10), mDifficulty((Difficulty)0), mMinStars(0) {
    Configure(i_pConfig);
}

AccomplishmentSetlist::~AccomplishmentSetlist() {
    
}

void AccomplishmentSetlist::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1f);

    i_pConfig->FindData(setlist, mSetlist, true);
    int difficultyVal = false;
    bool parsed = i_pConfig->FindData(difficulty, difficultyVal, false);
    if (parsed) {
        mDifficulty = (Difficulty)difficultyVal;
    }
    int instrumentVal = false;
    parsed = i_pConfig->FindData(instrument, instrumentVal, false);
    if (parsed) {
        mInstrument = (ScoreType)instrumentVal;
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

Difficulty AccomplishmentSetlist::GetRequiredDifficulty() const {
    return mDifficulty;
}

void AccomplishmentSetlist::InqRequiredScoreTypes(std::set<ScoreType>& o_rScoreTypes) const {
    MILO_ASSERT(o_rScoreTypes.empty(), 0x52);

    if (mInstrument != 10) {
        o_rScoreTypes.insert(mInstrument);
    }
    
    // return !o_rScoreTypes.empty();
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