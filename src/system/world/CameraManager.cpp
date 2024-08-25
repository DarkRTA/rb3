#include "world/CameraManager.h"
#include "world/Dir.h"
#include "rndobj/DOFProc.h"
#include "rndwii/Rnd.h"
#include "utl/Symbols.h"

Rand CameraManager::sRand(0);
int CameraManager::sSeed;
int gCooldown; // might need to change type

CameraManager::CameraManager(WorldDir* dir) : mParent(dir), mNextShot(dir, 0), mCurrentShot(dir, 0), unk2c(0.0f), mFreeCam(0) {
    MILO_ASSERT(mParent, 0x28);
    DOFProc::Init();
}

CameraManager::~CameraManager(){
    StartShot_(0);
    if(TheDOFProc) TheDOFProc->UnSet();
    RELEASE(mFreeCam);
}

void CameraManager::FirstShotOk(Symbol s){
    static Message first_shot_ok("first_shot_ok", DataNode(""));
    first_shot_ok[0] = DataNode(s);
    mParent->HandleType(first_shot_ok);
}

Symbol CameraManager::MakeCategoryAndFilters(DataArray* da, std::vector<PropertyFilter>& filts){
    Symbol sym = da->Sym(2);
    if(da->Size() > 3){
        DataArray* arr = da->Array(3);
        for(int i = 0; i < arr->Size(); i++){
            DataArray* currArr = arr->Array(i);
            PropertyFilter filt;
            filt.n1 = currArr->Evaluate(0);
            bool b1 = false;
            if(filt.n1.Type() == kDataSymbol){
                if(filt.n1.Sym(0) == flags_exact){
                    b1 = true;
                }
            }
            if(b1){
                filt.unk10 = currArr->Int(1);
                filt.n2 = DataNode(currArr->Int(2));
            }
            else {
                b1 = false;
                if(filt.n1.Type() == kDataSymbol){
                    if(filt.n1.Sym(0) == flags_any){
                        b1 = true;
                    }
                }
                if(b1){
                    filt.unk10 = currArr->Int(1);
                    filt.n2 = DataNode(1);
                }
                else {
                    filt.n2 = currArr->Evaluate(1);
                    filt.unk10 = -1;
                }
            }
            filts.push_back(filt);
        }
    }
    return sym;
}

DataNode CameraManager::OnPickCameraShot(DataArray* da){
    std::vector<PropertyFilter> pvec;
    pvec.reserve(20);
    return DataNode(PickCameraShot(MakeCategoryAndFilters(da, pvec), pvec));
}

void CameraManager::ForceCameraShot(CamShot* shot){
    mNextShot = shot;
}

void CameraManager::StartShot_(CamShot* shot){
    if(mCurrentShot) mCurrentShot->EndAnim();
    mCurrentShot = shot;
    if(mCurrentShot){
        mCurrentShot->StartAnim();
        unk2c = TheTaskMgr.Time(shot->Units());
    }
    static DataNode& venue_test = DataVariable("venue_test");
    if(venue_test != DataNode(1)){
        TheWiiRnd.SetTriFrameRendering(true);
        gCooldown = 0;
    }
}

CamShot* CameraManager::ShotAfter(CamShot* cshot){
    ObjDirItr<CamShot> it(mParent, true);
    CamShot* ret = it;
    for(; it != 0 && it != cshot; ++it);
    if(it) ++it;
    if(it) ret = it;
    return ret;
}

DataNode CameraManager::OnCycleShot(DataArray* da){
    CamShot* after = ShotAfter(mCurrentShot);
    if(after) ForceCameraShot(after);
    return DataNode(0);
}

FreeCamera* CameraManager::GetFreeCam(int padnum){
    if(!mFreeCam){
        mFreeCam = new FreeCamera(mParent, 0.001f, 0.2f, 0);
        mFreeCam->SetPadNum(padnum);
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
#ifdef VERSION_SZBE69_B8
    MessageTimer timer((MessageTimer::Active()) ? dynamic_cast<Hmx::Object*>(this) : 0, sym);
#endif
    HANDLE(pick_shot, OnPickCameraShot)
    HANDLE(find_shot, OnFindCameraShot)
    HANDLE_ACTION(force_shot, ForceCameraShot(_msg->Obj<CamShot>(2)))
    HANDLE_EXPR(current_shot, CurrentShot())
    HANDLE_EXPR(next_shot, NextShot())
    HANDLE_EXPR(get_free_cam, GetFreeCam(_msg->Int(2)))
    HANDLE_EXPR(has_free_cam, HasFreeCam())
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