#ifndef UTL_SONGINFOCOPY_H
#define UTL_SONGINFOCOPY_H
#include "utl/Symbol.h"
#include "utl/Str.h"
#include "utl/SongInfoAudioType.h"
#include "utl/BinStream.h"
#include <vector>

class TrackChannels {
public:
    TrackChannels(){}
    ~TrackChannels(){}
    std::vector<int> mChannels;
};

BinStream& operator<<(BinStream& bs, const TrackChannels& chans){
    bs << (int)chans.mChannels.size();
    for(std::vector<int>::const_iterator it = chans.mChannels.begin(); it != chans.mChannels.end(); it++){
        bs << *it;
    }
    return bs;
}

class SongInfo {
public:
    SongInfo(){}
    virtual ~SongInfo(){}
    virtual Symbol GetName() const = 0;
    virtual const char* GetBaseFileName() const = 0;
    virtual const char* GetPackageName() const = 0;

    // TODO: fix the return types of these methods below as you implement them
    virtual const std::vector<TrackChannels>& GetTracks() const = 0;
    virtual bool IsPlayTrackChannel(int) const = 0;
    virtual const std::vector<int>& FindTrackChannel(SongInfoAudioType) const = 0;
    virtual int NumChannelsOfTrack(SongInfoAudioType) const = 0;
    virtual int TrackIndex(SongInfoAudioType) const = 0;

    virtual int GetNumVocalParts() const = 0;
    virtual int GetHopoThreshold() const = 0;
    virtual const std::vector<float>& GetPans() const = 0;
    virtual const std::vector<float>& GetVols() const = 0;
    virtual const std::vector<int>& GetCores() const = 0;
    virtual const std::vector<int>& GetCrowdChannels() const = 0;
    virtual const std::vector<Symbol>& GetDrumSoloSamples() const = 0;
    virtual const std::vector<Symbol>& GetDrumFreestyleSamples() const = 0;
    virtual float GetMuteVolume() const = 0;
    virtual float GetVocalMuteVolume() const = 0;
    virtual int NumExtraMidiFiles() const = 0;
    virtual const char* GetExtraMidiFile(int) const = 0;
};

class SongInfoCopy {
public:
    SongInfoCopy();
    SongInfoCopy(const SongInfo*);
    virtual ~SongInfoCopy();
    virtual Symbol GetName() const;
    virtual const char* GetBaseFileName() const;
    virtual const char* GetPackageName() const;

    // TODO: fix the return types of these methods below as you implement them
    virtual const std::vector<TrackChannels>& GetTracks() const;
    virtual bool IsPlayTrackChannel(int) const;
    virtual const std::vector<int>& FindTrackChannel(SongInfoAudioType) const;
    virtual int NumChannelsOfTrack(SongInfoAudioType) const;
    virtual int TrackIndex(SongInfoAudioType) const;

    virtual int GetNumVocalParts() const;
    virtual int GetHopoThreshold() const;
    virtual const std::vector<float>& GetPans() const;
    virtual const std::vector<float>& GetVols() const;
    virtual const std::vector<int>& GetCores() const;
    virtual const std::vector<int>& GetCrowdChannels() const;
    virtual const std::vector<Symbol>& GetDrumSoloSamples() const;
    virtual const std::vector<Symbol>& GetDrumFreestyleSamples() const;
    virtual float GetMuteVolume() const;
    virtual float GetVocalMuteVolume() const;
    virtual int NumExtraMidiFiles() const;
    virtual const char* GetExtraMidiFile(int) const;

    Symbol mName;
    class String mBaseFileName;
    class String mPackageName;
    int mNumVocalParts;
    int mHopoThreshold;
    float mMuteVolume;
    float mVocalMuteVolume;
    std::vector<float> mPans;
    std::vector<float> mVols;
    std::vector<int> mCores;
    std::vector<int> mCrowdChannels;
    std::vector<Symbol> mDrumSoloSamples;
    std::vector<Symbol> mDrumFreestyleSamples;
    std::vector<TrackChannels> mTrackChannels;
    std::vector<String> mExtraMidiFiles;
};

#endif
