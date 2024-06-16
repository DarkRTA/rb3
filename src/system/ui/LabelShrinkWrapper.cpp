#include "ui/LabelShrinkWrapper.h"
#include "ui/UILabel.h"
#include "ui/UI.h"

INIT_REVS(LabelShrinkWrapper)

void LabelShrinkWrapper::Init(){
    Register();
    TheUI->InitResources("LabelShrinkWrapper");
}

LabelShrinkWrapper::LabelShrinkWrapper() : mLabel(this, 0), mShow(0), unk11c(0), unk120(0), unk124(0), unk128(0) {

}

LabelShrinkWrapper::~LabelShrinkWrapper(){

}

BEGIN_COPYS(LabelShrinkWrapper)
    CREATE_COPY_AS(LabelShrinkWrapper, p)
    MILO_ASSERT(p, 0x2F);
    COPY_MEMBER_FROM(p, mLabel)
    COPY_MEMBER_FROM(p, mShow)
    UIComponent::Copy(p, ty);
END_COPYS

SAVE_OBJ(LabelShrinkWrapper, 0x3C)

void LabelShrinkWrapper::Enter(){ UIComponent::Enter(); }

BEGIN_LOADS(LabelShrinkWrapper)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void LabelShrinkWrapper::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0)
    bs >> mLabel >> mShow;
    UIComponent::PreLoad(bs);
}

void LabelShrinkWrapper::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}