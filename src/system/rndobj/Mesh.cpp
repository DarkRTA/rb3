#include "Mesh.h"
#include "obj/Object.h"
#include "rndobj/MultiMesh.h"
#include "utl/Symbols.h"

INIT_REVS(RndMesh)

int RndMesh::MaxBones() { return MAX_BONES; }

bool RndMesh::IsSkinned() const { return mBones.size(); }

RndMesh::RndMesh() : mMat(this, NULL), mOwner(this, this), mBones(this),
    unk_0xF0(0), unk_0xF4(1), unk_0xF8(0), unk_0xFC(0), unk_0x108(0), unk_0x10C(0), unk_0x110(0), unk_0x114(0),
    unk_0x118(0), unk_0x11C(0) {
    unk9p0 = false;
    unk9p1 = false;
    unk9p2 = true;
    unk9p3 = false;
}

RndMesh::Vert::Vert() : x(0), y(0), z(0), nx(0), ny(0), nz(0) {}

void RndMesh::PreLoadVertices(BinStream& bs) {
    if (gAltRev > 4) {
        unk_0x11C = new FileLoader("", "", kLoadFront, 0, true, true, &bs);
    }
}

RndMultiMesh* RndMesh::CreateMultiMesh() {
    RndMesh* m = &(*mOwner);
    if (!m->unk_0xFC) {
        m->unk_0xFC = Hmx::Object::New<RndMultiMesh>();
        m->unk_0xFC->SetMesh(m);
    }
    m->unk_0xFC->mInstances.resize(0);
    return m->unk_0xFC;
}

SAVE_OBJ(RndMesh, 1135)

int RndMesh::NumVerts() const { return mVerts.size(); }
int RndMesh::NumFaces() const { return mFaces.size(); }

BinStream& operator>>(BinStream& bs, RndMesh::Face& f) {
    bs >> f.idx0 >> f.idx1 >> f.idx2;
    if (RndMesh::gRev < 1) {
        int x, y, z;
        bs >> z >> y >> x;
    }
    return bs;
}

#pragma dont_inline on
BEGIN_HANDLERS(RndMesh)
    HANDLE(compare_edge_verts, OnCompareEdgeVerts)
    HANDLE(attach_mesh, OnAttachMesh)
    HANDLE(get_face, OnGetFace)
    HANDLE(set_face, OnSetFace)
    HANDLE(get_vert_pos, OnGetVertXYZ)
    HANDLE(set_vert_pos, OnSetVertXYZ)
    HANDLE(get_vert_norm, OnGetVertNorm)
    HANDLE(set_vert_norm, OnSetVertNorm)
    HANDLE(get_vert_uv, OnGetVertUV)
    HANDLE(set_vert_uv, OnSetVertUV)
    HANDLE_EXPR(num_bones, NumBones())
    HANDLE(unitize_normals, OnUnitizeNormals)
    HANDLE(point_collide, OnPointCollide)
    HANDLE(configure_mesh, OnConfigureMesh)
    HANDLE_EXPR(estimated_size_kb, EstimatedSizeKb())
    HANDLE_ACTION(clear_bones, CopyBones(NULL))
    HANDLE_ACTION(copy_geom_from_owner, CopyGeometryFromOwner())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(2306)
END_HANDLERS
#pragma dont_inline reset