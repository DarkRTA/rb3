#include "ui/UIListMesh.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(UIListMesh)

UIListMesh::UIListMesh() : mMesh(this, 0), mDefaultMat(this, 0) {

}

RndMat* UIListMesh::DefaultMat() const { return mDefaultMat; }

UIListSlotElement* UIListMesh::CreateElement(UIList* uilist){
    MILO_ASSERT(mMesh, 0x5B);
    return new UIListMeshElement(this, 0);
}

RndTransformable* UIListMesh::RootTrans(){ return mMesh; }

void UIListMesh::Draw(const UIListWidgetDrawState& drawstate, const UIListState& liststate, const Transform& tf, UIComponent::State compstate, Box* box, DrawCommand cmd){
    if(mMesh){
        float somefloat = 1.0f;
        RndMat* themat = 0;
        if(TheLoadMgr.EditMode()){
            themat = mMesh->mMat;
            if(themat) somefloat = themat->mColor.alpha;
        }
        Transform xfm1 = mMesh->mLocalXfm;
        UIListSlot::Draw(drawstate, liststate, tf, compstate, box, cmd);
        mMesh->SetLocalXfm(xfm1);
        if(TheLoadMgr.EditMode()){
            mMesh->SetMat(themat);
            if(themat){
                themat->mColor.alpha = somefloat;
                themat->mDirty |= 1;
            }
        }
    }
}

SAVE_OBJ(UIListMesh, 0x8F)

BEGIN_LOADS(UIListMesh)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListSlot)
    bs >> mMesh >> mDefaultMat;
END_LOADS

BEGIN_COPYS(UIListMesh)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListMesh, m)
    MILO_ASSERT(m, 0x9F);
    COPY_MEMBER_FROM(m, mMesh)
    COPY_MEMBER_FROM(m, mDefaultMat)
END_COPYS

BEGIN_HANDLERS(UIListMesh)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(0xAF)
END_HANDLERS

BEGIN_PROPSYNCS(UIListMesh)
    SYNC_PROP(mesh, mMesh)
    SYNC_PROP(default_mat, mDefaultMat)
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS

inline void UIListMeshElement::Draw(const Transform& tf, float f, UIColor* col, Box* box){
    RndMesh* mesh = mListMesh->mMesh;
    MILO_ASSERT(mesh, 0x1B);
    mesh->SetWorldXfm(tf);
    if(box){
        Box localbox = *box;
        CalcBox(mesh, localbox);
        box->GrowToContain(localbox.mMin, false);
        box->GrowToContain(localbox.mMax, false);
    }
    else {
        if(mMat){
            float alpha = mMat->Alpha();
            mesh->SetMat(mMat);
            mMat->SetAlpha(f * alpha);
            if(col){
                mMat->SetColor(col->GetColor());
            }
            mesh->DrawShowing();
            mMat->SetAlpha(alpha);
        }
    }
}