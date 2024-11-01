#include "net_band/DataResults.h"

bool DataResult::GetDataResultValue(String str, DataNode& node) const {
    bool found = false;
    std::map<String, DataNode>::const_iterator it = mDataMap.find(str);
    if(it != mDataMap.end()){
        found = true;
        node = it->second;
    }
    return found;
}

DataResultList::DataResultList() : unk4(0) {
    mQDataResultString = new Quazal::String();
    mUpdated = 0;
}

DataResultList::~DataResultList(){
    delete mQDataResultString;
}

void DataResultList::Update(Message* msg){

}