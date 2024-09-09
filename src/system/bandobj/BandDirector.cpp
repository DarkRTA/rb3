#include "bandobj/BandDirector.h"
#include "bandobj/BandWardrobe.h"
#include "rndobj/Group.h"
#include "bandobj/CrowdAudio.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandDirector)

DataArray* BandDirector::sPropArr;
BandDirector* TheBandDirector;

const char* gVenues[5] = { "arena", "big_club", "festival", "small_club", "video" };

BandDirector::VenueLoader::VenueLoader() : mDir(0), mLoader(0) {}

BandDirector::VenueLoader::~VenueLoader(){
    MILO_ASSERT(!mLoader, 0x3C);
    delete mDir;
}

void BandDirector::VenueLoader::Unload(bool async){
    if(mDir) mDir->SetName(mDir->Name(), mDir);
    if(async) TheLoadMgr.StartAsyncUnload();
    RELEASE(mLoader);
    RELEASE(mDir);
    if(async) TheLoadMgr.FinishAsyncUnload();
    mName = "";
    TheBandDirector->VenueLoaded(0);
}

void BandDirector::VenueLoader::Load(const FilePath& fp, LoaderPos pos, bool async){
    Unload(async);
    mName = FileGetBase(fp.c_str(), 0);
    if(!mName.Null() && mName != "none"){
        mLoader = new DirLoader(fp, pos, this, 0, 0, false);
        if(!async) TheLoadMgr.PollUntilLoaded(mLoader, 0);
    }
}

void BandDirector::VenueLoader::FinishLoading(Loader* l){
    MILO_ASSERT(l == mLoader, 0x67);
    mDir = dynamic_cast<WorldDir*>(mLoader->GetDir());
    RELEASE(mLoader);
    TheBandDirector->VenueLoaded(mDir);
}

void BandDirector::Init(){
    Register();
    sPropArr = new DataArray(1);
}

void BandDirector::Terminate(){
    sPropArr->Release();
}

BandDirector::BandDirector() : mPropAnim(this, 0), mMerger(this, 0), mCurWorld(this, 0), unk58(0), unk74(this, 0), unk80(this, 0), unk8c(this, 0), unk98(this, 0),
    unka4(0), unkb0(0), unkb4(1), unkb5(0), unkb6(0), unkb8(this, 0), unkc4(this, 0), unkd0(this, 0), unke0(-1e+30f), unke4(0), unke5(1), unk108(-1.0f), unk10c(0),
    unk110(0), unk114(0) {
    static DataNode& banddirector = DataVariable("banddirector");
    banddirector = DataNode(this);
    unkb6 = !TheLoadMgr.EditMode();
    if(TheBandDirector){
        MILO_WARN("Trying to make > 1 BandDirector, which should be single");
    }
    else TheBandDirector = this;
    mDircuts.reserve(100);
}

BandDirector::~BandDirector(){
    if(TheBandDirector == this){
        static DataNode& banddirector = DataVariable("banddirector");
        banddirector = DataNode((Hmx::Object*)0);
        TheBandDirector = 0;
    }
    else MILO_WARN("Deleting second BandDirector, should be singleton");
}

void AddStageKitKeys(RndPropAnim* anim, BandDirector* dir){
    DataNode fognode(Symbol("stagekit_fog"));
    DataArrayPtr ptr(fognode);
    anim->AddKeys(dir, ptr, PropKeys::kSymbol);
}

Symbol HiddenInstrument(Symbol s){
    if(s == coop_bg) return keyboard;
    else if(s == coop_bk) return guitar;
    else if(s == coop_gk) return bass;
    else return gNullStr;
}

#pragma push
#pragma pool_data off
void BandDirector::Enter(){
    RndPollable::Enter();
    if(mMerger){
        unk5c = 0;
        unk60 = 3;
        unke0 = -1e+30f;
        unkdc = "";
        unk74 = GetWorld()->Find<RndPostProc>("world.pp", true);
        RndPostProc* profilm = GetWorld()->Find<RndPostProc>("ProFilm_a.pp", true);
        if(profilm) unk74->Copy(profilm, kCopyDeep);
        unk74->Select();
        unk8c = unk74;
        unk98 = unk74;
        unka4 = 0;
        sMotionBlurBlendAmount = SystemConfig("rnd", "motion_blur")->Float(1);
        unk80 = 0;
        unka8 = unkac = gNullStr;
        unkb0 = 0;
        unk108 = -1.0f;
        unkb5 = 0;
        mCurWorld = 0;
        if(mPropAnim){
            mPropAnim->StartAnim();
            mPropAnim->SetFrame(-1e+30f, 1.0f);
        }
        EnterVenue();
        unke4 = 0;
        unkc4 = 0;
        static Message allowMsg("allow_intro_shot", DataNode(0));
        int handled = HandleType(allowMsg).Int(0);
        if(handled && !unkd0) PickIntroShot();
        if(handled && unkd0){
            static Message msg("set_intro_shot", DataNode(0));
            msg[0] = DataNode(unkd0);
            DataNode handled = HandleType(msg);
            unkc4 = unkd0;
            unkd0 = 0;
        }
        else FindNextShot();
        Symbol hidden = HiddenInstrument(TheBandWardrobe->GetPlayMode());
        static const char* modes[3] = { "keyboard", "guitar", "bass" };
        for(int i = 0; i < 3U; i++){
            Symbol thismode = modes[i];
            RndGroup* grp = GetWorld()->Find<RndGroup>(MakeString("%s_spot.grp", modes[i]), false);
            if(grp) grp->SetShowing(thismode != hidden);
        }
        if(mPropAnim && unk110){
            DataArrayPtr ptr(DataNode(Symbol("stagekit_fog")));
            SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, ptr));
            if(!skeys){
                AddStageKitKeys(mPropAnim, this);
                skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, ptr));
            }
            if(skeys && skeys->empty()){
                float cap = Min(unk10c, 241.0f);
                for(float f = 0.0f; f + 60.0f < cap; f += 60.0f){
                    skeys->Add(on, (f + 15.0f) * 30.0f, false);
                    skeys->Add(off, (f + 30.0f) * 30.0f, false);
                }
            }
        }
    }
}
#pragma pop

void BandDirector::Exit(){
    RndPollable::Exit();
    if(mPropAnim) mPropAnim->EndAnim();
    if(mVenue.Dir()) mVenue.Dir()->Exit();
}

bool BandDirector::PostProcsFromPresets(const RndPostProc*& p1, const RndPostProc*& p2, float& fref){
    MILO_ASSERT(IsMusicVideo() && LightPresetMgr(), 0x161);
    LightPreset* mgr1 = 0;
    LightPreset* mgr2 = 0;
    LightPresetMgr()->GetPresets(mgr1, mgr2);
    if(!mgr1) mgr1 = mgr2;
    if(mgr1){
        RndPostProc* proc1 = mgr1->GetCurrentPostProc();
        if(proc1){
            RndPostProc* proc2 = mgr2 ? mgr2->GetCurrentPostProc() : 0;
            if(proc2){
                unk74->Interp(proc1, proc2, unkb0);
                p1 = proc1;
                p2 = proc2;
                fref = unkb0;
            }
            else {
                unk74->Copy(proc1, kCopyDeep);
                p1 = proc1;
                p2 = 0;
                fref = 1.0f;
            }
            return true;
        }
    }
    return false;
}

void BandDirector::Poll(){
    if(unke5){
        if(mCurWorld){
            mCurWorld->Poll();
            if(unkb4 && (unka8 != gNullStr || unkac != gNullStr)){
                LightPresetMgr()->Interp(unka8, unkac, unkb0);
            }
            LightPresetMgr()->Poll();
        }
    }
    if(unk74){
        const RndPostProc* p1 = 0;
        const RndPostProc* p2 = 0;
        float fref = 1.0f;
        const char* presets = "";
        if(unk80){
            unk74->Copy(unk80, kCopyDeep);
            presets = "camera";
            p1 = unk80;
        }
        else {
            bool ppfp = false;
            if(IsMusicVideo() && LightPresetMgr()){
                ppfp = PostProcsFromPresets(p1, p2, fref);
                if(ppfp) presets = "music video light presets";
            }
            if(!ppfp){
                unk74->Interp(unk8c, unk98, unka4);
                fref = unka4;
                presets = "song authoring";
                p1 = unk8c;
                p2 = unk98;
            }
        }
        UpdatePostProcOverlay(presets, p1, p2, fref);
        DataNode& fps_var = DataVariable("cheat.emulate_fps");
        if(fps_var.Int(0) > 0){
            int ifps = fps_var.Int(0);
            unk74->mEmulateFPS = ifps;
        }
    }
}

void BandDirector::UpdatePostProcOverlay(const char* cc, const RndPostProc* p1, const RndPostProc* p2, float f){
    RndOverlay* o = RndOverlay::Find("postproc", true);
    if(o->Showing()){
        TextStream* ts = TheDebug.mReflect;
        if(p1 && !p2){
            MILO_LOG("Post Proc %s is not blended\n", p1->Name());
        }
        else {
            if(p1) MILO_LOG("Post Proc A %s\n", p1->Name());
            if(p2) MILO_LOG("Post Proc B %s\n", p2->Name());
        }
        MILO_LOG("PostProc set by %s, blend is %.2f%%\n", cc ? cc : "", f * 100.0f);
        TheDebug.SetReflect(ts);
    }
}

void BandDirector::ListPollChildren(std::list<RndPollable*>& polls) const {
    polls.push_back(mVenue.Dir());
}

void BandDirector::DrawShowing(){
    if(mCurWorld) mCurWorld->DrawShowing();
}

void BandDirector::ListDrawChildren(std::list<RndDrawable*>& draws){
    draws.push_back(mVenue.Dir());
}

void BandDirector::CollideList(const Segment& seg, std::list<Collision>& colls){
    if(mCurWorld) mCurWorld->CollideListSubParts(seg, colls);
    RndDrawable::CollideList(seg, colls);
}

SAVE_OBJ(BandDirector, 0x1FA)

BEGIN_LOADS(BandDirector)
    LOAD_REVS(bs)
    ASSERT_REVS(6, 0)
    MILO_ASSERT(gRev > 2, 0x204);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndPollable)
    LOAD_SUPERCLASS(RndDrawable)
    if(gRev < 5) LOAD_SUPERCLASS(Hmx::Object)
    if(gRev < 6){
        Symbol s; bs >> s;
    }
    if(gRev < 4){
        char buf[0x100];
        bs.ReadString(buf, 0x100);
    }
END_LOADS

BEGIN_COPYS(BandDirector)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndPollable)
    CREATE_COPY(BandDirector)
END_COPYS

void BandDirector::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    RndDrawable::Replace(from, to);
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(BandDirector, BandDirector, LightPresetMgr())
#pragma pop

WorldDir* BandDirector::GetWorld(){
    if(mMerger) return dynamic_cast<WorldDir*>(mMerger->Dir());
    else return 0;
}

bool BandDirector::FacingCamera(Symbol s) const {
    return (strnicmp(s.Str(), "coop_", 5) == 0 && !BehindCamera(s));
}

bool BandDirector::BehindCamera(Symbol s) const {
    const char* str = s.Str();
    int len = strlen(str);
    return (len > 7 && strcmp(str + (len - 7), "_behind") == 0);
}

void BandDirector::FindNextShot(){
    unkc4 = 0;
    if(!unkdc.Null()){
        WorldDir* dir = mVenue.Dir();
        if(dir){
            std::vector<CameraManager::PropertyFilter> filts;
            CameraManager::PropertyFilter curfilt;
            BandCamShot* shot = unkb8;
            if(!FacingCamera(unkdc)) shot = 0;
            if(shot && !BehindCamera(shot->Category())){
                curfilt.prop = DataNode(flags_any);
                curfilt.match = DataNode(1);
                curfilt.mask = ~shot->Flags() & 0x7000;
                filts.push_back(curfilt);
            }
            unkc4 = dynamic_cast<BandCamShot*>(dir->mCameraManager.FindCameraShot(unkdc, filts));
            if(!unkc4){
                MILO_LOG("NOTIFY could not find BandCamShot %s in %s at %s, ignoring\n", unkdc, dir->mPathName, TheTaskMgr.GetMBT());
            }
        }
    }
}

void BandDirector::EnterVenue(){
    if(TheBandWardrobe){
        WorldDir* dir = mVenue.Dir();
        if(dir){
            dir->SetName(dir->Name(), GetWorld());
            dir->Enter();
            if(dir != mCurWorld){
                TheBandWardrobe->SetVenueDir(dir);
                if(mCurWorld) mCurWorld->Handle(remove_midi_parsers_msg, false);
                mCurWorld = dir;
                unk58 = true;
                if(mCurWorld){
                    if(TheCrowdAudio) TheCrowdAudio->SetBank(mCurWorld);
                    if(TheLoadMgr.EditMode()){
                        GetWorld()->mSphere = mCurWorld->mSphere;
                    }
                    mCurWorld->Handle(setup_midi_parsers_msg, false);
                    ClearLighting();
                }
            }
        }
    }
}

void BandDirector::ClearLighting(){
    if(mCurWorld) mCurWorld->Handle(clear_lighting_msg, false);
}

void GetVenuePath(FilePath& fp, const char* cc){
    FilePathTracker tracker(FileRoot());
    fp.SetRoot("none");
    if(*cc == '\0' || streq(cc, "none")){
        return;
    }
    else {
        for(int i = 0; gVenues[i] != 0; i++){
            char* str = strstr(cc, gVenues[i]);
            if(str){
                fp.SetRoot(MakeString("world/venue/%s/%s/%s.milo", gVenues[i], cc, cc));
                return;
            }
        }
        MILO_WARN("BandDirector unknown venue %s", cc);
    }
}

void BandDirector::SetShot(Symbol cat, Symbol s2){
    bool b1 = true;
    if(TheBandWardrobe){
        if(!IsDirected(s2)) b1 = false;
    }
    if(!b1){
        MILO_ASSERT(!BFTB(cat), 0x326);
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandDirector)
    HANDLE(first_shot_ok, OnFirstShotOK)
    HANDLE(shot_over, OnShotOver)
    HANDLE_ACTION(midi_add_postproc, OnMidiAddPostProc(_msg->Sym(2), _msg->Float(3), _msg->Float(4)))
    HANDLE(postproc_interp, OnPostProcInterp)
    HANDLE(save_song, OnSaveSong)
    HANDLE(on_file_loaded, OnFileLoaded)
    HANDLE(select_camera, OnSelectCamera)
    HANDLE_EXPR(is_music_video, IsMusicVideo())
    HANDLE(lightpreset_interp, OnLightPresetInterp)
    HANDLE(lightpreset_keyframe_interp, OnLightPresetKeyframeInterp)
    HANDLE(cycle_shot, OnCycleShot)
    HANDLE(force_shot, OnForceShot)
    HANDLE_EXPR(camera_source, mVenue.Dir())
    HANDLE(get_face_overrides, OnGetFaceOverrideClips)
    HANDLE_EXPR(facing_camera, FacingCamera(_msg->Sym(2)))
    HANDLE_ACTION(load_venue, LoadVenue(_msg->Sym(2), kLoadStayBack))
    HANDLE_ACTION(set_character_hide_hack_enabled, SetCharacterHideHackEnabled(_msg->Int(2)))
#ifdef VERSION_SZBE69_B8
    HANDLE(debug_char_interests, OnDebugInterestsForNextCharacter)
    HANDLE(toggle_interests_overlay, OnToggleInterestDebugOverlay)
    HANDLE(shot_annotate, OnShotAnnotate)
#endif
    HANDLE(cur_postprocs, OnPostProcs)
    HANDLE_EXPR(get_curworld, mCurWorld.Ptr())
    HANDLE_EXPR(get_world, mMerger ? mMerger->Dir() : (Hmx::Object*)0)
    HANDLE(set_dircut, OnSetDircut)
    HANDLE(force_preset, OnForcePreset)
    HANDLE(stomp_presets, OnStompPresets)
    HANDLE(midi_add_preset, OnMidiAddPreset)
    HANDLE_ACTION(midi_cleanup_presets, OnMidiPresetCleanup())
    HANDLE(get_cat_list, OnGetCatList)
    HANDLE(copy_cats, OnCopyCats)
    HANDLE(load_song, OnLoadSong)
    HANDLE(midi_shot_cat, OnMidiShotCategory)
    HANDLE_ACTION(add_symbol_key, AddSymbolKey(_msg->Sym(2), _msg->Sym(3), _msg->Float(4)))
    HANDLE_ACTION(clear_symbol_keys, ClearSymbolKeys(_msg->Sym(2)))
    HANDLE_ACTION(clear_symbol_keys_in_range, ClearSymbolKeysFrameRange(_msg->Sym(2), _msg->Float(3), _msg->Float(4)))
    HANDLE_ACTION(midi_harvest_dircuts, HarvestDircuts())
    HANDLE_ACTION(pick_new_shot, unk58 = 0)
    HANDLE_ACTION(set_end, SetSongEnd(_msg->Float(2)))
    HANDLE_MEMBER_PTR(LightPresetMgr())
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x513)
END_HANDLERS
#pragma pop

DataNode BandDirector::OnPostProcs(DataArray* da){
    DataNode* v2 = da->Var(2);
    DataNode* v3 = da->Var(3);
    DataNode* v4 = da->Var(4);
    *v2 = DataNode(unk8c);
    *v3 = DataNode(unk98);
    *v4 = DataNode(unka4);
    return DataNode(0);
}

DataNode BandDirector::OnPostProcInterp(DataArray* da){
    unk8c = da->Obj<RndPostProc>(2);
    unk98 = da->Obj<RndPostProc>(3);
    unka4 = da->Float(4);
    return DataNode(0);
}

BEGIN_PROPSYNCS(BandDirector)
    SYNC_PROP_SET(shot_5, unkdc, SetShot(_val.Sym(0), "shot_5"))
    SYNC_PROP_SET(shot_bg, unkdc, SetShot(_val.Sym(0), coop_bg))
    SYNC_PROP_SET(shot_bk, unkdc, SetShot(_val.Sym(0), coop_bk))
    SYNC_PROP_SET(shot_gk, unkdc, SetShot(_val.Sym(0), coop_gk))
    SYNC_PROP_SET(postproc, (Hmx::Object*)0, )
    SYNC_PROP_SET(lightpreset, verse, )
    SYNC_PROP_SET(lightpreset_keyframe, next, )
    SYNC_PROP_SET(world_event, none, ExportWorldEvent(_val.Sym(0)))
    SYNC_PROP(merger, mMerger)
    SYNC_PROP(disable_picking, unke4)
    SYNC_PROP(disabled, unkb5)
    SYNC_PROP(lightpreset_interp_enabled, unkb4)
    SYNC_PROP(excitement, unk60)
    SYNC_PROP(num_players_failed, unk5c)
    SYNC_PROP(cam_postproc, unk80)
    SYNC_PROP_SET(cur_shot, unkb8, )
    SYNC_PROP_SET(cur_world, mCurWorld, )
    SYNC_PROP_SET(bass_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "bass"))
    SYNC_PROP_SET(drum_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "drum"))
    SYNC_PROP_SET(guitar_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "guitar"))
    SYNC_PROP_SET(mic_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "mic"))
    SYNC_PROP_SET(keyboard_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "keyboard"))
    SYNC_PROP_SET(part2_sing, Symbol("singalong_off"), ) // fix set part
    SYNC_PROP_SET(part3_sing, Symbol("singalong_off"), ) // fix set part
    SYNC_PROP_SET(part4_sing, Symbol("singalong_off"), ) // fix set part
    SYNC_PROP_SET(crowd, Symbol("crowd_realtime"), SetCrowd(_val.Sym(0)))
    SYNC_PROP(propanim, mPropAnim)
    SYNC_PROP_SET(spot_bass, Symbol("off"), SetCharSpot("bass", _val.Sym(0)))
    SYNC_PROP_SET(spot_drums, Symbol("off"), SetCharSpot("drums", _val.Sym(0)))
    SYNC_PROP_SET(spot_guitar, Symbol("off"), SetCharSpot("guitar", _val.Sym(0)))
    SYNC_PROP_SET(spot_keyboard, Symbol("off"), SetCharSpot("keyboard", _val.Sym(0)))
    SYNC_PROP_SET(spot_vocal, Symbol("off"), SetCharSpot("vocal", _val.Sym(0)))
    SYNC_PROP_SET(stagekit_fog, Symbol("off"), SetFog(_val.Sym(0)))
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS