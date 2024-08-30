#include "world/Reflection.h"
#include "rndobj/Cam.h"

WorldReflection::WorldReflection() : mDraws(this, kObjListNoNull), mLodChars(this, kObjListNoNull), mVerticalStretch(1.0f), unkdc(0), unke0(0), mHideList(this, kObjListNoNull),
    mShowList(this, kObjListNoNull), unk104(this, kObjListNoNull), unk114(this, kObjListNoNull) {
    unkdc = ObjectDir::Main()->New<RndCam>("");
}

WorldReflection::~WorldReflection(){
    delete unkdc;
}