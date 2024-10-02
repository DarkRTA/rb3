#include "bandobj/BandDirector.h"
#include "bandobj/BandWardrobe.h"
#include "rndobj/Group.h"
#include "bandobj/CrowdAudio.h"
#include "world/Dir.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandDirector)

DataArray* BandDirector::sPropArr;
BandDirector* TheBandDirector;
bool gIsLoadingDlc;

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

BandDirector::BandDirector() : mPropAnim(this, 0), mMerger(this, 0), mCurWorld(this, 0), unk58(0), mWorldPostProc(this, 0), mCamPostProc(this, 0), mPostProcA(this, 0), mPostProcB(this, 0),
    mPostProcBlend(0), mLightPresetCatBlend(0), mLightPresetInterpEnabled(1), mDisabled(0), mAsyncLoad(0), mCurShot(this, 0), mNextShot(this, 0), mIntroShot(this, 0), unke0(-1e+30f), mDisablePicking(0), unke5(1), unk108(-1.0f), mEndOfSongSec(0),
    unk110(0), mSongPref(0) {
    static DataNode& banddirector = DataVariable("banddirector");
    banddirector = DataNode(this);
    mAsyncLoad = !TheLoadMgr.EditMode();
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
        mNumPlayersFailed = 0;
        mExcitement = 3;
        unke0 = -1e+30f;
        mShotCategory = "";
        mWorldPostProc = GetWorld()->Find<RndPostProc>("world.pp", true);
        RndPostProc* profilm = GetWorld()->Find<RndPostProc>("ProFilm_a.pp", true);
        if(profilm) mWorldPostProc->Copy(profilm, kCopyDeep);
        mWorldPostProc->Select();
        mPostProcA = mWorldPostProc;
        mPostProcB = mWorldPostProc;
        mPostProcBlend = 0;
        sMotionBlurBlendAmount = SystemConfig("rnd", "motion_blur")->Float(1);
        mCamPostProc = 0;
        mLightPresetCatA = mLightPresetCatB = gNullStr;
        mLightPresetCatBlend = 0;
        unk108 = -1.0f;
        mDisabled = 0;
        mCurWorld = 0;
        if(mPropAnim){
            mPropAnim->StartAnim();
            mPropAnim->SetFrame(-1e+30f, 1.0f);
        }
        EnterVenue();
        mDisablePicking = 0;
        mNextShot = 0;
        static Message allowMsg("allow_intro_shot", DataNode(0));
        int handled = HandleType(allowMsg).Int(0);
        if(handled && !mIntroShot) PickIntroShot();
        if(handled && mIntroShot){
            static Message msg("set_intro_shot", DataNode(0));
            msg[0] = DataNode(mIntroShot);
            DataNode handled = HandleType(msg);
            mNextShot = mIntroShot;
            mIntroShot = 0;
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
                float cap = Min(mEndOfSongSec, 241.0f);
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

DECOMP_FORCEACTIVE(BandDirector, "video")

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
                mWorldPostProc->Interp(proc1, proc2, mLightPresetCatBlend);
                p1 = proc1;
                p2 = proc2;
                fref = mLightPresetCatBlend;
            }
            else {
                mWorldPostProc->Copy(proc1, kCopyDeep);
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
            if(mLightPresetInterpEnabled && (mLightPresetCatA != gNullStr || mLightPresetCatB != gNullStr)){
                LightPresetMgr()->Interp(mLightPresetCatA, mLightPresetCatB, mLightPresetCatBlend);
            }
            LightPresetMgr()->Poll();
        }
    }
    if(mWorldPostProc){
        const RndPostProc* p1 = 0;
        const RndPostProc* p2 = 0;
        float fref = 1.0f;
        const char* presets = "";
        if(mCamPostProc){
            mWorldPostProc->Copy(mCamPostProc, kCopyDeep);
            presets = "camera";
            p1 = mCamPostProc;
        }
        else {
            bool ppfp = false;
            if(IsMusicVideo() && LightPresetMgr()){
                ppfp = PostProcsFromPresets(p1, p2, fref);
                if(ppfp) presets = "music video light presets";
            }
            if(!ppfp){
                mWorldPostProc->Interp(mPostProcA, mPostProcB, mPostProcBlend);
                fref = mPostProcBlend;
                presets = "song authoring";
                p1 = mPostProcA;
                p2 = mPostProcB;
            }
        }
        UpdatePostProcOverlay(presets, p1, p2, fref);
#ifdef MILO_DEBUG
        DataNode& fps_var = DataVariable("cheat.emulate_fps");
        if(fps_var.Int(0) > 0){
            int ifps = fps_var.Int(0);
            mWorldPostProc->mEmulateFPS = ifps;
        }
#endif
    }
}

void BandDirector::UpdatePostProcOverlay(const char* cc, const RndPostProc* p1, const RndPostProc* p2, float f){
#ifdef MILO_DEBUG
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
#endif
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

bool BandDirector::DirectedCut(Symbol s) const {
    return strncmp(s.mStr, "directed_", 9) == 0;
}

bool BandDirector::BFTB(Symbol s) const { return strncmp(s.mStr, "BFTB_", 5) == 0; }

bool BandDirector::FacingCamera(Symbol s) const {
    return (strnicmp(s.mStr, "coop_", 5) == 0 && !BehindCamera(s));
}

bool BandDirector::BehindCamera(Symbol s) const {
    const char* str = s.mStr;
    int len = strlen(str);
    return (len > 7 && strcmp(str + (len - 7), "_behind") == 0);
}

void BandDirector::FindNextShot(){
    mNextShot = 0;
    if(!mShotCategory.Null()){
        WorldDir* dir = mVenue.Dir();
        if(dir){
            std::vector<CameraManager::PropertyFilter> filts;
            CameraManager::PropertyFilter curfilt;
            BandCamShot* shot = mCurShot;
            if(!FacingCamera(mShotCategory)) shot = 0;
            if(shot && !BehindCamera(shot->Category())){
                curfilt.prop = DataNode(flags_any);
                curfilt.match = DataNode(1);
                curfilt.mask = ~shot->Flags() & 0x7000;
                filts.push_back(curfilt);
            }
            mNextShot = dynamic_cast<BandCamShot*>(dir->mCameraManager.FindCameraShot(mShotCategory, filts));
#ifdef MILO_DEBUG
            if(!mNextShot){
                MILO_LOG("NOTIFY could not find BandCamShot %s in %s at %s, ignoring\n", mShotCategory, dir->mPathName, TheTaskMgr.GetMBT());
            }
#endif
        }
    }
}

void BandDirector::PlayNextShot(){
    unk58 = false;
    if(mNextShot){
        BandCamShot* oldnextshot = mNextShot;
        mNextShot = 0;
        if(oldnextshot && DirectedCut(oldnextshot->Category())){
            float oldz = oldnextshot->mZeroTime;
            oldnextshot->ConvertFrames(oldz);
            float oldmin = oldnextshot->mMinTime;
            bool ret = oldnextshot->ConvertFrames(oldmin);
            MILO_ASSERT(ret, 0x2A1);
            MaxEq(oldmin, 0.25f);
            unke0 = oldmin + oldz + TheTaskMgr.Seconds(TaskMgr::b);
        }
        else {
            if(oldnextshot && BFTB(oldnextshot->Category())){
                unke0 = TheTaskMgr.Seconds(TaskMgr::b) + oldnextshot->GetTotalDurationSeconds();
            }
            else {
                bool b2 = false;
                bool b1 = false;
                if(unke0 == -1000.0f && mCurShot) b1 = true;
                if(b1){
                    b1 = true;
                    if(!DirectedCut(mCurShot->Category())){
                        if(!BFTB(mCurShot->Category())) b1 = false;
                    }
                    if(b1) b2 = true;
                }
                if(b2) unke0 = TheTaskMgr.Seconds(TaskMgr::b) + 1.0f;
                else unke0 = -1.0E+30f;
            }
        }
        mCurShot = oldnextshot;
        WorldDir* wdir = GetWorld();
        wdir->mCameraManager.ForceCameraShot(mCurShot);
        if(mCurWorld) mCurWorld->Handle(cam_cut_msg, false);
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
#ifdef MILO_DEBUG
                    if(TheLoadMgr.EditMode()){
                        GetWorld()->mSphere = mCurWorld->mSphere;
                    }
#endif
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

bool BandDirector::IsMusicVideo(){
    return strstr(mVenue.Name().mStr, "video");
}

void BandDirector::SetShot(Symbol cat, Symbol s2){
    bool b1 = true;
    if(TheBandWardrobe){
        if(!DirectedCut(cat)) b1 = false;
    }
    if(!b1){
        MILO_ASSERT(!BFTB(cat), 0x326);
        bool shot5 = s2 == "shot_5";
        bool playshot5 = TheBandWardrobe->PlayShot5();
        if(shot5 == playshot5){
            if(shot5){
                cat = RemapCat(cat, TheBandWardrobe->GetPlayMode());
            }
            else {
                if(s2 != TheBandWardrobe->GetPlayMode()) return;
            }
            mShotCategory = cat;
            unk58 = true;
        }
    }
}

bool BandDirector::ReadyForMidiParsers(){
    if(!mPropAnim && gIsLoadingDlc){
        static Message msg("on_pre_merge", DataNode(0), DataNode(0), DataNode(0));
        msg[0] = DataNode(song);
        msg[1] = DataNode((Hmx::Object*)0);
        OnFileLoaded(msg);
    }
    bool ret = false;
    bool b2 = false;
    if(mPropAnim){
        bool b1 = true;
        if(!mVenue.Dir()){
            if(mVenue.Name() == "none"){

            }
            else b1 = false;
        }
        if(b1) b2 = true;
    }
    if(b2 && TheBandWardrobe->AllCharsLoaded()) ret = true;
    return ret;
}

void BandDirector::SendMessage(Symbol s1, Symbol s2){
    if(TheBandWardrobe) TheBandWardrobe->SendMessage(s1, s2, true);
}

void BandDirector::SetCrowd(Symbol s){
    static Message msg("");
    msg.SetType(s);
    HandleType(msg);
}

inline BandCharacter* BandDirector::GetCharacter(int idx) const {
    if(TheBandWardrobe) return TheBandWardrobe->GetCharacter(idx);
    else return 0;
}

DECOMP_FORCEACTIVE(BandDirector, "ADD_", "BLEND_")

DataNode BandDirector::OnGetFaceOverrideClips(DataArray* da){
    std::list<Symbol> syms;
    BandCharacter* bchar = GetCharacter(da->Int(2));
    if(bchar){
        CharLipSyncDriver* driver = bchar->GetLipSyncDriver();
        if(driver){
            ObjectDir* overridedir = driver->OverrideDir();
            if(overridedir){
                for(ObjDirItr<CharClip> it(overridedir, false); it; ++it){
                    String blendstr("BLEND_");
                    blendstr += it->Name();
                    syms.push_back(blendstr.c_str());
                    String addstr("ADD_");
                    addstr += it->Name();
                    syms.push_back(addstr.c_str());
                }
            }
        }
    }
    DataArray* arr = new DataArray(syms.size() + 1);
    arr->Node(0) = DataNode(Symbol());
    int idx = 1;
    for(std::list<Symbol>::iterator it = syms.begin(); it != syms.end(); ++it, ++idx){
        arr->Node(idx) = DataNode(*it);
    }
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

void BandDirector::ForceShot(BandCamShot* shot){
    mNextShot = shot;
    mDisablePicking = mNextShot;
}

void BandDirector::PickIntroShot(){
    mNextShot = 0;
    DataNode handled = HandleType(pick_intro_shot_msg);
    mIntroShot = mNextShot;
    mNextShot = 0;
}

Symbol GetShotTrack(){
    if(TheBandWardrobe->PlayShot5()){
        return "shot_5";
    }
    else {
        char buf[10];
        strcpy(buf, TheBandWardrobe->GetPlayMode().mStr);
        memcpy(buf, "shot", 4);
        return buf;
    }
}

void BandDirector::AddDircut(Symbol cat, float frame){
    MILO_ASSERT(DirectedCut(cat), 0x40D);
    std::vector<CameraManager::PropertyFilter> filts;
    BandCamShot* shot = dynamic_cast<BandCamShot*>(mVenue.Dir()->mCameraManager.FindCameraShot(cat, filts));
    if(TheBandWardrobe && !TheBandWardrobe->AddDircut(shot)){
        MILO_WARN("Too many non-free Dircuts, not playing %s", PathName(shot));
        shot = 0;
    }
    if(shot){
        float f2c = shot->mZeroTime;
        if(shot->ConvertFrames(f2c)){
            frame = frame - f2c;
        }
        else MILO_FAIL("couldn't convert, in beats!");
    }
    mDircuts.Add(shot, frame, false);
}

void BandDirector::VenueLoaded(WorldDir*){
    mDircuts.clear();
}

void BandDirector::HarvestDircuts(){
    if(mPropAnim && mVenue.Dir()){
        mDircuts.clear();
        TheBandWardrobe->ClearDircuts();
        mIntroShot = 0;
        if(!TheBandWardrobe->DemandLoadSym()){
            CameraManager::PropertyFilter filt;
            int mask = 0;
            Symbol playmode = TheBandWardrobe->GetPlayMode();
            if(strncmp(playmode.mStr, "coop", 4) == 0){
                if(playmode == coop_bg) mask = 0x100000;
                else if(playmode == coop_bk) mask = 0x400000;
                else mask = 0x200000;
            }
            WorldDir* wdir = mVenue.Dir();
            for(std::vector<CameraManager::Category, unsigned int>::iterator it = wdir->mCameraManager.mCameraShotCategories.begin();
                it != wdir->mCameraManager.mCameraShotCategories.end(); ++it){
                for(ObjPtrList<CamShot, ObjectDir>::iterator cit = it->unk4->begin(); cit != it->unk4->end(); ++cit){
                    CamShot* shot = *cit;
                    shot->Disable(!TheBandWardrobe->ValidGenreGender(shot), 2);
                    shot->Disable((mask & shot->Flags()) == 0, 4);
                }
            }
            PickIntroShot();
            DataArrayPtr ptr(GetShotTrack());
            SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, (DataArray*)ptr));
            if(skeys){
                Keys<Symbol, Symbol>& keys = skeys->AsSymbolKeys();
                for(int i = 0; i < keys.size(); i++){
                    Symbol val = keys[i].value;
                    if(DirectedCut(val)){
                        if(TheBandWardrobe->PlayShot5()){
                            val = RemapCat(val, TheBandWardrobe->GetPlayMode());
                        }
                        float frame = keys[i].frame;
                        AddDircut(val, frame / 30.0f);
                    }
                }
            }
        }
        TheBandWardrobe->StartClipLoads(true, 0);
    }
}

void BandDirector::AddSymbolKey(Symbol s1, Symbol s2, float f){
    if(mPropAnim){
        DataArrayPtr ptr = DataArrayPtr(DataNode(s1));
        SymbolKeys* keys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, (DataArray*)ptr));
        if(keys) keys->Add(s2, f * 30.0f, false);
    }
}

void BandDirector::ClearSymbolKeys(Symbol s){
    if(mPropAnim){
        DataArrayPtr ptr = DataArrayPtr(DataNode(s));
        SymbolKeys* keys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, (DataArray*)ptr));
        if(keys) keys->clear();
    }
}

void BandDirector::ClearSymbolKeysFrameRange(Symbol s, float fstart, float fend){
    if(mPropAnim){
        DataArrayPtr ptr = DataArrayPtr(DataNode(s));
        SymbolKeys* keys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, (DataArray*)ptr));
        if(keys){
            int numkeys = keys->NumKeys();
            for(int i = 0; i < numkeys; i){
                float frame = 0;
                keys->FrameFromIndex(i, frame);
                frame /= 30.0f;
                if(frame >= fstart && frame <= fend) keys->RemoveKey(i);
                else i++;
            }
        }   
    }
}

void BandDirector::SetSongEnd(float f){
    mEndOfSongSec = f;
}

Symbol BandDirector::RemapCat(Symbol s1, Symbol s2){
    DataArray* remaparr = BandWardrobe::GetRemap(s2);
    DataArray* foundarr = remaparr->FindArray(s1, false);
    if(foundarr){
        s1 = foundarr->Sym(RandomInt(1, foundarr->Size()));
    }
    return s1;
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
#ifdef MILO_DEBUG
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
    HANDLE_ACTION(pick_new_shot, unk58 = 1)
    HANDLE_ACTION(set_end, SetSongEnd(_msg->Float(2)))
    HANDLE_MEMBER_PTR(LightPresetMgr())
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x513)
END_HANDLERS
#pragma pop

void BandDirector::FilterShot(int& flags){
    if(mCurShot){
        if(strstr(mCurShot->Category().mStr, "_behind")){
            flags |= 0x10;
        }
        else {
            bool b1 = false;
            if(!(flags & 0x20U)){
                if(strstr(mCurShot->Category().mStr, "_far")){
                    b1 = true;
                }
            }
            if(b1) flags |= 0x100;
        }
    }
}

const char* BandDirector::PickDist(float* fp, char* c1, char* c2){
    static const char* distNames[] = { "closeup", "near", "far", "behind" };
    float f1 = 0;
    for(int i = 0; i < 4; i++) f1 += fp[i];
    float randfl = RandomFloat(0.0f, f1);
    int d = 0;
    for(; d < 3; d++){
        randfl = randfl - fp[d];
        if(randfl < 0.0f) break;
    }
    if(d == 0 && *c1 != 'v'){
        strcpy(c2, RandomFloat(0.0f, 100.0f) > 30.0f ? "_hand" : "_head");
    }
    else *c2 = '\0';
    MILO_ASSERT(d >= 0 && d < 4, 0x54D);
    return distNames[d];
}

DataNode BandDirector::OnMidiShotCategory(DataArray* da){
    static int fs[] = { 1, 2, 4, 8, 3, 5, 9, 6, 0xA, 0xC, 0xD, 0xF };
    int mask = da->Int(2);
    Symbol s3c = TheBandWardrobe->GetPlayMode();
    int bits = CountBits(mask & 0xF);
    if(bits == 3 && (mask & 2)){
        mask &= 0xfffffffd;
        bits = 2;
    }
    if(bits == 0){
        mask |= fs[RandomInt(0, 0xC)];
        bits = CountBits(mask & 0xF);
    }
    if((mask & 0x40) && (bits != 1)){
        mask &= 0xffffffbf;
    }
    char buf[8];
    char buf2[8];
    float fls[] = { 4.0f, 3.0f, 4.0f, 1.0f };
    FilterShot(mask);
    if(bits == 4){
        if(mask & 0x100){
            mask &= 0xfffffffd;
            bits = 3;
        }
    }
    if((mask & 0x10) == 0){
        if((bits != 2) || ((mask & 2) == 0)) goto lol;
    }
    fls[3] = 0.0f;
lol:
    if((mask & 0x20) || bits == 4){
        bits = 4;
        mask |= 0x2F;
    }
    else fls[2] = 0.0f;

    if(bits != 1) mask |= 0x80;
    if(mask & 0x80) fls[0] = 0;
    if(mask & 0x60) fls[1] = 0;
    if(bits == 4) strcpy(buf, "all");
    else if(bits == 3) strcpy(buf, "front");
    else {
        bool b1 = mask & 1;
        int u5 = 0;
        if(b1){
            buf[0] = 'b';
            u5 = 1;
        }
        if(mask & 2){
            buf[u5] = 'd';
            u5++;
        }
        if(mask & 4){
            buf[u5] = 'g';
            u5++;
        }
        if(mask & 8){
            buf[u5] = 'v';
            u5++;
        }
        buf[u5] = 0;
    }
    return DataNode(Symbol(MakeString("coop_%s_%s%s", buf, PickDist(fls, buf, buf2), buf2)));
}

DataNode BandDirector::OnCycleShot(DataArray* da){
    WorldDir* wdir = mVenue.Dir();
    if(wdir){
        BandCamShot* shot = dynamic_cast<BandCamShot*>(wdir->CamManager().ShotAfter(mCurShot));
        ForceShot(shot);
    }
    return DataNode(0);
}

DataNode BandDirector::OnForceShot(DataArray* da){
    WorldDir* wdir = mVenue.Dir();
    if(wdir){
        ForceShot(wdir->Find<BandCamShot>(da->Str(2), false));
    }
    return DataNode(0);
}

DataNode BandDirector::OnLoadSong(DataArray* da){
    FilePathTracker tracker(FileRoot());
    const char* songfile = da->Str(2);
    gIsLoadingDlc = FileIsDLC(songfile);
    MILO_LOG("BandDirector::OnLoadSong: is dlc? %s\n", gIsLoadingDlc ? "yes" : "no");
    Symbol s3 = da->Sym(3);
    int i4 = da->Int(4);
    Symbol s5 = da->Sym(5);
    bool i6 = da->Int(6);
    DataArray* genrearr = TypeDef()->FindArray("anim_genres", true);
    DataArray* s3arr = genrearr->FindArray(s3, false);
    if(s3arr) s3 = s3arr->Sym(1);
    else {
        s3 = "rocker";
        MILO_WARN("song %s has unknown genre %s, forcing to rocker", songfile, s3);
    }

    Symbol speed;
    if(i4 == 0x10) speed = "slow";
    else if(i4 == 0x40) speed = "fast";
    else speed = "medium";

    if(TheBandWardrobe){
        TheBandWardrobe->SetSongInfo(speed, s5);
        TheBandWardrobe->SetSongAnimGenre(s3);
    }

    mMerger->Select("song", FilePath(songfile), true);
    if(i6) mMerger->StartLoad(mAsyncLoad);
    return DataNode(0);
}

DataNode BandDirector::OnFileLoaded(DataArray* da){
    Symbol sym = da->Sym(2);
    ObjectDir* dir = da->Obj<ObjectDir>(3);
    if(sym == song){
        mEndOfSongSec = 0;
        if(dir){
            mPropAnim = dir->Find<RndPropAnim>("song.anim", false);
            mSongPref = dir->Find<BandSongPref>("BandSongPref", false);
            if(TheBandWardrobe && mSongPref){
                TheBandWardrobe->SetSongAnimGenre(mSongPref->GetAnimGenre());
            }
        }
        if(!mPropAnim){
            unk110 = true;
            mPropAnim = Hmx::Object::New<RndPropAnim>();
            FileMerger::Merger* merger = mMerger->FindMerger("song", true);
            merger->mLoadedObjects.push_back(mPropAnim);
            mPropAnim->SetName("song.anim", mMerger->Dir());
            mPropAnim->SetType("song_anim");
            mPropAnim->SetRate(RndAnimatable::k480_fpb);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("shot_bg"))), PropKeys::kSymbol); 
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("bass_intensity"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("drum_intensity"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("guitar_intensity"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("mic_intensity"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("crowd"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("world_event"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("lightpreset"))), PropKeys::kSymbol);
            mPropAnim->SetInterpHandler(this, DataArrayPtr(DataNode(Symbol("lightpreset"))), Symbol("lightpreset_interp"));
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("lightpreset_keyframe"))), PropKeys::kSymbol);
            mPropAnim->SetInterpHandler(this, DataArrayPtr(DataNode(Symbol("lightpreset_keyframe"))), Symbol("lightpreset_keyframe_interp"));
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("postproc"))), PropKeys::kObject);
            mPropAnim->SetInterpHandler(this, DataArrayPtr(DataNode(Symbol("postproc"))), Symbol("postproc_interp"));
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("spot_bass"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("spot_drums"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("spot_guitar"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("spot_keyboard"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("spot_vocal"))), PropKeys::kSymbol);
            AddStageKitKeys(mPropAnim, this);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("part2_sing"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("part3_sing"))), PropKeys::kSymbol);
            mPropAnim->AddKeys(this, DataArrayPtr(DataNode(Symbol("part4_sing"))), PropKeys::kSymbol);
        }
        else unk110 = false;
        const char* instIntensities[] = { "mic_intensity", "bass_intensity", "drum_intensity", "guitar_intensity", "key_intensity", 0 };
        for(const char** ptr = instIntensities; *ptr != 0; ptr++){
            DataArrayPtr dptr = DataArrayPtr(DataNode(Symbol(*ptr)));
            SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, dptr));
            if(skeys) skeys->unk30 = true;
        }
        if(!mVenue.Name().Null()){
            if(TheBandWardrobe){
                TheBandWardrobe->LoadCharacters(mVenue.Name(), mAsyncLoad);
                if(mCurWorld){
                    FileMerger* m = mCurWorld->Find<FileMerger>("extras.fm", false);
                    if(m) m->StartLoad(true);
                }
                if(dir){
                    CharLipSync* sync = dir->Find<CharLipSync>("song.lipsync", false);
                    Symbol guitarmodeinst = mSongPref ? GetModeInst(mSongPref->Part2Inst()) : GetModeInst("guitar");
                    Symbol bassmodeinst = mSongPref ? GetModeInst(mSongPref->Part3Inst()) : GetModeInst("bass");
                    Symbol drummodeinst = mSongPref ? GetModeInst(mSongPref->Part3Inst()) : GetModeInst("drum");

                    BandCharacter* bchar2 = 0;
                    BandCharacter* bchar3 = 0;
                    BandCharacter* bchar4 = 0;
                    CharLipSyncDriver* thelipsyncdriver = 0;
                    for(int i = 0; i < 4; i++){
                        BandCharacter* bcharcur = TheBandWardrobe->GetCharacter(i);
                        Symbol bcharinst = bcharcur->InstrumentType();
                        if(bcharinst == "mic"){
                            bcharcur->SetLipSync(sync);
                            bcharcur->SetSingalong(1.0f);
                            thelipsyncdriver = bcharcur->GetLipSyncDriver();
                        }
                        else if(bcharinst == guitarmodeinst) bchar2 = bcharcur;
                        else if(bcharinst == bassmodeinst) bchar3 = bcharcur;
                        else if(bcharinst == drummodeinst) bchar4 = bcharcur;
                    }

                    if(bchar2){
                        bchar2->SetSingalong(0.0f);
                        CharLipSync* lipsync2 = dir->Find<CharLipSync>("part2.lipsync", false);
                        if(lipsync2) bchar2->SetLipSync(lipsync2);
                        else bchar2->SetSongOwner(thelipsyncdriver);
                    }
                    if(bchar3){
                        bchar3->SetSingalong(0.0f);
                        CharLipSync* lipsync3 = dir->Find<CharLipSync>("part3.lipsync", false);
                        if(lipsync3) bchar3->SetLipSync(lipsync3);
                        else bchar3->SetSongOwner(thelipsyncdriver);
                    }
                    if(bchar4){
                        bchar4->SetSingalong(0.0f);
                        CharLipSync* lipsync4 = dir->Find<CharLipSync>("part4.lipsync", false);
                        if(lipsync4) bchar4->SetLipSync(lipsync4);
                        else bchar4->SetSongOwner(thelipsyncdriver);
                    }
                }
            }
            else {
                FilePathTracker tracker(FileRoot());
                mChars.LoadFile(FilePath("world/shared/world_chars.milo"), false, true, kLoadFront, false);
            }
        }
    }
    return DataNode(0);
}

void BandDirector::LoadVenue(Symbol s, LoaderPos pos){
    FilePath fp;
    GetVenuePath(fp, s.mStr);
    mVenue.Load(fp, pos, mAsyncLoad);
}

void BandDirector::UnloadVenue(bool b){
    mVenue.Unload(b);
}

DataNode BandDirector::OnSaveSong(DataArray* da){
    return DataNode(0);
}

void ExtractPstCatAdjs(DataArray* arr, Symbol& s1, Symbol& s2){
    DataNode eval2(arr->Evaluate(2));
    if(eval2.Type() == kDataSymbol){
        s1 = eval2.Sym(arr);
    }
    else {
        MILO_WARN("unhandled light preset category at %f seconds\n", DataNode(arr->Evaluate(4)));
    }
    DataNode eval3(arr->Evaluate(3));
    if(eval3.Type() == kDataArray){
        DataArray* evalarr = eval3.Array(arr);
        int arrsize = evalarr->Size();
        if(arrsize > 0){
            s2 = evalarr->Sym(0);
            if(arrsize > 1){
                MILO_WARN("unhandled light preset adjective: %s, %f secs\n", evalarr->Str(1), DataNode(arr->Evaluate(4)));
            }
        }
    }
}

void ExtractCatAdj(Symbol s, Symbol& s1, Symbol& s2){
    char buf[256];
    StrNCopy(buf, s.mStr, 255);
    char* strplus = strstr(buf, "+");
    if(strplus){
        *strplus = 0;
        s1 = strplus == buf ? gNullStr : buf;
        s2 = !(strplus + 1) ? gNullStr : strplus + 1;
    }
    else {
        s1 = s;
        s2 = gNullStr;
    }
}

Symbol ConcatCatAdj(Symbol s1, Symbol s2){
    Symbol ret;
    if(s2 != gNullStr){
        ret = MakeString("%s+%s", s1.mStr, s2.mStr);
    }
    else ret = s1;
    return ret;
}

void BandDirector::OnMidiPresetCleanup(){
    if(!mPropAnim || !mVenue.Dir()) return;
    DataArrayPtr dptr(DataNode(Symbol("lightpreset")));
    PropKeys* keys = mPropAnim->GetKeys(this, dptr);
    if(!keys) return;
    WorldDir* wdir = mVenue.Dir();
    Keys<Symbol, Symbol>& skeys = keys->AsSymbolKeys();
    Keys<Symbol, Symbol> local_keys;
    for(int i = 0; i < skeys.size(); i++){
        Symbol s1, s2;
        ExtractCatAdj(skeys[i].value, s1, s2);
        if(s2 != gNullStr) s1 = s2;
        skeys[i].value = s1;
        LightPreset* lpreset = wdir->mPresetManager.PickRandomPreset(skeys[i].value);
        if(lpreset && i > 0){
            float fadein = lpreset->LegacyFadeIn() / 480.0f;
            ClampEq(fadein, 0.0f, 4.0f);
            float stb = SecondsToBeat(skeys[i].frame / 30.0f);
            float bts = BeatToSeconds(Max(0.0f, stb - fadein));
            float newframe = bts * 30.0f;
            if(skeys[i - 1].frame <= newframe){
                local_keys.push_back(Key<Symbol>(skeys[i - 1].value, newframe));
            }              
        }
        else if(!lpreset){
            MILO_WARN("Can't find light preset %s, %f secs", s1.mStr, skeys[i].frame / 30.0f);
        }
    }
    for(int i = 0; i < local_keys.size(); i++){
        skeys.Add(local_keys[i].value, local_keys[i].frame, true);
    }
}

DataNode BandDirector::OnMidiAddPreset(DataArray* da){
    MILO_ASSERT(mPropAnim, 0x7C4);
    DataArrayPtr dptr(DataNode(Symbol("lightpreset")));
    SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, dptr));
    if(skeys){
        Symbol s1, s2;
        ExtractPstCatAdjs(da, s1, s2);
        float frame = da->Float(4) * 30.0f;
        const Key<Symbol>* prev;
        const Key<Symbol>* next;
        float ref;
        int at = skeys->AtFrame(frame, prev, next, ref);
        if(prev){
            Symbol s50 = prev->value;
            Symbol s54, s58;
            ExtractCatAdj(s50, s54, s58);
            if(s2 == gNullStr){
                s2 = s1 == gNullStr ? gNullStr : s58;
            }
            if(s1 == gNullStr) s1 = s54;
            Symbol s5c = ConcatCatAdj(s1, s2);
            if(at >= 0 && skeys->at(at).frame == frame){
                skeys->at(at).value = s5c;
            }
            else skeys->Add(s5c, frame, false);
        }
        else {
            Symbol s60 = ConcatCatAdj(s1, s2);
            if(s60 != gNullStr) skeys->Add(s60, frame, false);
        }
    }
    return DataNode(0);
}

BandCamShot* BandDirector::FindNextDircut(){
    float secs = TheTaskMgr.Seconds(TaskMgr::b);
    float delta = secs - TheTaskMgr.DeltaSeconds();
    Key<BandCamShot*>* key = mDircuts.GetFirstInRange(secs, delta);
    if(!key) return 0;
    else {
        if(key->value) unk58 = true;
        return key->value;
    }
}

int curInterestDebugChar = 5;

DataNode BandDirector::OnDebugInterestsForNextCharacter(DataArray* da){
    int i4 = curInterestDebugChar;
    curInterestDebugChar = (curInterestDebugChar + 1) % 6;
    if(curInterestDebugChar == 4){
        for(i4 = 0; i4 < 4; i4++){
            BandCharacter* bc = GetCharacter(i4);
            if(bc) bc->SetDebugDrawInterestObjects(true);
        }
    }
    else if(curInterestDebugChar == 5){
        RndOverlay* o = RndOverlay::Find("eye_status", false);
        if(o) o->SetOverlay(false);
        for(i4 = 0; i4 < 4; i4++){
            BandCharacter* bc = GetCharacter(i4);
            if(bc) bc->SetDebugDrawInterestObjects(false);
        }
    }
    else {
        RndOverlay* o = RndOverlay::Find("eye_status", false);
        if(o) o->SetOverlay(true);
        int c = curInterestDebugChar;
        BandCharacter* bc = GetCharacter(c);
        if(bc) bc->SetDebugDrawInterestObjects(true);
        if(i4 < 4){
            BandCharacter* bc = GetCharacter(i4);
            if(bc) bc->SetDebugDrawInterestObjects(false);
        }
    }
    return DataNode(0);
}

DataNode BandDirector::OnToggleInterestDebugOverlay(DataArray* da){
    RndOverlay* o = RndOverlay::Find("eye_status", false);
    if(o) o->SetOverlay(o->Showing() == 0);
    return DataNode(0);
}

DataNode BandDirector::OnShotAnnotate(DataArray* da){
    if(!mPropAnim) return DataNode(0);
    else {
        RndPropAnim* propanim = da->Obj<RndPropAnim>(2);
        DataArray* arr3 = da->Array(3);
        PropKeys* keys = propanim->GetKeys(this, arr3);
        int i7 = da->Int(4);
        if(!keys || i7 < 0) return DataNode(0);
        else {
            Keys<Symbol, Symbol>& skeys = keys->AsSymbolKeys();
            Key<Symbol>& skey = skeys[i7];
            Symbol symval = skey.value;
            DataArrayPtr ptr;
            float f1 = 0;
            if(i7 + 1 < skeys.size()){
                f1 = (skeys[i7 + 1].frame - skey.frame) / 30.0f;
            }
            ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame), DataNode(MakeString("%.1f sec", f1)))));
            if(strneq(symval.mStr, "directed_", 9)){
                static DataArray* limits = SystemConfig("objects", "BandCamShot", "types", "band", "dircut_limits")->Array(1);
                static DataArray* freeDircuts = SystemConfig("objects", "BandCamShot", "types", "band", "free_dircuts")->Array(1);
                float f19 = 7.5f;
                float f21 = 0;
                DataArray* symarr = limits->FindArray(symval, false);
                float f18 = f19;
                float f20 = f19;
                if(symarr){
                    f21 = symarr->Float(1);
                    float f17 = symarr->Float(2);
                    if(f17 > 7.5f) f20 = f17;
                    f17 = symarr->Float(3);
                    if(f17 > 7.5f) f18 = f17;
                    f17 = symarr->Float(4);
                    if(f17 > 7.5f) f19 = f17;
                }
                else MILO_NOTIFY_ONCE("could not find %s in dircut_limits", symval);

                ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame + 7.5f), DataNode("fallback_end"))));
                ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame - f21), DataNode("zero_time"))));
                ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame + f20), DataNode("min_time"))));
                ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame + f18), DataNode("dur_min"))));
                ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame + f19), DataNode("dur_max"))));

                for(int i = 0; i < freeDircuts->Size(); i++){
                    if(symval == freeDircuts->Sym(i)){
                        ptr->Insert(ptr->Size(), DataNode(DataArrayPtr(DataNode(skey.frame), DataNode("free_dircut"))));
                        break;
                    }
                }
            }
            DataNode ret = DataNode(ptr, kDataArray);
            // return DataNode(ret);
        }
    }
}

DataNode BandDirector::OnPostProcs(DataArray* da){
    DataNode* v2 = da->Var(2);
    DataNode* v3 = da->Var(3);
    DataNode* v4 = da->Var(4);
    *v2 = DataNode(mPostProcA);
    *v3 = DataNode(mPostProcB);
    *v4 = DataNode(mPostProcBlend);
    return DataNode(0);
}

DataNode BandDirector::OnPostProcInterp(DataArray* da){
    mPostProcA = da->Obj<RndPostProc>(2);
    mPostProcB = da->Obj<RndPostProc>(3);
    mPostProcBlend = da->Float(4);
    return DataNode(0);
}

DataNode BandDirector::OnShotOver(DataArray* da){
    BandCamShot* shot = da->Obj<BandCamShot>(2);
    if(DirectedCut(shot->Category()) || BFTB(shot->Category())){
        unk58 = true;
        unke0 = -1000.0f;
    }
    else unke0 = -1e+30f;
    return DataNode(0);
}

DataNode BandDirector::OnSetDircut(DataArray* da){
    WorldDir* wdir = mVenue.Dir();
    if(wdir && !NoWorlds()){
        Symbol sym = da->Sym(2);
        std::vector<CameraManager::PropertyFilter> filts;
        mNextShot = dynamic_cast<BandCamShot*>(wdir->CamManager().FindCameraShot(sym, filts));
    }
    return DataNode(mNextShot);
}

DataNode BandDirector::OnLightPresetInterp(DataArray* da){
    if(da->Type(2) == kDataSymbol && da->Type(3) == kDataSymbol){
        mLightPresetCatA = da->Sym(2);
        mLightPresetCatB = da->Sym(3);
        mLightPresetCatBlend = da->Float(4);
        if(da->Type(6) == kDataSymbol){
            Symbol sym = da->Sym(6);
            if(mLightPresetCatA != mLightPresetCatB && sym != mLightPresetCatA){
                mLightPresetCatB = mLightPresetCatA;
            }
        }
        else mLightPresetCatB = mLightPresetCatA;
    }
    return DataNode(0);
}

float FindFrameWithLeadIn(){
    float beat = TheTaskMgr.Beat();
    float bts = BeatToSeconds(beat + 4.0f);
    return bts * 30.0f;
}

void BandDirector::FindNextPstKeyframe(float f1, float f2, Symbol s){
    unk108 = 1e+30f;
    float stb = SecondsToBeat(f2 / 30.0f);
    float beat = TheTaskMgr.Beat();
    if((stb - beat) + 1.1920929E-7f > 4.0f) unk108 = f2;
    else {
        DataArrayPtr ptr(DataNode(Symbol("lightpreset_keyframe")));
        SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, ptr));
        if(skeys){
            int idx = skeys->FindFirstAfter(f1);
            Keys<Symbol, Symbol>& keys = skeys->AsSymbolKeys();
            for(; idx < keys.size(); idx++){
                unk108 = keys[idx].frame;
                if(keys[idx].value != none){
                    if(f1 != unk108) break;
                }
            }
        }
    }
}

DataNode BandDirector::OnLightPresetKeyframeInterp(DataArray* da){
    if(!mCurWorld) return DataNode(0);
    else {
        float leadin = FindFrameWithLeadIn();
        bool b10 = unk108 < 0.0f;
        if(leadin >= unk108){
            Symbol s58;
            DataArrayPtr ptr(DataNode(Symbol("lightpreset_keyframe")));
            SymbolKeys* skeys = dynamic_cast<SymbolKeys*>(mPropAnim->GetKeys(this, ptr));
            if(skeys){
                int idx = skeys->FindLastBefore(unk108);
                Keys<Symbol, Symbol>& keys = skeys->AsSymbolKeys();
                if(idx > 0) s58 = keys[idx].value;
            }
            if(SymToPstKeyframe(s58) != LightPreset::kPresetKeyframeNum){
                LightPresetMgr()->SchedulePstKey(SymToPstKeyframe(s58));
            }
            b10 = true;
        }
        if(b10 || TheLoadMgr.EditMode()){
            float f5 = da->Float(5);
            Symbol s60 = da->Sym(3);
            float f108 = unk108;
            FindNextPstKeyframe(leadin, f5, s60);
            if(!b10 && f108 != unk108) LightPreset::ResetEvents();
        }
        return DataNode(0);
    }
}

DataNode BandDirector::OnForcePreset(DataArray* da){
    if(LightPresetMgr()){
        DataNode& eval = da->Evaluate(2);
        float f3 = da->Size() > 3 ? da->Float(3) : 0;
        LightPreset* lp;
        if(eval.Type() == kDataSymbol || eval.Type() == kDataString){
            lp = mCurWorld->Find<LightPreset>(eval.Str(0), false);
        }
        else lp = eval.Obj<LightPreset>(0);
        LightPresetMgr()->ForcePreset(lp, f3);
    }
    return DataNode(0);
}

DataNode BandDirector::OnStompPresets(DataArray* da){
    if(LightPresetMgr()){
        DataNode& eval2 = da->Evaluate(2);
        DataNode& eval3 = da->Evaluate(3);
        LightPreset* lp1;
        LightPreset* lp2;

        if(eval2.Type() == kDataSymbol || eval2.Type() == kDataString){
            lp1 = mCurWorld->Find<LightPreset>(eval2.Str(0), false);
        }
        else lp1 = eval2.Obj<LightPreset>(0);

        if(eval3.Type() == kDataSymbol || eval3.Type() == kDataString){
            lp2 = mCurWorld->Find<LightPreset>(eval3.Str(0), false);
        }
        else lp2 = eval3.Obj<LightPreset>(0);

        LightPresetMgr()->StompPresets(lp1, lp2);
    }
    return DataNode(0);
}

DataNode BandDirector::OnGetCatList(DataArray* da){
    Symbol s2 = da->Sym(2);
    DataArray* arr3 = da->Array(3);
    DataArray* arr = new DataArray(arr3->Size());

    int i1 = 0;
    for(int i = 0; i < arr3->Size(); i++){
        Symbol cursym = arr3->Sym(i);
        if(RemapCat(cursym, s2) != cursym){
            // ???
        }
        else {
            arr->Node(i1++) = DataNode(cursym);
        }
    }
    arr->Resize(i1);
    DataNode ret(arr, kDataArray);
    arr->Release();
    return DataNode(arr, kDataArray);
}

DataNode BandDirector::OnCopyCats(DataArray* da){
    if(!mPropAnim) return DataNode(0);
    else {
        Symbol s2 = da->Sym(2);
        String str30(s2.Str());
        str30.replace(0, 4, "shot");
        PropKeys* shotkeys = mPropAnim->GetKeys(this, DataArrayPtr(DataNode(Symbol(str30.c_str()))));
        PropKeys* shot5keys = mPropAnim->GetKeys(this, DataArrayPtr(DataNode(Symbol("shot_5"))));
        if(!shotkeys || !shot5keys) return DataNode(0);
        else {
            Keys<Symbol, Symbol>& sym5keys = shot5keys->AsSymbolKeys();
            Keys<Symbol, Symbol>& symkeys = shotkeys->AsSymbolKeys();
            symkeys.clear();
            for(int i = 0; i < sym5keys.size(); i++){
                Key<Symbol> curkey(sym5keys[i]);
                curkey.value = RemapCat(curkey.value, s2);
                symkeys.push_back(curkey);
            }
        }
        return DataNode(0);
    }
}

void BandDirector::OnMidiAddPostProc(Symbol s, float f1, float f2){
    MILO_ASSERT(mPropAnim, 0x9A1);
    DataArrayPtr dptr(DataNode(Symbol("postproc")));
    ObjectKeys* okeys = dynamic_cast<ObjectKeys*>(mPropAnim->GetKeys(this, dptr));
    if(okeys && mVenue.Dir()){
        RndPostProc* proc = mVenue.Dir()->Find<RndPostProc>(s.Str(), false);
        if(proc){
            float frame = f1 * 30.0f;
            const Key<ObjectStage>* prev;
            const Key<ObjectStage>* next;
            float ref;
            okeys->AtFrame(frame, prev, next, ref);
            if(prev){
                okeys->Add(prev->value, frame, false);
            }
            else {
                RndPostProc* profilma = mVenue.Dir()->Find<RndPostProc>("ProFilm_a.pp", false);
                if(profilma){
                    if(frame > 0) okeys->Add(profilma, 0, false);
                    okeys->Add(profilma, frame, false);
                }
            }
            okeys->Add(proc, f2 * 30.0f + frame, false);
        }
        else MILO_WARN("PostProc %s not found.  Cannot add to song.anim!\n", s.Str());
    }
}

void BandDirector::ExportWorldEvent(Symbol s){
    if(s != none){
        if(mCurWorld){
            static Message msg("");
            msg.SetType(s);
            mCurWorld->Export(msg, false);
        }
    }
}

void BandDirector::SendCurWorldMsg(Symbol s, bool b){
    static Message msg("");
    if(mCurWorld){
        msg.SetType(s);
        if(b) mCurWorld->HandleType(msg);
        else mCurWorld->Handle(msg, false);
    }
}

void BandDirector::SetCharSpot(Symbol s1, Symbol s2){
    Symbol playmode = TheBandWardrobe->GetPlayMode();
    if(HiddenInstrument(playmode) != s1){
        SendCurWorldMsg(MakeString("spotlight_%s_%s", s1.Str(), s2.Str()), false);
    }
}

void BandDirector::SetFog(Symbol){}

Symbol BandDirector::GetModeInst(Symbol s){
    if(s == "guitar" || s == "bass"){
        Symbol playmode = TheBandWardrobe->GetPlayMode();
        if(s == "guitar" && playmode == coop_bk) return keyboard;
        if(s == "bass" && playmode == coop_gk) return keyboard;
    }
    return s;
}

DataNode BandDirector::OnFirstShotOK(DataArray* da){
    Symbol s2 = da->Sym(2);
    if(strncmp(s2.mStr, "coop_", 5) != 0) return DataNode(0);
    else {
        float f3c = 1e+30f;
        float f10 = mPropAnim->GetFrame();
        Symbol symshottouse = TheBandWardrobe->PlayShot5() ? shot_5 : TheBandWardrobe->GetPlayMode();
        if(symshottouse == coop_bg) symshottouse = shot_bg;
        else if(symshottouse == coop_bk) symshottouse = shot_bk;
        else if(symshottouse == coop_gk) symshottouse = shot_gk;

        sPropArr->Node(0) = DataNode(symshottouse);
        Keys<Symbol, Symbol>& skeys = mPropAnim->GetKeys(this, sPropArr)->AsSymbolKeys();

        Keys<Symbol, Symbol>* keys = &skeys;
        MILO_ASSERT(keys, 0xA42);

        bool b2 = false;
        bool b1 = false;
        if(unke0 == -1000.0f && mCurShot) b1 = true;
        if(b1){
            if(DirectedCut(mCurShot->Category()) || BFTB(mCurShot->Category())) b2 = true;
        }
        if(b2) f10 += 30.0f;

        int idxafter = skeys.FindFirstAfter(f10);
        if(idxafter < skeys.size()){
            f3c = skeys[idxafter].frame;
            if(f3c == f10){
                if(idxafter + 1 < skeys.size()){
                    float fr = skeys[idxafter + 1].frame;
                    f3c = fr;
                }
                else f3c = 1e+30f;
            }
        }
        if(f3c == 1e+30f) f3c = mEndOfSongSec * 30.0f;

        int dircutidxafter = mDircuts.FindFirstAfter(TheTaskMgr.Seconds(TaskMgr::b));
        if(dircutidxafter < mDircuts.size() && mDircuts[dircutidxafter].value){
            MinEq(f3c, mDircuts[dircutidxafter].frame * 30.0f);
        }
        return DataNode(f3c - mPropAnim->GetFrame());
    }
}

void BandDirector::SetCharacterHideHackEnabled(bool b){
    int hack = BandCamShot::sHideAllCharactersHack - 1;
    bool hax = BandCamShot::sHideAllCharactersHack != 0;
    if(b) hack = BandCamShot::sHideAllCharactersHack + 1;
    BandCamShot::sHideAllCharactersHack = hack;
    if((hack != 0) == hax) return;
    unk58 = true;
    unke0 = -1000.0f;
}

BEGIN_PROPSYNCS(BandDirector)
    SYNC_PROP_SET(shot_5, mShotCategory, SetShot(_val.Sym(0), "shot_5"))
    SYNC_PROP_SET(shot_bg, mShotCategory, SetShot(_val.Sym(0), coop_bg))
    SYNC_PROP_SET(shot_bk, mShotCategory, SetShot(_val.Sym(0), coop_bk))
    SYNC_PROP_SET(shot_gk, mShotCategory, SetShot(_val.Sym(0), coop_gk))
    SYNC_PROP_SET(postproc, (Hmx::Object*)0, )
    SYNC_PROP_SET(lightpreset, verse, )
    SYNC_PROP_SET(lightpreset_keyframe, next, )
    SYNC_PROP_SET(world_event, none, ExportWorldEvent(_val.Sym(0)))
    SYNC_PROP(merger, mMerger)
    SYNC_PROP(disable_picking, mDisablePicking)
    SYNC_PROP(disabled, mDisabled)
    SYNC_PROP(lightpreset_interp_enabled, mLightPresetInterpEnabled)
    SYNC_PROP(excitement, mExcitement)
    SYNC_PROP(num_players_failed, mNumPlayersFailed)
    SYNC_PROP(cam_postproc, mCamPostProc)
    SYNC_PROP_SET(cur_shot, mCurShot, )
    SYNC_PROP_SET(cur_world, mCurWorld, )
    SYNC_PROP_SET(bass_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "bass"))
    SYNC_PROP_SET(drum_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "drum"))
    SYNC_PROP_SET(guitar_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "guitar"))
    SYNC_PROP_SET(mic_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "mic"))
    SYNC_PROP_SET(keyboard_intensity, Symbol("idle_realtime"), SendMessage(_val.Sym(0), "keyboard"))
    SYNC_PROP_SET(part2_sing, Symbol("singalong_off"), SendMessage(mSongPref ? GetModeInst(mSongPref->Part2Inst()) : GetModeInst("guitar"), _val.Sym(0)))
    SYNC_PROP_SET(part3_sing, Symbol("singalong_off"), SendMessage(mSongPref ? GetModeInst(mSongPref->Part3Inst()) : GetModeInst("bass"), _val.Sym(0)))
    SYNC_PROP_SET(part4_sing, Symbol("singalong_off"), SendMessage(mSongPref ? GetModeInst(mSongPref->Part4Inst()) : GetModeInst("drum"), _val.Sym(0)))
    SYNC_PROP_SET(crowd, Symbol("crowd_realtime"), SetCrowd(_val.Sym(0)))
    SYNC_PROP(propanim, mPropAnim)
    SYNC_PROP_SET(spot_bass, Symbol("off"), SetCharSpot(Symbol("bass"), _val.Sym(0)))
    SYNC_PROP_SET(spot_drums, Symbol("off"), SetCharSpot(Symbol("drums"), _val.Sym(0)))
    SYNC_PROP_SET(spot_guitar, Symbol("off"), SetCharSpot(Symbol("guitar"), _val.Sym(0)))
    SYNC_PROP_SET(spot_keyboard, Symbol("off"), SetCharSpot(Symbol("keyboard"), _val.Sym(0)))
    SYNC_PROP_SET(spot_vocal, Symbol("off"), SetCharSpot(Symbol("vocal"), _val.Sym(0)))
    SYNC_PROP_SET(stagekit_fog, Symbol("off"), SetFog(_val.Sym(0)))
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS