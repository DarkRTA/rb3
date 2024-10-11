#include "rndobj/Group.h"
#include "utl/Symbols.h"

int GROUP_REV = 14;
bool gInReplace;

RndGroup::RndGroup() : mObjects(this, kObjListOwnerControl), mEnv(this, 0), mDrawOnly(this, 0), mLod(this, 0), mLodScreenSize(0.0f), unkf8(0) {
    mSortInWorld = 0;
}

SAVE_OBJ(RndGroup, 0x30);

void RndGroup::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, GROUP_REV);
    if(rev > 7) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    RndTransformable::Load(bs);
    RndDrawable::Load(bs);
    if(rev > 10){
        bs >> mObjects >> mEnv;
        if(rev > 12) bs >> mDrawOnly;
        else mDrawOnly = 0;
        Update();
    }
    if(rev > 11){
        bs >> mLod >> mLodScreenSize;
    }
    if(rev > 13){
        bool read_in;
        bs >> read_in;
        mSortInWorld = read_in;
    }
    UpdateLODState();
}

BEGIN_COPYS(RndGroup)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(RndGroup)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mEnv)
        COPY_MEMBER(mDrawOnly)
        COPY_MEMBER(mLod)
        COPY_MEMBER(mLodScreenSize)
        COPY_MEMBER(mSortInWorld)
        if(ty == kCopyDeep) COPY_MEMBER(mObjects)
        else if(ty == kCopyFromMax) Merge(c);
    END_COPYING_MEMBERS
    Update();
END_COPYS

void RndGroup::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mObjects.begin();
    for(; it != mObjects.end(); ++it){
        if(*it == from) break;
    }
    if(it != mObjects.end()){
        AddObject(to, from);
        gInReplace = true;
        RemoveObject(from);
        gInReplace = false;
    }
}

BEGIN_HANDLERS(RndGroup)
    HANDLE_ACTION(sort_draws, SortDraws())
    HANDLE_ACTION(add_object, AddObject(_msg->GetObj(2), 0))
    HANDLE_ACTION(remove_object, RemoveObject(_msg->GetObj(2)))
    HANDLE_ACTION(clear_objects, ClearObjects())
    HANDLE(get_draws, OnGetDraws)
    if(sym == has_object){
        Hmx::Object* target = _msg->GetObj(2);
        Hmx::Object* existing_obj = 0;
        for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mObjects.begin(); it != mObjects.end(); ++it){
            if(*it == target){
                existing_obj = *it;
                break;
            }
        }
        return DataNode(existing_obj != 0);
    }
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x29B)
END_HANDLERS

BEGIN_PROPSYNCS(RndGroup)
    SYNC_PROP_MODIFY_ALT(objects, mObjects, Update())
    SYNC_PROP_STATIC(environ, mEnv)
    SYNC_PROP(draw_only, mDrawOnly)
    SYNC_PROP_MODIFY_ALT(lod, mLod, Update())
    SYNC_PROP_MODIFY(lod_screen_size, mLodScreenSize, UpdateLODState())
    {
        static Symbol _s("sort_in_world");
        if(sym == _s){
            if(_op == kPropSet) mSortInWorld = _val.Int();
            else _val = DataNode(mSortInWorld);
            return true;
        }
    }
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
