#ifndef BEATMATCH_SUBMIX_H
#define BEATMATCH_SUBMIX_H
#include "utl/Symbol.h"
#include <vector>
#include <list>

class DataArray; // forward dec

class Submix {
public:
    Submix(DataArray*);
    ~Submix();
    int GetNumSlots() const;
    void FillChannelList(std::list<int>&) const;
    void FillChannelList(std::list<int>&, int) const;

    Symbol mName;
    std::vector<int> mChannelsPerSlot;
};

class SubmixCollection {
public:
    SubmixCollection(DataArray*);
    ~SubmixCollection();
    Submix* Find(Symbol);
    
    std::vector<Submix*> mSubmixes;
};

#endif
