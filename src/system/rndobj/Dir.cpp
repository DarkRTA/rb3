#include "rndobj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "utl/FilePath.h"
#include "obj/ObjVersion.h"
#include "rndobj/PostProc.h"
#include "utl/Symbols.h"

INIT_REVS(RndDir)

DECOMP_FORCEACTIVE(Dir, "", __FILE__)

RndDir::RndDir() : mEnv(this, 0) {
    
}

void RndDir::Replace(Hmx::Object* o1, Hmx::Object* o2){
    MsgSource::Replace(o1, o2);
    RndTransformable::Replace(o1, o2);
}

void RndDir::Export(DataArray* da, bool b){
    MsgSource::Export(da, b);
    for(int i = 0; i < mSubDirs.size(); i++){
        if(mSubDirs[i]){
            mSubDirs[i]->Export(da, false);
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

void RndDir::OldLoadProxies(BinStream& bs, int i) {
    int items;
    bs >> items;
    if (items <= 0) return;
    for (int i = 0; i < items; i++) {
        FilePath a;
        class String b, c, d;
        char fpath[256];
        bs.ReadString(fpath, 256);
        a.Set(FilePath::sRoot.c_str(), fpath);
        int h, o, l, y, j, e, s, u, S;
        bs >> b;
        bs >> h;
        bs >> o;
        bs >> l;
        bs >> y;
        bs >> j;
        bs >> e;
        bs >> s;
        bs >> u;
        bs >> S; // somehow, this still isn't enough
    }
}

void RndDir::Load(BinStream& bs) { ObjectDir::Load(bs); }

void RndDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0xA, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    ObjectDir::PreLoad(bs);
}

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
            RndEnviron* envToSet = 0;
            char buf[0x80];
            bs.ReadString(buf, 0x80);
            if(envPtr && envPtr->Dir()){
                envPtr = dynamic_cast<RndEnviron*>(envPtr->Dir()->FindObject(buf, false));
            }
            else envPtr = 0;
        }
        else bs >> mEnv;
    }
    if(gRev > 2 && gRev != 9) bs >> mTestEvent;
    if(gRev - 4 < 5){
        Symbol s;
        bs >> s >> s;
    }
    if(gRev - 5 <= 2){
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
        if (d) d->mShowing = show;
    }
    return DataNode();
}

DataNode RndDir::OnSupportedEvents(DataArray*) {
    
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
