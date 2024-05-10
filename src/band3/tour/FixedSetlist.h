#ifndef TOUR_FIXEDSETLIST_H
#define TOUR_FIXEDSETLIST_H

#include "system/obj/Data.h"

class FixedSetlist {
    FixedSetlist();
    virtual ~FixedSetlist();
    void Init(const DataArray*);
    Symbol mName; Symbol GetName() const;
    Symbol mGroup; Symbol GetGroup() const;
    float mWeight; float GetWeight() const;
    DataArray* mSongEntries;
    Symbol GetSongName(int);
    int GetNumSongs() const;

    void InqSongs(std::vector<Symbol>&) const;

    std::vector<Symbol> mSongs;
};

#endif // TOUR_FIXEDSETLIST_H