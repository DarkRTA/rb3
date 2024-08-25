#include "char/CharIKFoot.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKFoot)

CharIKFoot::CharIKFoot() : unk88(this, 0), unk94(0), mData(this, 0), mDataIndex(0), mMe(this, 0) {
    unk88 = Hmx::Object::New<RndTransformable>();
    unk88->DirtyLocalXfm().Reset();
}

CharIKFoot::~CharIKFoot(){
    delete unk88;
}

void CharIKFoot::Enter(){
    unk94 = 0;
    unkb4 = 0.0f;
}

void CharIKFoot::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character*>(dir);
}

// https://decomp.me/scratch/G9HMd retail scratch
void CharIKFoot::DoFSM(Transform& tf){
    if(mMe && mMe->Teleported()) unk94 = 0;
    float deltasecs = TheTaskMgr.DeltaSeconds();
    if(deltasecs < 0.0f) deltasecs = 0.0f;
    tf.m = mFinger->WorldXfm().m;
    tf.v.z = mFinger->WorldXfm().v.z;
    bool b2 = false;
    unka8.z = tf.v.z;
    float vecat = mData->mLocalXfm.v[mDataIndex];
    float f10;
    if(vecat >= 1.0f) {
        if(vecat > 0.0f){
            if(unk94 == 1) f10 = 0.6f;
            else f10 = 0.5f;
        }
        if(f10 > tf.v.z) b2 = true;
    }
    else b2 = true;
    if(unk94 == 0){
        tf.v = mFinger->WorldXfm().v;
        if(b2){
            unka8 = tf.v;
            unk94 = 1;
        }
    }
    if(unk94 == 1){
        if(!b2){
            unk94 = 2;
            unkb4 = Distance(mFinger->WorldXfm().v, tf.v);
        }
        else {
            Vector3 v3c;
            Subtract(mFinger->WorldXfm().v, unka8, v3c);
            float len = Length(v3c);
            if(len > 0.125f) v3c *= 0.125f / len;
            Add(unka8, v3c, tf.v);
            return;
        }
    }
    if(unk94 == 2){
        Vector3 v48;
        Subtract(mFinger->WorldXfm().v, tf.v, v48);
        float len = Length(v48);
        unkb4 = Min(-(deltasecs * 25.0f - unkb4), len);
        if(unkb4 <= 0.0f) unk94 = 0;
        else v48 *= (len - unkb4) / len;
        tf.v += v48;
        if(b2){
            unka8 = tf.v;
            unk94 = 1;
        }
    }
}

void CharIKFoot::Poll(){
    if(!mFinger || !mHand || !mData) return;
    mTargets.clear();
    mTargets.push_back(IKTarget(ObjPtr<RndTransformable, ObjectDir>(unk88), 0));
    DoFSM(unk88->DirtyLocalXfm());
    CharIKHand::Poll();
    mTargets.clear();
}

CharIKHand::IKTarget::IKTarget(ObjPtr<RndTransformable, ObjectDir> o, float f) : mTarget(o), mExtent(f) {}

void CharIKFoot::PollDeps(std::list<Hmx::Object*>& l1, std::list<Hmx::Object*>& l2){
    CharIKHand::PollDeps(l1, l2);
}

SAVE_OBJ(CharIKFoot, 0x138)

BEGIN_LOADS(CharIKFoot)
    LOAD_REVS(bs)
    ASSERT_REVS(6, 0)
    LOAD_SUPERCLASS(CharIKHand)
    if(gRev < 6){
        Symbol s;
        bs >> s;
    }
    if(gRev < 5){
        int i;
        if(gRev > 1) bs >> i;
        if(gRev > 2) bs >> i;
        if(gRev > 3) bs >> i;
    }
    else {
        bs >> mData;
        bs >> mDataIndex;
    }
END_LOADS

BEGIN_COPYS(CharIKFoot)
    COPY_SUPERCLASS(CharIKHand)
    CREATE_COPY(CharIKFoot)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mData)
        COPY_MEMBER(mDataIndex)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKFoot)
    HANDLE_SUPERCLASS(CharIKHand)
    HANDLE_CHECK(0x16E)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKFoot)
    SYNC_PROP(data, mData)
    SYNC_PROP(data_index, mDataIndex)
    SYNC_SUPERCLASS(CharIKHand)
END_PROPSYNCS