#include "meta_band/SongSortMgr.h"
#include "decomp.h"
#include "os/Debug.h"

SongSortMgr *TheSongSortMgr;

void SongSortMgr::Init() {
    MILO_ASSERT(!TheSongSortMgr, 0x29);
    TheSongSortMgr = new SongSortMgr();
}

DECOMP_FORCEACTIVE(SongSortMgr, "TheSongSortMgr")

SongSortMgr::SongSortMgr() {}