#include "game/CrowdRating.h"

CrowdRating::CrowdRating(BandUser* u, Difficulty d) : unk10(1) {
    Configure(u, d);
    Reset();
}