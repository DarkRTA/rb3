#include "beatmatch/SlotChannelMapping.h"

SlotChannelMapping* NewSlotChannelMapping(SubmixCollection* submixes, const std::vector<int>& vec, bool b){
    if(vec.size() == 1){
        return new SingleSlotChannelMapping(*vec.begin());
    }
    else if(vec.size() == 2 || b){
        return new MassChannelMapping(vec);
    }
    else return 0;
}

SingleSlotChannelMapping::SingleSlotChannelMapping(int chan) : mChannel(chan) {

}

void SingleSlotChannelMapping::FillChannelList(std::list<int>& chanList) const {
    chanList.push_back(mChannel);
}

void SingleSlotChannelMapping::FillChannelList(std::list<int>& chanList, int i) const {
    chanList.push_back(mChannel);
}

MassChannelMapping::MassChannelMapping(const std::vector<int>& vec){
    for(std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++){
        mChannels.push_back(*it);
    }
}

void MassChannelMapping::FillChannelList(std::list<int>& chanList) const {
    
}

MultiChannelMapping::MultiChannelMapping(Submix*, const char*, std::vector<int>&){

}

void MultiChannelMapping::FillChannelList(std::list<int>& chanList) const {
    
}