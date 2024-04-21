#ifndef BEATMATCH_SONGDATA_H
#define BEATMATCH_SONGDATA_H
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/GemListInterface.h"
#include "beatmatch/HxSongData.h"
#include "beatmatch/GameGemList.h"

class SongData : public InternalSongParserSink, public GemListInterface, public HxSongData {
public:
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

    GameGemList* GetGemList(int);

    int dummy;
};

#endif
