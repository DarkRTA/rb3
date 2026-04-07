#include "synth/Emitter.h"
#include "math/Utl.h"
#include "rndobj/Dir.h"
#include "obj/DirLoader.h"
#include "synth/FxSend.h"
#include "synth/Sfx.h"
#include "utl/Symbols.h"

namespace {
    static RndDir *gIconDir;
}
int kEmitterRev = 3;

BEGIN_COPYS(SynthEmitter)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(SynthEmitter)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mSfx)
        COPY_MEMBER(mListener)
        COPY_MEMBER(mSynthEmitterEnabled)
        COPY_MEMBER(mRadOuter)
        COPY_MEMBER(mRadInner)
        COPY_MEMBER(mVolOuter)
        COPY_MEMBER(mVolInner)
        delete mInst;
    END_COPYING_MEMBERS
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
    if (rev >= 2)
        bs >> mRadOuter >> mRadInner;
    if (rev >= 3)
        bs >> mVolOuter >> mVolInner;
    delete mInst;
END_LOADS

void SynthEmitter::DrawShowing() {
    if (LOADMGR_EDITMODE) {
        CheckLoadResources();
        Transform &xfm = WorldXfm();
        gIconDir->SetLocalXfm(xfm);
        gIconDir->DrawShowing();
    }
}

RndDrawable *SynthEmitter::CollideShowing(const Segment &s, float &dist, Plane &plane) {
    if (LOADMGR_EDITMODE) {
        CheckLoadResources();
        RndDrawable *dirDraw = gIconDir->CollideShowing(s, dist, plane);
        if (dirDraw) {
            return this;
        }
    }
    return 0;
}

int SynthEmitter::CollidePlane(const Plane &plane) {
    if (LOADMGR_EDITMODE) {
        CheckLoadResources();
        return gIconDir->CollidePlane(plane);
    } else
        return 0;
}

void SynthEmitter::CheckLoadResources() {
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x8B);
    if (!gIconDir) {
        FilePath fp(FileSystemRoot(), "milo/emitter.milo");
        gIconDir = dynamic_cast<RndDir *>(DirLoader::LoadObjects(fp, 0, 0));
        MILO_ASSERT(gIconDir, 0x93);
    }
}

inline float CoolFloatFunc(
    float rad_inner, float vol_inner, float rad_outer, float vol_outer, float dst
) {
    // float vol_delta = vol_outer - vol_inner;
    // float rad_delta = rad_outer - rad_inner;
    float rela = (vol_outer - vol_inner) / (rad_outer - rad_inner);
    float f0 = -(rela * rad_inner - vol_inner);
    return rela * dst + f0;
}

// fn_8066E758 in retail
void SynthEmitter::Poll() {
    if (!mSfx || !mListener || !mSynthEmitterEnabled) {
        return;
    } else {
        Transform xfm;
        Invert(mListener->WorldXfm(), xfm);
        Vector3 pos;
        Multiply(WorldXfm().v, xfm, pos);
        float dist = Length(pos);
        if (dist > mRadOuter) {
            delete mInst;
            return;
        }
        bool just_started = !mInst;
        if (just_started) {
            mInst = dynamic_cast<SfxInst *>(mSfx->MakeInst());
            if (mInst == NULL)
                return;
        }
        // do volume ramping
        if (dist > mRadInner) {
            mInst->SetVolume(
                CoolFloatFunc(mRadInner, mVolInner, mRadOuter, mVolOuter, dist)
            );
        } else {
            mInst->SetVolume(mVolInner);
        }
        // falloff constant?
        float f = std::atan2(pos.y, pos.x);
        f *= 1.2732395f;
        f = 2.0f - f;
        mInst->SetPan(f);
        if (just_started) {
            mInst->Start();
        }
    }
}

SynthEmitter::~SynthEmitter() { delete mInst; }

SynthEmitter::SynthEmitter()
    : mSfx(this, 0), mInst(this, 0), mListener(this, 0), mRadInner(10.0f),
      mRadOuter(100.0f), mVolInner(0.0f), mVolOuter(-40.0f) {
    mSynthEmitterEnabled = true;
}

BEGIN_HANDLERS(SynthEmitter)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xE3)
END_HANDLERS

BEGIN_PROPSYNCS(SynthEmitter)
    SYNC_PROP_MODIFY_ALT(sfx, mSfx, delete mInst)
    SYNC_PROP_MODIFY_ALT(listener, mListener, delete mInst) {
        static Symbol _s("enabled");
        bool b = mSynthEmitterEnabled;
        if (sym == _s) {
            bool synced = PropSync(b, _val, _prop, _i + 1, _op);
            if (!synced)
                return false;
            else {
                mSynthEmitterEnabled = b;
                if (!(_op & (kPropSize | kPropGet)))
                    delete mInst;
                return true;
            }
        }
    }
    SYNC_PROP(outer_radius, mRadOuter)
    SYNC_PROP(inner_radius, mRadInner)
    SYNC_PROP(outer_volume, mVolOuter)
    SYNC_PROP(inner_volume, mVolInner)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS