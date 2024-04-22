#include "beatmatch/Submix.h"
#include "obj/Data.h"

void Submix::FillChannelList(std::list<int>& chans) const {
    for(int i = 0; i < mChannelsPerSlot.size(); i++){
        chans.push_back(mChannelsPerSlot[i]);
    }
}

SubmixCollection::SubmixCollection(DataArray* arr){
    if(arr){
        mSubmixes.reserve(arr->Size() - 1);
        for(int i = 1; i < arr->Size(); i++){
            mSubmixes.push_back(new Submix(arr->Array(i)));
        }
    }
}

SubmixCollection::~SubmixCollection(){
    for(int i = 0; i < mSubmixes.size(); i++){
        delete mSubmixes[i];
        mSubmixes[i] = 0;
    }
}

Submix* SubmixCollection::Find(Symbol sym){
    for(int i = 0; i < mSubmixes.size(); i++){
        if(mSubmixes[i]->mName == sym) return mSubmixes[i];
    }
    return 0;
}