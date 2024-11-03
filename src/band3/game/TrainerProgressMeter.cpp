#include "game/TrainerProgressMeter.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include "rndobj/Dir.h"
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

void TrainerProgressMeter::SetCompleted(int section, bool completed){
    MILO_ASSERT(section >= 0 && section < mCompleted.size(), 0x3C);
    mCompleted[section] = completed;
}

void TrainerProgressMeter::SetCurrent(int section){
    MILO_ASSERT(section < mCompleted.size(), 0x48);
    mCurrent = section;
}

void TrainerProgressMeter::Draw(){
    if(mProgressMeter){
        mProgressMeter->SetShowing(true);
        mProgressMeter->Find<RndMesh>("progress_bar_fillchunk01.mesh", true);
        float f = 170.0f / (float)mCompleted.size();
        mBar->SetShowing(true);
        for(int i = 0; i < mCompleted.size(); i++){
            if(mCompleted[i]){
                Transform xfm(mBarTrans);
                xfm.v.x = f * 0.5f + (float)i * f + (xfm.v.x - 85.0f);
                mBar->SetWorldXfm(xfm);
                mBar->Draw();
            }
        }
        mBar->SetShowing(false);
        mBoxes->SetShowing(true);
        mBoxes->Draw();
        mBoxes->SetShowing(false);
        if(mCurrent >= 0){
            mGlow->SetShowing(true);
            Transform xfm(mGlowTrans);
            xfm.v.x = f * 0.5f + (float)mCurrent * f + (xfm.v.x - 85.0f);
            mGlow->SetWorldXfm(xfm);
            mGlow->Draw();
            mGlow->SetShowing(false);
        }
    }
}

void TrainerProgressMeter::Hide(){
    mProgressMeter->SetShowing(false);
}