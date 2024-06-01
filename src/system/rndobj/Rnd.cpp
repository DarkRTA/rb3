#include "Rnd.h"
#include "obj/Object.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/AmbientOcclusion.h"
#include "rndobj/AnimFilter.h"
#include "rndobj/Cam.h"
#include "rndobj/CubeTex.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Dir.h"
#include "rndobj/Env.h"
#include "rndobj/Flare.h"
#include "rndobj/Fur.h"
#include "rndobj/Graph.h"
#include "rndobj/Group.h"
#include "rndobj/Lit.h"
#include "rndobj/Mat.h"
#include "rndobj/Mesh.h"
#include "rndobj/Movie.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Overlay.h"
#include "rndobj/Set.h"
#include "rndobj/ShaderOptions.h"
#include "rndobj/SoftParticles.h"
#include "rndobj/Text.h"
#include "rndobj/Trans.h"
#include "rndobj/TransProxy.h"
#include "types.h"
#include "utl/Option.h"
#include "utl/PoolAlloc.h"
#include "utl/Str.h"
#include "utl/Symbols.h"
#include <cstring>
#include <list>

bool gFailKeepGoing;
bool gFailRestartConsole;
// int gpDbgFrameID;

namespace {
    bool AddToNotifies(const char* add, std::list<class String>& notifies) {
        u32 i = 0;
        if (notifies.size() > 16) return false;
        for (std::list<class String>::iterator it = notifies.begin(); it != notifies.end(); it++) {
            bool strFound = !strcmp(it->c_str(), add);
            if (strFound) return false;
        }
        class String s(add);
        notifies.push_back(s);
        return true;
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

void Rnd::Modal(bool& b, char* c, bool bb){
    if(bb) TheDebug << MakeString("%s\n", c);
}

Rnd::Rnd() : mClearColor(0.3f, 0.3f, 0.3f), mWidth(640), mHeight(480), mScreenBpp(16), mDrawCount(0), mDrawTimer(), 
    mTimersOverlay(0), mRateOverlay(0), mHeapOverlay(0), mStatsOverlay(0), unk84(0), unk88(0), unk8c(0), unk90(0), unk94(0), unk98(0), unk9c(0),
    unkc0(0.0f), unkc8(6), mFrameID(0), unkd0("    "), mSync(1), unkdc(0), unkdd(0), unkde(0), unkdf(1), mAspect(kWidescreen), unk_0xE4(0),
    unke8(0), unke9(0), mShrinkToSafe(1), mInGame(0), unkec(0), unked(0), unkee(0), unkef(0), unkf0(0), unkf4(0), unkf8(0), mPostProcOverride(0),
    unk110(this, kObjListNoNull), mDraws(this, kObjListNoNull), unk130(0), unk131(1), mProcCounter(), unk14c(7), unk150(7), unk15c(-1) {
    for(int i = 0; i < 8; i++) unk_arr[i] = 0;
    gpDbgFrameID = (int*)&mFrameID;
}

float Rnd::YRatio() {
    static const float kRatio[4] = {1.0f, 0.75f, 0.5625f, 0.5625f}; // qualifiers :)
    return kRatio[mAspect];
}

void TerminateCallback() {

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
    MILO_ASSERT((mScreenBpp == 16) || (mScreenBpp == 32), 575);
    SetupFont();
    RndGraph::Init();
    REGISTER_OBJ_FACTORY(DOFProc)
    RndTransformable::Init();
    REGISTER_OBJ_FACTORY(RndSet)
    REGISTER_OBJ_FACTORY(RndAnimFilter)
    REGISTER_OBJ_FACTORY(RndFlare)
    REGISTER_OBJ_FACTORY(RndCam)
    REGISTER_OBJ_FACTORY(RndMesh)
    // MeshDeform
    RndText::Init();
    REGISTER_OBJ_FACTORY(RndFont)
    REGISTER_OBJ_FACTORY(RndEnviron)
    REGISTER_OBJ_FACTORY(RndMat)
    REGISTER_OBJ_FACTORY(RndTex)
    REGISTER_OBJ_FACTORY(RndFur)
    REGISTER_OBJ_FACTORY(RndCubeTex)
    REGISTER_OBJ_FACTORY(RndSoftParticles)
    REGISTER_OBJ_FACTORY(RndAmbientOcclusion)
    REGISTER_OBJ_FACTORY(RndMovie)
    REGISTER_OBJ_FACTORY(RndLight)

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
    unkdc = mTimersOverlay->mShowing;
    CreateDefaults();
    // InitParticleSystem() - from rndobj/Part.cpp
    DataRegisterFunc("keep_going", FailKeepGoing);
    DataRegisterFunc("restart_console", FailRestartConsole);
    // RndUtlInit()
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

void Rnd::UnregisterPostProcessor(PostProcessor* p){
    for(std::list<PostProcessor*>::iterator it = mPostProcessors.begin(); it != mPostProcessors.end(); it++){
        if(p == *it) mPostProcessors.erase(it);
    }
}

void Rnd::SetPostProcOverride(RndPostProc* pp){
    mPostProcOverride = pp;
}

PostProcessor* Rnd::GetPostProcOverride() const { return mPostProcOverride; }

float Rnd::UpdateOverlay(RndOverlay* ovl, float f) {
    if (ovl == mRateOverlay) UpdateRate(); 
    else if (ovl == mHeapOverlay) UpdateHeap(); 
    else if (ovl == mTimersOverlay) f = DrawTimers(f);
    return f;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Rnd)
    HANDLE_EXPR(aspect, mAspect)
    HANDLE_EXPR(screen_width, mWidth)
    HANDLE_EXPR(screen_height, mHeight)
    HANDLE(screen_dump, OnScreenDump)
    HANDLE(screen_dump_unique, OnScreenDumpUnique)
    HANDLE(scale_object, OnScaleObject)
    HANDLE(reflect, OnReflect)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(1832)
END_HANDLERS
#pragma pop
