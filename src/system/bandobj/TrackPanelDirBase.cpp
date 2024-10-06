#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/BandCrowdMeter.h"
#include "bandobj/TrackPanelInterface.h"
#include "obj/DataFunc.h"
#include "rndobj/Group.h"
#include "obj/ObjVersion.h"
#include "obj/Msg.h"
#include "rndobj/EventTrigger.h"
#include "utl/TimeConversion.h"
#include "utl/Symbols.h"

INIT_REVS(TrackPanelDirBase);

bool gShowHUD = true;

DataNode ToggleHUD(DataArray* da){
    gShowHUD = gShowHUD == 0;
    return gShowHUD;
}

TrackPanelDirBase::TrackPanelDirBase() : mViewTimeEasy(0), mViewTimeExpert(0), mNetTrackAlpha(0), mPulseOffset(0), mConfiguration(this, 0), mConfigurableObjects(this, kObjListNoNull),
    mTracks(this), mGemTracks(this), unk224(0), mTrackPanel(0), mApplauseMeter(this, 0), mBandLogoRival(0), mBandLogo(0), mPerformanceMode(0), mDoubleSpeedActive(0), mIndependentTrackSpeeds(0) {
    DataRegisterFunc("toggle_hud", ToggleHUD);
    if(SystemConfig()->FindArray("track_graphics", false)){
        if(SystemConfig("track_graphics")->FindArray("pulse_offset", false)){
            mPulseOffset = SystemConfig("track_graphics")->FindFloat("pulse_offset");
        }
    }
}

SAVE_OBJ(TrackPanelDirBase, 0x3F)

float TrackPanelDirBase::GetPulseAnimStartDelay(bool b) const {
    float beat = MsToBeat(TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f + 16.70000076293945f);
    if(b) beat = beat + mPulseOffset;
    return std::floor(beat) + 1.0f - beat;
}

void TrackPanelDirBase::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

DECOMP_FORCEACTIVE(TrackPanelDirBase, "non-empty list passed to TrackPanelDirBase::GetConfigList, will be cleared")

void TrackPanelDirBase::PostLoad(BinStream& bs){
    PanelDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(!IsProxy()){
        bs >> mViewTimeEasy;
        bs >> mViewTimeExpert;
        bs >> mNetTrackAlpha;
        bs >> mConfigurableObjects;
    }
}

BEGIN_COPYS(TrackPanelDirBase)
    COPY_SUPERCLASS(PanelDir)
    CREATE_COPY(TrackPanelDirBase)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mViewTimeEasy)
        COPY_MEMBER(mViewTimeExpert)
        COPY_MEMBER(mNetTrackAlpha)
        COPY_MEMBER(mConfigurableObjects)
    END_COPYING_MEMBERS
END_COPYS

void TrackPanelDirBase::SetConfiguration(Hmx::Object* o, bool b){
    if(o){
        static Message apply("apply", b);
        apply[0] = b;
        mConfiguration = o;
        o->Handle(apply, true);
    }
    if(!mPerformanceMode) SetShowing(gShowHUD);
}

void TrackPanelDirBase::ReapplyConfiguration(bool b){
    if(mConfiguration){
        static Message apply("apply", b);
        apply[0] = b;
        mConfiguration->Handle(apply, true);
        if(!mPerformanceMode) SetShowing(gShowHUD);
    }
}

bool TrackPanelDirBase::ModifierActive(Symbol s){
    Hmx::Object* gamemodeobj = FindObject("gamemode", true);
    if(gamemodeobj){
        if(gamemodeobj->Property("always_show_hud", true)->Int(0) == 0){
            if(gamemodeobj->Property("is_practice", true)->Int(0) != 0) return false;
            else {
                Hmx::Object* modmgr = FindObject("modifier_mgr", true);
                if(modmgr){
                    static Message active("is_modifier_active", "");
                    active[0] = s;
                    int ret = modmgr->Handle(active, true).Int(0);
                    if(ret != 0) return true;
                }
            }
        }
    }
    return false;
}

void TrackPanelDirBase::Enter(){
    PanelDir::Enter();
    if(TheLoadMgr.EditMode()){
        if(Find<EventTrigger>("reset_all.trig", false)){
            ConfigureTracks(true);
            Reset();
        }
    }
}

float GetTrackViewTime(const Symbol& s1, Symbol s2){
    DataArray* cfg = SystemConfig("objects", "view_times", s1);
    return cfg->FindFloat(s2);
}

void TrackPanelDirBase::UpdateTrackSpeed(){
    if(!mTrackPanel || !mTrackPanel->ShouldUpdateScrollSpeed()) return;
    else {
        mDoubleSpeedActive = ModifierActive(mod_doublespeed);
        mIndependentTrackSpeeds = ModifierActive(mod_independent_track_speeds);
        float f1 = mDoubleSpeedActive ? 1.5f : 1.0f;
        if(mIndependentTrackSpeeds){
            for(int i = 0; i < mGemTracks.size(); i++){
                GemTrackDir* tdir = mGemTracks[i];
                TrackInstrument inst = tdir->GetInstrument();
                Symbol diffsym = tdir->GetPlayerDifficultySym();
                if(tdir->InUse() && inst >= kInstGuitar && diffsym != gNullStr){
                    Symbol instsym = tdir->GetInstrumentSymbol();
                    float viewtime = GetTrackViewTime(instsym, diffsym);
                    tdir->SetScrollSpeed(viewtime / f1);
                }
            }
        }
        else {
            float f14 = 0;
            float f11 = f14;
            float f13 = f14;
            float f15 = f14;
            for(int i = 0; i < mGemTracks.size(); i++){
                GemTrackDir* tdir = mGemTracks[i];
                TrackInstrument inst = tdir->GetInstrument();
                Symbol diffsym = tdir->GetPlayerDifficultySym();
                if(tdir->InUse() && inst >= kInstGuitar && diffsym != gNullStr){
                    Symbol instsym = tdir->GetInstrumentSymbol();
                    float viewtime = GetTrackViewTime(instsym, diffsym);
                    f15 += 1.0f;
                    f11 += viewtime;
                    if(!tdir->HasNetPlayer()){
                        f13 += 1.0f;
                        f14 += viewtime;
                    }
                }
            }
            if(f15 > 0){
                float speed = f13 == 0 ? f11 / f15 : f14 / f13;
                speed /= f1;
                for(int i = 0; i < mGemTracks.size(); i++){
                    mGemTracks[i]->SetScrollSpeed(speed);
                }
            }
        }
    }
}

void TrackPanelDirBase::SetShowing(bool b){
    Find<RndGroup>("draw_order.grp", true)->SetShowing(b);
}

void TrackPanelDirBase::UpdateJoinInProgress(bool b1, bool b2){
    GetCrowdMeter()->UpdateJoinInProgress(b1, b2);
}

void TrackPanelDirBase::FailedJoinInProgress(){
    GetCrowdMeter()->FailedJoinInProgress();
}

void TrackPanelDirBase::ToggleSurface(){
    for(int i = 0; i < mGemTracks.size(); i++){
        RndMesh* d = mGemTracks[i]->mSurfaceMesh;
        d->SetShowing(!d->Showing());
    }
}

void TrackPanelDirBase::ToggleNowbar(){
    for(int i = 0; i < mGemTracks.size(); i++){
        RndGroup* grp = mGemTracks[i]->Find<RndGroup>("now_bar.grp", true);
        grp->SetShowing(!grp->Showing());
    }
}

void TrackPanelDirBase::SetPlayerLocal(BandTrack* track){
    track->SetPlayerLocal(mNetTrackAlpha);
}

void TrackPanelDirBase::CodaSuccess(){
    MILO_NOTIFY_ONCE("calling non-h2h coda success in h2h mode");
}

bool TrackPanelDirBase::ReservedVocalPlayerSlot(int i){
    if(mTrackPanel) return mTrackPanel->SlotReservedForVocals(i);
    else return i == 2;
}

BandTrack* TrackPanelDirBase::GetBandTrackInSlot(int slot){
    MILO_ASSERT(( 0) <= (slot) && (slot) < ( mTracks.size()), 0x180);
    return mTracks[slot];
}

BEGIN_HANDLERS(TrackPanelDirBase)
    HANDLE_EXPR(gem_tracks_size, (int)mGemTracks.size())
    HANDLE_EXPR(get_gem_track, _msg->Int(2) < mGemTracks.size() ? mGemTracks[_msg->Int(2)].Ptr() : (GemTrackDir*)0)
    HANDLE_ACTION(configure_tracks, ConfigureTracks(1))
    HANDLE_ACTION(set_configuration, SetConfiguration(_msg->Obj<Hmx::Object>(2), _msg->Size() > 3 ? _msg->Int(3) : 1))
    HANDLE_ACTION(enter, Enter())
    HANDLE_ACTION(reset, Reset())
    HANDLE_ACTION(set_multiplier, SetMultiplier(_msg->Int(2), false))
    HANDLE_ACTION(play_intro, PlayIntro())
    HANDLE_ACTION(hide_score, HideScore())
    HANDLE_ACTION(game_over, GameOver())
    HANDLE_ACTION(coda, Coda())
    HANDLE_ACTION(set_showing, SetShowing(_msg->Int(2)))
    HANDLE_EXPR(showing, Showing())
    HANDLE_ACTION(toggle_surface, ToggleSurface())
    HANDLE_ACTION(toggle_nowbar, ToggleNowbar())
    HANDLE(foreach_configurable_object, DataForEachConfigObj)
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_CHECK(0x1A7)
END_HANDLERS

void TrackPanelDirBase::PlayIntro(){}
void TrackPanelDirBase::HideScore(){}
void TrackPanelDirBase::GameOver(){}

BEGIN_PROPSYNCS(TrackPanelDirBase)
    SYNC_PROP(view_time_easy, mViewTimeEasy)
    SYNC_PROP(view_time_expert, mViewTimeExpert)
    SYNC_PROP(net_track_alpha, mNetTrackAlpha)
    SYNC_PROP(configuration, mConfiguration)
    SYNC_PROP(configurable_objects, mConfigurableObjects)
    SYNC_SUPERCLASS(PanelDir)
END_PROPSYNCS

DataNode TrackPanelDirBase::DataForEachConfigObj(DataArray* da){
    DataNode* var = da->Var(2);
    DataNode dvar(*var);
    for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mConfigurableObjects.begin(); it != mConfigurableObjects.end(); ++it){
        *var = *it;
        for(int i = 3; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
    }
    *var = dvar;
    return 0;
}