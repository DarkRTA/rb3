#pragma once
#include "Track.h"
#include "game/BandUser.h"

class GemTrack : public Track {
public:
    GemTrack(BandUser*);
    virtual ~GemTrack();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Init();
    virtual void PlayerInit();
    virtual void PostInit();

    virtual void SetBonusGems(bool);
    virtual void SetGemsEnabled(float);
    virtual void SetGemsEnabledByPlayer();
    virtual void UpdateGems();
    virtual float NextKickNoteMs() const;
    virtual Hmx::Object* GetSmasher(int);
    virtual void ResetSmashers(bool);
    virtual bool Lefty() const;
    virtual void RebuildBeats();
    virtual void UpdateSlotXfms();
    virtual void UpdateShifts();
    virtual void RefreshCurrentShift();
    virtual void PlayKeyIntros();
    
    virtual void Poll(float);
    virtual void Jump(float);
    virtual void SetDir(RndDir*);
    virtual RndDir* GetDir();
    virtual BandTrack* GetBandTrack();
    virtual void SetSmasherGlowing(int, bool);
    virtual void PopSmasher(int);
    virtual void OnMissPhrase(int);
    virtual void RemovePlayer();
    virtual void UpdateLeftyFlip();
};