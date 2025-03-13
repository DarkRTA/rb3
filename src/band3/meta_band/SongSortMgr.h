#pragma once
#include "SongSortByRecent.h"
#include "SongSortByReview.h"
#include "beatmatch/TrackType.h"
#include "meta/StoreOffer.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SetlistSortByLocation.h"
#include "meta_band/SongRecord.h"
#include "meta_band/SongSortByArtist.h"
#include "meta_band/SongSortByDiff.h"
#include "meta_band/SongSortByPlays.h"
#include "meta_band/SongSortByRank.h"
#include "meta_band/SongSortBySong.h"
#include "meta_band/SongSortByStars.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include <vector>
#include <set>

enum FilterType {
    kFilterDifficulty = 0,
    kFilterVocalParts = 1,
    kFilterLength = 2,
    kFilterSource = 3,
    kFilterRating = 4,
    kFilterDecade = 5,
    kFilterGenre = 6,
    // some missing enums here
    kNumFilterTypes = 0xB
};

enum SongSortType {
    kSongSortBySong = 0,
    kSongSortByArtist = 1,
    kSongSortByDiff = 2,
    kSongSortByStars = 3,
    kSongSortByRank = 4,
    kSongSortByRecent = 5,
    kSongSortByPlays = 6,
    kSongSortByReview = 7,
    kSetlistSortByLocation = 8,
    kNumSongSortTypes = 9
};

class SongSortMgr {
public:
    class SongFilter {
    public:
        SongFilter() : requiredTrackType(kTrackNone) { filters.resize(0xB); }
        ~SongFilter() {}

        SongFilter &operator=(const SongFilter &rhs) {
            filters = rhs.filters;
            requiredTrackType = rhs.requiredTrackType;
            excludedSongs = rhs.excludedSongs;
            return *this;
        }

        const std::set<Symbol> &GetFilterSet(FilterType type) const {
            MILO_ASSERT_RANGE(type, 0, kNumFilterTypes, 0x66);
            return filters[type];
        }

        void AddFilter(FilterType type, Symbol s) {
            MILO_ASSERT_RANGE(type, 0, kNumFilterTypes, 0x5E);
            filters[type].insert(s);
        }

        void ClearFilter(int idx) { filters[idx].clear(); }

        void Reset() {
            for (int i = 0; i < 11; i++)
                ClearFilter(i);
            requiredTrackType = kTrackNone;
            excludedSongs.clear();
        }

        std::vector<std::set<Symbol> > filters; // 0x0
        TrackType requiredTrackType; // 0x8
        std::vector<int> excludedSongs; // 0xc
    };

    SongSortMgr();
    virtual ~SongSortMgr();

    bool DoesSongMatchFilter(int, const SongFilter *, Symbol) const;
    void BuildSortTree(SongSortType);
    void BuildSortList(SongSortType);
    void ClearAllSorts();
    bool InqSongsForSetlist(Symbol, std::vector<Symbol> &);
    void BuildSetlistList();
    void BuildInternalSetlists();

    static void Init();

    std::map<Symbol, SongRecord> mSongs; // 0x4
    std::map<Symbol, SetlistRecord> mSetlists; // 0x1c
    std::vector<StoreOffer *> unk34;
    std::vector<SavedSetlist *> unk3c;
    NodeSort *mSorts[kNumSongSortTypes]; // 0x44
};

extern SongSortMgr *TheSongSortMgr;
