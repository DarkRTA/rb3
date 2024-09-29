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
    kControllerNone = 3,
    kNumControllerTypes = 3,
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
    kTrackDrum = 0,
    kTrackGuitar = 1, // guess
    kTrackBass = 2, // guess

    kTrack4 = 4,
    kTrackKeyboard = 5,
    kTrackProGuitar = 6,

    kTrackProBass = 8
};

TrackType ScoreTypeToTrackType(ScoreType scoreType);
ControllerType TrackTypeToControllerType(TrackType trackType);
Symbol TrackTypeToSym(TrackType);

#endif // GAME_DEFINES_H