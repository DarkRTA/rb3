#include "bandobj/PlayerDiffIcon.h"
#include "utl/Symbols.h"

PlayerDiffIcon::PlayerDiffIcon() : unk118(0), unk11c(0), mNumPlayers(1), mDiff(0), unk130(1.0f), unk134(1.0f), unk138(1.0f), unk13c(1.0f), unk140(1.0f) {

}

PlayerDiffIcon::~PlayerDiffIcon(){
    
}

BEGIN_HANDLERS(PlayerDiffIcon)
    HANDLE_ACTION(set_num_players_diff, SetNumPlayersDiff(_msg->Int(2), _msg->Int(3)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xBD)
END_HANDLERS

BEGIN_PROPSYNCS(PlayerDiffIcon)
    SYNC_PROP(num_players, mNumPlayers)
    SYNC_PROP(diff, mDiff)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS