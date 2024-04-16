#include "UILabel.h"
#include "obj/Object.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

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

void UILabel::Terminate() {}

BEGIN_COPYS(UILabel)
    GET_COPY_AND_ASSERT(UILabel, 96)
    COPY_SUPERCLASS(UIComponent)
    SetCreditsText();
END_COPYS


SAVE_OBJ(UILabel, 173)

void UILabel::Load(BinStream& bs) { PreLoad(bs); PostLoad(bs); }

void UILabel::Draw() {
    if (!(h <= 0)) RndDrawable::Draw();
}

void UILabel::Update() {
    if (!sDeferUpdate) LabelUpdate(false, false);
}

void UILabel::LabelUpdate(bool b, bool c) {
    
}


BEGIN_HANDLERS(UILabel)
    HANDLE_EXPR(get_string_width, mText->GetStringWidthUTF8(_msg->Str(2), NULL, false, NULL))
    HANDLE_ACTION(adjust_height, AdjustHeight(true))
    HANDLE(set_token_fmt, OnSetTokenFmt)
    HANDLE(set_int, OnSetInt)
    HANDLE_ACTION(set_float, SetFloat(_msg->Str(2), _msg->Float(3)))
    HANDLE_ACTION(center_with_label, CenterWithLabel(_msg->Obj<UILabel>(2), _msg->Int(3), _msg->Float(4)))
    HANDLE_EXPR(has_highlight_mesh, (bool)mLabelDir->HighlightMeshGroup())
    HANDLE(get_material_variations, OnGetMaterialVariations)
    HANDLE(get_altmaterial_variations, OnGetAltMaterialVariations)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(1554)
END_HANDLERS


BEGIN_PROPSYNCS(UILabel)
    SYNC_PROP(leading, h);
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
