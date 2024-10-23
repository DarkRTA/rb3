#include "game/Defines.h"
#include "meta_band/Calibration.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "rndobj/TransAnim.h"
#include "synth/Synth.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include <cmath>

float CalibrationPanel::kAnimPerceptualOffset = 0;

namespace {
    ControllerType GetControllerType(){

    }
}

CalibrationPanel::CalibrationPanel() : mCycleTimeMs(755.0f), mStream(0), mFader(0), unk44(0), mHalfOffAnim(0), mEnableVideo(1), mNumHits(32), unk5c(0), mTestState(tsIdle), unk64(0), mHardwareMode(0),
    mAnimCycleFrames(50.0f), mAnimNumCycles(1), mMaxSlack(100), mRestingFrame(0), unk80(0), mVolDb(-6.0f), unk8c(0.275f), unka0(0), unkcc(0), unkd0(0), unkd4(0), unkd8(0),
    unkdc(0), unke4(0), mTopOutliers(3), mBottomOutliers(3) {

}

CalibrationPanel::~CalibrationPanel(){
    RELEASE(mStream);
    RELEASE(mFader);
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

void CalibrationPanel::UpdateProgress(bool b){
    RndTransAnim* tabanim = mDir->Find<RndTransAnim>("prog_bar_tab.tnm", true);
    RndTransAnim* boneanim = mDir->Find<RndTransAnim>("bone_prog_bar.tnm", true);
}

void CalibrationPanel::Draw(){ UIPanel::Draw(); }

void CalibrationPanel::UpdateStream(){
    if(mStream){
        if(mStream->IsPlaying() && mTestState == tsIdle){
            mStream->Stop();
        }
        else if(mStream->IsFinished() && mTestState == tsTesting){
            mStream->Stop();
            mTestState = tsPostTest;
        }
        else if(unk44 && mStream->IsReady()){
            mStream->Play();
            unk44 = false;
        }
    }
}

DataNode CalibrationPanel::OnInitializeContent(DataArray* arr){
    memset(unka4, 0, 0x14);
    memset(unkb8, 0, 0x14);
    RndTransAnim* tabanim = mDir->Find<RndTransAnim>("prog_bar_tab.tnm", true);
    RndTransAnim* boneanim = mDir->Find<RndTransAnim>("bone_prog_bar.tnm", true);
    tabanim->SetFrame(0, 1);
    boneanim->SetFrame(0, 1);
    ControllerType ty = GetControllerType();
    switch(ty){
        case kControllerGuitar:
            mDir->Find<UILabel>("green1.lbl", true)->SetIcon('G');
            mDir->Find<UILabel>("green02.lbl", true)->SetIcon('G');
            mDir->Find<UILabel>("cal_video_instructions.lbl", true)->SetTextToken(cal_video_desc_guitar);
            mDir->Find<UILabel>("cal_audio_instructions.lbl", true)->SetTextToken(cal_audio_desc_guitar);
            break;
        case kControllerDrum:
            mDir->Find<UILabel>("green1.lbl", true)->SetIcon('1');
            mDir->Find<UILabel>("green02.lbl", true)->SetIcon('1');
            mDir->Find<UILabel>("cal_video_instructions.lbl", true)->SetTextToken(cal_video_desc_drum);
            mDir->Find<UILabel>("cal_audio_instructions.lbl", true)->SetTextToken(cal_audio_desc_drum);
            break;
        default:
            mDir->Find<UILabel>("green1.lbl", true)->SetIcon('A');
            mDir->Find<UILabel>("green02.lbl", true)->SetIcon('A');
            mDir->Find<UILabel>("cal_video_instructions.lbl", true)->SetTextToken(cal_video_desc_pad);
            mDir->Find<UILabel>("cal_audio_instructions.lbl", true)->SetTextToken(cal_audio_desc_pad);
            break;
    }
    if(mHardwareMode){
        mDir->Find<UILabel>("audio_title.lbl", true)->SetTextToken(cal_hw_audio_title);
        mDir->Find<UILabel>("video_title.lbl", true)->SetTextToken(cal_hw_video_title);
        mDir->Find<UILabel>("cal_video_instructions.lbl", true)->SetTextToken(cal_video_desc_calbert);
        mDir->Find<UILabel>("cal_audio_instructions.lbl", true)->SetTextToken(cal_audio_desc_calbert);
        mDir->Find<RndGroup>("cal_hardware_video_illustration.grp", true)->SetShowing(mEnableVideo);
        mDir->Find<RndGroup>("cal_hardware_audio_illustration.grp", true)->SetShowing(!mEnableVideo);
    }
    else {
        mDir->Find<UILabel>("audio_title.lbl", true)->SetTextToken(cal_audio_title);
        mDir->Find<UILabel>("video_title.lbl", true)->SetTextToken(cal_video_title);
        mDir->Find<RndGroup>("cal_hardware_video_illustration.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("cal_hardware_audio_illustration.grp", true)->SetShowing(false);
    }
    unka0 = ty == 1 ? 0 : -1;
    SetTestState(tsIdle);
    if(mStream) RELEASE(mStream);
    if(mFader) RELEASE(mFader);
    const char* sound = "sfx/streams/sync_clap";
    if(mHardwareMode) sound = "sfx/streams/sync_beep";
    mFader = Hmx::Object::New<Fader>();
    mStream = TheSynth->NewStream(sound, 0, 2.0f, false);
    MILO_ASSERT(mStream, 0x205);
    if(mStream){
        mStream->SetVolume(mVolDb);
        mFader->SetVal(-96.0f);
        mStream->mFaders->Add(mFader);
    }
    InitializeVisuals();
    return 0;
}

void CalibrationPanel::StartAudio(){
    mStream->SetVolume(mVolDb);
    if(mStream->GetFilePos() > 0){
        mStream->Resync(0);
    }
    if(mStream->IsReady()){
        mStream->Play();
    }
    else unk44 = true;
}

void CalibrationPanel::StopAudio(){
    unk44 = false;
    if(mStream){
        mFader->DoFade(-96.0f, 200.0f);
    }
}

DataNode CalibrationPanel::OnStartTest(DataArray* arr){
    static DataNode& cal_num_hits = DataVariable("cal_num_hits");
    if(cal_num_hits.Int() != 0) mNumHits = cal_num_hits.Int();
    static DataNode& cal_num_outliers = DataVariable("cal_num_outliers");
    if(cal_num_outliers.Int() != 0){
        int outliers = cal_num_outliers.Int();
        mBottomOutliers = outliers;
        mTopOutliers = outliers;
    }
    unkd8 = 0;
    unkdc = 0;
    unkd4 = 0;
    unke4 = 0;
    mPad = arr->Obj<User>(2)->GetLocalUser()->GetPadNum();
    PrepareHwCalibrationState();
    StartAudio();
    unkd0 = -1.0f;
    unk48.clear();
    SetTestState(tsPreRoll);
    int u4 = 10;
    if(mHardwareMode) u4 = 40;
    unk90 = u4;
    unk64 = 0;
    unk5c = mCycleTimeMs / 2.0f;
    if(mEnableVideo){
        mDir->Find<RndGroup>("visuals_anim.grp", true)->Animate(0, false, 0);
    }
    if(mEnableAudio){
        mDir->Find<RndGroup>("audio_anim.grp", true)->Animate(0, false, 0);
        unke0 = false;
    }
    return 0;
}

void CalibrationPanel::PrepareHwCalibrationState(){
    if(mHardwareMode){
        unkcc = true;
        if(mEnableVideo){
            JoypadSetCalbertMode(mPad, 1);
        }
        else {
            JoypadSetCalbertMode(mPad, 2);
        }
    }
}

void CalibrationPanel::TerminateHwCalibrationState(){
    if(unkcc){
        JoypadSetCalbertMode(mPad, 0);
        unkcc = false;
    }
}

void CalibrationPanel::InitializeVisuals(){
    mDir->Find<RndGroup>("cal_visuals.grp", true)->SetShowing(mEnableVideo);
    mDir->Find<RndGroup>("cal_audio.grp", true)->SetShowing(mEnableAudio);
    mDir->Find<RndGroup>("prog_bar.grp", true)->SetShowing(false);
    if(mHardwareMode){
        mDir->Find<RndGroup>("cal_metronome.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("visuals_anim.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("audio_anim.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("cal_hardware.grp", true)->SetShowing(false);
        unk88 = 0;
    }
    else {
        mDir->Find<RndGroup>("cal_metronome.grp", true)->SetShowing(true);
        mDir->Find<RndGroup>("cal_hardware.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("visuals_anim.grp", true)->SetShowing(false);
        mDir->Find<RndGroup>("audio_anim.grp", true)->SetShowing(false);
        if(mEnableVideo){
            mDir->Find<RndGroup>("visuals_anim.grp", true)->SetShowing(true);
            mDir->Find<RndGroup>("visuals_anim.grp", true)->StopAnimation();
            mDir->Find<RndGroup>("visuals_anim.grp", true)->SetFrame(0, 1);
            mDir->Find<RndMesh>("strum.mesh", true)->SetShowing(false);
            mDir->Find<RndMesh>("drum_hit.mesh", true)->SetShowing(false);
            mDir->Find<RndMesh>("button_press_ps3.mesh", true)->SetShowing(false);
            mDir->Find<RndMesh>("button_press_xbox.mesh", true)->SetShowing(false);
            switch(GetControllerType()){
                case kControllerGuitar:
                    mDir->Find<RndMesh>("strum.mesh", true)->SetShowing(true);
                    break;
                case kControllerDrum:
                    mDir->Find<RndMesh>("drum_hit.mesh", true)->SetShowing(true);
                    break;
                default:
                    mDir->Find<RndMesh>("button_press_ps3.mesh", true)->SetShowing(true);
                    break;
            }
        }
        if(mEnableAudio){
            mDir->Find<RndGroup>("audio_anim.grp", true)->SetShowing(true);
            mDir->Find<RndGroup>("audio_anim.grp", true)->StopAnimation();
            mDir->Find<RndGroup>("audio_anim.grp", true)->SetFrame(0, 1);
        }
        const char* str = "cal_visuals.grp";
        mDir->Find<RndGroup>(str, true)->SetFrame(mRestingFrame, 1);
    }
}

void CalibrationPanel::EndTest(){
    MILO_LOG("-----------------------------\n");
    MILO_LOG("Pre Sort Calibration samples:\n");
    for(int i = 0; i < unk48.size(); i++){
        MILO_LOG("%f ms\n", unk48[i]);
    }
    std::sort(unk48.begin(), unk48.end());
    MILO_LOG("------------------------------------------\n");
    MILO_LOG("Sorted Calibration samples, not truncated:\n");
    for(int i = 0; i < unk48.size(); i++){
        MILO_LOG("%f ms\n", unk48[i]);
    }
    SetTestState(tsPostTest);
    mFader->DoFade(-96.0f, 1000.0f);
    unk80 = GetAudioTimeMs();
}