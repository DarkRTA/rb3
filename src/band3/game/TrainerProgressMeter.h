#pragma once
#include "math/Mtx.h"
#include "rndobj/Dir.h"
#include "rndobj/Mesh.h"
#include <vector>

class TrainerProgressMeter {
public:
    TrainerProgressMeter();
    ~TrainerProgressMeter();
    void Init(RndDir*, int);

    std::vector<bool> mCompleted; // 0x0
    RndDir* mProgressMeter; // 0x8
    RndMesh* mBar; // 0xc
    Transform mBarTrans; // 0x10
    RndMesh* mGlow; // 0x40
    Transform mGlowTrans; // 0x44
    RndMesh* mBoxes; // 0x74
    int mCurrent; // 0x78
};
