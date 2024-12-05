#include "world/CameraManager.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include "world/CameraShot.h"
#include "world/Dir.h"
#include "rndobj/DOFProc.h"
#include "rndwii/Rnd.h"
#include "utl/Symbols.h"
#include "utl/VectorSizeDefs.h"
#include <algorithm>

Rand CameraManager::sRand(0);
int CameraManager::sSeed;
int gCooldown; // might need to change type

CameraManager::CameraManager(WorldDir* dir) : mParent(dir), mNextShot(dir, 0), mCurrentShot(dir, 0), mCamStartTime(0.0f), mFreeCam(0) {
    MILO_ASSERT(mParent, 0x28);
    DOFProc::Init();
}

CameraManager::~CameraManager(){
    StartShot_(0);
    if(TheDOFProc) TheDOFProc->UnSet();
    RELEASE(mFreeCam);
    for(std::vector<Category VECTOR_SIZE_LARGE>::iterator it = mCameraShotCategories.begin(); it != mCameraShotCategories.end(); ++it){
        delete it->unk4;
    }
}

ObjPtrList<CamShot>& CameraManager::FindOrAddCategory(Symbol cat){
    Category targetCat;
    targetCat.unk0 = cat;
    Category* lowerCat = std::lower_bound(mCameraShotCategories.begin(), mCameraShotCategories.end(), targetCat);
    if(lowerCat == mCameraShotCategories.end() || lowerCat->unk0 != cat){
        targetCat.unk4 = new ObjPtrList<CamShot>(mParent, kObjListNoNull);
        mCameraShotCategories.push_back(targetCat);
        std::sort(mCameraShotCategories.begin(), mCameraShotCategories.end());
        lowerCat = std::lower_bound(mCameraShotCategories.begin(), mCameraShotCategories.end(), targetCat);
    }
    return *lowerCat->unk4;
}

void CameraManager::RandomizeCategory(ObjPtrList<CamShot>& camlist){
    std::vector<CamShot*> camshots;
    {
        MemDoTempAllocations m(true, false);
        camshots.resize(camlist.size());
    }
    int idx = 0;
    for(ObjPtrList<CamShot>::iterator it = camlist.begin(); it != camlist.end(); ++it){
        camshots[idx++] = *it;
    }
    std::sort(camshots.begin(), camshots.end(), NameSort());
    for(int i = 0; i < camshots.size(); i++){
        int randIdx = sRand.Int(i, camshots.size());
        std::swap( camshots[i], camshots[randIdx]);
    }
    camlist.clear();
    for(int i = 0; i < idx; i++){
        camlist.push_back(camshots[i]);
    }
}

void CameraManager::Randomize(){
    sRand.Seed(sSeed);
    for(std::vector<Category VECTOR_SIZE_LARGE>::iterator it = mCameraShotCategories.begin(); it != mCameraShotCategories.end(); ++it){
        RandomizeCategory(*it->unk4);
    }
}

void CameraManager::SyncObjects(){
    mCameraShotCategories.clear();
    mCameraShotCategories.reserve(100);
    for(ObjDirItr<CamShot> it(mParent, true); it != 0; ++it){
        if(it->PlatformOk()){
            FindOrAddCategory(it->Category()).push_back(it);
        }
    }
    Randomize();
}

bool CameraManager::ShotMatches(CamShot* shot, const std::vector<PropertyFilter>& filts){
    int flags = shot->Flags();
    for(std::vector<PropertyFilter>::const_iterator it = filts.begin(); it != filts.end(); ++it){
        DataNode d28;
        if(it->prop.Type() == kDataArray){
            d28 = shot->Property(it->prop.Array(), true)->Evaluate();
        }
        else {
            Symbol sym = it->prop.Sym();
            if(sym == flags_exact) d28 = flags & it->mask;
            else if(sym == flags_any) d28 = (flags & it->mask) != 0;
            else d28 = shot->Property(sym, true)->Evaluate();
        }

        if(it->match.Type() == kDataArray){
            DataArray* arr = it->match.Array();
            uint idx;
            for(idx = 0; idx != arr->Size(); idx++){
                if(d28 == arr->Node(idx)) break;
            }
            if(idx == arr->Size()) return false;
        }
        else if(d28 != it->match) return false;
    }
    return true;
}

CamShot* CameraManager::PickCameraShot(Symbol s, const std::vector<PropertyFilter>& filts){
    CamShot* shot = FindCameraShot(s, filts);
    if(!shot){
#ifdef MILO_DEBUG
        String str("No acceptable camera shot:");
        str << " cat: " << s;
        for(std::vector<PropertyFilter>::const_iterator it = filts.begin(); it != filts.end(); ++it){
            str << " (" << it->prop << " " << it->match;
            if(it->prop == flags_any || it->prop == flags_exact){
                str << MakeString(" 0x%x", it->mask);
            }
            str << ")";
        }
        MILO_WARN(str.c_str());
#endif
        return 0;
    }
    else mNextShot = shot;
    return shot;
}

CamShot* CameraManager::FindCameraShot(Symbol s, const std::vector<PropertyFilter>& filts){
    FirstShotOk(s);
    ObjPtrList<CamShot, ObjectDir>& camlist = FindOrAddCategory(s);
    for(ObjPtrList<CamShot, ObjectDir>::iterator it = camlist.begin(); it != camlist.end(); ++it){
        CamShot* cur = *it;
        if(!cur->Disabled() && ShotMatches(cur, filts)){
            if(cur->ShotOk(mCurrentShot)){
                camlist.MoveItem(camlist.end(), camlist, it);
                return cur;
            }
        }
    }
    return 0;
}

int CameraManager::NumCameraShots(Symbol s, const std::vector<PropertyFilter>& filts){
    FirstShotOk(s);
    ObjPtrList<CamShot, ObjectDir>& camlist = FindOrAddCategory(s);
    int num = 0;
    for(ObjPtrList<CamShot, ObjectDir>::iterator it = camlist.begin(); it != camlist.end(); ++it){
        CamShot* cur = *it;
        if(cur->Disabled() == 0 && ShotMatches(cur, filts) && cur->ShotOk(mCurrentShot)) num++;
    }
    return num;
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
        for(uint i = 0; i != arr->Size(); i++){
            DataArray* currArr = arr->Array(i);
            PropertyFilter filt;
            filt.prop = currArr->Evaluate(0);
            bool b1 = false;
            if(filt.prop.Type() == kDataSymbol){
                if(filt.prop.Sym() == flags_exact){
                    b1 = true;
                }
            }
            if(b1){
                filt.mask = currArr->Int(1);
                filt.match = DataNode(currArr->Int(2));
            }
            else {
                b1 = false;
                if(filt.prop.Type() == kDataSymbol){
                    if(filt.prop.Sym() == flags_any){
                        b1 = true;
                    }
                }
                if(b1){
                    filt.mask = currArr->Int(1);
                    filt.match = DataNode(1);
                }
                else {
                    filt.match = currArr->Evaluate(1);
                    filt.mask = -1;
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
    Symbol sym = MakeCategoryAndFilters(da, pvec);
    return DataNode(PickCameraShot(sym, pvec));
}

DataNode CameraManager::OnFindCameraShot(DataArray* da){
    std::vector<PropertyFilter> pvec;
    pvec.reserve(20);
    Symbol sym = MakeCategoryAndFilters(da, pvec);
    return DataNode(FindCameraShot(sym, pvec));
}

DataNode CameraManager::OnNumCameraShots(DataArray* da){
    std::vector<PropertyFilter> pvec;
    pvec.reserve(20);
    Symbol sym = MakeCategoryAndFilters(da, pvec);
    return DataNode(NumCameraShots(sym, pvec));
}

void CameraManager::ForceCameraShot(CamShot* shot){
    mNextShot = shot;
}

void CameraManager::StartShot_(CamShot* shot){
    if(mCurrentShot) mCurrentShot->EndAnim();
    mCurrentShot = shot;
    if(mCurrentShot){
        mCurrentShot->StartAnim();
        mCamStartTime = TheTaskMgr.Time(shot->Units());
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
    if(LOADMGR_EDITMODE){
        static DataNode& anim = DataVariable("milo.anim");
        if(anim.Type() == kDataObject){
            return anim.Obj<CamShot>();
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
    return (ttime - mCamStartTime) * fpu;
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
#ifdef MILO_DEBUG
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

DataNode CameraManager::OnIterateShot(DataArray* da){
    DataNode* var = da->Var(2);
    DataNode d28(*var);
    for(std::vector<Category VECTOR_SIZE_LARGE>::iterator it = mCameraShotCategories.begin(); it != mCameraShotCategories.end(); ++it){
        for(ObjPtrList<CamShot, ObjectDir>::iterator lit = it->unk4->begin(); lit != it->unk4->end(); ++lit){
            *var = DataNode(*lit);
            for(int i = 3; i < da->Size(); i++){
                da->Command(i)->Execute();
            }
        }
    }
    *var = d28;
    return DataNode(0);
}
