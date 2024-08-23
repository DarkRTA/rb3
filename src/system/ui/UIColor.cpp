#include "ui/UIColor.h"
#include "os/Debug.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

unsigned short UIColor::gRev = 0;
unsigned short UIColor::gAltRev = 0;

UIColor::UIColor() : mColor(1.0f,1.0f,1.0f,1.0f) {
    
}

const Hmx::Color& UIColor::GetColor() const {
    return mColor;
}

void UIColor::SetColor(const Hmx::Color& color){
    mColor = color;
}

SAVE_OBJ(UIColor, 0x24)

void UIColor::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    Hmx::Object::Load(bs);
    bs >> mColor;
}

BEGIN_COPYS(UIColor)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(UIColor)
    MILO_ASSERT(c, 0x34);
    COPY_MEMBER(mColor)
END_COPYS

BEGIN_HANDLERS(UIColor);
    HANDLE_SUPERCLASS(Hmx::Object);
    HANDLE_CHECK(0x3A);
END_HANDLERS;

BEGIN_PROPSYNCS(UIColor);
    SYNC_PROP(color, mColor);
END_PROPSYNCS;
