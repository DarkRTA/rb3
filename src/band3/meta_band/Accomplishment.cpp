#include "Accomplishment.h"
#include "system/utl/MakeString.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols2.h"
#include "system/utl/Symbols3.h"
#include "system/utl/Symbols4.h"
#include "game/Defines.h"
#include "os/Debug.h"
#include <string>
#include "Campaign.h"

#include "decomp.h"

Accomplishment::Accomplishment(DataArray* i_pConfig, int index) : mName(gNullStr), mAccomplishmentType(0), mCategory(gNullStr),
    mAward(gNullStr), mUnitsToken(gNullStr), mUnitsTokenSingular(gNullStr), mIconOverride(gNullStr), mSecretCampaignLevelPrereq(gNullStr),
    mScoreType((ScoreType)10), mLaunchableDifficulty((Difficulty)0), mPassiveMsgChannel(gNullStr), mPassiveMsgPriority(-1),
    mPlayerCountMin(-1), mPlayerCountMax(-1), mDynamicPrereqsNumSongs(-1), mDynamicPrereqsFilter(gNullStr), mProgressStep(0),
    mIndex(index), mContextId(0), mMetaScoreValue(gNullStr), mRequiresUnison(false), mRequiresBre(false), mDynamicAlwaysVisible(false),
    mShouldShowDenominator(true), mShowBestAfterEarn(true), mHideProgress(false), mCanBeEarnedWithNoFail(true), mIsTrackedInLeaderboard(false) {

    Configure(i_pConfig);
}

Accomplishment::~Accomplishment() {

}

void Accomplishment::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x3e);

    mName = i_pConfig->Sym(0);

    DataArray* controllerTypes = i_pConfig->FindArray(launchable_controller_types, false);
    if (controllerTypes != NULL) {
        mControllerTypes.reserve(controllerTypes->Size() - 1);
        for (int i = 1; i < controllerTypes->Size(); i++) {
            DataNode& node = controllerTypes->Node(i);
            ControllerType controllerType = (ControllerType)node.Int(controllerTypes);

            mControllerTypes.push_back(controllerType);
        }
    }

    int scoreType = 0;
    if (i_pConfig->FindData(launchable_scoretype, scoreType, false)) {
        mScoreType = (ScoreType)scoreType;
    }

    int launchableDifficulty = 0;
    if(i_pConfig->FindData(launchable_difficulty, launchableDifficulty, false)) {
        mLaunchableDifficulty = (Difficulty)launchableDifficulty;
    }

    i_pConfig->FindData(launchable_playercount_min, mPlayerCountMin, false);
    i_pConfig->FindData(launchable_playercount_max, mPlayerCountMax, false);
    i_pConfig->FindData(launchable_requires_unison_ability, mRequiresUnison, false);
    i_pConfig->FindData(launchable_requires_bre_ability, mRequiresBre, 0);
    i_pConfig->FindData(secret_campaignlevel_prereq, mSecretCampaignLevelPrereq, false);

    DataArray* secretPrereqs = i_pConfig->FindArray(secret_prereqs, false);
    if (secretPrereqs != NULL) {
        mSecretPrereqs.reserve(secretPrereqs->Size() - 1);
        for (int i = 1; i < secretPrereqs->Size(); i++) {
            DataNode& node = secretPrereqs->Node(i);
            Symbol s = node.Sym(secretPrereqs);

            mSecretPrereqs.push_back(s);
        }
    }

    DataArray* dynamicPrereqs = i_pConfig->FindArray(dynamic_prereqs, false);
    if (dynamicPrereqs != NULL) {
        dynamicPrereqs->FindData(num_songs, mDynamicPrereqsNumSongs, false);
        dynamicPrereqs->FindData(always_visible, mDynamicAlwaysVisible, false);
        dynamicPrereqs->FindData(precached_filter, mDynamicPrereqsFilter, false);

        dynamicPrereqs = dynamicPrereqs->FindArray(songs, false);

        if(dynamicPrereqs != NULL){
            mDynamicPrereqsSongs.reserve(dynamicPrereqs->Size() - 1);
            for (int i = 1; i < dynamicPrereqs->Size(); i++) {
                DataNode& node = dynamicPrereqs->Node(i);
                Symbol s = node.Sym(dynamicPrereqs);

                mDynamicPrereqsSongs.push_back(s);
            }
            if (mDynamicPrereqsSongs.size() < mDynamicPrereqsNumSongs) {
                TheDebug.Notify(MakeString("There are less songs in the dynamic prereq song list than the num_songs provided: %s\n", mName.Str()));
                mDynamicPrereqsNumSongs = 0xffffffff;
            }
        }
    }

    i_pConfig->FindData(passive_msg_channel, mPassiveMsgChannel, false);
    i_pConfig->FindData(passive_msg_priority, mPassiveMsgPriority, false);

    bool noMsgChannel = !(mPassiveMsgChannel == gNullStr);

    if (noMsgChannel) {
        if (mPassiveMsgPriority < 1) {
            TheDebug.Notify(MakeString("Passive Message Priority for goal %s is less than the minimum: %i!\n", mName.Str(), 1));
            mPassiveMsgPriority = 1;
        } else if (1000 < mPassiveMsgPriority) {
            TheDebug.Notify(MakeString("Passive Message Priority for goal %s is more than the maximum: %i!\n", mName.Str(), 1000));
            mPassiveMsgPriority = 1000;
        }
    }

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

int Accomplishment::GetType() const {
    return 0;
}

Symbol Accomplishment::GetName() const {
    return mName;
}

Symbol Accomplishment::GetDescription() const {
    return MakeString("%s_desc", mName);
}

DECOMP_FORCEACTIVE(Accomplishment, "%s_howto")

Symbol Accomplishment::GetSecretDescription() const {
    return acc_secretdesc;
}

Symbol Accomplishment::GetFlavorText() const {
    return MakeString("%s_flavor", mName);
}

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

const std::vector<Symbol>& Accomplishment::GetSecretPrereqs() const {
    return mSecretPrereqs;
}

bool Accomplishment::IsDynamic() const {
    bool noFilter = !mDynamicPrereqsSongs.empty();
    if (!noFilter) {
        if (gNullStr) {
            noFilter = !strcmp(mDynamicPrereqsFilter.Str(), gNullStr);
        } else { noFilter = (mDynamicPrereqsFilter.Str() == gNullStr); }
        noFilter = !noFilter;
    }
    return noFilter;
}

bool Accomplishment::GetDynamicAlwaysVisible() const {
    return mDynamicAlwaysVisible;
}

const std::vector<Symbol>& Accomplishment::GetDynamicPrereqsSongs() const {
    return mDynamicPrereqsSongs;
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

int Accomplishment::GetContextID() const {
    return mContextId;
}

void Accomplishment::GetIconArt() const {
    bool noIconArt;
    if (gNullStr) {
        noIconArt = !strcmp(mIconOverride.Str(), gNullStr);
    } else { noIconArt = (mIconOverride.Str() == gNullStr); }

    if (!noIconArt) {
        MakeString("ui/accomplishments/accomplishment_art/%s_keep.png", mIconOverride.Str());
    } else {
        MakeString("ui/accomplishments/accomplishment_art/%s_keep.png", mName.Str());
    }
}

DECOMP_FORCEACTIVE(Accomplishment, "%s_gray")

bool Accomplishment::IsFulfilled(BandProfile*) const {
    return false;
}

bool Accomplishment::IsRelevantForSong(Symbol) const {
    return false;
}

bool Accomplishment::InqProgressValues(BandProfile*, int&, int&) {
    return false;
}

Symbol Accomplishment::GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const {
    return gNullStr;
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

Symbol Accomplishment::GetMetaScoreValue() const {
    return mMetaScoreValue;
}

char* Accomplishment::GetIconPath() {
    return "ui/accomplishments/accomplishment_art/%s_keep.png";
 }

bool Accomplishment::IsUserOnValidScoreType(LocalBandUser* i_pUser) const {
    ControllerType controllerType = i_pUser->GetControllerType();

    std::set<ScoreType> scoreTypes;
    ScoreType scoreType;

    bool hasScoreType = InqRequiredScoreTypes(scoreTypes);
    bool returnValue;
    if (scoreTypes.size() == 0) {
        returnValue = false;
    } else {
        std::set<ScoreType>::iterator iterator = scoreTypes.begin();
        while (iterator != scoreTypes.end()) {
            scoreType = *iterator;
            TrackType trackType = ScoreTypeToTrackType(scoreType);
            ControllerType c = TrackTypeToControllerType(trackType);

            if (controllerType == c) {
                returnValue = true;
                break;
            }
            iterator++;
        }
    }
    return returnValue;
}

bool Accomplishment::IsUserOnValidController(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x253);

    ControllerType controllerType = i_pUser->GetControllerType();
    bool isValid = IsUserOnValidScoreType(i_pUser);
    bool returnValue;

    for (size_t i = 0; i < mControllerTypes.size(); i++) {
        if (controllerType == mControllerTypes.at(i)) {
            return true;
        }
    }
    
    return false;
}

Difficulty Accomplishment::GetRequiredDifficulty() const {
    return mLaunchableDifficulty;
}

ScoreType Accomplishment::GetRequiredScoreType() const {
    std::set<ScoreType> scoreTypes;

    bool hasScoreType = InqRequiredScoreTypes(scoreTypes);
    if ((int)scoreTypes.size() == 1) {
        std::set<ScoreType>::iterator iterator = scoreTypes.begin();
        return *iterator;
    } 
    return (ScoreType)10;
}

bool Accomplishment::InqRequiredScoreTypes(std::set<ScoreType>& o_rScoreTypes) const {
    MILO_ASSERT(o_rScoreTypes.empty(), 0x28d);

    if (mScoreType != 10) {
        o_rScoreTypes.insert(mScoreType);
    }

    return !o_rScoreTypes.empty();
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

void Accomplishment::InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const {

}

void Accomplishment::InitializeTrackerDesc(TrackerDesc& trackerDesc) const {
    MILO_ASSERT(TheCampaign, 0x2b8);

    Symbol user = TheCampaign->GetLaunchUser();

    trackerDesc.symbol2 = user;
    trackerDesc.symbol3 = mName;
    trackerDesc.int1 = 2;
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

int Accomplishment::GetPassiveMsgPriority() const {
    return mPassiveMsgPriority;
}
