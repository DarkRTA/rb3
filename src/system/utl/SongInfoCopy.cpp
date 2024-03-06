#include "utl/SongInfoCopy.h"
#include "os/System.h"

SongInfoCopy::SongInfoCopy(const SongInfo* info) : mName(), mBaseFileName(), mPackageName() {
    mName = info->GetName();
    mBaseFileName = info->GetBaseFileName();
//       iVar4 = FileIsDLC(*(char **)(this + 0x10));
//   if (iVar4 != 0) {
//     local_40 = (String *)0x0;
//     local_3c = 0;
//     local_3a = 0;
//     String::split((String *)(this + 8),::@stringBase0,(vector<> *)&local_40);
//     if (3 < local_3c) {
//       iVar4 = String::find((String *)(local_40 + 0x18),s__song_80bbfaea);
//       if (iVar4 == -1) {
//         String::operator_+=((String *)(local_40 + 0x18),s__song_80bbfaea);
//         String::String(&SStack_2c,local_40);
//         uVar10 = 1;
//         iVar4 = 0xc;
//         while( true ) {
//           if (local_3c <= uVar10) break;
//           String::operator_+=(&SStack_2c,::@stringBase0);
//           String::operator_+=(&SStack_2c,local_40 + iVar4);
//           uVar10 = uVar10 + 1;
//           iVar4 = iVar4 + 0xc;
//         }
//         String::operator_=((String *)(this + 8),(String *)&SStack_2c);
//         String::~String(&SStack_2c);
//       }
//     }
//     pSVar1 = local_40;
//     if (&stack0x00000000 != (undefined *)0x40) {
//       for (pSVar11 = local_40 + (uint)local_3c * 0xc; pSVar11 != pSVar1; pSVar11 = pSVar11 + -0xc)  {
//         (**(code **)(*(int *)(pSVar11 + -0xc) + 8))(pSVar11 + -0xc,0xffffffff);
//       }
//       if (&stack0x00000000 != (undefined *)0x40) {
//         if (local_40 != (String *)0x0) {
//           _MemOrPoolFreeSTL((uint)local_3a * 0xc,1,local_40);
//         }
//         local_40 = (String *)0x0;
//         local_3c = 0;
//         local_3a = 0;
//       }
//     }
//   }
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
