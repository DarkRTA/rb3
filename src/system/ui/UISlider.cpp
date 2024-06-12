#include "ui/UISlider.h"
#include "ui/UI.h"

INIT_REVS(UISlider)

UISlider::UISlider() : unk118(0), unk11c(10), unk120(0) {

}

void UISlider::Init(){
    TheUI->InitResources("UISlider");
    REGISTER_OBJ_FACTORY(UISlider);
}

BEGIN_COPYS(UISlider)
    CREATE_COPY_AS(UISlider, s)
    MILO_ASSERT(s, 0x2B);
    UIComponent::Copy(s, ty);
    COPY_MEMBER_FROM(s, unk_0x4)
END_COPYS

SAVE_OBJ(UISlider, 0x36)

BEGIN_LOADS(UISlider)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void UISlider::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    UIComponent::PreLoad(bs);
}

void UISlider::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    if(gRev != 0){
        bs >> unk_0x4;
    }
    Update();
}

void UISlider::Enter(){
    UIComponent::Enter();
    Reset();
}