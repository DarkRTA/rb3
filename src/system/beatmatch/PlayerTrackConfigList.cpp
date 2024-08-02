#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/BeatMatchUtl.h"

#define kMorePlayersThanWeWillEverNeed 8

// fn_80472568
PlayerTrackConfigList::PlayerTrackConfigList(int reserve_num_players) : mAutoVocals(0), mUseVocalHarmony(0), mUseRealDrums(0), mDiscoUnflip(0), unk2c(0),
    mGameCymbalLanes(0), unk34(0), unk38(0), unk3c(1), unk3d(0) {
    MILO_ASSERT(kMorePlayersThanWeWillEverNeed > reserve_num_players, 0x21);
    mTrackDiffs.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackNums.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackTypes.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackOccupied.reserve(kMorePlayersThanWeWillEverNeed);
    mConfigs.reserve(reserve_num_players);
}

void PlayerTrackConfigList::Reset(){
    mTrackDiffs.clear();
    mTrackNums.clear();
    mTrackTypes.clear();
    mTrackOccupied.clear();
    mConfigs.clear();
    unk3d = false;
    unk38 = 0;
    mAutoVocals = false;
    mUseRealDrums = false;
    mDiscoUnflip = false;
    unk2c = false;
    mGameCymbalLanes = 0;
}

void PlayerTrackConfigList::AddConfig(const UserGuid& u, TrackType ty, int i, int j, bool b){
    PlayerTrackConfig ptc(u, ty, i, j, b);
    mConfigs.push_back(ptc);
}

void PlayerTrackConfigList::AddPlaceholderConfig(const UserGuid& u, int i, bool b){
    AddConfig(u, kTrackNone, -1, i, b);
}

void PlayerTrackConfigList::UpdateConfig(const UserGuid& u, TrackType ty, int i, int j, bool b){
    GetConfigByUserGuid(u).Update(ty, i, j, b);
}

void PlayerTrackConfigList::ChangeDifficulty(const UserGuid& u, int i){
    PlayerTrackConfig& cfg = GetConfigByUserGuid(u);
    cfg.Update(cfg.mTrackType, i, cfg.mSlot, cfg.mRemote);
    mTrackDiffs[cfg.unk20] = i;
}

const UserGuid& PlayerTrackConfigList::GetUserGuidByIndex(int idx) const {
    return mConfigs[idx].mUserGuid;
}

PlayerTrackConfig& PlayerTrackConfigList::GetConfigByUserGuid(const UserGuid& u) const {
    for(int i = 0; i < mConfigs.size(); i++){
        PlayerTrackConfig& cur = (PlayerTrackConfig&)mConfigs[i];
        if(cur.mUserGuid == u) return cur;
    }
    MILO_FAIL("Couldn't find config for user %s", u.ToString());
    return (PlayerTrackConfig&)mConfigs.front();
}

PlayerTrackConfig& PlayerTrackConfigList::GetConfigByUserGuid(const UserGuid& u){
    for(int i = 0; i < mConfigs.size(); i++){
        PlayerTrackConfig& cur = mConfigs[i];
        if(cur.mUserGuid == u) return cur;
    }
    MILO_FAIL("Couldn't find config for user %s", u.ToString());
    return mConfigs.front();
}

void PlayerTrackConfigList::SetAutoVocals(bool b){ mAutoVocals = b; }
bool PlayerTrackConfigList::GetAutoVocals() const { return mAutoVocals; }
void PlayerTrackConfigList::SetUseVocalHarmony(bool b){ mUseVocalHarmony = b; }
bool PlayerTrackConfigList::UseVocalHarmony() const { return mUseVocalHarmony; }
int PlayerTrackConfigList::NumSingers() const { return 3; }
void PlayerTrackConfigList::SetUseRealDrums(bool b){ mUseRealDrums = b; }
bool PlayerTrackConfigList::UseRealDrums() const { return mUseRealDrums; }
void PlayerTrackConfigList::SetGameCymbalLanes(unsigned int ui){ mGameCymbalLanes = ui; }
unsigned int PlayerTrackConfigList::GetGameCymbalLanes() const { return mGameCymbalLanes; }

UserGuid& PlayerTrackConfigList::InstrumentPlayer(SongInfoAudioType ty, int i) const {
    for(int idx = 0; idx < mConfigs.size(); idx++){
        TrackType trackty = mConfigs[idx].mTrackType;
        if(trackty != kTrackNone && TrackTypeToAudioType(trackty) == ty){
            if(i == 0) return (UserGuid&)mConfigs[idx].mUserGuid;
            i--;
        }
    }
    return gNullUserGuid;
}
