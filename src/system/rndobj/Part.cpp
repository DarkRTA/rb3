#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"

RndParticleSys::~RndParticleSys(){
    
}

RndParticleSys::RndParticleSys() : unkc8(0), mMaxParticles(0), unkd0(0), unkd4(0), unkd8(0), unkdc(0), unke0(0.0f), unke4(0.0f), mMesh(this, 0),
    mMat(this, 0), unk210(this, 0), mBounce(this, 0), mGrowRatio(0.0f) {

}