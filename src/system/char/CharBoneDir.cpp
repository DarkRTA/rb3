#include "char/CharBoneDir.h"

CharBoneDir::CharBoneDir() : mRecenter(this), mMoveContext(0), mBakeOutFacing(1), mContextFlags(0), mFilterContext(0), mFilterBones(this, kObjListNoNull) {

}

CharBoneDir::~CharBoneDir(){
    
}