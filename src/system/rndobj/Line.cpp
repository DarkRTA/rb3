#include "rndobj/Line.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "types.h"
#include "utl/Symbols4.h"
#include <math.h>

static int LINE_REV = 4;

void RndLine::SetMat(RndMat* mat) {
    mMat = mat;
    mMesh->SetMat(mat);
}

SAVE_OBJ(RndLine, 535)

void RndLine::UpdateInternal() {
    mFoldCos = cos(mFoldAngle);
    mMesh->SetMat(mMat);
    SetNumPoints(mPoints.size());
}

BinStream& operator>>(BinStream& bs, RndLine::Point point) {
    bs >> point.v >> point.c;
    return bs;
}

BEGIN_LOADS(RndLine)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, LINE_REV)
    if (rev > 3) {
        Hmx::Object::Load(bs);
    }
    RndDrawable::Load(bs);
    if (rev < 3) {
        ObjPtrList<Hmx::Object, ObjectDir> list(this, kObjListNoNull);
        u32 _;
        bs >> _ >> list;
    }
    RndTransformable::Load(bs);
    bs >> mMat >> mPoints >> mWidth;
    if (rev > 0) {
        bs >> mFoldAngle;
        LOAD_BITFIELD(u8, mLineHasCaps)
    }
    if (rev > 1) {
        LOAD_BITFIELD(u8, mLinePairs)
    }
    UpdateInternal();
END_LOADS

TextStream& operator<<(TextStream&, const RndLine::Point&){

}

void RndLine::Print(){
    TheDebug << "   points: " << mPoints << "\n";
    TheDebug << "   width: " << mWidth << "\n";
    TheDebug << "   foldAngle: " << mFoldAngle << "\n";
    TheDebug << "   hasCaps: " << mLineHasCaps << "\n";
    TheDebug << "   linePairs:" << mLinePairs << "\n";
}

RndLine::RndLine() : mWidth(1.0f), mFoldAngle(1.570796f), mMat(this, 0) {
    mLineHasCaps = true;
    mLinePairs = false;
    mLineUpdate = true;
    mMesh = Hmx::Object::New<RndMesh>();
    mMesh->mGeomOwner->mMutable = 0x1F;
    mMesh->SetTransParent(this, false);
    UpdateInternal();
}

RndLine::~RndLine(){

}

DataNode RndLine::OnSetMat(const DataArray* array) {
    RndMat* mat = array->Obj<RndMat>(2);
    SetMat(mat);
    mShowing = mat;
    return 0;
}

BEGIN_HANDLERS(RndLine)
    HANDLE_EXPR(num_points, (int)mPoints.size())
    HANDLE_ACTION(set_point_pos, {
        Vector3 v(_msg->Float(2),_msg->Float(3),_msg->Float(4));
        SetPointPos(_msg->Int(1), v);
        })
    HANDLE_ACTION(set_update, SetUpdate(_msg->Int(2)))
    HANDLE(set_mat, OnSetMat)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(797)
END_HANDLERS

BEGIN_PROPSYNCS(RndLine)
    SYNC_PROP(width, mWidth);
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS
