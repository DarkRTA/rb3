#include "bandobj/BandDirector.h"
#include "utl/Symbols.h"

DataArray* BandDirector::sPropArr;
BandDirector* TheBandDirector;

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
    unke8.reserve(100);
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
    DataArray* arr = new DataArray(1);
    arr->Node(0) = fognode;
    anim->AddKeys(dir, arr, PropKeys::kSymbol);
    arr->Release();
}

Symbol HiddenInstrument(Symbol s){
    if(s == coop_bg) return keyboard;
    else if(s == coop_bk) return guitar;
    else if(s == coop_gk) return bass;
    else return gNullStr;
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
    HANDLE_EXPR(camera_source, unkf0.Dir())
    HANDLE(get_face_overrides, OnGetFaceOverrideClips)
    HANDLE_EXPR(facing_camera, FacingCamera(_msg->Sym(2)))
    HANDLE_ACTION(load_venue, LoadVenue(_msg->Sym(2), kLoadStayBack))
    HANDLE_ACTION(set_character_hide_hack_enabled, SetCharacterHideHackEnabled(_msg->Int(2)))
    HANDLE(debug_char_interests, OnDebugInterestsForNextCharacter)
    HANDLE(toggle_interests_overlay, OnToggleInterestDebugOverlay)
    HANDLE(shot_annotate, OnShotAnnotate)
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

BEGIN_PROPSYNCS(BandDirector)
END_PROPSYNCS