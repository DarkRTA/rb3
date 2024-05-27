#ifndef TOUR_FIXEDSETLIST_H
#define TOUR_FIXEDSETLIST_H

#include "system/obj/Data.h"

class FixedSetlist {

public:
    FixedSetlist();
    virtual ~FixedSetlist();

private:
    void Init(const DataArray*);
    Symbol GetName() const;
    Symbol GetGroup() const;
    float GetWeight() const;

    Symbol GetSongName(int);
    int GetNumSongs() const;

    void InqSongs(std::vector<Symbol>&) const;

    Symbol mName;               // 0x04
    Symbol mGroup;              // 0x08
    float mWeight;              // 0x0c
    DataArray* m_pSongEntries;  // 0x10
    std::vector<Symbol> o_rSongs; // 0x14

};

#endif // TOUR_FIXEDSETLIST_H