#ifndef CHAR_CHARMESHCACHEMGR_H
#define CHAR_CHARMESHCACHEMGR_H
#include <vector>

class RndMesh; // forward dec

class SyncMeshCB {
public:
    SyncMeshCB(){}
    virtual ~SyncMeshCB(){}
    virtual void SyncMesh(RndMesh*, int) = 0;
    virtual bool HasMesh(RndMesh*) = 0;
    virtual int GetVerts(RndMesh*) const = 0; // fix return type
};

class CharMeshCacheMgr : public SyncMeshCB {
public:
    CharMeshCacheMgr();
    virtual ~CharMeshCacheMgr();
    virtual void SyncMesh(RndMesh*, int);
    virtual bool HasMesh(RndMesh*);
    virtual int GetVerts(RndMesh*) const; // fix return type

    std::vector<int> mCache;
    bool mDisabled;
};

#endif
