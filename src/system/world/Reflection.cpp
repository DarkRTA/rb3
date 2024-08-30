#include "world/Reflection.h"
#include "rndobj/Cam.h"
#include "utl/Symbols.h"

INIT_REVS(WorldReflection)

WorldReflection::WorldReflection() : mDraws(this, kObjListNoNull), mLodChars(this, kObjListNoNull), mVerticalStretch(1.0f), unke0(0), mHideList(this, kObjListNoNull),
    mShowList(this, kObjListNoNull), unk104(this, kObjListNoNull), unk114(this, kObjListNoNull) {
    unkdc = ObjectDir::Main()->New<RndCam>("");
}

WorldReflection::~WorldReflection(){
    delete unkdc;
}

void WorldReflection::DoHide(){
    unk104.clear();
    unk114.clear();
    for(ObjPtrList<RndDrawable, ObjectDir>::iterator it = mHideList.begin(); it != mHideList.end(); ++it){
        RndDrawable* cur = *it;
        if(cur->Showing()){
            cur->SetShowing(false);
            unk114.push_back(cur);
        }
    }
    for(ObjPtrList<RndDrawable, ObjectDir>::iterator it = mShowList.begin(); it != mShowList.end(); ++it){
        RndDrawable* cur = *it;
        if(!cur->Showing()){
            cur->SetShowing(true);
            unk104.push_back(cur);
        }
    }
}

void WorldReflection::UnHide(){
    for(ObjPtrList<RndDrawable, ObjectDir>::iterator it = unk104.begin(); it != unk104.end(); ++it){
        RndDrawable* cur = *it;
        cur->SetShowing(false);
    }
    for(ObjPtrList<RndDrawable, ObjectDir>::iterator it = unk114.begin(); it != unk114.end(); ++it){
        RndDrawable* cur = *it;
        cur->SetShowing(true);
    }
    unk104.clear();
    unk114.clear();
}

void WorldReflection::DoLOD(int i){
    for(ObjPtrList<Character, ObjectDir>::iterator it = mLodChars.begin(); it != mLodChars.end(); ++it){
        Character* c = *it;
        if(c) c->SetMinLod(i);
    }
}

void WorldReflection::DrawShowing(){
    START_AUTO_TIMER("world_reflect");
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
    if(gRev > 1) bs >> mHideList >> mShowList;
    if(gRev > 2) bs >> mLodChars;
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