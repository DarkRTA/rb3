#ifndef WORLD_CAMERAMANAGER_H
#define WORLD_CAMERAMANAGER_H
#include "obj/ObjPtr_p.h"

class WorldDir;

class CameraManager {
public:
    CameraManager(WorldDir*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~CameraManager();

    WorldDir* mParent;
};

#endif
