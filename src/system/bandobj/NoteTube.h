#ifndef BANDOBJ_NOTETUBE_H
#define BANDOBJ_NOTETUBE_H

#include "rndobj/Mesh.h"
#include "obj/Object.h"
#include <vector>

class TubePlate {
    public:
    TubePlate(int);
    ~TubePlate();
    void Bake();
    void Reset();

    RndMesh* unk_0x0;
    u32 unk_0x4, unk_0x8;
    f32 unk_0xC, unk_0x10;
    u8 unk_0x14;
    f32 unk_0x18, unk_0x1C, unk_0x20;
    u8 unk_0x24;
};

class NoteTube : public Hmx::Object {
public:
    NoteTube();
    virtual ~NoteTube() {} // in VocalTrack

    bool unk_0x1C;
    int unk_0x20;
    bool unk_0x24;
    int mGlowLevel; 
    u8 unk_0x2C, unk_0x2D;
    float unk_0x30, unk_0x34, unk_0x38;
    u32 unk_0x3C, unk_0x40; 
    TubePlate* unk_0x44, *unk_0x48;
    u32 unk_0x4C, unk_0x50;
    float unk_0x54;
    std::vector<Vector3> mPoints;
    float unk_0x60;

    void SetNumPoints(int);
    void SetPointPos(int, Vector3);
    void SetGlowLevel(int);
    int NumGlowLevels() const { return 4; }
    void BakePlates();
};

#endif // BANDOBJ_NOTETUBE_H