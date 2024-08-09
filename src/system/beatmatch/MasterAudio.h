#ifndef BEATMATCH_MASTERAUDIO_H
#define BEATMATCH_MASTERAUDIO_H
#include "obj/Data.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/SongData.h"
#include "beatmatch/BeatMasterSink.h"
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/HxAudio.h"
#include "beatmatch/PitchMucker.h"
#include "beatmatch/Submix.h"
#include "obj/Object.h"
#include "synth/Faders.h"

class TrackDataCollection {
public:
    TrackDataCollection(){}
    std::vector<int> mTrackData; // 0x0
};

class MasterAudio : public BeatMasterSink, public BeatMatchSink, public Hmx::Object, public HxAudio {
public:
    MasterAudio(DataArray*, int, BeatMaster*, SongData*);
    virtual ~MasterAudio();
    virtual void Beat(int, int);
    virtual void UpdateSongPos(const SongPos&);
    virtual void HandleSubmix(int, const char*);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsReady();
    virtual bool Paused() const;
    virtual void SetPaused(bool);
    virtual void Poll();
    virtual float GetTime() const;
    virtual int GetSongStream();
    virtual void SetMasterVolume(float);
    
    virtual void Hit(int, float, int, unsigned int, GemHitFlags);
    virtual void ReleaseGem(int, float, int, float);
    virtual void Miss(int, int, float, int, int, GemHitFlags);
    virtual void SpuriousMiss(int, int, float, int);
    virtual void Pass(int, float, int, bool);
    virtual void Ignore(int, float, int, const UserGuid&);
    virtual void ImplicitGem(int, float, int, const UserGuid&);
    virtual void SeeGem(int, float, int);
    virtual void FillSwing(int, int, int, int, bool);
    virtual void SetTrack(const UserGuid&, int);
    virtual void Swing(int, int, float, bool, bool);
    virtual void FretButtonDown(int, float);
    virtual void FretButtonUp(int, float);
    virtual void MercurySwitch(bool, float);
    virtual void WhammyBar(float){}
    virtual void FilteredWhammyBar(float);
    virtual void SwingAtHopo(int, float, int);
    virtual void Hopo(int, float, int);
    virtual void SetCurrentPhrase(int, const PhraseInfo&);
    virtual void NoCurrentPhrase(int);
    virtual void FillReset();
    virtual void FillComplete(int, int);

    int mNumPlayers; // 0x28
    int mSongStream; // 0x2c
    SongData* mSongData; // 0x30
    bool mStreamEnabled; // 0x34
    Fader* mMasterFader; // 0x38
    Fader* mForegroundFader; // 0x3c
    Fader* mMultiplayerFader; // 0x40
    Fader* mBackgroundFader; // 0x44
    Fader* mBackgroundAttenFader; // 0x48
    Fader* mCommonFader; // 0x4c
    Fader* mRemoteFader; // 0x50
    Fader* mPracticeFader; // 0x54
    Fader* mVocalDuckFader; // 0x58
    Fader* mVocalCueFader; // 0x5c
    Fader* mVocalFailFader; // 0x60
    Fader* mCrowdFader; // 0x64
    Fader* mBaseCrowdFader; // 0x68
    SubmixCollection* mSubmixes; // 0x6c
    std::vector<int> mChannelData; // 0x70
    TrackDataCollection mTrackData; // 0x78
    bool mPlayingInCommon; // 0x80
    float mMultiplayerStereoScale; // 0x84
    float mMultiplayerVolume; // 0x88
    float mMultiplayerCommonVolume; // 0x8c
    float mPlayerAtten; // 0x90
    float mBackgroundVolume; // 0x94
    float mMuteVolume; // 0x98
    float mVocalMuteVolume; // 0x9c
    float mPassVolume; // 0xa0
    float mUnplayedVolume; // 0xa4
    float mCueVolume; // 0xa8
    float mPracticeVolume; // 0xac
    float mRemoteVolume; // 0xb0
    float mMasterVolume; // 0xb4

    bool mMuteMaster; // 0xb8
    bool mMuckWithPitch; // 0xb9

    PitchMucker* mPitchMucker; // 0xbc - PitchMucker*
    bool mWhammyEnabled; // 0xc0
    float mTimeOffset; // 0xc4

};

#endif
