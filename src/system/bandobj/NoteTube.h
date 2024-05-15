#ifndef BANDOBJ_NOTETUBE_H
#define BANDOBJ_NOTETUBE_H

#include "obj/Object.h"
#include <vector>

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
    u32 unk_0x3C, unk_0x40, unk_0x44, unk_0x48, unk_0x4C, unk_0x50;
    float unk_0x54;
    std::vector<Vector3> mPoints;
    float unk_0x60;

    void SetNumPoints(int);
    void SetPointPos(int, Vector3);
    void SetGlowLevel(int);
    int NumGlowLevels() const { return 4; }
};

#endif // BANDOBJ_NOTETUBE_H