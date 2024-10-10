#ifndef GAME_MULTIPLAYERANALYZER_H
#define GAME_MULTIPLAYERANALYZER_H
#include "beatmatch/SongData.h"
#include "system/utl/HxGuid.h"

class PlayerScoreInfo {};

class MultiplayerAnalyzer {
public:
    class Data {
    public:
        HxGuid mGuid;
        char unk_pre[8];
        float m_maxStreakPoints;
        float m_maxPoints;
        float unk_0x20;
        float unk_0x24;
        char unk_Stuff[24];
    };

    class GemScore {

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
    void OverrideBasePoints(int, TrackType, const UserGuid&, int, int, int);

    const Data *GetData(const UserGuid &) const;
    Data *GetData(const UserGuid &);

    char *mUnk_0x0;
    SongData *mSongData;

    // Whatever type is here is 0x40 size
    std::vector<Data> mUnk_0x8;
    std::vector<PlayerScoreInfo *> mUnk_0x10; // 0x10 - base scores
    int mUnk_0x18;
};

#endif // GAME_MULTIPLAYERANALYZER_H