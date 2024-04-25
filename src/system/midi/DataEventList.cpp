#include "midi/DataEvent.h"

DataEventList::DataEventList() : mCurIndex(0), mSize(0), mElement(-1), mCompType(kDataUnhandled), mValue(0) {
    
}

DataEventList::~DataEventList(){
    mTemplate.mMsg->Release();
}

void DataEventList::Compress(DataArray* arr, int i){
    mElement = i;
    if(mTemplate.mMsg) mTemplate.mMsg->Release();
    mTemplate.mMsg = arr;
    if(arr) arr->AddRef();
    mValue = &arr->Node(i).mValue.integer;
}