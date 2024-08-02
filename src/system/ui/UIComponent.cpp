#include "UIComponent.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "os/System.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "ui/UIMessages.h"
#include "obj/Utl.h"
#include "os/File.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(UIComponent)
int UIComponent::sSelectFrames = 0;
bool gResettingType;

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

UIComponent::UIComponent() : mNavRight(this, NULL), mNavDown(this, NULL), unk_0xD4(0), mResource(NULL),
    mResourceName(), mResourceDir(NULL), unk108(0), mState(kNormal), mLoading(0), mMockSelect(0) { }

void UIComponent::Init() {
    Register();
    sSelectFrames = SystemConfig("objects", "UIComponent")->FindInt("select_frames");
}

UIComponent::~UIComponent(){
    if(mResource) mResource->Release();
}

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
                MILO_WARN("Resetting %s (%s) to default type (%s)", ClassName(), Name(), PathName(Dir()));
                SetTypeDef(defaultArr);
                return;
            }
            else {
                MILO_FAIL("No default type for %s, please add to %s (%s)", ClassName(), typesArr->File(), PathName(Dir()));
                return;
            }
        }
    }
    if(TypeDef() != da){
        Hmx::Object::SetTypeDef(da);
        UpdateResource();
    }
}

BEGIN_COPYS(UIComponent)
    CREATE_COPY(UIComponent)
    MILO_ASSERT(c, 134);
    COPY_MEMBER(mResourceName)
    COPY_MEMBER(mResourceDir)
    COPY_MEMBER(mResourcePath)
    Hmx::Object::Copy(c, ty);
    CopyMembers(c, ty);
END_COPYS

void UIComponent::ResourceCopy(const UIComponent* c){
    MILO_ASSERT(c, 0x94);
    Hmx::Object::SetTypeDef((DataArray*)c->TypeDef());
    CopyMembers(c, kCopyShallow);
    if(mResourcePath.length() != 0){
        mResourceDir = c->mResourceDir;
        MILO_ASSERT(mResourceDir.Ptr(), 0x9B);
    }
    else {
        mResource = c->mResource;
        mResource->PostLoad();
        MILO_ASSERT(mResource->Dir(), 0xA1);
    }
    Update();
}

void UIComponent::CopyMembers(const UIComponent* c, Hmx::Object::CopyType ty){
    RndTransformable::Copy(c, ty);
    RndDrawable::Copy(c, ty);
    mNavRight = c->mNavRight;
    mNavDown = c->mNavDown;
    mResourceName = c->mResourceName;
    mResourceDir = c->mResourceDir;
    mResourcePath = c->mResourcePath;
}

SAVE_OBJ(UIComponent, 182)

void UIComponent::Load(BinStream& bs) {PreLoad(bs); PostLoad(bs);}

void UIComponent::PreLoad(BinStream& bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    mResourcePath = GetResourcesPath();
    mLoading = true;
    Hmx::Object::Load(bs);
    mLoading = false;
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
    if(mResource) mResource->PostLoad();
    bool b1 = false;
    bool b2 = false;
    if(!Type().Null() && mResourcePath.length() != 0) b1 = true;
    if(b1 && mResourceName.length() == 0) b2 = true;
    if(b2){
        mResourceName = Type().Str();
        MILO_WARN("upgrading UIComponent %s to new resource loading system (Old type: %s). Please resave this file and checkin (%s).\n", Name(), mResourceName.c_str(), PathName(this));
        ResourceFileUpdated(false);
        SetType("");
        mResource = 0;
        DataVariable("uicomponent.resource_upgrade") = DataNode(1);
    }
    if(mResourceName.length() != 0){
        mResourceDir.PostLoad(0);
    }
}

bool UIComponent::Exiting() const {
    return mState == kSelecting;
}

void UIComponent::Enter() {
    RndPollable::Enter();
    unk108 = 0;
    if (mState == kSelecting) {
        SetState(kFocused);
    }
}

void UIComponent::Exit() {RndPollable::Exit();}

void UIComponent::Poll() {
    if(unk108 == 0) return;
    if(--unk108 != 0) return;
    FinishSelecting();
}

#pragma push
#pragma pool_data off
void UIComponent::SendSelect(LocalUser* user){
    if(mState == kFocused){
        SetState(kSelecting);
        static UIComponentSelectMsg select_msg(0, 0);
        UNCONST_ARRAY(select_msg)->Node(2) = DataNode(this);
        UNCONST_ARRAY(select_msg)->Node(3) = DataNode(user);
        TheUI->Handle(select_msg, false);
        if(mState != kSelecting) unk_0xD4 = 0;
        else {
            unk_0xD4 = TheUI->mCurrentScreen;
            mSelectingUser = user;
            MILO_ASSERT(sSelectFrames < 255, 0x137);
            MILO_ASSERT(sSelectFrames >= 0, 0x138);
            unk108 = sSelectFrames;
        }
    }
}
#pragma pop

void UIComponent::MockSelect(){
    MILO_ASSERT(sSelectFrames < 255, 0x13F);
    MILO_ASSERT(sSelectFrames >= 0, 0x140);
    unk108 = sSelectFrames;
    SetState(UIComponent::kSelecting);
    mMockSelect = true;
}

void UIComponent::Update(){
    if(mResourcePath.length() != 0){
        if(!mResourceDir){
            FileStat stat;
            const char* default_str = "default";
            const char* milo_str = MakeString("%s/%s.milo", mResourcePath.c_str(), default_str);
            if(!default_str){
                MILO_FAIL("No default_resource for %s, please add 'default_resource' block ", ClassName());
                return;
            }
            int filestat = FileGetStat(milo_str, &stat);
            if(filestat == -1){
                MILO_FAIL("%s %s (%s) is missing default resource file %s, please fix", ClassName(), Name(), PathName(this), milo_str);
            }
            else {
                MILO_ASSERT(!mLoading, 0x161);
                MILO_WARN("Resetting %s (%s) resource to default because resource %s couldn't be found (%s)",
                    ClassName(), Name(), mResourceName.c_str(), PathName(Dir()));
                mResourceName = default_str;
                ResourceFileUpdated(false);
                UIComponent::Update();
            }
        }
    }
    else {
        if(mResource){
            RndDir* rdir = mResource->Dir();
            if(rdir){
                mMeshes.clear();
                DataArray* mesharr = TypeDef()->FindArray(meshes, false);
                if(mesharr){
                    for(int i = 0; i < mesharr->Size(); i++){
                        DataArray* innerarr = mesharr->Array(i);
                        RndMesh* newmesh = rdir->Find<RndMesh>(innerarr->Str(0), true);
                        UIMesh uimesh(newmesh);
                        for(int j = 1; j < innerarr->Size(); j++){
                            DataArray* anotherarr = innerarr->Array(j);
                            State state = SymToUIComponentState(anotherarr->Sym(0));
                            RndMat* mat = rdir->Find<RndMat>(anotherarr->Str(1), true);
                            uimesh.mMats[state] = mat;
                        }
                        mMeshes.push_back(uimesh);
                    }
                }
            }
            else {
                const DataArray* def = TypeDef();
                MILO_WARN("Can't find %s (%s) resource file %s for type %s! (%s)",
                    ClassName(), Name(), def->FindStr("resource_file"), Type(), PathName(this));
                DataArray* cfg = SystemConfig("objects", ClassName(), "types");
                DataArray* defaultarr = cfg->FindArray("default", false);
                if(!defaultarr){
                    MILO_FAIL("No default type for %s, please add to %s", ClassName(), cfg->File());
                }
                else if(defaultarr == def){
                    MILO_FAIL("%s default type has invalid resource file, please fix %s", ClassName(), cfg->File());
                }
                else {
                    MILO_ASSERT(!mLoading, 0x1A7);
                    MILO_WARN("Resetting %s (%s) type to default (%s)", ClassName(), Name(), PathName(Dir()));
                    gResettingType = true;
                    SetTypeDef(defaultarr);
                    gResettingType = false;
                    UIComponent::Update();
                }
            }
        }
    }
}

void UIComponent::UpdateMeshes(State s){
    for(std::vector<UIMesh>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it){
        if((*it).mMesh->mMat != (*it).mMats[s]){
            (*it).mMesh->SetMat((*it).mMats[s]);
        }
    }
}

ObjectDir* UIComponent::ResourceDir(){
    if(mResourceDir) return mResourceDir;
    else if(mResource) return mResource->Dir();
    else return 0;
}

void UIComponent::UpdateResource(){
    if(mResource) mResource->Release();
    mResource = TheUI->Resource(this);
    if(mResource){
        mResource->Load(mLoading);
    }
    if(!mLoading && !gResettingType) Update();
}

void UIComponent::ResourceFileUpdated(bool b) {
    if(!mResourceName.empty()){
        mResourcePath = GetResourcesPath();
        const char* pathstr = MakeString("%s/%s.milo", mResourcePath.c_str(), mResourceName);
        mResourceDir.LoadFile(FilePath(FileRoot(), pathstr), b, true, kLoadFront, false);
        if(!b) mResourceDir.PostLoad(0);
    }
    else mResourceDir = 0;
    if(!b) Update();
}

const char* UIComponent::GetResourcesPath(){
    std::vector<Symbol> syms;
    syms.push_back(ClassName());
    ListSuperClasses(ClassName(), syms);
    DataArray* arr = 0;
    for(int i = 0; i < syms.size(); i++){
        arr = SystemConfig(objects, syms[i])->FindArray(resources_path, false);
        if(arr) break;
    }
    if(!arr) return 0;
    else {
        const char* str = arr->Str(1);
        if(*str == '\0') return 0;
        else return FileMakePath(FileGetPath(arr->File(), 0), str, 0);
    }
}

DataNode UIComponent::OnGetResourcesPath(DataArray* da) {
    if(mResourcePath.length() != 0){
        return DataNode(FileRelativePath(FileRoot(), mResourcePath.c_str()));
    }
    else return DataNode("");
}

#pragma push
#pragma pool_data off
void UIComponent::FinishSelecting(){
    if(mState != kDisabled && mState != kNormal) SetState(kFocused);
    if(!mMockSelect && unk_0xD4 == TheUI->mCurrentScreen){
        static UIComponentSelectDoneMsg select_msg(this, 0);
        UNCONST_ARRAY(select_msg)->Node(2) = DataNode(this);
        UNCONST_ARRAY(select_msg)->Node(3) = DataNode(mSelectingUser);
        TheUI->Handle(select_msg, false);
    }
    else mMockSelect = false;
}
#pragma pop

BEGIN_HANDLERS(UIComponent)
    HANDLE_EXPR(get_state, mState)
    HANDLE_ACTION(set_state, SetState((UIComponent::State)_msg->Int(2)))
    HANDLE_EXPR(can_have_focus, CanHaveFocus())
    HANDLE_EXPR(get_resource_dir, ResourceDir())
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
    SYNC_PROP_MODIFY_ALT(resource_name, mResourceName, ResourceFileUpdated(false))
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS
