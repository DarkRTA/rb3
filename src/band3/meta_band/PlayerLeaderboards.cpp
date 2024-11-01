#include "meta_band/PlayerLeaderboards.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/ProfileMgr.h"
#include "net/Net.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "os/PlatformMgr.h"
#include "utl/Symbol.h"

PlayerLeaderboard::PlayerLeaderboard(Profile* p, Callback* cb) : Leaderboard(EntityID(), cb) {
    if(!p){
        p = TheProfileMgr.GetProfileFromPad(ThePlatformMgr.GetOwnerOfGuest(0));
    }
    if(p){
        Server* s = TheNet.mServer;
        mEntityID = EntityID(s->GetPlayerID(p->GetPadNum()));
    }
}

Symbol PlayerLeaderboard::OnSelectRow(int, BandUser*){
    if(IsEnumComplete()) NumData();
    return gNullStr;
}

bool PlayerLeaderboard::CanRowsBeSelected() const { return false; }
bool PlayerLeaderboard::IsRowFriend(int idx) const { return mLeaderboardRows[idx].mIsFriend; }
bool PlayerLeaderboard::IsRowSelf(int idx) const { return mLeaderboardRows[idx].mIsSelf; }

PlayerSongLeaderboard::PlayerSongLeaderboard(Profile* p, Leaderboard::Callback* cb, ScoreType s, int id) : PlayerLeaderboard(p, cb), mScoreType(s), mSongID(id) {

}

void PlayerSongLeaderboard::EnumerateFromID(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetLeaderboardByPlayer(ids, mSongID, mScoreType, kSong, ModeToLeaderboardMode(mMode), sPageSize, mDataResultList, this);
}

void PlayerSongLeaderboard::EnumerateRankRange(int i1, int i2){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetLeaderboardByRankRange(ids, mSongID, mScoreType, i1, i1 + i2, kSong, mDataResultList, this);
}

void PlayerSongLeaderboard::GetStats(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetMaxRank(ids, mSongID, mScoreType, kSong, mDataResultList, this);
}

PlayerBattleLeaderboard::PlayerBattleLeaderboard(Profile* p, Leaderboard::Callback* cb, int id) : PlayerLeaderboard(p, cb), mSongID(id) {

}

void PlayerBattleLeaderboard::EnumerateFromID(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetBattleLeaderboardByPlayer(ids, mSongID, ModeToLeaderboardMode(mMode), sPageSize, mDataResultList, this);
}

void PlayerBattleLeaderboard::EnumerateRankRange(int i1, int i2){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetBattleLeaderboardByRankRange(ids, mSongID, i1, i1 + i2, mDataResultList, this);
}

void PlayerBattleLeaderboard::GetStats(){
    mDataResultList.Clear();
    std::vector<int> ids;
    GetPlayerIds(ids);
    TheRockCentral.GetBattleMaxRank(ids, mSongID, mDataResultList, this);
}