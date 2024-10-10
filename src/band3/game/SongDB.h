#ifndef GAME_SONGDB_H
#define GAME_SONGDB_H
#include "system/beatmatch/SongData.h"
#include "system/beatmatch/SongParserSink.h"
#include "game/MultiplayerAnalyzer.h"
#include "game/Defines.h"
#include "midi/DataEvent.h"
#include <vector>

class SongDB : public SongParserSink {
public:
    class TrackData {
    public:
        TrackData(TrackType ty) : unk0(ty) {}

        TrackType unk0;
        std::vector<int> unk4;
        std::vector<int> unkc;
        std::vector<int> unk14;
        std::vector<int> unk1c;
        std::vector<int> unk24;
        std::vector<int> unk2c;
        std::vector<int> unk34;
        std::vector<int> unk3c;
    };

    SongDB();
    virtual ~SongDB();
    virtual void SetNumTracks(int);
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void AddMultiGem(int, const GameGem&){}
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase&);

    float GetSongDurationMs() const;
    void ParseEvents(DataEventList*);
    void SpewAllVocalNotes() const;
    void SpewTrackSizes() const;
    void SetupPhrases();
    void DisableCodaGems();
    void RunMultiplayerAnalyzer();
    void SetupPracticeSections();
    void PostLoad(DataEventList*);
    void RebuildPhrases(int);
    void ClearTrackPhrases(int);
    void RebuildData();
    void OverrideBasePoints(int, TrackType, const UserGuid&, int, int, int);
    int TotalBasePoints();
    int GetCodaStartTick() const;
    bool IsInCoda(int) const;
    int GetNumTracks() const;
    int GetNumTrackData() const;
    int GetBaseMaxPoints(const UserGuid&) const;
    int GetBaseMaxStreakPoints(const UserGuid&) const;
    int GetBaseBonusPoints(const UserGuid&) const;
    GameGemList* GetGemList(int) const;
    GameGemList* GetGemListByDiff(int, int) const;
    const std::vector<GameGem>& GetGems(int) const;
    std::vector<RangeSection>& GetRangeSections();
    void ChangeDifficulty(int, Difficulty);
    void SetTrainerGems(int, int);

    SongData* GetSongData() { return mSongData; }

    SongData* mSongData; // 0x4
    std::vector<TrackData> mTrackData; // 0x8
    float mSongDurationMs; // 0x10
    int mCodaStartTick; // 0x14
    MultiplayerAnalyzer* mMultiplayerAnalyzer; // 0x18
    std::vector<int> mPracticeSections; // 0x1c
    int unk24; // 0x24
    int unk28; // 0x28
};

extern SongDB* TheSongDB;

#endif
