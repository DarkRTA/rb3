#include "rndobj/Poll.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

BEGIN_HANDLERS(RndPollable);
    HANDLE_ACTION(enter, Enter());
    HANDLE_ACTION(poll, Poll());
    static Symbol _s("exit");
    if(sym == _s){
        Exit();
        return DataNode(0);
    }
    HANDLE_CHECK(0x1A);
END_HANDLERS;

void RndPollable::Enter(){
    HandleType(enter_msg.Data());
}

void RndPollable::Exit(){
    HandleType(exit_msg.Data());
}
