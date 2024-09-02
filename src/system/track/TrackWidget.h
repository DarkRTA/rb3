#ifndef TRACK_TRACKWIDGET_H
#define TRACK_TRACKWIDGET_H
#include "rndobj/Draw.h"
#include "rndobj/Text.h"
#include "obj/ObjPtr_p.h"
#include "track/TrackWidgetImp.h"
#include "track/TrackDir.h"

class RndEnviron;

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
    void ApplyOffsets(Transform&);
    void UpdateActiveStatus();
    void RemoveAt(float);
    void RemoveAt(float, int);
    float GetFirstInstanceY();
    void AddInstance(Transform, float);
    void AddTextInstance(const Transform&, class String, bool);
    void AddMeshInstance(const Transform&, RndMesh*, float);
    void SetTrackDir(TrackDir* dir){ mTrackDir = dir; }
    bool Empty(){ return mImp->Empty(); }

    float NewYOffset(float secs) const {
        return mYOffset + mTrackDir->SecondsToY(secs);
    }

    DataNode OnSetMeshes(const DataArray*);
    DataNode OnAddInstance(const DataArray*);
    DataNode OnAddTextInstance(const DataArray*);
    DataNode OnAddMeshInstance(const DataArray*);

    NEW_OBJ(TrackWidget)
    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS

    static void Register(){
        REGISTER_OBJ_FACTORY(TrackWidget);
    }

    ObjPtrList<RndMesh, class ObjectDir> mMeshes; // 0x20
    ObjPtrList<RndMesh, class ObjectDir> mMeshesLeft; // 0x30
    ObjPtrList<RndMesh, class ObjectDir> mMeshesSpan; // 0x40
    ObjPtrList<RndMesh, class ObjectDir> mMeshesRight; // 0x50
    ObjPtr<RndEnviron, class ObjectDir> mEnviron; // 0x60
    float mBaseLength; // 0x6c
    float mBaseWidth; // 0x70
    float mXOffset; // 0x74
    float mYOffset; // 0x78
    float mZOffset; // 0x7c
    TrackDir* mTrackDir; // 0x80
    TrackWidgetImpBase* mImp; // 0x84
    ObjPtr<RndFont, class ObjectDir> mFont; // 0x88
    ObjPtr<RndText, class ObjectDir> mTextObj; // 0x94
    RndText::Alignment mTextAlignment; // 0xa0
    Hmx::Color mTextColor; // 0xa4
    Hmx::Color mAltTextColor; // 0xb4
    ObjPtr<RndMat, class ObjectDir> mMat; // 0xc4
    // 0xd0
    bool mActive : 1; // 0xd0 >> 7 & 1
    bool mWideWidget : 1; // 0xd0 >> 6 & 1
    bool mAllowRotation : 1; // 0xd0 >> 5 & 1
    bool mAllowShift : 1; // 0xd0 >> 4 & 1
    bool mAllowLineRotation : 1; // 0xd0 >> 3 & 1
    int mWidgetType : 3;
    int mMaxMeshes : 9;
    int mCharsPerInst : 10; 
    int mMaxTextInstances : 10;
};

#endif // TRACK_TRACKWIDGET_H