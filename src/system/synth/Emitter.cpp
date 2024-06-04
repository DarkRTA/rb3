#include "synth/Emitter.h"
#include "rndobj/Dir.h"
#include "obj/DirLoader.h"
#include "synth/FxSend.h"
#include "synth/Sfx.h"
#include "utl/Symbols.h"

namespace {
    static RndDir* gIconDir;
}
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

RndDrawable* SynthEmitter::CollideShowing(const Segment& s, float& dist, Plane& plane){
    if(TheLoadMgr.EditMode()){
        CheckLoadResources();
        RndDrawable* dirDraw = gIconDir->CollideShowing(s, dist, plane);
        if(dirDraw){
            return this;
        }
    }
    return 0;
}

int SynthEmitter::CollidePlane(const Plane& plane){
    if(TheLoadMgr.EditMode()){
        CheckLoadResources();
        return gIconDir->CollidePlane(plane);
    }
    else return 0;
}

void SynthEmitter::CheckLoadResources(){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x8B);
    if(!gIconDir){
        const char* str = "milo/emitter.milo";
        const char* root = FileSystemRoot();
        FilePath fp;
        fp.Set(root, str);
        gIconDir = dynamic_cast<RndDir*>(DirLoader::LoadObjects(fp, 0, 0));
        MILO_ASSERT(gIconDir, 0x93);
    }
}

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

BEGIN_PROPSYNCS(SynthEmitter)
    SYNC_PROP_ACTION(sfx, mSfx, kPropSize|kPropGet, delete mInst)
    SYNC_PROP_ACTION(listener, mListener, kPropSize|kPropGet, delete mInst)
    { 
        static Symbol _s("enabled"); 
        bool b = mSynthEmitterEnabled;
        if(sym == _s){
            bool synced = PropSync(b, _val, _prop, _i + 1, _op);
            if(!synced) return false;
            else {
                mSynthEmitterEnabled = b;
                if(!(_op & (kPropSize|kPropGet))) delete mInst;
                return true; 
            }
        }
    }
    SYNC_PROP(outer_radius, mRadOuter)
    SYNC_PROP(inner_radius, mRadInner)
    SYNC_PROP(outer_volume, mVolOuter)
    SYNC_PROP(inner_volume, mVolInner)
    if(RndTransformable::SyncProperty(_val, _prop, _i, _op)) return true;
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS