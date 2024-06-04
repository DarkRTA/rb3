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
    return UIComponent::kNumStates;
}

UIComponent::UIComponent() : mNavRight(this, NULL), mNavDown(this, NULL), unk_0xD4(0), mMesh(NULL),
    mResourceName(), mObjDir(NULL), a(0), mState(kNormal), c(0), d(0) { }


void UIComponent::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    DataArray* cfg = SystemConfig("UIComponent", "objects")->FindArray("select_frames", true);
    sSelectFrames = cfg->Int(1);
}

UIComponent::~UIComponent() {}

Symbol UIComponent::StateSym() const {
    return UIComponentStateToSym((UIComponent::State)mState);
}

void UIComponent::SetState(UIComponent::State s) {
    if (!CanHaveFocus() && s == kFocused) {
        MILO_WARN("Component: %s cannot have focus.  Why are we setting it to the focused state?", Name());
        s = kNormal;
    }
    mState = s;
}

void UIComponent::SetTypeDef(DataArray* da) {
    if(!da && strlen(mResourcePath.c_str()) == 0){
        DataArray* cfg = SystemConfig("objects", ClassName());
        DataArray* found = cfg->FindArray("init", false);
        if(found){
            DataArray* typesArr = cfg->FindArray("types", true);
            DataArray* defaultArr = typesArr->FindArray("default", false);
            if(defaultArr){
                MILO_WARN("Resetting %s (%s) to default type (%s)", ClassName(), Name(), PathName(this));
                SetTypeDef(defaultArr);
                return;
            }
            else {
                MILO_FAIL("No default type for %s, please add to %s (%s)", ClassName(), typesArr->mFile, PathName(this));
                return;
            }
        }
    }
    if(mTypeDef != da){
        Hmx::Object::SetTypeDef(da);
        UpdateResource();
    }
}

BEGIN_COPYS(UIComponent)
    CREATE_COPY(UIComponent, c)
    MILO_ASSERT(c, 134);
    COPY_MEM(c, mDir)
    COPY_MEM(c, mResourcePath)
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
        mMesh->PostLoad();
    }
}

bool UIComponent::Exiting() const {
    return mState == kSelecting;
}

void UIComponent::Enter() {
    RndPollable::Enter();
    a = false;
    if (mState == kSelecting) {
        SetState(kFocused);
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
        return mMesh->mDir.mDir;
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
