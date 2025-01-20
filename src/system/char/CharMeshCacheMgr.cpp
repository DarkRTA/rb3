#include "char/CharMeshCacheMgr.h"
#include "os/Debug.h"

inline MeshCacher::MeshCacher(RndMesh* mesh, bool b) : mMesh(mesh), mFlags(0), mDisabled(b) {
    MILO_ASSERT(mMesh, 0x10E);
}

CharMeshCacheMgr::CharMeshCacheMgr() : mCache(), mDisabled(0) {

}

CharMeshCacheMgr::~CharMeshCacheMgr(){
    for(int i = 0; i < mCache.size(); i++){
        delete mCache[i];
    }
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

const std::vector<SyncMeshCB::Vert>& CharMeshCacheMgr::GetVerts(RndMesh* mesh) const {
    for(int i = 0; i < mCache.size(); i++){
        if(mesh == mCache[i]->mMesh){
            return mCache[i]->mVerts;
        }
    }
    return *(std::vector<SyncMeshCB::Vert>*)0;
}

// 804f0f10 - syncmesh
void CharMeshCacheMgr::SyncMesh(RndMesh* mesh, int mask){
    int i = 0;
    for(; i < mCache.size(); i++){
        if(mesh == mCache[i]->mMesh) break;
    }
    if(i == mCache.size()){
        mCache.push_back(new MeshCacher(mesh, mDisabled));
    }
    mCache[i]->Sync(mask);
}

void CharMeshCacheMgr::StuffMeshes(ObjPtrList<RndMesh>& meshlist){
    for(int i = 0; i < mCache.size(); i++){
        meshlist.push_back(mCache[i]->mMesh);
    }
}