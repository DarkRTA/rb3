#include "MiniLeaderboardDisplay.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Symbols2.h"

INIT_REVS(MiniLeaderboardDisplay)

void MiniLeaderboardDisplay::Init() {
    Symbol s = MiniLeaderboardDisplay::StaticClassName(), s2;
    Hmx::Object::RegisterFactory(s, MiniLeaderboardDisplay::NewObject);
    TheUI->InitResources("MiniLeaderboardDisplay");
}

MiniLeaderboardDisplay::MiniLeaderboardDisplay() : mAllowSoloScores(true) {}

MiniLeaderboardDisplay::~MiniLeaderboardDisplay() {}

BEGIN_COPYS(MiniLeaderboardDisplay)
    CREATE_COPY_AS(MiniLeaderboardDisplay, p)
    MILO_ASSERT(p, 41);
    UIComponent::Copy(p, ty);
    mAllowSoloScores = p->mAllowSoloScores;
END_COPYS

SAVE_OBJ(MiniLeaderboardDisplay, 54)

BEGIN_LOADS(MiniLeaderboardDisplay)
    PreLoad(bs); PostLoad(bs);
END_LOADS

void MiniLeaderboardDisplay::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    if (gRev >= 1) {
        bs >> mAllowSoloScores;
    }
    UIComponent::PreLoad(bs);
}

void MiniLeaderboardDisplay::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

void MiniLeaderboardDisplay::DrawShowing() {
    RndDir* d = mResource->Dir();
    MILO_ASSERT(d, 88);
    d->SetWorldXfm(mCache->mFlags&1 ? WorldXfm_Force() : mWorldXfm);
    d->Draw();
}

BEGIN_HANDLERS(MiniLeaderboardDisplay)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(102)
END_HANDLERS

BEGIN_PROPSYNCS(MiniLeaderboardDisplay)
    SYNC_PROP_MODIFY(allow_solo_scores, mAllowSoloScores, Update())
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
