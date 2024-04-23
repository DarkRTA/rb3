#include "rndobj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "utl/FilePath.h"
#include "utl/Symbols.h"

RndDir::RndDir() : mEnv(this, 0) {
    
}

void RndDir::Replace(Hmx::Object* o1, Hmx::Object* o2){
    MsgSource::Replace(o1, o2);
    RndTransformable::Replace(o1, o2);
}

SAVE_OBJ(RndDir, 0x1C1)

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
    SYNC_PROP(polls, mPolls)
    SYNC_PROP(draws, mDraws)
    SYNC_SUPERCLASS(ObjectDir)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
