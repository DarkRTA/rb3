#include "meta_band/SongSortMgr.h"
#include "SongSortByRecent.h"
#include "SongSortByReview.h"
#include "decomp.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SetlistSortByLocation.h"
#include "meta_band/SongRecord.h"
#include "meta_band/SongSort.h"
#include "meta_band/SongSortByArtist.h"
#include "meta_band/SongSortByDiff.h"
#include "meta_band/SongSortByPlays.h"
#include "meta_band/SongSortByRank.h"
#include "meta_band/SongSortBySong.h"
#include "meta_band/SongSortByStars.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "stl/_pair.h"
#include "utl/Symbols3.h"

SongSortMgr *TheSongSortMgr;

void SongSortMgr::Init() {
    MILO_ASSERT(!TheSongSortMgr, 0x29);
    TheSongSortMgr = new SongSortMgr();
}

DECOMP_FORCEACTIVE(SongSortMgr, "TheSongSortMgr")

SongSortMgr::SongSortMgr() {
    mSorts[kSongSortByDiff] = new SongSortByDiff();
    mSorts[kSongSortBySong] = new SongSortBySong();
    mSorts[kSongSortByArtist] = new SongSortByArtist();
    mSorts[kSongSortByStars] = new SongSortByStars();
    mSorts[kSongSortByRank] = new SongSortByRank();
    mSorts[kSongSortByRecent] = new SongSortByRecent();
    mSorts[kSongSortByPlays] = new SongSortByPlays();
    mSorts[kSongSortByReview] = new SongSortByReview();
    mSorts[kSetlistSortByLocation] = new SetlistSortByLocation();
}

SongSortMgr::~SongSortMgr() {
    for (int i = 0; i < kNumSongSortTypes; i++) {
        RELEASE(mSorts[i]);
    }
}

void SongSortMgr::BuildSetlistList() {
    mSetlists.clear();
    if (unk3c.empty()) {
        BuildInternalSetlists();
    }
    FOREACH (it, unk3c) {
        SetlistRecord record(*it);
        Symbol token = record.GetToken();
        mSetlists.insert(std::make_pair(token, record));
    }
    std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
    FOREACH (pit, profiles) {
        const std::vector<LocalSavedSetlist *> &setlists = (*pit)->GetSavedSetlists();
        FOREACH (it, setlists) {
            SetlistRecord record(*it);
            Symbol token = record.GetToken();
            mSetlists.insert(std::make_pair(token, record));
        }
    }
    if (TheMusicLibrary->NetSetlistsSucceeded()) {
        std::vector<NetSavedSetlist *> setlists;
        TheMusicLibrary->GetNetSetlists(setlists);
        FOREACH (it, setlists) {
            SetlistRecord record(*it);
            Symbol token = record.GetToken();
            mSetlists.insert(std::make_pair(token, record));
        }
    }
    MILO_ASSERT(mSetlists.size(), 0xF0);
}

void SongSortMgr::BuildSortTree(SongSortType ty) {
    if (ty == kSetlistSortByLocation) {
        SetlistSortByLocation *sort =
            dynamic_cast<SetlistSortByLocation *>(mSorts[kSetlistSortByLocation]);
        MILO_ASSERT(sort, 0xF8);
        sort->BuildSetlistTree(mSetlists);
    } else {
        SongSort *sort = dynamic_cast<SongSort *>(mSorts[ty]);
        MILO_ASSERT(sort, 0xFE);
        sort->BuildSongTree(mSongs, unk34);
    }
}

void SongSortMgr::BuildSortList(SongSortType ty) {
    if (ty == kSetlistSortByLocation) {
        SetlistSortByLocation *sort =
            dynamic_cast<SetlistSortByLocation *>(mSorts[kSetlistSortByLocation]);
        MILO_ASSERT(sort, 0x108);
        sort->BuildSetlistList();
    } else {
        SongSort *sort = dynamic_cast<SongSort *>(mSorts[ty]);
        MILO_ASSERT(sort, 0x10E);
        sort->BuildSongList();
    }
}

void SongSortMgr::ClearAllSorts() {
    for (int i = 0; i < kNumSongSortTypes; i++) {
        mSorts[i]->DeleteList();
        mSorts[i]->DeleteTree();
        mSorts[i]->Clear();
    }
}

bool SongSortMgr::InqSongsForSetlist(Symbol s, std::vector<Symbol> &songVector) {
    MILO_ASSERT(songVector.empty(), 0x120);
    DataArray *cfg = SystemConfig(song_select, internal_setlists);
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *arr = cfg->Array(i);
        if (arr->Sym(0) == s) {
            DataArray *songsArr = arr->FindArray(songs, true);
            for (int j = 1; j < songsArr->Size(); j++) {
                Symbol curSym = songsArr->Sym(j);
                songVector.push_back(curSym);
            }
            return true;
        }
    }
    return false;
}