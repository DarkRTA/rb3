#include "meta/DataArraySongInfo.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int DataArraySongInfo::sSaveVer = 1;

// this big macro needs to evaluate to a bool for the purpose of a MILO_ASSERT
// I think this ultimately needs to evaluate to a DataArray*
// and it takes in a Symbol - see my shoddy attempt at it with FIND_WITH_BACKUP below
#define GET_MEMBER_ARRAY(sym) \
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

#define FIND_WITH_BACKUP(sym) \
    arr1->FindArray(sym, false) ? arr1->FindArray(sym, false) : arr2->FindArray(sym, false)

DataArraySongInfo::DataArraySongInfo(DataArray* arr1, DataArray* arr2, Symbol){
    bool member_exists;
    DataArray* existing_member_array;
    MILO_ASSERT(FIND_WITH_BACKUP(name), 0x1C);
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

void DataArraySongInfo::Load(BinStream& bs) {
    int lol;
    bs >> lol;
    bs >> mName;
    bs >> mBaseFileName;
    bs >> mPackageName;
    bs >> mNumVocalParts;
    bs >> mHopoThreshold;
    bs >> mMuteVolume;
    bs >> mVocalMuteVolume;
    bs >> mPans;
    bs >> mVols;
    bs >> mCores;
    bs >> mCrowdChannels;
    bs >> mDrumSoloSamples;
    bs >> mDrumFreestyleSamples;
    // bs >> mTrackChannels; // why does this cause an error?
    bs >> mExtraMidiFiles;
}

void DataArraySongInfo::SetBaseFileName(const char* name){
    mBaseFileName = name;
}

void DataArraySongInfo::AddExtraMidiFile(const char* cc1, const char* cc2){
    class String k(cc1);
    mExtraMidiFiles.push_back(k);
}

BinStream& operator<<(BinStream& bs, const DataArraySongInfo& dinfo){
    dinfo.Save(bs);
    return bs;
}

BinStream& operator>>(BinStream& bs, DataArraySongInfo& dinfo){
    dinfo.Load(bs);
    return bs;
}

BinStream& operator<<(BinStream& bs, const TrackChannels& chans){
    bs << chans.mAudioType;
    bs << chans.mChannels;
    return bs;
}

BinStream& operator>>(BinStream& bs, TrackChannels& chans){
    int ty;
    bs >> ty;
    chans.mAudioType = (SongInfoAudioType)ty;
    bs >> chans.mChannels;
    return bs;
}