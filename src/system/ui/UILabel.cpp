#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"

UILabel::UILabel() : mText(Hmx::Object::New<RndText>()), hi(), mFont(this, NULL), a(gNullStr), b(gNullStr), f(30), h(1), mColor(this, NULL),
                    mColor2(this, NULL) {
    mText->SetTransParent(this, false);
    mPath = GetResourcesPath();
}

UILabel::~UILabel() {

}

void UILabel::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    Hmx::Object::RegisterFactory(UILabelDir::StaticClassName(), UILabelDir::NewObject);
}

Hmx::Object* UILabel::NewObject() {return new UILabel;}
Hmx::Object* UILabelDir::NewObject() {return new UILabelDir;}

void UILabel::Terminate() {}

BEGIN_COPYS(UILabel)
    GET_COPY_AND_ASSERT(UILabel, 96)
    COPY_SUPERCLASS(UIComponent)
    SetCreditsText();
END_COPYS


SAVE_OBJ(UILabel, 173)

void UILabel::Draw() {
    if (!(h <= 0)) RndDrawable::Draw();
}

void UILabel::Update() {
    if (!sDeferUpdate) LabelUpdate(false, false);
}

void UILabel::LabelUpdate(bool b, bool c) {
    
}
