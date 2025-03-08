#include "meta_band/SongSortByRank.h"

RankCmp::RankCmp(int val, const char *name, RankCmp::RankType ty)
    : mVal(val), mSongName(name), mType(ty) {}