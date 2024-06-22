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