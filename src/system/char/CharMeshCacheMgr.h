#pragma once
#include "rndobj/Mesh.h"
#include "utl/MemMgr.h"
#include <vector>

// size: 0x24
class MeshCacher {
public:
    MeshCacher(RndMesh*, bool);
    ~MeshCacher(){
        if(mMesh->KeepMeshData()){
            SyncMesh();
            mMesh->SetKeepMeshData(!mDisabled);
            if(!mDisabled) PopulateMesh();
        }
    }

    // TODO: rename these once you have a better idea of what they do
    void SyncMesh(){ mMesh->Sync(mFlags | 0xA0); }
    void Sync(int mask){
        mFlags |= mask;
        if(mFlags & 0x1F){
            if(mVerts.size() == 0){
                MemDoTempAllocations temp(true, false);
                mVerts.resize(mMesh->Verts().size());
                for(int i = 0; i < mVerts.size(); i++){
                    SyncMeshCB::Vert& curVert = mVerts[i];
                    curVert.pos = mMesh->VertAt(i).pos;
                    SyncMeshCB::Vert& curVert2 = mVerts[i];
                    curVert2.norm = mMesh->VertAt(i).norm;
                }
            }
        }
        if(mFlags & 0x20){
            if(mFaces.size() == 0){
                mFaces = mMesh->Faces();
            }
        }
        if(mFlags & 0x400 && mColors.size() == 0){
            MemDoTempAllocations temp(true, false);
            mColors.resize(mMesh->Verts().size());
            for(int i = 0; i < mVerts.size(); i++){
                Hmx::Color& curColor = mColors[i];
                curColor = mMesh->VertAt(i).color;
            }
        }
    }

    void PopulateMesh(){
        for(int i = 0; i < mVerts.size(); i++){
            RndMesh::Vert& curVert = mMesh->VertAt(i);
            curVert.pos = mVerts[i].pos;
            curVert.norm = mVerts[i].norm;
        }
        if(mFaces.size() != 0){
            mMesh->Faces() = mFaces;
        }
        for(int i = 0; i < mColors.size(); i++){
            RndMesh::Vert& curVert = mMesh->VertAt(i);
            curVert.color = mColors[i];
        }
    }

    RndMesh* mMesh; // 0x0
    int mFlags; // 0x4 - flags?
    bool mDisabled; // 0x8
    std::vector<SyncMeshCB::Vert> mVerts; // 0xc
    std::vector<RndMesh::Face> mFaces; // 0x14
    std::vector<Hmx::Color> mColors; // 0x1c
};

class CharMeshCacheMgr : public SyncMeshCB {
public:
    CharMeshCacheMgr();
    virtual ~CharMeshCacheMgr();
    virtual void SyncMesh(RndMesh*, int);
    virtual bool HasMesh(RndMesh*);
    virtual const std::vector<SyncMeshCB::Vert>& GetVerts(RndMesh*) const; // fix return type

    void Disable(bool);
    void StuffMeshes(ObjPtrList<RndMesh, ObjectDir>&);

    std::vector<MeshCacher*> mCache; // 0x4
    bool mDisabled; // 0xc
};
