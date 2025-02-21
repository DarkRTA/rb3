#pragma once
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/SongData.h"
#include "beatmatch/TrackType.h"
#include "game/Defines.h"
#include "system/utl/HxGuid.h"

class PlayerScoreInfo {
public:
    PlayerScoreInfo(TrackType a, Difficulty b, int c, int d, int e)
        : mTrackType(a), mDifficulty(b), unk8(c), unkc(d), unk10(e) {}
    TrackType mTrackType; // 0x0
    Difficulty mDifficulty; // 0x4
    int unk8; // 0x8 - max streak points?
    int unkc; // 0xc - max points?
    int unk10; // 0x10
    std::vector<int> unk14; // 0x14
};

class MultiplayerAnalyzer {
public:
    class GemScore {
    public:
        GemScore() : unk0(0), unk4(0) {}
        GemScore(int i, float f) : unk0(i), unk4(f) {}
        int unk0; // tick?
        float unk4; // score?
    };

    class Data {
    public:
        Data() {}
        void SetUserGuid(const UserGuid &u) { mGuid = u; }
        UserGuid mGuid; // 0x0
        TrackType mTrackType; // 0x10
        Difficulty mDifficulty; // 0x14
        float mMaxStreakPts; // 0x18
        float mMaxPts; // 0x1c
        float unk_0x20; // 0x20
        float unk_0x24; // 0x24
        int mHeadPoints; // 0x28
        int mTailPoints; // 0x2c
        int mChordPoints; // 0x30
        int mMaxMultiplier; // 0x34
        std::vector<GemScore> mGemScores; // 0x38
    };

    MultiplayerAnalyzer(SongData *);
    void PostLoad();
    int TotalBasePoints() const;
    void AddUser(const UserGuid &);
    float GetMaxPoints(const UserGuid &) const;
    float GetMaxStreakPoints(const UserGuid &) const;
    float GetBonusPoints(const UserGuid &) const;

    void AddTrack(int, TrackType);
    void AddGem(int, const GameGem &);
    void AddSolo(const UserGuid &, int);
    void AddSolos();
    void GetCodaExtents(const UserGuid &, int &, int &);
    void AddGems();
    void AddCodas();
    void OverrideBasePoints(int, TrackType, const UserGuid &, int, int, int);
    void Configure(PlayerTrackConfigList *);

    const Data *GetData(const UserGuid &) const;
    Data *GetData(const UserGuid &);

    const char *mName; // 0x0
    SongData *mSongData; // 0x4
    std::vector<Data> mDatas; // 0x8
    std::vector<PlayerScoreInfo> mScoreInfos; // 0x10 - base scores?
    PlayerTrackConfigList *mConfig; // 0x18
    int mNumPlayers; // 0x1c
};
