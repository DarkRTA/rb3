#include "Accomplishment.h"
#include "system/utl/MakeString.h"
#include "system/utl/Symbols2.h"
#include "os/Debug.h"

Accomplishment::Accomplishment(DataArray* i_pConfig, int) {
    Configure(i_pConfig);
}

Accomplishment::~Accomplishment() {
    
}

void Accomplishment::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x00);
}

int Accomplishment::GetType() const {
    return 0;
}

Symbol Accomplishment::GetName() const {
    return mName;
}

Symbol Accomplishment::GetDescription() const {
    return MakeString("", "");
}

Symbol Accomplishment::GetSecretDescription() const {
    return acc_secretdesc;
}

Symbol Accomplishment::GetFlavorText() const {
    return MakeString("", "");
}

void Accomplishment::GetShouldShowDenominator() const {
}

void Accomplishment::ShowBestAfterEarn() const {}
void Accomplishment::HideProgress() const {}
void Accomplishment::GetSecretCampaignLevelPrereq() const {}
void Accomplishment::GetSecretPrereqs() const {}
void Accomplishment::IsDynamic() const {}
void Accomplishment::GetDynamicAlwaysVisible() const {}
void Accomplishment::GetDynamicPrereqsSongs() const{}
void Accomplishment::GetDynamicPrereqsNumSongs() const{}
void Accomplishment::GetDynamicPrereqsFilter() const{}
void Accomplishment::GetCategory() const{}
void Accomplishment::GetContextID() const {}
void Accomplishment::GetIconArt() const {}
bool Accomplishment::IsFulfilled(BandProfile*) const {
    return false;
}

bool Accomplishment::IsRelevantForSong(Symbol) const {
    return false;
}

bool Accomplishment::InqProgressValues(BandProfile*, int&, int&) {
    return false;
}

void Accomplishment::GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const{}
bool Accomplishment::InqIncrementalSymbols(BandProfile*, std::vector<Symbol, unsigned short>&) const {
    return 0;
}


void Accomplishment::IsSymbolEntryFulfilled(BandProfile*, Symbol) const {}
void Accomplishment::CanBeLaunched() const {}
bool Accomplishment::HasSpecificSongsToLaunch() const {
    return false;
}
void Accomplishment::GetAward() const {}
void Accomplishment::HasAward() const {}
void Accomplishment::GetMetaScoreValue() const {}
void Accomplishment::GetIconPath() {    }
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
void Accomplishment::CanBeEarnedWithNoFail() const {}
void Accomplishment::IsTrackedInLeaderboard() const {}
void Accomplishment::GetUnitsToken(int) const {}
void Accomplishment::GetPassiveMsgChannel() const {}
void Accomplishment::GetPassiveMsgPriority() const {}