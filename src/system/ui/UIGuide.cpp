#include "ui/UIGuide.h"

UIGuide::UIGuide() : mType(0), mPos(0.5f) {
    
}

UIGuide::~UIGuide(){
    
}

void UIGuide::Save(BinStream&){
    MILO_ASSERT(0, 0x21);
}

void UIGuide::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(o, ty);
    const UIGuide* c = dynamic_cast<const UIGuide*>(o);
    if(c){
        mType = c->mType;
        mPos = c->mPos;
    }
}
