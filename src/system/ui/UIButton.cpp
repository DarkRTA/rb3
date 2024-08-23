#include "UIButton.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "ui/UIComponent.h"
#include "ui/UI.h"

INIT_REVS(UIButton)

UIButton::UIButton() { }

void UIButton::Init() {
    TheUI->InitResources("UIButton");
    Register();
}

Hmx::Object* UIButton::NewObject() {return new UIButton;}

BEGIN_COPYS(UIButton)
    CREATE_COPY_AS(UIButton, f);
    MILO_ASSERT(f, 42);
    COPY_SUPERCLASS(UILabel)
END_COPYS

SAVE_OBJ(UIButton, 54)

void UIButton::Load(BinStream& bs) {
    PreLoad(bs);
    PostLoad(bs);
}

void UIButton::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    UILabel::PreLoad(bs);
}

void UIButton::PostLoad(BinStream& bs) { UILabel::PostLoad(bs);}

BEGIN_HANDLERS(UIButton)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_SUPERCLASS(UILabel)
    HANDLE_CHECK(87)
END_HANDLERS

DataNode UIButton::OnMsg(const ButtonDownMsg& msg) {
    if (msg.GetAction() == 1 && GetState() == UIComponent::kFocused) {
        SendSelect(msg.GetUser());
        return DataNode(1);
    }
    return DataNode(kDataUnhandled, 0);
}

BEGIN_PROPSYNCS(UIButton)
    SYNC_SUPERCLASS(UILabel)
END_PROPSYNCS
