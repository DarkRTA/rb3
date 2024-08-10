#ifndef BEATMATCH_SONGDATA_H
#define BEATMATCH_SONGDATA_H
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/GemListInterface.h"
#include "beatmatch/HxSongData.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/BeatMatchUtl.h"
#include "beatmatch/RGChords.h"
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

        Symbol mName;
        TickedInfoCollection<String>* mLyrics; // fix type
        BeatmatchAudioType mAudioType;
        AudioTrackNum mAudioTrackNum;
        TrackType mType;
        bool mIndependentSlots;
    };

    class BackupTrack {
    public:
        BackupTrack() : mOriginalTrack(0), mGems(0), mMixes(0) {}
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
    virtual TempoMap* GetTempoMap() const {
        return mTempoMap;
    }
    virtual BeatMap* GetBeatMap() const;
    virtual MeasureMap* GetMeasureMap() const;
    virtual void SetTrack(Symbol);
    virtual bool GetGem(int, int&, int&, int&);

    bool GetTrillSlotsAtTick(int, int, std::pair<int, int>&) const;
    int GetRollingSlotsAtTick(int, int) const;
    bool GetNextRoll(int, int, unsigned int&, int&) const;
    const char* SongFullPath() const;
    void AddSink(SongParserSink*);
    void FixUpTrackConfig(PlayerTrackConfigList*);
    void SetUpTrackDifficulties(PlayerTrackConfigList*);
    void UpdatePlayerTrackConfigList(PlayerTrackConfigList*);
    void ComputeVocalRangeData();
    unsigned int GetGameCymbalLanes() const;

    GameGemList* GetGemList(int);
    AudioTrackNum GetAudioTrackNum(int) const;
    void Load(SongInfo*, int, PlayerTrackConfigList*, std::vector<MidiReceiver*>&, bool, SongDataValidate);
    bool Poll();

    int unkc; // 0xc
    int unk10; // 0x10
    int unk14; // 0x14
    bool unk18; // 0x18
    int unk1c; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
    bool unk28; // 0x28
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
    PhraseAnalyzer* unk94; // 0x94
    int unk98; // 0x98
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
    int unkd8; // 0xd8
    int unkdc; // 0xdc
    int unke0; // 0xe0
    String unke4; // 0xe4
    std::map<int, float> mapf0; // 0xf0
    std::vector<RangeSection> mRangeSections;
    std::vector<std::vector<RangeSection> > mKeyboardRangeSections;
    int unk118;
    int unk11c;
    bool unk120;
};

#endif
