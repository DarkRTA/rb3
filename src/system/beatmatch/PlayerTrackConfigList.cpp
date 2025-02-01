#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/BeatMatchUtl.h"
#include "decomp.h"

#define kMorePlayersThanWeWillEverNeed 8

// fn_80472568
PlayerTrackConfigList::PlayerTrackConfigList(int reserve_num_players)
    : mAutoVocals(0), mUseVocalHarmony(0), mUseRealDrums(0), mDiscoUnflip(0), unk2c(0),
      mGameCymbalLanes(0), mUseGHDrums(0), mDefaultDifficulty(0), mNeedsProcessing(1),
      mProcessed(0) {
    MILO_ASSERT(kMorePlayersThanWeWillEverNeed > reserve_num_players, 0x21);
    mTrackDiffs.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackNums.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackTypes.reserve(kMorePlayersThanWeWillEverNeed);
    mTrackOccupied.reserve(kMorePlayersThanWeWillEverNeed);
    mConfigs.reserve(reserve_num_players);
}

DECOMP_FORCEACTIVE(
    PlayerTrackConfigList,
    "PlayerTrackConfigList: Asked for active UserGuid #%d, which doesn't exist"
)

void PlayerTrackConfigList::Reset() {
    mTrackDiffs.clear();
    mTrackNums.clear();
    mTrackTypes.clear();
    mTrackOccupied.clear();
    mConfigs.clear();
    mProcessed = false;
    mDefaultDifficulty = 0;
    mAutoVocals = false;
    mUseRealDrums = false;
    mDiscoUnflip = false;
    unk2c = false;
    mGameCymbalLanes = 0;
}

int PlayerTrackConfigList::AddConfig(
    const UserGuid &u, TrackType ty, int x, int j, bool b
) {
    PlayerTrackConfig ptc(u, ty, x, j, b);
    mConfigs.push_back(PlayerTrackConfig());
    int i = 0;
    for (; i < mConfigs.size() - 1; i++) {
        if (u < ConfigAt(i).mUserGuid)
            break;
    }
    for (int j = mConfigs.size() - 1; i < j; j--) {
        mConfigs[j] = mConfigs[j - 1];
    }
    mConfigs[i] = ptc;
    return i;
}

void PlayerTrackConfigList::AddPlaceholderConfig(const UserGuid &u, int i, bool b) {
    AddConfig(u, kTrackNone, -1, i, b);
}

void PlayerTrackConfigList::UpdateConfig(
    const UserGuid &u, TrackType ty, int i, int j, bool b
) {
    GetConfigByUserGuid(u).Update(ty, i, j, b);
}

void PlayerTrackConfigList::ProcessConfig(const UserGuid &u) {
    ProcessConfig(GetConfigByUserGuid(u));
}

void PlayerTrackConfigList::RemoveConfig(const UserGuid &u) {
    for (int i = 0; i < mConfigs.size(); i++) {
        if (ConfigAt(i).mUserGuid == u) {
            int tracknum = mConfigs[i].TrackNum();
            if (tracknum != -1) {
                mTrackOccupied[tracknum] = 0;
            }
            mConfigs.erase(mConfigs.begin() + i);
            return;
        }
    }
}

bool PlayerTrackConfigList::UserPresent(const UserGuid &u) {
    for (int i = 0; i < mConfigs.size(); i++) {
        if (ConfigAt(i).mUserGuid == u)
            return true;
    }
    return false;
}

const UserGuid &PlayerTrackConfigList::TrackPlayer(int trk) const {
    for (int i = 0; i < mConfigs.size(); i++) {
        if (trk == mConfigs[i].TrackNum())
            return ConfigAt(i).mUserGuid;
    }
    return gNullUserGuid;
}

bool PlayerTrackConfigList::TrackUsed(int trk) const {
    return !TrackPlayer(trk).IsNull();
}

void PlayerTrackConfigList::ChangeDifficulty(const UserGuid &u, int i) {
    PlayerTrackConfig &cfg = GetConfigByUserGuid(u);
    cfg.Update(cfg.GetTrackType(), i, cfg.Slot(), cfg.Remote());
    mTrackDiffs[cfg.TrackNum()] = i;
}

const UserGuid &PlayerTrackConfigList::GetUserGuidByIndex(int idx) const {
    return mConfigs[idx].mUserGuid;
}

PlayerTrackConfig &PlayerTrackConfigList::GetConfigByUserGuid(const UserGuid &u) const {
    for (int i = 0; i < mConfigs.size(); i++) {
        PlayerTrackConfig &cur = (PlayerTrackConfig &)mConfigs[i];
        if (cur.mUserGuid == u)
            return cur;
    }
    MILO_FAIL("Couldn't find config for user %s", u.ToString());
    return (PlayerTrackConfig &)mConfigs.front();
}

PlayerTrackConfig &PlayerTrackConfigList::GetConfigByUserGuid(const UserGuid &u) {
    for (int i = 0; i < mConfigs.size(); i++) {
        PlayerTrackConfig &cur = mConfigs[i];
        if (cur.mUserGuid == u)
            return cur;
    }
    MILO_FAIL("Couldn't find config for user %s", u.ToString());
    return mConfigs.front();
}

void PlayerTrackConfigList::SetAutoVocals(bool b) { mAutoVocals = b; }
bool PlayerTrackConfigList::GetAutoVocals() const { return mAutoVocals; }
void PlayerTrackConfigList::SetUseVocalHarmony(bool b) { mUseVocalHarmony = b; }
bool PlayerTrackConfigList::UseVocalHarmony() const { return mUseVocalHarmony; }
int PlayerTrackConfigList::NumSingers() const { return 3; }
void PlayerTrackConfigList::SetUseRealDrums(bool b) { mUseRealDrums = b; }
bool PlayerTrackConfigList::UseRealDrums() const { return mUseRealDrums; }
void PlayerTrackConfigList::SetGameCymbalLanes(unsigned int ui) { mGameCymbalLanes = ui; }
unsigned int PlayerTrackConfigList::GetGameCymbalLanes() const {
    return mGameCymbalLanes;
}

UserGuid &PlayerTrackConfigList::InstrumentPlayer(SongInfoAudioType ty, int i) const {
    for (int idx = 0; idx < mConfigs.size(); idx++) {
        TrackType trackty = mConfigs[idx].GetTrackType();
        if (trackty != kTrackNone && TrackTypeToAudioType(trackty) == ty) {
            if (i == 0)
                return (UserGuid &)ConfigAt(idx).mUserGuid;
            i--;
        }
    }
    return gNullUserGuid;
}

void PlayerTrackConfigList::Process(std::vector<TrackType> &tracktypes) {
    MILO_ASSERT(!mProcessed, 0x14D);
    MILO_ASSERT(mTrackTypes.empty(), 0x14E);
    mTrackTypes = tracktypes;
    int size = mTrackTypes.size();
    mTrackDiffs.reserve(size);
    mTrackNums.reserve(size);
    mTrackOccupied.reserve(size);
    for (int i = 0; i < size; i++) {
        mTrackDiffs.push_back(mDefaultDifficulty);
        mTrackNums.push_back(i);
        mTrackOccupied.push_back(0);
    }
    if (mNeedsProcessing) {
        for (int i = 0; i < mConfigs.size(); i++) {
            ProcessConfig(mConfigs[i]);
        }
        mProcessed = true;
    }
}

int PlayerTrackConfigList::TrackNumOfExactType(TrackType ty) {
    for (int i = 0; i < mTrackTypes.size(); i++) {
        if (ty == mTrackTypes[i] && mTrackOccupied[i] == 0)
            return i;
    }
    return -1;
}

int PlayerTrackConfigList::TrackNumOfType(TrackType ty) {
    if (mTrackTypes.empty()) {
        MILO_FAIL(
            "Attempt to call PlayerTrackConfigList::TrackNumOfType before song is loaded"
        );
    }
    int num = TrackNumOfExactType(ty);
    if (num != -1)
        return num;
    else {
        switch (ty) {
        case kTrackRealGuitar22Fret:
            num = TrackNumOfExactType(kTrackRealGuitar);
            break;
        case kTrackRealBass22Fret:
            num = TrackNumOfExactType(kTrackRealBass);
            break;
        default:
            num = -1;
            break;
        }
    }
    return num;
}

void PlayerTrackConfigList::ProcessConfig(PlayerTrackConfig &cfg) {
    TrackType ty = cfg.mTrackType;
    if (ty != kTrackNone) {
        int diff = cfg.mDifficulty;
        int num = TrackNumOfType(ty);
        if (num != -1) {
            cfg.mTrackNum = num;
            mTrackDiffs[num] = diff;
            mTrackOccupied[num] = 1;
        } else {
            MILO_FAIL(
                "Couldn't create track of type %s. Either songs.dta claims it exists but it doesn't, or you're trying to play head-to-head, which is obsolete.",
                TrackTypeToSym(ty)
            );
        }
    }
}

DECOMP_FORCEACTIVE(
    PlayerTrackConfigList,
    "Player %s: ",
    "(remote) ",
    "%s, diff %d, track %d\n",
    "Track %d is diff %d, came from track %d\n"
)