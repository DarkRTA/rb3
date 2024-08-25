#include "world/CameraManager.h"
#include "world/Dir.h"
#include "rndobj/DOFProc.h"
#include "utl/Symbols.h"

CameraManager::CameraManager(WorldDir* dir) : mParent(dir), unk8(0), unkc(0), unk10(0), mNextShot(dir, 0), mCurrentShot(dir, 0), unk2c(0.0f), mFreeCam(0) {
    MILO_ASSERT(mParent, 0x28);
    DOFProc::Init();
}

CameraManager::~CameraManager(){
    StartShot_(0);
    TheDOFProc->UnSet();
}

DataNode CameraManager::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? dynamic_cast<Hmx::Object*>(this) : 0, sym);
    HANDLE(pick_shot, OnPickCameraShot)
    HANDLE(find_shot, OnFindCameraShot)
    HANDLE_ACTION(force_shot, ForceCameraShot(_msg->Obj<CamShot>(2)))
    HANDLE_EXPR(current_shot, mCurrentShot)
    HANDLE_EXPR(next_shot, mNextShot)
    HANDLE_EXPR(get_free_cam, GetFreeCam(_msg->Int(2)))
    HANDLE_EXPR(has_free_cam, mFreeCam != 0)
    HANDLE_ACTION(delete_free_cam, DeleteFreeCam())
    HANDLE(cycle_shot, OnCycleShot)
    HANDLE_EXPR(shot_after, ShotAfter(_msg->Obj<CamShot>(2)))
    HANDLE(camera_random_seed, OnRandomSeed)
    HANDLE(iterate_shot, OnIterateShot)
    HANDLE(num_shots, OnNumCameraShots)
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x242, PathName(dynamic_cast<Hmx::Object*>(this)), sym);
END_HANDLERS