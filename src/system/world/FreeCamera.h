#ifndef WORLD_FREECAMERA_H
#define WORLD_FREECAMERA_H
#include "obj/Object.h"

class WorldDir;
class RndTransformable;

class FreeCamera : public Hmx::Object {
public:
    FreeCamera(WorldDir*, float, float, int);
    virtual ~FreeCamera();
    virtual DataNode Handle(DataArray*, bool);

    void UpdateFromCamera();
    void SetParentDof(bool, bool, bool);
    void Poll();
    void SetPadNum(int p){ mPadNum = p; }

    RndTransformable* mParent; // 0x1c
    Vector3 mRot; // 0x20
    Transform mXfm; // 0x2c
    float mFov; // 0x5c
    bool mFrozen; // 0x60
    int mPadNum; // 0x64
    float mRotateRate; // 0x68
    float mSlewRate; // 0x6c
    int mFocalPlane; // 0x70
    bool mUseParentRotateX; // 0x74
    bool mUseParentRotateY; // 0x75
    bool mUseParentRotateZ; // 0x76
    WorldDir* mWorld; // 0x78
};

#endif
