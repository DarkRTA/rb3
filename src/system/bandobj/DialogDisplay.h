#pragma once
#include "rndobj/Poll.h"
#include "rndobj/Mesh.h"
#include "ui/UILabel.h"

class DialogDisplay : public RndPollable {
public:
    DialogDisplay();
    OBJ_CLASSNAME(DialogDisplay);
    OBJ_SET_TYPE(DialogDisplay);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~DialogDisplay();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    float GetLabelHeight();
    void SetLabel(UILabel*);
    void SetTopBone(RndMesh*);
    void SetBottomBone(RndMesh*);

    UILabel* GetLabel() const { return mDialogLabel.Ptr() ? mDialogLabel.Ptr() : 0; }
    RndMesh* GetTopBone() const { return mTopBone.Ptr() ? mTopBone.Ptr() : 0; }
    RndMesh* GetBottomBone() const { return mBottomBone.Ptr() ? mBottomBone.Ptr() : 0; }

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(DialogDisplay);
    }
    NEW_OBJ(DialogDisplay);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<UILabel, ObjectDir> mDialogLabel; // 0x8
    ObjPtr<RndMesh, ObjectDir> mTopBone; // 0x14
    ObjPtr<RndMesh, ObjectDir> mBottomBone; // 0x20
};