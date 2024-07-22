#include "char/CharMeshCacheMgr.h"
#include "os/Debug.h"

inline MeshCacher::MeshCacher(RndMesh* mesh, bool b) : mMesh(mesh), unk4(0), mDisabled(b) {
    MILO_ASSERT(mMesh, 0x10E);
}

CharMeshCacheMgr::CharMeshCacheMgr() : mCache(), mDisabled(0) {

}

CharMeshCacheMgr::~CharMeshCacheMgr(){

}

void CharMeshCacheMgr::Disable(bool disable){
    MILO_ASSERT(mCache.empty(), 0x178);
    mDisabled = disable;
}

bool CharMeshCacheMgr::HasMesh(RndMesh* mesh){
    for(int i = 0; i < mCache.size(); i++){
        if(mesh == mCache[i]->mMesh) return true;
    }
    return false;
}

const std::vector<RndMesh::Vert>& CharMeshCacheMgr::GetVerts(RndMesh* mesh) const {
    for(int i = 0; i < mCache.size(); i++){
        if(mesh == mCache[i]->mMesh){
            return mCache[i]->unkc;
        }
    }
    return *(std::vector<RndMesh::Vert>*)0;
}

// 804f0f10 - syncmesh
void CharMeshCacheMgr::SyncMesh(RndMesh* mesh, int mask){
    int idx = 0;
    for(int i = 0; i < mCache.size(); i++){
        if(mCache[idx++]->mMesh == mesh) break;
    }
    if(idx == mCache.size()){
        mCache.push_back(new MeshCacher(mesh, mDisabled));
    }
    // mCache[idx].somemethodthatsinlined - fn_804F0FD0
}

void CharMeshCacheMgr::StuffMeshes(ObjPtrList<RndMesh, ObjectDir>& meshlist){
    for(int i = 0; i < mCache.size(); i++){
        meshlist.push_back(mCache[i]->mMesh);
    }
}