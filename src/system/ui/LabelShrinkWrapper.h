#ifndef UI_LABELSHRINKWRAPPER_H
#define UI_LABELSHRINKWRAPPER_H
#include "ui/UIComponent.h"
#include "obj/ObjPtr_p.h"

class UILabel;

class LabelShrinkWrapper : public UIComponent {
public:
    LabelShrinkWrapper();
    OBJ_CLASSNAME(LabelShrinkWrapper)
    OBJ_SET_TYPE(LabelShrinkWrapper)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~LabelShrinkWrapper();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void Update();

    void UpdateAndDrawWrapper();
    void SetShouldShow(bool);
    void SetLabel(UILabel*);

    UILabel* Label() const {
        if(!m_pLabel) return 0;
        else return m_pLabel;
    }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(LabelShrinkWrapper)
    static void Init();

    static void Register(){ REGISTER_OBJ_FACTORY(LabelShrinkWrapper); }

    ObjPtr<UILabel, ObjectDir> m_pLabel; // 0x10c
    bool m_pShow; // 0x118
    RndMesh* m_pTopLeftBone; // 0x11c
    RndMesh* m_pTopRightBone; // 0x120
    RndMesh* m_pBottomLeftBone; // 0x124
    RndMesh* m_pBottomRightBone; // 0x128
};

#endif
