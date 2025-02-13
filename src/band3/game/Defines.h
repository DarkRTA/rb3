#pragma once
#include "beatmatch/TrackType.h"
#include "utl/Str.h"
#include "utl/Symbol.h"

enum Difficulty {
    kDifficultyEasy = 0,
    kDifficultyMedium = 1,
    kDifficultyHard = 2,
    kDifficultyExpert = 3,
    kNumDifficulties = 4
};

Difficulty DefaultDifficulty();
Symbol DifficultyToSym(Difficulty);
Difficulty SymToDifficulty(Symbol);

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

TrackType ScoreTypeToTrackType(ScoreType scoreType);
ControllerType TrackTypeToControllerType(TrackType trackType);
Symbol TrackTypeToSym(TrackType);
Symbol ControllerTypeToSym(ControllerType);
Symbol ScoreTypeToSym(ScoreType);
ControllerType SymToControllerType(Symbol);
TrackType ControllerTypeToTrackType(ControllerType, bool);
ScoreType TrackTypeToScoreType(TrackType, bool, bool);
ScoreType SymToScoreType(Symbol);
void CensorString(String &);
bool RepresentSamePart(TrackType, TrackType);
Symbol DifficultyToShortSym(Difficulty);
void GetTracksPlayableByController(
    ControllerType ct, std::vector<TrackType> &tracks, class OvershellPanel *panel
);
bool IsTrackPlayableByController(TrackType, ControllerType);
void GetTracksRepresentativeOfPart(TrackType ty, std::vector<TrackType> &tracks);
bool RepresentSamePart(TrackType t1, TrackType t2);
bool IsRepresentativePartPlayableByController(TrackType t, ControllerType c);
bool ControllerHasRepresentativePartPriority(ControllerType, TrackType);