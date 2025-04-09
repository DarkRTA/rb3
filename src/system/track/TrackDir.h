#pragma once
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Group.h"
#include "ui/PanelDir.h"
#include "obj/ObjPtr_p.h"

class RndGroup;
class RndMesh;
class TrackTest;
class TrackWidget;
class ArpeggioShapePool;

/** "Base class for track system. Contains configuration for
 * track speed, length, slot positions. Manages TrackWidget instances." */
class TrackDir : public PanelDir {
public:
    TrackDir();
    OBJ_CLASSNAME(TrackDir)
    OBJ_SET_TYPE(TrackDir)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual ~TrackDir();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void DrawShowing();
    virtual void Poll();
    // everything below this is for TrackDir (i.e. not from PanelDir)
    virtual void SyncFingerFeedback();
    virtual void SetDisplayRange(float) {}
    virtual void SetDisplayOffset(float, bool) {}
    virtual RndDir *SmasherPlate();
    virtual float GetFretPosOffset(int) const { return 0; }
    virtual int GetNumFretPosOffsets() const { return 0; }
    virtual float GetCurrentChordLabelPosOffset() const { return 0; }
    virtual int PrepareChordMesh(unsigned int);
    virtual RndMesh *GetChordMesh(unsigned int, bool) { return nullptr; }
    virtual void SetUnisonProgress(float) {}
    virtual void ClearChordMeshRefCounts();
    virtual void DeleteUnusedChordMeshes();
    virtual void AddChordRepImpl(
        RndMesh *,
        TrackWidget *,
        TrackWidget *,
        TrackWidget *,
        float,
        const std::vector<int> &,
        class String
    ) {
        MILO_ASSERT(0, 0x68);
    }
    virtual ArpeggioShapePool *GetArpeggioShapePool() { return nullptr; }
    virtual bool IsBlackKey(int) const;
    virtual void KeyMissLeft() {}
    virtual void KeyMissRight() {}
    virtual bool IsActiveInSession() const { return false; }
    virtual void PreDraw() {}
    virtual void PostDraw() {}

    void AddActiveWidget(class TrackWidget *);
    void AddTestWidget(class TrackWidget *, int);
    void ClearAllWidgets();
    void ClearAllGemWidgets();
    /** "Toggle running the track in test mode" */
    void ToggleRunning();
    float CutOffY() const;
    void SetupKeyShifting(RndDir *);
    void ResetKeyShifting();
    void PollActiveWidgets();
    float TopSeconds() const;
    float BottomSeconds() const;
    float SecondsToY(float) const;
    float YToSeconds(float) const;
    void SetSlotXfm(int, const Transform &);
    void MakeSecondsXfm(float, Transform &) const;
    void MakeWidgetXfm(int, float, Transform &) const;
    void MakeSlotXfm(int, Transform &) const;
    void SetScrollSpeed(float);
    float ViewTimeSeconds() const;
    void SetRunning(bool);
    bool WarnOnResort() const { return mWarnOnResort; }
    const Transform &SlotAt(int idx) const { return mSlots[idx]; }
    bool IsEnabled() const {
        return IsActiveInSession() || mShowingWhenEnabled->Showing();
    }

    DECLARE_REVS;
    NEW_OBJ(TrackDir)

    static void Register() { REGISTER_OBJ_FACTORY(TrackDir); }

    bool mRunning; // 0x1d6
    /** "Should contain everything to draw (except widget resources)" */
    ObjPtr<RndGroup> mDrawGroup; // 0x1d8
    /** "Animated at rate where frame=y position of now bar" */
    ObjPtr<RndGroup> mAnimGroup; // 0x1e4
    /** "World units widgets move per second". Ranges from 1 to 10000. */
    float mYPerSecond; // 0x1f0
    /** "Distance where widgets are pushed onto track" */
    float mTopY; // 0x1f4
    /** "Distance where widgets are pruned from track" */
    float mBottomY; // 0x1f8
    std::vector<Transform> mSlots; // 0x1fc
    std::vector<Transform> vec2; // 0x204
    bool mWarnOnResort; // 0x20c
    std::vector<TrackWidget *> mActiveWidgets; // 0x210
    ObjPtr<RndGroup> mShowingWhenEnabled; // 0x218
    ObjPtr<RndGroup> mStationaryBack; // 0x224
    ObjPtr<RndGroup> mKeyShiftStationaryBack; // 0x230
    ObjPtr<RndGroup> mStationaryBackAfterKeyShift; // 0x23c
    ObjPtr<RndGroup> mMovingBack; // 0x248
    ObjPtr<RndGroup> mKeyShiftMovingBack; // 0x254
    ObjPtr<RndGroup> mKeyShiftStationaryMiddle; // 0x260
    ObjPtr<RndGroup> mStationaryMiddle; // 0x26c
    ObjPtr<RndGroup> mMovingFront; // 0x278
    ObjPtr<RndGroup> mKeyShiftMovingFront; // 0x284
    ObjPtr<RndGroup> mKeyShiftStationaryFront; // 0x290
    ObjPtr<RndGroup> mStationaryFront; // 0x29c
    ObjPtr<RndGroup> mAlwaysShowing; // 0x2a8
    ObjPtr<RndTransformable> mRotatorCam; // 0x2b4
    ObjPtr<RndEnviron> mTrack; // 0x2c0
    ObjPtr<RndEnviron> mTrackGems; // 0x2cc
    Transform unk2d8; // 0x2d8
    Transform unk308; // 0x308
    Transform unk338; // 0x338
    float unk368; // 0x368
#ifdef MILO_DEBUG
    TrackTest *mTest; // 0x36c
#endif
};
