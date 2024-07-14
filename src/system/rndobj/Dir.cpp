#include "rndobj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "utl/FilePath.h"
#include "obj/ObjVersion.h"
#include "obj/DirLoader.h"
#include "rndobj/PostProc.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Utl.h"
#include "utl/STLHelpers.h"
#include <algorithm>
#include "utl/Symbols.h"

INIT_REVS(RndDir)

DECOMP_FORCEACTIVE(Dir, "", __FILE__)

RndDir::RndDir() : mEnv(this, 0) {
    
}

void RndDir::Replace(Hmx::Object* o1, Hmx::Object* o2){
    MsgSource::Replace(o1, o2);
    RndTransformable::Replace(o1, o2);
}

void RndDir::RemovingObject(Hmx::Object* o){
    Hmx::Object* obj = o;
    ObjectDir::RemovingObject(obj);
    VectorRemove(mDraws, obj);
    VectorRemove(mPolls, obj);
    VectorRemove(mAnims, obj);
}

// fn_805D265C
void RndDir::SetSubDir(bool b){
    ObjectDir::SetSubDir(b);
    mDraws.clear();
    mPolls.clear();
    mAnims.clear();
}

// fn_805D26A0
void RndDir::SyncObjects(){
    mAnims.clear();
    mPolls.clear();
    if(!IsSubDir()){
        SyncDrawables();
        std::list<RndAnimatable*> animchildren;
        for(ObjDirItr<RndAnimatable> it(this, true); it != 0; ++it){
            if(it != this){
                mAnims.push_back(it);
                it->ListAnimChildren(animchildren);
            }
        }
        for(std::list<RndAnimatable*>::iterator it = animchildren.begin(); it != animchildren.end(); ++it){
            VectorRemove(mAnims, *it);
        }
        std::list<RndPollable*> pollchildren;
        for(ObjDirItr<RndPollable> it(this, true); it != 0; ++it){
            if(it != this){
                mPolls.push_back(it);
                it->ListPollChildren(pollchildren);
            }
        }
        for(std::list<RndPollable*>::iterator it = pollchildren.begin(); it != pollchildren.end(); ++it){
            VectorRemove(mPolls, *it);
        }
        std::sort(mPolls.begin(), mPolls.end(), SortPolls);
        if(this != mDir){
            MsgSource* src = dynamic_cast<MsgSource*>(mDir);
            if(src) ChainSourceSubdir(src, this);
        }
        ObjectDir::SyncObjects();
    }
}

// fn_805D33A4
void RndDir::SyncDrawables(){
    mDraws.clear();
    if(!IsSubDir()){
        std::list<RndDrawable*> drawchildren;
        for(ObjDirItr<RndDrawable> it(this, true); it != 0; ++it){
            if(it != this){
                mDraws.push_back(it);
                it->ListDrawChildren(drawchildren);
                it->UpdatePreClearState();
            }
        }
        UpdatePreClearState();
        for(std::list<RndDrawable*>::iterator it = drawchildren.begin(); it != drawchildren.end(); ++it){
            VectorRemove(mDraws, *it);
        }
        std::sort(mDraws.begin(), mDraws.end(), SortDraws);
    }
}

// fn_805D37CC - update sphere

void RndDir::Poll(){
    if(Showing()){
        for(std::vector<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
            (*it)->Poll();
        }
    }
}

void RndDir::Enter(){
    if(TheLoadMgr.EditMode()){
        DataNode events = OnSupportedEvents(0);
        DataArray* arr = events.Array(0);
        if(!arr->Contains(DataNode(mTestEvent))){
            mTestEvent = Symbol("");
        }
    }
    for(std::vector<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
        (*it)->Enter();
    }
    if(this != mDir){
        MsgSource* src = dynamic_cast<MsgSource*>(mDir);
        if(src) ChainSourceSubdir(src, this);
    }
    RndPollable::Enter();
}

void RndDir::Exit(){
    for(std::vector<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); ++it){
        (*it)->Exit();
    }
    RndPollable::Exit();
}

// fn_805D3C1C
void RndDir::ListPollChildren(std::list<RndPollable*>& children) const {
    if(IsProxy()){
        children.insert(children.begin(), mPolls.begin(), mPolls.end());
    }
}

int RndDir::CollidePlane(const Plane& pl){
    int ret = -1;
    for(std::vector<RndDrawable*>::iterator it = mDraws.begin(); it != mDraws.end(); ++it){
        if(it == mDraws.begin()) ret = (*it)->CollidePlane(pl);
        else if(ret != (*it)->CollidePlane(pl)) return 0;
    }
    return ret;
}

void RndDir::CollideListSubParts(const Segment& seg, std::list<Collision>& colls){
    if(CollideSphere(seg)){
        for(std::vector<RndDrawable*>::iterator it = mDraws.begin(); it != mDraws.end(); ++it){
            (*it)->CollideList(seg, colls);
        }
    }
}

void RndDir::CollideList(const Segment& seg, std::list<Collision>& colls){
    if(IsProxy() && !sForceSubpartSelection){
        RndDrawable::CollideList(seg, colls);
    }
    else CollideListSubParts(seg, colls);
}

void RndDir::SetFrame(float frame, float blend){
    if(Showing()){
        RndAnimatable::SetFrame(frame, blend);
        for(std::vector<RndAnimatable*>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
            (*it)->SetFrame(frame, blend);
        }
    }
}

float RndDir::EndFrame(){
    float frame = 0.0f;
    for(std::vector<RndAnimatable*>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        float end = (*it)->EndFrame();
        if(frame < end) frame = end;
    }
    return frame;
}

// fn_805D4A9C
void RndDir::Export(DataArray* da, bool b){
    MsgSource::Export(da, b);
    for(int i = 0; i < mSubDirs.size(); i++){
        if(mSubDirs[i]){
            mSubDirs[i]->Export(da, false);
        }
    }
}

void RndDir::ChainSourceSubdir(MsgSource* src, ObjectDir* dir){
    MsgSource* src2 = dynamic_cast<MsgSource*>(dir);
    if(src2){
        ChainSource(src, src2);
        for(int i = 0; i < dir->mSubDirs.size(); i++){
            ChainSourceSubdir(src, dir->mSubDirs[i].Ptr());
        }
    }
}

SAVE_OBJ(RndDir, 0x1C1)

BEGIN_COPYS(RndDir)
    COPY_SUPERCLASS(ObjectDir)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(RndDir)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mEnv)
            COPY_MEMBER(mTestEvent)
        }
    END_COPYING_MEMBERS
END_COPYS

// fn_805D4CAC
void RndDir::OldLoadProxies(BinStream& bs, int rev) {
    int items;
    bs >> items;
    for (int i = 0; i < items; i++) {
        FilePath fp68;
        String name;
        Transform t58;
        String s80;
        String s8c;
        bs >> fp68;
        bs >> name;
        bs >> t58;
        if(rev > 0xB) bs >> s80;
        else s80 = 0;
        bs >> s8c;
        float f94;
        bs >> f94;
        bool b98;
        if(rev > 0xB) bs >> b98;
        else b98 = true;
        RndDir* loadedDir = dynamic_cast<RndDir*>(DirLoader::LoadObjects(fp68, 0, 0));
        MILO_ASSERT(!name.empty(), 0x203);
        loadedDir->SetName(name.c_str(), this);
        loadedDir->SetDirtyLocalXfm(t58);
        loadedDir->SetTransParent(Find<RndTransformable>(s80.c_str(), false), false);
        loadedDir->SetOrder(f94);
        loadedDir->SetShowing(b98);
        loadedDir->SetEnv(Find<RndEnviron>(s8c.c_str(), false));
        SetProxyFile(fp68, true);
    }
}

void RndDir::Load(BinStream& bs) { ObjectDir::Load(bs); }

void RndDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0xA, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    ObjectDir::PreLoad(bs);
}

// fn_805D4F54
void RndDir::PostLoad(BinStream& bs){
    ObjectDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    LOAD_SUPERCLASS(RndAnimatable)
    LOAD_SUPERCLASS(RndDrawable)
    if(gRev != 0) LOAD_SUPERCLASS(RndTransformable)
    if(gRev > 1){
        if(gLoadingProxyFromDisk){
            ObjPtr<RndEnviron, ObjectDir> envPtr(this, 0);
            envPtr.Load(bs, false, 0);
        }
        else bs >> mEnv;
    }
    if(gRev > 2 && gRev != 9) bs >> mTestEvent;
    if(gRev == 4 || gRev == 5 || gRev == 6 || gRev == 7 || gRev == 8){
        Symbol s;
        bs >> s >> s;
    }
    if(gRev == 5 || gRev == 6 || gRev == 7){
        RndPostProc* rpp = Hmx::Object::New<RndPostProc>();
        rpp->LoadRev(bs, gRev);
        delete rpp;
    }
}

BEGIN_HANDLERS(RndDir)
    HANDLE(show_objects, OnShowObjects)
    HANDLE(supported_events, OnSupportedEvents)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(ObjectDir)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(609)
END_HANDLERS

DataNode RndDir::OnShowObjects(DataArray* da) {
    DataArray* array = da->Array(2);
    bool show = da->Int(3);
    for (int i = 0; i < array->Size(); i++) {
        RndDrawable* d = array->Obj<RndDrawable>(i);
        if (d) d->SetShowing(show);
    }
    return DataNode();
}

DataNode RndDir::OnSupportedEvents(DataArray* da) {
    DataArrayPtr ptr(new DataArray(0x400));
    std::list<DataArray*> oList;
    ptr.Node(0) = DataNode(Symbol());
    int idx = 1;
    for(ObjDirItr<EventTrigger> it(this, true); it != 0; ++it){
        DataArray* events = it->SupportedEvents();
        if(events){
            oList.push_back(events);
            for(int i = 0; i < events->Size(); i++){
                ptr.Node(idx++) = events->Node(i);
            }
        }
    }
    ((DataArray*)ptr)->Resize(idx);
    return DataNode(ptr);
}

BEGIN_PROPSYNCS(RndDir)
    SYNC_PROP_STATIC(environ, mEnv)
    SYNC_PROP(polls, mPolls)
    SYNC_PROP(draws, mDraws)
    SYNC_PROP(test_event, mTestEvent)
    SYNC_SUPERCLASS(ObjectDir)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
