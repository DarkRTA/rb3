#include "world/FreeCamera.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "math/Rot.h"

FreeCamera::FreeCamera(WorldDir* dir, float f1, float f2, int i) : mParent(0), mFrozen(0), mPadNum(i), mRotateRate(f1), mSlewRate(f2),
    mUseParentRotateX(1), mUseParentRotateY(1), mUseParentRotateZ(1), mWorld(dir) {
    UpdateFromCamera();
}

FreeCamera::~FreeCamera(){

}

void FreeCamera::UpdateFromCamera(){
    TheDOFProc->FocalPlane();
}

void FreeCamera::SetParentDof(bool b1, bool b2, bool b3){
    mUseParentRotateX = b1;
    mUseParentRotateY = b2;
    mUseParentRotateZ = b3;
}

void FreeCamera::Poll(){
    TheDOFProc->Enabled();
    TheDOFProc->BlurDepth();
    TheDOFProc->MaxBlur();
    TheDOFProc->MinBlur();
}

BEGIN_HANDLERS(FreeCamera)
    HANDLE_ACTION(set_parent, mParent = _msg->Obj<RndTransformable>(2))
    HANDLE_ACTION(set_pos, mXfm.v.Set(_msg->Float(2), _msg->Float(3), _msg->Float(4)))
    HANDLE_ACTION(set_rot, mRot = Vector3(_msg->Float(2) * RAD2DEG, _msg->Float(3) * RAD2DEG, _msg->Float(4) * RAD2DEG))
    HANDLE_ACTION(set_parent_dof, SetParentDof(_msg->Int(2), _msg->Int(3), _msg->Int(4)))
    HANDLE_ACTION(set_frozen, mFrozen = _msg->Int(2))
    HANDLE_CHECK(0xDC)
END_HANDLERS
