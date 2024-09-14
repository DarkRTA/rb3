#include "bandobj/TrackPanelDir.h"
#include "utl/Symbols.h"

TrackPanelDir::TrackPanelDir() : unk258(this, 0), mCrowdMeter(this, 0), unk270(this, 0), unk27c(this, 0), mEndingBonus(this, 0), unk294(this, 0), unk2a0(this, 0),
    unk2ac(1), unk2ad(0), mTracksExtended(0), mGemTrackRsrcMgr(this, 0), mVocals(1), mVocalsNet(0) {

}

TrackPanelDir::~TrackPanelDir(){
    
}

BEGIN_HANDLERS(TrackPanelDir)
    HANDLE_ACTION(game_won, GameWon())
    HANDLE_ACTION(game_lost, GameLost())
    HANDLE_ACTION(game_skip, GameLost())
    HANDLE_ACTION(set_crowd_rating, SetCrowdRating(_msg->Float(2)))
    HANDLE_ACTION(game_won_finale, GameWon())
    HANDLE_EXPR(tracks_extended, TracksExtended())
    HANDLE_SUPERCLASS(TrackPanelDirBase)
    HANDLE_CHECK(0x3F3)
END_HANDLERS