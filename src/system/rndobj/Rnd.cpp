#include "Rnd.h"
#include "rndobj/ModalKeyListener.h"
#include "obj/Object.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/OSFuncs.h"
#include "os/System.h"
#include "rndobj/AmbientOcclusion.h"
#include "rndobj/AnimFilter.h"
#include "rndobj/Cam.h"
#include "rndobj/CamAnim.h"
#include "rndobj/CubeTex.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Dir.h"
#include "rndobj/Env.h"
#include "rndobj/EnvAnim.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Flare.h"
#include "rndobj/Fur.h"
#include "rndobj/Gen.h"
#include "rndobj/Graph.h"
#include "rndobj/Group.h"
#include "rndobj/HiResScreen.h"
#include "rndobj/Line.h"
#include "rndobj/Lit.h"
#include "rndobj/LitAnim.h"
#include "rndobj/Mat.h"
#include "rndobj/MatAnim.h"
#include "rndobj/Mesh.h"
#include "rndobj/MeshAnim.h"
#include "rndobj/MeshDeform.h"
#include "rndobj/Morph.h"
#include "rndobj/MotionBlur.h"
#include "rndobj/Movie.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/MultiMeshProxy.h"
#include "rndobj/Overlay.h"
#include "rndobj/Part.h"
#include "rndobj/PartAnim.h"
#include "rndobj/PartLauncher.h"
#include "rndobj/PollAnim.h"
#include "rndobj/PostProc.h"
#include "rndobj/PropAnim.h"
#include "rndobj/ScreenMask.h"
#include "rndobj/Set.h"
#include "rndobj/ShaderOptions.h"
#include "rndobj/SoftParticles.h"
#include "rndobj/TexBlendController.h"
#include "rndobj/TexBlender.h"
#include "rndobj/TexRenderer.h"
#include "rndobj/Text.h"
#include "rndobj/Trans.h"
#include "rndobj/TransAnim.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Utl.h"
#include "rndobj/Wind.h"
#include "types.h"
#include "utl/Cheats.h"
#include "utl/FileStream.h"
#include "utl/MemMgr.h"
#include "utl/Option.h"
#include "utl/PoolAlloc.h"
#include "utl/Str.h"
#include "utl/Symbols.h"
#include <cstring>
#include <list>

int gCurHeap = -1;
bool gNotifyKeepGoing;
bool gFailKeepGoing;
bool gFailRestartConsole;

BEGIN_HANDLERS(ModalKeyListener)
    HANDLE_MESSAGE(KeyboardKeyMsg)
    HANDLE_CHECK(0xF8)
END_HANDLERS

DataNode ModalKeyListener::OnMsg(const KeyboardKeyMsg& k){
    if(((DataArray*)k)->Int(2) == 0x12e){
        if(!GetEnabledKeyCheats() && !TheRnd->mConsole->mShowing){
            TheRnd->ShowConsole(true);
            return DataNode(0);
        }
        else return DataNode(kDataUnhandled, 0);
    }
    else {
        if(!TheRnd->mConsole->mShowing){
            gNotifyKeepGoing = true;
            return DataNode(0);
        }
        else return DataNode(kDataUnhandled, 0);
    }
}

static DataNode FailKeepGoing(DataArray*) {
    gFailKeepGoing = true;
    return DataNode();
}

static DataNode FailRestartConsole(DataArray*) {
    gFailRestartConsole = true;
    return DataNode();
}

void Rnd::ShowConsole(bool b) { mConsole->SetShowing(b); }
bool Rnd::ConsoleShowing() { return mConsole->mShowing; }

void WordWrap(const char*, int, char*, int){

}

void Rnd::Modal(bool& b, char* c, bool bb){
    if(bb) TheDebug << MakeString("%s\n", c);
    if(CanModal(b)){
        if(MainThread()){
            // timer stuff
            strcat(c, "Rnd::Modal");
        }
        char buf[0x1000];
        WordWrap(c, 0x5a, buf, 0x1000);
        if(!bb){
            strcat(buf, "\n\n-- Waiting on Stack Trace --\n");
        }
        else if(!b){
            strcat(buf, "\n\n-- Press any button to continue --\n");
        }
        else strcat(buf, "\n\n-- Program ended --\n");

        strcat(c, ""); // only here to generate the string in the pool
    }
}

Rnd::Rnd() : mClearColor(0.3f, 0.3f, 0.3f), mWidth(640), mHeight(480), mScreenBpp(16), mDrawCount(0), mDrawTimer(),
    mTimersOverlay(0), mRateOverlay(0), mHeapOverlay(0), mStatsOverlay(0), unk84(0), unk88(0), unk8c(0), mDefaultCam(0), unk94(0), unk98(0), unk9c(0),
    unkc0(0.0f), unkc8(6), mFrameID(0), unkd0("    "), mSync(1), mGsTiming(0), mShowSafeArea(0), unkde(0), unkdf(1), mAspect(kWidescreen), unk_0xE4(0),
    unke8(0), unke9(0), mShrinkToSafe(1), mInGame(0), unkec(0), mDisablePostProc(0), unkee(0), unkef(0), unkf0(0), unkf4(0), unkf8(0), mPostProcOverride(0),
    unk110(this, kObjListNoNull), mDraws(this, kObjListNoNull), unk130(0), unk131(1), mProcCounter(), mProcCmds(kProcessAll), mLastProcCmds(kProcessAll)
#ifdef MILO_DEBUG
    , mForceCharLod(-1) // jank it up!
#endif
    {
    for(int i = 0; i < 8; i++) unk_arr[i] = 0;
#ifdef MILO_DEBUG
    gpDbgFrameID = (int*)&mFrameID;
#endif
}

float Rnd::YRatio() {
    static const float kRatio[4] = {1.0f, 0.75f, 0.5625f, 0.5625f}; // qualifiers :)
    return kRatio[mAspect];
}

void TerminateCallback() {
    RndUtlTerminate();
    TheRnd->Terminate();
}

void Rnd::DrawRectScreen(const Hmx::Rect& r, const Hmx::Color& c1, RndMat* m, const Hmx::Color* c2, const Hmx::Color* c3){
    DrawRect(r, c1, m, c2, c3);
}

Vector2& Rnd::DrawString(const char*, const Vector2& v, const Hmx::Color&, bool){
    static Vector2 s;
    s = v;
    return s;
}

void Rnd::SetupFont(){
    mFont = SystemConfig("rnd", "font");
    for(int i = 0; i < 0x1a; i++){
        DataArray* cloned = CONST_ARRAY(mFont)->Node(i + 0x42).Array(mFont)->Clone(true, false, 0);
        for(int j = 0; j < cloned->Size(); j++){
            DataArray* jArr = cloned->Array(j);
            for(int k = 1; k < jArr->Size(); k += 2){
                jArr->Node(k) = DataNode(0.7f * jArr->Float(k) + 0.3f);
            }
        }
        mFont->Node(i + 0x62) = DataNode(cloned, kDataArray);
        cloned->Release();
    }
}

void Rnd::PreInit() {
    SetName("rnd", ObjectDir::sMainDir);
    TheDebug.AddExitCallback(TerminateCallback);
    DataArray* rndcfg = SystemConfig("rnd");
    rndcfg->FindData("bpp", mScreenBpp, true);
    rndcfg->FindData("height", mHeight, true);
    rndcfg->FindData("clear_color", mClearColor, true);
    rndcfg->FindData("sync", mSync, true);
    rndcfg->FindData("aspect", (int&)mAspect, true);
    if(OptionBool("widescreen", false)) mAspect = kWidescreen;

    // some other code
    mWidth = YRatio();

    MILO_ASSERT((mScreenBpp == 16) || (mScreenBpp == 32), 575);
    SetupFont();
    RndGraph::Init();
    RndUtlPreInit();
    DOFProc::Register();
    RndTransformable::Init();
    RndSet::Init();
    RndAnimFilter::Init();
    RndFlare::Init();
    RndCam::Init();
    RndMesh::Init();
    RndMeshDeform::Init();
    RndText::Init();
    RndFont::Init();
    RndEnviron::Init();
    RndMat::Init();
    RndTex::Init();
    RndFur::Init();
    RndCubeTex::Init();
    RndSoftParticles::Init();
    RndAmbientOcclusion::Init();
    RndMovie::Init();
    RndLight::Init();
    RndTransAnim::Init();
    RndLightAnim::Init();
    RndMeshAnim::Init();
    RndMatAnim::Init();
    RndTransProxy::Init();
    RndPartLauncher::Init();
    RndLine::Init();
    RndGenerator::Init();
    RndParticleSys::Init();
    RndParticleSysAnim::Init();
    RndMultiMesh::Init();
    RndMultiMeshProxy::Init();
    RndMorph::Init();
    RndCamAnim::Init();
    RndEnvAnim::Init();
    RndTransformable::Register();
    RndGroup::Init();
    RndDir::Init();
    RndMotionBlur::Init();
    RndTexBlendController::Init();
    RndTexBlender::Init();
    RndTexRenderer::Init();
    RndScreenMask::Init();
    RndPostProc::Init();
    RndOverlay::Init();
    RndPropAnim::Init();
    EventTrigger::Init();
    RndWind::Init();
    RndPollAnim::Init();

    InitShaderOptions();
    mRateOverlay = RndOverlay::Find("rate", true);
    mHeapOverlay = RndOverlay::Find("heap", true);
    mStatsOverlay = RndOverlay::Find("stats", true);
    mTimersOverlay = RndOverlay::Find("timers", true);
    mRateOverlay->SetCallback(this);
    mHeapOverlay->SetCallback(this);
    mStatsOverlay->SetCallback(this);
    mTimersOverlay->SetCallback(this);
    mConsole = new RndConsole();
    unkde = 0;
    unkdf = 1;
    mGsTiming = mTimersOverlay->mShowing;
    CreateDefaults();
    InitParticleSystem();
    DataRegisterFunc("keep_going", FailKeepGoing);
    DataRegisterFunc("restart_console", FailRestartConsole);
    RndUtlInit();
}

void Rnd::Init() {
    DataArray* syscfg = SystemConfig("rnd");
    DataArray* da = syscfg->FindArray("timer_stats", false);
    if (da) {
        if (da->Int(1)) {
            TheDebug << MakeString("");
            SetShowTimers(true, true);
        }
    }
}

void Rnd::Terminate() {
    gpDbgFrameID = 0;
    delete mConsole;
    mConsole = NULL;
    TheDebug.RemoveExitCallback(TerminateCallback);
    RndOverlay::Terminate();
    RndMultiMesh::Terminate();
    DOFProc::Terminate();
    SetName(NULL, NULL);
}

void Rnd::RegisterPostProcessor(PostProcessor* p){
    mPostProcessors.push_back(p);
}

void Rnd::UnregisterPostProcessor(PostProcessor* p){
    for(std::list<PostProcessor*>::iterator it = mPostProcessors.begin(); it != mPostProcessors.end(); it++){
        if(p == *it) mPostProcessors.erase(it);
    }
}

void Rnd::SetPostProcOverride(RndPostProc* pp){
    mPostProcOverride = pp;
}

PostProcessor* Rnd::GetPostProcOverride() const { return mPostProcOverride; }

void Rnd::EndWorld(){
    if(!unkdf){
        // function ptr stuff here?
        unkdf = true;
    }
}

void Rnd::DoWorldBegin(){
    if(mPostProcOverride) mPostProcOverride->BeginWorld();
    else for(std::list<PostProcessor*>::iterator it = mPostProcessors.begin(); it != mPostProcessors.end(); it++){
        (*it)->BeginWorld();
    }
}

void Rnd::CopyWorldCam(RndCam* cam){
    if(mProcCmds & 1){
        if(!cam) cam = RndCam::sCurrent;
        unk94->Copy(cam, Hmx::Object::kCopyShallow);
        unk94->SetTransParent(0, false);
        unkef = true;
    }
}

void Rnd::DoWorldEnd(){
    if(!unkef) CopyWorldCam(0);
    unkef = false;
    if(mPostProcOverride) mPostProcOverride->EndWorld();
    else for(std::list<PostProcessor*>::iterator it = mPostProcessors.begin(); it != mPostProcessors.end(); it++){
        (*it)->EndWorld();
    }
}

void Rnd::DoPostProcess(){
    if(!mDisablePostProc){
        if(mPostProcOverride) mPostProcOverride->DoPost();
        else for(std::list<PostProcessor*>::iterator it = mPostProcessors.begin(); it != mPostProcessors.end(); it++){
            (*it)->DoPost();
        }
    }
}

void Rnd::SetShowTimers(bool b1, bool b2){
    RndOverlay* o = mTimersOverlay;
    o->mShowing = b1;
    o->mTimer.Restart();
    unkec = b2;
    SetGSTiming(b1);
}

float Rnd::UpdateOverlay(RndOverlay* ovl, float f) {
    if (ovl == mRateOverlay) UpdateRate();
    else if (ovl == mHeapOverlay) UpdateHeap();
    else if (ovl == mTimersOverlay) f = DrawTimers(f);
    return f;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Rnd)
    HANDLE_ACTION(reset_postproc, RndPostProc::Reset())
    HANDLE_ACTION(set_postproc_override, SetPostProcOverride(_msg->Obj<RndPostProc>(2)))
    HANDLE_ACTION(set_dof_depth_scale, RndPostProc::DOFOverrides().SetDepthScale(_msg->Float(2)))
    HANDLE_ACTION(set_dof_depth_offset, RndPostProc::DOFOverrides().SetDepthOffset(_msg->Float(2)))
    HANDLE_ACTION(set_dof_min_scale, RndPostProc::DOFOverrides().SetMinBlurScale(_msg->Float(2)))
    HANDLE_ACTION(set_dof_min_offset, RndPostProc::DOFOverrides().SetMinBlurOffset(_msg->Float(2)))
    HANDLE_ACTION(set_dof_max_scale, RndPostProc::DOFOverrides().SetMaxBlurScale(_msg->Float(2)))
    HANDLE_ACTION(set_dof_max_offset, RndPostProc::DOFOverrides().SetMaxBlurOffset(_msg->Float(2)))
    HANDLE_ACTION(set_dof_width_scale, RndPostProc::DOFOverrides().SetBlurWidthScale(_msg->Float(2)))
    HANDLE_ACTION(set_dof_tint, DOFProc::SetDepthOfFieldTint(_msg->Int(2), Hmx::Color(_msg->Float(3), _msg->Float(4), _msg->Float(5))))
    HANDLE_ACTION(set_aspect, SetAspect((Aspect)_msg->Int(2)))
    HANDLE_EXPR(aspect, mAspect)
    HANDLE_EXPR(screen_width, mWidth)
    HANDLE_EXPR(screen_height, mHeight)
    HANDLE_EXPR(highlight_style, RndDrawable::GetHighlightStyle())
    HANDLE_ACTION(set_highlight_style, RndDrawable::SetHighlightStyle((HighlightStyle)_msg->Int(2)))
    HANDLE_EXPR(get_normal_display_length, RndDrawable::GetNormalDisplayLength())
    HANDLE_ACTION(set_normal_display_length, RndDrawable::SetNormalDisplayLength(_msg->Float(2)))
    HANDLE_EXPR(get_force_select_proxied_subparts, RndDrawable::GetForceSubpartSelection())
    HANDLE_ACTION(set_force_select_proxied_subparts, RndDrawable::SetForceSubpartSelection(_msg->Int(2)))
    HANDLE_ACTION(set_sync, SetSync(_msg->Int(2)))
    HANDLE_ACTION(set_shrink_to_safe, SetShrinkToSafeArea(_msg->Int(2)))
    HANDLE(show_console, OnShowConsole)
    HANDLE(toggle_timers, OnToggleTimers)
    HANDLE(toggle_overlay_position, OnToggleOverlayPosition)
    HANDLE(toggle_timers_verbose, OnToggleTimersVerbose)
    HANDLE(toggle_overlay, OnToggleOverlay)
    HANDLE_EXPR(show_safe_area, mShowSafeArea)
    HANDLE_ACTION(set_show_safe_area, mShowSafeArea = _msg->Int(2))
    HANDLE(show_overlay, OnShowOverlay)
    HANDLE(set_sphere_test, OnSetSphereTest)
    HANDLE_EXPR(overlay_showing, RndOverlay::Find(_msg->Str(2), true)->Showing())
    HANDLE_ACTION(hi_res_screen, TheHiResScreen->TakeShot("ur_hi", _msg->Int(2)))
    HANDLE_ACTION(proc_lock, SetProcAndLock(ProcAndLock() == 0))
    HANDLE_ACTION(set_in_game, SetInGame(_msg->Int(2)))
    HANDLE_ACTION(toggle_in_game, SetInGame(InGame() == 0))
    HANDLE(clear_color_r, OnClearColorR)
    HANDLE(clear_color_g, OnClearColorG)
    HANDLE(clear_color_b, OnClearColorB)
    HANDLE(clear_color_packed, OnClearColorPacked)
    HANDLE(set_clear_color, OnSetClearColor)
    HANDLE(set_clear_color_packed, OnSetClearColorPacked)
    HANDLE(screen_dump, OnScreenDump)
    HANDLE(screen_dump_unique, OnScreenDumpUnique)
    HANDLE(scale_object, OnScaleObject)
    HANDLE(reflect, OnReflect)
    HANDLE(toggle_heap, OnToggleHeap)
    HANDLE(test_draw_groups, OnTestDrawGroups)
    HANDLE_ACTION(test_texture_size, TestTextureSize(_msg->Obj<ObjectDir>(2), _msg->Int(3), _msg->Int(4), _msg->Int(5), _msg->Int(6), _msg->Int(7)))
    HANDLE_ACTION(test_texture_paths, TestTexturePaths(_msg->Obj<ObjectDir>(2)))
    HANDLE_ACTION(test_material_textures, TestMaterialTextures(_msg->Obj<ObjectDir>(2)))
    HANDLE_ACTION(set_gfx_mode, SetGfxMode((GfxMode)_msg->Int(2)))
    HANDLE_EXPR(default_cam, mDefaultCam)
    HANDLE_EXPR(last_proc_cmds, mLastProcCmds)
    HANDLE_EXPR(toggle_all_postprocs, mDisablePostProc = mDisablePostProc == 0)
    HANDLE_ACTION(recreate_defaults, CreateDefaults())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(force_lod, mForceCharLod = _msg->Int(2))
    HANDLE_CHECK(1832)
END_HANDLERS
#pragma pop

DataNode Rnd::OnShowOverlay(const DataArray* da){
    RndOverlay* o = RndOverlay::Find(da->Str(2), true);
    o->mShowing = da->Int(3);
    o->mTimer.Restart();
    if(da->Size() > 4){
        o->SetTimeout(da->Float(4));
    }
    return DataNode(0);
}

DataNode Rnd::OnToggleHeap(const DataArray*){
    int num = MemNumHeaps();
    RndOverlay* o = mHeapOverlay;
    if(!o->mShowing){
        o->mShowing = true;
        o->mTimer.Restart();
    }
    else {
        gCurHeap++;
        if(gCurHeap >= num){
            gCurHeap = -1;
            o->mShowing = false;
            o->mTimer.Restart();
        }
        else {
            o->mShowing = true;
            o->mTimer.Restart();
        }
    }
    return DataNode(0);
}

DataNode Rnd::OnReflect(const DataArray* da){
    RndOverlay* o = RndOverlay::Find(da->Sym(2), true);
    if(o->Showing()){
        TextStream* idk = TheDebug.SetReflect(o);
        for(int i = 3; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
        TheDebug.SetReflect(idk);
    }
    return DataNode(0);
}

DataNode Rnd::OnToggleOverlay(const DataArray* da){
    RndOverlay* o = RndOverlay::Find(da->Str(2), true);
    o->mShowing = o->mShowing == 0;
    o->mTimer.Restart();
    if(o->mShowing){
        o->mDumpCount = 1;
    }
    return DataNode(o->mShowing);
}

DataNode Rnd::OnToggleOverlayPosition(const DataArray*){
    RndOverlay::TogglePosition();
    return DataNode(0);
}

void Rnd::SetProcAndLock(bool b){
    mProcCounter.SetProcAndLock(b);
}

bool Rnd::ProcAndLock() const { return mProcCounter.mProcAndLock; }

void Rnd::ResetProcCounter(){
    if(unkde){
        mProcCounter.mCount = -1;
    }
    else mLastProcCmds = ProcessCmd(mLastProcCmds | kProcessWorld);
}

bool Rnd::GetEvenOddDisabled() const { return mProcCounter.mEvenOddDisabled; }
void Rnd::SetEvenOddDisabled(bool b){ mProcCounter.SetEvenOddDisabled(b); }

String UniqueFileName(const char*){

}

void Rnd::ScreenDump(const char* cc){
    RndTex* tex = Hmx::Object::New<RndTex>();
    RndBitmap bmap;
    tex->SetBitmap(0, 0, 0, RndTex::kFrontBuffer, 0, 0);
    tex->LockBitmap(bmap, true);
    FileStream fs(cc, FileStream::kWrite, true);
    if(fs.Fail()) MILO_WARN("Screenshot failed; could not open destination file (%s).", cc);
    else bmap.SaveBmp(&fs);
    delete tex;
}

void Rnd::ScreenDumpUnique(const char* cc){
    ScreenDump(UniqueFileName(cc).c_str());
}

DataNode Rnd::OnShowConsole(const DataArray*){
    ShowConsole(true);
    return DataNode(0);
}

DataNode Rnd::OnToggleTimers(const DataArray*){
    SetShowTimers(unkec || !mTimersOverlay->mShowing, false);
    return DataNode(0);
}

DataNode Rnd::OnToggleTimersVerbose(const DataArray*){
    SetShowTimers(unkec == 0, unkec == 0);
    return DataNode(0);
}

DataNode Rnd::OnClearColorR(const DataArray*){
    return DataNode(mClearColor.red);
}

DataNode Rnd::OnClearColorG(const DataArray*){
    return DataNode(mClearColor.green);
}

DataNode Rnd::OnClearColorB(const DataArray*){
    return DataNode(mClearColor.blue);
}

DataNode Rnd::OnClearColorPacked(const DataArray*){
    return DataNode((int)mClearColor.Pack());
}

DataNode Rnd::OnSetClearColor(const DataArray* da){
    SetClearColor(Hmx::Color(da->Float(2), da->Float(3), da->Float(4)));
    return DataNode(0);
}

DataNode Rnd::OnSetClearColorPacked(const DataArray* da){
    float red = (da->Int(2) & 255) / 255.0f;
    float green = ((da->Int(2) >> 8) & 255) / 255.0f;
    float blue = ((da->Int(2) >> 0x10) & 255) / 255.0f;
    SetClearColor(Hmx::Color(red, green, blue));
    return DataNode(0);
}

DataNode Rnd::OnScreenDump(const DataArray* da){
    ScreenDump(da->Str(2));
    return DataNode(0);
}

DataNode Rnd::OnScreenDumpUnique(const DataArray* da){
    ScreenDumpUnique(da->Str(2));
    return DataNode(0);
}

DataNode Rnd::OnScaleObject(const DataArray* da){
    RndScaleObject(da->GetObj(2), da->Float(3), da->Float(4));
    return DataNode(0);
}

DataNode Rnd::OnSetSphereTest(const DataArray* da){
    unk131 = da->Int(2);
    return DataNode(0);
}
