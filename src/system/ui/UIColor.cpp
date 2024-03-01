#include "ui/UIColor.h"
#include "os/Debug.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

unsigned short UIColor::gRev = 0;
unsigned short UIColor::gAltRev = 0;

UIColor::UIColor() : mColor() {
    
}

const Hmx::Color& UIColor::GetColor() const {
    return mColor;
}

void UIColor::SetColor(const Hmx::Color& color){
    mColor = color;
}

void UIColor::Save(BinStream&){
    MILO_ASSERT(0, 0x24);
}

void UIColor::Load(BinStream& bs){
    int rev;
    bs >> rev;
    gRev = (unsigned int)rev;
    gAltRev = (unsigned int)rev >> 0x10;
    if((unsigned short)rev != 0){
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)0);
    }
    if(gAltRev != 0){
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)0);
    }
    Hmx::Object::Load(bs);
    bs >> mColor;
}

void UIColor::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(o, ty);
    const UIColor* c = dynamic_cast<const UIColor*>(o);
    MILO_ASSERT(c, 0x34);
    mColor = c->mColor;
}

BEGIN_HANDLERS(UIColor);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x3A);
END_HANDLERS;

BEGIN_PROPSYNCS(UIColor);
    SYNC_PROP(color, mColor);
END_PROPSYNCS;
