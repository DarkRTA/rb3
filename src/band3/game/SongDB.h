#pragma once
#include "beatmatch/DrumMap.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/VocalNote.h"
#include "game/PracticeSectionProvider.h"
#include "system/beatmatch/SongData.h"
#include "system/beatmatch/SongParserSink.h"
#include "game/MultiplayerAnalyzer.h"
#include "game/Defines.h"
#include "midi/DataEvent.h"
#include "game/Player.h"
#include "utl/MBT.h"
#include <vector>

class SongDB : public SongParserSink {
public:
    class TrackData {
    public:
        TrackData(TrackType ty) : mTrackType(ty) {}
        const std::vector<unsigned char> &GetGemStates(BeatmatchPhraseType) const;

        TrackType mTrackType; // 0x0
        std::vector<Extent> mSoloPhraseExtents; // 0x4
        std::vector<Extent> mCommonPhraseExtents; // 0xc
        std::vector<Extent> mArpeggioPhraseExtents; // 0x14
        std::vector<Extent> mChordMarkupPhraseExtents; // 0x1c
        std::vector<unsigned char> unk24; // 0x24
        std::vector<unsigned char> unk2c; // 0x2c
        std::vector<int> unk34; // 0x34
        std::vector<int> unk3c; // 0x3c
    };

    SongDB();
    virtual ~SongDB();
    virtual void SetNumTracks(int);
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void AddMultiGem(int, const GameGem &) {}
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase &);

    float GetSongDurationMs() const;
    void ParseEvents(DataEventList *);
    void SpewAllVocalNotes() const;
    void SpewTrackSizes() const;
    void SetupPhrases();
    void DisableCodaGems();
    void RunMultiplayerAnalyzer();
    void SetupPracticeSections();
    void PostLoad(DataEventList *);
    void RebuildPhrases(int);
    void ClearTrackPhrases(int);
    void RebuildData();
    void OverrideBasePoints(int, TrackType, const UserGuid &, int, int, int);
    int TotalBasePoints();
    int GetCodaStartTick() const;
    bool IsInCoda(int) const;
    int GetNumTracks() const;
    int GetNumTrackData() const;
    int GetBaseMaxPoints(const UserGuid &) const;
    int GetBaseMaxStreakPoints(const UserGuid &) const;
    int GetBaseBonusPoints(const UserGuid &) const;
    const GameGemList *GetGemList(int) const;
    GameGemList *GetGemListByDiff(int, int) const;
    const std::vector<GameGem> &GetGems(int) const;
    std::vector<RangeSection> &GetRangeSections();
    void ChangeDifficulty(int, Difficulty);
    void SetTrainerGems(int, int);
    int GetBeatsPerMeasure(int) const;
    int NumCommonPhrases() const;
    int GetCommonPhraseTracks(int) const;
    int GetCommonPhraseID(int, int) const;
    int GetPhraseID(int, int) const;
    bool IsUnisonPhrase(int) const;
    bool GetCommonPhraseExtent(int, int, Extent &);
    FillInfo *GetFillInfo(int, int);
    const GameGem &GetGem(int, int) const;
    int GetTotalGems(int) const;
    VocalNoteList *GetVocalNoteList(int) const;
    void GetBandFailCue(String &) const;
    void SetFakeHitGemsInFill(bool);
    bool GetPhraseExtents(BeatmatchPhraseType, int, int, int &, int &);
    void ClearQuarantinedPhrases(int);
    void SetupTrackPhrases(int);
    int GetSoloGemCount(int) const;
    int GetSustainGemCount(int) const;
    bool IsInPhrase(BeatmatchPhraseType, int, int) const;
    std::vector<PlayerScoreInfo> &GetBaseScores();
    DrumFillInfo *GetDrumFillInfo(int) const;
    int GetVocalNoteListCount() const;
    std::vector<Extent> &GetExtents(int, BeatmatchPhraseType);
    int GetNumOverdrivePhrases(int) const;
    int GetNumUnisonPhrases(int) const;
    int GetNumPhraseIDs(int) const;
    MBT GetMBT(int) const;
    void SetupSoloPhrasesForTrack(int);
    void SetupCommonPhrasesForTrack(int);
    int NextPhraseIndexAfter(int, int);
    void SetupPhrasesForTrack(int, std::vector<Extent> &, std::vector<unsigned char> &);
    void RecalculateGemTimes(int);
    void EnableGems(int, float, float);
    float GetPitchOffsetForTick(int) const;

    SongData *GetData() const { return mSongData; }

    SongData *mSongData; // 0x4
    std::vector<TrackData> mTrackData; // 0x8
    float mSongDurationMs; // 0x10
    int mCodaStartTick; // 0x14
    MultiplayerAnalyzer *mMultiplayerAnalyzer; // 0x18
    std::vector<PracticeSection> mPracticeSections; // 0x1c
    int unk24; // 0x24
    int unk28; // 0x28
};

extern SongDB *TheSongDB;
