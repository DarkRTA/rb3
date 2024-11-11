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
#include "obj/Msg.h"
#include "ui/UIScreen.h"
#include "utl/FilePath.h"
#include <vector>

class UIComponent : public RndDrawable, public RndTransformable, public RndPollable {
    public:

    enum State {
        kNormal = 0,
        kFocused = 1,
        kDisabled = 2,
        kSelecting = 3,
        kSelected = 4,
        kNumStates = 5,
    };

    // size 0x18
    class UIMesh {
    public:
        UIMesh(){}
        UIMesh(RndMesh* mesh) : mMesh(mesh) {
            for(int i = 0; i < kNumStates; i++) mMats[i] = 0;
        }
        RndMesh* mMesh;
        RndMat* mMats[kNumStates];
    };

    UIComponent();
    OBJ_CLASSNAME(UIComponent)
    OBJ_SET_TYPE(UIComponent)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Highlight(){ RndDrawable::Highlight(); }
    virtual ~UIComponent();
    virtual void SetTypeDef(DataArray*);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void ResourceCopy(const UIComponent*);
    virtual void SetState(UIComponent::State);
    virtual Symbol StateSym() const;
    virtual bool Entering() const { return false; }
    virtual bool Exiting() const;
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool CanHaveFocus() {return true;}
    virtual void CopyMembers(const UIComponent*, CopyType);
    virtual void Update();

    State GetState(){ return (State)mState; }

    void FinishSelecting();
    void SendSelect(LocalUser*);
    const char* GetResourcesPath();
    void ResourceFileUpdated(bool);
    DataNode OnGetResourcesPath(DataArray*);
    class ObjectDir* ResourceDir();
    void UpdateResource();
    void UpdateMeshes(State);
    void MockSelect();

    UIComponent* NavRight(){ return mNavRight; }
    UIComponent* NavDown(){ return mNavDown; }
    bool Loading() const { return mLoading; }

    NEW_OVERLOAD
    DELETE_OVERLOAD

    ObjPtr<UIComponent, class ObjectDir> mNavRight; // 0xB8
    ObjPtr<UIComponent, class ObjectDir> mNavDown; // 0xC4
    LocalUser* mSelectingUser; // 0xD0
    UIScreen* unk_0xD4; // 0xD4
    UIResource* mResource; // 0xD8
    std::vector<UIMesh> mMeshes; // 0xDC
    class String mResourceName; // 0xE4
    ObjDirPtr<class ObjectDir> mResourceDir; // 0xF0
    class String mResourcePath; // 0xFC
    unsigned char unk108; // 0x108
    unsigned char mState; // 0x109
    bool mLoading; // 0x10A
    bool mMockSelect; // 0x10B

    NEW_OBJ(UIComponent)
    static void Init();
    static void Register(){ REGISTER_OBJ_FACTORY(UIComponent); }
    static int sSelectFrames;
    DECLARE_REVS
};

Symbol UIComponentStateToSym(UIComponent::State);
UIComponent::State SymToUIComponentState(Symbol);

#include "obj/Msg.h"

DECLARE_MESSAGE(UIComponentScrollMsg, "component_scroll");
    UIComponentScrollMsg(UIComponent* comp, LocalUser* user) : 
        Message(Type(), comp, user){}
    UIComponent* GetUIComponent() const { return mData->Obj<UIComponent>(2); }
END_MESSAGE;

DECLARE_MESSAGE(UIComponentSelectMsg, "component_select");
    UIComponentSelectMsg(UIComponent* comp, LocalUser* user) : 
        Message(Type(), comp, user){}
END_MESSAGE;

DECLARE_MESSAGE(UIComponentSelectDoneMsg, "component_select_done");
    UIComponentSelectDoneMsg(UIComponent* comp, LocalUser* user) : 
        Message(Type(), comp, user){}
END_MESSAGE;

DECLARE_MESSAGE(UIComponentScrollSelectMsg, "component_scroll_select");
    UIComponentScrollSelectMsg(UIComponent* comp, LocalUser* user, bool b) : 
        Message(Type(), comp, user, b){}
END_MESSAGE;

DECLARE_MESSAGE(UIComponentFocusChangeMsg, "component_focus");
    UIComponentFocusChangeMsg(UIComponent* comp1, UIComponent* comp2, PanelDir* dir, Symbol s) : 
        Message(Type(), comp1, comp2, dir, s){}
END_MESSAGE;

DECLARE_MESSAGE(UIComponentScrollStartMsg, "component_scroll_start");
    UIComponentScrollStartMsg(UIComponent* comp, LocalUser* user) :
        Message(Type(), DataNode(comp), DataNode(user)){}
END_MESSAGE;

#endif // UI_UICOMPONENT_H
