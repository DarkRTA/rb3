#include "bandobj/VocalTrackDir.h"
#include "bandobj/TrackInterface.h"
#include "obj/ObjVersion.h"
#include "obj/DataFunc.h"
#include "rndobj/Rnd.h"
#include "utl/ClassSymbols.h"
#include "utl/Symbols.h"

INIT_REVS(VocalTrackDir)

VocalTrackDir::VocalTrackDir() : BandTrack(this), mHiddenPartAlpha(0.3f), unk2a4(1), unk2a5(1), mIsTop(1), unk2a7(0), mFeedbackStateLead(0), mFeedbackStateHarm1(0), mFeedbackStateHarm2(0),
    mVocalMics(this, 0), unk2f0(this, 0), mMinPitchRange(12.0f), mPitchDisplayMargin(3.0f), mArrowSmoothing(0.85f), mConfigurableObjects(this, kObjListNoNull), mVoxCfg(this, 0),
    mTambourineSmasher(this, 0), mTambourineNowShowTrig(this, 0), mTambourineNowHideTrig(this, 0), mLeadPhraseFeedbackBottomLbl(this, 0), mPhraseFeedbackTrig(this, 0),
    mSpotlightSparklesOnlyTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mPitchArrow1(this, 0), mPitchArrow2(this, 0), mPitchArrow3(this, 0), mPitchWindow(1),
    mPitchWindowHeight(2.5f), mPitchWindowMesh(this, 0), mPitchWindowOverlay(this, 0), mLeadLyrics(1), mLeadLyricHeight(0.4f), mLeadLyricMesh(this, 0), mHarmLyrics(1),
    mHarmLyricHeight(0.4f), mHarmLyricMesh(this, 0), mLeftDecoMesh(this, 0), mRightDecoMesh(this, 0), mNowBarWidth(0.2f), mNowBarMesh(this, 0), mRemoteVocals(0),
    mTrackLeftX(-20.0f), mTrackRightX(20.0f), mTrackBottomZ(0.0f), mTrackTopZ(10.0f), mPitchBottomZ(0.0f), mPitchTopZ(2.0f), mNowBarX(-10.0f), unk42c(0), mPitchGuides("harmonic"),
    mTubeStyle(this, 0), mArrowStyle(this, 0), mFontStyle(this, 0), unk458(this, 0), unk464(this, 0), unk470(this, 0), unk47c(this, 0), mLastMin(36.0f), mLastMax(84.0f), mMiddleCZPos(0),
    mTonic(0x3c), mRangeScaleAnim(this, 0), mRangeOffsetAnim(this, 0), unk4b0(1), unk4b4(2), mLeftTrans(0), mRightTrans(0), mBottomTrans(0), mTopTrans(0),
    mPitchBottomTrans(0), mPitchTopTrans(0), mPitchMidTrans(0), mNowTrans(0), mTubeRangeGrp(this, 0), mTubeSpotlightGrp(this, 0), mTubeBack0Grp(this, 0), mTubeBack1Grp(this, 0),
    mTubeBack2Grp(this, 0), mTubeFront0Grp(this, 0), mTubeFront1Grp(this, 0), mTubeFront2Grp(this, 0), mTubeGlow0Grp(this, 0), mTubeGlow1Grp(this, 0), mTubeGlow2Grp(this, 0),
    mTubePhoneme0Grp(this, 0), mTubePhoneme1Grp(this, 0), mTubePhoneme2Grp(this, 0), unk580(this, 0), unk58c(this, 0), unk598(this, 0), unk5a4(this, 0), unk5b0(this, 0), unk5bc(this, 0),
    unk5c8(this, 0), unk5d4(this, 0), unk5e0(this, 0), unk5ec(this, 0), unk5f8(this, 0), unk604(this, 0), unk610(this, 0), mVocalsGrp(this, 0), mScroller(this, 0), mLeadLyricScroller(this, 0),
    mHarmonyLyricScroller(this, 0), mBREGrp(this, 0), mLeadBREGrp(this, 0), mHarmonyBREGrp(this, 0), mPitchScrollGroup(this, 0), mLeadLyricScrollGroup(this, 0),
    mHarmonyLyricScrollGroup(this, 0), unk694(0), unk698(0), unk69c(0), unk6a0(0), mLeadDeployMat(this, 0), mHarmDeployMat(this, 0), unk6bc(-1.0f), unk6c0(0.3f),
    unk6c4(-1), unk6c8(0), mArrowFXDrawGrp(this, 0), unk6d8(18.0f), unk6dc(48.0f), unk6e0(0) {

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
        COPY_MEMBER(unk458)
        COPY_MEMBER(unk464)
        COPY_MEMBER(unk470)
        COPY_MEMBER(unk47c)
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
        COPY_MEMBER(unk580)
        COPY_MEMBER(unk58c)
        COPY_MEMBER(unk598)
        COPY_MEMBER(unk5a4)
        COPY_MEMBER(unk5b0)
        COPY_MEMBER(unk5bc)
        COPY_MEMBER(unk5c8)
        COPY_MEMBER(unk5d4)
        COPY_MEMBER(unk5e0)
        COPY_MEMBER(unk5ec)
        COPY_MEMBER(unk5f8)
        COPY_MEMBER(unk604)
        COPY_MEMBER(unk610)
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
        case kDataInt: return MakeString("%d", node.Int(0));
        case kDataFloat: return MakeString("%f", node.Float(0));
        case kDataVar: return MakeString("%s", DataVarName(node.Var(0)));
        case kDataFunc: return MakeString("%s", DataFuncName(node.Func(0)));
        case kDataObject:
            if(node.NotNull()) return MakeString("%s", node.GetObj(0)->Name());
            else return MakeString("<null>");
        case kDataSymbol: return node.Sym(0).Str();
        case kDataArray: return MakeString("<array>");
        case kDataCommand: return MakeString("<command>");
        case kDataString: return node.Str(0);
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
            bs >> unk458;
            bs >> unk464;
            if(gRev >= 4){
                bs >> unk470;
                bs >> unk47c;
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
        mRemoteVocals = mVoxCfg->Property(remote, true)->Int(0);
        unk4b0 = mVoxCfg->Property(align, true)->Sym(0) == top;
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
    TrackInterface* parent = BandTrack::mParent;
    if(parent && parent->HasNetPlayer()) b8 = true;
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
        if(unk458) unk458->SetText("");
        if(unk464) unk464->SetText("");
        if(unk470) unk470->SetText("");
        if(unk47c) unk47c->SetText("");
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