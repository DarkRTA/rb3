#ifndef TOUR_GIGFILTER_H
#define TOUR_GIGFILTER_H

#include "system/obj/Data.h"

class GigFilter {
    public:
    GigFilter();
    virtual ~GigFilter();
    void Init(const DataArray*);
    Symbol GetName() const;
    bool IsInternal() const;
    void GetFilter() const;
    void GetFilteredPartSym() const;
    // void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, int, Symbol) const;
    void GetWeight() const;

    Symbol mName;       // 0x04
    bool mIsInternal;   // 0x08
};

#endif // TOUR_GIGFILTER_H