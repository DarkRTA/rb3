#pragma once
#include "utl/Symbol.h"
#include <vector>
#include <list>

class DataArray; // forward dec

class Submix {
public:
    Submix(DataArray *);
    ~Submix();
    int GetNumSlots() const;
    void FillChannelList(std::list<int> &) const;
    void FillChannelList(std::list<int> &, int) const;

    Symbol mName; // 0x0
    std::vector<std::list<int> > mChannelsPerSlot; // 0x4
};

class SubmixCollection {
public:
    SubmixCollection(DataArray *);
    ~SubmixCollection();
    Submix *Find(Symbol);

    std::vector<Submix *> mSubmixes;
};
