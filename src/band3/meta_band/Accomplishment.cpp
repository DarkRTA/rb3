#include "Accomplishment.h"
#include "system/utl/MakeString.h"
#include "system/utl/Symbols2.h"
#include "os/Debug.h"
#include <string>

Accomplishment::Accomplishment(DataArray* i_pConfig, int) : mName(gNullStr), mAward(gNullStr) {
    Configure(i_pConfig);
}

Accomplishment::~Accomplishment() {
    
}

void Accomplishment::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x3e);

    mName = i_pConfig->Sym(0);
}

std::string unusedStrings[] = {
    "There are less songs in the dynamic prereq song list than the num_songs provided: %s.", 
    "Passive Message Priority for goal %s is less than the minimum: %i!", 
    "Passive Message Priority for goal %s is more than the maximum: %i!", 
    "%s_howto", 

};

int Accomplishment::GetType() const {
    return 0;
}

Symbol Accomplishment::GetName() const {
    return mName;
}

Symbol Accomplishment::GetDescription() const {
    return MakeString("%s_desc", mName);
}

Symbol Accomplishment::GetSecretDescription() const {
    return acc_secretdesc;
}

Symbol Accomplishment::GetFlavorText() const {
    return MakeString("%s_flavor", mName);
}

std::string unusedStrings2[] = {
    "%s_gray", 
    "i_pUser", 
    "o_rScoreTypes.empty()", 
    "TheCampaign"
};

bool Accomplishment::GetShouldShowDenominator() const {
    return mShouldShowDenominator;
}

bool Accomplishment::ShowBestAfterEarn() const {
    return mShowBestAfterEarn;
}

bool Accomplishment::HideProgress() const {
    return mHideProgress;
}

Symbol Accomplishment::GetSecretCampaignLevelPrereq() const {
    return mSecretCampaignLevelPrereq;
}

Accomplishment* Accomplishment::GetSecretPrereqs() const {
    return (Accomplishment*)((unsigned long)this + 8);  // ???
}

bool Accomplishment::IsDynamic() const {
    return strcmp(mName.Str(), gNullStr) != 0;
}

bool Accomplishment::GetDynamicAlwaysVisible() const {
    return mDynamicAlwaysVisible;
}

int Accomplishment::GetDynamicPrereqsSongs() const {
    return mDynamicPrereqsNumSongs;
}

int Accomplishment::GetDynamicPrereqsNumSongs() const {
    return mDynamicPrereqsNumSongs;
}

void Accomplishment::GetDynamicPrereqsFilter() const {

}

Symbol Accomplishment::GetCategory() const {
    return mCategory;
}

void Accomplishment::GetContextID() const {

}

void Accomplishment::GetIconArt() const {

}

bool Accomplishment::IsFulfilled(BandProfile*) const {
    return false;
}

bool Accomplishment::IsRelevantForSong(Symbol) const {
    return false;
}

bool Accomplishment::InqProgressValues(BandProfile*, int&, int&) {
    return false;
}

bool Accomplishment::GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const {
    return strcmp(mName.Str(), gNullStr) != 0;
}

bool Accomplishment::InqIncrementalSymbols(BandProfile*, std::vector<Symbol, unsigned short>&) const {
    return 0;
}


bool Accomplishment::IsSymbolEntryFulfilled(BandProfile*, Symbol) const {
    return false;
}

bool Accomplishment::CanBeLaunched() const {
    if (mName == acc_calibrate) {
        return true;
    }

    if (mName == acc_charactercreate) {
        return true;
    }

    if (mName == acc_bandcreate) {
        return true;
    }

    if (mName == acc_bandlogo) {
        return true;
    }

    if (mName == acc_standins) {
        return true;
    }

    if (mName == acc_joinalabel) {
        return true;
    }

    if (mName == acc_startalabel) {
        return true;
    }

    if (mName == acc_createsetlist) {
        return true;
    }

    if (mName == acc_HMXrecommends) {
        return true;
    }

    if (mName == acc_multiplayersession) {
        return true;
    }

    if (mName == acc_guitartutorial01) {
        return true;
    }

    if (mName == acc_guitartutorial02) {
        return true;
    }

    if (mName == acc_guitartutorial03) {
        return true;
    }

    return false;
}

bool Accomplishment::HasSpecificSongsToLaunch() const {
    return false;
}

Symbol Accomplishment::GetAward() const {
    return mAward;
}

bool Accomplishment::HasAward() const {
    return strcmp(mAward.Str(), gNullStr) != 0;
}

int Accomplishment::GetMetaScoreValue() const {
    return mMetaScoreValue;
}

char* Accomplishment::GetIconPath() { 
    return "ui/accomplishments/accomplishment_art/%s_keep.png";
 }

void Accomplishment::IsUserOnValidScoreType(LocalBandUser*) const {}
void Accomplishment::IsUserOnValidController(LocalBandUser*) const {}
void Accomplishment::GetRequiredDifficulty() const {}
void Accomplishment::GetRequiredScoreType() const {}
void Accomplishment::InqRequiredScoreTypes(std::set<ScoreType>&) const {}
void Accomplishment::GetRequiredMinPlayers() const {}
void Accomplishment::GetRequiredMaxPlayers() const {}
void Accomplishment::GetRequiresUnisonAbility() const {}
void Accomplishment::GetRequiresBREAbility() const {}
// void Accomplishment::InitializeMusicLibraryTask() const {}

void Accomplishment::InitializeTrackerDesc(TrackerDesc&) const {}

bool Accomplishment::CanBeEarnedWithNoFail() const {
    return mCanBeEarnedWithNoFail;
}

bool Accomplishment::IsTrackedInLeaderboard() const {
    return mIsTrackedInLeaderboard;
}

void Accomplishment::GetUnitsToken(int) const {}

void Accomplishment::GetPassiveMsgChannel() const {}

void Accomplishment::GetPassiveMsgPriority() const {}