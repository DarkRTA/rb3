#include "world/Reflection.h"
#include "obj/Object.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

INIT_REVS(WorldReflection)

WorldReflection::WorldReflection()
    : mDraws(this), mLodChars(this), mVerticalStretch(1.0f), unke0(0), mHideList(this),
      mShowList(this), unk104(this), unk114(this) {
    unkdc = ObjectDir::Main()->New<RndCam>("");
}

WorldReflection::~WorldReflection() { delete unkdc; }

void WorldReflection::DoHide() {
    unk104.clear();
    unk114.clear();
    FOREACH (it, mHideList) {
        RndDrawable *cur = *it;
        if (cur->Showing()) {
            cur->SetShowing(false);
            unk114.push_back(cur);
        }
    }
    FOREACH (it, mShowList) {
        RndDrawable *cur = *it;
        if (!cur->Showing()) {
            cur->SetShowing(true);
            unk104.push_back(cur);
        }
    }
}

void WorldReflection::UnHide() {
    FOREACH (it, unk104) {
        RndDrawable *cur = *it;
        cur->SetShowing(false);
    }
    FOREACH (it, unk114) {
        RndDrawable *cur = *it;
        cur->SetShowing(true);
    }
    unk104.clear();
    unk114.clear();
}

void WorldReflection::DoLOD(int i) {
    FOREACH (it, mLodChars) {
        Character *c = *it;
        if (c)
            c->SetMinLod(i);
    }
}

void WorldReflection::DrawShowing() {
    START_AUTO_TIMER("world_reflect");
    if (!unke0) {
        unke0 = true;
        RndCam *cur = RndCam::sCurrent;
        unkdc->Copy(RndCam::sCurrent, kCopyDeep);
        Transform tf48(WorldXfm());
        Transform tf78;
        Invert(tf48, tf78);
        Transform tfa8;
        tfa8.Reset();
        tfa8.m.z.z = -mVerticalStretch;
        Multiply(tf78, tfa8, tfa8);
        Multiply(tfa8, tf48, tfa8);
        Multiply(cur->WorldXfm(), tfa8, unkdc->DirtyLocalXfm());
        unkdc->Select();
        Mode oldMode = TheRnd->DrawMode();
        TheRnd->SetDrawMode((Mode)7);
        DoHide();
        DoLOD(1);
        FOREACH (it, mDraws) {
            RndDrawable *cur = *it;
            if (cur)
                cur->Draw();
        }
        DoLOD(-1);
        UnHide();
        TheRnd->SetDrawMode(oldMode);
        cur->Select();
        unke0 = false;
    }
}

SAVE_OBJ(WorldReflection, 0xA0)

BEGIN_LOADS(WorldReflection)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mVerticalStretch;
    bs >> mDraws;
    if (gRev > 1)
        bs >> mHideList >> mShowList;
    if (gRev > 2)
        bs >> mLodChars;
END_LOADS

BEGIN_COPYS(WorldReflection)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(WorldReflection)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mVerticalStretch)
        COPY_MEMBER(mDraws)
        COPY_MEMBER(mHideList)
        COPY_MEMBER(mShowList)
        COPY_MEMBER(mLodChars)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(WorldReflection)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD0)
END_HANDLERS

BEGIN_PROPSYNCS(WorldReflection)
    SYNC_PROP(vertical_stretch, mVerticalStretch)
    SYNC_PROP(draws, mDraws)
    SYNC_PROP(lod_chars, mLodChars)
    SYNC_PROP(hide_list, mHideList)
    SYNC_PROP(show_list, mShowList)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS