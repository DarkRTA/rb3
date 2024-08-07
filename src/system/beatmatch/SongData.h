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

    virtual void CalcSongPos(float);
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

    GameGemList* GetGemList(int);

    int unkc;
    int unk10;
    int unk14;
    bool unk18;
    int unk1c;
    int unk20;
    int unk24;
    bool unk28;
    // fix vector types
    std::vector<SongParserSink*> mSongParserSinks;
    std::vector<BeatMatcher*> mBeatMatchers;
    std::vector<TrackInfo*> mTrackInfos;
    std::vector<int> mTrackDifficulties;
    std::vector<DrumFillInfo*> mFills;
    std::vector<DrumMap*> mDrumMaps;
    std::vector<RangedDataCollection<unsigned int>*> mRollInfos;
    std::vector<RangedDataCollection<std::pair<int, int> >*> mTrillInfos;
    std::vector<RangedDataCollection<RGRollChord>*> mRGRollInfos;
    std::vector<RangedDataCollection<RGTrill>*> mRGTrillInfos;
    std::vector<DrumMixDB*> mDrumMixDBs;
    std::vector<GameGemDB*> mGemDBs;
    std::vector<PhraseDB*> mPhraseDBs;
    int unk94; // actually a PhraseAnalyzer
    int unk98; // 0x98
    std::vector<VocalNoteList*> mVocalNoteLists; // 0x9c
    std::vector<BackupTrack*> mBackupTracks; // 0xa4
    std::vector<FakeTrack*> mFakeTracks; // 0xac
    TempoMap* mTempoMap; // 0xb4
    MeasureMap* mMeasureMap; // 0xb8
    BeatMap* mBeatMap; // 0xbc
    TuningOffsetList* mTuningOffsetList; // 0xc0
    std::vector<float> vecc4; // float
    std::vector<float> veccc; // float
    float unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    String unke4;
    std::map<int, float> mapf0;
    std::vector<RangeSection> mRangeSections;
    std::vector<std::vector<RangeSection> > mKeyboardRangeSections;
    int unk118;
    int unk11c;
    bool unk120;
};

#endif
