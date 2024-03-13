#include "char/CharGuitarString.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

CharGuitarString::CharGuitarString() : mOpen(0), mNut(this, 0), mBridge(this, 0), mBend(this, 0), mTarget(this, 0) {

}

CharGuitarString::~CharGuitarString(){
    
}

SAVE_OBJ(CharGuitarString, 0x47)

BEGIN_COPYS(CharGuitarString)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(CharGuitarString)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mNut)
        COPY_MEMBER(mBridge)
        COPY_MEMBER(mBend)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(CharGuitarString)
    HANDLE_ACTION(set_open, mOpen = _msg->Int(2) != 0)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x70)
END_HANDLERS
