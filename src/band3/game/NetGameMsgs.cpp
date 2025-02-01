#include "NetGameMsgs.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Player.h"
#include "meta_band/AccomplishmentManager.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "utl/Symbols.h"

PlayerGameplayMsg::PlayerGameplayMsg(
    User *user, int opCode, int arg1, int arg2, int arg3
) {
    MILO_ASSERT_RANGE(opCode, 0, 256, 0x1E);
    mUserGuid = user->mUserGuid;
    mOpcode = opCode;
    mArg1 = arg1;
    mArg2 = arg2;
    mArg3 = arg3;
}

void PlayerGameplayMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << (unsigned char)mOpcode;
    bs << mArg1;
    bs << mArg2;
    bs << mArg3;
}

void PlayerGameplayMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    unsigned char op;
    bs >> op;
    mOpcode = op;
    bs >> mArg1;
    bs >> mArg2;
    bs >> mArg3;
}

void PlayerGameplayMsg::Dispatch() {
    static Message gameplayMsg(incoming_msg, 0, 0, 0, 0, 0);
    gameplayMsg[0] = mOpcode;
    gameplayMsg[1] = TheBandUserMgr->GetUser(mUserGuid, true);
    gameplayMsg[2] = mArg1;
    gameplayMsg[3] = mArg2;
    gameplayMsg[4] = mArg3;
    Hmx::Object *delegator =
        ObjectDir::Main()->Find<Hmx::Object>("net_gameplay_delegator", true);
    MILO_ASSERT(delegator, 0x44);
    delegator->Handle(gameplayMsg, true);
}

void RestartGameMsg::Save(BinStream &bs) const { bs << mFromWin; }

void RestartGameMsg::Load(BinStream &bs) { bs >> mFromWin; }

#pragma push
#pragma pool_data off
void RestartGameMsg::Dispatch() {
    static DataArrayPtr restart("game_restart");
    ThePlatformMgr.SetIsRestarting(true);
    static DataArrayPtr restartFromWin("game_restart_from_win");
    if (mFromWin) {
        restartFromWin->Execute();
    } else {
        restart->Execute();
    }
}
#pragma pop

ResumeNoScoreGameMsg::ResumeNoScoreGameMsg() : mFraction(0) {}
ResumeNoScoreGameMsg::ResumeNoScoreGameMsg(float f) : mFraction(f) {}

void ResumeNoScoreGameMsg::Save(BinStream &bs) const { bs << mFraction; }

void ResumeNoScoreGameMsg::Load(BinStream &bs) { bs >> mFraction; }

void ResumeNoScoreGameMsg::Dispatch() {
    static DataArrayPtr restart("game_resume_no_score", 0.0f);
    restart->Node(1) = mFraction;
    restart->Execute();
}

PlayerStatsMsg::PlayerStatsMsg(User *user, int score, const Stats &stats)
    : mUserGuid(user->mUserGuid), mScore(score), mStats(stats) {}

void PlayerStatsMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << mScore;
    mStats.SaveForEndGame(bs);
}

void PlayerStatsMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    bs >> mScore;
    mStats.LoadForEndGame(bs);
}

void PlayerStatsMsg::Dispatch() {
    BandUser *user = TheBandUserMgr->GetBandUser(mUserGuid, true);
    if (user->mPlayer) {
        user->mPlayer->SetStats(mScore, mStats);
    }
}

SetUserTrackTypeMsg::SetUserTrackTypeMsg(User *user, String string)
    : mUserGuid(user->mUserGuid), mTrackType(string) {}

void SetUserTrackTypeMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << mTrackType;
}

void SetUserTrackTypeMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    bs >> mTrackType;
}

void SetUserTrackTypeMsg::Dispatch() {
    BandUser *pUser = TheBandUserMgr->GetBandUser(mUserGuid, true);
    MILO_ASSERT(pUser && pUser->IsLocal(), 0xC1);
    Symbol tracktypesym(mTrackType.c_str());
    pUser->SetTrackType(tracktypesym);
}

SetUserDifficultyMsg::SetUserDifficultyMsg(User *user, String string)
    : mUserGuid(user->mUserGuid), mDifficulty(string) {}

void SetUserDifficultyMsg::Save(BinStream &binStream) const {
    binStream << mUserGuid;
    binStream << mDifficulty;
}

void SetUserDifficultyMsg::Load(BinStream &binStream) {
    binStream >> mUserGuid;
    binStream >> mDifficulty;
}

void SetUserDifficultyMsg::Dispatch() {
    BandUser *pUser = TheBandUserMgr->GetBandUser(mUserGuid, true);
    MILO_ASSERT(pUser && pUser->IsLocal(), 0xDD);
    Symbol diffsym(mDifficulty.c_str());
    pUser->SetDifficulty(diffsym);
}

SetlistSubmissionMsg::SetlistSubmissionMsg(const std::vector<int> &ids, int users) {
    mSongIDs = ids;
    mNumUsers = users;
}

void SetlistSubmissionMsg::Save(BinStream &bs) const {
    bs << mSongIDs;
    bs << mNumUsers;
}

void SetlistSubmissionMsg::Load(BinStream &bs) {
    bs >> mSongIDs;
    bs >> mNumUsers;
}

void SetlistSubmissionMsg::Dispatch() {
    // SetlistMergePanel* panel =
    // ObjectDir::Main()->Find<SetlistMergePanel>("setlist_merge_panel", true);
    // MILO_ASSERT(panel, 0xF9);
    //   SetlistMergePanel::HandleSetlistSubmission(this_00,(vector<> *)(this + 4),*(int
    //   *)(this + 0xc)) ;
}

TourMostStarsMsg::TourMostStarsMsg(Symbol symbol, int cap) : unk4(symbol), unk8(cap) {}

void TourMostStarsMsg::Save(BinStream &bs) const {
    bs << unk4;
    bs << unk8;
}

void TourMostStarsMsg::Load(BinStream &bs) {
    bs >> unk4;
    bs >> unk8;
}

void TourMostStarsMsg::Dispatch() {
    TheAccomplishmentMgr->UpdateMostStarsForAllParticipants(unk4, unk8);
}

TourPlayedMsg::TourPlayedMsg(Symbol symbol) : mTourPlayed(symbol) {}

void TourPlayedMsg::Save(BinStream &binStream) const { binStream << mTourPlayed; }

void TourPlayedMsg::Load(BinStream &binStream) { binStream >> mTourPlayed; }

void TourPlayedMsg::Dispatch() {
    TheAccomplishmentMgr->UpdateTourPlayedForAllParticipants(mTourPlayed);
}

AccomplishmentMsg::AccomplishmentMsg(Symbol symbol) : mAccomplishment(symbol) {}

void AccomplishmentMsg::Save(BinStream &binStream) const { binStream << mAccomplishment; }

void AccomplishmentMsg::Load(BinStream &binStream) { binStream >> mAccomplishment; }

void AccomplishmentMsg::Dispatch() {
    TheAccomplishmentMgr->EarnAccomplishmentForAllParticipants(mAccomplishment);
}

AccomplishmentEarnedMsg::AccomplishmentEarnedMsg(
    Symbol symbol1, const char *text, Symbol symbol2
)
    : mSymbol1(symbol1), mStr(text), mSymbol2(symbol2) {}

void AccomplishmentEarnedMsg::Save(BinStream &binStream) const {
    binStream << mSymbol1;
    binStream << mStr;
    binStream << mSymbol2;
}

void AccomplishmentEarnedMsg::Load(BinStream &binStream) {
    binStream >> mSymbol1;
    binStream >> mStr;
    binStream >> mSymbol2;
}

void AccomplishmentEarnedMsg::Dispatch() {
    TheAccomplishmentMgr->HandleRemoteAccomplishmentEarned(
        mSymbol1, mStr.c_str(), mSymbol2
    );
}

SetPartyShuffleModeMsg::SetPartyShuffleModeMsg() {}
void SetPartyShuffleModeMsg::Save(BinStream &) const {}
void SetPartyShuffleModeMsg::Load(BinStream &) {}

void SetPartyShuffleModeMsg::Dispatch() {
    // requires musiclibrary
}

TourHideShowFiltersMsg::TourHideShowFiltersMsg(bool show) : mShowMode(show) {}

void TourHideShowFiltersMsg::Save(BinStream &binStream) const { binStream << mShowMode; }

void TourHideShowFiltersMsg::Load(BinStream &binStream) { binStream >> mShowMode; }

void TourHideShowFiltersMsg::Dispatch() {
    static Message msg("client_tour_hideshow_filters", 0);
    msg[0] = mShowMode;
}

SongResultsScrollMsg::SongResultsScrollMsg(int param1, int param2)
    : unk_0x4(param1), unk_0x8(param2) {}

void SongResultsScrollMsg::Save(BinStream &binStream) const {
    binStream << unk_0x4;
    binStream << unk_0x8;
}

void SongResultsScrollMsg::Load(BinStream &binStream) {
    binStream >> unk_0x4;
    binStream >> unk_0x8;
}

void SongResultsScrollMsg::Dispatch() {
    static Message msg("net_songresults_scroll", 0, 0);
    msg[0] = unk_0x4;
    msg[1] = unk_0x8;
}

void SetUpMicsMsg::Save(BinStream &bs) const {
    bs << mHasMic1;
    bs << mHasMic2;
    bs << mHasMic3;
}

void SetUpMicsMsg::Load(BinStream &bs) {
    bs >> mHasMic1;
    bs >> mHasMic2;
    bs >> mHasMic3;
}
