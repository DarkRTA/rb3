#pragma once
#include "char/CharBonesMeshes.h"
#include "char/CharClip.h"
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "rndobj/MeshAnim.h"
#include <vector>

class BandHeadShaper {
public:
    BandHeadShaper();
    ~BandHeadShaper();

    bool Start(ObjectDir*, Symbol, RndMesh*, SyncMeshCB*, bool);
    void AddDegrees(const char*, int, float*, int);
    void AddFrame(const char*, int, float);
    void AddChildBones(RndTransformable*);
    void Reskin();
    void End();

    static ObjectDir* GetViseme(Symbol, bool);
    static int GetCount(Symbol);
    static void Init();
    static void Terminate();

    static int sNoseNum;
    static int sMouthNum;
    static int sEyeNum;
    static int sShapeNum;
    static int sChinNum;

    RndMesh* mDst; // 0x0
    ObjectDir* mHeadDir; // 0x4
    RndMeshAnim* mAnim; // 0x8
    CharClip* mBase; // 0xc
    CharBonesMeshes* mBones; // 0x10
    std::vector<int>* mMapping; // 0x14
    std::vector<RndTransformable*> unk18; // 0x18
    bool mBonesOnly; // 0x20
};