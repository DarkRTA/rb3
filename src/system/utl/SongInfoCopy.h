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
    SongInfoAudioType mAudioType; // 0x0 - SongInfoAudioType? maybe?
    std::vector<int> mChannels; // 0x4
};

BinStream& operator<<(BinStream&, const TrackChannels&);
BinStream& operator>>(BinStream&, TrackChannels&);

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
    virtual const TrackChannels* FindTrackChannel(SongInfoAudioType) const = 0;
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

class SongInfoCopy : public SongInfo {
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
    virtual const TrackChannels* FindTrackChannel(SongInfoAudioType) const;
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

    Symbol mName; // 0x4
    class String mBaseFileName; // 0x8
    class String mPackageName; // 0x14
    int mNumVocalParts; // 0x20
    int mHopoThreshold; // 0x24
    float mMuteVolume; // 0x28
    float mVocalMuteVolume; // 0x2c
    std::vector<float> mPans; // 0x30
    std::vector<float> mVols; // 0x38
    std::vector<int> mCores; // 0x40
    std::vector<int> mCrowdChannels; // 0x48
    std::vector<Symbol> mDrumSoloSamples; // 0x50
    std::vector<Symbol> mDrumFreestyleSamples; // 0x58
    std::vector<TrackChannels> mTrackChannels; // 0x60
    std::vector<class String> mExtraMidiFiles; // 0x68
};

#endif
