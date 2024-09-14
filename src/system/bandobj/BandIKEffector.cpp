#include "bandobj/BandIKEffector.h"
#include "utl/Symbols.h"

BandIKEffector::BandIKEffector() : mEffector(this, 0), mGround(this, 0), mMore(this, 0), mElbow(this, 0), mConstraints(this), unk64(this, 0) {

}

BandIKEffector::~BandIKEffector(){
    
}

BEGIN_HANDLERS(BandIKEffector)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x388)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(BandIKEffector::Constraint)
    SYNC_PROP(target, o.mTarget)
    SYNC_PROP(finger, o.mFinger)
    SYNC_PROP(weight, o.mWeight)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandIKEffector)
    SYNC_PROP(effector, mEffector)
    SYNC_PROP(ground, mGround)
    SYNC_PROP(more, mMore)
    SYNC_PROP(elbow, mElbow)
    SYNC_PROP(constraints, mConstraints)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS