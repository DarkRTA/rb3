#include "meta/DataArraySongInfo.h"
#include "os/Debug.h"

int DataArraySongInfo::sSaveVer = 1;

// this big macro needs to evaluate to a bool for the purpose of a MILO_ASSERT
#define FIND_WITH_BACKUP(sym) \
    member_exists = true; \
    existing_member_array = arr1->FindArray(sym, false); \
    if(!existing_member_array){ \
        bool exists_in_missing = false; \
        if(arr2){ \
            existing_member_array = arr2->FindArray(sym, false); \
            if(existing_member_array) exists_in_missing = true; \
        } \
        if(!exists_in_missing) member_exists = false; \
    }

DataArraySongInfo::DataArraySongInfo(DataArray*, DataArray*, Symbol){
    bool member_exists;
    DataArray* existing_member_array;
}

DataArraySongInfo::DataArraySongInfo(SongInfo* info) : SongInfoCopy(info) {

}

DataArraySongInfo::DataArraySongInfo(){
    
}

DataArraySongInfo::~DataArraySongInfo(){
    
}

void DataArraySongInfo::Save(BinStream& bs) const {
    bs << sSaveVer;
    bs << mName;
    bs << mBaseFileName;
    bs << mPackageName;
    bs << mNumVocalParts;
    bs << mHopoThreshold;
    bs << mMuteVolume;
    bs << mVocalMuteVolume;
    bs << mPans;
    bs << mVols;
    bs << mCores;
    bs << mCrowdChannels;
    bs << mDrumSoloSamples;
    bs << mDrumFreestyleSamples;
    bs << mTrackChannels;
    bs << mExtraMidiFiles;
}

void DataArraySongInfo::SetBaseFileName(const char* name){
    mBaseFileName = name;
}
