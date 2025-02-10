#pragma once
#include "bandobj/NoteTube.h"
#include "bandobj/VocalTrackDir.h"
#include "bandtrack/Lyric.h"
#include "bandtrack/Track.h"
#include "bandtrack/VocalStyle.h"
#include "game/BandUser.h"
#include "game/VocalPlayer.h"
#include "obj/Data.h"
#include "rndobj/Group.h"
#include <deque>
#include <vector>

class TambourineGem {
public:
    TambourineGem() : unk0(0), unk4(-1), unk8(2) {}

    float unk0;
    int unk4;
    int unk8;
};

class TambourineGemPool {
public:
    TambourineGemPool();
    ~TambourineGemPool();
    void FreeUsedGems() {
        while (!mUsedGems.empty()) {
            mFreeGems.push_back(mUsedGems.front());
            mUsedGems.front()->unk8 = 2;
            mUsedGems.pop_front();
        }
    }

    std::deque<TambourineGem *> mFreeGems; // 0x0
    std::deque<TambourineGem *> mUsedGems; // 0x28
    int unk50; // 0x50 - TambourineManager*?
};

class VocalTrack : public Track {
public:
    class LyricShift {
    public:
        int unk0;
        int unk4;
        int unk8;
    };

    class RangeShift {
    public:
        int unk0;
        int unk4;
        int unk8;
        int unkc;
        int unk10;
        int unk14;
    };

    VocalTrack(BandUser *);
    virtual ~VocalTrack();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Init();
    virtual void PushGameplayOptions(VocalParam, int);
    virtual bool IsScrolling() const;
    virtual bool InTambourinePhrase() const;
    virtual int IncrementVolume(int);
    virtual bool IsCurrentVocalParam(VocalParam);
    virtual void RebuildVocalHUD();
    virtual int NumSingers() const;
    virtual bool UseVocalHarmony();
    virtual void SetCanDeploy(bool);
    virtual int GetNumVocalParts();
    virtual bool ShowPitchCorrectionNotice() const;
    virtual void Poll(float);
    virtual void SetDir(RndDir *);
    virtual RndDir *GetDir();
    virtual BandTrack *GetBandTrack();
    virtual void SetVocalStyle(VocalStyle);

    void InitPlatePool();
    void DumpAllPlates();
    void DumpPlates(std::deque<TubePlate *> &, const char *);
    void ClearLyrics();
    void ClearMarkers();
    void ClearAllTubePlates();
    void InitPlateList(std::deque<TubePlate *> &, int, int);
    void ReturnFirstMarker();
    void UpdateMarkerVisibility(float, float);
    void InvalidateMarkers(float);
    void UpdateAllTubePlates(float);
    void UpdateTubePlates(std::deque<TubePlate *> &, float, float, bool);
    void ClearTubePlates(std::deque<TubePlate *> &);
    void ResetAllTubePlates();
    void ResetTubePlates(std::deque<TubePlate *> &);
    void HookupTubePlates(NoteTube *);
    TubePlate *GetCurrentPlate(std::deque<TubePlate *> &, int);
    void ResetTimingData();
    void ReadTimingData(const DataArray *);
    void RebuildHUD();
    void CreateMarker(Symbol, float, bool);
    void CreateMarkers();
    void ConfigNoteTube(bool, int, int, bool, float);

    bool unk68; // 0x68
    int unk6c; // 0x6c - vocal style
    int unk70; // 0x70
    float unk74; // 0x74
    float unk78; // 0x78
    int unk7c; // 0x7c
    ObjPtr<VocalTrackDir> mDir; // 0x80
    ObjPtr<VocalPlayer> mPlayer; // 0x8c
    std::deque<LyricPlate *> mLyricsLead; // 0x98
    std::deque<LyricPlate *> mLyricsHarmony; // 0xc0
    float unke8;
    float unkec;
    float unkf0;
    int unkf4;
    int unkf8;
    int unkfc;
    int unk100;
    int unk104;
    int unk108;
    int unk10c[3];
    int unk118[2];
    int unk120[2];
    bool unk128; // 0x128
    std::vector<std::deque<TubePlate *> > mFrontTubePlates; // 0x12c
    std::vector<std::deque<TubePlate *> > mBackTubePlates; // 0x134
    std::vector<std::deque<TubePlate *> > mPhonemeTubePlates; // 0x13c
    std::deque<TubePlate *> mLeadDeployPlates; // 0x144
    std::deque<TubePlate *> mHarmonyDeployPlates; // 0x16c
    std::vector<RndMesh *> unk194; // 0x194
    int unk19c; // 0x19c
    std::deque<std::pair<RndMesh *, float> > unk1a0; // 0x1a0
    ObjPtr<RndGroup> unk1c8; // 0x1c8
    TambourineGemPool *mTambourineGemPool; // 0x1d4
    std::deque<TambourineGem *> mTambourineGems; // 0x1d8
    int unk200; // 0x200
    int unk204; // 0x204
    int unk208; // 0x208
    int unk20c; // 0x20c
    int unk210; // 0x210
    std::deque<RangeShift> mRangeShifts; // 0x214
    float unk23c; // 0x23c
    float unk240; // 0x240
    std::deque<LyricShift> mLeadLyricShifts; // 0x244
    std::deque<LyricShift> mHarmonyLyricShifts; // 0x26c
    float unk294;
    float unk298;
    float unk29c;
    float unk2a0;
    float unk2a4;
    float unk2a8;
    float unk2ac;
    float unk2b0;
    int unk2b4[3]; // 0x2b4
    float mStaticDeployZoneXSize; // 0x2c0
    float mStaticDeployBufferX; // 0x2c4
    float mStaticDeployMarginX; // 0x2c8
    float mLyricShiftMs; // 0x2cc
    float mLyricShiftQuickMs; // 0x2d0
    float mLyricShiftAnticipationMs; // 0x2d4
    float mMinLyricHighlightMs; // 0x2d8
    float mMinPhraseHighlightMs; // 0x2dc
    float mLyricOverlapWindowMs; // 0x2e0
    bool unk2e4;
    NoteTube *mNoteTube; // 0x2e8
    bool unk2ec;
};
