#include "char/CharServoBone.h"
#include "char/Character.h"
#include "char/CharBoneDir.h"
#include "char/Waypoint.h"
#include "utl/Symbols.h"

DECOMP_FORCEACTIVE(CharServoBone, ".cb", "bone_facing_delta.pos", "bone_facing.pos", "bone_pelvis")

INIT_REVS(CharServoBone)

CharServoBone::CharServoBone() : mPelvis(0), mFacingRotDelta(0), mFacingPosDelta(0), mFacingRot(0), mFacingPos(0), mMoveSelf(0), mDeltaChanged(0), mRegulate(this, 0) {

}

CharServoBone::~CharServoBone(){

}

void CharServoBone::Highlight(){}

void CharServoBone::SetName(const char* cc, ObjectDir* dir){
    Hmx::Object::SetName(cc, dir);
    mMe = dynamic_cast<Character*>(Dir());
}

void CharServoBone::SetClipType(Symbol sym){
    if(sym != mClipType){
        mClipType = sym;
        ClearBones();
        CharBoneDir::StuffBones(*this, mClipType);
    }
}

void CharServoBone::Enter(){
    ZeroDeltas();
    mRegulate = 0;
    mDeltaChanged = false;
    mMoveSelf = mFacingPosDelta;
}

void CharServoBone::ZeroDeltas(){
    if(mFacingPosDelta) mFacingPosDelta->Zero();
    if(!mFacingRotDelta) return;
    *mFacingRotDelta = 0.0f;
}

void CharServoBone::SetMoveSelf(bool b){
    if(mMoveSelf == b) return;
    mMoveSelf = b;
    mDeltaChanged = true;
}

SAVE_OBJ(CharServoBone, 0x14A)

BEGIN_LOADS(CharServoBone)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    Symbol s;
    if(gRev > 1) bs >> s;
    SetClipType(s);
END_LOADS

BEGIN_COPYS(CharServoBone)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharServoBone)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMoveSelf)
        SetClipType(c->mClipType);
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharServoBone)
    HANDLE_SUPERCLASS(CharPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x16E)
END_HANDLERS

BEGIN_PROPSYNCS(CharServoBone)
    SYNC_PROP_SET(clip_type, mClipType, SetClipType(_val.Sym(0)))
    SYNC_PROP_SET(move_self, mMoveSelf, SetMoveSelf(_val.Int(0)))
    SYNC_PROP(delta_changed, mDeltaChanged)
    SYNC_PROP(regulate, mRegulate)
    SYNC_SUPERCLASS(CharBonesMeshes)
END_PROPSYNCS