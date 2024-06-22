#include "rndobj/Gen.h"
#include "rndobj/TransAnim.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"

RndGenerator::RndGenerator() : mPath(this, 0), mPathStartFrame(0.0f), mPathEndFrame(0.0f), mMesh(this, 0), mMultiMesh(this, 0), mParticleSys(this, 0), 
    mNextFrameGen(-9999999.0f), mRateGenLow(100.0f), mRateGenHigh(100.0f), mScaleGenLow(1.0f), mScaleGenHigh(1.0f),
    mPathVarMaxX(0.0f), mPathVarMaxY(0.0f), mPathVarMaxZ(0.0f), mCurMultiMesh(0) {

}

RndGenerator::~RndGenerator(){
    
}