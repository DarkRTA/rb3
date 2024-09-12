#pragma once
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"
#include "rndobj/Text.h"
#include "rndobj/Mat.h"
#include "rndobj/MatAnim.h"
#include "rndobj/Trans.h"

class ArpeggioShape {
public:
    ArpeggioShape(RndGroup*, RndMesh*, RndText*, RndText*, RndMat*, RndMatAnim*);
    ~ArpeggioShape();

    void UnhookFromParentGroup();

    RndTransformable* unk0; // 0x0
    RndGroup* mParentGroup; // 0x4
    RndMesh* unk8; // 0x8
    RndText* unkc; // 0xc
    RndText* unk10; // 0x10
    RndMat* unk14; // 0x14
    RndMatAnim* unk18; // 0x18
};

class ArpeggioShapePool {
public:
    ArpeggioShapePool(ObjectDir*, RndGroup*, int);
    ~ArpeggioShapePool();

    void CreateArpeggioShape();

    std::list<ArpeggioShape*> mShapes; // 0x0
    RndMesh* mChordShapeMesh; // 0x8
    RndText* mFretNumbersChord; // 0xc
    RndText* mChordLabel; // 0x10
    RndGroup* mShapesGroup; // 0x14
    RndMat* mChordShapeMat; // 0x18
    RndMatAnim* mFadeMatAnim; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
};