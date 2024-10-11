#include "bandobj/VocalTrackDir.h"
#include "bandobj/TrackInterface.h"
#include "obj/ObjVersion.h"
#include "obj/DataFunc.h"
#include "rndobj/Rnd.h"
#include "utl/ClassSymbols.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(VocalTrackDir)

VocalTrackDir::VocalTrackDir() : BandTrack(this), mHiddenPartAlpha(0.3f), unk2a4(1), unk2a5(1), mIsTop(1), unk2a7(0), mFeedbackStateLead(0), mFeedbackStateHarm1(0), mFeedbackStateHarm2(0),
    mVocalMics(this, 0), unk2f0(this, 0), mMinPitchRange(12.0f), mPitchDisplayMargin(3.0f), mArrowSmoothing(0.85f), mConfigurableObjects(this, kObjListNoNull), mVoxCfg(this, 0),
    mTambourineSmasher(this, 0), mTambourineNowShowTrig(this, 0), mTambourineNowHideTrig(this, 0), mLeadPhraseFeedbackBottomLbl(this, 0), mPhraseFeedbackTrig(this, 0),
    mSpotlightSparklesOnlyTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mPitchArrow1(this, 0), mPitchArrow2(this, 0), mPitchArrow3(this, 0), mPitchWindow(1),
    mPitchWindowHeight(2.5f), mPitchWindowMesh(this, 0), mPitchWindowOverlay(this, 0), mLeadLyrics(1), mLeadLyricHeight(0.4f), mLeadLyricMesh(this, 0), mHarmLyrics(1),
    mHarmLyricHeight(0.4f), mHarmLyricMesh(this, 0), mLeftDecoMesh(this, 0), mRightDecoMesh(this, 0), mNowBarWidth(0.2f), mNowBarMesh(this, 0), mRemoteVocals(0),
    mTrackLeftX(-20.0f), mTrackRightX(20.0f), mTrackBottomZ(0.0f), mTrackTopZ(10.0f), mPitchBottomZ(0.0f), mPitchTopZ(2.0f), mNowBarX(-10.0f), unk42c(0), mPitchGuides("harmonic"),
    mTubeStyle(this, 0), mArrowStyle(this, 0), mFontStyle(this, 0), mLeadText(this, 0), mHarmText(this, 0), mLeadPhonemeText(this, 0), mHarmPhonemeText(this, 0),
    mLastMin(36.0f), mLastMax(84.0f), mMiddleCZPos(0), mTonic(0x3c), mRangeScaleAnim(this, 0), mRangeOffsetAnim(this, 0), unk4b0(1), unk4b4(2), mLeftTrans(0), mRightTrans(0),
    mBottomTrans(0), mTopTrans(0), mPitchBottomTrans(0), mPitchTopTrans(0), mPitchMidTrans(0), mNowTrans(0), mTubeRangeGrp(this, 0), mTubeSpotlightGrp(this, 0),
    mTubeBack0Grp(this, 0), mTubeBack1Grp(this, 0), mTubeBack2Grp(this, 0), mTubeFront0Grp(this, 0), mTubeFront1Grp(this, 0), mTubeFront2Grp(this, 0), mTubeGlow0Grp(this, 0),
    mTubeGlow1Grp(this, 0), mTubeGlow2Grp(this, 0), mTubePhoneme0Grp(this, 0), mTubePhoneme1Grp(this, 0), mTubePhoneme2Grp(this, 0), mSpotlightMat(this, 0), mLeadBackMat(this, 0),
    mHarm1BackMat(this, 0), mHarm2BackMat(this, 0), mLeadFrontMat(this, 0), mHarm1FrontMat(this, 0), mHarm2FrontMat(this, 0), mLeadGlowMat(this, 0), mHarm1GlowMat(this, 0), mHarm2GlowMat(this, 0), mLeadPhonemeMat(this, 0), mHarm1PhonemeMat(this, 0),
    mHarm2PhonemeMat(this, 0), mVocalsGrp(this, 0), mScroller(this, 0), mLeadLyricScroller(this, 0), mHarmonyLyricScroller(this, 0), mBREGrp(this, 0), mLeadBREGrp(this, 0),
    mHarmonyBREGrp(this, 0), mPitchScrollGroup(this, 0), mLeadLyricScrollGroup(this, 0), mHarmonyLyricScrollGroup(this, 0), unk694(0), unk698(0), unk69c(0), unk6a0(0),
    mLeadDeployMat(this, 0), mHarmDeployMat(this, 0), mGlowSize(-1.0f), mGlowAlpha(0.3f), unk6c4(-1), unk6c8(0), mArrowFXDrawGrp(this, 0), unk6d8(18.0f), unk6dc(48.0f), unk6e0(0) {

}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(VocalTrackDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(VocalTrackDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(unk2a4)
        COPY_MEMBER(mIsTop)
        COPY_MEMBER(unk2f0)
        COPY_MEMBER(mMinPitchRange)
        COPY_MEMBER(mArrowSmoothing)
        COPY_MEMBER(mConfigurableObjects)
        COPY_MEMBER(mVoxCfg)
        COPY_MEMBER(mTambourineSmasher)
        COPY_MEMBER(mTambourineNowShowTrig)
        COPY_MEMBER(mTambourineNowHideTrig)
        COPY_MEMBER(mPhraseFeedbackTrig)
        COPY_MEMBER(mSpotlightSparklesOnlyTrig)
        COPY_MEMBER(mSpotlightPhraseSuccessTrig)
        COPY_MEMBER(mLyricColorMap)
        COPY_MEMBER(mLyricAlphaMap)
        COPY_MEMBER(mPitchWindow)
        COPY_MEMBER(mPitchWindowHeight)
        COPY_MEMBER(mPitchWindowMesh)
        COPY_MEMBER(mPitchWindowOverlay)
        COPY_MEMBER(mLeadLyrics)
        COPY_MEMBER(mLeadLyricHeight)
        COPY_MEMBER(mLeadLyricMesh)
        COPY_MEMBER(mHarmLyrics)
        COPY_MEMBER(mHarmLyricHeight)
        COPY_MEMBER(mHarmLyricMesh)
        COPY_MEMBER(mLeftDecoMesh)
        COPY_MEMBER(mRightDecoMesh)
        COPY_MEMBER(mNowBarWidth)
        COPY_MEMBER(mNowBarMesh)
        COPY_MEMBER(mRemoteVocals)
        COPY_MEMBER(mTrackLeftX)
        COPY_MEMBER(mTrackRightX)
        COPY_MEMBER(mTrackBottomZ)
        COPY_MEMBER(mTrackTopZ)
        COPY_MEMBER(mPitchBottomZ)
        COPY_MEMBER(mPitchTopZ)
        COPY_MEMBER(mNowBarX)
        COPY_MEMBER(mPitchGuides)
        COPY_MEMBER(mTubeStyle)
        COPY_MEMBER(mArrowStyle)
        COPY_MEMBER(mFontStyle)
        COPY_MEMBER(mLeadText)
        COPY_MEMBER(mHarmText)
        COPY_MEMBER(mLeadPhonemeText)
        COPY_MEMBER(mHarmPhonemeText)
        COPY_MEMBER(mLastMin)
        COPY_MEMBER(mLastMax)
        COPY_MEMBER(mMiddleCZPos)
        COPY_MEMBER(mTonic)
        COPY_MEMBER(mRangeScaleAnim)
        COPY_MEMBER(mRangeOffsetAnim)
        COPY_MEMBER(mTubeRangeGrp)
        COPY_MEMBER(mTubeSpotlightGrp)
        COPY_MEMBER(mTubeBack0Grp)
        COPY_MEMBER(mTubeBack1Grp)
        COPY_MEMBER(mTubeBack2Grp)
        COPY_MEMBER(mTubeFront0Grp)
        COPY_MEMBER(mTubeFront1Grp)
        COPY_MEMBER(mTubeFront2Grp)
        COPY_MEMBER(mTubeGlow0Grp)
        COPY_MEMBER(mTubeGlow1Grp)
        COPY_MEMBER(mTubeGlow2Grp)
        COPY_MEMBER(mTubePhoneme0Grp)
        COPY_MEMBER(mTubePhoneme1Grp)
        COPY_MEMBER(mTubePhoneme2Grp)
        COPY_MEMBER(mSpotlightMat)
        COPY_MEMBER(mLeadBackMat)
        COPY_MEMBER(mHarm1BackMat)
        COPY_MEMBER(mHarm2BackMat)
        COPY_MEMBER(mLeadFrontMat)
        COPY_MEMBER(mHarm1FrontMat)
        COPY_MEMBER(mHarm2FrontMat)
        COPY_MEMBER(mLeadGlowMat)
        COPY_MEMBER(mHarm1GlowMat)
        COPY_MEMBER(mHarm2GlowMat)
        COPY_MEMBER(mLeadPhonemeMat)
        COPY_MEMBER(mHarm1PhonemeMat)
        COPY_MEMBER(mHarm2PhonemeMat)
        COPY_MEMBER(mLeadDeployMat)
        COPY_MEMBER(mHarmDeployMat)
        CopyTrack(c);
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

SAVE_OBJ(VocalTrackDir, 0x107)

BEGIN_LOADS(VocalTrackDir)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void VocalTrackDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(7, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

const char* TypeToString(DataType ty){
    switch(ty){
        case kDataInt: return Int.Str();
        case kDataFloat: return Float.Str();
        case kDataVar: return Var.Str();
        case kDataFunc: return Func.Str();
        case kDataObject: return Object.Str();
        case kDataSymbol: return Sym.Str();
        case kDataUnhandled: return Unhandled.Str();
        case kDataArray: return Array.Str();
        case kDataCommand: return Command.Str();
        case kDataString: return String.Str();
        case kDataProperty: return Property.Str();
        case kDataGlob: return Glob.Str();
        default: return UNEXPECTED.Str();
    }
}

const char* DataToString(const DataNode& node){
    switch(node.Type()){
        case kDataInt: return MakeString("%d", node.Int());
        case kDataFloat: return MakeString("%f", node.Float());
        case kDataVar: return MakeString("%s", DataVarName(node.Var()));
        case kDataFunc: return MakeString("%s", DataFuncName(node.Func()));
        case kDataObject:
            if(node.NotNull()) return MakeString("%s", node.GetObj()->Name());
            else return MakeString("<null>");
        case kDataSymbol: return node.Sym().Str();
        case kDataArray: return MakeString("<array>");
        case kDataCommand: return MakeString("<command>");
        case kDataString: return node.Str();
        case kDataProperty: return MakeString("<property>");
        case kDataGlob: return MakeString("<glob>");
        default: return MakeString("unhandled");
    }
}

#pragma push
#pragma dont_inline on
void VocalTrackDir::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(!IsProxy()){
        bool ba9, baa, bab, bac;
        float f88;
        int i8c;
        if(gRev < 2){
            MILO_NOTIFY_ONCE("VocalTrackDir class has changed significantly since this file was last saved.  Many parameters will need to be updated.");
            Hmx::Color col;
            std::vector<Hmx::Color> cols;
            ObjPtr<Hmx::Object, ObjectDir> objectPtr(this, 0);
            std::vector<float> floats;
            bs >> i8c; bs >> i8c; bs >> f88; bs >> i8c;
            bs >> mConfigurableObjects;
            bs >> mLyricColorMap[5];
            bs >> mLyricColorMap[6];
            bs >> mLyricColorMap[7];
            bs >> mLyricColorMap[0x15];
            bs >> mLyricColorMap[0x16];
            bs >> mLyricColorMap[0x17];
            bs >> mLyricColorMap[0xC];
            bs >> mLyricColorMap[0xD];
            bs >> mLyricColorMap[0xE];
            bs >> mLyricColorMap[0xF];
            bs >> mLyricColorMap[0x1C];
            bs >> mLyricColorMap[0x1D];
            bs >> mLyricColorMap[0x1E];
            bs >> mLyricColorMap[0x1F];
            bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            bs >> col; bs >> col;
            bs >> f88; bs >> f88;
            if(gRev >= 1){ bs >> f88; bs >> f88; }
            bs >> f88;
            bs >> unk2f0;
            bs >> ba9;
            bs >> mMinPitchRange;
            bs >> mArrowSmoothing;
            bs >> f88; bs >> f88;
            bs >> cols;
            bs >> floats;
            bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            bs >> mPhraseFeedbackTrig;
            bs >> mSpotlightSparklesOnlyTrig;
            bs >> mSpotlightPhraseSuccessTrig;
            bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            if(Type() == vocal_harmony_prototype){
                MILO_LOG("** Converting prototype to C (%d props)\n", mTypeProps.Size());
                for(int i = 0; i < mTypeProps.Size(); i++){
                    if(Property(mTypeProps.Key(i), true)->Type() == mTypeProps.Value(i).Type()){
                        MILO_LOG("\tSetting property %s to %s\n", mTypeProps.Key(i).Str(), DataToString(mTypeProps.Value(i)));
                        SetProperty(mTypeProps.Key(i), mTypeProps.Value(i));
                    }
                    else {
                        MILO_LOG("\tMismatched types for property %s: %s v. %s\n", mTypeProps.Key(i).Str(),
                            TypeToString(Property(mTypeProps.Key(i), true)->Type()), TypeToString(mTypeProps.Value(i).Type()));
                    }
                }
                MILO_LOG("**\n\n");
            }
        }
        else {
            bs >> mConfigurableObjects;
            bs >> mVoxCfg;
            if(!TheLoadMgr.EditMode()) mVoxCfg = 0;
            bs >> unk2f0;
            bs >> mMinPitchRange;
            bs >> mArrowSmoothing;
            if(gRev < 3) bs >> f88;
            if(gRev < 7) bs >> f88;
            if(gRev < 3){
                std::vector<Hmx::Color> cols;
                ObjPtr<Hmx::Object, ObjectDir> objectPtr(this, 0);
                bs >> cols;
                bs >> objectPtr; bs >> objectPtr; bs >> objectPtr; bs >> objectPtr;
            }
            else if(gRev >= 6){
                bs >> mTambourineSmasher;
                bs >> mTambourineNowShowTrig;
                bs >> mTambourineNowHideTrig;
            }
            bs >> mPhraseFeedbackTrig;
            bs >> mSpotlightSparklesOnlyTrig;
            bs >> mSpotlightPhraseSuccessTrig;
            bs >> mLyricColorMap;
            bs >> mLyricAlphaMap;
            if(gRev < 5){
                ObjPtr<StreakMeter, ObjectDir> streakPtr(this, 0);
                bs >> streakPtr; bs >> streakPtr;
            }
            bs >> mPitchWindow;
            bs >> mPitchWindowHeight;
            bs >> mPitchWindowMesh;
            bs >> mPitchWindowOverlay;
            bs >> mLeadLyrics;
            bs >> mLeadLyricHeight;
            bs >> mLeadLyricMesh;
            bs >> mHarmLyrics;
            bs >> mHarmLyricHeight;
            bs >> mHarmLyricMesh;
            if(gRev < 3){
                Symbol s;
                bs >> s; bs >> s; bs >> s;
                bs >> f88;
                bs >> baa;
            }
            bs >> mLeftDecoMesh;
            bs >> mRightDecoMesh;
            bs >> mNowBarWidth;
            if(gRev < 3) bs >> bab;
            bs >> mNowBarMesh;
            bs >> mRemoteVocals;
            bs >> mTrackLeftX;
            bs >> mTrackRightX;
            bs >> mTrackBottomZ;
            bs >> mTrackTopZ;
            bs >> mPitchBottomZ;
            bs >> mPitchTopZ;
            bs >> mNowBarX;
            bs >> mPitchGuides;
            bs >> mTubeStyle;
            bs >> mArrowStyle;
            bs >> mFontStyle;
            bs >> mLeadText;
            bs >> mHarmText;
            if(gRev >= 4){
                bs >> mLeadPhonemeText;
                bs >> mHarmPhonemeText;
            }
            bs >> mLastMin;
            bs >> mLastMax;
            bs >> mMiddleCZPos;
            bs >> mTonic;
            if(gRev < 3){
                ObjPtr<Hmx::Object, ObjectDir> objectPtr(this, 0);
                bs >> objectPtr;
                bs >> bac; bs >> bac;
            }
            bs >> mRangeScaleAnim;
            bs >> mRangeOffsetAnim;
            if(gRev >= 4){
                bs >> mLeadDeployMat;
                bs >> mHarmDeployMat;
            }
        }
    }
    LoadTrack(bs, IsProxy(), gLoadingProxyFromDisk, true);
}
#pragma pop

void VocalTrackDir::SetConfiguration(Hmx::Object* o, HarmonyShowingState state){
    if(o != mVoxCfg || state != unk4b4){
        mVoxCfg = o;
        unk4b4 = state;
        mRemoteVocals = mVoxCfg->Property(remote, true)->Int();
        unk4b0 = mVoxCfg->Property(align, true)->Sym() == top;
        if(unk2a7 && mPlayerIntro){
            mPlayerIntro->SetLocalPos(Find<RndTransformable>("h2h_player_intro_trans.grp", true)->mLocalXfm.v);
        }
        ConfigPanels();
        if(BandTrack::mParent) BandTrack::mParent->RebuildVocalHUD();
        SetRange(mLastMin, mLastMax, mTonic, true);
    }
}

void VocalTrackDir::UpdateConfiguration(){
    bool widescreen = TheRnd->GetAspect() == Rnd::kWidescreen;
    bool b8 = false;
    if(BandTrack::mParent && BandTrack::mParent->HasNetPlayer()) b8 = true;
    b8 |= mSimulatedNet;
    Hmx::Object* voxobj = FindObject(MakeString("%s%s%s",
        b8 ? "vocals_remote" : "vocals",
        mIsTop ? "_top" : "_bottom",
        widescreen ? "_wide" : ""), false);
    bool b9 = false;
    if(mHarmLyrics && BandTrack::mParent && BandTrack::mParent->UseVocalHarmony()) b9 = true;
    SetConfiguration(voxobj, (HarmonyShowingState)!b9);
}

void VocalTrackDir::TrackReset(){
    SyncObjects();
    if(BandTrack::mParent){
        if(mLeadText) mLeadText->SetText("");
        if(mHarmText) mHarmText->SetText("");
        if(mLeadPhonemeText) mLeadPhonemeText->SetText("");
        if(mHarmPhonemeText) mHarmPhonemeText->SetText("");
        for(int i = 0; i < 3; i++) GetPitchArrow(i)->Clear();
    }
    if(mPlayerFeedback){
        mPlayerFeedback->Find<EventTrigger>("setup_vocal.trig", true)->Trigger();
    }
    ResetSmashers(true);
    if(!BandTrack::mParent || !BandTrack::mParent->FailedAtStart()) EnablePlayer();
    std::floor(TheTaskMgr.Beat());
    TheTaskMgr.Beat();
    unk6c8 = true;
}

void VocalTrackDir::ResetSmashers(bool b){
    mTambourineSmasher->HandleType(reset_msg);
    if(b) mTambourineSmasher->HandleType(reset_particles_msg);
}

void VocalTrackDir::PlayIntro(){
    if(!BandTrack::mParent || !BandTrack::mParent->FailedAtStart()){
        mIntroTrig->Trigger();
        mPitchArrow1->ClearParticles();
        mPitchArrow2->ClearParticles();
        mPitchArrow3->ClearParticles();
    }
    BandTrack::PlayIntro();
    if(unk6e0){
        EventTrigger* trig = Find<EventTrigger>("pitch_correction_on.trig", false);
        if(trig) trig->Trigger();
    }
}

void VocalTrackDir::Deploy(){
    BandTrack::Deploy();
    PopupHelp("deploy", false);
}

void VocalTrackDir::SetTambourine(bool b){
    if(b) mTambourineNowShowTrig->Trigger();
    else mTambourineNowHideTrig->Trigger();
    mTambourineSmasher->HandleType(reset_msg);
    mTambourineSmasher->HandleType(reset_particles_msg);
}

void VocalTrackDir::Tambourine(Symbol s){
    mTambourineSmasher->Handle(Message(s), true);
}

void VocalTrackDir::TambourineNote(){
    if(mPopupObject) mPopupObject->Handle(tambourine_note_msg, true);
}

void VocalTrackDir::SetVocalLineColors(VocalHUDColor* color){
    if(mStreakMeter){
        for(int i = 0; i < 3; i++) mStreakMeter->SetPartColor(i, color[i]);
        if(color[0] != kVocalColorInvalid){
            Find<RndPropAnim>("phoneme_color_lead.anim", true)->SetFrame(color[0], 1.0f);
        }
        if(color[1] != kVocalColorInvalid){
            Find<RndPropAnim>("phoneme_color_harm1.anim", true)->SetFrame(color[1], 1.0f);
        }
        if(color[2] != kVocalColorInvalid){
            Find<RndPropAnim>("phoneme_color_harm2.anim", true)->SetFrame(color[2], 1.0f);
        }
    }
}

DECOMP_FORCEACTIVE(VocalTrackDir, "slider.sld", "arrow_param.anim", "vocal_param.anim", "set_enabled")

void VocalTrackDir::UpdateVocalMeters(bool b1, bool b2, bool b3, bool b4){
    if(mStreakMeter){
        mStreakMeter->SetPartActive(0, b1);
        mStreakMeter->SetPartActive(1, b2);
        mStreakMeter->SetPartActive(2, b3);
        if(b4) mStreakMeter->ForceFadeInactiveParts();
    }
}

Symbol GetRating(int i){
    switch(i){
        case 0: return vox_rating_0;
        case 1: return vox_rating_1;
        case 2: return vox_rating_2;
        case 3: return vox_rating_3;
        case 4: return vox_rating_4;
        case 5: return vox_rating_5;
        case 6: return vox_rating_6;
        default: return "";
    }
}

void VocalTrackDir::SetStreakPct(float f){
    if(mStreakMeter) mStreakMeter->SetWipe(f);
}

void VocalTrackDir::SetEnableVocalsOptions(bool){}

void VocalTrackDir::ShowPhraseFeedback(int i1, int i2, int i3, bool b){
    int parts = mStreakMeter->NumActiveParts();
    if(BandTrack::mParent) parts = Min(parts, BandTrack::mParent->NumSingers());
    int i_sum = i1 == 4;
    if(i2 == 4) i_sum++;
    if(i3 == 4) i_sum++;
    if(mLeadPhraseFeedbackBottomLbl){
        if(parts > 3 && i_sum == parts)
            mLeadPhraseFeedbackBottomLbl->SetTextToken(perfect_harmony);
        else mLeadPhraseFeedbackBottomLbl->SetTextToken(GetRating(i1));
    }
    if(mStreakMeter) mStreakMeter->ShowPhraseFeedback(i1, b);
    mPhraseFeedbackTrig->Trigger();
}

void VocalTrackDir::SpotlightPhraseSuccess(){
    if(mStarPowerMeter){
        if(BandTrack::mParent && BandTrack::mParent->IsDeployingOverdrive()){
            mSpotlightSparklesOnlyTrig->Trigger();
        }
        else mSpotlightPhraseSuccessTrig->Trigger();
    }
    BandTrack::SpotlightPhraseSuccess();
}

void VocalTrackDir::ShowMicDisplay(bool b){
    mVocalMics->SetShowing(b);
}

void VocalTrackDir::SetMicDisplayLabel(Symbol s){
    mVocalMics->Find<class BandLabel>("label.lbl", true)->SetTextToken(s);
}

void VocalTrackDir::SetMissingMicsForDisplay(bool b1, bool b2, bool b3){
    bool big_b = b1 | b2 | b3;
    mVocalMics->Find<RndAnimatable>("arrow_configuration.anim", true)->SetFrame(big_b, 1.0f);
}

void VocalTrackDir::CanChat(bool show){
    Find<RndDir>("chat", true)->Find<EventTrigger>(show ? "show.trig" : "hide.trig", true)->Trigger();
}

void VocalTrackDir::SetupNetVocals(){
    if(BandTrack::mParent){
        BandTrack::mParent->Init();
        BandTrack::mParent->SetVocalStyle(1);
        UpdateConfiguration();
    }
}

void VocalTrackDir::SetPlayerLocal(float f){
    if(BandTrack::mParent && BandTrack::mParent->HasNetPlayer() || mSimulatedNet) SetupNetVocals();
    else {
        Find<RndEnviron>("track.env", true)->SetProperty(fade_max, DataNode(1));
        if(mPlayerFeedback) mPlayerFeedback->Find<RndEnviron>("environ.env", true)->SetProperty(fade_max, DataNode(1));
    }
}

DataNode VocalTrackDir::OnGetDisplayMode(DataArray* da){
    if(BandTrack::mParent){
        DataNode handled = BandTrack::mParent->Handle(da, false);
        if(handled.Type() != kDataUnhandled) return DataNode(handled);
    }
    return DataNode("invalid");
}

void VocalTrackDir::RecalculateLyricZ(bool*, bool*){

}

PitchArrow* VocalTrackDir::GetPitchArrow(int idx){
    switch(idx){
        case 0: return mPitchArrow1;
        case 1: return mPitchArrow2;
        case 2: return mPitchArrow3;
        default: return 0;
    }
}

void VocalTrackDir::Reset(){
    SyncObjects();
    BandTrack::Reset();
    UpdateConfiguration();
    if(mPitchArrow1) mPitchArrow1->Reset(mArrowFXDrawGrp);
    if(mPitchArrow2) mPitchArrow2->Reset(mArrowFXDrawGrp);
    if(mPitchArrow3) mPitchArrow3->Reset(mArrowFXDrawGrp);
    RndGroup* tubesGrp = Find<RndGroup>("tubes_milo.grp", false);
    if(tubesGrp) tubesGrp->SetShowing(false);
    if(BandTrack::mParent){
        BandTrack::mParent->RefreshPlayerHUD();
        unk6e0 = BandTrack::mParent->ShowPitchCorrectionNotice();
    }
    CanChat(false);
    SetTambourine(false);
}

void VocalTrackDir::Retract(bool b){
    BandTrack::Retract(b);
    if(b){
        mPitchArrow1->ClearParticles();
        mPitchArrow2->ClearParticles();
        mPitchArrow3->ClearParticles();
    }
}

void VocalTrackDir::SyncObjects(){
    RndDir::SyncObjects();
    if(!mLeftTrans) mLeftTrans = Find<RndTransformable>("track_left.trans", false);
    if(!mRightTrans) mRightTrans = Find<RndTransformable>("track_right.trans", false);
    if(!mBottomTrans) mBottomTrans = Find<RndTransformable>("track_bottom.trans", false);
    if(!mTopTrans) mTopTrans = Find<RndTransformable>("track_top.trans", false);
    if(!mPitchBottomTrans) mPitchBottomTrans = Find<RndTransformable>("pitch_bottom.trans", false);
    if(!mPitchTopTrans) mPitchTopTrans = Find<RndTransformable>("pitch_top.trans", false);
    if(!mPitchMidTrans) mPitchMidTrans = Find<RndTransformable>("pitch_mid.trans", false);
    if(!mNowTrans) mNowTrans = Find<RndTransformable>("now_bar.trans", false);
    if(!mPitchArrow1) mPitchArrow1 = Find<PitchArrow>("pitch_arrow_1", false);
    if(!mPitchArrow2) mPitchArrow2 = Find<PitchArrow>("pitch_arrow_2", false);
    if(!mPitchArrow3) mPitchArrow3 = Find<PitchArrow>("pitch_arrow_3", false);
    if(!mTubeRangeGrp) mTubeRangeGrp = Find<RndGroup>("tubes.grp", false);
    if(!mTubeSpotlightGrp) mTubeSpotlightGrp = Find<RndGroup>("spotlight.grp", false);
    if(!mTubeBack0Grp) mTubeBack0Grp = Find<RndGroup>("back0.grp", false);
    if(!mTubeBack1Grp) mTubeBack1Grp = Find<RndGroup>("back1.grp", false);
    if(!mTubeBack2Grp) mTubeBack2Grp = Find<RndGroup>("back2.grp", false);
    if(!mTubeFront0Grp) mTubeFront0Grp = Find<RndGroup>("front0.grp", false);
    if(!mTubeFront1Grp) mTubeFront1Grp = Find<RndGroup>("front1.grp", false);
    if(!mTubeFront2Grp) mTubeFront2Grp = Find<RndGroup>("front2.grp", false);
    if(!mTubeGlow0Grp) mTubeGlow0Grp = Find<RndGroup>("glow0.grp", false);
    if(!mTubeGlow1Grp) mTubeGlow1Grp = Find<RndGroup>("glow1.grp", false);
    if(!mTubeGlow2Grp) mTubeGlow2Grp = Find<RndGroup>("glow2.grp", false);
    if(!mTubePhoneme0Grp) mTubePhoneme0Grp = Find<RndGroup>("phoneme0.grp", false);
    if(!mTubePhoneme1Grp) mTubePhoneme1Grp = Find<RndGroup>("phoneme1.grp", false);
    if(!mTubePhoneme2Grp) mTubePhoneme2Grp = Find<RndGroup>("phoneme2.grp", false);
    if(!mVocalsGrp) mVocalsGrp = Find<RndGroup>("vocals.grp", false);
    if(!mScroller) mScroller = Find<RndTransformable>("scroller.trans", false);
    if(!mLeadLyricScroller) mLeadLyricScroller = Find<RndTransformable>("lead_lyric_scroller.trans", false);
    if(!mHarmonyLyricScroller) mHarmonyLyricScroller = Find<RndTransformable>("harmony_lyric_scroller.trans", false);
    if(!mBREGrp) mBREGrp = Find<RndGroup>("bre.grp", false);
    if(!mLeadBREGrp) mLeadBREGrp = Find<RndGroup>("lead_bre.grp", false);
    if(!mHarmonyBREGrp) mHarmonyBREGrp = Find<RndGroup>("harmony_bre.grp", false);
    if(!mPitchScrollGroup) mPitchScrollGroup = Find<RndGroup>("pitch_scroll.grp", false);
    if(!mLeadLyricScrollGroup) mLeadLyricScrollGroup = Find<RndGroup>("lead_lyric_scroll.grp", false);
    if(!mHarmonyLyricScrollGroup) mHarmonyLyricScrollGroup = Find<RndGroup>("harmony_lyric_scroll.grp", false);
    if(!mBeatAnimsGrp) mBeatAnimsGrp = Find<RndGroup>("beat_anims.grp", false);
    if(!mArrowFXDrawGrp) mArrowFXDrawGrp = Find<RndGroup>("arrow_fx_draw.grp", false);
    if(!mTambourineSmasher) mTambourineSmasher = Find<RndDir>("tambourine_smasher", false);
    if(!mTambourineNowShowTrig) mTambourineNowShowTrig = Find<EventTrigger>("tambourine_now_show.trig", false);
    if(!mTambourineNowHideTrig) mTambourineNowHideTrig = Find<EventTrigger>("tambourine_now_hide.trig", false);
    if(!mVocalMics) mVocalMics = Find<RndDir>("vocals_mics", false);
    if(!mLeadPhraseFeedbackBottomLbl) mLeadPhraseFeedbackBottomLbl = Find<class BandLabel>("lead_phrase_feedback_bottom.lbl", false);
    UpdateTubeStyle();
}

void VocalTrackDir::ConfigPanels(){
    if(mFontStyle) ApplyFontStyle(mFontStyle);
    float f8 = 0;
    if(mHarmLyrics && BandTrack::mParent){
        if(BandTrack::mParent->UseVocalHarmony()) f8 += 1.0f;
    }
    if(mRemoteVocals || !mPitchWindow) f8 += 2.0f;
    if(TheRnd->GetAspect() == Rnd::kWidescreen) f8 += 10.0f;
    Find<RndAnimatable>("config.anim", true)->SetFrame(f8, 1.0f);

    mTrackBottomZ = mBottomTrans->mLocalXfm.v.z;
    mTrackTopZ = mTopTrans->mLocalXfm.v.z;
    mNowBarX = mNowTrans->mLocalXfm.v.x;
    mPitchBottomZ = mPitchBottomTrans->mLocalXfm.v.z;
    mPitchTopZ = mPitchTopTrans->mLocalXfm.v.z;
    mTrackRightX = mRightTrans->mLocalXfm.v.x;
    mTrackLeftX = mLeftTrans->mLocalXfm.v.x;
    RndTransformable* lyrictrans = Find<RndTransformable>("static_lyric_phrase_splitter.trans", false);
    unk42c = lyrictrans ? lyrictrans->mLocalXfm.v.x : mTrackRightX;
    if(ObjectDir::sMainDir->FindObject("milo", false)){
        if(mPitchArrow1) mPitchArrow1->SetLocalPos(Vector3(0,0, mPitchTopZ * 3.0f + mPitchBottomZ * 0.25f));
        if(mPitchArrow2) mPitchArrow2->SetLocalPos(Vector3(0,0, mPitchBottomZ + mPitchTopZ * 0.5f));
        if(mPitchArrow3) mPitchArrow3->SetLocalPos(Vector3(0,0, mPitchBottomZ * 3.0f + mPitchTopZ * 0.25f));
    }
}

DECOMP_FORCEACTIVE(VocalTrackDir, "pitch_window_mat_config.anim", "massive pitch range in vocal HUD: [%.0f, %.0f], probably a bug", "spotlight.mat")

void VocalTrackDir::ApplyArrowStyle(Hmx::Object* o){
    if(o && o->Type() == arrow_style){
        if(mPitchArrow1 && o->Property(arrow_A, true)->NotNull()){
            FilePath fp(o->Property(arrow_A, true)->Str());
            mPitchArrow1->SetProxyFile(fp, false);
            mPitchArrow1->Reset(0);
        }
        if(mPitchArrow2 && o->Property(arrow_B, true)->NotNull()){
            FilePath fp(o->Property(arrow_B, true)->Str());
            mPitchArrow2->SetProxyFile(fp, false);
            mPitchArrow2->Reset(0);
        }
        if(mPitchArrow3 && o->Property(arrow_C, true)->NotNull()){
            FilePath fp(o->Property(arrow_C, true)->Str());
            mPitchArrow3->SetProxyFile(fp, false);
            mPitchArrow3->Reset(0);
        }
    }
}

void VocalTrackDir::ApplyFontStyle(Hmx::Object* o){
    Hmx::Color c20(1.0f, 1.0f, 1.0f, 1.0f);
    Hmx::Color c30(1.0f, 1.0f, 1.0f, 0.75f);
    Hmx::Color c40(1.0f, 1.0f, 1.0f, 1.0f);
    Hmx::Color c50(1.0f, 1.0f, 1.0f, 0.75f);

    if(mLeadText){
        mLeadText->SetShowing(false);
        c20 = mLeadText->mColor;
    }
    if(mHarmText){
        mHarmText->SetShowing(false);
        c30 = mHarmText->mColor;
    }
    if(mLeadPhonemeText){
        mLeadPhonemeText->SetShowing(false);
        c40 = mLeadPhonemeText->mColor;
    }
    if(mHarmPhonemeText){
        mHarmPhonemeText->SetShowing(false);
        c50 = mHarmPhonemeText->mColor;
    }

    if(o && o->Type() == font_style){
        Hmx::Object* miloObj = ObjectDir::sMainDir->FindObject("milo", false);
        bool objexists = miloObj;
        if(o->Property(lead_text, true)->NotNull()){
            mLeadText = o->Property(lead_text, true)->Obj<RndText>();
            mLeadText->SetShowing(objexists);
            mLeadText->SetColor(c20);
        }
        else mLeadText = 0;
        if(o->Property(harmony_text, true)->NotNull()){
            mHarmText = o->Property(harmony_text, true)->Obj<RndText>();
            mHarmText->SetShowing(objexists);
            mHarmText->SetColor(c30);
        }
        else mHarmText = 0;
        if(o->Property(lead_phoneme_text, true)->NotNull()){
            mLeadPhonemeText = o->Property(lead_phoneme_text, true)->Obj<RndText>();
            mLeadPhonemeText->SetShowing(objexists);
            mLeadPhonemeText->SetColor(c40);
        }
        else mLeadPhonemeText = mLeadText;
        if(o->Property(harmony_phoneme_text, true)->NotNull()){
            mHarmPhonemeText = o->Property(harmony_phoneme_text, true)->Obj<RndText>();
            mHarmPhonemeText->SetShowing(objexists);
            mHarmPhonemeText->SetColor(c50);
        }
        else mHarmPhonemeText = mHarmText;
    }
}

void VocalTrackDir::SetRange(float min, float max, int tonic, bool b){
    if((b || min != mLastMin || max != mLastMax || tonic != mTonic) && min < max && mPitchWindowMesh && mRangeScaleAnim && mRangeOffsetAnim){
        mLastMin = min;
        mLastMax = max;
    }
}

void VocalTrackDir::UpdateTubeStyle(){
    if(mTubeStyle){
        if(!mSpotlightMat) mSpotlightMat = Find<RndMat>("spotlight.mat", true);
        if(!mLeadBackMat && mTubeStyle->Property(lead_back, true)->NotNull()){
            mLeadBackMat = mTubeStyle->Property(lead_back, true)->Obj<RndMat>();
        }
        if(!mLeadFrontMat && mTubeStyle->Property(lead_front, true)->NotNull()){
            mLeadFrontMat = mTubeStyle->Property(lead_front, true)->Obj<RndMat>();
        }
        if(!mLeadGlowMat && mTubeStyle->Property(lead_glow, true)->NotNull()){
            mLeadGlowMat = mTubeStyle->Property(lead_glow, true)->Obj<RndMat>();
        }
        if(!mLeadPhonemeMat && mTubeStyle->Property(lead_phoneme, true)->NotNull()){
            mLeadPhonemeMat = mTubeStyle->Property(lead_phoneme, true)->Obj<RndMat>();
        }
        if(!mHarm1BackMat && mTubeStyle->Property(harmony_1_back, true)->NotNull()){
            mHarm1BackMat = mTubeStyle->Property(harmony_1_back, true)->Obj<RndMat>();
        }
        if(!mHarm1FrontMat && mTubeStyle->Property(harmony_1_front, true)->NotNull()){
            mHarm1FrontMat = mTubeStyle->Property(harmony_1_front, true)->Obj<RndMat>();
        }
        if(!mHarm1GlowMat && mTubeStyle->Property(harmony_1_glow, true)->NotNull()){
            mHarm1GlowMat = mTubeStyle->Property(harmony_1_glow, true)->Obj<RndMat>();
        }
        if(!mHarm1PhonemeMat && mTubeStyle->Property(harmony_1_phoneme, true)->NotNull()){
            mHarm1PhonemeMat = mTubeStyle->Property(harmony_1_phoneme, true)->Obj<RndMat>();
        }
        if(mTubeStyle->Property(same_as_harmony_1, true)->Int()){
            mHarm2BackMat = mHarm1BackMat;
            mHarm2FrontMat = mHarm1FrontMat;
            mHarm2GlowMat = mHarm1GlowMat;
            mHarm2PhonemeMat = mHarm1PhonemeMat;
        }
        else {
            if(!mHarm2BackMat && mTubeStyle->Property(harmony_2_back, true)->NotNull()){
                mHarm2BackMat = mTubeStyle->Property(harmony_2_back, true)->Obj<RndMat>();
            }
            if(!mHarm2FrontMat && mTubeStyle->Property(harmony_2_front, true)->NotNull()){
                mHarm2FrontMat = mTubeStyle->Property(harmony_2_front, true)->Obj<RndMat>();
            }
            if(!mHarm2GlowMat && mTubeStyle->Property(harmony_2_glow, true)->NotNull()){
                mHarm2GlowMat = mTubeStyle->Property(harmony_2_glow, true)->Obj<RndMat>();
            }
            if(!mHarm2PhonemeMat && mTubeStyle->Property(harmony_2_phoneme, true)->NotNull()){
                mHarm2PhonemeMat = mTubeStyle->Property(harmony_2_phoneme, true)->Obj<RndMat>();
            }
        }
        mGlowSize = mTubeStyle->Property(glow_size, true)->Float();
        mGlowAlpha = mTubeStyle->Property(glow_alpha, true)->Float();
        if(mLeadGlowMat) mLeadGlowMat->SetAlpha(mGlowAlpha);
        if(mHarm1GlowMat) mHarm1GlowMat->SetAlpha(mGlowAlpha);
        if(mHarm2GlowMat) mHarm2GlowMat->SetAlpha(mGlowAlpha);
    }
}

DataNode VocalTrackDir::OnSetLyricColor(const DataArray* da){
    Hmx::Color c20(0,0,0,da->Float(4));
    Symbol sym(da->Sym(3));
    c20.Unpack(da->Int(2));
    if(sym == lead){
        if(mLeadText) mLeadText->SetColor(Hmx::Color32(c20));
        if(mLeadPhonemeText) mLeadPhonemeText->SetColor(Hmx::Color32(c20));
    }
    else if(sym == harmony){
        if(mHarmText) mHarmText->SetColor(Hmx::Color32(c20));
        if(mHarmPhonemeText) mHarmPhonemeText->SetColor(Hmx::Color32(c20));
    }
    return DataNode(0);
}

DataNode VocalTrackDir::OnSetDisplayMode(DataArray* da){
    if(BandTrack::mParent){
        DataNode handled = BandTrack::mParent->Handle(da, false);
        if(handled.Type() != kDataUnhandled) return DataNode(handled);
    }
    return DataNode("invalid");
}

void VocalTrackDir::Extend(bool b){
    Reset();
    RndTransAnim* tnm = Find<RndTransAnim>("intro.tnm", false);
    if(tnm){
        if(b) tnm->SetFrame(tnm->EndFrame(), 1.0f);
        else tnm->Animate(tnm->StartFrame(), tnm->EndFrame(), tnm->Units(), 0, 0);
    }
}

void VocalTrackDir::RefreshCrowdRating(float f, CrowdMeterState state){
    if(state == kCrowdMeterWarning){
        unk1c = false;
        SetCrowdRating(f, state);
    }
}

void VocalTrackDir::SetPerformanceMode(bool b){
    Find<RndGroup>("main.grp", true)->SetShowing(!b);
    Find<RndGroup>("lyrics.grp", true)->SetShowing(!b);
    Find<RndGroup>("lyrics_harmony.grp", true)->SetShowing(!b);
    BandTrack::SetPerformanceMode(b);
}

void VocalTrackDir::SortArrowFx(){
    if(mArrowFXDrawGrp && (PitchArrow::NeedSort(mPitchArrow1) || PitchArrow::NeedSort(mPitchArrow2) || PitchArrow::NeedSort(mPitchArrow3))){
        mArrowFXDrawGrp->SortDraws();
    }
}

#pragma push
#pragma dont_inline on
BEGIN_PROPSYNCS(VocalTrackDir)
    SYNC_PROP(is_top, mIsTop)
    SYNC_PROP(feedback_state_lead, mFeedbackStateLead)
    SYNC_PROP(feedback_state_harm_1, mFeedbackStateHarm1)
    SYNC_PROP(feedback_state_harm_2, mFeedbackStateHarm2)
    SYNC_PROP(lead_coming, mLyricColorMap[5])
    SYNC_PROP(lead_now, mLyricColorMap[6])
    SYNC_PROP(lead_past, mLyricColorMap[7])
    SYNC_PROP(lead_od_coming, mLyricColorMap[0x15])
    SYNC_PROP(lead_od_now, mLyricColorMap[0x16])
    SYNC_PROP(lead_od_past, mLyricColorMap[0x17])
    SYNC_PROP(harmony_coming, mLyricColorMap[1])
    SYNC_PROP(harmony_now, mLyricColorMap[2])
    SYNC_PROP(harmony_past, mLyricColorMap[3])
    SYNC_PROP(harmony_od_coming, mLyricColorMap[0x11])
    SYNC_PROP(harmony_od_now, mLyricColorMap[0x12])
    SYNC_PROP(harmony_od_past, mLyricColorMap[0x13])
    SYNC_PROP(lead_static_preview, mLyricColorMap[0xC])
    SYNC_PROP(lead_static_coming, mLyricColorMap[0xD])
    SYNC_PROP(lead_static_now, mLyricColorMap[0xE])
    SYNC_PROP(lead_static_past, mLyricColorMap[0xF])
    SYNC_PROP(lead_static_od_preview, mLyricColorMap[0x1C])
    SYNC_PROP(lead_static_od_coming, mLyricColorMap[0x1D])
    SYNC_PROP(lead_static_od_now, mLyricColorMap[0x1E])
    SYNC_PROP(lead_static_od_past, mLyricColorMap[0x1F])
    SYNC_PROP(harmony_static_preview, mLyricColorMap[8])
    SYNC_PROP(harmony_static_coming, mLyricColorMap[9])
    SYNC_PROP(harmony_static_now, mLyricColorMap[0xA])
    SYNC_PROP(harmony_static_past, mLyricColorMap[0xB])
    SYNC_PROP(harmony_static_od_preview, mLyricColorMap[0x18])
    SYNC_PROP(harmony_static_od_coming, mLyricColorMap[0x19])
    SYNC_PROP(harmony_static_od_now, mLyricColorMap[0x1A])
    SYNC_PROP(harmony_static_od_past, mLyricColorMap[0x1B])
    SYNC_PROP(scrolling_coming_alpha, mLyricAlphaMap[1])
    SYNC_PROP(scrolling_now_alpha, mLyricAlphaMap[2])
    SYNC_PROP(scrolling_past_alpha, mLyricAlphaMap[3])
    SYNC_PROP(static_preview_alpha, mLyricAlphaMap[8])
    SYNC_PROP(static_coming_alpha, mLyricAlphaMap[9])
    SYNC_PROP(static_now_alpha, mLyricAlphaMap[0xA])
    SYNC_PROP(static_past_alpha, mLyricAlphaMap[0xB])
    SYNC_PROP(min_pitch_range, mMinPitchRange)
    SYNC_PROP(pitch_display_margin, mPitchDisplayMargin)
    SYNC_PROP(arrow_smoothing, mArrowSmoothing)
    SYNC_PROP(configurable_objects, mConfigurableObjects)
    SYNC_PROP(phrase_feedback_trig, mPhraseFeedbackTrig)
    SYNC_PROP(spotlight_sparkles_only_trig, mSpotlightSparklesOnlyTrig)
    SYNC_PROP(spotlight_phrase_success_trig, mSpotlightPhraseSuccessTrig)
    SYNC_PROP(vox_configuration, mVoxCfg)
    SYNC_PROP(pitch_window, mPitchWindow)
    SYNC_PROP(pitch_window_height, mPitchWindowHeight)
    SYNC_PROP(pitch_window_mesh, mPitchWindowMesh)
    SYNC_PROP(pitch_window_overlay, mPitchWindowOverlay)
    SYNC_PROP(lead_lyrics, mLeadLyrics)
    SYNC_PROP(lead_lyric_height, mLeadLyricHeight)
    SYNC_PROP(lead_lyric_mesh, mLeadLyricMesh)
    SYNC_PROP(harmony_lyrics, mHarmLyrics)
    SYNC_PROP(harmony_lyric_height, mHarmLyricHeight)
    SYNC_PROP(harmony_lyric_mesh, mHarmLyricMesh)
    SYNC_PROP(left_deco_mesh, mLeftDecoMesh)
    SYNC_PROP(right_deco_mesh, mRightDecoMesh)
    SYNC_PROP(now_bar_width, mNowBarWidth)
    SYNC_PROP(now_bar_mesh, mNowBarMesh)
    SYNC_PROP(remote, mRemoteVocals)
    SYNC_PROP(track_left, mTrackLeftX)
    SYNC_PROP(track_right, mTrackRightX)
    SYNC_PROP(track_bottom, mTrackBottomZ)
    SYNC_PROP(track_top, mTrackTopZ)
    SYNC_PROP(pitch_bottom, mPitchBottomZ)
    SYNC_PROP(pitch_top, mPitchTopZ)
    SYNC_PROP(now_bar, mNowBarX)
    SYNC_PROP(pitch_guides, mPitchGuides)
    SYNC_PROP(tube_style, mTubeStyle)
    SYNC_PROP(arrow_style, mArrowStyle)
    SYNC_PROP(font_style, mFontStyle)
    SYNC_PROP(last_min, mLastMin)
    SYNC_PROP(last_max, mLastMax)
    SYNC_PROP(middle_c_z_pos, mMiddleCZPos)
    SYNC_PROP(tonic, mTonic)
    SYNC_PROP(range_scale_anim, mRangeScaleAnim)
    SYNC_PROP(range_offset_anim, mRangeOffsetAnim)
    SYNC_PROP(lead_deploy_mat, mLeadDeployMat)
    SYNC_PROP(harmony_deploy_mat, mHarmDeployMat)
    SYNC_PROP(hidden_part_alpha, mHiddenPartAlpha)
    SYNC_PROP(overdrive_meter, mStarPowerMeter)
    SYNC_SUPERCLASS(BandTrack)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(VocalTrackDir)
    HANDLE_ACTION(set_vox_configuration, SetConfiguration(_msg->Obj<Hmx::Object>(2), (HarmonyShowingState)2))
    HANDLE_ACTION(update_configuration, UpdateConfiguration())
    HANDLE(display_mode, OnGetDisplayMode)
    HANDLE(set_display_mode, OnSetDisplayMode)
    HANDLE_ACTION(set_feedback_state, ShowPhraseFeedback(_msg->Int(2), _msg->Int(3), _msg->Int(4), false))
    HANDLE_ACTION(set_phrase_meter, SetStreakPct(_msg->Float(2)))
    HANDLE_ACTION(spotlight_phrase_success, SpotlightPhraseSuccess())
    HANDLE_ACTION(set_enable_vocals_options, SetEnableVocalsOptions(_msg->Int(2)))
    HANDLE(foreach_configurable_object, DataForEachConfigObj)
    HANDLE_ACTION(rebuild_hud, if(BandTrack::mParent) BandTrack::mParent->RebuildVocalHUD())
    HANDLE_ACTION(apply_font_style, ApplyFontStyle(_msg->Obj<Hmx::Object>(2)))
    HANDLE_ACTION(apply_arrow_style, ApplyArrowStyle(_msg->Obj<Hmx::Object>(2)))
    HANDLE(set_lyric_color, OnSetLyricColor)
    HANDLE_ACTION(track_in, Extend(false))
    HANDLE_ACTION(track_in_now, Extend(true))
    HANDLE_ACTION(track_out, Retract(false))
    HANDLE_ACTION(track_out_now, Retract(true))
    HANDLE(isolate_vocal_part, OnIsolatePart)
    HANDLE_ACTION(show_all_parts, SetIsolatedPart(-1))
    HANDLE_EXPR(num_vocal_parts, NumVocalParts())
    HANDLE_ACTION(set_range, SetRange(_msg->Float(2), _msg->Float(3), _msg->Int(4), false))
    HANDLE_EXPR(num_vocal_parts, NumVocalParts())
    HANDLE_SUPERCLASS(BandTrack)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x71C)
END_HANDLERS
#pragma pop

DataNode VocalTrackDir::DataForEachConfigObj(DataArray* da){
    DataNode* var = da->Var(2);
    DataNode backup(*var);
    for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mConfigurableObjects.begin(); it != mConfigurableObjects.end(); ++it){
        *var = DataNode(*it);
        for(int i = 3; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
    }
    *var = backup;
    return DataNode(0);
}

DataNode VocalTrackDir::OnIsolatePart(DataArray* da){
    int part = da->Int(2);
    if(part + 1U > 3){
        MILO_NOTIFY_ONCE("isolating invalid vocal part: %d", part);
        return DataNode(0);
    }
    else {
        SetIsolatedPart(part);
        return DataNode(0);
    }
}

void VocalTrackDir::SetIsolatedPart(int part){
    if(unk6c4 != part){
        unk6c4 = part;
        unk6c8 = true;
    }
}

void VocalTrackDir::UpdatePartIsolation(){
    if(unk6c8){
        if(BandTrack::mParent) BandTrack::mParent->RebuildVocalHUD();
        if(mStreakMeter) mStreakMeter->SetIsolatedPart(unk6c4);
        unk6c8 = false;
    }
}

int VocalTrackDir::NumVocalParts(){
    if(BandTrack::mParent) return BandTrack::mParent->GetNumVocalParts();
    else return 0;
}

void VocalTrackDir::TutorialReset(){
    Find<RndAnimatable>("freestyle_wave_show.anim", true)->SetFrame(0, 1.0f);
    Find<RndAnimatable>("spotlight_phrase_success.grp", true)->SetFrame(2000.0f, 1.0f);
    StreakMeter* meter = Find<StreakMeter>("streak_meter_vox_top", true);
    meter->Find<RndAnimatable>("flash.anim", true)->SetFrame(11.0f, 1.0f);
    meter->Find<RndAnimatable>("star_power.panim", true)->SetFrame(10.0f, 1.0f);
    meter->Find<RndParticleSys>("star_power.part", true)->FreeAllParticles();
}
