#include "beatmatch/SlotChannelMapping.h"
#include "os/Debug.h"

SlotChannelMapping *
NewSlotChannelMapping(SubmixCollection *submixes, const std::vector<int> &vec, bool b) {
    if (vec.size() == 1) {
        return new SingleSlotChannelMapping(vec[0]);
    } else if (vec.size() == 2 || b) {
        return new MassChannelMapping(vec);
    } else
        return 0;
}

SingleSlotChannelMapping::SingleSlotChannelMapping(int chan) : mChannel(chan) {}

void SingleSlotChannelMapping::FillChannelList(std::list<int> &chanList) const {
    chanList.push_back(mChannel);
}

void SingleSlotChannelMapping::FillChannelList(std::list<int> &chanList, int i) const {
    chanList.push_back(mChannel);
}

MassChannelMapping::MassChannelMapping(const std::vector<int> &vec) {
    mChannels.insert(mChannels.end(), vec.begin(), vec.end());
}

void MassChannelMapping::FillChannelList(std::list<int> &chanList) const {
    chanList.insert(chanList.end(), mChannels.begin(), mChannels.end());
}

void MassChannelMapping::FillChannelList(std::list<int> &chanList, int) const {
    chanList.insert(chanList.end(), mChannels.begin(), mChannels.end());
}

int MassChannelMapping::ChannelBitfield(int) const {
    int mask = 0;
    for (std::list<int>::const_iterator it = mChannels.begin(); it != mChannels.end();
         ++it) {
        mask |= (1 << *it);
    }
    return mask;
}

MultiChannelMapping::MultiChannelMapping(
    Submix *submix, const char *cc, std::vector<int> &vec
) {
    if (!submix)
        MILO_FAIL("submix '%s' is not defined", cc);
    for (int i = 0; i < submix->GetNumSlots(); i++) {
        mChannelsPerSlot.push_back(std::list<int>());
        std::list<int> &curList = mChannelsPerSlot.back();
        submix->FillChannelList(curList, i);
        if (vec.size() != 0) {
            for (std::list<int>::iterator it = curList.begin(); it != curList.end();
                 ++it) {
                if (*it >= vec.size()) {
                    MILO_WARN(
                        "MIDI authoring error: submix %s refers to channel %d when only channels 0-%d are available",
                        cc,
                        *it,
                        vec.size() - 1
                    );
                } else {
                    int vecInt = vec[*it];
                    int &listInt = *it;
                    listInt = vecInt;
                }
            }
        }
    }
}

void MultiChannelMapping::FillChannelList(std::list<int> &chanList) const {
    for (int i = 0; i < mChannelsPerSlot.size(); i++) {
        chanList.insert(
            chanList.end(), mChannelsPerSlot[i].begin(), mChannelsPerSlot[i].end()
        );
    }
}

void MultiChannelMapping::FillChannelList(std::list<int> &chanList, int laneNum) const {
    if (laneNum == -1)
        FillChannelList(chanList);
    else {
        if (laneNum >= mChannelsPerSlot.size()) {
            MILO_FAIL(
                "gem in lane %d but drums only have %d channels of audio\n",
                laneNum + 1,
                mChannelsPerSlot.size()
            );
        }
        chanList.insert(
            chanList.end(),
            mChannelsPerSlot[laneNum].begin(),
            mChannelsPerSlot[laneNum].end()
        );
    }
}

int MultiChannelMapping::ChannelBitfield(int slot) const {
    MILO_ASSERT(slot != -1, 0x97);
    if (slot >= mChannelsPerSlot.size()) {
        MILO_FAIL(
            "asking about lane %d but drums only have %d channels of audio\n",
            slot + 1,
            mChannelsPerSlot.size()
        );
    }
    int mask = 0;
    for (std::list<int>::const_iterator it = mChannelsPerSlot[slot].begin();
         it != mChannelsPerSlot[slot].end();
         ++it) {
        mask |= (1 << *it);
    }
    return mask;
}