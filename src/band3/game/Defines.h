#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

#include "utl/Symbol.h"

enum Difficulty {
    kDifficultyEasy,
    kDifficultyMedium,
    kDifficultyHard,
    kDifficultyExpert
};

Difficulty DefaultDifficulty();
Symbol DifficultyToSym(Difficulty);

enum ControllerType {
    kControllerDrum = 0,
    kControllerGuitar = 1,
    kControllerVocals = 2,
    kControllerKeys = 3,
    kControllerRealGuitar = 4,
    kControllerNone = 5,
    kNumControllerTypes = 5
};

enum ScoreType {
    kScoreDrum = 0,
    kScoreFirst = 0,
    kScoreBass = 1,
    kScoreGuitar = 2,
    kScoreVocals = 3,
    kScoreHarmony = 4,
    kScoreKeys = 5,
    kScoreRealDrum = 6,
    kScoreRealGuitar = 7,
    kScoreRealBass = 8,
    kScoreRealKeys = 9,
    kScoreBand = 10,
    kNumScoreTypes = 11
};

enum TrackType {
    kTrackDrum,
    kTrackGuitar,
    kTrackBass,
    kTrackVocals,
    kTrackKeys,
    kTrackRealKeys,
    kTrackRealGuitar,
    kTrackRealGuitar22Fret,
    kTrackRealBass,
    kTrackRealBass22Fret,
    kTrackNone,
    kNumTrackTypes,
    kTrackPending,
    kTrackPendingVocals
};

TrackType ControllerTypeToTrackType(ControllerType controllerType, bool isReal);
TrackType ScoreTypeToTrackType(ScoreType scoreType);
ControllerType TrackTypeToControllerType(TrackType trackType);
Symbol TrackTypeToSym(TrackType);

#endif // GAME_DEFINES_H