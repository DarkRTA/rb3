#include "meta/DataArraySongInfo.h"

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
