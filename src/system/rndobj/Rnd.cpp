#include "Rnd.h"
#include "obj/Object.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
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
#include "rndobj/Text.h"
#include "rndobj/Trans.h"
#include "rndobj/TransProxy.h"
#include "types.h"
#include "utl/PoolAlloc.h"
#include "utl/Str.h"
#include "utl/Symbols.h"
#include <cstring>
#include <list>

bool gFailKeepGoing;
bool gFailRestartConsole;

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

Rnd::Rnd() : unk_0x20(0.3), unk_0x24(0.3), unk_0x28(0.3), unk_0x2C(1), mWidth(640), mHeight(480), 
    mDraws(this, kObjListNoNull) {}

float Rnd::YRatio() {
    static const float kRatio[4] = {1.0f, 0.75f, 0.5625f, 0.5625f}; // qualifiers :)
    return kRatio[mAspectRatio];
}

void TerminateCallback() {

}

void Rnd::PreInit() {
    SetName("rnd", ObjectDir::sMainDir);
    DataArray* rndcfg = SystemConfig("rnd");
    rndcfg->FindData("bpp", mScreenBpp, false);
    MILO_ASSERT((mScreenBpp == 16) || (mScreenBpp == 32), 575);
    RndGraph::Init();
    Hmx::Object::RegisterFactory(DOFProc::StaticClassName(), DOFProc::NewObject);
    RndTransformable::Init();
    Hmx::Object::RegisterFactory(RndSet::StaticClassName(), RndSet::NewObject);
    Hmx::Object::RegisterFactory(RndAnimFilter::StaticClassName(), RndAnimFilter::NewObject);
    Hmx::Object::RegisterFactory(RndFlare::StaticClassName(), RndFlare::NewObject);
    Hmx::Object::RegisterFactory(RndCam::StaticClassName(), RndCam::NewObject);
    Hmx::Object::RegisterFactory(RndMesh::StaticClassName(), RndMesh::NewObject);

    RndText::Init();
    Hmx::Object::RegisterFactory(RndFont::StaticClassName(), RndFont::NewObject);
    Hmx::Object::RegisterFactory(RndEnviron::StaticClassName(), RndEnviron::NewObject);
    Hmx::Object::RegisterFactory(RndMat::StaticClassName(), RndMat::NewObject);
    Hmx::Object::RegisterFactory(RndTex::StaticClassName(), RndTex::NewObject);
    Hmx::Object::RegisterFactory(RndFur::StaticClassName(), RndFur::NewObject);
    Hmx::Object::RegisterFactory(RndCubeTex::StaticClassName(), RndCubeTex::NewObject);
    Hmx::Object::RegisterFactory(RndMovie::StaticClassName(), RndMovie::NewObject);
    Hmx::Object::RegisterFactory(RndLight::StaticClassName(), RndLight::NewObject);

    Hmx::Object::RegisterFactory(RndTransProxy::StaticClassName(), RndTransProxy::NewObject);

    Hmx::Object::RegisterFactory(RndMultiMesh::StaticClassName(), RndMultiMesh::NewObject);


    Hmx::Object::RegisterFactory(RndTransformable::StaticClassName(), RndTransformable::NewObject); // ?
    Hmx::Object::RegisterFactory(RndGroup::StaticClassName(), RndGroup::NewObject);
    Hmx::Object::RegisterFactory(RndDir::StaticClassName(), RndDir::NewObject);
    mConsole = new (_PoolAlloc(0x58, 0x58, FastPool)) RndConsole;
    DataRegisterFunc("keep_going", FailKeepGoing);
    DataRegisterFunc("restart_console", FailRestartConsole);
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

float Rnd::UpdateOverlay(RndOverlay* ovl, float f) {
    if (ovl == unk_0x74) UpdateRate(); else if (ovl == unk_0x78) UpdateHeap(); else if (ovl == unk_0x70) f = DrawTimers(f);
    return f;
}

#pragma dont_inline on

BEGIN_HANDLERS(Rnd)
    HANDLE_EXPR(aspect, mAspectRatio)
    HANDLE_EXPR(screen_width, mWidth)
    HANDLE_EXPR(screen_height, mHeight)
    HANDLE(screen_dump, OnScreenDump)
    HANDLE(screen_dump_unique, OnScreenDumpUnique)
    HANDLE(scale_object, OnScaleObject)
    HANDLE(reflect, OnReflect)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(1832)
END_HANDLERS

#pragma dont_inline reset

void Rnd::ReInit() {}