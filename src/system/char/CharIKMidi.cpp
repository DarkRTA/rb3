#include "char/CharIKMidi.h"
#include "obj/Task.h"
#include "obj/Msg.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKMidi)

CharIKMidi::CharIKMidi() : mBone(this, 0), mCurSpot(this, 0), mNewSpot(this, 0), mSpotChanged(0), mAnimBlender(this, 0), mMaxAnimBlend(1.0f), mAnimFracPerBeat(0.0f), mAnimFrac(0.0f) {
    Enter();
}

CharIKMidi::~CharIKMidi(){

}

void CharIKMidi::Enter(){
    mCurSpot = 0;
    mNewSpot = 0;
    mSpotChanged = false;
    mFrac = 0.0f;
    mFracPerBeat = 0.0f;
    mLocalXfm.Reset();
    mOldLocalXfm.Reset();
    RndPollable::Enter();
}

void DoDebugDraws(CharIKMidi* mid, float f){
    for(ObjDirItr<MsgSource> it(ObjectDir::Main(), true); it != 0; ++it){
        if(it){
            static Message msg("debug_draw", DataNode(2.0f), DataNode(2.0f));
            msg->Node(2) = DataNode(f);
            msg->Node(3) = DataNode(TheTaskMgr.Beat());
            it->Handle(msg, false);
        }
    }
}

void CharIKMidi::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBone);
    changedBy.push_back(mBone);
    changedBy.push_back(mCurSpot);
}

SAVE_OBJ(CharIKMidi, 0xEA);

BEGIN_LOADS(CharIKMidi)
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mBone;
    if(gRev < 3){
        ObjVector<ObjPtr<RndTransformable, ObjectDir> > vec(this);
        bs >> vec;
    }
    if(gRev == 2 || gRev == 3){
        String asdf;
        bs >> asdf;
    }
    if(gRev > 4){
        bs >> mAnimBlender;
        bs >> mMaxAnimBlend;
    }
END_LOADS

BEGIN_COPYS(CharIKMidi)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharIKMidi)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBone)
        COPY_MEMBER(mAnimBlender)
        COPY_MEMBER(mMaxAnimBlend)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKMidi)
    HANDLE_ACTION(new_spot, NewSpot(Dir()->Find<RndTransformable>(_msg->Str(2), true), _msg->Float(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x11C)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKMidi)
    SYNC_PROP(bone, mBone)
    SYNC_PROP(anim_blend_weightable, mAnimBlender)
    SYNC_PROP(anim_blend_max, mMaxAnimBlend)
    SYNC_PROP_SET(cur_spot, mCurSpot, NewSpot(_val.Obj<RndTransformable>(0), 0))
END_PROPSYNCS