#include "synth/Emitter.h"

int kEmitterRev = 3;

BEGIN_COPYS(SynthEmitter)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    GET_COPY(SynthEmitter)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mSfx)
        COPY_MEMBER(mListener)
        COPY_MEMBER(mSynthEmitterEnabled)
        COPY_MEMBER(mRadOuter)
        COPY_MEMBER(mRadInner)
        COPY_MEMBER(mVolOuter)
        COPY_MEMBER(mVolInner)
        delete mInst;
    END_COPY_CHECKED
END_COPYS

SAVE_OBJ(SynthEmitter, 0x30)

BEGIN_LOADS(SynthEmitter)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, kEmitterRev)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mSfx >> mListener;
    bool b;
    bs >> b;
    mSynthEmitterEnabled = b;
    if(rev >= 2) bs >> mRadOuter >> mRadInner;
    if(rev >= 3) bs >> mVolOuter >> mVolInner;
    delete mInst;
END_LOADS

SynthEmitter::~SynthEmitter(){
    delete mInst;
}

SynthEmitter::SynthEmitter() : mSfx(this, 0), mInst(this, 0), mListener(this, 0), mRadInner(10.0f), mRadOuter(100.0f), mVolInner(0.0f), mVolOuter(-40.0f) {
    mSynthEmitterEnabled = true;
}

BEGIN_HANDLERS(SynthEmitter)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xE3)
END_HANDLERS