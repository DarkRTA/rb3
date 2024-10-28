#pragma once
#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/VocalTrackDir.h"
#include "bandobj/BandCrowdMeter.h"
#include "bandobj/EndingBonus.h"
#include "bandobj/GemTrackResourceManager.h"
#include "rndobj/EventTrigger.h"

class TrackPanelDir : public TrackPanelDirBase {
public:
    TrackPanelDir();
    OBJ_CLASSNAME(TrackPanelDir)
    OBJ_SET_TYPE(TrackPanelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~TrackPanelDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void ConfigureTracks(bool);
    virtual void ConfigureTrack(int);
    virtual void AssignTracks();
    virtual void AssignTrack(int, TrackInstrument, bool);
    virtual void RemoveTrack(int);
    virtual void SetConfiguration(Hmx::Object*, bool);
    virtual void ReapplyConfiguration(bool);
    virtual void Reset();
    virtual void ResetAll();
    virtual void PlayIntro();
    virtual bool TracksExtended() const { return mTracksExtended; }
    virtual void GameOver();
    virtual void HideScore();
    virtual void Coda();
    virtual void CodaEnd();
    virtual void SetCodaScore(int);
    virtual void SoloEnd(BandTrack*, int, Symbol);
    virtual void SetTrackPanel(TrackPanelInterface*);
    virtual void ResetPlayers();
    virtual void StartFinale();
    virtual void SetMultiplier(int, bool);
    virtual void SetCrowdRating(float);
    virtual void CodaSuccess();
    virtual void UnisonStart(int);
    virtual void UnisonEnd();
    virtual void UnisonSucceed();
    virtual EndingBonus* GetEndingBonus(){ return mEndingBonus; }
    virtual BandCrowdMeter* GetCrowdMeter(){ return mCrowdMeter; }
    virtual void SetupApplauseMeter(int, const char*, const char*, RndDir*, RndDir*, bool, Symbol);
    virtual void DisablePlayer(int, bool);
    virtual void EnablePlayer(int);
    virtual void FadeBotbBandNames(bool);
    virtual void CleanUpChordMeshes();
    virtual void SetApplauseMeterScale(int, int);
    virtual void StartPulseAnims(float);
    virtual GemTrackResourceManager* GetGemTrackResourceManager() const { return mGemTrackRsrcMgr; }

    void GameWon();
    void GameLost();
    void ConfigureCrowdMeter();
    void ApplyVocalTrackShowingStatus();
    TrackInstrument GetInstrument(int) const;
    void SetBotbBandIcon(ObjectDir*, RndDir*, bool);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(TrackPanelDir)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(TrackPanelDir)

    int unk244; // 0x244
    int mTestMultiplier; // 0x248
    int unk24c; // 0x24c
    int unk250; // 0x250
    int unk254; // 0x254
    ObjPtr<VocalTrackDir, ObjectDir> mVocalTrack; // 0x258
    ObjPtr<BandCrowdMeter, ObjectDir> mCrowdMeter; // 0x264
    ObjPtr<RndDir, ObjectDir> mBandScoreMultiplier; // 0x270
    ObjPtr<EventTrigger, ObjectDir> mBandScoreMultiplierTrig; // 0x27c
    ObjPtr<EndingBonus, ObjectDir> mEndingBonus; // 0x288
    ObjPtr<RndDir, ObjectDir> mScoreboard; // 0x294
    ObjPtr<RndGroup, ObjectDir> mPulseAnimGrp; // 0x2a0
    bool unk2ac; // 0x2ac
    bool unk2ad; // 0x2ad
    bool mTracksExtended; // 0x2ae
    ObjPtr<GemTrackResourceManager, ObjectDir> mGemTrackRsrcMgr; // 0x2b0
    bool mVocals; // 0x2bc
    bool mVocalsNet; // 0x2bd
    int mGemInst[4]; // 0x2c0
    bool mGemNet[4]; // 0x2d0
};