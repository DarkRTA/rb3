#include "Accomplishment.h"
#include "system/utl/MakeString.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols2.h"
#include "system/utl/Symbols3.h"
#include "system/utl/Symbols4.h"
#include "os/Debug.h"
#include <string>

Accomplishment::Accomplishment(DataArray* i_pConfig, int) : mName(gNullStr), mSecretPrereqs(NULL), mCategory(gNullStr), mAward(gNullStr),
 mUnitsToken(gNullStr), mUnitsTokenSingular(gNullStr), mIconOverride(gNullStr), mSecretCampaignLevelPrereq(gNullStr), mRequiresUnison(false), 
 mDynamicAlwaysVisible(true), mShouldShowDenominator(true), mHideProgress(false), mCanBeEarnedWithNoFail(true), mIsTrackedInLeaderboard(false) {
    Configure(i_pConfig);
}

Accomplishment::~Accomplishment() {
    
}

void Accomplishment::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x3e);

    mName = i_pConfig->Sym(0);
    DataArray* controllerTypes = i_pConfig->FindArray(launchable_controller_types, false);
    if (controllerTypes != NULL) {
        mVector1.reserve(controllerTypes->Size());
        for (int i = 0; i < controllerTypes->Size(); i++) {
            DataNode& node = controllerTypes->Node(i);
            if (1) {

            } else {

            }
        }
    }

    Symbol scoreType;
    if (i_pConfig->FindData(launchable_scoretype, scoreType, false)) {
        mScoreType = scoreType;
    }

    Symbol launchableDifficulty;
    if(i_pConfig->FindArray(launchable_difficulty, false)) {
        mLaunchableDifficulty = launchableDifficulty;
    }

    i_pConfig->FindData(launchable_playercount_min, mPlayerCountMin, false);
    i_pConfig->FindData(launchable_playercount_max, mPlayerCountMax, false);
    i_pConfig->FindData(launchable_requires_unison_ability, mRequiresUnison, false);
    i_pConfig->FindData(launchable_requires_bre_ability, mRequiresBre, 0);
    i_pConfig->FindData(secret_campaignlevel_prereq, mSecretCampaignLevelPrereq, false);

    DataArray* secretPrereqs = i_pConfig->FindArray(secret_prereqs, false);
    if (secretPrereqs != NULL) {

    }

    DataArray* dynamicPrereqs = i_pConfig->FindArray(dynamic_prereqs, false);
    if (dynamicPrereqs != NULL) {

    }

    i_pConfig->FindData(passive_msg_channel, mPassiveMsgChannel, false);
    i_pConfig->FindData(passive_msg_priority, mPassiveMsgPriority, false);

    // if() {}
    // else {}

    // if() {}
    // else {}

    i_pConfig->FindData(progress_step, mProgressStep, false);
    i_pConfig->FindData(show_best_after_earn, mShowBestAfterEarn, false);
    i_pConfig->FindData(show_denominator, mShouldShowDenominator, false);
    i_pConfig->FindData(hide_progress, mHideProgress, false);
    i_pConfig->FindData(can_be_earned_with_no_fail, mCanBeEarnedWithNoFail, false);
    i_pConfig->FindData(leaderboard, mIsTrackedInLeaderboard, false);
    int accomplishmentType;
    i_pConfig->FindData(accomplishment_type, accomplishmentType, true);
    mAccomplishmentType = accomplishmentType;
    i_pConfig->FindData(category, mCategory, true);
    i_pConfig->FindData(award, mAward, false);
    i_pConfig->FindData(icon_override, mIconOverride, false);
    i_pConfig->FindData(units_token, mUnitsToken, false);
    i_pConfig->FindData(units_token_singular, mUnitsTokenSingular, false);
    i_pConfig->FindData(metascore_value, mMetaScoreValue, true);
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
    // Returning mSecretPrereqs doesn't compile to the same thing. I know it's terrible. 
    return (Accomplishment*)((unsigned long)this + 8);   
}

bool Accomplishment::IsDynamic() const {
    bool noFilter;
    if (gNullStr) {
        noFilter = !strcmp(mDynamicPrereqsFilter.Str(), gNullStr);
    } else { noFilter = (mDynamicPrereqsFilter.Str() == gNullStr); }
    return noFilter;
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

Symbol Accomplishment::GetDynamicPrereqsFilter() const {
    return mDynamicPrereqsFilter;
}

Symbol Accomplishment::GetCategory() const {
    return mCategory;
}

Symbol Accomplishment::GetContextID() const {
    return mContextId;
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
    return !(mAward == "");
}

int Accomplishment::GetMetaScoreValue() const {
    return mMetaScoreValue;
}

char* Accomplishment::GetIconPath() { 
    return "ui/accomplishments/accomplishment_art/%s_keep.png";
 }

void Accomplishment::IsUserOnValidScoreType(LocalBandUser*) const {

}

void Accomplishment::IsUserOnValidController(LocalBandUser*) const {

}

Symbol Accomplishment::GetRequiredDifficulty() const {
    return mLaunchableDifficulty;
}

void Accomplishment::GetRequiredScoreType() const {

}

void Accomplishment::InqRequiredScoreTypes(std::set<ScoreType>&) const {

}

int Accomplishment::GetRequiredMinPlayers() const {
    return mPlayerCountMin;
}

int Accomplishment::GetRequiredMaxPlayers() const {
    return mPlayerCountMax;
}

bool Accomplishment::GetRequiresUnisonAbility() const {
    return mRequiresUnison;
}

bool Accomplishment::GetRequiresBREAbility() const {
    return mRequiresBre;
}

// void Accomplishment::InitializeMusicLibraryTask() const {}

void Accomplishment::InitializeTrackerDesc(TrackerDesc&) const {

}

bool Accomplishment::CanBeEarnedWithNoFail() const {
    return mCanBeEarnedWithNoFail;
}

bool Accomplishment::IsTrackedInLeaderboard() const {
    return mIsTrackedInLeaderboard;
}

Symbol Accomplishment::GetUnitsToken(int useSingular) const {
    bool noToken;
    if (gNullStr) {
        noToken = !strcmp(mUnitsToken.Str(), gNullStr);
    } else { noToken = (mUnitsToken.Str() == gNullStr); }

    if (!noToken) {
        if (useSingular == 1) {
            bool noSingularToken;
            if (gNullStr) {
                noSingularToken = !strcmp(mUnitsTokenSingular.Str(), gNullStr);
            } else { noSingularToken = (mUnitsTokenSingular.Str() == gNullStr); }

            if (!noSingularToken) {
                return mUnitsTokenSingular;
            } else {
                return mUnitsToken;
            }
        } else {
            return mUnitsToken;
        }
    } else {
        if (useSingular == 1) {
            return campaign_goalunits_singular_default;
        } 
        return campaign_goalunits_default;
    }
}

Symbol Accomplishment::GetPassiveMsgChannel() const {
    return mPassiveMsgChannel;
}

Symbol Accomplishment::GetPassiveMsgPriority() const {
    return mPassiveMsgPriority;
}
