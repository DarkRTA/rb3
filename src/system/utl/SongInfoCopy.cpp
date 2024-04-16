#include "utl/SongInfoCopy.h"
#include "os/System.h"
#include "os/File_Wii.h"

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
    // mTrackChannels = info->GetTracks(); // this causes an error and i have no clue why
    int midifilenum = NumExtraMidiFiles();
    mExtraMidiFiles.reserve(midifilenum);
    for(int i = 0; i < midifilenum; i++){
        mExtraMidiFiles.push_back(String(GetExtraMidiFile(midifilenum)));
    }
}

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

// this is wrong
const std::vector<int>& SongInfoCopy::FindTrackChannel(SongInfoAudioType ty) const {
    for(int i = 0; i < mTrackChannels.size(); i++){
        if(i == (int)ty){
            return mTrackChannels[i].mChannels;
        }   
    }
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
