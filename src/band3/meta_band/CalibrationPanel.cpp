#include "meta_band/Calibration.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "rndobj/Group.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Symbols3.h"
#include <cmath>

float CalibrationPanel::kAnimPerceptualOffset = 0;

CalibrationPanel::CalibrationPanel() : mCycleTimeMs(755.0f), unk3c(0), mFader(0), unk44(0), mHalfOffAnim(0), mEnableVideo(1), mNumHits(32), unk5c(0), mTestState(tsIdle), unk64(0), mHardwareMode(0),
    mAnimCycleFrames(50.0f), mAnimNumCycles(1), mMaxSlack(100), mRestingFrame(0), unk80(0), mVolDb(-6.0f), unk8c(0.275f), unka0(0), unkcc(0), unkd0(0), unkd4(0), unkd8(0),
    unkdc(0), unke4(0), mTopOutliers(3), mBottomOutliers(3) {

}

CalibrationPanel::~CalibrationPanel(){
    // RELEASE(unk3c);
    // RELEASE(mFader);
}

void CalibrationPanel::Poll(){
    if(mTestState == tsPostTest){
        float ms = GetAudioTimeMs();
        if(ms - unk80 > mCycleTimeMs * 1.1f){
            SetTestState(tsIdle);
            StopAudio();
        }
    }
    UpdateAnimation();
    UpdateLabel();
    UpdateStream();
    if(GetTestRep() >= unk90 && mTestState == tsTesting){
        SetTestState(tsIdle);
    }
    if(mHardwareMode){
        ScanHardwareModeInputs();
    }
    // InputMgr stuff
    if(ThePlatformMgr.mGuideShowing){
        SetTestState(tsIdle);
    }
    UIPanel::Poll();
}

void CalibrationPanel::UpdateAnimation(){
    if(mTestState != tsIdle){
        if(mHardwareMode){
            if(mTestState == tsPreRoll){
                if(mEnableAudio){
                    mFader->DoFade(0, mCycleTimeMs / 2.0f);
                }
                SetTestState(tsTesting);
                unk7c = 1;
                unk7c = GetTestRep();
            }
            float f1 = mCycleTimeMs;
            float f10 = GetAudioTimeMs();
            f10 = std::fmod(mCycleTimeMs / 2.0f + f10, f1);
            RndGroup* hwgrp = mDir->Find<RndGroup>("cal_hardware.grp", true);
            if(f10 > mCycleTimeMs / 2.0){
                hwgrp->SetShowing(unk88);
                if(unk88 < 0) unk88 = 0;
                unk88--;
            }
            else {
                unk88 = 9;
                hwgrp->SetShowing(false);
            }
        }
        else {
            float f1 = mCycleTimeMs;
            float f10 = GetAudioTimeMs();
            f10 = std::fmod(mCycleTimeMs / 2.0f + f10, f1);
            f10 = ReshapeTime(f10);
            f10 = (f10 * mAnimCycleFrames) / mCycleTimeMs;
            MILO_ASSERT(mAnimNumCycles == 1 || mAnimNumCycles == 2, 0xBE);
            if(mAnimNumCycles == 2 && GetTestRep()){
                f10 = f10 + mAnimCycleFrames;
            }
            if(mHalfOffAnim){
                f10 = mAnimCycleFrames / 2.0f + f10;
            }
            f10 = std::fmod(f10, mAnimCycleFrames * (float)mAnimNumCycles);
            float frame = HandlePreAndPostTestAnim(f10);
            mDir->Find<RndGroup>("cal_visuals.grp", true)->SetFrame(frame, 1.0f);
        }
    }
    else if(mHardwareMode){
        mDir->Find<RndGroup>("cal_hardware.grp", true)->SetShowing(false);
    }
}

float CalibrationPanel::HandlePreAndPostTestAnim(float f){
    float ftouse = f;
    if(mTestState == tsPreRoll){
        bool b6;
        if(mRestingFrame == 0){
            b6 = f < unk64;
        }
        else {
            b6 = false;
            if(f >= mRestingFrame && unk64 <= mRestingFrame) b6 = true;
        }
        if(b6){
            if(mEnableAudio){
                mFader->DoFade(0, mCycleTimeMs / 2.0f);
            }
            SetTestState(tsTesting);
            unk7c = 1;
            unk7c = GetTestRep();
        }
        else {
            unk64 = f;
            return mRestingFrame;
        }
    }
    else if(mTestState == tsPostTest){
        for(int i = 0; i < mAnimNumCycles; i++){
            ftouse = mAnimCycleFrames * (float)i + mRestingFrame;
            bool b6;
            if(ftouse == 0){
                b6 = f < unk64;
            }
            else {
                b6 = false;
                if(f >= ftouse && unk64 <= ftouse) b6 = true;
            }
            if(b6 || (unk64 == ftouse)) break;
            ftouse = f;
        }
    }
    unk64 = ftouse;
    return ftouse;
}

void CalibrationPanel::UpdateLabel(){
    UILabel* countdownlabel = mDir->Find<UILabel>("cal_countdown.lbl", true);
    UILabel* repslabel = mDir->Find<UILabel>("cal_reps.lbl", true);
    RndGroup* progbargrp = mDir->Find<RndGroup>("prog_bar.grp", true);
    RndGroup* calvidlabelsgrp = mDir->Find<RndGroup>("cal_video_labels.grp", true);
    RndGroup* calhwvidgrp = mDir->Find<RndGroup>("cal_hardware_video_illustration.grp", true);
    RndGroup* calhwaudgrp = mDir->Find<RndGroup>("cal_hardware_audio_illustration.grp", true);
    RndGroup* calhwdarkgrp = mDir->Find<RndGroup>("cal_hardware_darkness.grp", true);
    if(mTestState == tsTesting){
        if(mHardwareMode){
            progbargrp->SetShowing(true);
            calhwaudgrp->SetShowing(false);
            calhwvidgrp->SetShowing(false);
            countdownlabel->SetTextToken(gNullStr);
            repslabel->SetTextToken(gNullStr);
            UpdateProgress(false);
            calvidlabelsgrp->SetShowing(false);
            calhwdarkgrp->SetShowing(true);
        }
        else {
            calhwdarkgrp->SetShowing(false);
            calvidlabelsgrp->SetShowing(true);
            float f14 = std::fmod(GetAudioTimeMs(), mCycleTimeMs);
            int i48 = GetAudioTimeMs() / mCycleTimeMs;
            if(i48 - unk7c >= 5){
                progbargrp->SetShowing(true);
                repslabel->SetInt(mNumHits - unk48.size(), false);
                repslabel->SetShowing(false);
                countdownlabel->SetTextToken(gNullStr);
                UpdateProgress(true);
            }
            else {
                progbargrp->SetShowing(false);
                if(unk5c > f14){
                    if(GetTestRep() - 4 == 0){
                        countdownlabel->SetTextToken(lag_go);
                    }
                    else {
                        countdownlabel->SetInt(4 - GetTestRep(), false);
                    }
                    repslabel->SetTextToken(gNullStr);
                }
                unk5c = f14;
            }
        }
    }
    else {
        calhwdarkgrp->SetShowing(false);
        calvidlabelsgrp->SetShowing(true);
        countdownlabel->SetTextToken(gNullStr);
        repslabel->SetTextToken(gNullStr);
        progbargrp->SetShowing(false);
        if(mHardwareMode){
            if(mEnableVideo) calhwvidgrp->SetShowing(true);
            else calhwaudgrp->SetShowing(true);
        }
    }
}