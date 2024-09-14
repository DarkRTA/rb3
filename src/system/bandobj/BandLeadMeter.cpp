#include "bandobj/BandLeadMeter.h"
#include "utl/Symbols.h"

BandLeadMeter::BandLeadMeter() : mNeedleAnim(this, 0), mLogoGlowAnim(this, 0), mGlowMesh1(this, 0), mGlowMesh2(this, 0), mPeggedAnim1(this, 0), mPeggedAnim2(this, 0),
    mLensMesh(this, 0), mLensMatNeutral(this, 0), mLensMat1(this, 0), mLensMat2(this, 0), unk204(10000), mScoreDiff(0) {
    SyncScores();
}

BEGIN_HANDLERS(BandLeadMeter)
    HANDLE_ACTION(refresh, SyncScores())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x80)
END_HANDLERS

BEGIN_PROPSYNCS(BandLeadMeter)
    SYNC_PROP_MODIFY(score_diff, mScoreDiff, SyncScores())
    SYNC_PROP(needle_anim, mNeedleAnim)
    SYNC_PROP(logo_glow_anim, mLogoGlowAnim)
    SYNC_PROP(glow_mesh_1, mGlowMesh1)
    SYNC_PROP(glow_mesh_2, mGlowMesh2)
    SYNC_PROP(pegged_anim_1, mPeggedAnim1)
    SYNC_PROP(pegged_anim_2, mPeggedAnim2)
    SYNC_PROP(lens_mesh, mLensMesh)
    SYNC_PROP(lens_mat_neutral, mLensMatNeutral)
    SYNC_PROP(lens_mat_1, mLensMat1)
    SYNC_PROP(lens_mat_2, mLensMat2)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS