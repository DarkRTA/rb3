#include "ScoreUtl.h"
#include "BandUser.h"
#include "BandUserMgr.h"
#include "Scoring.h"

int GetStarsForScore(int score, const UserGuid &guid) {
    BandUser *user = TheBandUserMgr->GetBandUser(guid, true);
    TrackType type = user->GetTrackType();

    int stars = TheScoring->GetSoloNumStars(score, type);

    return stars;
}