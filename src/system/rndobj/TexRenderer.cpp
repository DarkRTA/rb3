#include "rndobj/TexRenderer.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "revolution/gx/GXPixel.h"
#include "rndobj/Draw.h"
#include "rndobj/Graph.h"
#include "rndobj/Mat.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "rndobj/Dir.h"
#include "rndwii/Mat.h"
#include "utl/Messages3.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(RndTexRenderer)

RndTexRenderer::RndTexRenderer()
    : mDirty(1), mForce(0), mDrawPreClear(1), mDrawWorldOnly(0), mDrawResponsible(1),
      mNoPoll(0), mPrimeDraw(0), mFirstDraw(1), mForceMips(0), mImposterHeight(0.0f),
      mOutputTexture(this, 0), mDraw(this, 0), mCam(this, 0), mMirrorCam(this, 0) {}

RndTexRenderer::~RndTexRenderer() {}

void RndTexRenderer::ListAnimChildren(std::list<RndAnimatable *> &children) const {
    RndDrawable *draw = mDraw;
    RndAnimatable *anim = dynamic_cast<RndAnimatable *>(draw);
    if (anim)
        children.push_back(anim);
}

void RndTexRenderer::ListDrawChildren(std::list<RndDrawable *> &children) {
    if (mDraw && mDrawResponsible)
        children.push_back(mDraw);
}

void RndTexRenderer::ListPollChildren(std::list<RndPollable *> &children) const {
    RndDrawable *draw = mDraw;
    if (draw && mNoPoll) {
        RndPollable *poll = dynamic_cast<RndPollable *>(draw);
        if (poll)
            children.push_back(poll);
    }
}

void RndTexRenderer::Enter() { RndPollable::Enter(); }

void RndTexRenderer::DrawShowing() {
    if (mDrawPreClear)
        return;
    else
        DrawToTexture();
}

float ComputeAngle(const Vector3 &, const Vector3 &, const Vector3 &);

#pragma push
#pragma dont_inline on
#pragma auto_inline on
void RndTexRenderer::DrawToTexture() {
    if (TheRnd->DrawMode() == 0) {
        if (((Hmx::Object *)Dir() == mDraw) || !Showing())
            return;
        else {
            if (!mDrawWorldOnly || TheRnd->ProcCmds() & kProcessWorld) {
                if (mDirty && mDraw && mOutputTexture) {
                    if (!(mOutputTexture->GetType() & kProcessPost)) {
                        MILO_NOTIFY_ONCE("%s not renderable", mOutputTexture->Name());
                        return;
                    }
                    Transform tf98;
                    float f33 = 0;
                    if (!mForce)
                        HandleType(pre_render_msg);
                    RndCam *cam;
                    RndDir *rdir = dynamic_cast<RndDir *>(mDraw.Ptr());
                    if (mImposterHeight && rdir) {
                        cam = RndCam::Current();
                        tf98 = cam->WorldXfm();
                        f33 = cam->YFov();
                        Transform tfc8;
                        Transpose(rdir->WorldXfm().m, tfc8.m);
                        Multiply(cam->WorldXfm().m, tfc8.m, tfc8.m);
                        Subtract(cam->WorldXfm().v, rdir->WorldXfm().v, tfc8.v);
                        tfc8.v.z -= mImposterHeight / 2.0f;
                        float f34 =
                            Max(Length(tfc8.v),
                                mImposterHeight / 2.0f + cam->NearPlane());
                        Multiply(Vector3(0, -f34, 0), tfc8.m, tfc8.v);
                        tfc8.v.z += mImposterHeight / 2.0f;
                        cam->SetWorldXfm(tfc8);
                        float atanned = atanf(mImposterHeight / 2.0f / f34);
                        cam->SetFrustum(
                            cam->NearPlane(), cam->FarPlane(), atanned * 2.0f, 1.0f
                        );
                    } else {
                        cam = mCam;
                        if (!cam)
                            cam = mDraw->CamOverride();
                        if (rdir && !cam)
                            cam = dynamic_cast<RndCam *>(rdir->CurCam());
                        if (!cam)
                            cam = TheRnd->DefaultCam();
                        if (cam == TheRnd->DefaultCam())
                            tf98 = cam->WorldXfm();
                    }
                    RndCam *current = RndCam::Current();
                    RndTex *targetTex = current->TargetTex();
                    if (targetTex) {
                        MILO_NOTIFY_ONCE(
                            "%s: Cannot render to texture (%s) while already rendering to texture (%s).",
                            PathName(targetTex),
                            PathName(this),
                            PathName(targetTex)
                        );
                    }
                    RndMesh *mesh5 = nullptr;
                    if (mMirrorCam) {
                        RndMat *mat4 = nullptr;
                        FOREACH_OBJREF (it, mOutputTexture) {
                            mat4 = dynamic_cast<RndMat *>((*it)->RefOwner());
                            if (mat4)
                                break;
                        }
                        if (mat4) {
                            FOREACH_OBJREF (it, mat4) {
                                mesh5 = dynamic_cast<RndMesh *>((*it)->RefOwner());
                                if (mesh5)
                                    break;
                            }
                        }
                        if (!mesh5) {
                            MILO_NOTIFY_ONCE(
                                "%s could not find mesh to mirror about. Is %s not being mapped onto a mesh?",
                                Name(),
                                mOutputTexture->Name()
                            );
                            return;
                        }
                        if (!mesh5->GetKeepMeshData()) {
                            MILO_NOTIFY_ONCE(
                                "%s could not do mirroring because the mesh %s doesn't have its keep_mesh_data flag turned on. ",
                                Name(),
                                mesh5->Name()
                            );
                            return;
                        }
                        RndMesh::Face &curFace = mesh5->Faces(0);
                        Transform &meshXfm = mesh5->WorldXfm();
                        RndMesh::Vert *verts[3] = { &mesh5->Verts(curFace.v1),
                                                    &mesh5->Verts(curFace.v2),
                                                    &mesh5->Verts(curFace.v3) };
                        Vector3 vertVectors[3] = { verts[0]->pos,
                                                   verts[1]->pos,
                                                   verts[2]->pos };
                        Multiply(vertVectors[0], meshXfm, vertVectors[0]);
                        Multiply(vertVectors[1], meshXfm, vertVectors[1]);
                        Multiply(vertVectors[2], meshXfm, vertVectors[2]);
                        Vector3 v294;
                        mesh5->SkinVertex(*verts[0], &v294);
                        Normalize(v294, v294);
                        Transform tf120;
                        tf120.v = meshXfm.v;
                        tf120.m.z = v294;
                        Subtract(vertVectors[1], vertVectors[0], tf120.m.x);
                        Normalize(tf120.m.x, tf120.m.x);
                        Cross(tf120.m.z, tf120.m.x, tf120.m.y);
                        Transform tf150;
                        Invert(tf120, tf150);
                        cam->SetWorldXfm(mMirrorCam->WorldXfm());
                        Transform tf180;
                        tf180.Reset();
                        tf180.m.z.z = -1.0f;
                        Multiply(tf150, tf180, tf180);
                        Multiply(tf180, tf120, tf180);
                        Multiply(mMirrorCam->WorldXfm(), tf180, cam->DirtyLocalXfm());
                        Hmx::Matrix3 m1a8;
                        Hmx::Matrix3 m1cc;
                        for (int i = 0; i < 3; i++) {
                            m1a8[i].Set(verts[i]->uv.x, verts[i]->uv.y, 1.0f);
                            m1cc[i] = vertVectors[i];
                        }
                        Hmx::Matrix3 m1f0;
                        Invert(m1a8, m1a8);
                        Multiply(m1a8, m1cc, m1f0);
                        Vector3 v2a0(0.5f, 0.0f, 1.0f);
                        Vector3 v2ac(0.5f, 1.0f, 1.0f);
                        Multiply(v2a0, m1f0, v2a0);
                        Multiply(v2ac, m1f0, v2ac);
                        float f28 = ComputeAngle(cam->WorldXfm().v, v2a0, v2ac);
                        Transform tf220(cam->WorldXfm());
                        Vector3 v2b8;
                        Multiply(Vector3(0.5f, 0.5f, 1.0f), m1f0, v2b8);
                        tf220.LookAt(v2b8, Vector3(0, 0, 1));
                        cam->SetWorldXfm(tf220);
                        Vector3 vecs248[3] = { Vector3(0, 0, 1),
                                               Vector3(0, 1, 1),
                                               Vector3(1, 0, 1) };
                        for (int i = 0; i < 3; i++) {
                            Multiply(vecs248[i], m1f0, vecs248[i]);
                        }
                        Vector3 v2c4;
                        Subtract(vecs248[2], vecs248[0], v2c4);
                        Vector3 va0;
                        Subtract(vecs248[1], vecs248[0], va0);
                        cam->SetFrustum(
                            cam->NearPlane(),
                            cam->FarPlane(),
                            f28,
                            Length(va0) / Length(v2c4)
                        );
                        if (DataVariable("rndtex.debug_mirror").Int()) {
                            RndGraph *graph = RndGraph::GetOneFrame();
                            Vector3 vecs278[4] = { Vector3(0, 0, 1),
                                                   Vector3(0, 1, 1),
                                                   Vector3(1, 0, 1),
                                                   Vector3(1, 1, 1) };
                            for (int i = 0; i < 4; i++) {
                                Multiply(vecs278[i], m1f0, vecs278[i]);
                                graph->AddSphere(vecs278[i], 2.0f, Hmx::Color(1, 1, 1));
                            }
                            graph->AddSphere(v2a0, 1.0f, Hmx::Color(0, 0, 1));
                            graph->AddSphere(v2ac, 1.0f, Hmx::Color(0, 0, 1));
                            for (int i = 0; i < 3; i++) {
                                graph->AddSphere(
                                    vertVectors[i], 1.0f, Hmx::Color(1, 0, 0)
                                );
                            }
                        }
                    }

                    cam->SetTargetTex(mOutputTexture);
                    cam->Select();
                    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
                    WiiMat::SetOverrideAlphaWrite(true);
                    int cap = (mFirstDraw && mPrimeDraw) ? 2 : 1;
                    for (int i = 0; i < cap; i++) {
                        DrawBefore();
                        if (rdir && rdir->ClassName() == "WorldDir") {
                            rdir->RndDir::DrawShowing();
                        } else
                            mDraw->DrawShowing();
                        DrawAfter();
                    }
                    cam->SetTargetTex(nullptr);
                    if (!mMirrorCam) {
                        if (mImposterHeight) {
                            cam->SetWorldXfm(tf98);
                            cam->SetFrustum(cam->NearPlane(), cam->FarPlane(), f33, 1.0f);
                        } else if (cam == TheRnd->DefaultCam()) {
                            cam->SetWorldXfm(tf98);
                        }
                    }
                    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
                    WiiMat::SetOverrideAlphaWrite(false);
                    current->Select();
                    mFirstDraw = false;
                    if (!mForce)
                        HandleType(post_render_msg);
                }
                if (!mForce)
                    mDirty = false;
            }
        }
    }
}
#pragma pop

float RndTexRenderer::StartFrame() {
    RndDrawable *draw = mDraw;
    RndAnimatable *anim = dynamic_cast<RndAnimatable *>(draw);
    if (anim) {
        return anim->StartFrame();
    } else
        return 0.0f;
}

float RndTexRenderer::EndFrame() {
    RndDrawable *draw = mDraw;
    RndAnimatable *anim = dynamic_cast<RndAnimatable *>(draw);
    if (anim) {
        return anim->EndFrame();
    } else
        return 0.0f;
}

void RndTexRenderer::SetFrame(float f1, float f2) {
    RndDrawable *draw = mDraw;
    RndAnimatable *anim = dynamic_cast<RndAnimatable *>(draw);
    if (anim) {
        anim->SetFrame(f1, f2);
        mDirty = true;
    }
}

void RndTexRenderer::UpdatePreClearState() {
    TheRnd->PreClearDrawAddOrRemove(this, mDrawPreClear, false);
    mDirty = true;
}

BEGIN_COPYS(RndTexRenderer)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndPollable)
    CREATE_COPY(RndTexRenderer)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDraw)
        COPY_MEMBER(mCam)
        COPY_MEMBER(mOutputTexture)
        COPY_MEMBER(mForce)
        COPY_MEMBER(mDrawWorldOnly)
        COPY_MEMBER(mDrawResponsible)
        COPY_MEMBER(mImposterHeight)
        COPY_MEMBER(mDrawPreClear)
        COPY_MEMBER(mPrimeDraw)
        COPY_MEMBER(mForceMips)
        COPY_MEMBER(mMirrorCam)
        COPY_MEMBER(mNoPoll)
        InitTexture();
        mDirty = true;
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndTexRenderer, 0x1FA)

BEGIN_LOADS(RndTexRenderer)
    LOAD_REVS(bs)
    ASSERT_REVS(0xB, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if (gRev > 2) {
        LOAD_SUPERCLASS(RndAnimatable)
        LOAD_SUPERCLASS(RndDrawable)
        if (gRev > 10)
            LOAD_SUPERCLASS(RndPollable)
    }
    if (gRev < 1) {
        FilePath fp;
        bs >> fp;
    } else {
        mDraw.Load(bs, false, nullptr);
    }
    if (gRev > 3)
        bs >> mCam;
    else
        mCam = 0;
    bs >> mOutputTexture;
    InitTexture();
    if (gRev > 1)
        bs >> mForce >> mImposterHeight;
    if (gRev > 4)
        bs >> mDrawResponsible;
    else
        mDrawResponsible = true;
    if (gRev > 5)
        bs >> mDrawPreClear;
    else
        mDrawPreClear = false;
    if (gRev > 6)
        bs >> mDrawWorldOnly;
    if (gRev > 7)
        bs >> mPrimeDraw;
    if (gRev > 8)
        bs >> mForceMips;
    if (gRev > 9)
        bs >> mMirrorCam;
    if (gRev > 10)
        bs >> mNoPoll;
    mDirty = true;
END_LOADS

void RndTexRenderer::InitTexture() {
    if (mForceMips) {
        RndTex *tex = mOutputTexture;
        if (tex)
            tex->SetBitmap(tex->mWidth, tex->mHeight, tex->mBpp, tex->mType, true, 0);
    }
    mDirty = true;
}

DataNode RndTexRenderer::OnGetRenderTextures(DataArray *da) {
    return GetRenderTextures(Dir());
}

BEGIN_HANDLERS(RndTexRenderer)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE(get_render_textures, OnGetRenderTextures)
    HANDLE_CHECK(0x280)
END_HANDLERS

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndTexRenderer)
    SYNC_PROP_MODIFY_ALT(draw, mDraw, mDirty = true; mFirstDraw = true;)
    SYNC_PROP_MODIFY_ALT(cam, mCam, mDirty = true)
    SYNC_PROP_MODIFY_ALT(output_texture, mOutputTexture, InitTexture())
    SYNC_PROP_MODIFY(force, mForce, mDirty = true)
    SYNC_PROP_MODIFY(imposter_height, mImposterHeight, mDirty = true)
    SYNC_PROP_MODIFY(draw_pre_clear, mDrawPreClear, UpdatePreClearState()) {
        static Symbol _s("draw_world_only");
        if (sym == _s) {
            if (_op == kPropSet)
                mDrawWorldOnly = _val.Int();
            else
                _val = DataNode(mDrawWorldOnly);
            return true;
        }
    }
    {
        static Symbol _s("draw_responsible");
        if (sym == _s) {
            if (_op == kPropSet)
                mDrawResponsible = _val.Int();
            else
                _val = DataNode(mDrawResponsible);
            return true;
        }
    }
    {
        static Symbol _s("no_poll");
        if (sym == _s) {
            if (_op == kPropSet)
                mNoPoll = _val.Int();
            else
                _val = DataNode(mNoPoll);
            return true;
        }
    }
    SYNC_PROP_MODIFY(prime_draw, mPrimeDraw, mDirty = true)
    SYNC_PROP_MODIFY_ALT(force_mips, mForceMips, InitTexture())
    SYNC_PROP_MODIFY_ALT(mirror_cam, mMirrorCam, mDirty = true)
    SYNC_SUPERCLASS(RndAnimatable)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndPollable)
END_PROPSYNCS
#pragma pop
