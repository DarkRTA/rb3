#include "meta/DataArraySongInfo.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int DataArraySongInfo::sSaveVer = 1;

// https://decomp.me/scratch/qGyeB
DataArraySongInfo::DataArraySongInfo(DataArray* main_arr, DataArray* backup_arr, Symbol name_sym){
    mName = name_sym;

    // this part needs to be a macro, FIND_WITH_BACKUP(name)
    DataArray* member_arr;
    MILO_ASSERT(FIND_WITH_BACKUP(name), 0x1C);
    mBaseFileName = member_arr->Str(1);

    if(FIND_WITH_BACKUP(pkg_name)){
        mPackageName = member_arr->Str(1);
    }
    if(FIND_WITH_BACKUP(vocal_parts)){
        mNumVocalParts = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(hopo_threshold)){
        mHopoThreshold = member_arr->Int(1);
    }
    if(FIND_WITH_BACKUP(mute_volume)){
        mMuteVolume = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(mute_volume_vocals)){
        mVocalMuteVolume = member_arr->Float(1);
    }
    if(FIND_WITH_BACKUP(pans)){
        DataArray* pan_arr = member_arr->Array(1);
        mPans.reserve(pan_arr->Size());
        for(int i = 0; i < pan_arr->Size(); i++){
            mPans.push_back(pan_arr->Float(i));
        }
    }
    if(FIND_WITH_BACKUP(vols)){
        DataArray* vol_arr = member_arr->Array(1);
        mVols.reserve(vol_arr->Size());
        for(int i = 0; i < vol_arr->Size(); i++){
            mVols.push_back(vol_arr->Float(i));
        }
    }    
    if(FIND_WITH_BACKUP(cores)){
        DataArray* core_arr = member_arr->Array(1);
        mCores.reserve(core_arr->Size());
        for(int i = 0; i < core_arr->Size(); i++){
            mCores.push_back(core_arr->Int(i));
        }
    }
    if(FIND_WITH_BACKUP(crowd_channels)){
        mCrowdChannels.reserve(member_arr->Size() - 1);
        for(int i = 1; i < member_arr->Size(); i++){
            mCrowdChannels.push_back(member_arr->Int(i));
        }
    }
    if(FIND_WITH_BACKUP(drum_solo)){
        DataArray* solo_arr = member_arr->FindArray("seqs", true)->Array(1);
        mDrumSoloSamples.reserve(solo_arr->Size());
        for(int i = 0; i < solo_arr->Size(); i++){
            mDrumSoloSamples.push_back(solo_arr->Sym(i));
        }
    }
    if(FIND_WITH_BACKUP(drum_freestyle)){
        DataArray* freestyle_arr = member_arr->FindArray("seqs", true)->Array(1);
        mDrumFreestyleSamples.reserve(freestyle_arr->Size());
        for(int i = 0; i < freestyle_arr->Size(); i++){
            mDrumFreestyleSamples.push_back(freestyle_arr->Sym(i));
        }
    }
    if(FIND_WITH_BACKUP(tracks)){
        DataArray* track_arr = member_arr->Array(1);
        mTrackChannels.reserve(track_arr->Size());
        for(int i = 0; i < track_arr->Size(); i++){
            DataArray* chan_arr = track_arr->Array(i);
            mTrackChannels = std::vector<TrackChannels>();
            mTrackChannels[i].mAudioType = SymbolToAudioType(chan_arr->Sym(0));
            DataNode& chan_node = chan_arr->Node(1);
            if(chan_node.Type() == kDataArray){
                DataArray* chan_nums = chan_node.Array(0);
                for(int j = 0; j < chan_nums->Size(); j++){
                    mTrackChannels[i].mChannels.push_back(chan_nums->Int(j));
                }
            }
            else {
                mTrackChannels[i].mChannels.push_back(chan_node.Int(0));
            }
        }
    }
    
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
    bs >> mTrackChannels;
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