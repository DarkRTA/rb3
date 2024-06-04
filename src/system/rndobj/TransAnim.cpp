#include "rndobj/TransAnim.h"
#include "rndobj/Draw.h"

static int TRANSANIM_REV = 7;

RndTransAnim::RndTransAnim() : mTrans(this, 0), mTransSpline(0), mScaleSpline(0), mRotSlerp(0), mRotSpline(0), 
    mRotKeys(), mTransKeys(), mScaleKeys(), mKeysOwner(this, this), mRepeatTrans(0), mFollowPath(0) {

}

void RndTransAnim::SetTrans(RndTransformable* trans){
    mTrans = trans;
}

void RndTransAnim::SetKeysOwner(RndTransAnim* o){
    MILO_ASSERT(o, 0x2C);
    mKeysOwner = o;
}

void RndTransAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndTransAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndTransAnim, 0x4B)

void RndTransAnim::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, TRANSANIM_REV);
    if(rev > 4) LOAD_SUPERCLASS(Hmx::Object);
    LOAD_SUPERCLASS(RndAnimatable);
    if(rev < 6) RndDrawable::DumpLoad(bs);
    bs >> mTrans;
    if(rev != 2){
        bs >> mRotKeys >> mTransKeys;
    }
    bs >> mKeysOwner;
    if(!mKeysOwner) mKeysOwner = this;
}

BEGIN_COPYS(RndTransAnim)
    CREATE_COPY_AS(RndTransAnim, t)
    MILO_ASSERT(t, 0xE8);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    mTrans = t->mTrans;
    if(ty == kCopyShallow || ty == kCopyFromMax && t->mKeysOwner != t){
        mKeysOwner = t->mKeysOwner;
    }
    else {
        mKeysOwner = this;
        mTransKeys = t->mKeysOwner->mTransKeys;
        mRotKeys = t->mKeysOwner->mRotKeys;
        mScaleKeys = t->mKeysOwner->mScaleKeys;
        mTransSpline = t->mKeysOwner->mTransSpline;
        mRepeatTrans = t->mKeysOwner->mRepeatTrans;
        mScaleSpline = t->mKeysOwner->mScaleSpline;
        mFollowPath = t->mKeysOwner->mFollowPath;
        mRotSlerp = t->mKeysOwner->mRotSlerp;
        mRotSpline = t->mKeysOwner->mRotSpline;
    }
END_COPYS

void RndTransAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   trans: " << mTrans.Ptr() << "\n";
    ts << "   framesOwner: " << mKeysOwner.Ptr() << "\n";
    ts << "   rotKeys: " << mRotKeys << "\n";
    ts << "   transKeys: " << mTransKeys << "\n";
    ts << "   scaleKeys: " << mScaleKeys << "\n";
    ts << "   transSpline: " << mTransSpline << "\n";
    ts << "   scaleSpline: " << mScaleSpline << "\n";
    ts << "   rotSlerp: " << mRotSlerp << "\n";
    ts << "   rotSpline: " << mRotSpline << "\n";
    ts << "   repeatTrans: " << mRepeatTrans << "\n";
    ts << "   followPath: " << mFollowPath << "\n";
}