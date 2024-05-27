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

};

enum TrackType {

};

TrackType ScoreTypeToTrackType(ScoreType scoreType);
ControllerType TrackTypeToControllerType(TrackType trackType);

#endif // GAME_DEFINES_H