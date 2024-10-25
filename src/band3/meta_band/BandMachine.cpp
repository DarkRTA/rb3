#include "meta_band/BandMachine.h"
#include "game/NetGameMsgs.h"

bool IsWaitingNetUIState(NetUIState state){
    return state >= 3 && state <= 8;
}

BandMachine::BandMachine() : unk1c(0), unk20(0), unk60(""), unk6c(""), unk78(0) {

}

void BandMachine::Reset(){
    unk1c = 0;
    unk20 = 0;
    unk60 = "";
    unk6c = "";
    unk78 = 0;
}