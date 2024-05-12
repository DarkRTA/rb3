#include "AccomplishmentSetlist.h"

#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"
 
AccomplishmentSetlist::AccomplishmentSetlist(DataArray* i_pConfig, int i) : mAccomplishment(i_pConfig, i), mSetlist("") {
    Configure(i_pConfig);
}

AccomplishmentSetlist::~AccomplishmentSetlist() {
    
}

void AccomplishmentSetlist::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1f);

    i_pConfig->FindData(setlist, mSetlist, true);
    if(i_pConfig->FindData(difficulty, mDifficulty, false)) {
        mDifficulty = 0;
    }
    if(i_pConfig->FindData(instrument, mInstrument, false)) {
        mInstrument = 0;
    }
    i_pConfig->FindData(min_stars, mMin_stars, false);
}

int AccomplishmentSetlist::GetType() const {
    return mDifficulty;
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
    MILO_ASSERT(o_rScoreTypes.empty(), 0x00);

    
}

bool AccomplishmentSetlist::CheckRequirements(ScoreType scoreType, Difficulty difficulty, int instrument) {
    if (!(scoreType == mDifficulty)) { // TODO: What do I compare this to
        return false;
    }

    if (instrument != mInstrument) {
        return false;
    }

    if (difficulty < mDifficulty) {
        return false;
    }

    return true;
}