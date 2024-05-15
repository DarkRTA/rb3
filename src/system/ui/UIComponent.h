#ifndef UI_UICOMPONENT_H
#define UI_UICOMPONENT_H

#include "types.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/User.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "ui/UIResource.h"
#include "utl/FilePath.h"
#include <vector>


class UIComponent : public RndDrawable, public RndTransformable, public RndPollable {
    public:

    class UIMesh {
        
    };

    enum State {
        kStateNormal,
        kStateFocused,
        kStateDisabled,
        kStateSelecting,
        kStateSelected,
        kStateInvalid
    };
    UIComponent();
    virtual ~UIComponent();
    OBJ_CLASSNAME(UIComponent)
    OBJ_SET_TYPE(UIComponent)
    virtual void SetTypeDef(DataArray *);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Poll();
    virtual void SetState(UIComponent::State);
    virtual void Exit();
    virtual void Enter();
    virtual void Highlight();
    virtual int CanHaveFocus() {return true;}
    virtual void CopyMembers(const UIComponent*, CopyType);

    void FinishSelecting();
    Symbol StateSym() const;
    void SendSelect(LocalUser*);
    char* GetResourcesPath();
    void ResourceFileUpdated(bool);
    DataNode OnGetResourcesPath(DataArray*);
    bool Exiting() const;
    class ObjectDir* ResourceDir();

    NEW_OVERLOAD
    DELETE_OVERLOAD

    ObjPtr<UIComponent, class ObjectDir> mNavRight;
    ObjPtr<UIComponent, class ObjectDir> mNavDown;
    int test1; // 0xD0
    int unk_0xD4; // 0xD4
    UIResource* mMesh; // 0xD8
    std::vector<int> unk_0xDC; // 0xDC
    class String mResourceName; // 0xE4
    ObjDirPtr<class ObjectDir> mObjDir; // 0xF0
    class String mResourcePath; // 0xFC
    bool a; // 0x108
    u8 mState; // 0x109
    bool c, d; // 0x10A, 0x10B

    NEW_OBJ(UIComponent)
    static void Init();
    static int sSelectFrames;
    DECLARE_REVS
};

Symbol UIComponentStateToSym(UIComponent::State);
UIComponent::State SymToUIComponentState(Symbol);

#endif // UI_UICOMPONENT_H
