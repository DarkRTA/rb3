#include "rndobj/Poll.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

BEGIN_HANDLERS(RndPollable);
    HANDLE_ACTION(enter, Enter());
    HANDLE_ACTION(poll, Poll());
    HANDLE_ACTION_STATIC(exit, Exit());
    HANDLE_CHECK(0x1A);
END_HANDLERS;

void RndPollable::Enter(){
    HandleType(enter_msg);
}

void RndPollable::Exit(){
    HandleType(exit_msg);
}
