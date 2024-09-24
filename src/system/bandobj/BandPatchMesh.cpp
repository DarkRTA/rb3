#include "bandobj/BandPatchMesh.h"
#include "bandobj/BandCharDesc.h"
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

BandPatchMesh::MeshPair::PatchPair& BandPatchMesh::MeshPair::AddPatch(bool permanent){
    MILO_ASSERT(!permanent || patches.size() == 0, 0x4BE);
    ObjectDir* dir = mesh.Owner()->Dir();
    const char* name = PatchName();
    RndMesh* mesh = 0;
    if(permanent) mesh = dir->Find<RndMesh>(name, false);
    if(!mesh){
        mesh = Hmx::Object::New<RndMesh>();
        if(permanent){
            mesh->SetName(PatchName(), dir);
            mesh->SetOrder(0.01f);
        }
    }
    AddMappingPatch(mesh);
    return patches.back();
}

const char* BandPatchMesh::MeshPair::PatchName() const {
    if(mesh) return MakeString("%s_patch.mesh", FileGetBase(mesh->Name(), 0));
    else return "";
}

BandPatchMesh::BandPatchMesh(Hmx::Object* o) : mMeshes(o), mRenderTo(true), mSrc(o, 0), mCategory(0) {

}

bool BandPatchMesh::ReProject(){
    PostRender();
    if(mSrc) ProjectPatches(mSrc->LocalXfm(), 0, true);
    PostRender();
    return mRenderTo;
}

void BandPatchMesh::PreRender(BandCharDesc* desc, int iii){
    if(mCategory == 0 || (iii & mCategory)){
        for(ObjVector<MeshPair>::iterator mp = mMeshes.begin(); mp != mMeshes.end(); ++mp){
            MILO_ASSERT(mp->patches.empty(), 0x509);
        }
        if(mSrc){
            for(ObjVector<MeshPair>::iterator mp = mMeshes.begin(); mp != mMeshes.end(); ++mp){
                mp->AddPatch(true);
            }
        }
        ObjectDir* pdir = desc->GetPatchDir();
        if(pdir){
            for(int i = 0; i < desc->mPatches.size(); i++){
                BandCharDesc::Patch& patch = desc->mPatches[i];
                if(patch.mCategory & mCategory){
                    RndMesh* mesh = desc->GetPatchMesh(patch);
                    RndTex* tex = 0;
                    if(patch.mTexture == -1){
                        if(mesh && mesh->GetMat()){
                            tex = mesh->GetMat()->GetDiffuseTex();
                        }
                        else {
                            MILO_WARN("%s could not find texture from placement mesh, category %d.", PathName(pdir), mCategory);
                        }
                    }
                    else tex = desc->GetPatchTex(patch);
                    if(tex){
                        if(!mesh){
                            if(!patch.mMeshName.empty()){
                                MILO_WARN("%s: could not find placement mesh %s", PathName(pdir), patch.mMeshName.c_str());
                            }
                            else ConstructQuad(tex);
                        }
                        else if(patch.mTexture == -1){
                            if(mMeshes.size() == 1){
                                AddMappingPatch(mMeshes[0], mesh);
                            }
                        }
                        else {
                            Transform tf60;
                            if(FindXfm(mesh, patch.mUV, tf60)){
                                Hmx::Matrix3 m88;
                                m88.RotateAboutZ(patch.mRotation);
                                Multiply(m88, tf60.m, tf60.m);
                                tf60.m.x *= (patch.mScale.x * 0.5f);
                                tf60.m.y *= (patch.mScale.y * 0.5f);
                                ProjectPatches(tf60, tex, false);
                            }
                            else {
                                MILO_WARN("Could not project %s onto %s\n", tex->Name(), mesh->Name());
                            }
                        }
                    }
                }
            }
            desc->AddOverlays(*this);
        }
    }
}

void BandPatchMesh::Compress(BandCharDesc* desc){
    ObjectDir* pdir = desc->GetPatchDir();
    for(int i = 0; i < mMeshes.size(); i++){
        for(int j = 0; j < mMeshes[i].patches.size(); j++){
            RndMesh* patch = mMeshes[i].patches[j].mPatch;
            if(patch){
                RndTex* tex = mMeshes[i].patches[j].mTex;
                if(tex && pdir && tex->Dir() == pdir){
                    delete tex;
                }
                if(!patch->Dir()) delete patch;
            }
        }
    }
}

void BandPatchMesh::ListDrawChildren(std::list<RndDrawable*>& list){
    if(mRenderTo){
        for(int i = 0; i < mMeshes.size(); i++){
            for(int j = 0; j < mMeshes[i].patches.size(); j++){
                list.push_back(mMeshes[i].patches[j].mPatch);
            }
        }
    }
}

void BandPatchMesh::AddMappingPatch(BandPatchMesh::MeshPair& pair, RndMesh* mesh){
    MILO_ASSERT(mRenderTo, 0x761);
    mesh->SetTransParent(0, false);
    mesh->CopyBones(0);
    mesh->SetHasAOCalc(false);
    pair.AddMappingPatch(mesh);
}

void BandPatchMesh::ConstructQuad(RndTex* tex){
    MILO_ASSERT(mRenderTo, 0x76B);
    if(mMeshes.size() != 1){
        MILO_WARN("%s: Can't construct quad with %d meshes, must exactly 1", PathName(mMeshes.Owner()), mMeshes.size());
    }
    else Construct(mMeshes[0], tex, true, false, 0);
}

void BandPatchMesh::Construct(BandPatchMesh::MeshPair& meshpair, RndTex* tex, bool quad, bool perm, BandPatchMesh::WorkVerts* wv){
    MILO_ASSERT(quad || wv, 0x77D);
    BandPatchMesh::MeshPair::PatchPair& patchpair = meshpair.AddPatch(perm);
    patchpair.mTex = tex;
    if(mRenderTo){
        patchpair.mPatch->SetTransParent(0, false);
        patchpair.mPatch->CopyBones(0);
        patchpair.mPatch->SetHasAOCalc(false);
    }
    else {
        patchpair.mPatch->SetOrder(0.01f);
        patchpair.mPatch->CopyBones(meshpair.mesh);
        patchpair.mPatch->RndTransformable::Copy(meshpair.mesh, Hmx::Object::kCopyDeep);
        patchpair.mPatch->SetHasAOCalc(meshpair.mesh->HasAOCalc());
    }
    if(quad){
        if(!mRenderTo) MILO_WARN("Generating quad patch for non render to!");
        patchpair.mPatch->Verts().resize(4, true);
        patchpair.mPatch->Faces().resize(2);
        for(int i = 0; i < 4; i++){
            bool b13 = false;
            if(i == 1 || i == 2) b13 = true;
            float x, y;
            if(b13) x = 1.0f;
            else x = 0;
            if(i < 2) y = 1.0f;
            else y = 0;
            Vector2 v30(y, x);
            SetRenderToVert((RndMesh::Vert&)patchpair.mPatch->VertAt(i), v30, v30);
        }
        patchpair.mPatch->Faces()[0].Set(0, 1, 2);
        patchpair.mPatch->Faces()[1].Set(0, 2, 3);
    }
    else wv->SetVertsAndFaces(patchpair.mPatch, mRenderTo);
    patchpair.mPatch->Sync(0x13F);
    RndMeshDeform* deform = RndMeshDeform::FindDeform(patchpair.mPatch);
    delete deform;
    if(perm){
        MakeString("Generated by OutfitConfig patch port to %s", meshpair.mesh->Name());
        if(!quad && !mRenderTo){
            RndMeshDeform* df = RndMeshDeform::FindDeform(meshpair.mesh);
            if(df){
                RndMeshDeform* newdef = Hmx::Object::New<RndMeshDeform>();
                RndMesh* patch = patchpair.mPatch;
                const char* deformname = MakeString("%s.deform", FileGetBase(patch->Name(), 0));
                newdef->SetName(deformname, patch->Dir());
                newdef->Copy(df, Hmx::Object::kCopyDeep);
                newdef->SetMesh(patchpair.mPatch);
                wv->CopyDeformWeights(newdef, df);
            }
        }
    }
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
    SYNC_PROP(patches, o.patches)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(BandPatchMesh)
    SYNC_PROP(meshes, o.mMeshes)
    SYNC_PROP(src, o.mSrc)
    SYNC_PROP(render_to, o.mRenderTo)
    SYNC_PROP(category, o.mCategory)
END_CUSTOM_PROPSYNC