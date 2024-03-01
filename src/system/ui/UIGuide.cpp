#include "ui/UIGuide.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short UIGuide::gRev = 0;
unsigned short UIGuide::gAltRev = 0;

UIGuide::UIGuide() : mType(0), mPos(0.5f) {
    
}

UIGuide::~UIGuide(){
    
}

void UIGuide::Save(BinStream&){
    MILO_ASSERT(0, 0x21);
}

void UIGuide::Load(BinStream& bs){
    int rev;
    bs >> rev;
    gRev = (unsigned int)rev;
    gAltRev = (unsigned int)rev >> 0x10;
    if((unsigned short)rev > 1){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)1);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)0);
    }
    Hmx::Object::Load(bs);
    bs >> mType >> mPos;
}

void UIGuide::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(o, ty);
    const UIGuide* c = dynamic_cast<const UIGuide*>(o);
    if(c){
        mType = c->mType;
        mPos = c->mPos;
    }
}

BEGIN_PROPSYNCS(UIGuide);
    SYNC_PROP(pos, mPos);
    SYNC_PROP(type, mType);
END_PROPSYNCS;

BEGIN_HANDLERS(UIGuide);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x47);
END_HANDLERS;
