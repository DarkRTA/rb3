#ifndef BEATMATCH_SONGDATA_H
#define BEATMATCH_SONGDATA_H
#include "beatmatch/FillInfo.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/GemListInterface.h"
#include "beatmatch/HxSongData.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/BeatMatchUtl.h"
#include "beatmatch/Phrase.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/SongParser.h"
#include "utl/MemStream.h"
#include "utl/RangedData.h"
#include "utl/TickedInfo.h"
#include "utl/TempoMap.h"
#include <vector>
#include <map>

// forward decs
class SongInfo;
class SongParserSink;
class BeatMatcher;
class DrumMap;
class DrumMixDB;
class GameGemDB;
class PhraseDB;
class VocalNoteList;
class MeasureMap;
class BeatMap;
class TuningOffsetList;
class DrumFillInfo;
class PlayerTrackConfigList;
class PhraseAnalyzer;
class MidiReceiver;

enum SongDataValidate {
    kSongData_NoValidation,
    kSongData_ValidateUsingNameOnly,
    kSongData_Validate
};

class SongData : public InternalSongParserSink, public GemListInterface, public HxSongData {
public:
    class TrackInfo {
    public:
        TrackInfo(Symbol, SongInfoAudioType, AudioTrackNum, TrackType, bool);
        ~TrackInfo();

        bool FakeAudio() const { return mAudioType == kAudioFake; }

        Symbol mName; // 0x0
        TickedInfoCollection<String>* mLyrics; // 0x4
        BeatmatchAudioType mAudioType; // 0x8
        AudioTrackNum mAudioTrackNum; // 0xc
        TrackType mType; // 0x10
        bool mIndependentSlots; // 0x14
    };

    class BackupTrack {
    public:
        BackupTrack() : mOriginalTrack(0), mGems(0), mMixes(0) {}
        BackupTrack(int trk, GameGemDB* g, DrumMixDB* d) : mOriginalTrack(trk), mGems(g), mMixes(d) {}
        ~BackupTrack();

        int mOriginalTrack;
        GameGemDB* mGems;
        DrumMixDB* mMixes;
    };

    class FakeTrack {
    public:
        FakeTrack(Symbol);
        ~FakeTrack();
        Symbol mName;
        GameGemDB* mGems;
    };

    SongData();
    virtual ~SongData();
    virtual void AddTrack(int, AudioTrackNum, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void ClearTrack(int);
    virtual void OnEndOfTrack(int, bool);
    virtual void AddMultiGem(int, const MultiGemInfo&);
    virtual void AddRGGem(int, const RGGemInfo&);
    virtual void AddVocalNote(const VocalNote&);
    virtual void AddPitchOffset(int, float);
    virtual void AddLyricShift(int);
    virtual void OnTambourineGem(int);
    virtual void StartVocalPlayerPhrase(int, int);
    virtual void EndVocalPlayerPhrase(int, int);
    virtual void AddPhrase(BeatmatchPhraseType, int, int, float, int, float, int);
    virtual void AddDrumFill(int, int, int, int, bool);
    virtual void AddRoll(int, int, unsigned int, int, int);
    virtual void AddTrill(int, int, int, int, int, int);
    virtual void AddRGRoll(int, int, const RGRollChord&, int, int);
    virtual void AddRGTrill(int, int, const RGTrill&, int, int);
    virtual void AddMix(int, int, int, const char*);
    virtual void AddLyricEvent(int, int, const char*);
    virtual void DrumMapLane(int, int, int, bool);
    virtual void AddBeat(int, int);
    virtual void SetDetailedGrid(bool);
    virtual void AddRangeShift(int, float);
    virtual void AddKeyboardRangeShift(int, int, float, int, int);
    virtual SongPos CalcSongPos(float);
    virtual TempoMap* GetTempoMap() const { return mTempoMap; }
    virtual BeatMap* GetBeatMap() const;
    virtual MeasureMap* GetMeasureMap() const;
    virtual void SetTrack(Symbol);
    virtual bool GetGem(int, int&, int&, int&);

    bool GetTrillSlotsAtTick(int, int, std::pair<int, int>&) const;
    unsigned int GetRollingSlotsAtTick(int, int) const;
    bool GetNextRoll(int, int, unsigned int&, int&) const;
    bool GetNextRGRoll(int, int, RGRollChord&, int&) const;
    const char* SongFullPath() const;
    void AddSink(SongParserSink*);
    void FixUpTrackConfig(PlayerTrackConfigList*);
    void SetUpTrackDifficulties(PlayerTrackConfigList*);
    void UpdatePlayerTrackConfigList(PlayerTrackConfigList*);
    void ComputeVocalRangeData();
    unsigned int GetGameCymbalLanes() const;
    void PostLoad(PlayerTrackConfigList*);
    void MakeBackupTracks();
    void RestoreAllTracksFromBackup();
    GameGemList* GetGemList(int);
    GameGemList* GetGemListByDiff(int, int);
    AudioTrackNum GetAudioTrackNum(int) const;
    void Load(SongInfo*, int, PlayerTrackConfigList*, std::vector<MidiReceiver*>&, bool, SongDataValidate);
    void Load(const char*, SongInfo*, int, PlayerTrackConfigList*, std::vector<MidiReceiver*>&, bool);
    void PostLoadTrack(int);
    bool Poll();
    void PostLoadVocals();
    void SendPhrases(int);
    void SendGems(int);
    void ChangeTrackDiff(int, int);
    void ValidateVocalSPPhrases();
    void UnflipGems(int, int, int);
    void RestoreGems(int, int, int);
    void TrimOverlappingGems(int, int, int);
    bool HasBackupTrack(int) const;
    void RestoreTrackFromBackup(int);
    Symbol TrackName(int) const;
    int TrackNamed(Symbol) const;
    DrumFillInfo* GetDrumFillInfo(int);
    FillInfo* GetFillInfo(int);
    bool GetUsingRealDrums() const;
    void SetFakeHitGemsInFill(bool);
    bool GetFakeHitGemsInFill() const;
    TickedInfoCollection<String>& GetSubmixes(int) const;
    void EnableGems(int, float, float);
    void RecalculateGemTimes(int);
    RangedDataCollection<RGRollChord>* GetRGRollInfo(int) const;
    RangedDataCollection<RGTrill>* GetRGTrillInfo(int) const;
    RangedDataCollection<std::pair<int, int> >* GetTrillInfo(int) const;
    RangedDataCollection<unsigned int>* GetRollInfo(int) const;
    bool RollStartsAt(int, int, int&) const;
    bool TrillStartsAt(int, int, int&);
    bool RGRollStartsAt(int, int, int&) const;
    bool RGTrillStartsAt(int, int, int&);
    bool GetRGTrillAtTick(int, int, RGTrill&) const;
    RGRollChord GetRGRollingSlotsAtTick(int, int) const;
    void AddBeatMatcher(BeatMatcher*);
    void RemoveBeatMatcher(BeatMatcher*);
    void PostDynamicAdd(BeatMatcher*, int);
    const PhraseList& GetPhraseList(int, BeatmatchPhraseType) const;
    TrackType TrackTypeAt(int idx) const {
        return mTrackInfos[idx]->mType;
    }
    bool HasTrackDiffs() const { return mTrackDifficulties.size(); }

    int unkc; // 0xc
    int mNumTracks; // 0x10
    int mNumDifficulties; // 0x14
    bool mLoaded; // 0x18
    SongInfo* mSongInfo; // 0x1c
    int mSectionStartTick; // 0x20
    int mSectionEndTick; // 0x24
    bool mFakeHitGemsInFill; // 0x28
    std::vector<SongParserSink*> mSongParserSinks; // 0x2c
    std::vector<BeatMatcher*> mBeatMatchers; // 0x34
    std::vector<TrackInfo*> mTrackInfos; // 0x3c
    std::vector<int> mTrackDifficulties; // 0x44
    std::vector<DrumFillInfo*> mFills; // 0x4c
    std::vector<DrumMap*> mDrumMaps; // 0x54
    std::vector<RangedDataCollection<unsigned int>*> mRollInfos; // 0x5c
    std::vector<RangedDataCollection<std::pair<int, int> >*> mTrillInfos; // 0x64
    std::vector<RangedDataCollection<RGRollChord>*> mRGRollInfos; // 0x6c
    std::vector<RangedDataCollection<RGTrill>*> mRGTrillInfos; // 0x74
    std::vector<DrumMixDB*> mDrumMixDBs; // 0x7c
    std::vector<GameGemDB*> mGemDBs; // 0x84
    std::vector<PhraseDB*> mPhraseDBs; // 0x8c
    PhraseAnalyzer* mPhraseAnalyzer; // 0x94
    int mLoadingVocalNoteListIndex; // 0x98
    std::vector<VocalNoteList*> mVocalNoteLists; // 0x9c
    std::vector<BackupTrack*> mBackupTracks; // 0xa4
    std::vector<FakeTrack*> mFakeTracks; // 0xac
    TempoMap* mTempoMap; // 0xb4
    MeasureMap* mMeasureMap; // 0xb8
    BeatMap* mBeatMap; // 0xbc
    TuningOffsetList* mTuningOffsetList; // 0xc0
    std::vector<float> vecc4; // 0xc4
    std::vector<float> veccc; // 0xcc
    float unkd4; // 0xd4
    MemStream* mMemStream; // 0xd8
    SongParser* mSongParser; // 0xdc
    PlayerTrackConfigList* mPlayerTrackConfigList; // 0xe0
    String unke4; // 0xe4
    std::map<int, float> mRangeShifts; // 0xf0
    std::vector<RangeSection> mRangeSections; // 0x108
    std::vector<std::vector<RangeSection> > mKeyboardRangeSections; // 0x110
    GameGemList* mGems; // 0x118
    int mHopoThreshold; // 0x11c
    bool mDetailedGrid; // 0x120
};

#endif
