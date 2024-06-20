#include "rndobj/PartLauncher.h"

RndPartLauncher::RndPartLauncher() : mPart(this, 0), mTrans(this, 0), mMeshEmitter(this, 0), mNumParts(0), mEmitRate(0.0f, 0.0f), mEmitCount(0.0f), mPartOverride(&gNoPartOverride) {

}