#include "utl/SongInfoCopy.h"
#include "os/System.h"

SongInfoCopy::SongInfoCopy() : mName() {
    mName = Symbol();
    mNumVocalParts = 1;
    mHopoThreshold = 0;
    mMuteVolume = 0.0f;
    mVocalMuteVolume = 0.0f;
    DataArray* cfg = SystemConfig()->FindArray("beatmatcher", false);
    if(cfg){
        mHopoThreshold = cfg->FindArray("parser", true)->FindArray("hopo_threshold", true)->Int(1);
        mMuteVolume = cfg->FindArray("audio", true)->FindArray("mute_volume",true)->Float(1);
        mVocalMuteVolume = cfg->FindArray("audio", true)->FindArray("mute_volume_vocals",true)->Float(1);
    }
}

SongInfoCopy::~SongInfoCopy(){

}

const char* SongInfoCopy::GetName() const {
    return mName.Str();
}

const char* SongInfoCopy::GetBaseFileName() const {
    return mBaseFileName.c_str();
}

const char* SongInfoCopy::GetPackageName() const {
    if(!mPackageName.empty()) return mPackageName.c_str();
    else return 0;
}

int SongInfoCopy::GetNumVocalParts() const {
    return mNumVocalParts;
}

int SongInfoCopy::GetHopoThreshold() const {
    return mHopoThreshold;
}

const std::vector<float>& SongInfoCopy::GetPans() const {
    return mPans;
}

const std::vector<float>& SongInfoCopy::GetVols() const {
    return mVols;
}

const std::vector<int>& SongInfoCopy::GetCores() const {
    return mCores;
}

const std::vector<int>& SongInfoCopy::GetCrowdChannels() const {
    return mCrowdChannels;
}

const std::vector<Symbol>& SongInfoCopy::GetDrumSoloSamples() const {
    return mDrumSoloSamples;
}

const std::vector<Symbol>& SongInfoCopy::GetDrumFreestyleSamples() const {
    return mDrumFreestyleSamples;
}

float SongInfoCopy::GetMuteVolume() const {
    return mMuteVolume;
}

float SongInfoCopy::GetVocalMuteVolume() const {
    return mVocalMuteVolume;
}

int SongInfoCopy::NumExtraMidiFiles() const {
    return mExtraMidiFiles.size();
}

const char* SongInfoCopy::GetExtraMidiFile(int idx) const {
    return mExtraMidiFiles[idx].c_str();
}
