#include "char/CharGuitarString.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharGuitarString)

CharGuitarString::CharGuitarString() : mOpen(0), mNut(this, 0), mBridge(this, 0), mBend(this, 0), mTarget(this, 0) {

}

CharGuitarString::~CharGuitarString(){
    
}

// fn_80507700 - poll
// checks out in retail: https://decomp.me/scratch/Bxu4k
void CharGuitarString::Poll(){
    if(!mNut || !mBridge || !mBend || !mTarget) return;
    Transform tf50(mBend->WorldXfm());
    const Vector3& nutvec = mNut->WorldXfm().v;
    const Vector3& bridgevec = mBridge->WorldXfm().v;
    Transform& tf4(mTarget->WorldXfm());
    Vector3 tmp;
    Subtract(tf4.v, nutvec, tmp);
    Vector3 tmp2;
    Subtract(bridgevec, nutvec, tmp2);
    float clamped = Clamp(0.0f, 1.0f, Dot(tmp,tmp2) / Dot(tmp2,tmp2));
    if(mOpen) clamped = 0.0f;
    Interp(nutvec, bridgevec, clamped, tf50.v);
    mBend->SetWorldXfm(tf50);
}

void CharGuitarString::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mNut);
    changedBy.push_back(mBridge);
    changedBy.push_back(mTarget);
    change.push_back(mBend);
}


SAVE_OBJ(CharGuitarString, 0x47)

void CharGuitarString::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    Hmx::Object::Load(bs);
    bs >> mNut;
    bs >> mBridge;
    bs >> mBend;
    bs >> mTarget;
}

BEGIN_COPYS(CharGuitarString)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharGuitarString)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mNut)
        COPY_MEMBER(mBridge)
        COPY_MEMBER(mBend)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharGuitarString)
    HANDLE_ACTION(set_open, mOpen = _msg->Int(2) != 0)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x70)
END_HANDLERS

BEGIN_PROPSYNCS(CharGuitarString)
    SYNC_PROP(nut, mNut)
    SYNC_PROP(bridge, mBridge)
    SYNC_PROP(bend, mBend)
    SYNC_PROP(target, mTarget)
END_PROPSYNCS
