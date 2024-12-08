#include "Mesh.h"
#include "decomp.h"
#include "math/Bsp.h"
#include "math/Geo.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "math/strips/Striper.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "obj/DataUtl.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Rnd.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/BufStream.h"
#include "utl/ChunkStream.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include <vector>

INIT_REVS(RndMesh)

PatchVerts gPatchVerts;
int MESH_REV_SEP_COLOR = 0x25;

DECOMP_FORCEACTIVE(Mesh, "%s: exceeds bone limit of %d", "BSP tree outside bounding box",
    "Made BSP tree for \"%s\" (nodes:%d depth:%d)\n", "Couldn't make BSP tree for \"%s\"")

int RndMesh::MaxBones() { return MAX_BONES; }

RndDrawable* RndMesh::CollideShowing(const Segment& seg, float& f, Plane& pl){
    Segment sega0;
    Transform tf58;
    sLastCollide = -1;
    if(IsSkinned() || sRawCollide) sega0 = seg;
    else {
        FastInvert(WorldXfm(), tf58);
        Multiply(seg.start, tf58, sega0.start);
        Multiply(seg.end, tf58, sega0.end);
    }
    if(mGeomOwner->mBSPTree){
        if(Intersect(sega0, mGeomOwner->mBSPTree, f, pl) && f){
            Multiply(pl, WorldXfm(), pl);
            return this;
        }
    }
    else {
        if(GetVolume() == kVolumeTriangles){
            bool b1 = false;
            f = 1.0f;
            for(std::vector<Face>::iterator it = Faces().begin(); it != Faces().end(); ++it){
                const Vert& vert0 = VertAt(it->v1);
                const Vert& vert1 = VertAt(it->v2);
                const Vert& vert2 = VertAt(it->v3);
                Triangle tri;
                if(IsSkinned() && !sRawCollide){
                    tri.Set(SkinVertex(vert0, 0), SkinVertex(vert1, 0), SkinVertex(vert2, 0));
                }
                else tri.Set(vert0.pos, vert1.pos, vert2.pos);
                float fintersect;
                if(Intersect(sega0, tri, false, fintersect)){
                    Interp(sega0.start, sega0.end, fintersect, sega0.end);
                    f *= fintersect;
                    pl.Set(tri.origin, tri.frame.z);
                    b1 = true;
                    sLastCollide = (it - Faces().begin());
                }
            }
            if(b1){
                if(!sRawCollide) Multiply(pl, WorldXfm(), pl);
                return this;
            }
        }
    }
    return 0;
}

int RndMesh::CollidePlane(const RndMesh::Face& face, const Plane& plane){
    bool first = VertAt(face.v1).pos <= plane;
    bool second = VertAt(face.v2).pos <= plane;
    bool third = VertAt(face.v3).pos <= plane;
    if(first == second && second == third){
        int ret = -1;
        if(first) ret = 1;
        return ret;
    }
    else return 0;
}

int RndMesh::CollidePlane(const Plane& plane){
    int super = RndDrawable::CollidePlane(plane);
    if(super != 0) return super;
    Transform tf48;
    FastInvert(WorldXfm(), tf48);
    Plane pl58;
    Multiply(plane, tf48, pl58);
    if(GetVolume() == kVolumeTriangles){
        if(Faces().empty()) return -1;
        else {
            std::vector<Face>::iterator faceIt = Faces().begin();
            int faceColl = CollidePlane(*faceIt, pl58);
            if(faceColl == 0) return 0;
            else {
                ++faceIt;
                for(; faceIt != Faces().end(); ++faceIt){
                    if(faceColl != CollidePlane(*faceIt, pl58)){
                        return 0;
                    }
                }
                return faceColl;
            }
        }
    }
    else return 0;
}

void RndMesh::UpdateSphere(){
    Sphere s;
    if(mBones.empty()){
        MakeWorldSphere(s, true);
        Transform tf;
        FastInvert(WorldXfm(), tf);
        Multiply(s, tf, s);
    }
    else s.Zero();
    RndDrawable::SetSphere(s);
}

float RndMesh::GetDistanceToPlane(const Plane& p, Vector3& v){
    if(Verts().empty()) return 0;
    else {
        Transform& world = WorldXfm();
        Vector3 v58;
        Multiply(Verts()[0].pos, world, v58);
        v = v58;
        float dot = p.Dot(v);
        for(Vert* it = Verts().begin(); it != Verts().end(); ++it){
            Multiply(it->pos, world, v58);
            float dotted = p.Dot(v58);
            if(std::fabs(dotted) < std::fabs(dot)){
                dot = dotted;
                v = v58;
            }
        }
        return dot;
    }
}

bool RndMesh::MakeWorldSphere(Sphere& s, bool b){
    if(b){
        Box box;
        CalcBox(this, box);
        Vector3 v68;
        CalcBoxCenter(v68, box);
        s.Set(v68, 0);
        const Transform& worldXfm = WorldXfm();
        for(Vert* it = Verts().begin(); it != Verts().end(); ++it){
            Vector3 v50;
            Multiply(it->pos, worldXfm, v50);
            Vector3 v5c;
            Subtract(v50, s.center, v5c);
            s.radius = Max(s.GetRadius(), Dot(v5c, v5c));
        }
        s.radius = sqrtf(s.GetRadius());
        return true;
    }
    else if(mSphere.GetRadius()){
        Multiply(mSphere, WorldXfm(), s);
        return true;
    }
    else return false;
}

void RndMesh::SetVolume(RndMesh::Volume vol){
    if(mGeomOwner != this) mGeomOwner->SetVolume(vol);
    else {
        mVolume = vol;
        RELEASE(mBSPTree);
        if(mVerts.empty() || mFaces.empty()) return;
        else {
            if(mVolume == kVolumeBox){
                Box box;
                for(Vert* it = mVerts.begin(); it != mVerts.end(); ++it){
                    box.GrowToContain(it->pos, &it->pos == &mVerts.begin()->pos);
                }
                mBSPTree = new BSPNode();
                BSPNode* bspIt = mBSPTree;
                for(int i = 0; i < 6; i++){
                    Vector3 vb0;
                    vb0.Zero();
                    vb0[i % 3] = i > 2 ? -1.0f : 1.0f;
                    bspIt->plane.Set(i > 2 ? box.mMin : box.mMax, vb0);
                    bspIt->left = 0;
                    if(i == 5){
                        bspIt->right = 0;
                    }
                    else {
                        bspIt->right = new BSPNode();
                        bspIt = bspIt->right;
                    }
                }
            }
            else if(mVolume == kVolumeBSP){
                std::list<BSPFace> faces;
                for(int i = mFaces.size() - 1; i >= 0; i--){
                    Face& curFace = mFaces[i];
                    const Vector3& v1 = mVerts[curFace.v1].pos;
                    const Vector3& v2 = mVerts[curFace.v2].pos;
                    const Vector3& v3 = mVerts[curFace.v3].pos;
                    BSPFace bspFace;
                    bspFace.Set(v1, v2, v3);
                    faces.push_back(bspFace);
                }
                if(!MakeBSPTree(mBSPTree, faces, 0)){
                    RELEASE(mBSPTree);
                }
                if(mBSPTree){
                    Box boxa0;
                    for(Vert* it = mVerts.begin(); it != mVerts.end(); ++it){
                        boxa0.GrowToContain(it->pos, &it->pos == &mVerts.begin()->pos);
                    }
                    if(!CheckBSPTree(mBSPTree, boxa0)){
                        MILO_WARN("BSP tree outside bounding box");
                        RELEASE(mBSPTree);
                    }
                }
                if(mBSPTree){
                    int x = 0, y = 0;
                    NumNodes(mBSPTree, x, y);
                    MILO_LOG("Made BSP tree for \"%s\" (nodes:%d depth:%d)\n", Name(), x, y);
                }
                else {
                    MILO_WARN("Couldn't make BSP tree for \"%s\"", Name());
                    mVolume = kVolumeEmpty;
                }
            }
        }
    }
}

void RndMesh::SetMat(RndMat* m) { mMat = m; }
void RndMesh::SetGeomOwner(RndMesh* m) {MILO_ASSERT(m, 487); mGeomOwner = m;}

void RndMesh::ScaleBones(float f) {
    for (std::vector<RndBone>::iterator it = mBones.begin(); it != mBones.end(); it++) {
        it->mOffset.v *= f;
    }
}

void RndMesh::SetBone(int idx, RndTransformable* bone, bool calcOffset){
    mBones[idx].mBone = bone;
    if(calcOffset){
        Transform tf48;
        Invert(bone->WorldXfm(), tf48);
        Multiply(WorldXfm(), tf48, mBones[idx].mOffset);
    }
}

RndMesh::RndMesh() : mMat(this), mGeomOwner(this, this), mBones(this),
    mMutable(0), mVolume(kVolumeTriangles), mBSPTree(0), mMultiMesh(0), mCompressedVerts(0),
    mNumCompressedVerts(0), mFileLoader(0) {
    mHasAOCalc = false;
    mKeepMeshData = false;
    mUseCachedBoxLightColors = true;
    mForceNoQuantize = false;
}

RndMesh::~RndMesh() {
    RELEASE(mFileLoader);
    RELEASE(mBSPTree);
    RELEASE(mMultiMesh);
    ClearCompressedVerts();
}

void RndMesh::VertVector::resize(int n, bool b){
    unka = b;
    if(mCapacity){
        MILO_ASSERT(n <= mCapacity, 0x26A);
        mNumVerts = n;
    }
    else if(n == 0){
        delete [] mVerts;
        mVerts = 0;
        mNumVerts = 0;
    }
    else if(n != mNumVerts){
        Vert* oldverts = mVerts;
        Vert* oldit = oldverts;
        Vert* end = oldverts + Min(n, size());
        {
            MemDoTempAllocations m(true, false);
            mVerts = new Vert[n];
        }
        mNumVerts = n;

        Vert* newit = mVerts;
        while(oldit != end){
            *newit++ = *oldit++;
        }

        delete [] oldverts;
    }
}

void RndMesh::VertVector::reserve(int capacity, bool b){
    MILO_ASSERT(capacity > mCapacity, 0x297);
    MILO_ASSERT(capacity > mNumVerts, 0x298);
    mCapacity = 0;
    int num = mNumVerts;
    int temp = 0;
    if (capacity <= 0xFFFFU) {
        temp = 1;
    }    
    MILO_ASSERT_FMT(temp, "RndMesh::reserve(): capacity %d overflows short!\n", capacity);    
    resize(capacity, b);
    mCapacity = capacity;
    mNumVerts = num;
}

void RndMesh::VertVector::realloc_perm(){
    if(unka){
        MemDoTempAllocations m(false, false);
        Vert* oldverts = mVerts;
        mVerts = new Vert[mNumVerts];
        for(int i = 0; i < mNumVerts; i++){
            mVerts[i] = oldverts[i];
        }
        delete [] oldverts;
        unka = 0;
        mCapacity = 0;
    }
}

RndMesh::VertVector& RndMesh::VertVector::operator=(const RndMesh::VertVector& c){
    MILO_ASSERT(mCapacity == 0, 0x2E0);
    MILO_ASSERT(c.mCapacity == 0, 0x2E1);
    if(c.mNumVerts != mNumVerts){
        mNumVerts = Max(c.mNumVerts, 0);
        delete [] mVerts;
        mVerts = nullptr;
        if(mNumVerts != 0){
            MemDoTempAllocations m(true, false);
            unka = 1;
            mVerts = new Vert[mNumVerts];
        }
    }
    if(mVerts){
        Vert* otherVerts = c.mVerts;
        Vert* otherEnd = &otherVerts[mNumVerts];
        Vert* myVerts = mVerts;
        while(otherVerts != otherEnd){
            *myVerts++ = *otherVerts++;
        }
    }
}

void RndMesh::PreLoadVertices(BinStream& bs) {
    if (gAltRev > 4) {
        mFileLoader = new FileLoader("", "", kLoadFront, 0, true, true, &bs);
    }
}

void RndMesh::PostLoadVertices(BinStream& bs) {
    void* buf = 0;
    int len = 0;
    if (mFileLoader) {
        buf = (void*)mFileLoader->GetBuffer(0);
        len = mFileLoader->GetSize();
        (delete mFileLoader, mFileLoader = 0);
    }
    BufStream bfs(buf, len, true);
    if(buf) &bs = &bfs;
    int count;
    bs >> count;
    bool b58;
    if(gRev > 0x22) bs >> b58;
    else b58 = false;
    unsigned int compressedSize = 0;
    unsigned int loadedCompressedSize = 0;
    bool b4 = false;
    unsigned int loadedVersion = 0;
    if(b58){
        bs >> loadedCompressedSize;
        bs >> loadedVersion;
#ifdef MILO_DEBUG
        MILO_ASSERT(IsVertexCompressionSupported(TheLoadMgr.GetPlatform()), 0x331);
#else
        IsVertexCompressionSupported(kPlatformWii);
#endif
        MILO_FAIL("Unsupported platform for vertex compression");
        b4 = false;
        if(loadedCompressedSize == 0 && loadedVersion == 0) b4 = true;
        if(!b4){
            MILO_WARN("Loaded stale compressed vertex data, resave mesh file \"%s\"(loaded size = %d, current = %d; loaded ver = %d, current = %d",
                bs.Name(), loadedCompressedSize, 0U, loadedVersion, 0U);
        }
    }
    if(b58){
        if(b4){
            mNumCompressedVerts = count;
            if(mNumCompressedVerts != 0){
                compressedSize *= count;
                MILO_ASSERT(compressedSize > 0, 0x369);
                mCompressedVerts = new unsigned char[compressedSize];
                ReadChunks(bs, mCompressedVerts, compressedSize, 0);
            }
        }
        else {
            loadedCompressedSize *= count;
            MILO_ASSERT(loadedCompressedSize> 0, 0x376);
            bs.Seek(loadedCompressedSize, BinStream::kSeekCur);
        }
    }
    else {
        bool resizebool = !(mMutable & 0x1F) && !mKeepMeshData;
        mVerts.resize(count, resizebool);
        int i5 = 0;
        for(Vert* it = mVerts.begin(); it != mVerts.end(); ++it){
            bs >> *it;
            i5 += 1;
            if((i5 & 0x1FF) == 0){
                while(bs.Eof() == TempEof) Timer::Sleep(0);
            }
        }
    }
    if(buf) _MemFree(buf);
}

RndMultiMesh* RndMesh::CreateMultiMesh() {
    RndMesh* owner = mGeomOwner;
    if(!owner->mMultiMesh){
        owner->mMultiMesh = Hmx::Object::New<RndMultiMesh>();
        owner->mMultiMesh->SetMesh(owner);
    }
    owner->mMultiMesh->mInstances.resize(0);
    return owner->mMultiMesh;
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
    if (bs.Cached() && bs.GetPlatform() == kPlatformWii && mGeomOwner == this && !mFaces.empty()
        && !mVerts.empty() && !(mMutable & 0x20)) ret = true;
    return ret;
}

DECOMP_FORCEACTIVE(Mesh, "0", "Endian.h", "block != NULL", "count >= 0")

void RndMesh::CreateStrip(int i, int j, Striper& striper, STRIPERRESULT& sr, bool onesided) {
    STRIPERCREATE sc;
    sc.WFaces = &mFaces[i].v1;
    sc.NbFaces = j;
    sc.ConnectAllStrips = false;
    sc.OneSided = onesided;
    sc.SGIAlgorithm = false;
    MILO_ASSERT(striper.Init(sc), 1115);
    MILO_ASSERT(striper.Compute(sr), 1116);
    for (int i = 1; i < sr.NbStrips; i++) {
        sr.StripLengths[i] += sr.StripLengths[i - 1];
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
        ObjPtrList<Hmx::Object> l(this, kObjListNoNull);
        bs >> i >> l;
    }
    int zmode = 0;
    if(gRev < 0x14){
        int i14, i18;
        bs >> i14 >> i18;
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
        if(zmode == 0 || mMat->GetZMode()){
            mMat->SetZMode((ZMode)zmode);
        }
    }
    if(gRev < 0xD){
        ObjOwnerPtr<RndMesh> meshOwner(this, 0);
        bs >> meshOwner;
        if(meshOwner != mGeomOwner) MILO_WARN("Combining face and vert owner of %s", Name());
    }
    if(gRev < 0xF){
        ObjPtr<RndTransformable> tPtr(this, 0);
        bs >> tPtr;
        SetTransParent(tPtr, false);
        SetTransConstraint(RndTransformable::kParentWorld, 0, false);
    }
    if(gRev < 0xE){
        ObjPtr<RndTransformable> tPtr(this, 0);
        ObjPtr<RndTransformable> tPtr2(this, 0);
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
    PostLoadVertices(bs);
    bs >> mFaces;
    if(gRev == 5 || gRev == 6 || gRev == 7 || gRev == 8 || gRev == 9 || gRev == 10 ||
        gRev == 11 || gRev == 12 || gRev == 13 || gRev == 14 || gRev == 15 || gRev == 16 ||
        gRev == 17 || gRev == 18 || gRev == 19 || gRev == 20 || gRev == 21 || gRev == 22 || gRev == 23
    ){
        int count; unsigned short s1, s2;
        bs >> count;
        for(; count != 0; count--){
            bs >> s1 >> s2;
        }
    }
    if(gRev > 0x17) bs >> mPatches;
    else if(gRev > 0x15){
        mPatches.clear();
        int count;
        unsigned int ui;
        bs >> count;
        for(; count != 0; count--){
            std::vector<unsigned short> usvec;
            std::vector<unsigned int> uivec;
            bs >> ui >> usvec >> uivec;
            mPatches.push_back(ui);
        }
    }
    else if(gRev > 0x10) bs >> mPatches;

    if(gRev > 0x1C){
        bs >> mBones;
        int max = MaxBones();
        if(mBones.size() > max) mBones.resize(MaxBones());
    }
    else if(gRev > 0xD){
        ObjPtr<RndTransformable> tPtr(this, 0);
        bs >> tPtr;
        if(tPtr){
            mBones.resize(4);
            if(gRev > 0x16){
                mBones[0].mBone = tPtr;
                bs >> mBones[1].mBone >> mBones[2].mBone >> mBones[3].mBone;
                bs >> mBones[0].mOffset >> mBones[1].mOffset >> mBones[2].mOffset >> mBones[3].mOffset;
                if(gRev < 0x19){
                    for(Vert* it = mVerts.begin(); it != mVerts.end(); ++it){
                        it->boneWeights.Set(((1.0f - it->boneWeights.GetX()) - it->boneWeights.GetY()) - it->boneWeights.GetZ(),
                            it->boneWeights.GetX(), it->boneWeights.GetY(), it->boneWeights.GetZ());
                    }
                }
            }
            else {
                if(TransConstraint() == RndTransformable::kParentWorld){
                    mBones[0].mBone = TransParent();
                }
                else {
                    mBones[0].mBone = this;
                }
                mBones[0].mOffset.Reset();
                mBones[1].mBone = tPtr;
                bs >> mBones[2].mBone >> mBones[1].mOffset >> mBones[2].mOffset;
                mBones[3].mBone = 0;
            }
            for(int i = 0; i < 4; i++){
                if(!mBones[i].mBone){
                    mBones.resize(i);
                    break;
                }
            }
        }
        else mBones.clear();
    }
    RemoveInvalidBones();
    if(gAltRev > 5 && CacheStrips(bs)){
        MemDoTempAllocations m(true, false);
        MILO_ASSERT(mStriperResults.empty(), 0x5BA);
        mStriperResults.resize(mPatches.size());
        for(std::vector<STRIPERRESULT>::iterator it = mStriperResults.begin(); it != mStriperResults.end(); ++it){
            bs >> *it;
        }
    }
    if(gRev != 0 && gRev < 4){
        std::vector<std::vector<unsigned short> > usvec;
        bs >> usvec;
    }
    if(gRev == 0){
        bool bd4;
        int ic0, ic4, ic8, icc;
        bs >> bd4 >> ic0 >> ic4 >> ic8;
        bs >> icc;
    }
    if(gRev == 0x12 && mGeomOwner == this) SetVolume(mVolume);
    if(gRev < 0x1F) SetZeroWeightBones();
    if(gRev > 0x23){
        bool keep; bs >> keep;
        mKeepMeshData = keep;
    }
    if(gRev < MESH_REV_SEP_COLOR && IsSkinned()){
        for(Vert* it = mVerts.begin(); it != mVerts.end(); ++it){
            Hmx::Color32& col = it->color;
            it->boneWeights.Set(col.fr(), col.fg(), col.fb(), col.fa());
            col.Clear();
        }
    }
    if(gRev > 0x25){
        bool calc; bs >> calc;
        mHasAOCalc = calc;
    }
    if(gAltRev > 1){
        bool noquant; bs >> noquant;
        mForceNoQuantize = noquant;
    }
    if(gAltRev > 3){
        bool b; bs >> b;
    }
    Sync(0xBF);
    if(gAltRev < 3 && NumBones() > 1){
        MILO_WARN("--->Arvin/Diana: Skinned mesh needs to be re-exported: %s", PathName(this));
    }
}
#pragma pop

void RndMesh::SetZeroWeightBones(){
    if(mBones.size() >= 2){
        for(int i = 0; i < mVerts.size(); i++){
            Vert& curvert = mVerts[i];
            if(curvert.boneWeights.GetY() == 0) curvert.boneIndices[1] = curvert.boneIndices[0];
            if(curvert.boneWeights.GetZ() == 0) curvert.boneIndices[2] = curvert.boneIndices[0];
            if(curvert.boneWeights.GetW() == 0) curvert.boneIndices[3] = curvert.boneIndices[0];
        }
    }
}

void RndMesh::CopyGeometryFromOwner(){
    RndMesh* owner = GeometryOwner();
    if(owner != this){
        CopyGeometry(owner, true);
        Sync(0x3F);
    }
}

void RndMesh::CopyBones(const RndMesh* mesh){
    if(mesh) mBones = mesh->mBones;
    else mBones.clear();
}

BEGIN_COPYS(RndMesh)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(RndMesh)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMat)
        if(ty != kCopyFromMax) COPY_MEMBER(mKeepMeshData)
        if(ty == kCopyFromMax) mMutable |= c->mMutable;
        else COPY_MEMBER(mMutable)
        mHasAOCalc = false;
        COPY_MEMBER(mForceNoQuantize)
        if(ty == kCopyShallow || (ty == kCopyFromMax && c->mGeomOwner != c)){
            COPY_MEMBER(mGeomOwner)
            CopyBones(c);
        }
        else {
            CopyGeometry(c, ty != kCopyFromMax);
            if(ty != kCopyFromMax) COPY_MEMBER(mHasAOCalc);
        }
    END_COPYING_MEMBERS
    Sync(0xBF);
END_COPYS

void RndMesh::CopyGeometry(const RndMesh* mesh, bool b){
    mGeomOwner = this;
    mVerts = mesh->mGeomOwner->mVerts;
    mFaces = mesh->mGeomOwner->mFaces;
    mPatches = mesh->mGeomOwner->mPatches;
    if(b) SetVolume(mesh->mGeomOwner->mVolume);
    mBones = mesh->mBones;
    // some operation on mStriperResults that sets every member to 0
    mStriperResults = std::vector<STRIPERRESULT>();
    // ClearAndShrink(mStriperResults);
    if(mStriperResults.size() != 0){
        MemDoTempAllocations m(true, false);
        mStriperResults.resize(mStriperResults.size());
        int i = 0;
        int stripersize = mStriperResults.size();
        for(; i < stripersize; i++){
            mStriperResults[i] = mesh->mStriperResults[i];
        }
    }
}

BinStream& operator>>(BinStream& bs, RndMesh::Vert& v) {
    float f34, f38;
    bs >> v.pos;
    if (RndMesh::gRev != 10 && RndMesh::gRev < 23) { bs >> f34 >> f38; }
    bs >> v.norm;
    if(RndMesh::gRev < MESH_REV_SEP_COLOR) bs >> v.color;
    else bs >> v.color;
    bs >> v.uv;
    if(RndMesh::gRev >= MESH_REV_SEP_COLOR){
        Vector4 v4; bs >> v4;
        v.boneWeights.Set(v4.x, v4.y, v4.z, v4.w);
    }
    if(RndMesh::gRev != 10 && RndMesh::gRev < 23){
        v.boneWeights.Set((1.0f - f34) - f38, f34, f38, 0);
    }
    if(RndMesh::gRev < 0xB){
        Vector2 v2; bs >> v2;
    }
    if(RndMesh::gRev > 0x1C){
        bs >> v.boneIndices[0] >> v.boneIndices[1] >> v.boneIndices[2] >> v.boneIndices[3];
    }
    if(RndMesh::gRev > 0x1D){
        Vector4 v4; bs >> v4;
    }
    return bs;
}

TextStream& operator<<(TextStream& ts, RndMesh::Volume v) {
    if (v == RndMesh::kVolumeEmpty) ts << "Empty";
    else if (v == RndMesh::kVolumeTriangles) ts << "Triangles";
    else if (v == RndMesh::kVolumeBSP) ts << "BSP";
    else if (v == RndMesh::kVolumeBox) ts << "Box";
    return ts;
}

void RndMesh::Print(){
    TextStream& t = TheDebug;
    t << "   mat: " << mMat << "\n";
    t << "   geomOwner: " << mGeomOwner << "\n";
    t << "   mutable: " << mMutable << "\n";
    t << "   volume: " << mVolume << "\n";
    t << "   bones: TODO\n";
    t << "   geometry: TODO\n";
}

#ifdef MILO_DEBUG
int RndMesh::NumFaces() const { return mFaces.size(); }
int RndMesh::NumVerts() const { return mVerts.size(); }
#endif

void RndMesh::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    if(mGeomOwner == from){
        RndMesh* meshto = dynamic_cast<RndMesh*>(to);
        if(meshto) mGeomOwner = meshto->mGeomOwner;
        else mGeomOwner = this;
    }
}

BinStream& operator>>(BinStream& bs, RndMesh::Face& f) {
    bs >> f.v1 >> f.v2 >> f.v3;
    if (RndMesh::gRev < 1) {
        Vector3 v; bs >> v;
    }
    return bs;
}

void FaceCenter(RndMesh* mesh, RndMesh::Face* face, Vector3& v){
    v.Set(0,0,0);
    for(int i = 0; i < 3; i++){
        v += mesh->VertAt((*face)[i]).pos;
    }
    v *= 0.33333333f;
}

void RndMesh::Sync(int flags) {
    OnSync(mKeepMeshData ? flags | 0x200 : flags);
}

void RndMesh::OnSync(int flags){
    if(mGeomOwner != this || (flags & 0x80U) || !(flags & 0x20U)) return;
    mPatches.clear();
    if(PatchOkay(mVerts.size(), mFaces.size())){
        mPatches.push_back(mFaces.size());
    }
    else if(flags & 0x100U){
        int u13 = 0xFFFF;
        int i4 = 0;
        int i12 = 0;
        for(std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it){
            i12 = Max(Max<u16>(i12, it->v1, it->v2), it->v3);
            u13 = Min(Min<u16>(u13, it->v1, it->v2), it->v3);
            if(!PatchOkay((i12 - u13) + 1, i4 + 1)){
                mPatches.push_back(i4);
                i12 = Max(it->v1, it->v2, it->v3);
                u13 = Min(it->v1, it->v2, it->v3);
                i4 = 1;
            }
            else i4++;
        }
        mPatches.push_back(i4);
    }
    else {
        gPatchVerts.Clear();
        std::vector<Face> faces;
        Vector3 v40(0,0,0);
        int i4 = 0;
        while(true){
            if(mFaces.empty()) break;
            int u5 = 4;
            float f68 = 0;
            std::vector<Face>::iterator faceIt = mFaces.begin();
            for(; faceIt != mFaces.end(); ++faceIt){
                int uvar16 = !gPatchVerts.HasVert(faceIt->v1) + !gPatchVerts.HasVert(faceIt->v2) + !gPatchVerts.HasVert(faceIt->v3);
                if(uvar16 < u5){
                    Vector3 v4c;
                    FaceCenter(this, faceIt, v4c);
                    f68 = DistanceSquared(v4c, v40);
                    u5 = uvar16;
                }
                else if(uvar16 == u5){
                    Vector3 v58;
                    FaceCenter(this, faceIt, v58);
                    if(MinEq(f68, DistanceSquared(v58, v40))){
                        u5 = uvar16;
                    }
                }
            }
            if(!PatchOkay(u5 + gPatchVerts.NumVerts(), i4 + 1)){
                gPatchVerts.Clear();
                mPatches.push_back(i4);
                i4 = 0;
            }
            for(int i = 0; i < 3; i++){
                if(!gPatchVerts.HasVert((*faceIt)[i])){
                    gPatchVerts.Add((*faceIt)[i], mVerts, v40);
                }
            }
            mPatches.push_back(i4);
            mFaces = faces;
        }
    }
}

// matches in retail
Vector3 RndMesh::SkinVertex(const RndMesh::Vert& vert, Vector3* vptr){
    Vector3 ret(0,0,0);
    if(NumBones() > 0){
        const short* indices = vert.boneIndices;
        Transform tf60;
        tf60.Zero();
        bool b1 = false;
        for(int i = 0; i < 4; i++){
            int boneIdx = indices[i];
            if(boneIdx < NumBones()){
                RndTransformable* curBoneTrans = BoneTransAt(boneIdx);
                unsigned short vec16Idx = vert.boneWeights[i];
                if(vec16Idx && curBoneTrans){
                    Transform tf90;
                    Multiply(BoneOffsetAt(boneIdx), curBoneTrans->WorldXfm(), tf90);
                    ScaleAddEq(tf60, tf90, vert.boneWeights.FloatAt(i));
                    b1 = true;
                }
            }
        }
        if(!b1){
            MILO_WARN("This mesh (%s // %s) cannot be skinned properly because it has an invalid, unweighted transform",
                ((Hmx::Object*)this)->Name(), ((Hmx::Object*)this)->Dir()->GetPathName());
            *vptr = vert.norm;
            ret = vert.pos;
        }
        else {
            Multiply(vert.pos, tf60, ret);
            if(vptr){
                *vptr = TransformNormal(vert.norm, tf60.m);
            }
        }
    }
    else {
        const Transform& worldXfm = WorldXfm();
        Multiply(vert.pos, worldXfm, ret);
        if(vptr){
            *vptr = TransformNormal(vert.norm, worldXfm.m);
        }
    }
    return ret;
}

void RndMesh::ClearCompressedVerts() {
    RELEASE(mCompressedVerts);
    mNumCompressedVerts = 0;
}

void RndMesh::SetNumVerts(int num){
    Verts().resize(num, true);
    Sync(0x3F);
}

void RndMesh::SetNumFaces(int num){
    Faces().resize(num);
    Sync(0x3F);
}

void RndMesh::Mats(std::list<RndMat*>& mats, bool){
    if(mMat){
        mMat->SetShaderOpts(GetDefaultMatShaderOpts(this, mMat));
        mats.push_back(mMat);
    }
}

void RndMesh::SetKeepMeshData(bool keep){
    if(keep != mKeepMeshData){
        mKeepMeshData = keep;
        if(!mKeepMeshData){
            mVerts.clear();
            ClearAndShrink(mFaces);
            ClearAndShrink(mPatches);
        }
    }
}

void RndMesh::UpdateApproxLighting(){
    if(sUpdateApproxLight && !TheRnd->UnkE4()){
        RndEnviron* curEnv = RndEnviron::sCurrent;
        if(curEnv){
            mUseCachedBoxLightColors = !mUseCachedBoxLightColors;
            if(mUseCachedBoxLightColors){
                curEnv->ApplyApproxLighting(mBoxLightColorsCached);
            }
            else {
                Vector3& v = WorldXfm().v;
                Sphere s;
                if(MakeWorldSphere(s, false) && s.GetRadius() > 0){
                    v = s.center;
                }
                curEnv->UpdateApproxLighting(&v, mBoxLightColorsCached);
            }
        }
    }
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
    return tree && Intersect(v, tree);
}

DataNode RndMesh::OnAttachMesh(const DataArray* da) {
    RndMesh* m = da->Obj<RndMesh>(2);
    AttachMesh(this, m);
    delete m;
    return 0;
}

DataNode RndMesh::OnGetVertNorm(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2446);
    v = &mVerts[index];
    *da->Var(3) = v->norm.x;
    *da->Var(4) = v->norm.y;
    *da->Var(5) = v->norm.z;
    return 0;
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
    return 0;
}

DataNode RndMesh::OnGetVertXYZ(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2469);
    v = &mVerts[index];
    *da->Var(3) = v->pos.x;
    *da->Var(4) = v->pos.y;
    *da->Var(5) = v->pos.z;
    return 0;
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
    return 0;
}

DataNode RndMesh::OnGetVertUV(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2492);
    v = &mVerts[index];
    *da->Var(3) = v->uv.x;
    *da->Var(4) = v->uv.y;
    return 0;
}

DataNode RndMesh::OnSetVertUV(const DataArray* da) {
    Vert* v;
    s32 index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mVerts.size(), 2502);
    v = &mVerts[index];
    v->uv.x = da->Float(3);
    v->uv.y = da->Float(4);
    Sync(31);
    return 0;
}

DataNode RndMesh::OnGetFace(const DataArray* da) {
    Face* f;
    int index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mFaces.size(), 2513);
    f = &mFaces[index];
    *da->Var(3) = f->v1;
    *da->Var(4) = f->v2;
    *da->Var(5) = f->v3;
    return 0;
}

DataNode RndMesh::OnSetFace(const DataArray* da) {
    Face* f;
    int index = da->Int(2);
    MILO_ASSERT(index >= 0 && index < mFaces.size(), 2524);
    f = &mFaces[index];
    f->v1 = da->Int(3); f->v2 = da->Int(4); f->v3 = da->Int(5);
    Sync(32);
    return 0;
}

DataNode RndMesh::OnUnitizeNormals(const DataArray* da){
    for(Vert* it = Verts().begin(); it != Verts().end(); ++it){
        Normalize(it->norm, it->norm);
    }
    return 0;
}

DataNode RndMesh::OnConfigureMesh(const DataArray* da){
    if(Type() != configurable_mesh) MILO_WARN("Can't configure nonconfigurable mesh %s\n", Name());
    else {
        float fleft = Property(left, true)->Float();
        float fright = Property(right, true)->Float();
        float fheight = Property(height, true)->Float();
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
    return 0;
}

bool RndMesh::HasValidBones(unsigned int* ui) const {
    int idx = 0;
    for(ObjVector<RndBone>::const_iterator it = mBones.begin(); it != mBones.end(); ++it, ++idx){
        if(!it->mBone){
            if(ui) *ui = idx;
            return false;
        }
    }
    if(ui) *ui = mBones.size();
    return true;
}

void RndMesh::RemoveInvalidBones(){
    for(ObjVector<RndBone>::iterator it = mBones.begin(); it != mBones.end(); ){
        if(it->mBone) ++it;
        else it = mBones.erase(it);
    }
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
    SYNC_PROP_BITFIELD_STATIC(mutable, mGeomOwner->mMutable, 0xB90)
    SYNC_PROP_SET(num_verts, Verts().size(), SetNumVerts(_val.Int()))
    SYNC_PROP_SET(num_faces, (int)Faces().size(), SetNumFaces(_val.Int()))
    SYNC_PROP_SET(volume, GetVolume(), SetVolume((Volume)_val.Int()))
    SYNC_PROP_SET(has_valid_bones, HasValidBones(0), _val.Int())
    SYNC_PROP(bones, mBones)
    {
        static Symbol _s("has_ao_calculation");
        if(sym == _s){
            if(_op == kPropSet) mHasAOCalc = _val.Int();
            else _val = DataNode(mHasAOCalc);
            return true;
        }
    }
    {
        static Symbol _s("force_no_quantize");
        if(sym == _s){
            if(_op == kPropSet) mForceNoQuantize = _val.Int();
            else _val = DataNode(mForceNoQuantize);
            return true;
        }
    }
    SYNC_PROP_SET(keep_mesh_data, mKeepMeshData, SetKeepMeshData(_val.Int()))
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop
