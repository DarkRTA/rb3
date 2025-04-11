#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Text.h"
#include "obj/ObjPtr_p.h"
#include "track/TrackWidgetImp.h"
#include "track/TrackDir.h"

class RndEnviron;

/** "Any object that is placed on the track and scrolls towards the
 * player.  Can have any number of meshes and an environment. Drawn efficiently
 * and pruned automatically by TrackDir." */
class TrackWidget : public RndDrawable {
public:
    enum WidgetType {
        kImmediateWidget = 0,
        kMultiMeshWidget = 1,
        kTextWidget = 2,
        kMatWidget = 3
    };
    TrackWidget();
    OBJ_CLASSNAME(TrackWidget)
    OBJ_SET_TYPE(TrackWidget)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Mats(std::list<class RndMat *> &, bool);
    virtual void DrawShowing();
    virtual ~TrackWidget();

    void SetScale(float);
    void Clear();
    void SyncImp();
    void Init();
    void Poll();
    void CheckValid() const;
    void CheckScales() const;
    void SetInactive();
    void SetTextAlignment(RndText::Alignment);
    int Size() const;
    void ApplyOffsets(Transform &);
    void UpdateActiveStatus();
    void RemoveAt(float);
    void RemoveAt(float, int);
    float GetFirstInstanceY();
    void AddInstance(Transform, float);
    void AddTextInstance(const Transform &, class String, bool);
    void AddMeshInstance(const Transform &, RndMesh *, float);
    void SetTrackDir(TrackDir *dir) { mTrackDir = dir; }
    bool Empty();

    float NewYOffset(float secs) const { return mYOffset + mTrackDir->SecondsToY(secs); }
    void SetBaseLength(float len) { mBaseLength = len; }

    DataNode OnSetMeshes(const DataArray *);
    DataNode OnAddInstance(const DataArray *);
    DataNode OnAddTextInstance(const DataArray *);
    DataNode OnAddMeshInstance(const DataArray *);

    NEW_OBJ(TrackWidget)
    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS

    static void Register() { REGISTER_OBJ_FACTORY(TrackWidget); }

    /** "Meshes used to draw widgets, drawn in order" */
    ObjPtrList<RndMesh> mMeshes; // 0x20
    ObjPtrList<RndMesh> mMeshesLeft; // 0x30
    ObjPtrList<RndMesh> mMeshesSpan; // 0x40
    ObjPtrList<RndMesh> mMeshesRight; // 0x50
    /** "Environment used to draw widget" */
    ObjPtr<RndEnviron> mEnviron; // 0x60
    /** "Length of unscaled geometry, should be 0 if no duration".
     * Ranges from 1e-2 to 1000. */
    float mBaseLength; // 0x6c
    /** "Width of unscaled geometry, should be 0 if no scaling".
     * Ranges from 1e-2 to 1000. */
    float mBaseWidth; // 0x70
    /** "X offset to be applied to all widget instances" */
    float mXOffset; // 0x74
    /** "Y offset to be applied to all widget instances" */
    float mYOffset; // 0x78
    /** "Z offset to be applied to all widget instances" */
    float mZOffset; // 0x7c
    TrackDir *mTrackDir; // 0x80
    TrackWidgetImpBase *mImp; // 0x84
    ObjPtr<RndFont> mFont; // 0x88
    ObjPtr<RndText> mTextObj; // 0x94
    RndText::Alignment mTextAlignment; // 0xa0
    /** "Primary color for text instances" */
    Hmx::Color mTextColor; // 0xa4
    /** "Secondary color for text instances" */
    Hmx::Color mAltTextColor; // 0xb4
    ObjPtr<RndMat> mMat; // 0xc4
    // 0xd0
    bool mActive : 1; // 0xd0 >> 7 & 1
    bool mWideWidget : 1; // 0xd0 >> 6 & 1
    /** "Allow meshes to be rotated/scaled" */
    bool mAllowRotation : 1; // 0xd0 >> 5 & 1
    /** "Allow widget instances to shift their X/Z coordinates in coordination with their
     * smasher during a keyboard lane shift" */
    bool mAllowShift : 1; // 0xd0 >> 4 & 1
    /** "Individual lines can have different rotations" */
    bool mAllowLineRotation : 1; // 0xd0 >> 3 & 1
    int mWidgetType : 3; // 0xd0 & 7?
    int mMaxMeshes : 9;
    int mCharsPerInst : 10;
    int mMaxTextInstances : 10;
};
