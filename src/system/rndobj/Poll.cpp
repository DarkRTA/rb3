#include "rndobj/Poll.h"
#include "utl/Messages.h"

void RndPollable::Enter(){
    HandleType(enter_msg.Data());
}

void RndPollable::Exit(){
    HandleType(exit_msg.Data());
}
