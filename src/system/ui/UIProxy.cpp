#include "ui/UIProxy.h"
#include "obj/ObjVersion.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

INIT_REVS(UIProxy)

UIProxy::UIProxy() : mDir(), mEnv(this, 0), mMainTrans(0), mSyncOnMove(0), mPolled(0) {
    mOldXfm.Reset();
    mOldXfm.v.x = -1.0E+30f;
}

// fn_805757B8
void UIProxy::SetTypeDef(DataArray* da){
    if(TypeDef() != da){
        UIComponent::SetTypeDef(da);
        mDir = 0;
        mSyncOnMove = false;
        if(da){
            da->FindData("sync_on_move", mSyncOnMove, false);
            DataArray* fileArr = da->FindArray("file", false);
            if(TheLoadMgr.EditMode() || fileArr->Size() != 3 || fileArr->Int(2) != 0){
                bool shared = true;
                da->FindData("share", shared, false);
                FilePath fp(FileGetPath(da->File(), 0), fileArr->Str(1));
                mDir.LoadFile(fp, Loading(), shared, kLoadFront, false);
                mPolled = false;
                if(!Loading()) UpdateDir();
            }
        }
    }
}

BEGIN_COPYS(UIProxy)
    COPY_SUPERCLASS(UIComponent)
    CREATE_COPY(UIProxy)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mEnv)
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(UIProxy, 0x4F);

BEGIN_LOADS(UIProxy)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void UIProxy::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    UIComponent::PreLoad(bs);
}

// fn_80575AB0
void UIProxy::PostLoad(BinStream& bs){
    mDir.PostLoad(0);
    UIComponent::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev == 1){
        bool b; bs >> b;
    }
    if(gRev > 2) bs >> mEnv;
    UpdateDir();
}

// fn_80575B64 - poll
void UIProxy::Poll(){
    UIComponent::Poll();
    if(!Loading() && !mDir.Ptr() && mDir.IsLoaded()){
        mDir.PostLoad(0);
        UpdateDir();
    }
    if(mDir.Ptr() && Showing()){
        SyncDir();
        mDir->Poll();
        mPolled = true;
    }
}

// fn_80575C1C
void UIProxy::DrawShowing(){
    if(mDir.Ptr() && mPolled){
        RndEnviron* oldEnv = mDir->GetEnv();
        mDir->SetEnv(mEnv);
        mDir->DrawShowing();
        mDir->SetEnv(oldEnv);
    }
}

// fn_80575CBC
RndDrawable* UIProxy::CollideShowing(const Segment& seg, float& f, Plane& pl){
    if(!mDir.Ptr()) return 0;
    else {
        SyncDir();
        return mDir->CollideShowing(seg, f, pl) ? this : 0;
    }
}

int UIProxy::CollidePlane(const Plane& pl){
    if(!mDir.Ptr()) return -1;
    else {
        SyncDir();
        return mDir->CollidePlane(pl);
    }
}

// fn_80575DC0
void UIProxy::SetProxyDir(const FilePath& fp, bool b){
    mMainTrans = 0;
    mDir.LoadFile(fp, true, b, kLoadFront, false);
    mPolled = 0;
}

// fn_80575E14
void UIProxy::SetProxyDir(RndDir* dir){
    mDir = dir;
    mPolled = 0;
    UpdateDir();
}

// fn_80575E54
void UIProxy::SyncDir(){
    const Transform& world = WorldXfm();
    if(mSyncOnMove && !TheLoadMgr.EditMode()){
        if(world == mOldXfm) return;
        mOldXfm = world;
    }
    if(mMainTrans) mMainTrans->SetWorldXfm(world);
    else {
        if(mDir->TransParent()) mDir->SetWorldXfm(world);
        else mDir->SetLocalXfm(world);
    }
    HandleType(sync_dir_msg);
}

// fn_80576014
void UIProxy::UpdateDir(){
    DataArray* transArr = TypeDef()->FindArray("main_trans", false);
    if(transArr){
        if(mDir.Ptr()){
            mMainTrans = mDir->Find<RndTransformable>(transArr->Str(1), true);
        }
        else {
            MILO_WARN("%s Couldn't load main_trans", PathName(this));
            mMainTrans = 0;
        }
    }
    else mMainTrans = 0;
    UpdateSphere();
    if(mDir.Ptr()){
        mDir->Enter();
        mPolled = false;
        mOldXfm.v.x = -1e+30f;
    }
}

DataNode UIProxy::OnSetProxyDir(DataArray* da){
    if(da->Size() == 2){
        SetProxyDir(FilePath(da->Str(2)), da->Int(3));
    }
    else SetProxyDir(da->Obj<RndDir>(2));
    return DataNode(1);
}

BEGIN_HANDLERS(UIProxy)
    HANDLE_EXPR(proxy_dir, mDir)
    HANDLE(set_proxy_dir, OnSetProxyDir)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x10F)
END_HANDLERS

BEGIN_PROPSYNCS(UIProxy)
    SYNC_PROP_STATIC(environ, mEnv)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS