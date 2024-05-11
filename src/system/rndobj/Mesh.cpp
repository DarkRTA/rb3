#include "Mesh.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Trans.h"
#include "utl/BufStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include <vector>

INIT_REVS(RndMesh)

int RndMesh::MaxBones() { return MAX_BONES; }

bool RndMesh::IsSkinned() const { return mBones.size(); }

void RndMesh::SetMat(RndMat* m) { mMat = m; }

RndMesh::RndMesh() : mMat(this, NULL), mOwner(this, this), mBones(this),
    unk_0xF0(0), unk_0xF4(1), unk_0xF8(0), unk_0xFC(0), unk_0x108(0), unk_0x10C(0), unk_0x110(0), unk_0x114(0),
    unk_0x118(0), unk_0x11C(0) {
    unk9p0 = false;
    unk9p1 = false;
    unk9p2 = true;
    unk9p3 = false;
}

RndMesh::Vert::Vert() : x(0), y(0), z(0), nx(0), ny(1), nz(0), unk_0x18(0), unk_0x1A(0), unk_0x1C(0), unk_0x1E(0),
    unk_0x20(-1), u(0), v(0), unk_0x2C(0), unk_0x2E(0), unk_0x30(0), unk_0x32(0) {}

void RndMesh::PreLoadVertices(BinStream& bs) {
    if (gAltRev > 4) {
        unk_0x11C = new FileLoader("", "", kLoadFront, 0, true, true, &bs);
    }
}

void RndMesh::PostLoadVertices(BinStream& bs) {
    void* buf; int len;
    if (unk_0x11C) {
        buf = (void*)unk_0x11C->GetBuffer(NULL);
        len = unk_0x11C->GetSize();
        delete unk_0x11C;
        unk_0x11C = NULL;
    }
    BufStream bfs(buf, len, true);
    if (buf) bs = bfs;
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

void RndMesh::Load(BinStream& bs) {
    PreLoad(bs);
    PostLoad(bs);
}

void RndMesh::PreLoad(BinStream& bs) {
    uint dump, asdf, fdsa, uuuuu;
    char blag[128];
    LOAD_REVS(bs)
    ASSERT_REVS(38, 6)
    if (gRev > 25) Hmx::Object::Load(bs);
    RndTransformable::Load(bs);
    RndDrawable::Load(bs);
    if (gRev < 15) {
        ObjPtrList<Hmx::Object, class ObjectDir> l(this, kObjListNoNull);
        bs >> dump >> l;
    }
    if (gRev < 20) {
        bs >> asdf >> fdsa;
    }
    if (gRev < 3) {
        bs >> uuuuu;
    }
    bs >> mMat;
    if (gRev == 27) {
        bs.ReadString(blag, 128); // allegedly this is for a second, funnier mat
        
        bs >> mOwner;
    }

    PreLoadVertices(bs);
}

#pragma dont_inline on
void RndMesh::PostLoad(BinStream& bs) {
    PostLoadVertices(bs);
    bs >> mFaces;
    if ((ushort)(gRev + 0xFFFB) <= 18) {
        int i; u16 a,b;
        for (bs >> i; i != 0; i--) {
            bs >> a >> b;
        }
    }
    if (gRev > 23) bs >> unk_0xD0;
    else {
        if (gRev > 21) {
            unk_0xD0.clear();
            int i; 
            for (bs >> i; i != 0; i--) {
                int x; std::vector<u16> v; std::vector<uint> v2;
                bs >> x >> v >> v2;
                u8 y = x; unk_0xD0.push_back(y);
            }
        } else {
            if (gRev > 16) bs >> unk_0xD0;
        }
    }
    if (gRev > 28) {
        bs >> mBones;
        if (mBones.size() > MaxBones()) mBones.resize(MaxBones());
    } else {
        if (gRev > 13) {
            ObjPtr<RndTransformable, class ObjectDir> t(this, NULL);
            bs >> t;
            if ((RndTransformable*)t) {
                mBones.resize(4);
                if (gRev > 22) {
                    //mBones[0] = t;
                    bs >> mBones[1] >> mBones[2] >> mBones[3];
                    bs >> mBones[0].mXfm >> mBones[1].mXfm >> mBones[2].mXfm >> mBones[3].mXfm;
                    if (gRev < 25) { // incoming headache
                        for (std::vector<Vert>::iterator it = mVerts.begin(); it != mVerts.end(); it++) {

                        }
                    }
                } else {
                    if (TransConstraint() == kParentWorld) {

                    }
                }
            }
            mBones.clear();
        }
    }
    RemoveInvalidBones();


    for (std::vector<Vert>::iterator it = mVerts.begin(); it != mVerts.end(); it++) {
                            
    }
    if (gRev > 37) { bool b; bs >> b; unk9p0 = b;}
    if (gAltRev > 1) { bool b; bs >> b; unk9p3 = b;}
    if (gAltRev > 3) { bool b; bs >> b;}
    Sync(191);
    if (gAltRev >= 3 || NumBones() > 1) MILO_NOTIFIER_WARN("%s", PathName(this));
}
#pragma dont_inline reset

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

BEGIN_PROPSYNCS(RndMesh)
    SYNC_PROP(mat, mMat)
    SYNC_PROP(geom_owner, mOwner)


END_PROPSYNCS