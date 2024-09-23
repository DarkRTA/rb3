#ifndef CHAR_CHARMESHCACHEMGR_H
#define CHAR_CHARMESHCACHEMGR_H
#include "rndobj/Mesh.h"
#include <vector>

// size: 0x24
class MeshCacher {
public:
    MeshCacher(RndMesh*, bool);

    RndMesh* mMesh; // 0x0
    int unk4; // 0x4
    bool mDisabled; // 0x8
    std::vector<RndMesh::Vert> unkc; // 0xc
    std::vector<int> unk14; // 0x14
    std::vector<int> unk1c; // 0x1c
};

class CharMeshCacheMgr : public SyncMeshCB {
public:
    CharMeshCacheMgr();
    virtual ~CharMeshCacheMgr();
    virtual void SyncMesh(RndMesh*, int);
    virtual bool HasMesh(RndMesh*);
    virtual const std::vector<RndMesh::Vert>& GetVerts(RndMesh*) const; // fix return type

    void Disable(bool);
    void StuffMeshes(ObjPtrList<RndMesh, ObjectDir>&);

    std::vector<MeshCacher*> mCache; // 0x4
    bool mDisabled; // 0xc
};

#endif
