#include "utl/SongInfoCopy.h"
#include "os/System.h"
#include "os/File.h"
#include <algorithm>

SongInfoCopy::SongInfoCopy(const SongInfo* info) : mName(), mBaseFileName(), mPackageName() {
    mName = info->GetName();
    mBaseFileName = info->GetBaseFileName();
    if(FileIsDLC(mBaseFileName.c_str())){
        std::vector<String> substrs;
        mBaseFileName.split("/", substrs);
        if(substrs.size() > 3){
            if(substrs[2].find("_song") == String::npos){
                substrs[2] += "_song";
                String _songStr(substrs[0]);
                for(int idx = 1; idx < substrs.size(); idx++){
                    _songStr += "/";
                    _songStr += substrs[idx];
                }
                mBaseFileName = _songStr;
            }
        }
    }
    mPackageName = info->GetPackageName();
    mNumVocalParts = info->GetNumVocalParts();
    mHopoThreshold = info->GetHopoThreshold();
    mMuteVolume = info->GetMuteVolume();
    mVocalMuteVolume = info->GetVocalMuteVolume();
    mPans = info->GetPans();
    mVols = info->GetVols();
    mCores = info->GetCores();
    mCrowdChannels = info->GetCrowdChannels();
    mDrumSoloSamples = info->GetDrumSoloSamples();
    mDrumFreestyleSamples = info->GetDrumFreestyleSamples();
    mTrackChannels = info->GetTracks();
    int midifilenum = info->NumExtraMidiFiles();
    mExtraMidiFiles.reserve(midifilenum);
    for(int i = 0; i < midifilenum; i++){
        mExtraMidiFiles.push_back(info->GetExtraMidiFile(i));
    }
}

SongInfoCopy::SongInfoCopy() : mName(), mBaseFileName(), mPackageName() {
    mName = gNullStr;
    mNumVocalParts = 1;
    mHopoThreshold = 0;
    mMuteVolume = 0.0f;
    mVocalMuteVolume = 0.0f;
    DataArray* cfg = SystemConfig()->FindArray("beatmatcher", false);
    if(cfg){
        mHopoThreshold = cfg->FindArray("parser", true)->FindInt("hopo_threshold");
        mMuteVolume = cfg->FindArray("audio", true)->FindFloat("mute_volume");
        mVocalMuteVolume = cfg->FindArray("audio", true)->FindFloat("mute_volume_vocals");
    }
}

SongInfoCopy::~SongInfoCopy(){

}

Symbol SongInfoCopy::GetName() const {
    return mName;
}

const char* SongInfoCopy::GetBaseFileName() const {
    return mBaseFileName.c_str();
}

const char* SongInfoCopy::GetPackageName() const {
    if(!mPackageName.empty()) return mPackageName.c_str();
    else return 0;
}

const std::vector<TrackChannels>& SongInfoCopy::GetTracks() const {
    return mTrackChannels;
}

// fn_803612E0
bool SongInfoCopy::IsPlayTrackChannel(int chan) const {
    for(int i = 0; i < mTrackChannels.size(); i++){
        if(std::find(mTrackChannels[i].mChannels.begin(), mTrackChannels[i].mChannels.end(), chan) != mTrackChannels[i].mChannels.end()){
            return true;
        }
    }
    return false;
}

const TrackChannels* SongInfoCopy::FindTrackChannel(SongInfoAudioType ty) const {
    for(int i = 0; i < mTrackChannels.size(); i++){
        if(mTrackChannels[i].mAudioType == ty){
            return &mTrackChannels[i];
        }
    }
    return 0;
}

int SongInfoCopy::NumChannelsOfTrack(SongInfoAudioType ty) const {
    const TrackChannels* tc = FindTrackChannel(ty);
    if(tc) return tc->mChannels.size();
    else return 0;
}

int SongInfoCopy::TrackIndex(SongInfoAudioType ty) const {
    for(int i = 0; i < mTrackChannels.size(); i++){
        if(mTrackChannels[i].mAudioType == ty) return i;
    }
    return -1;
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
