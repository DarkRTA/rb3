#ifndef TRACK_TRACKWIDGET_H
#define TRACK_TRACKWIDGET_H
#include "rndobj/Draw.h"
#include "rndobj/Text.h"
#include "obj/ObjPtr_p.h"
#include "track/TrackWidgetImp.h"

class RndEnviron;
class TrackDir;

class TrackWidget : public RndDrawable {
public:
    TrackWidget();
    OBJ_CLASSNAME(TrackWidget)
    OBJ_SET_TYPE(TrackWidget)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void DrawShowing();
    virtual ~TrackWidget();

    void Clear();
    void SyncImp();
    void Init();
    void Poll();
    void CheckValid() const;
    void CheckScales() const;
    void SetInactive();
    void SetTextAlignment(RndText::Alignment);
    bool Empty();
    void ApplyOffsets(Transform&);
    void UpdateActiveStatus();
    void RemoveAt(float);
    float GetFirstInstanceY();
    void AddInstance(Transform, float);
    void AddTextInstance(const Transform&, class String, bool);
    void AddMeshInstance(const Transform&, RndMesh*, float);
    void SetTrackDir(TrackDir* dir){ mTrackDir = dir; }

    DataNode OnSetMeshes(const DataArray*);
    DataNode OnAddInstance(const DataArray*);
    DataNode OnAddTextInstance(const DataArray*);
    DataNode OnAddMeshInstance(const DataArray*);

    NEW_OBJ(TrackWidget)
    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS

    ObjPtrList<RndMesh, class ObjectDir> mMeshes; // 0x20
    ObjPtrList<RndMesh, class ObjectDir> mMeshesLeft; // 0x30
    ObjPtrList<RndMesh, class ObjectDir> mMeshesSpan; // 0x40
    ObjPtrList<RndMesh, class ObjectDir> mMeshesRight; // 0x50
    ObjPtr<RndEnviron, class ObjectDir> mEnviron; // 0x60
    float mBaseLength; // 0x6c
    float mBaseWidth; // 0x70
    Vector3 mOffset; // 0x74
    TrackDir* mTrackDir; // 0x80
    TrackWidgetImpBase* mImp; // 0x84
    ObjPtr<RndFont, class ObjectDir> mFont; // 0x88
    ObjPtr<RndText, class ObjectDir> mTextObj; // 0x94
    RndText::Alignment mTextAlignment; // 0xa0
    Hmx::Color mTextColor; // 0xa4
    Hmx::Color mAltTextColor; // 0xb4
    ObjPtr<RndMat, class ObjectDir> mMat; // 0xc4
    bool unkd0b7 : 1; // 0xd0 >> 7 & 1
    bool mWideWidget : 1; // 0xd0 >> 6 & 1
    bool mAllowRotation : 1; // 0xd0 >> 5 & 1
    bool mAllowShift : 1; // 0xd0 >> 4 & 1
    bool mAllowLineRotation : 1; // 0xd0 >> 3 & 1
    bool unkd1;
    bool unkd2;
    bool unkd3;
    int unkd4 : 10;

    // rlwinm r0, r5, 0, 8, 4: accesses bits 27-23 (sets to 0) - 5 bits
    // rlwimi r0, r4, 15, 8, 16: 15-23? - 7 bits
    // rlwinm r0, r0, 0, 27, 16: accesses bits 15-4 (sets to 0) - 12 bits

    // mMaxMeshes: 0xd0...? - accesses bits 14-23
    // mCharsPerInst: 0xd0...? - accesses bits 4-14
    // mWidgetType: 0xd0...? - accesses bits 23-26

    // accesses bits 0-21
    // mMaxTextInstances: 0xd4 >> 0x16, accesses bits 22-31???
};

#endif // TRACK_TRACKWIDGET_H