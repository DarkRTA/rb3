#pragma once
#include "beatmatch/TrackType.h"
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

class SongSortMgr {
public:
    class SongFilter {
    public:
        SongFilter() : requiredTrackType(kTrackNone) { filters.resize(0xB); }
        ~SongFilter() {}

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

    static void Init();
};

extern SongSortMgr *TheSongSortMgr;
