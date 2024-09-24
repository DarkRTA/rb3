#include "bandobj/BandPatchMesh.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(BandPatchMesh);

void BandPatchMesh::MeshVert::SetVert(const BandPatchMesh::MeshVert* mvert, const RndMesh::Vert* vert){
    mVert = vert;
    unk4 = mvert->unk4;
    unk10 = mvert->unk10;
    unk1c = mvert->unk1c;
    unk26 = mvert->unk26;
}

void BandPatchMesh::MeshVert::SetVert(const RndMesh::Vert* vert){
    mVert = vert;
    ZeroOut();
}

void BandPatchMesh::MeshVert::ZeroOut(){
    unk1c.Zero();
    unk4.Zero();
    unk10.Zero();
}

void BandPatchMesh::MeshVert::Normalize(int count){
    MILO_ASSERT(count > 0, 0x7E);
    unk1c /= count;
    Vector3 v40;
    Cross(unk4, unk10, v40);
    Hmx::Quat q50;
    MakeRotQuat(v40, mVert->norm, q50);
    Hmx::Matrix3 m34;
    MakeRotMatrix(q50, m34);
    Multiply(unk4, m34, unk4);
    Multiply(unk10, m34, unk10);
    ::Normalize(unk4, unk4);
    ::Normalize(unk10, unk10);
    Vector3 v5c;
    ::Add(unk4, unk10, v5c);
    ::Normalize(v5c, v5c);
    Vector3 v68;
    Cross(mVert->norm, v5c, v68);
    ::Normalize(v68, v68);
    ::Add(v5c, v68, unk10);
    Subtract(v5c, v68, unk4);
    ::Normalize(unk4, unk4);
    ::Normalize(unk10, unk10);
    unk26 = 0;
    if(unk1c.x < 0) unk26 |= 1;
    else if(unk1c.x > 1.0f) unk26 |= 2;
    if(unk1c.y < 0) unk26 |= 4;
    else if(unk1c.y > 1.0f) unk26 |= 8;
}

BandPatchMesh::BandPatchMesh(Hmx::Object* o) : mMeshes(o), mRenderTo(true), mSrc(o, 0), mCategory(0) {

}

void BandPatchMesh::SetRenderToVert(RndMesh::Vert& vert, const Vector2& pos, const Vector2& uv){
    vert.uv = uv;
    vert.pos.Set((pos.x - 0.5f) * 2.0f, (pos.y - 0.5f) * 2.0f, 0);
    vert.norm.Set(0,0,-1.0f);
    vert.boneWeights.Set(0,0,0,0);
    vert.color.Clear();
}

BinStream& operator>>(BinStream& bs, BandPatchMesh::MeshPair& mp){
    bs >> mp.mesh;
    return bs;
}

BinStream& operator>>(BinStream& bs, BandPatchMesh& mesh){
    int rev; bs >> rev;
    BandPatchMesh::gRev = getHmxRev(rev);
    BandPatchMesh::gAltRev = getAltRev(rev);
#ifdef MILO_DEBUG
    if(BandPatchMesh::gRev > 4){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(mesh.mSrc.Owner()), "BandPatchMesh", BandPatchMesh::gRev, (unsigned short)4);
    }
    if(BandPatchMesh::gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(mesh.mSrc.Owner()), "BandPatchMesh", BandPatchMesh::gAltRev, (unsigned short)0);
    }
#endif
    bs >> mesh.mSrc;
    if(BandPatchMesh::gRev > 3) bs >> mesh.mMeshes;
    else {
        mesh.mMeshes.resize(1);
        bs >> mesh.mMeshes[0].mesh;
    }
    if(BandPatchMesh::gRev < 1){
        Symbol s; bs >> s;
    }
    if(BandPatchMesh::gRev < 4){
        Symbol s; bs >> s;
    }
    if(BandPatchMesh::gRev > 1){
        if(BandPatchMesh::gRev > 2) bs >> mesh.mRenderTo;
        else {
            Symbol s; bs >> s;
            mesh.mRenderTo = !s.Null();
        }
    }
    if(BandPatchMesh::gRev > 3) bs >> mesh.mCategory;
    return bs;
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