#ifndef TRACK_TRACKDIR_H
#define TRACK_TRACKDIR_H
#include "obj/Object.h"
#include "ui/PanelDir.h"
#include "obj/ObjPtr_p.h"

class RndGroup;
class RndMesh;
class TrackTest;
class TrackWidget;
class ArpeggioShapePool;

class TrackDir : public PanelDir {
public:
    TrackDir();
    OBJ_CLASSNAME(TrackDir)
    OBJ_SET_TYPE(TrackDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~TrackDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void DrawShowing();
    virtual void Poll();
    virtual void SyncFingerFeedback();
    virtual void SetDisplayRange(float){}
    virtual void SetDisplayOffset(float, bool){}
    virtual RndDir* SmasherPlate();
    virtual float GetFretPosOffset(int) const;
    virtual int GetNumFretPosOffsets() const { return 0; }
    virtual float GetCurrentChordLabelPosOffset() const;
    virtual int PrepareChordMesh(unsigned int);
    virtual int GetChordMesh(unsigned int, bool);
    virtual void SetUnisonProgress(float){}
    virtual void ClearChordMeshRefCounts();
    virtual void DeleteUnusedChordMeshes();
    virtual void AddChordImpl(RndMesh*, TrackWidget*, TrackWidget*, TrackWidget*, float, const std::vector<int>&, class String);
    virtual ArpeggioShapePool* GetArpeggioShapePool();
    virtual bool IsBlackKey(int) const;
    virtual void KeyMissLeft();
    virtual void KeyMissRight();
    virtual bool IsActiveInSession() const { return false; }
    virtual void PreDraw(){}
    virtual void PostDraw(){}

    void AddActiveWidget(class TrackWidget*);
    void AddTestWidget(class TrackWidget*, int);
    void ClearAllWidgets();
    void ClearAllGemWidgets();
    void ToggleRunning();
    float CutOffY() const;
    void SetupKeyShifting(RndDir*);
    void ResetKeyShifting();
    void PollActiveWidgets();
    float TopSeconds() const;
    float BottomSeconds() const;
    float SecondsToY(float) const;
    float YToSeconds(float) const;
    void SetSlotXfm(int, const Transform&);
    void MakeSecondsXfm(float, Transform&) const;
    void MakeWidgetXfm(int, float, Transform&) const;
    void MakeSlotXfm(int, Transform&) const;
    void SetScrollSpeed(float);
    float ViewTimeSeconds() const;
    void SetRunning(bool);
    bool WarnOnResort() const { return mWarnOnResort; }
    const Transform& SlotAt(int idx) const { return mSlots[idx]; }

    DECLARE_REVS;
    NEW_OBJ(TrackDir)

    static void Register(){
        REGISTER_OBJ_FACTORY(TrackDir);
    }

    bool mRunning; // 0x1d6
    ObjPtr<RndGroup, ObjectDir> mDrawGroup; // 0x1d8
    ObjPtr<RndGroup, ObjectDir> mAnimGroup; // 0x1e4
    float mYPerSecond; // 0x1f0
    float mTopY; // 0x1f4
    float mBottomY; // 0x1f8
    std::vector<Transform> mSlots; // 0x1fc
    std::vector<Transform> vec2; // 0x204
    bool mWarnOnResort; // 0x20c
    std::vector<TrackWidget*> mActiveWidgets; // 0x210
    ObjPtr<RndGroup, ObjectDir> mShowingWhenEnabled; // 0x218
    ObjPtr<RndGroup, ObjectDir> mStationaryBack; // 0x224
    ObjPtr<RndGroup, ObjectDir> mKeyShiftStationaryBack; // 0x230
    ObjPtr<RndGroup, ObjectDir> mStationaryBackAfterKeyShift; // 0x23c
    ObjPtr<RndGroup, ObjectDir> mMovingBack; // 0x248
    ObjPtr<RndGroup, ObjectDir> mKeyShiftMovingBack; // 0x254
    ObjPtr<RndGroup, ObjectDir> mKeyShiftStationaryMiddle; // 0x260
    ObjPtr<RndGroup, ObjectDir> mStationaryMiddle; // 0x26c
    ObjPtr<RndGroup, ObjectDir> mMovingFront; // 0x278
    ObjPtr<RndGroup, ObjectDir> mKeyShiftMovingFront; // 0x284
    ObjPtr<RndGroup, ObjectDir> mKeyShiftStationaryFront; // 0x290
    ObjPtr<RndGroup, ObjectDir> mStationaryFront; // 0x29c
    ObjPtr<RndGroup, ObjectDir> mAlwaysShowing; // 0x2a8
    ObjPtr<RndTransformable, ObjectDir> mRotatorCam; // 0x2b4
    ObjPtr<RndEnviron, ObjectDir> mTrack; // 0x2c0
    ObjPtr<RndEnviron, ObjectDir> mTrackGems; // 0x2cc
    Transform unk2d8;
    Transform unk308;
    Transform unk338;
    float unk368;
#ifdef MILO_DEBUG
    TrackTest* mTest; // 0x36c
#endif
};

#endif // TRACK_TRACKDIR_H