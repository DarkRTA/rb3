#include "beatmatch/Submix.h"
#include "obj/Data.h"
#include "os/Debug.h"

Submix::Submix(DataArray *arr) : mName(arr->Sym(0)) {
    DataArray *subArr = arr->Array(1);
    for (int i = 0; i < subArr->Size(); i++) {
        mChannelsPerSlot.push_back(std::list<int>());
        DataNode &curNode = subArr->Node(i);
        if (curNode.Type() == kDataArray) {
            DataArray *curArr = curNode.Array();
            for (int j = 0; j < curArr->Size(); j++) {
                mChannelsPerSlot.back().push_back(curArr->Int(j));
            }
        } else {
            mChannelsPerSlot.back().push_back(subArr->Int(i));
        }
    }
}

Submix::~Submix() {}

int Submix::GetNumSlots() const { return mChannelsPerSlot.size(); }

void Submix::FillChannelList(std::list<int> &chans) const {
    for (int i = 0; i < mChannelsPerSlot.size(); i++) {
        chans.insert(chans.end(), mChannelsPerSlot[i].begin(), mChannelsPerSlot[i].end());
    }
}

void Submix::FillChannelList(std::list<int> &chans, int laneNum) const {
    if (laneNum == -1)
        FillChannelList(chans);
    else {
        if (laneNum >= mChannelsPerSlot.size()) {
            MILO_FAIL(
                "gem in lane %d but drums only have %d channels of audio\n",
                laneNum + 1,
                mChannelsPerSlot.size()
            );
        }
        chans.insert(
            chans.end(),
            mChannelsPerSlot[laneNum].begin(),
            mChannelsPerSlot[laneNum].end()
        );
    }
}

SubmixCollection::SubmixCollection(DataArray *arr) {
    if (arr) {
        mSubmixes.reserve(arr->Size() - 1);
        for (int i = 1; i < arr->Size(); i++) {
            mSubmixes.push_back(new Submix(arr->Array(i)));
        }
    }
}

SubmixCollection::~SubmixCollection() {
    for (int i = 0; i < mSubmixes.size(); i++) {
        RELEASE(mSubmixes[i]);
    }
}

Submix *SubmixCollection::Find(Symbol sym) {
    for (int i = 0; i < mSubmixes.size(); i++) {
        if (mSubmixes[i]->mName == sym)
            return mSubmixes[i];
    }
    return 0;
}