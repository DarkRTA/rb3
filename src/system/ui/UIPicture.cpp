#include "UIPicture.h"
#include "os/Debug.h"
#include "os/File.h"
#include "ui/UIComponent.h"
#include "ui/UITransitionHandler.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols4.h"
#include "utl/Loader.h"
#include <string.h>

UIPicture::UIPicture() : UITransitionHandler(NULL), mMesh(this, NULL), mTexFile(), mLoadedFile() {
    mTex = Hmx::Object::New<RndTex>();
    mHookTex = true;
    mDelayedTexFile.Set(FilePath::sRoot.c_str(), "");
    //static char* why2 = "tex_file";
}

void UIPicture::SetTypeDef(DataArray* da) {
    UIComponent::SetTypeDef(da);
    if (da == NULL) return;
    if (!strlen(da->Str(1))) return;
    FilePath p(FileGetPath(da->Str(1), NULL));
    SetTex(p);
}

UIPicture::~UIPicture() {
    CancelLoading();
    delete mTex;
}

BEGIN_COPYS(UIPicture)
    GET_COPY_AND_ASSERT(UIPicture, 65)
    COPY_SUPERCLASS(UIComponent)
    UITransitionHandler::CopyHandlerData(c);
END_COPYS

SAVE_OBJ(UIPicture, 79)

void UIPicture::Load(BinStream& bs) {
    PreLoad(bs);
    PostLoad(bs);
}

void UIPicture::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)

    bs >> mMesh;
    if (gRev > 1) UITransitionHandler::LoadHandlerData(bs);
    UIComponent::PreLoad(bs);
}

// why is classname here?????

void UIPicture::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    CancelLoading();
    if (TheLoadMgr.mCacheMode && mMesh.mPtr != NULL ) { // i think this might be a fakematch
        /*??.field0x8 &= 0x7fU*/
    }
}

void UIPicture::Poll() {
    UIComponent::Poll();
    if (mDelayedTexFile != "") {
        UpdateTexture(mDelayedTexFile);
        mDelayedTexFile.Set(FilePath::sRoot.c_str(), "p");
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
        if (TheLoadMgr.mCacheMode) {
            mDelayedTexFile = p;
        } else UpdateTexture(p);
    }
}

void UIPicture::FinishValueChange() {
    if (mLoader) {
        if (mLoader->StateName()) {
            FinishLoading();
            UITransitionHandler::FinishValueChange();
        } else {
            if (mMesh.mPtr) HookupMesh();
        }
    }
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
    if (mTex) {
        delete mTex;
        mTex = 0;
    }
}

void UIPicture::HookupMesh() {

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
    SYNC_PROP(tex_file, mTexFile)
    SYNC_PROP_ACTION(mesh, mMesh, 0x11, HookupMesh())
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
