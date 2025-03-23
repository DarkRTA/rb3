#pragma once
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/MatAnim.h"
#include "bandobj/CrowdMeterIcon.h"
#include "bandobj/TrackInstruments.h"

class TrackPanelInterface;

class BandCrowdMeter : public RndDir {
public:
    class IconData {
    public:
        IconData(BandCrowdMeter *, CrowdMeterIcon *, RndGroup *);
        ~IconData() {}

        void Reset();
        void SetUsed(bool);
        void SetVal(float);
        bool Used() const { return mUsed; }

        ObjPtr<CrowdMeterIcon> unk0; // 0x0
        ObjPtr<RndGroup> unkc; // 0xc
        bool unk18; // 0x18
        bool unk19; // 0x19
        bool unk1a; // 0x1a
        bool mUsed; // 0x1b
        float unk1c; // 0x1c
        bool unk20; // 0x20
    };

    BandCrowdMeter();
    OBJ_CLASSNAME(BandCrowdMeterDir);
    OBJ_SET_TYPE(BandCrowdMeterDir);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual ~BandCrowdMeter();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void Poll();

    bool Disabled() const;
    void SetCrowd(float);
    void SetIconVal(int, float);
    void SetMaxed(bool);
    float GetPeakValue();
    void Reset();
    void UpdateExcitement(bool);
    void SetPlayerIconState(int, CrowdMeterState);
    void Deploy(int);
    void StopDeploy(int);
    void EnablePlayer(int);
    void DisablePlayer(int);
    void ShowPeakArrow(bool);
    void OnShowWorstCase();
    void Disable();
    void Enable();
    void SetPlayerValue(int, float);
    void SetPlayerQuarantined(int, bool);
    void DropInPlayer(int);
    void DropOutPlayer(int);
    bool Draining() const;
    bool Deploying() const;
    void UpdateJoinInProgress(bool, bool);
    void FailedJoinInProgress();
    void UpdatePlayers(const std::vector<TrackInstrument> &);
    float InitialCrowdRating() const;
    CrowdMeterIcon *PlayerIcon(int);
    void SetTrackPanel(TrackPanelInterface *panel) { mTrackPanel = panel; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(BandCrowdMeter)
    static void Init() { Register(); }
    REGISTER_OBJ_FACTORY_FUNC(BandCrowdMeter)

    std::vector<IconData> mIconData; // 0x18c
    bool mMaxed; // 0x194
    float mPeakValue; // 0x198
    bool mDisabled; // 0x19c
    std::vector<Hmx::Color> mLevelColors; // 0x1a0
    int mExcitement; // 0x1a8 - excitementlevel
    TrackPanelInterface *mTrackPanel; // 0x1ac
    ObjPtrList<RndGroup> mOrderedPeaks; // 0x1b0
    ObjPtr<EventTrigger> mBandEnergyDeployTrig; // 0x1c0
    ObjPtr<EventTrigger> mBandEnergyStopTrig; // 0x1cc
    ObjPtr<EventTrigger> mDisabledStartTrig; // 0x1d8
    ObjPtr<EventTrigger> mDisabledStopTrig; // 0x1e4
    ObjPtr<EventTrigger> mShowPeakArrowTrig; // 0x1f0
    ObjPtr<EventTrigger> mHidePeakArrowTrig; // 0x1fc
    std::vector<ObjPtr<EventTrigger> > mExcitementTrigs; // 0x208
    ObjPtr<EventTrigger> mCanJoinTrig; // 0x210
    ObjPtr<EventTrigger> mCannotJoinTrig; // 0x21c
    ObjPtr<EventTrigger> mJoinInvalidTrig; // 0x228
    int unk234; // 0x234
    ObjPtr<RndMatAnim> mCrowdMeterAnim; // 0x238
    float mValue; // 0x244
    float mIconValues[5]; // 0x248
};