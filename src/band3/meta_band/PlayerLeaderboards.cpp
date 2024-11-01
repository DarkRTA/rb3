#include "meta_band/PlayerLeaderboard.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/ProfileMgr.h"
#include "net/Net.h"
#include "net/Server.h"
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