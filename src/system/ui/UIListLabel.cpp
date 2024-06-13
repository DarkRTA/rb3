#include "ui/UIListLabel.h"
#include "ui/UIList.h"
#include "utl/Symbols.h"

INIT_REVS(UIListLabel)

UIListLabel::UIListLabel() : mLabel(this, 0) {

}

const char* UIListLabel::GetDefaultText() const {
    if(mLabel) return mLabel->GetDefaultText();
    else return gNullStr;
}

UILabel* UIListLabel::ElementLabel(int display) const {
    if(mElements.empty()) return 0;
    else {
        MILO_ASSERT(( 0) <= (display) && (display) < ( mElements.size()), 0x6E);
        UIListLabelElement* le = dynamic_cast<UIListLabelElement*>(mElements[display]);
        MILO_ASSERT(le, 0x71);
        return le->mLabel;
    }
}

UIListSlotElement* UIListLabel::CreateElement(UIList* uilist){
    MILO_ASSERT(mLabel, 0x80);
    UILabel* l = dynamic_cast<UILabel*>(Hmx::Object::NewObject(mLabel->ClassName()));
    MILO_ASSERT(l, 0x83);
    l->ResourceCopy(mLabel);
    l->SetTextToken(gNullStr);
    return new UIListLabelElement(this, l);
}

RndTransformable* UIListLabel::RootTrans(){
    return mLabel;
}

SAVE_OBJ(UIListLabel, 0x9A)

BEGIN_LOADS(UIListLabel)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    LOAD_SUPERCLASS(UIListSlot)
    bs >> mLabel;
END_LOADS

BEGIN_COPYS(UIListLabel)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListLabel, l)
    MILO_ASSERT(l, 0xB0);
    COPY_MEMBER_FROM(l, mLabel)
END_COPYS

BEGIN_HANDLERS(UIListLabel)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(0xBF)
END_HANDLERS

BEGIN_PROPSYNCS(UIListLabel)
    SYNC_PROP(label, mLabel)
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS