#include "bandobj/TrackPanelDirBase.h"
#include "obj/DataFunc.h"
#include "rndobj/Group.h"
#include "obj/ObjVersion.h"
#include "obj/Msg.h"
#include "rndobj/EventTrigger.h"
#include "utl/Symbols.h"

INIT_REVS(TrackPanelDirBase);

bool gShowHUD = true;

DataNode ToggleHUD(DataArray* da){
    gShowHUD = gShowHUD == 0;
    return DataNode(gShowHUD);
}

TrackPanelDirBase::TrackPanelDirBase() : mViewTimeEasy(0), mViewTimeExpert(0), mNetTrackAlpha(0), mPulseOffset(0), mConfiguration(this, 0), mConfigurableObjects(this, kObjListNoNull),
    unk20c(this), unk21c(this), unk224(0), unk228(0), unk22c(this, 0), unk238(0), unk23c(0), unk240(0), mDoubleSpeedActive(0), mIndependentTrackSpeeds(0) {
    DataRegisterFunc("toggle_hud", ToggleHUD);
    if(SystemConfig()->FindArray("track_graphics", false)){
        if(SystemConfig("track_graphics")->FindArray("pulse_offset", false)){
            mPulseOffset = SystemConfig("track_graphics")->FindFloat("pulse_offset");
        }
    }
}

SAVE_OBJ(TrackPanelDirBase, 0x3F)

void TrackPanelDirBase::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

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
        static Message apply("apply", DataNode(b));
        apply[0] = DataNode(b);
        mConfiguration = o;
        o->Handle(apply, true);
    }
    if(!unk240) SetShowing(gShowHUD);
}

void TrackPanelDirBase::ReapplyConfiguration(bool b){
    if(mConfiguration){
        static Message apply("apply", DataNode(b));
        apply[0] = DataNode(b);
        mConfiguration->Handle(apply, true);
        if(!unk240) SetShowing(gShowHUD);
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
                    static Message active("is_modifier_active", DataNode(""));
                    active[0] = DataNode(s);
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

void TrackPanelDirBase::SetShowing(bool b){
    Find<RndGroup>("draw_order.grp", true)->SetShowing(b);
}

void TrackPanelDirBase::CodaSuccess(){
    MILO_NOTIFY_ONCE("calling non-h2h coda success in h2h mode");
}

BEGIN_HANDLERS(TrackPanelDirBase)
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