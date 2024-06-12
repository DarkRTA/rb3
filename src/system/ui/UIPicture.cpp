#include "UIPicture.h"
#include "os/Debug.h"
#include "os/File.h"
#include "ui/UIComponent.h"
#include "ui/UITransitionHandler.h"
#include "obj/PropSync_p.h"
#include "utl/Loader.h"
#include <string.h>
#include "utl/Symbols.h"

INIT_REVS(UIPicture)

UIPicture::UIPicture() : UITransitionHandler(this), mMesh(this, NULL), mTexFile(), mLoadedFile(), 
    mTex(Hmx::Object::New<RndTex>()), mLoader(0), mHookTex(true), mDelayedTexFile("") {
    
}

void UIPicture::SetTypeDef(DataArray* da) {
    if(TypeDef() != da){
        UIComponent::SetTypeDef(da);
        if(da){
            DataArray* findtex = da->FindArray("tex_file", false);
            if(findtex){
                if(strlen(findtex->Str(1)) != 0){
                    const char* str = findtex->Str(1);
                    const char* path = FileGetPath(findtex->mFile.Str(), 0);
                    FilePath fp;
                    fp.Set(path, str);
                    SetTex(fp);
                }
            }
        }
    }
}

UIPicture::~UIPicture() {
    CancelLoading();
    delete mTex;
}

BEGIN_COPYS(UIPicture)
    CREATE_COPY_AS(UIPicture, p)
    MILO_ASSERT(p, 0x41);
    UIComponent::Copy(p, ty);
    COPY_MEMBER_FROM(p, mMesh)
    UITransitionHandler::CopyHandlerData(p);
END_COPYS

SAVE_OBJ(UIPicture, 79)

void UIPicture::Load(BinStream& bs) {
    PreLoad(bs);
    PostLoad(bs);
}

void UIPicture::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    if(gRev != 0){
        if(TheLoadMgr.EditMode()){
            char buf[256];
            FilePath fp;
            bs.ReadString(buf, 0x100);
            fp.SetRoot(buf);
            SetTex(fp);
        }
        else {
            char buf[256];
            bs.ReadString(buf, 0x100);
            mTexFile.SetRoot(buf);
        }
        bs >> mMesh;
    }
    if (gRev >= 2) UITransitionHandler::LoadHandlerData(bs);
    UIComponent::PreLoad(bs);
}

void UIPicture::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    CancelLoading();
    if(!TheLoadMgr.EditMode() && mMesh){
        mMesh->mShowing = false;
    }
}

void UIPicture::Poll() {
    UIComponent::Poll();
    if (mDelayedTexFile != "") {
        UpdateTexture(mDelayedTexFile);
        mDelayedTexFile.SetRoot("");
    }
    UpdateHandler();
}

void UIPicture::Exit() {
    UIComponent::Exit();
    CancelLoading();
}

bool UIPicture::IsEmptyValue() const {
    return mTexFile == "";
}

void UIPicture::SetTex(const FilePath& p) {
    if (HasTransitions() || (!(p == mLoadedFile) || !(p == mTexFile))) {
        if (TheLoadMgr.EditMode()) {
            mDelayedTexFile = p;
        } else UpdateTexture(p);
    }
}

void UIPicture::FinishValueChange() {
    if(mLoader && mLoader->IsLoaded()){
        FinishLoading();
        UITransitionHandler::FinishValueChange();
    }
    else if(mMesh) mMesh->mShowing = false;
}

void UIPicture::UpdateTexture(const FilePath& p) {
    mTexFile = p;
    CancelLoading();
    if (mTexFile != "") {
        if (!strstr(mTexFile.c_str(), "_keep")) MILO_WARN("%s will not be included on a disc build", p);
        mLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(mTexFile, kLoadFront));
        MILO_ASSERT(mLoader, 227);
    }
    UITransitionHandler::StartValueChange();
}

void UIPicture::FinishLoading() {
    MILO_ASSERT(mLoader, 235);
    MILO_ASSERT(mLoader->IsLoaded(), 236);
    mTex->SetBitmap(mLoader);
    HookupMesh();
    mLoader = NULL;
    mLoadedFile = mTexFile;
}

void UIPicture::CancelLoading() {
    if (mLoader) {
        delete mLoader;
        mLoader = 0;
    }
}

void UIPicture::HookupMesh() {
    if(mMesh && mHookTex){
        RndMat* mat = mMesh->mMat;
        if(mat){
            RndTex* tex = mTex;
            if(tex && tex->mWidth != 0 && tex->mHeight != 0){
                mat->mDiffuseTex = tex;
                mat->mDirty |= 2;
            }
            else {
                mat->mDiffuseTex = 0;
                mat->mDirty |= 2;
            }
        }
        else {
            if(mLoader || TheLoadMgr.EditMode()){
                MILO_WARN("%s does not have material", mMesh->Name());
            }
        }
        mMesh->mShowing = true;
    }
}

void UIPicture::SetHookTex(bool b) {
    mHookTex = b;
    if (b == 0) return;
    mLoadedFile.Set(FilePath::sRoot.c_str(), "");
}

BEGIN_HANDLERS(UIPicture)
    HANDLE_EXPR(tex, mTex)
    HANDLE_ACTION(set_hook_tex, SetHookTex(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(288)
END_HANDLERS

BEGIN_PROPSYNCS(UIPicture)
    SYNC_PROP_SET(tex_file, mTexFile, SetTex(FilePath(_val.Str(0))))
    SYNC_PROP_SET(in_anim, GetInAnim(), SetInAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_PROP_SET(out_anim, GetOutAnim(), SetOutAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_PROP_MODIFY_ALT(mesh, mMesh, HookupMesh())
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
