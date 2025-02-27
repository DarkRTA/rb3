#pragma once
#include "GemManager.h"
#include "Track.h"
#include "bandobj/GemTrackDir.h"
#include "beatmatch/FillInfo.h"
#include "game/BandUser.h"
#include "rndobj/Anim.h"

class GemTrack : public Track {
public:
    class RangeShift {
    public:
        RangeShift(int i1, int i2, float f1, float f2)
            : unk0(i1), unk4(i2), unk8(-1), unkc(f1), unk10(-1), unk14(f2), unk18(0),
              unk1c(0), unk20(0) {}
        int unk0;
        int unk4;
        float unk8;
        float unkc;
        float unk10;
        float unk14;
        bool unk18;
        int unk1c;
        int unk20;
    };

    GemTrack(BandUser *);
    virtual ~GemTrack();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Init();
    virtual void PlayerInit();
    virtual void PostInit();

    virtual void SetBonusGems(bool);
    virtual void SetGemsEnabled(float);
    virtual void SetGemsEnabledByPlayer();
    virtual void UpdateGems();
    virtual float NextKickNoteMs() const;
    virtual Hmx::Object *GetSmasher(int);
    virtual void ResetSmashers(bool);
    virtual bool Lefty() const { return mTrackConfig.IsLefty(); }
    virtual void RebuildBeats();
    virtual void UpdateSlotXfms();
    virtual void UpdateShifts();
    virtual void RefreshCurrentShift();
    virtual void PlayKeyIntros();

    virtual void Poll(float);
    virtual void Jump(float);
    virtual void SetDir(RndDir *);
    virtual RndDir *GetDir() { return mTrackDir; }
    virtual BandTrack *GetBandTrack();
    virtual void SetSmasherGlowing(int, bool);
    virtual void PopSmasher(int);
    virtual void OnMissPhrase(int);
    virtual void RemovePlayer();
    virtual void UpdateLeftyFlip();

    GemManager *GetGemManager();
    void HandleNewSong();
    void ApplyShiftImmediately(const RangeShift &);
    void ResetFills(bool);
    void UpdateShiftsToTick(int);
    void UpdateFills();
    void ChangeDifficulty(Difficulty, int);
    void DropIn(int);
    void SetPlayerState(const PlayerState &);
    void DrawFill(FillInfo *, int, int);
    void RedrawTrackElements(float);
    void DrawTrackElements(int, int);
    void See(float, int);
    void Hit(float, int, int);
    void Miss(float, int, int);
    void Pass(int);
    void Ignore(int);
    void PartialHit(float, int, unsigned int, int);
    void FillHit(int, int);
    void SetFretButtonPressed(int, bool);
    void ReleaseGem(float, int);
    void SetInCoda(bool);
    void UpdateEffects(int);
    void OverrideRangeShift(float, float);
    void SetEnableSlot(int, bool);
    void DrawBeatLine(Symbol, int, int, bool);
    void DrawBeatLines(int, int);
    GemTrackDir *GetTrackDir() const { return mTrackDir; }
    bool ShiftsEnabled() const;
    float TickToOffset(int) const;
    float GetRange() const { return mRange; }
    float GetOffset() const { return mOffset; }

    bool mResetFills; // 0x68
    bool mUseFills; // 0x69
    ObjPtr<GemTrackDir> mTrackDir; // 0x6c
    int mLastTopTick; // 0x78
    int mLastBottomTick; // 0x7c
    GemManager *mGemManager; // 0x80
    PlayerState mPlayerState; // 0x84
    PlayerState mLastPlayerState; // 0x9c
    unsigned short unkb4; // 0xb4
    bool mUpdateShifting; // 0xb6
    bool mEnableShifting; // 0xb7
    std::vector<RangeShift> mRangeShifts; // 0xb8
    RangeShift *mCurrentRangeShift; // 0xc0
    float mRange; // 0xc4
    float mOffset; // 0xc8
    ObjPtr<RndAnimatable> mUpcomingShiftMaskAnim; // 0xcc
    int unkd8; // 0xd8 - mBeatLineSubdivisionTicks?
    ObjPtrList<Task> mKeyIntroTasks; // 0xdc
};