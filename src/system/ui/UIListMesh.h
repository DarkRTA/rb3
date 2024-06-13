#ifndef UI_UILISTMESH_H
#define UI_UILISTMESH_H
#include "ui/UIListSlot.h"
#include "ui/UILabel.h"
#include "obj/ObjPtr_p.h"

class UIListMesh : public UIListSlot {
public:
    UIListMesh();
    virtual ~UIListMesh(){}
    OBJ_CLASSNAME(UIListMesh)
    OBJ_SET_TYPE(UIListMesh)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Draw(const UIListWidgetDrawState&, const UIListState&, const Transform&, UIComponent::State, Box*, DrawCommand);
    virtual UIListSlotElement* CreateElement(UIList*);
    virtual RndTransformable* RootTrans();
    
    RndMat* DefaultMat() const;

    DECLARE_REVS

    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x5c
    ObjPtr<RndMat, ObjectDir> mDefaultMat; // 0x68
};

class UIListMeshElement : public UIListSlotElement {
public:
    UIListMeshElement(UIListMesh* lm, RndMat* m) : mListMesh(lm), mMat(m) {}
    virtual ~UIListMeshElement(){}
    virtual void Fill(const UIListProvider&, int, int);
    virtual void Draw(const Transform&, float, UIColor*, Box*);
    
    UIListMesh* mListMesh;
    RndMat* mMat;
};

#endif
