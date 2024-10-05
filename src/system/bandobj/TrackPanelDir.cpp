#include "bandobj/TrackPanelDir.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(TrackPanelDir);

TrackPanelDir::TrackPanelDir() : unk244(1), mTestMultiplier(1), unk24c(0), unk250(0), mVocalTrack(this, 0), mCrowdMeter(this, 0), mBandScoreMultiplier(this, 0),
    mBandScoreMultiplierTrig(this, 0), mEndingBonus(this, 0), mScoreboard(this, 0), mPulseAnimGrp(this, 0),
    unk2ac(1), unk2ad(0), mTracksExtended(0), mGemTrackRsrcMgr(this, 0), mVocals(1), mVocalsNet(0) {
    for(int i = 0; i < 4; i++){
        mGemTracks.push_back(ObjPtr<GemTrackDir, ObjectDir>(this, 0));
        unk2d0[i] = 0;
    }
    unk2c0 = 0;
    unk2c4 = 1;
    unk2c8 = 2;
    unk2cc = -1;
}

TrackPanelDir::~TrackPanelDir(){
    delete mGemTrackRsrcMgr;
}

SAVE_OBJ(TrackPanelDir, 0x3F)

void TrackPanelDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    TrackPanelDirBase::PreLoad(bs);
}

void TrackPanelDir::PostLoad(BinStream& bs){
    TrackPanelDirBase::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev < 1){
        int i;
        bs >> i >> i >> i >> i;
    }
}

BEGIN_COPYS(TrackPanelDir)
    COPY_SUPERCLASS(TrackPanelDirBase)
END_COPYS

void TrackPanelDir::SyncObjects(){
    PanelDir::SyncObjects();
    if(!mBandScoreMultiplier) mBandScoreMultiplier = Find<RndDir>("star_meter_multiplier", true);
    if(!mBandScoreMultiplierTrig) mBandScoreMultiplierTrig = Find<EventTrigger>("star_multiplier_number.trig", true);
    if(!mCrowdMeter) mCrowdMeter = Find<BandCrowdMeter>("crowd_meter", true);
    if(!mEndingBonus) mEndingBonus = Find<EndingBonus>("ending_bonus", true);
    if(!mVocalTrack) mVocalTrack = Find<VocalTrackDir>("vocals", true);
    if(!mApplauseMeter) mApplauseMeter = Find<RndDir>("applause_meter", true);
    if(!mBandLogoRival) mBandLogoRival = Find<RndDir>("bandlogo_rival", true);
    if(!mBandLogo) mBandLogo = Find<RndDir>("bandlogo", true);
    if(!mScoreboard) mScoreboard = Find<RndDir>("scoreboard", true);
    if(!mPulseAnimGrp) mPulseAnimGrp = Find<RndGroup>("beat_anims.grp", false);
    if(!mGemTracks[0]){
        mGemTracks[0] = Find<GemTrackDir>("track_0", true);
        mGemTracks[0]->mGemTrackDirID = 0;
    }
    if(!mGemTracks[1]){
        mGemTracks[1] = Find<GemTrackDir>("track_1", true);
        mGemTracks[1]->mGemTrackDirID = 1;
    }
    if(!mGemTracks[2]){
        mGemTracks[2] = Find<GemTrackDir>("track_2", true);
        mGemTracks[2]->mGemTrackDirID = 2;
    }
    if(!mGemTracks[3]){
        mGemTracks[3] = Find<GemTrackDir>("track_3", true);
        mGemTracks[3]->mGemTrackDirID = 3;
    }
    if(!mVocalTrack->mEndgameFeedback) mVocalTrack->mEndgameFeedback = Find<RndDir>("endgame_feedback_vox", false);
    if(!mGemTrackRsrcMgr || !mGemTrackRsrcMgr->unk1c){
        RELEASE(mGemTrackRsrcMgr);
        ObjectDir* dir = Find<ObjectDir>("gem_track_resources", false);
        if(dir) mGemTrackRsrcMgr = new GemTrackResourceManager(dir);
    }
}

void TrackPanelDir::AssignTracks(){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0xA3);
    mInstruments.clear();
    for(int i = 0; i < 5; i++) mInstruments.push_back(kInstNone);
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