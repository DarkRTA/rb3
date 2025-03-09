#include "meta_band/SongSortByStars.h"
#include "bandobj/StarDisplay.h"
#include "os/Debug.h"

StarsCmp::StarsCmp(int stars, float rank, const char *name)
    : mStars(stars), mRank(rank), mName(name) {
    mHeaderSym = StarDisplay::GetSymbolForStarCount(stars);
    MILO_ASSERT(!mHeaderSym.Null(), 0x1D);
}