#pragma once
#include "bandobj/BandTrack.h"
#include "bandobj/TrackInterface.h"
#include "game/BandUser.h"
#include "obj/Object.h"
#include "rndobj/Dir.h"

class Track : public TrackInterface {
public:
    Track(BandUser*);
    virtual ~Track(){}
    virtual DataNode Handle(DataArray*, bool);

    virtual bool ShouldDisablePopupHelp() const;
    virtual bool InGame() const;
    virtual bool HasPlayer() const;
    virtual bool HasLocalPlayer() const;
    virtual bool HasNetPlayer() const;
    virtual bool IsLocal() const;
    virtual bool PlayerDisabled() const;
    virtual const char* GetTrackIcon() const;
    virtual const char* GetPlayerName() const;
    virtual const char* UserName() const;

    virtual int GetUser() const; // fix ret type
    virtual int GetPlayerDifficulty() const;
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
    virtual void SetUserNameLabel(ObjectDir*, const char*);
    virtual bool InGameMode(Symbol) const;
    virtual bool IsScoring() const;
    
    virtual void Load();
    virtual void Unload();
    virtual bool IsLoaded();
    virtual void FinishLoad();
    virtual void Draw();
    virtual void Poll(float);
    virtual void Jump(float);
    virtual void SetShowing(bool);
    virtual bool Showing();
    virtual void SetDir(RndDir*);
    virtual RndDir* GetDir() = 0;
    virtual BandTrack* GetBandTrack() = 0;
    virtual Hmx::Object* GetObj(Symbol);
    virtual void SetSmasherGlowing(int, bool);
    virtual void PopSmasher(int);
    virtual void OnMissPhrase(int);
    virtual void RemovePlayer();
};