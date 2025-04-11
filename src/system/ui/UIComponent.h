#pragma once
#include "types.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/User.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "ui/PanelDir.h"
#include "ui/UIResource.h"
#include "obj/Msg.h"
#include "ui/UIScreen.h"
#include "utl/FilePath.h"
#include <vector>

/**
 * @brief A base implementation of a UI object.
 * Original _objects description:
 * "Base class of all UI components,
 * defines navigation and component state"
 */
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
        // UIMesh(){}
        // UIMesh(RndMesh* mesh) : mMesh(mesh) {
        //     for(int i = 0; i < kNumStates; i++) mMats[i] = 0;
        // }
        RndMesh *mMesh;
        RndMat *mMats[kNumStates];
    };

    UIComponent();
    OBJ_CLASSNAME(UIComponent)
    OBJ_SET_TYPE(UIComponent)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual ~UIComponent();
    virtual void SetTypeDef(DataArray *);
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void ResourceCopy(const UIComponent *);
    virtual void SetState(UIComponent::State);
    virtual Symbol StateSym() const;
    virtual bool Entering() const { return false; }
    virtual bool Exiting() const;
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool CanHaveFocus() { return true; }
    virtual void CopyMembers(const UIComponent *, CopyType);
    virtual void Update();

    void FinishSelecting();
    void SendSelect(LocalUser *);
    const char *GetResourcesPath();
    void ResourceFileUpdated(bool);
    DataNode OnGetResourcesPath(DataArray *);
    class ObjectDir *ResourceDir();
    void UpdateResource();
    void UpdateMeshes(State);
    void MockSelect();

    UIComponent *NavRight() { return mNavRight; }
    UIComponent *NavDown() { return mNavDown; }
    bool Loading() const { return mLoading; }
    State GetState() { return (State)mState; }

    NEW_OVERLOAD
    DELETE_OVERLOAD

    ObjPtr<UIComponent> mNavRight; // 0xB8
    ObjPtr<UIComponent> mNavDown; // 0xC4
    LocalUser *mSelectingUser; // 0xD0
    UIScreen *mSelectScreen; // 0xD4
    UIResource *mResource; // 0xD8
    std::vector<UIMesh> mMeshes; // 0xDC
    /** "path to resource file for this component" */
    String mResourceName; // 0xE4
    ObjDirPtr<ObjectDir> mResourceDir; // 0xF0
    String mResourcePath; // 0xFC
    unsigned char mSelected; // 0x108
    unsigned char mState; // 0x109
    bool mLoading; // 0x10A
    bool mMockSelect; // 0x10B

    NEW_OBJ(UIComponent)
    static void Init();
    static void Register() { REGISTER_OBJ_FACTORY(UIComponent); }
    static int sSelectFrames;
    DECLARE_REVS

    // open resource: "opens the current resource file for this component - will open in a
    // new milo window"
};

Symbol UIComponentStateToSym(UIComponent::State);
UIComponent::State SymToUIComponentState(Symbol);

#include "obj/Msg.h"

DECLARE_MESSAGE(UIComponentScrollMsg, "component_scroll");
UIComponentScrollMsg(UIComponent *comp, LocalUser *user) : Message(Type(), comp, user) {}
UIComponent *GetUIComponent() const { return mData->Obj<UIComponent>(2); }
LocalUser *GetUser() const { return mData->Obj<LocalUser>(3); }
END_MESSAGE

DECLARE_MESSAGE(UIComponentSelectMsg, "component_select");
UIComponentSelectMsg(UIComponent *comp, LocalUser *user) : Message(Type(), comp, user) {}
UIComponent *GetComponent() const { return mData->Obj<UIComponent>(2); }
LocalUser *GetUser() const { return mData->Obj<LocalUser>(3); }
END_MESSAGE

DECLARE_MESSAGE(UIComponentSelectDoneMsg, "component_select_done");
UIComponentSelectDoneMsg(UIComponent *comp, LocalUser *user)
    : Message(Type(), comp, user) {}
UIComponent *GetComponent() const { return mData->Obj<UIComponent>(2); }
LocalUser *GetUser() const { return mData->Obj<LocalUser>(3); }
END_MESSAGE

DECLARE_MESSAGE(UIComponentScrollSelectMsg, "component_scroll_select");
UIComponentScrollSelectMsg(UIComponent *comp, LocalUser *user, bool selected)
    : Message(Type(), comp, user, selected) {}
UIComponent *GetComponent() const { return mData->Obj<UIComponent>(2); }
LocalUser *GetUser() const { return mData->Obj<LocalUser>(3); }
bool GetSelected() const { return mData->Int(4); }
END_MESSAGE

// #define FOCUS_MSG (component_focus ($new_focus $old_focus $panel_dir $nav_type))
DECLARE_MESSAGE(UIComponentFocusChangeMsg, "component_focus");
UIComponentFocusChangeMsg(UIComponent *comp1, UIComponent *comp2, PanelDir *dir, Symbol s)
    : Message(Type(), comp1, comp2, dir, s) {}
UIComponent *GetNewFocus() const { return mData->Obj<UIComponent>(2); }
UIComponent *GetOldFocus() const { return mData->Obj<UIComponent>(3); }
PanelDir *GetDir() const { return mData->Obj<PanelDir>(4); }
Symbol GetNavType() const { return mData->Sym(5); }
END_MESSAGE

DECLARE_MESSAGE(UIComponentScrollStartMsg, "component_scroll_start");
UIComponentScrollStartMsg(UIComponent *comp, LocalUser *user)
    : Message(Type(), comp, user) {}
UIComponent *GetComponent() const { return mData->Obj<UIComponent>(2); }
LocalUser *GetUser() const { return mData->Obj<LocalUser>(3); }
END_MESSAGE
