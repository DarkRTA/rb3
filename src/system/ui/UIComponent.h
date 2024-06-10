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
        kNormal = 0,
        kFocused = 1,
        kDisabled = 2,
        kSelecting = 3,
        kSelected = 4,
        kNumStates = 5,
    };

    UIComponent();
    OBJ_CLASSNAME(UIComponent)
    OBJ_SET_TYPE(UIComponent)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Highlight();
    virtual ~UIComponent();
    virtual void SetTypeDef(DataArray*);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void ResourceCopy(const UIComponent*);
    virtual void SetState(UIComponent::State);
    virtual Symbol StateSym() const;
    virtual bool Entering() const;
    virtual bool Exiting() const;
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool CanHaveFocus() {return true;}
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();

    void FinishSelecting();
    void SendSelect(LocalUser*);
    const char* GetResourcesPath();
    void ResourceFileUpdated(bool);
    DataNode OnGetResourcesPath(DataArray*);
    class ObjectDir* ResourceDir();
    void UpdateResource();

    NEW_OVERLOAD
    DELETE_OVERLOAD

    ObjPtr<UIComponent, class ObjectDir> mNavRight;
    ObjPtr<UIComponent, class ObjectDir> mNavDown;
    int test1; // 0xD0
    int unk_0xD4; // 0xD4
    UIResource* mResource; // 0xD8
    std::vector<int> unk_0xDC; // 0xDC
    class String mResourceName; // 0xE4
    ObjDirPtr<class ObjectDir> mObjDir; // 0xF0
    class String mResourcePath; // 0xFC
    bool a; // 0x108
    char mState; // 0x109
    bool c, d; // 0x10A, 0x10B

    NEW_OBJ(UIComponent)
    static void Init();
    static int sSelectFrames;
    DECLARE_REVS
};

Symbol UIComponentStateToSym(UIComponent::State);
UIComponent::State SymToUIComponentState(Symbol);

#endif // UI_UICOMPONENT_H
