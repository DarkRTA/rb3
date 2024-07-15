#ifndef WORLD_CAMERAMANAGER_H
#define WORLD_CAMERAMANAGER_H
#include "obj/ObjPtr_p.h"
#include "world/CameraShot.h"

class WorldDir;

class CameraManager {
public:
    CameraManager(WorldDir*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CameraManager();

    void Enter();
    void PrePoll();
    void Poll();
    void SyncObjects();

    WorldDir* mParent;
    int unk8, unkc, unk10;
    ObjPtr<CamShot, class ObjectDir> unk14;
    ObjPtr<CamShot, class ObjectDir> unk20;
    float unk2c;
    int unk30;
};

#endif
