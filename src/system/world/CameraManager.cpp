#include "world/CameraManager.h"
#include "world/Dir.h"
#include "rndobj/DOFProc.h"
#include "utl/Symbols.h"

int CameraManager::sSeed;

CameraManager::CameraManager(WorldDir* dir) : mParent(dir), mNextShot(dir, 0), mCurrentShot(dir, 0), unk2c(0.0f), mFreeCam(0) {
    MILO_ASSERT(mParent, 0x28);
    DOFProc::Init();
}

CameraManager::~CameraManager(){
    StartShot_(0);
    if(TheDOFProc) TheDOFProc->UnSet();
    RELEASE(mFreeCam);
}

CamShot* CameraManager::ShotAfter(CamShot* cshot){
    for(ObjDirItr<CamShot> it(mParent, true); it != 0; ++it){

    }
}

DataNode CameraManager::OnCycleShot(DataArray* da){
    CamShot* after = ShotAfter(mCurrentShot);
    if(after) ForceCameraShot(after);
    return DataNode(0);
}

FreeCamera* CameraManager::GetFreeCam(int padnum){
    if(!mFreeCam){
        mFreeCam = new FreeCamera(mParent, 0.001f, 0.2f, 0);
        mFreeCam->mPadNum = padnum;
    }
    return mFreeCam;
}

void CameraManager::DeleteFreeCam(){
    RELEASE(mFreeCam);
}

CamShot* CameraManager::MiloCamera(){
    if(TheLoadMgr.EditMode()){
        static DataNode& anim = DataVariable("milo.anim");
        if(anim.Type() == kDataObject){
            return anim.Obj<CamShot>(0);
        }
    }
    return 0;
}

void CameraManager::PrePoll(){
    if(!MiloCamera()){
        if(mNextShot){
            StartShot_(mNextShot);
            mNextShot = 0;
        }
        if(mCurrentShot){
            mCurrentShot->SetPreFrame(CalcFrame(), 1.0f);
        }
    }
}

float CameraManager::CalcFrame(){
    float ttime = TheTaskMgr.Time(mCurrentShot->Units());
    float fpu = mCurrentShot->FramesPerUnit();
    return (ttime - unk2c) * fpu;
}

void CameraManager::Enter(){
    StartShot_(0);
    DeleteFreeCam();
}

void CameraManager::Poll(){
    if(!MiloCamera()){
        if(mCurrentShot){
            mCurrentShot->SetFrame(CalcFrame(), 1.0f);
        }
        if(mFreeCam) mFreeCam->Poll();
    }
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

DataNode CameraManager::OnRandomSeed(DataArray* da){
    sSeed = da->Int(2);
    return DataNode(0);
}