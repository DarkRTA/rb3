#include "ui/UIColor.h"
#include "os/Debug.h"
#include "obj/MessageTimer.h"

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

DataNode UIColor::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    {
        DataNode handled = Hmx::Object::Handle(_msg, false);
        if(handled.Type() != kDataUnhandled){
            return DataNode(handled);
        }
    }
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, 0x3A, PathName(this), sym);
    return DataNode(kDataUnhandled, 0);
    
}
