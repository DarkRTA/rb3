#ifndef TOUR_GIGFILTER_H
#define TOUR_GIGFILTER_H
#include "system/obj/Data.h"
#include "meta_band/SongSortMgr.h"

class GigFilter {
public:
    GigFilter();
    virtual ~GigFilter();

    void Init(const DataArray*);
    Symbol GetName() const;
    bool IsInternal() const;
    const SongSortMgr::SongFilter& GetFilter() const;
    Symbol GetFilteredPartSym() const;
    // void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, int, Symbol) const;
    float GetWeight() const;

    Symbol mName;       // 0x04
    bool mIsInternal;   // 0x08
    SongSortMgr::SongFilter mFilter; // 0xc
    Symbol mFilteredPartSym; // 0x20
    float mWeight; // 0x24
};

#endif // TOUR_GIGFILTER_H