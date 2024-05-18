#include "char/CharServoBone.h"
#include "char/Character.h"
#include "char/Waypoint.h"

CharServoBone::CharServoBone() : mPelvis(0), mFacingRotDelta(0), mFacingPosDelta(0), mFacingRot(0), mFacingPos(0), mMoveSelf(0), mDeltaChanged(0), mWay(this, 0) {

}

CharServoBone::~CharServoBone(){

}

void CharServoBone::Highlight(){}

void CharServoBone::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character*>(mDir);
}