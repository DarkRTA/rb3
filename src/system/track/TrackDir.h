#ifndef TRACK_TRACKDIR_H
#define TRACK_TRACKDIR_H
#include "obj/Object.h"
#include "ui/PanelDir.h"
#include "obj/ObjPtr_p.h"

class RndGroup;
class RndMesh;
class TrackTest;
class TrackWidget;

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
    virtual void SetDisplayRange(float);
    virtual void SetDisplayOffset(float, bool);
    virtual int SmasherPlate(); // change return type
    virtual float GetFretPosOffset(int) const;
    virtual int GetNumFretPosOffets() const;
    virtual float GetCurrentChordLabelPosOffset() const;
    virtual int PrepareChordMesh(unsigned int);
    virtual int GetChordMesh(unsigned int, bool);
    virtual void SetUnisonProgress(float);
    virtual void ClearChordMeshRefCounts();
    virtual void DeleteUnusedChordMeshes();
    virtual void AddChordImpl(RndMesh*, TrackWidget*, TrackWidget*, TrackWidget*, float, const std::vector<int>&, class String);
    virtual int GetArpeggioShapePool();
    virtual bool IsBlackKey(int) const;
    virtual void KeyMissLeft();
    virtual void KeyMissRight();
    virtual bool IsActiveInSession() const;
    virtual void PreDraw();
    virtual void PostDraw();

    float SecondsToY(float) const;
    void AddActiveWidget(class TrackWidget*);
    void AddTestWidget(class TrackWidget*, int);
    void ClearAllWidgets();
    void ToggleRunning();
    float CutOffY() const;
    NEW_OBJ(TrackDir)

    bool mRunning; // 0x1d6
    ObjPtr<RndGroup, ObjectDir> mDrawGroup; // 0x1d8
    ObjPtr<RndGroup, ObjectDir> mAnimGroup; // 0x1e4
    float mYPerSecond; // 0x1f0
    float mTopY; // 0x1f4
    float mBottomY; // 0x1f8
    std::vector<Transform> mSlots; // 0x1fc
    std::vector<int> vec2; // 0x204
    bool mWarnOnResort; // 0x20c
    std::vector<void*> vec3; // 0x210
    ObjPtr<RndGroup, ObjectDir> unk218;
    ObjPtr<RndGroup, ObjectDir> unk224;
    ObjPtr<RndGroup, ObjectDir> unk230;
    ObjPtr<RndGroup, ObjectDir> unk23c;
    ObjPtr<RndGroup, ObjectDir> unk248;
    ObjPtr<RndGroup, ObjectDir> unk254;
    ObjPtr<RndGroup, ObjectDir> unk260;
    ObjPtr<RndGroup, ObjectDir> unk26c;
    ObjPtr<RndGroup, ObjectDir> unk278;
    ObjPtr<RndGroup, ObjectDir> unk284;
    ObjPtr<RndGroup, ObjectDir> unk290;
    ObjPtr<RndGroup, ObjectDir> unk29c;
    ObjPtr<RndGroup, ObjectDir> unk2a8;
    ObjPtr<RndTransformable, ObjectDir> unk2b4;
    ObjPtr<RndEnviron, ObjectDir> unk2c0;
    ObjPtr<RndEnviron, ObjectDir> unk2cc;
    Transform unk2d8;
    Transform unk308;
    Transform unk338;
    float unk368;
    TrackTest* mTest;
};

#endif // TRACK_TRACKDIR_H