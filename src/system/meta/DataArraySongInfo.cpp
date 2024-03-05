#include "meta/DataArraySongInfo.h"

DataArraySongInfo::DataArraySongInfo(SongInfo* info) : SongInfoCopy(info) {

}

DataArraySongInfo::DataArraySongInfo(){
    
}

DataArraySongInfo::~DataArraySongInfo(){
    
}

void DataArraySongInfo::Save(BinStream& bs) const {
    bs << sSaveVer << mName << mBaseFileName << mPackageName << 
        mNumVocalParts << mHopoThreshold << mMuteVolume << mVocalMuteVolume << 
        mPans << mVols << mCores << mCrowdChannels << mDrumSoloSamples << mDrumFreestyleSamples << // TODO: insert mTrackChannels
        mExtraMidiFiles;
}

void DataArraySongInfo::SetBaseFileName(const char* name){
    mBaseFileName = name;
}
