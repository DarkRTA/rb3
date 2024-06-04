#include "ScreenMask.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "rndobj/Cam.h"
#include "rndobj/HiResScreen.h"
#include "rndobj/Rnd.h"
#include <list>

int SCREENMASK_REV = 2;

ADD_NOTIFS

RndScreenMask::RndScreenMask() : mMat(this, 0), mColor(), mRect(0.0f, 0.0f, 1.0f, 1.0f) {
    mUseCurrentRect = 0;
}

BEGIN_COPYS(RndScreenMask)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(RndScreenMask)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMat)
        COPY_MEMBER(mColor)
        COPY_MEMBER(mRect)
        COPY_MEMBER(mUseCurrentRect)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RndScreenMask, 0x38)

void RndScreenMask::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if (rev > SCREENMASK_REV){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev, SCREENMASK_REV);
    }
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mMat >> mColor;
    if(rev > 0){
        bs >> mRect;
    }
    if(rev > 1){
        bool userect_loaded;
        bs >> userect_loaded;
        mUseCurrentRect = userect_loaded;
    }
}

void RndScreenMask::DrawShowing() {
    

    {
        static DebugNotifyOncer _dw;
        const char* s = MakeString("%s: Overriding camera screen_rect not supported with render texture", mName);
        if (::AddToNotifies(s, _dw.mNotifies))
            TheDebugNotifier << s;
    }
    if (!mUseCurrentRect && !RndCam::sCurrent->mTargetTex.mPtr) {
        //TheRnd->PostSave();
        TheHiResScreen->InvScreenRect();
    } else {
        TheHiResScreen->InvScreenRect();
        Hmx::Color c; Hmx::Rect r;
        TheRnd->DrawRect(r, c, mMat, NULL, NULL);
    }
}

BEGIN_HANDLERS(RndScreenMask)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xB0)
END_HANDLERS

BEGIN_PROPSYNCS(RndScreenMask)
    SYNC_PROP(mat, mMat)
    SYNC_PROP(color, mColor)
    SYNC_PROP(alpha, mColor.alpha)
    SYNC_PROP(screen_rect, mRect)
    static Symbol _s("use_cam_rect");
    if(sym == _s){
        if(_op == kPropSet){
            mUseCurrentRect = _val.Int(0) != 0;
        }
        else {
            _val = DataNode(mUseCurrentRect);
        }
        return true;
    }
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
