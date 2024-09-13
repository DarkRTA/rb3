#ifndef GAME_SCORING_H
#define GAME_SCORING_H

#include "beatmatch/TrackType.h"

class Scoring {
public:
    int GetHeadPoints(TrackType) const;
    int GetTailPoints(TrackType, int) const;
};

extern Scoring TheScoring;

#endif // GAME_SCORING_H