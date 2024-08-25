#ifndef WORLD_CAMERAMANAGER_H
#define WORLD_CAMERAMANAGER_H
#include "obj/ObjPtr_p.h"
#include "world/CameraShot.h"
#include "world/FreeCamera.h"

class WorldDir;

class CameraManager {
public:
    class Category {
    public:
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

    DataNode OnPickCameraShot(DataArray*);
    DataNode OnFindCameraShot(DataArray*);
    DataNode OnCycleShot(DataArray*);
    DataNode OnRandomSeed(DataArray*);
    DataNode OnIterateShot(DataArray*);
    DataNode OnNumCameraShots(DataArray*);

    NEW_POOL_OVERLOAD(CameraManager)
    DELETE_POOL_OVERLOAD(CameraManager)
    static int sSeed;

    WorldDir* mParent; // 0x4
    std::vector<int, u32> unk8; // 0x8
    ObjPtr<CamShot, class ObjectDir> mNextShot; // 0x14
    ObjPtr<CamShot, class ObjectDir> mCurrentShot; // 0x20
    float unk2c; // 0x2c
    FreeCamera* mFreeCam; // 0x30
};

#endif
