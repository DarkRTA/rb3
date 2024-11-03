#include "game/TrainerProgressMeter.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "rndobj/PropAnim.h"

TrainerProgressMeter::TrainerProgressMeter() : mProgressMeter(0), mBar(0), mGlow(0), mBoxes(0), mCurrent(-1) {

}

TrainerProgressMeter::~TrainerProgressMeter(){

}

void TrainerProgressMeter::Init(RndDir* progressMeter, int numSections){
    MILO_ASSERT(progressMeter, 0x1F);
    MILO_ASSERT(numSections > 0 && numSections <= 40, 0x20);
    mProgressMeter = progressMeter;
    mBar = mProgressMeter->Find<RndMesh>("progress_bar_fillchunk01.mesh", true);
    mBar->SetShowing(false);
    mGlow = mProgressMeter->Find<RndMesh>("progress_bar_glowchunk01.mesh", true);
    mGlow->SetShowing(false);
    mBoxes = mProgressMeter->Find<RndMesh>("progress_bar_boxes.mesh", true);
    mBoxes->SetShowing(false);
    mCompleted.resize(numSections);
    for(int i = 0; i < numSections; i++){
        mCompleted[i] = false;
    }
    RndPropAnim* anim = mProgressMeter->Find<RndPropAnim>("progress_meter_config.anim", true);
    if(anim) anim->SetFrame(numSections - 1, 1.0f);
    mBarTrans = mBar->WorldXfm();
    mGlowTrans = mGlow->WorldXfm();
}