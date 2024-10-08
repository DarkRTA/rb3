#include "meta_band/OvershellPanel.h"
#include "game/BandUserMgr.h"
#include "meta_band/SessionMgr.h"

OvershellPanel::OvershellPanel(SessionMgr* smgr, BandUserMgr* umgr) : Synchronizable("overshell"), mPanelOverrideFlow(kOverrideFlow_None), mActiveStatus(kOvershellInactive),
    mSongOptionsRequired(0), unk89(0), unk8a(1), mPartRestrictedUser(0), mPartRestriction(kTrackNone), mMinimumDifficulty(kDifficultyEasy), mPartResolver(0),
    unk4b8(0), unk4bc(0), unk4c8(0) {
    if(smgr) mSessionMgr = smgr;
    else {
        MILO_ASSERT(TheSessionMgr, 0x73);
        mSessionMgr = TheSessionMgr;
    }
    if(umgr) mBandUserMgr = umgr;
    else {
        MILO_ASSERT(TheBandUserMgr, 0x7D);
        mBandUserMgr = TheBandUserMgr;
    }
}

OvershellPanel::~OvershellPanel(){

}