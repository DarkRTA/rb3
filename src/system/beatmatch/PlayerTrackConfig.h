#ifndef BEATMATCH_PLAYERTRACKCONFIG_H
#define BEATMATCH_PLAYERTRACKCONFIG_H
#include "beatmatch/TrackType.h"
#include "utl/HxGuid.h"
#include "utl/SongInfoAudioType.h"
#include "os/Debug.h"
#include <vector>

class PlayerTrackConfig {
public:
    PlayerTrackConfig(const UserGuid &u, TrackType ty, int i, int j, bool b)
        : mUserGuid(u), mTrackType(ty), mDifficulty(i), mSlot(j), mRemote(b),
          mTrackNum(-1) {}

    void Update(TrackType ty, int i, int slot, bool remote) {
        mTrackType = ty;
        mDifficulty = i;
        MILO_ASSERT(mSlot == slot, 0x34);
        MILO_ASSERT(mRemote == remote, 0x35);
    }

    UserGuid mUserGuid; // 0x0
    TrackType mTrackType; // 0x10
    int mDifficulty; // 0x14
    int mSlot; // 0x18
    bool mRemote; // 0x1c
    int mTrackNum; // 0x20
};

class PlayerTrackConfigList {
public:
    PlayerTrackConfigList(int);
    void Reset();
    void AddPlaceholderConfig(const UserGuid &, int, bool);
    void AddConfig(const UserGuid &, TrackType, int, int, bool);
    void UpdateConfig(const UserGuid &, TrackType, int, int, bool);
    void ChangeDifficulty(const UserGuid &, int);
    const UserGuid &GetUserGuidByIndex(int) const;
    PlayerTrackConfig &GetConfigByUserGuid(const UserGuid &) const;
    PlayerTrackConfig &GetConfigByUserGuid(const UserGuid &);
    void SetAutoVocals(bool);
    bool GetAutoVocals() const;
    void SetUseVocalHarmony(bool);
    bool UseVocalHarmony() const;
    int NumSingers() const;
    void SetUseRealDrums(bool);
    bool UseRealDrums() const;
    void SetGameCymbalLanes(unsigned int);
    unsigned int GetGameCymbalLanes() const;
    UserGuid &InstrumentPlayer(SongInfoAudioType, int) const;
    void Process(std::vector<TrackType> &);
    void ProcessConfig(PlayerTrackConfig &);
    void ProcessConfig(const UserGuid &);
    int TrackNumOfExactType(TrackType);
    int TrackNumOfType(TrackType);
    bool TrackUsed(int) const;
    const UserGuid &TrackPlayer(int) const;
    bool UserPresent(const UserGuid &);
    void RemoveConfig(const UserGuid &);

    std::vector<int> mTrackDiffs; // 0x0
    std::vector<int> mTrackNums; // 0x8
    std::vector<TrackType> mTrackTypes; // 0x10
    std::vector<int> mTrackOccupied; // 0x18
    std::vector<PlayerTrackConfig> mConfigs; // 0x20
    bool mAutoVocals; // 0x28
    bool mUseVocalHarmony; // 0x29
    bool mUseRealDrums; // 0x2a
    bool mDiscoUnflip; // 0x2b
    bool unk2c; // 0x2c
    unsigned int mGameCymbalLanes; // 0x30
    bool mUseGHDrums; // 0x34
    int mDefaultDifficulty; // 0x38
    bool mNeedsProcessing; // 0x3c
    bool mProcessed; // 0x3d
};

#endif