#include "rndobj/Line.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"

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