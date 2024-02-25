#include "ui/UIColor.h"
#include "os/Debug.h"
#include "obj/PropSync.h"
#include "utl/Symbols.h"

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
    if(rev & 0xFFFF != 0){
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

bool UIColor::SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op){
    if(_i == _prop->Size()) return true;
    else {
        Symbol sym = _prop->Sym(_i);
        if(sym == color){
            return PropSync(mColor, _val, _prop, _i + 1, _op);
        }
        else return false;
    }
}
