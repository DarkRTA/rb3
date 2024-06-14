#include "ui/UIListSubList.h"
#include "utl/Symbols.h"

INIT_REVS(UIListSubList)

int UIListSubList::sNextFillSelection = -1;

UIListSubList::UIListSubList() : mList(this, 0) {

}

UIList* UIListSubList::SubList(int i){
    UIListSubListElement* sle = dynamic_cast<UIListSubListElement*>(mElements[i]);
    MILO_ASSERT(sle, 0x5E);
    return sle->List();
}

void UIListSubList::Draw(const UIListWidgetDrawState& drawstate, const UIListState& liststate, const Transform& tf, UIComponent::State compstate, Box* box, DrawCommand cmd){
    if(RootTrans()){
        int size = drawstate.mElements.size();
        for(int i = 0; i < size; i++){
            UIList* uilist = SubList(i);
            int el = drawstate.mElements[i]; // TODO: fix the vector type of drawstate's mElements
            switch(el){
                case 0:
                    uilist->SetState((UIComponent::State)0);
                    break;
                case 1:
                    if(compstate == UIComponent::kFocused){
                        uilist->SetState((UIComponent::State)1);
                    }
                    else uilist->SetState((UIComponent::State)0);
                    break;
                case 2:
                    uilist->SetState((UIComponent::State)2);
                    break;
            }
        }
    }
    UIListSlot::Draw(drawstate, liststate, tf, compstate, box, cmd);
}

UIListSlotElement* UIListSubList::CreateElement(UIList* parent){
    MILO_ASSERT(mList, 0x89);
    UIList* l = dynamic_cast<UIList*>(Hmx::Object::NewObject(mList->ClassName()));
    MILO_ASSERT(l, 0x8C);
    l->SetParent(parent);
    l->SetType(mList->Type());
    l->Copy(mList, kCopyDeep);
    if(!TheLoadMgr.EditMode()) MILO_ASSERT(parent, 0x94);
    if(parent){
        l->SetInAnim(parent->GetInAnim());
        l->SetOutAnim(parent->GetOutAnim());
    }
    return new UIListSubListElement(this, l);
}

RndTransformable* UIListSubList::RootTrans(){ return mList; }

SAVE_OBJ(UIListSubList, 0xAC)

BEGIN_LOADS(UIListSubList)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListSlot)
    bs >> mList;
END_LOADS

BEGIN_COPYS(UIListSubList)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListSubList, sl)
    MILO_ASSERT(sl, 0xBC);
    COPY_MEMBER_FROM(sl, mList)
END_COPYS

BEGIN_HANDLERS(UIListSubList)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(0xC2)
END_HANDLERS

BEGIN_PROPSYNCS(UIListSubList)
    SYNC_PROP(list, mList)
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS

inline void UIListSubListElement::Draw(const Transform& tf, float f, UIColor* col, Box* box){
    mList->SetWorldXfm(tf);
    if(box){
        Box localbox;
        mList->CalcBoundingBox(localbox);
        box->GrowToContain(localbox.mMin, false);
        box->GrowToContain(localbox.mMax, false);
    }
    else mList->DrawShowing();
}

inline void UIListSubListElement::Fill(const UIListProvider& prov, int i, int j){
    UIListProvider* theProvider;
    if(TheLoadMgr.EditMode()) theProvider = mList;
    else theProvider = prov.Provider(i, j, mSlot);
    if(theProvider){
        mList->SetProvider(theProvider);
        int thefill = UIListSubList::sNextFillSelection;
        if(-1 < UIListSubList::sNextFillSelection){

        }
        mList->SetSelected(thefill, -1);
        UIListSubList::sNextFillSelection = -1;
    }
}