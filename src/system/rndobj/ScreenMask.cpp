#include "rndobj/ScreenMask.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include <list>

int SCREENMASK_REV = 2;

namespace {
    bool AddToNotifies(const char* str, std::list<class String>& list){
        if(list.size() > 0x10) return false;
        for(std::list<class String>::iterator it = list.begin(); it != list.end(); it++){
            bool strFound = !strcmp(it->c_str(), str);
            if(strFound) return false;
        }
        list.push_back(str);
        return true;
    }
}

RndScreenMask::RndScreenMask() : mMat(this, 0) {
    mUseCurrentRect = 0;
}

BEGIN_COPYS(RndScreenMask)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    GET_COPY(RndScreenMask)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mMat)
        COPY_MEMBER(mColor)
        COPY_MEMBER(mRect)
        COPY_MEMBER(mUseCurrentRect)
    END_COPY_CHECKED
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
