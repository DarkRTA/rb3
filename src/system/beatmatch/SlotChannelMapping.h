#ifndef BEATMATCH_SLOTCHANNELMAPPING_H
#define BEATMATCH_SLOTCHANNELMAPPING_H
#include <vector>
#include <list>
#include "beatmatch/Submix.h"

class SlotChannelMapping {
public:
    SlotChannelMapping(){}
    virtual ~SlotChannelMapping(){}
    virtual void FillChannelList(std::list<int>&) const = 0;
    virtual void FillChannelList(std::list<int>&, int) const = 0;
    virtual int GetNumSlots() const = 0;
    virtual int ChannelBitfield(int) const = 0;
};

class SingleSlotChannelMapping : public SlotChannelMapping {
public:
    SingleSlotChannelMapping(int);
    virtual ~SingleSlotChannelMapping(){}
    virtual void FillChannelList(std::list<int>&) const;
    virtual void FillChannelList(std::list<int>&, int) const;
    virtual int GetNumSlots() const { return 1; }
    virtual int ChannelBitfield(int) const { return 1 << mChannel; }

    int mChannel;
};

class MassChannelMapping : public SlotChannelMapping {
public:
    MassChannelMapping(const std::vector<int>&);
    virtual ~MassChannelMapping(){}
    virtual void FillChannelList(std::list<int>&) const;
    virtual void FillChannelList(std::list<int>&, int) const;
    virtual int GetNumSlots() const { return 1; }
    virtual int ChannelBitfield(int) const;

    std::list<int> mChannels; // list type could be wrong
};

class MultiChannelMapping : public SlotChannelMapping {
public:
    MultiChannelMapping(Submix*, const char*, std::vector<int>&);
    virtual ~MultiChannelMapping(){}
    virtual void FillChannelList(std::list<int>&) const;
    virtual void FillChannelList(std::list<int>&, int) const;
    virtual int GetNumSlots() const { return mChannelsPerSlot.size(); }
    virtual int ChannelBitfield(int slot) const;

    std::vector<int> mChannelsPerSlot; // vector type could be wrong
};

SlotChannelMapping* NewSlotChannelMapping(SubmixCollection*, const std::vector<int>&, bool);

#endif