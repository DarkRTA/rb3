#include "char/CharServoBone.h"
#include "char/Waypoint.h"

CharServoBone::CharServoBone() : mPelvis(0), mFacingRotDelta(0), mFacingPosDelta(0), mFacingRot(0), mFacingPos(0), mMoveSelf(0), mDeltaChanged(0), mWay(this, 0) {

}

CharServoBone::~CharServoBone(){

}

    // RndEnviron* mPelvis;
    // float* mFacingRotDelta;
    // Vector3* mFacingPosDelta;
    // float* mFacingRot;
    // Vector3* mFacingPos;
    // bool mMoveSelf;
    // bool mDeltaChanged;
    // Character* mMe;
    // Symbol mClipType;
    // ObjPtr<Waypoint, ObjectDir> mWay;