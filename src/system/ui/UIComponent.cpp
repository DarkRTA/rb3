#include "UIComponent.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/System.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

INIT_REVS(UIComponent)
int UIComponent::sSelectFrames = 0;

Symbol UIComponentStateToSym(UIComponent::State s) {
    static Symbol syms[5] = {"normal", "focused", "disabled", "selecting", "selected"};
    return syms[s];
}

UIComponent::State SymToUIComponentState(Symbol s) {
    for (int i = 0; i < 5; i++) {
        if (s.Str() == UIComponentStateToSym((UIComponent::State)i).Str()) return (UIComponent::State)i;
    }
    MILO_ASSERT(false, 38);
    return UIComponent::kStateInvalid;
}

UIComponent::UIComponent() : mNavRight(this, NULL), mNavDown(this, NULL), mObjDir(NULL), mMesh(NULL), a(0), mState(kStateNormal), c(0), d(0) {
    
}


void UIComponent::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    DataArray* da = SystemConfig("UIComponent", "objects");
    da = da->FindArray("select_frames", true);
    sSelectFrames = da->Int(1);
}

Hmx::Object* UIComponent::NewObject() {return new UIComponent;}

UIComponent::~UIComponent() {}

Symbol UIComponent::StateSym() const {
    return UIComponentStateToSym((UIComponent::State)mState);
}

void UIComponent::SetState(UIComponent::State s) {
    if (!CanHaveFocus() && s == kStateFocused) {
        MILO_WARN("Component: %s cannot have focus.  Why are we setting it to the focused state?", Name());
        s = kStateNormal;
    }
    mState = s;
}

void UIComponent::SetTypeDef(DataArray* da) {

}

BEGIN_COPYS(UIComponent)
    GET_COPY_AND_ASSERT(UIComponent, 134)
    COPY_MEMBER(mDir);
    COPY_MEMBER(mResourcePath)
    COPY_SUPERCLASS(Hmx::Object);
    CopyMembers(c, ty);
END_COPYS

SAVE_OBJ(UIComponent, 182)

void UIComponent::Load(BinStream& bs) {PreLoad(bs); PostLoad(bs);}

void UIComponent::PreLoad(BinStream& bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    mResourcePath = GetResourcesPath();
    c = true;
    Hmx::Object::Load(bs);
    c = false;
    RndTransformable::Load(bs);
    RndDrawable::Load(bs);
    if (gRev > 0) {
        bs >> mNavRight >> mNavDown;
    }
    if (gRev > 1) {
        bs >> mResourceName;
        ResourceFileUpdated(true);
    }
}

void UIComponent::PostLoad(BinStream& bs) {
    if (mMesh) {
        mMesh->PostLoad(bs);
    }
}

bool UIComponent::Exiting() const {
    return mState == kStateSelecting;
}

void UIComponent::Enter() {
    RndPollable::Enter();
    a = false;
    if (mState == kStateSelecting) {
        SetState(kStateFocused);
    }
}

void UIComponent::Exit() {RndPollable::Exit();}

void UIComponent::Poll() {
    if (!a) return;
    if (a -= 1) return; // fake"match" but it's as good as it gets
    FinishSelecting();
}

class ObjectDir* UIComponent::ResourceDir() {
    if (mObjDir.mDir) return mObjDir.mDir;
    if (mMesh) {
        return (class ObjectDir*)mMesh->filler; // TODO fix when RndMesh is memberized
    }
    return NULL;
}

void UIComponent::ResourceFileUpdated(bool) {

}

DataNode UIComponent::OnGetResourcesPath(DataArray* da) {

}

BEGIN_HANDLERS(UIComponent)
    HANDLE_EXPR(get_state, mState)
    HANDLE_ACTION(set_state, SetState((UIComponent::State)_msg->Int(2)))
    HANDLE_ACTION(can_have_focus, CanHaveFocus())
    HANDLE_ACTION(get_resource_dir, ResourceDir())
    HANDLE(get_resources_path, OnGetResourcesPath)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(579)
END_HANDLERS

BEGIN_PROPSYNCS(UIComponent)
    SYNC_PROP(nav_right, mNavRight)
    SYNC_PROP(nav_down, mNavDown)
    if (sym == resource_name) {
        if (PropSync(mResourceName, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) ResourceFileUpdated(false);
            return true;
        }
        return false;
    }
    if (RndDrawable::SyncProperty(_val, _prop, _i, _op)) return true;
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS
