#pragma once
#include "obj/Object.h"

enum VocalParam {
    kVocalParamAny,
    kVocalParamMicVolume,
    kVocalParamMic1Gain,
    kVocalParamMic2Gain,
    kVocalParamMic3Gain,
    kVocalParamCueVolume
};

class TrackInterface : public Hmx::Object {
public:
    TrackInterface(){}
    virtual ~TrackInterface(){}
    virtual void Init(){}
    virtual void PlayerInit(){}
    virtual void PostInit(){}

    // 29 pure virtuals
    virtual bool ShouldDisablePopupHelp() const = 0;
    virtual bool InGame() const = 0;
    virtual bool HasPlayer() const = 0;
    virtual bool HasLocalPlayer() const = 0;
    virtual bool HasNetPlayer() const = 0;
    virtual bool IsLocal() const = 0;
    virtual bool PlayerDisabled() const = 0;
    virtual const char* GetTrackIcon() const = 0;
    virtual const char* GetPlayerName() const = 0;
    virtual const char* UserName() const = 0;

    virtual int GetUser() const = 0; // fix ret type
    virtual int GetPlayerDifficulty() const = 0;
    virtual Symbol GetPlayerDifficultySym() const = 0;
    virtual bool PlayerDisconnected() const = 0;
    virtual bool PlayerDisconnectedAtStart() const = 0;
    virtual void DTSPopup(bool) const = 0;
    virtual int GetBandMultiplier() const = 0;
    virtual void PushGameplayOptions(VocalParam, int) = 0;
    virtual int GetNoBackFromBrink() const = 0;
    virtual void RefreshPlayerHUD() = 0;

    virtual bool FailedAtStart() = 0;
    virtual bool IsDeployingOverdrive() const = 0;
    virtual bool IsNoFailActive() const = 0;
    virtual bool IsGameOver() const = 0;
    virtual bool IsGamePaused() const = 0;
    virtual void SetPlayingIntro(float) = 0;
    virtual void SetUserNameLabel(ObjectDir*, const char*) = 0;
    virtual bool InGameMode(Symbol) const = 0;
    virtual bool IsScoring() const = 0;

    virtual void SetBonusGems(bool){}
    virtual void SetGemsEnabled(float){}
    virtual void SetGemsEnabledByPlayer(){}
    virtual void UpdateGems(){}
    virtual float NextKickNoteMs() const { return 3.4028235E+38f; }
    virtual Hmx::Object* GetSmasher(int){ return 0; } // TODO: this return type is almost definitely wrong, fix it
    virtual void ResetSmashers(bool){}
    virtual bool Lefty() const { return 0; }
    virtual void RebuildBeats(){}
    virtual void UpdateSlotXfms(){}
    virtual void SetWrapPoint(int){}
    virtual void UpdateShifts(){}
    virtual void RefreshCurrentShift(){}
    virtual void PlayKeyIntros(){}
    virtual bool IsScrolling() const { return true; }
    virtual void SetScreamThresholds(float, float){}
    virtual bool InTambourinePhrase() const { return false; }
    virtual int IncrementVolume(int){ return 0; }
    virtual bool IsCurrentVocalParam(VocalParam){ return false; }
    virtual void SetVocalStyle(int){}
    virtual void RebuildVocalHUD(){}
    virtual int NumSingers() const { return 0; }
    virtual bool UseVocalHarmony(){ return true; }
    virtual void SetCanDeploy(bool){}
    virtual int GetNumVocalParts();
    virtual bool ShowPitchCorrectionNotice() const { return 0; }
};