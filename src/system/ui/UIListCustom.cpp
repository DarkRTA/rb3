#include "UIListCustom.h"
#include "decomp.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "ui/UIComponent.h"
#include "ui/UILabel.h"
#include "ui/UIListProvider.h"
#include "ui/UIListSlot.h"
#include "utl/Symbols.h"

INIT_REVS(UIListCustom)

DECOMP_FORCEACTIVE(
    UIListCustom, __FILE__, "( 0) <= (display) && (display) < ( mElements.size())", "le"
)

inline void
UIListCustomElement::Draw(const Transform &tf, float f, UIColor *col, Box *box) {
    RndTransformable *t = dynamic_cast<RndTransformable *>(mPtr);
    MILO_ASSERT(t, 34);
    t->SetWorldXfm(tf);
    UIListCustomTemplate *temp = dynamic_cast<UIListCustomTemplate *>(mPtr);
    if (box) {
        if (temp)
            temp->GrowBoundingBox(*box);
    } else {
        if (temp)
            temp->SetAlphaColor(f, col);
        RndDrawable *d = dynamic_cast<RndDrawable *>(mPtr);
        MILO_ASSERT(d, 49);
        d->Draw();
    }
}

UIListCustom::UIListCustom() : mObject(this, NULL) {}

void UIListCustom::SetObject(Hmx::Object *o) {
    if (o) {
        RndTransformable *is_t = dynamic_cast<RndTransformable *>(o);
        RndDrawable *is_d = dynamic_cast<RndDrawable *>(o);
        if (!is_t)
            MILO_WARN("Object is not transformable");
        if (!is_d)
            MILO_WARN("Object is not drawable");
        if (!is_t || !is_d)
            o = NULL;
    }
    mObject = o;
}

UIListSlotElement *UIListCustom::CreateElement(UIList *) {
    MILO_ASSERT(mObject, 105);
    Hmx::Object *c = Hmx::Object::NewObject(mObject->ClassName());
    if (UIComponent *d = dynamic_cast<UIComponent *>(c)) {
        d->ResourceCopy(dynamic_cast<UIComponent *>(mObject.mPtr));
    } else {
        c->Copy(mObject.mPtr, kCopyDeep);
    }
    return new UIListCustomElement(this, c);
}

RndTransformable *UIListCustom::RootTrans() {
    return dynamic_cast<RndTransformable *>(mObject.Ptr());
}

SAVE_OBJ(UIListCustom, 127)

BEGIN_LOADS(UIListCustom)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    UIListSlot::Load(bs);
    bs >> mObject;
END_LOADS

BEGIN_COPYS(UIListCustom)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListCustom, c)
    MILO_ASSERT(c, 143);
    COPY_MEMBER(mObject)
END_COPYS

BEGIN_HANDLERS(UIListCustom)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(149)
END_HANDLERS

BEGIN_PROPSYNCS(UIListCustom)
    SYNC_PROP_SET(object, mObject, SetObject(_val.GetObj()))
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS

// DECOMP_FORCEBLOCK(UIListCustom, (UIListCustomElement* ce), ce->Draw(Transform(), 0,
// NULL, NULL); ce->Poll();)
