#pragma once
#include "TrackConfig.h"
#include "bandobj/BandTrack.h"
#include "bandobj/CrowdMeterIcon.h"
#include "bandobj/TrackInterface.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "obj/Object.h"
#include "rndobj/Dir.h"

class Track : public TrackInterface {
public:
    Track(BandUser *);
    virtual ~Track() {}
    virtual DataNode Handle(DataArray *, bool);

    virtual bool ShouldDisablePopupHelp() const;
    virtual bool InGame() const;
    virtual bool HasPlayer() const;
    virtual bool HasLocalPlayer() const;
    virtual bool HasNetPlayer() const;
    virtual bool IsLocal() const;
    virtual bool PlayerDisabled() const;
    virtual const char *GetTrackIcon() const;
    virtual const char *GetPlayerName() const;
    virtual const char *UserName() const;

    virtual const User *GetUser() const; // fix ret type
    virtual Difficulty GetPlayerDifficulty() const;
    virtual Symbol GetPlayerDifficultySym() const;
    virtual bool PlayerDisconnected() const;
    virtual bool PlayerDisconnectedAtStart() const;
    virtual void DTSPopup(bool) const;
    virtual int GetBandMultiplier() const;
    virtual void PushGameplayOptions(VocalParam, int);
    virtual int GetNoBackFromBrink() const;
    virtual void RefreshPlayerHUD();

    virtual bool FailedAtStart();
    virtual bool IsDeployingOverdrive() const;
    virtual bool IsNoFailActive() const;
    virtual bool IsGameOver() const;
    virtual bool IsGamePaused() const;
    virtual void SetPlayingIntro(float);
    virtual void SetUserNameLabel(ObjectDir *, const char *);
    virtual bool InGameMode(Symbol) const;
    virtual bool IsScoring() const;

    virtual void Load() {}
    virtual void Unload() {}
    virtual bool IsLoaded() { return true; }
    virtual void FinishLoad() {}
    virtual void Draw() {}
    virtual void Poll(float);
    virtual void Jump(float) {}
    virtual void SetShowing(bool) {}
    virtual bool Showing() { return true; }
    virtual void SetDir(RndDir *) {}
    virtual RndDir *GetDir() = 0;
    virtual BandTrack *GetBandTrack() = 0;
    virtual Hmx::Object *GetObj(Symbol);
    virtual void SetSmasherGlowing(int, bool) {}
    virtual void PopSmasher(int) {}
    virtual void OnMissPhrase(int) {}
    virtual void RemovePlayer() {}

    Symbol GetType() const;
    const BandUser *GetBandUser() const;
    Player *GetPlayer() const;
    void StartPulseAnims(float);
    int GetTrackNum() const;

    TrackConfig mTrackConfig; // 0x1c
    float mLastRating; // 0x48
    CrowdMeterState mLastRatingState; // 0x4c
    bool unk50; // 0x50
    int mLastStreakCount; // 0x54
    int mSlotIdx; // 0x58
    GameplayOptions *mGameplayOptions; // 0x5c
    bool mIntroPlaying; // 0x60
    float mIntroEndMs; // 0x64
};

Track *NewTrack(BandUser *);
