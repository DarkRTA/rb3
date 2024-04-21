#ifndef BEATMATCH_INTERNALSONGPARSERSINK_H
#define BEATMATCH_INTERNALSONGPARSERSINK_H
#include "utl/Symbol.h"
#include "beatmatch/TrackType.h"
#include "utl/SongInfoAudioType.h"
#include "beatmatch/GemInfo.h"
#include "beatmatch/VocalNote.h"

struct AudioTrackNum {
    int mVal;
};

enum BeatmatchPhraseType {
    kCommonPhrase = 0,
    kSoloPhrase = 1,
    kPlayerOneFocusPhrase = 2,
    kPlayerTwoFocusPhrase = 3,
    kArpeggioPhrase = 4,
    kChordMarkupPhrase = 5,
    kNoPhrase = 6,
    kNumPhraseTypes = 6
};

class InternalSongParserSink {
public:
    InternalSongParserSink(){}
    virtual ~InternalSongParserSink(){}
    virtual void AddTrack(int, AudioTrackNum, Symbol, SongInfoAudioType, TrackType, bool) = 0;
    virtual void ClearTrack(int) = 0;
    virtual void OnEndOfTrack(int, bool) = 0;
    virtual void AddMultiGem(int, const MultiGemInfo&) = 0;
    virtual void AddRGGem(int, const RGGemInfo&) = 0;
    virtual void AddVocalNote(const VocalNote&) = 0;
    virtual void AddPitchOffset(int, float) = 0;
    virtual void AddLyricShift(int) = 0;
    virtual void OnTambourineGem(int) = 0;
    virtual void StartVocalPlayerPhrase(int, int) = 0;
    virtual void EndVocalPlayerPhrase(int, int) = 0;
    virtual void AddPhrase(BeatmatchPhraseType, int, int, float, int, float, int) = 0;
    virtual void AddDrumFill(int, int, int, int, bool) = 0;
    virtual void AddRoll(int, int, unsigned int, int, int) = 0;
    virtual void AddTrill(int, int, int, int, int, int) = 0;
    virtual void AddRGRoll(int, int, const RGRollChord&, int, int) = 0;
    virtual void AddRGTrill(int, int, const RGTrill&, int, int) = 0;
    virtual void AddMix(int, int, int, const char*) = 0;
    virtual void AddLyricEvent(int, int, const char*) = 0;
    virtual void DrumMapLane(int, int, int, bool) = 0;
    virtual void AddBeat(int, int) = 0;
    virtual void SetDetailedGrid(bool) = 0;
    virtual void AddRangeShift(int, float) = 0;
    virtual void AddKeyboardRangeShift(int, int, float, int, int) = 0;
};

#endif
