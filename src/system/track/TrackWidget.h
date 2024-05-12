#ifndef TRACK_TRACKWIDGET_H
#define TRACK_TRACKWIDGET_H

#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/Font.h"
#include "rndobj/Mat.h"
#include "rndobj/Mesh.h"
#include "rndobj/Text.h"
#include "track/TrackDir.h"
#include "track/TrackWidgetImp.h"

class TrackWidget : public RndDrawable {
public:
    ObjPtrList<RndMesh, ObjectDir> unk_0x20, unk_0x30, unk_0x40, unk_0x50;
    ObjPtr<RndEnviron, ObjectDir> unk_0x60;
    float unk_0x6C, unk_0x70;
    Vector3 unk_0x74;
    TrackDir* unk_0x80;
    TrackWidgetImpBase* unk_0x84;
    ObjPtr<RndFont, ObjectDir> unk_0x88;
    ObjPtr<RndText, ObjectDir> unk_0x94;
    RndText::Alignment mAlignment;
    Hmx::Color unk_0xA4, unk_0xB4;
    ObjPtr<RndMat, ObjectDir> unk_0xC4;
    int mActive : 1; // 0xD0_0; :sparkles: bitfield nonsense :sparkles:
    int unk_0xD0_1 : 1;
    int unk_0xD0_2 : 1;
    int unk_0xD0_3 : 1;
    int mWidgetType : 2; // 0xD0_4-5
    int unk_0xD0_6 : 1;
    int unk_0xD0_7 : 1;
    int unk_0xD4;

    TrackWidget();
    virtual ~TrackWidget();
    OBJ_CLASSNAME(TrackWidget)
    OBJ_SET_TYPE(TrackWidget)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Mats(std::list<class RndMat*>&, bool);

    void Clear();
    void SyncImp();
    void Init();
    void DrawShowing();
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
    void AddTextInstance(const Transform&, String, bool);
    void AddMeshInstance(const Transform&, RndMesh*, float);

    DataNode OnSetMeshes(const DataArray*);
    DataNode OnAddInstance(const DataArray*);
    DataNode OnAddTextInstance(const DataArray*);
    DataNode OnAddMeshInstance(const DataArray*);

    NEW_OBJ(TrackWidget)
    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
};

#endif // TRACK_TRACKWIDGET_H