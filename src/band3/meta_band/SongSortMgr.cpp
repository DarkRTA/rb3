#include "meta_band/SongSortMgr.h"
#include "SongSortByRecent.h"
#include "SongSortByReview.h"
#include "SongSortMgr.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "meta_band/BandSongMgr.h"
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
#include "utl/BinStream.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

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

void SongSortMgr::SongFilter::IntersectFilter(SongSortMgr::SongFilter *filter) {
    MILO_ASSERT(filter, 0x51);
    FOREACH (it, filter->excludedSongs) {
        filter->excludedSongs.push_back(*it); // ???
    }
    for (int i = 0; i < kNumFilterTypes; i++) {
        std::set<Symbol> &curSet = filter->filters[i];
        bool otherHasFilt = filter->HasFilterType((FilterType)i);
        if (HasFilterType((FilterType)i) && otherHasFilt) {
            std::vector<Symbol> v20;
            FOREACH_CONST_POST (it, filters[i]) {
                Symbol cur = *it;
                if (!HasFilter((FilterType)i, cur)) {
                    v20.push_back(cur);
                }
            }
            FOREACH (it, v20) {
                RemoveFilter((FilterType)i, *it);
            }
            if (!HasFilterType((FilterType)i)) {
                MILO_WARN("Intersecting filters has resulted in an empty filter type!");
            }
        } else if (otherHasFilt) {
            FOREACH_CONST_POST (it, curSet) {
                AddFilter((FilterType)i, *it);
            }
        }
    }
}

void SongSortMgr::BuildSetlistList() {
    mSetlists.clear();
    if (mInternalSetlists.empty()) {
        BuildInternalSetlists();
    }
    FOREACH (it, mInternalSetlists) {
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

void SongSortMgr::BuildInternalSetlists() {
    DataArray *cfg = SystemConfig(song_select, internal_setlists);
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *curArr = cfg->Array(i);
        bool visible = curArr->FindInt(music_library_visible);
        if (visible) {
            Symbol titleSym = curArr->Sym(0);
            Symbol descSym = curArr->FindSym(desc);
            InternalSavedSetlist *setlist = new InternalSavedSetlist(titleSym, descSym);
            DataArray *dateArr = curArr->FindArray(date, true);
            setlist->SetDateTime(
                DateTime(dateArr->Int(1), dateArr->Int(2), dateArr->Int(3), 0, 0, 0)
            );
            bool b1 = false;
            DataArray *songsArr = curArr->FindArray(songs, true);

            int songArrIdx = 1;
            while (songArrIdx < songsArr->Size()) {
                int songID =
                    TheSongMgr.GetSongIDFromShortName(songsArr->Sym(songArrIdx), false);
                if (songID != 0) {
                    setlist->AddSong(songID);
                    b1 = true;
                    songArrIdx++;
                } else
                    songsArr->Remove(songArrIdx);
            }
            if (b1) {
                mInternalSetlists.push_back(setlist);
            } else {
                delete setlist;
                cfg->Remove(i);
                i--;
            }
        }
    }
}

void SongSortMgr::ClearInternalSetlists() {
    FOREACH (it, mInternalSetlists) {
        delete *it;
    }
    mInternalSetlists.clear();
}

NodeSort *SongSortMgr::GetSort(SongSortType ty) { return mSorts[ty]; }

SongRecord *SongSortMgr::GetRecord(int songID) {
    if (TheSongMgr.Data(songID)) {
        Symbol theShortname = TheSongMgr.GetShortNameFromSongID(songID, false);
        if (theShortname != gNullStr) {
            // return &mSongs[theShortname];
        }
    }
    return nullptr;
}

bool SongSortMgr::IsSetlistSort(SongSortType ty) { return ty == kSetlistSortByLocation; }

bool SongSortMgr::SongSortMgr::IsValidNextSortTransition(
    SongSortType ty1, SongSortType ty2
) {
    if (ty1 == ty2)
        return true;
    else if ((ty1 == kSetlistSortByLocation && ty2 != kSetlistSortByLocation)
             || (ty1 != kSetlistSortByLocation && ty2 == kSetlistSortByLocation))
        return false;
    else
        return true;
}

BinStream &operator<<(BinStream &bs, const SongSortMgr::SongFilter &filt) {
    bs << filt.excludedSongs;
    bs << filt.requiredTrackType;
    for (int i = 0; i < kNumFilterTypes; i++) {
        const std::set<Symbol> &curSet = filt.filters[i];
        bs << curSet.size();
        FOREACH (it, curSet) {
            Symbol cur = *it;
            bs << cur;
        }
    }
    return bs;
}

BinStream &operator>>(BinStream &bs, SongSortMgr::SongFilter &filt) {
    bs >> filt.excludedSongs;
    int t = 0;
    bs >> t;
    filt.requiredTrackType = (TrackType)t;
    for (int i = 0; i < kNumFilterTypes; i++) {
        int curSize = 0;
        bs >> curSize;
        for (int j = 0; j < curSize; j++) {
            Symbol s = gNullStr;
            bs >> s;
            filt.AddFilter((FilterType)i, s);
        }
    }
    return bs;
}