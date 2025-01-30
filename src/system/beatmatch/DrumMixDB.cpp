#include "beatmatch/DrumMixDB.h"
#include "macros.h"
#include "os/Debug.h"

DrumMixDB::DrumMixDB(int num_mixes){
    mMixLists.reserve(num_mixes);
    for(int i = 0; i < num_mixes; i++){
        mMixLists.push_back(new TickedInfoCollection<String>());
    }
}

DrumMixDB::~DrumMixDB(){
    for(int i = 0; i < mMixLists.size(); i++){
        RELEASE(mMixLists[i]);
    }
}

void DrumMixDB::Clear(){
    for(int i = 0; i < mMixLists.size(); i++){
        mMixLists[i]->Clear();
    }
}

bool DrumMixDB::AddMix(int diff, int tick, const char* str){
    MILO_ASSERT_RANGE(diff, 0, mMixLists.size(), 0x2D);
    return mMixLists[diff]->AddInfo(tick, str);
}

TickedInfoCollection<String>& DrumMixDB::GetMixList(int diff){
    MILO_ASSERT_RANGE(diff, 0, mMixLists.size(), 0x39);
    return *mMixLists[diff];
}

DrumMixDB* DrumMixDB::Duplicate() const {
    DrumMixDB* db = new DrumMixDB(mMixLists.size());
    for(int i = 0; i < mMixLists.size(); i++){
        db->mMixLists[i]->CopyFrom(*mMixLists[i]);
    }
    return db;
}