#ifndef WORLD_CAMERAMANAGER_H
#define WORLD_CAMERAMANAGER_H
#include "obj/ObjPtr_p.h"
#include "world/CameraShot.h"
#include "world/FreeCamera.h"
#include "math/Rand.h"

class WorldDir;

class CameraManager {
public:
    class Category {
    public:
        Symbol unk0;
        ObjPtrList<CamShot, ObjectDir>* unk4;
    };

    // size 0x14
    class PropertyFilter {
    public:
        PropertyFilter(){}
        DataNode prop; // 0x0
        DataNode match; // 0x8
        int mask; // 0x10
    };

    CameraManager(WorldDir*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CameraManager();

    void Enter();
    void PrePoll();
    void Poll();
    void SyncObjects();
    void StartShot_(CamShot*);
    void ForceCameraShot(CamShot*);
    FreeCamera* GetFreeCam(int);
    void DeleteFreeCam();
    CamShot* ShotAfter(CamShot*);
    CamShot* MiloCamera();
    float CalcFrame();
    void FirstShotOk(Symbol);

    bool ShotMatches(CamShot*, const std::vector<PropertyFilter>&);
    Symbol MakeCategoryAndFilters(DataArray*, std::vector<PropertyFilter>&);
    CamShot* PickCameraShot(Symbol, const std::vector<PropertyFilter>&);
    CamShot* FindCameraShot(Symbol, const std::vector<PropertyFilter>&);
    int NumCameraShots(Symbol, const std::vector<PropertyFilter>&);
    ObjPtrList<CamShot, ObjectDir>* FindOrAddCategory(Symbol);

    CamShot* NextShot() const { return mNextShot; }
    CamShot* CurrentShot() const { return mCurrentShot; }
    bool HasFreeCam() const { return mFreeCam; }

    DataNode OnPickCameraShot(DataArray*);
    DataNode OnFindCameraShot(DataArray*);
    DataNode OnCycleShot(DataArray*);
    DataNode OnRandomSeed(DataArray*);
    DataNode OnIterateShot(DataArray*);
    DataNode OnNumCameraShots(DataArray*);

    NEW_POOL_OVERLOAD(CameraManager)
    DELETE_POOL_OVERLOAD(CameraManager)
    static Rand sRand;
    static int sSeed;

    WorldDir* mParent; // 0x4
    std::vector<Category, u32> mCameraShotCategories; // 0x8
    ObjPtr<CamShot, class ObjectDir> mNextShot; // 0x14
    ObjPtr<CamShot, class ObjectDir> mCurrentShot; // 0x20
    float mCamStartTime; // 0x2c
    FreeCamera* mFreeCam; // 0x30
};

#endif
