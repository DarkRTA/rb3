#include "TrackWidgetImp.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/Text.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "rndwii/MultiMesh.h"
#include "utl/Loader.h"

void ImmediateWidgetImp::DrawInstances(const ObjPtrList<RndMesh> &meshes, int i2) {
    Transform tf68;
    int idx = 0;
    for (ObjPtrList<RndMesh>::iterator it = meshes.begin(); it != meshes.end();
         ++idx, ++it) {
        if (i2 >= 0 && idx >= i2)
            break;
        RndMesh *mesh = *it;
        if (LOADMGR_EDITMODE) {
            tf68 = mesh->LocalXfm();
        }
        std::list<RndMultiMesh::Instance>::iterator instIt;
        if (mesh->HasDynamicConstraint()) {
            for (instIt = mInstances.begin(); instIt != mInstances.end(); ++instIt) {
                mesh->SetLocalXfm(instIt->mXfm);
                mesh->DrawShowing();
            }
        } else if (mesh->NumBones() > 0) {
            RndTransformable *t = mesh->BoneTransAt(0);
            Vector3 va8(0, 0, 0);
            Transform tf98;
            for (instIt = mInstances.begin(); instIt != mInstances.end(); ++instIt) {
                tf98 = instIt->mXfm;
                va8.y = tf98.m.y.y;
                tf98.m.y.y = 1;
                t->SetLocalPos(va8);
                mesh->SetWorldXfm(tf98);
                mesh->DrawShowing();
            }
        } else if (mAllowRotation) {
            mesh->WorldXfm();
            for (instIt = mInstances.begin(); instIt != mInstances.end(); ++instIt) {
                mesh->SetWorldPos(instIt->mXfm.v);
                mesh->DrawShowing();
            }
        } else {
            for (instIt = mInstances.begin(); instIt != mInstances.end(); ++instIt) {
                mesh->SetWorldXfm(instIt->mXfm);
                mesh->DrawShowing();
            }
        }
        if (LOADMGR_EDITMODE) {
            mesh->SetLocalXfm(tf68);
        }
    }
}

MultiMeshWidgetImp::MultiMeshWidgetImp(const ObjPtrList<RndMesh> &meshlist, bool b)
    : mMeshes(meshlist), unk10(b) {
    for (int i = 0; i < mMeshes.size(); i++) {
        mMultiMeshes.push_back(Hmx::Object::New<RndMultiMesh>());
    }
}

MultiMeshWidgetImp::~MultiMeshWidgetImp() {
    for (int i = 0; i < mMultiMeshes.size(); i++)
        delete mMultiMeshes[i];
}

void MultiMeshWidgetImp::Init() {
    int idx = 0;
    FOREACH (it, mMeshes) {
        RndMesh *cur = *it;
        mMultiMeshes[idx]->SetMesh(cur);
        idx++;
    }
}

std::list<RndMultiMesh::Instance> &MultiMeshWidgetImp::Instances() {
    MILO_FAIL("MultiMeshWidgetImp::Instances() called; not implemented");
    return mMultiMeshes.front()->mInstances;
}

void MultiMeshWidgetImp::PushInstance(RndMultiMesh::Instance &inst) {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        mMultiMeshes[i]->mInstances.push_back(inst);
    }
}

void MultiMeshWidgetImp::DrawInstances(const ObjPtrList<RndMesh> &meshes, int i2) {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        RndMultiMesh *mesh = mMultiMeshes[i];
        if (unk10) {
            WiiMultiMesh *wiiMesh = dynamic_cast<WiiMultiMesh *>(mesh);
            wiiMesh->unk34 = true;
            mesh->DrawShowing();
        }
        if (i2 >= 0 && i <= i2)
            break;
    }
}

bool MultiMeshWidgetImp::Empty() {
    if (mMultiMeshes.empty())
        return true;
    else
        return mMultiMeshes.front()->mInstances.empty();
}

int MultiMeshWidgetImp::Size() {
    if (mMultiMeshes.empty())
        return 0;
    else
        return mMultiMeshes.front()->mInstances.size();
}

void MultiMeshWidgetImp::Clear() {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        DoClear(mMultiMeshes[i]->mInstances);
    }
}

void MultiMeshWidgetImp::RemoveUntil(float f1, float f2) {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        RndMultiMesh *mesh = mMultiMeshes[i];
        std::list<RndMultiMesh::Instance> &insts = mesh->mInstances;
        DoRemoveUntil(insts, f1, f2);
    }
}

void MultiMeshWidgetImp::RemoveAt(float f1, float f2, float f3) {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        RndMultiMesh *mesh = mMultiMeshes[i];
        std::list<RndMultiMesh::Instance> &insts = mesh->mInstances;
        DoRemoveAt(insts, f1, f2, f3);
    }
}

float MultiMeshWidgetImp::GetFirstInstanceY() {
    if (mMultiMeshes.empty())
        return 0;
    else
        return DoGetFirstInstanceY(mMultiMeshes.front()->mInstances);
}

float MultiMeshWidgetImp::GetLastInstanceY() {
    if (mMultiMeshes.empty())
        return 0;
    else
        return DoGetLastInstanceY(mMultiMeshes.front()->mInstances);
}

void MultiMeshWidgetImp::Sort() {
    for (int i = 0; i < mMultiMeshes.size(); i++) {
        RndMultiMesh *mesh = mMultiMeshes[i];
        std::list<RndMultiMesh::Instance> &insts = mesh->mInstances;
        DoSort(insts);
    }
}

CharWidgetImp::CharWidgetImp(
    RndFont *f,
    RndText *t,
    int i1,
    int i2,
    RndText::Alignment a,
    Hmx::Color32 c1,
    Hmx::Color32 c2,
    bool b7
)
    : mNeedRebuild(true), mNeedSync(false), mCharsPerInst(i1), mMaxInstances(i2),
      mText(t), mFont(f) {
    if (Valid()) {
        mText->SetFixedLength(mCharsPerInst * mMaxInstances);
        mText->ReserveLines(mMaxInstances);
        mReusableLines.reserve(mMaxInstances);
        mText->SetAlignment(a);
        mText->SetColor(c1);
        mText->SetAltStyle(
            mText->mStyle.font,
            mText->mStyle.size,
            &c2,
            mText->mStyle.zOffset,
            mText->mStyle.italics,
            true
        );
        mText->unk124b4p1 = b7;
        Transform tf60;
        tf60.Reset();
        mText->SetWorldXfm(tf60);
    }
}

void CharWidgetImp::PushInstance(TextInstance &inst) {
    if (Valid()) {
        Instances().push_back(inst);
        TextInstance &firstInst = Instances().back();
        MILO_ASSERT(mText, 0x159);
        if (mText->GetAlignment() & 4) {
            int len = firstInst.mText.length();
            if (mCharsPerInst - len > 0) {
                String newStr(mCharsPerInst - len, ' ');
                firstInst.mText =
                    MakeString("%s%s", newStr.c_str(), firstInst.mText.c_str());
            }
        }
        if (mReusableLines.empty()) {
            RndText::Style &style =
                firstInst.mUseAltStyle ? mText->mAltStyle : mText->mStyle;
            firstInst.mLineId = mText->AddLineUTF8(
                firstInst.mText, firstInst.mXfm, style, nullptr, &mNeedSync, mCharsPerInst
            );
            if (firstInst.mLineId == -1) {
                MILO_WARN(
                    "CharWidgetImp::PushInstance() - AddLineUTF8 failed; please alert Track/HUD coder"
                );
            }
        } else {
            firstInst.mLineId = mReusableLines.back();
            RndText::Style &style =
                firstInst.mUseAltStyle ? mText->mAltStyle : mText->mStyle;
            mText->ReplaceLineText(
                firstInst.mLineId,
                firstInst.mText,
                firstInst.mXfm,
                style,
                nullptr,
                &mNeedSync,
                mCharsPerInst
            );
            mReusableLines.pop_back();
        }
    }
}

std::list<TextInstance> &CharWidgetImp::Instances() { return mInstances; }

void CharWidgetImp::SetScale(float f) { SetLocalScale(mText, Vector3(f, 1, f)); }

void CharWidgetImp::RemoveInstances(
    std::list<TextInstance> &insts,
    std::list<TextInstance>::iterator from,
    std::list<TextInstance>::iterator to
) {
    if (Valid()) {
        std::list<TextInstance>::iterator it = from;
        for (; it != to; ++it) {
            TextInstance &cur = *it;
            int id = cur.mLineId;
            if (id < 0 || id >= mMaxInstances) {
                MILO_WARN("widget instance in unexpected state - rebuilding");
                mNeedRebuild = true;
            } else {
                Transform tf50;
                tf50.Reset();
                mText->ReplaceLineText(
                    id,
                    "",
                    tf50,
                    cur.mUseAltStyle ? mText->mAltStyle : mText->mStyle,
                    nullptr,
                    &mNeedSync,
                    mCharsPerInst
                );
                mReusableLines.push_back(id);
            }
        }
        insts.erase(from, to);
    }
}

void CharWidgetImp::Poll() {
    if (Valid()) {
        if (mNeedRebuild) {
            mText->SetText("");
            mReusableLines.clear();
            std::list<TextInstance>::iterator it = Instances().begin();
            std::list<TextInstance>::iterator itEnd = Instances().end();
            for (; it != itEnd; ++it) {
                TextInstance &cur = *it;
                int id;
                cur.mLineId = id = mText->AddLineUTF8(
                    cur.mText,
                    cur.mXfm,
                    cur.mUseAltStyle ? mText->mAltStyle : mText->mStyle,
                    nullptr,
                    &mNeedSync,
                    mCharsPerInst
                );
                if (id == -1) {
                    MILO_WARN(
                        "CharWidgetImp::Poll() - AddLineUTF8 failed; please alert Track/HUD coder"
                    );
                }
            }
            mNeedRebuild = false;
        }
        if (mNeedSync) {
            mText->SetMeshForceNoQuantize();
            mText->SyncMeshes();
            mNeedSync = false;
        }
    }
}

void CharWidgetImp::DrawInstances(const ObjPtrList<RndMesh> &, int) {
    if (Valid()) {
        mText->SetMeshForceNoUpdate();
        mText->DrawShowing();
    }
}

void CharWidgetImp::Clear() {
    Instances().clear();
    SetDirty(true);
}

// std::list<MeshInstance>* MatWidgetImp::Instances() { return &mInstances; }

// void CharWidgetImp::SetDirty(bool b) { mDirty = b; }

// int CharWidgetImp::AddTextInstance(Transform t, String s, bool b) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     TextInstance i(t, s);
//     PushInstance(i);
//     if (x) Sort();
//     return x;
// }

// int MultiMeshWidgetImp::AddInstance(Transform t, float) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     RndMultiMesh::Instance i(t);
//     PushInstance(i);
//     if (x) Sort();
//     return x;
// }

// std::list<RndMultiMesh::Instance>* ImmediateWidgetImp::Instances() { return
// &mInstances; }

// int ImmediateWidgetImp::AddInstance(Transform t, float) {
//     int x = 0;
//     if (!Empty() && t.v.y < GetLastInstanceY()) x = 1;
//     RndMultiMesh::Instance i(t);
//     PushInstance(i);
//     if (x) Sort();
//     return x;
// }
