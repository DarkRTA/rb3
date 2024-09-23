#include "bandobj/BandPatchMesh.h"
#include "utl/Symbols.h"

BandPatchMesh::BandPatchMesh(Hmx::Object* o) : mMeshes(o), mRenderTo(true), mSrc(o, 0), mCategory(0) {

}

BEGIN_CUSTOM_PROPSYNC(BandPatchMesh::MeshPair::PatchPair)
    SYNC_PROP(patch, o.mPatch)
    SYNC_PROP(tex, o.mTex)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandPatchMesh::MeshPair)
    SYNC_PROP(mesh, o.mesh)
    SYNC_PROP(patches, o.mPatches)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandPatchMesh)
    SYNC_PROP(meshes, o.mMeshes)
    SYNC_PROP(src, o.mSrc)
    SYNC_PROP(render_to, o.mRenderTo)
    SYNC_PROP(category, o.mCategory)
END_CUSTOM_PROPSYNC