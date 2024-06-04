#include "char/CharGuitarString.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharGuitarString)

CharGuitarString::CharGuitarString() : mOpen(0), mNut(this, 0), mBridge(this, 0), mBend(this, 0), mTarget(this, 0) {

}

CharGuitarString::~CharGuitarString(){
    
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
