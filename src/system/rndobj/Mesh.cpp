#include "Mesh.h"
#include "decomp.h"
#include "math/strips/Striper.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/BufStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include <vector>

INIT_REVS(RndMesh)

PatchVerts gPatchVerts;

int RndMesh::MaxBones() { return MAX_BONES; }
bool RndMesh::IsSkinned() const { return mBones.size(); }
void RndMesh::SetMat(RndMat* m) { mMat = m; }
void RndMesh::SetGeomOwner(RndMesh* m) {MILO_ASSERT(m, 487); mGeomOwner = m;}

void RndMesh::ScaleBones(float f) {
    for (std::vector<RndBone>::iterator it = mBones.begin(); it != mBones.end(); it++) {
        it->mOffset.v *= f;
    }
}

RndMesh::RndMesh() : mMat(this, NULL), mGeomOwner(this, this), mBones(this),
    mMutable(0), mVolume(kVolumeTriangles), mBSPTree(0), unk_0xFC(0), unk_0x114(0),
    unk_0x118(0), unk_0x11C(0) {
    mHasAOCalc = false;
    mKeepMeshData = false;
    unk9p2 = true;
    mForceNoQuantize = false;
}

RndMesh::~RndMesh() { 
    delete unk_0x11C; unk_0x11C = NULL; 
    delete mBSPTree; mBSPTree = NULL; 
    delete unk_0xFC; unk_0xFC = NULL;
    ClearCompressedVerts();
}

RndMesh::Vert::Vert() : pos(0,0,0), norm(0,1.0f,0), boneWeights(),
    color(), uv(0,0) {
    for(int i = 0; i < 4; i++) boneIndices[i] = 0;
}

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
    RndMesh* m = &(*mGeomOwner);
    if (!m->unk_0xFC) {
        m->unk_0xFC = Hmx::Object::New<RndMultiMesh>();
        m->unk_0xFC->SetMesh(m);
    }
    m->unk_0xFC->mInstances.resize(0);
    return m->unk_0xFC;
}

BinStream& operator>>(BinStream& bs, STRIPERRESULT& sr) {
    bs >> sr.NbStrips;
    int runs; bs >> runs;
    sr.AllocLengthsAndRuns(sr.NbStrips, runs);
    bs.Read(sr.StripLengths, sr.NbStrips * 4);
    bs.Read(sr.StripRuns, runs * 2);

    return bs;
}

bool RndMesh::CacheStrips(BinStream& bs) {
    bool ret = false;
    if (bs.Cached() && bs.GetPlatform() == kPlatformWii && mGeomOwner.mPtr == this && mFaces.size() != 0
        && mVerts.size() != 0 && !(mMutable & 0x20)) ret = true;
    return ret;
}

void RndMesh::CreateStrip(int i, int j, Striper& striper, STRIPERRESULT& sr, bool onesided) {
    STRIPERCREATE sc;
    sc.WFaces = &mFaces[i].idx0;
    sc.NbFaces = j;
    sc.ConnectAllStrips = false;
    sc.OneSided = onesided;
    sc.SGIAlgorithm = false;
    MILO_ASSERT(striper.Init(sc), 1115);
    MILO_ASSERT(striper.Compute(sr), 1116);
    for (int i = 1; i < sr.NbStrips; i++) {
        sr.NbStrips += sr.StripLengths[i];
    }
}

SAVE_OBJ(RndMesh, 1135)

void RndMesh::Load(BinStream& bs) {
    PreLoad(bs);
    PostLoad(bs);
}

void RndMesh::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(38, 6)
    if(gRev > 25) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    LOAD_SUPERCLASS(RndDrawable)
    if(gRev < 15){
        int i;
        ObjPtrList<Hmx::Object, ObjectDir> l(this, kObjListNoNull);
        bs >> i;
        bs >> l;
    }
    int zmode = 0;
    if(gRev < 0x14){
        int i14, i18;
        bs >> i14;
        bs >> i18;
        if(i14 == 0 || i18 == 0) zmode = 0;
        else if(i14 == 1) zmode = 2;
        else {
            zmode = 1;
            if(i18 == 7) zmode = 3;
        }
    }
    if(gRev < 3){
        int i; bs >> i;
    }
    bs >> mMat;
    if(gRev == 0x1B){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(!mMat && buf[0] != '\0'){
            mMat = LookupOrCreateMat(buf, Dir());
        }
    }
    bs >> mGeomOwner;
    if(!mGeomOwner) mGeomOwner = this;
    if(gRev < 0x14 && mMat){
        if(zmode != 0){
            if(!mMat->GetZMode()){
                goto lol;
            }
        }
        mMat->SetZMode((ZMode)zmode);
    }
lol:
    if(gRev < 0xD){
        ObjOwnerPtr<RndMesh, ObjectDir> meshOwner(this, 0);
        bs >> meshOwner;
        if(meshOwner != mGeomOwner) MILO_WARN("Combining face and vert owner of %s", Name());
    }
    if(gRev < 0xF){
        ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
        bs >> tPtr;
        SetTransParent(tPtr, false);
        SetTransConstraint(RndTransformable::kParentWorld, 0, false);
    }
    if(gRev < 0xE){
        ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
        ObjPtr<RndTransformable, ObjectDir> tPtr2(this, 0);
        bs >> tPtr >> tPtr2;
    }
    if(gRev < 3){
        Vector3 v; bs >> v;
    }
    if(gRev < 0xF){
        Sphere s;
        bs >> s;
        SetSphere(s);
    }
    if(gRev == 5 || gRev == 6 || gRev == 7){
        bool b; bs >> b;
    }
    if(gRev == 6 || gRev == 7 || gRev == 8 || gRev == 9 || gRev == 10 || gRev == 11 || gRev == 12 ||
        gRev == 13 || gRev == 14 || gRev == 15 || gRev == 16 || gRev == 17 || gRev == 18 || gRev == 19 || gRev == 20){
        String str;
        bs >> str;
        int i; bs >> i;
    }
    if(gRev > 0xF) bs >> mMutable;
    else if(gRev > 0xB){
        bool b; bs >> b;
        int num = 0;
        if(b) num = 0x1F;
        mMutable = num;
    }
    if(gRev > 0x11) bs >> (int&)mVolume;
    if(gRev > 0x12){
        RELEASE(mBSPTree);
        bs >> mBSPTree;
    }
    if(gRev == 7){
        bool b; bs >> b;
    }
    if(gRev == 9 || gRev == 10){
        int i; bs >> i;
    }
    PreLoadVertices(bs);
}

#pragma push
#pragma dont_inline on
void RndMesh::PostLoad(BinStream& bs) {
    // PostLoadVertices(bs);
    // bs >> mFaces;
    // if ((ushort)(gRev + 0xFFFB) <= 18) {
    //     int i; u16 a,b;
    //     for (bs >> i; i != 0; i--) {
    //         bs >> a >> b;
    //     }
    // }
    // if (gRev > 23) bs >> unk_0xD0;
    // else {
    //     if (gRev > 21) {
    //         unk_0xD0.clear();
    //         int i; 
    //         for (bs >> i; i != 0; i--) {
    //             int x; std::vector<u16> v; std::vector<uint> v2;
    //             bs >> x >> v >> v2;
    //             u8 y = x; unk_0xD0.push_back(y);
    //         }
    //     } else {
    //         if (gRev > 16) bs >> unk_0xD0;
    //     }
    // }
    // if (gRev > 28) {
    //     bs >> mBones;
    //     if (mBones.size() > MaxBones()) mBones.resize(MaxBones());
    // } else {
    //     if (gRev > 13) {
    //         ObjPtr<RndTransformable, class ObjectDir> t(this, NULL);
    //         bs >> t;
    //         if ((RndTransformable*)t) {
    //             mBones.resize(4);
    //             if (gRev > 22) {
    //                 (ObjPtr<RndTransformable, class ObjectDir>&)mBones[0] = t;
    //                 // bs >> mBones[1] >> mBones[2] >> mBones[3];
    //                 // bs >> mBones[0].mOffset >> mBones[1].mOffset >> mBones[2].mOffset >> mBones[3].mOffset;
    //                 if (gRev < 25) { // incoming headache
    //                     for (Vert* it = mVerts.begin(); it != mVerts.end(); it++) {
    //                         // it->why.Set(1 - it->why.GetX() - it->why.GetY() - it->why.GetZ(), 
    //                         //     it->why.GetX(), it->why.GetY(), it->why.GetZ());
    //                     }
    //                 }
    //             } else {
    //                 if (TransConstraint() == kParentWorld) 
    //                     (ObjPtr<RndTransformable, class ObjectDir>&)mBones[0] = TransParent(); 
    //                 else (ObjPtr<RndTransformable, class ObjectDir>&)mBones[0] = this;
    //                 mBones[0].mOffset.Reset();
    //                 (ObjPtr<RndTransformable, class ObjectDir>&)mBones[1] = t;
    //                 bs >> mBones[2];
    //                 bs >> mBones[1].mOffset >> mBones[2].mOffset;
    //                 (ObjPtr<RndTransformable, class ObjectDir>&)mBones[3] = NULL;
    //             }
    //         }
    //         mBones.clear();
    //     }
    // }
    // RemoveInvalidBones();


    // for (Vert* it = mVerts.begin(); it != mVerts.end(); it++) {
                            
    // }
    // if (gRev > 37) { bool b; bs >> b; mHasAOCalc = b;}
    // if (gAltRev > 1) { bool b; bs >> b; mForceNoQuantize = b;}
    // if (gAltRev > 3) { bool b; bs >> b;}
    // Sync(191);
    // if (gAltRev >= 3 || NumBones() > 1) MILO_WARN("%s", PathName(this));
}

DECOMP_FORCEBLOCK(Mesh, (Hmx::Color32* c), { c->Clear(); c->fr(); c->fg(); c->fb(); c->fa(); })
DECOMP_FORCEFUNC(Mesh, RndMesh, NumBones())
#pragma pop

BinStream& operator>>(BinStream& bs, RndMesh::Vert& v) {
    bs >> v.pos;
    if (RndMesh::gRev != 10 && RndMesh::gRev < 23) { int a,b; bs >> a >> b; }
    bs >> v.norm;


    if (RndMesh::gRev < 20) { int a,b; bs >> b >> a; }
    if (RndMesh::gRev > 28) bs >> v.boneIndices[0] >> v.boneIndices[1] >> v.boneIndices[2] >> v.boneIndices[3];
    if (RndMesh::gRev > 29) {
        int a,b,c,d;
        bs >> d >> c >> b >> a;
    }
    return bs;
}

TextStream& operator<<(TextStream& ts, RndMesh::Volume v) {
    if (v == RndMesh::kVolumeEmpty) ts << "kVolumeEmpty";
    else if (v == RndMesh::kVolumeTriangles) ts << "kVolumeTriangles";
    else if (v == RndMesh::kVolumeBSP) ts << "kVolumeBSP";
    else if (v == RndMesh::kVolumeBox) ts << "kVolumeBox";
    return ts;
}
#ifdef MILO_DEBUG
int RndMesh::NumFaces() const { return mFaces.size(); }
int RndMesh::NumVerts() const { return mVerts.size(); }
#endif

BinStream& operator>>(BinStream& bs, RndMesh::Face& f) {
    bs >> f.idx0 >> f.idx1 >> f.idx2;
    if (RndMesh::gRev < 1) {
        Vector3 v; bs >> v;
    }
    return bs;
}

void RndMesh::Sync(int i) {
    OnSync(mKeepMeshData ? i | 0x200 : i);
}

void RndMesh::ClearCompressedVerts() {
    delete unk_0x114;
    unk_0x114 = NULL;
    unk_0x118 = 0;
}

#pragma push
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
#ifdef MILO_DEBUG
    HANDLE_EXPR(estimated_size_kb, EstimatedSizeKb())
#endif
    HANDLE_ACTION(clear_bones, CopyBones(NULL))
    HANDLE_ACTION(copy_geom_from_owner, CopyGeometryFromOwner())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(2306)
END_HANDLERS
#pragma pop

DataNode RndMesh::OnPointCollide(const DataArray* da){
    BSPNode* tree = GetBSPTree();
    Vector3 v(da->Float(2), da->Float(3), da->Float(4));
    Multiply(WorldXfm(), v, v);
    return DataNode(tree && Intersect(v, tree));
}

DataNode RndMesh::OnAttachMesh(const DataArray* da) {
    RndMesh* m = da->Obj<RndMesh>(2);
    AttachMesh(this, m);
    delete m;
    return DataNode(0);
}

DataNode RndMesh::OnGetVertNorm(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2446);
    v = &mVerts[index];
    *da->Var(3) = DataNode(v->norm.x);
    *da->Var(4) = DataNode(v->norm.y);
    *da->Var(5) = DataNode(v->norm.z);
    return DataNode(0);
}

DataNode RndMesh::OnSetVertNorm(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2457);
    v = &mVerts[index];
    v->norm.x = da->Float(3);
    v->norm.y = da->Float(4);
    v->norm.z = da->Float(5);
    Sync(31);
    return DataNode(0);
}

DataNode RndMesh::OnGetVertXYZ(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2469);
    v = &mVerts[index];
    *da->Var(3) = DataNode(v->pos.x);
    *da->Var(4) = DataNode(v->pos.y);
    *da->Var(5) = DataNode(v->pos.z);
    return DataNode(0);
}

DataNode RndMesh::OnSetVertXYZ(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2480);
    v = &mVerts[index];
    v->pos.x = da->Float(3);
    v->pos.y = da->Float(4);
    v->pos.z = da->Float(5);
    Sync(31);
    return DataNode(0);
}

DataNode RndMesh::OnGetVertUV(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2492);
    v = &mVerts[index];
    *da->Var(3) = DataNode(v->uv.x);
    *da->Var(4) = DataNode(v->uv.y);
    return DataNode(0);
}

DataNode RndMesh::OnSetVertUV(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2502);
    v = &mVerts[index];
    v->uv.x = da->Float(3);
    v->uv.y = da->Float(4);
    Sync(31);
    return DataNode(0);
}

DataNode RndMesh::OnGetFace(const DataArray* da) {
    Face* f;
    int index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mFaces.size(), 2513);
    f = &mFaces[index];
    *da->Var(3) = DataNode(f->idx0);
    *da->Var(4) = DataNode(f->idx1);
    *da->Var(5) = DataNode(f->idx2);
    return DataNode(0);
}

DataNode RndMesh::OnSetFace(const DataArray* da) {
    Face* f;
    int index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mFaces.size(), 2524);
    f = &mFaces[index];
    f->idx0 = da->Int(3); f->idx1 = da->Int(4); f->idx2 = da->Int(5);
    Sync(32);
    return DataNode(0);
}

DataNode RndMesh::OnUnitizeNormals(const DataArray* da){
    for(Vert* it = Verts().begin(); it != Verts().end(); ++it){
        Normalize(it->norm, it->norm);
    }
    return DataNode(0);
}

DataNode RndMesh::OnConfigureMesh(const DataArray* da){
    if(Type() != configurable_mesh) MILO_WARN("Can't configure nonconfigurable mesh %s\n", Name());
    else {
        float fleft = Property(left, true)->Float(0);
        float fright = Property(right, true)->Float(0);
        float fheight = Property(height, true)->Float(0);
        Vector3 v54(fleft, 0, fheight);
        Vector3 v60(fleft, 0, 0);
        Vector3 v6c(fright, 0, 0);
        Vector3 v78(fright, 0, fheight);
        mVerts[0].pos = v54;
        mVerts[1].pos = v60;
        mVerts[2].pos = v6c;
        mVerts[3].pos = v78;
        Sync(0x3F);
    }
    return DataNode(0);
}

BEGIN_CUSTOM_PROPSYNC(RndBone)
    SYNC_PROP(bone, o.mBone)
    SYNC_PROP(offset, o.mOffset)
END_CUSTOM_PROPSYNC

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndMesh)
    SYNC_PROP(mat, mMat)
    SYNC_PROP_MODIFY_ALT(geom_owner, mGeomOwner, if(!mGeomOwner) mGeomOwner = this)
    {
        static Symbol _s("mutable");
        if(sym == _s){
            _i++;
            if(_i < _prop->Size()){
                DataNode& node = _prop->Node(_i);
                int res = 0;
                switch(node.Type()){
                    case kDataInt:
                        res = node.Int(0);
                        break;
                    case kDataSymbol:
                        const char* bitstr = node.Sym(0).Str();
                        if(strncmp("BIT_", bitstr, 4) != 0){
                            MILO_FAIL("%s does not begin with BIT_", bitstr);
                        }
                        Symbol bitsym(bitstr + 4);
                        DataArray* macro = DataGetMacro(bitsym);
                        if(!macro){
                            MILO_FAIL("PROPERTY_BITFIELD %s could not find macro %s", _s, bitsym);
                        }
                        res = macro->Int(0);
                        break;
                    default:
                        MILO_ASSERT(0, 0xB90);
                        break;
                }
                MILO_ASSERT(_op <= kPropInsert, 0xB90);
                if(_op == kPropGet){
                    int final = mGeomOwner->mMutable & res;
                    _val = DataNode(final > 0);
                }
                else {
                    if(_val.Int(0) != 0) mGeomOwner->mMutable |= res;
                    else mGeomOwner->mMutable &= ~res;
                }
                return true;
            }
            else return PropSync(mGeomOwner->mMutable, _val, _prop, _i, _op);
        }
    }
    SYNC_PROP_SET(num_verts, Verts().size(), SetNumVerts(_val.Int(0)))
    SYNC_PROP_SET(num_faces, (int)Faces().size(), SetNumFaces(_val.Int(0)))
    SYNC_PROP_SET(volume, GetVolume(), SetVolume((Volume)_val.Int(0)))
    SYNC_PROP_SET(has_valid_bones, HasValidBones(0), _val.Int(0))
    SYNC_PROP(bones, mBones)
    {
        static Symbol _s("has_ao_calculation");
        if(sym == _s){
            if(_op == kPropSet) mHasAOCalc = _val.Int(0);
            else _val = DataNode(mHasAOCalc);
            return true;
        }
    }
    {
        static Symbol _s("force_no_quantize");
        if(sym == _s){
            if(_op == kPropSet) mForceNoQuantize = _val.Int(0);
            else _val = DataNode(mForceNoQuantize);
            return true;
        }
    }
    SYNC_PROP_SET(keep_mesh_data, mKeepMeshData, SetKeepMeshData(_val.Int(0)))
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop