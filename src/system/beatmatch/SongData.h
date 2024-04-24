#ifndef BEATMATCH_SONGDATA_H
#define BEATMATCH_SONGDATA_H
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/GemListInterface.h"
#include "beatmatch/HxSongData.h"
#include "beatmatch/GameGemList.h"
#include "BeatMatch/BeatMatchUtl.h"
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
class TempoMap;
class MeasureMap;
class BeatMap;
class TuningOffsetList;
class TickedInfoCollection;
class DrumFillInfo;

class SongData : public InternalSongParserSink, public GemListInterface, public HxSongData {
public:
    class TrackInfo {
    public:
        Symbol mName;
        TickedInfoCollection* mLyrics;
        BeatmatchAudioType mAudioType;
        AudioTrackNum mAudioTrackNum;
        TrackType mType;
        bool mIndependentSlots;
    };

    class BackupTrack {
    public:
        int mOriginalTrack;
        GameGemDB* mGems;
        DrumMixDB* mMixes;
    };

    class FakeTrack {
    public:
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
    virtual TempoMap* GetTempoMap() const;
    virtual BeatMap* GetBeatMap() const;
    virtual MeasureMap* GetMeasureMap() const;

    virtual void SetTrack(Symbol);
    virtual bool GetGem(int, int&, int&, int&);

    bool GetTrillSlotsAtTick(int, int, std::pair<int, int>&) const;
    int GetRollingSlotsAtTick(int, int) const;
    bool GetNextRoll(int, int, unsigned int&, int&) const;

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
    std::vector<int> vec44; // just an int, nice
    std::vector<DrumFillInfo*> mFills;
    std::vector<DrumMap*> mDrumMaps;
    std::vector<int> vec5c; // RangedDataCollection<unsigned int>*
    std::vector<int> vec64; // RangedDataCollection<std::pair<int, int>>*
    std::vector<int> vec6c; // RangedDataCollection<RGRollChord>*
    std::vector<int> vec74; // RangedDataCollection<RGTrill>*
    std::vector<DrumMixDB*> mDrumMixDBs;
    std::vector<GameGemDB*> mGemDBs;
    std::vector<PhraseDB*> mPhraseDBs;
    int unk94; // actually a PhraseAnalyzer
    int unk98;
    std::vector<VocalNoteList*> mVocalNoteLists;
    std::vector<BackupTrack*> mBackupTracks;
    std::vector<FakeTrack*> mFakeTracks;
    TempoMap* mTempoMap;
    MeasureMap* mMeasureMap;
    BeatMap* mBeatMap;
    TuningOffsetList* mTuningOffsetList;
    std::vector<float> vecc4; // float
    std::vector<float> veccc; // float
    float unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    String unke4;
    std::map<int, float> mapf0;
    std::vector<int> mRangeSections; // RangeSection
    std::vector<int> unk110; // std::vector<RangeSection> - a vector of vectors, gg hmx
    int unk118;
    int unk11c;
    bool unk120;
};

#endif
