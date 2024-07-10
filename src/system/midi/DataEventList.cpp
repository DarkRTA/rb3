#include "midi/DataEvent.h"
#include "os/Debug.h"
#include <algorithm>

namespace {
    bool EventTimeCompComp(float f, const DataEventList::CompEv& ev){
        return f < ev.start;
    }
}

DataEventList::DataEventList() : mCurIndex(0), mSize(0), mElement(-1), mCompType(kDataUnhandled), mValue(0) {
    
}

// fn_8052A590
DataEventList::~DataEventList(){

}

// fn_8052AE4C
void DataEventList::Compress(DataArray* arr, int i){
    mElement = i;
    mTemplate.SetMsg(arr);
    mValue = &arr->Node(i).mValue.integer;
}

// fn_8052AEFC
void DataEventList::InsertEvent(float start, float end, const DataNode& node, int idx){
    if(mElement < 0){
        if(mSize == 0) mEvents.reserve(32);
        mEvents.insert(mEvents.begin() + idx, DataEvent(start, end, node.Array(0)));
    }
    else {
        CompEv event;
        event.start = start;
        event.end = end;
        event.value = node.mValue.integer;
        if(mSize == 0){
            mComps.reserve(32);
            mCompType = node.Type();
            mTemplate.mMsg->Node(mElement) = node;
            MILO_ASSERT(mCompType == kDataSymbol || mCompType == kDataInt, 0x43);
        }
        else if(mCompType != node.Type()){
            String str;
            node.Print(str, false);
            MILO_WARN("Trying to add event %s but mCompType is %s, ignoring", str, mCompType == kDataInt ? "kDataInt" : "kDataSymbol");
            return;
        }
        mComps.insert(mComps.begin() + idx, event);
    }
    mSize++;
}

int DataEventList::FindStartFromBack(float start) const {
    int ret = mSize - 1;
    if(mElement < 0){
        for(int i = mSize - 1; i >= 0; i--){
            if(start >= mEvents[i].start){
                ret = i;
                break;
            }
        }
    }
    else {
        for(int i = mSize - 1; i >= 0; i--){
            if(start >= mComps[i].start){
                ret = i;
                break;
            }
        }
    }
    return ret;
}

void DataEventList::Reset(float f){
    if(mElement < 0){
        // std::lower_bound(mComps.begin(), mComps.end(), f, EventTimeCompComp);
    }
}

const DataEvent& DataEventList::Event(int i) const {
    if(mElement >= 0){
        const DataEventList::CompEv& compev = mComps[i];
        // mTemplate.start = compev.start;
        // mTemplate.end = compev.end;
        // mValue = &compev.value;
        return mTemplate;
    }
    else return mEvents[i];
}

DataEvent* DataEventList::NextEvent(float f){
    if(mCurIndex >= mSize) return 0;
    if(mElement >= 0){
        if(f < mComps[mCurIndex].start) return 0;
    }
    else if(f < mEvents[mCurIndex].start) return 0;
    mCurIndex++;
    return &(DataEvent&)Event(mCurIndex);
}

float* DataEventList::EndPtr(int index){
    MILO_ASSERT(index < mSize, 0xC0);
    if(mElement < 0) return &mEvents[index].end;
    else return &mComps[index].end;
}

void DataEventList::Clear(){
    mCurIndex = 0;
    mSize = 0;
    // probably wrong
    mComps = std::vector<CompEv, unsigned int>();
    mEvents = std::vector<DataEvent, unsigned short>();
}