#include "ui/UIListSlot.h"
#include "ui/UIList.h"
#include "utl/STLHelpers.h"
#include "utl/Symbols.h"

INIT_REVS(UIListSlot)

UIListSlot::UIListSlot() : mSlotDrawType(kUIListSlotDrawAlways), mNextElement(0) {

}

UIListSlot::~UIListSlot(){
    ClearElements();
}

void UIListSlot::ClearElements(){
    std::vector<UIListSlotElement*>::iterator it = mElements.begin();
    std::vector<UIListSlotElement*>::iterator itEnd = mElements.end();
    for(; it != itEnd; it++){
        delete *it;
    }
    mElements.clear();
    delete mNextElement;
    mNextElement = 0;
}

bool UIListSlot::Matches(const char* cc) const {
    return strcmp(mMatchName.c_str(), cc) == 0;
}

const char* UIListSlot::MatchName() const { return mMatchName.c_str(); }

void UIListSlot::CreateElements(UIList* uilist, int count){
    if(RootTrans()){
        ClearElements();
        for(int i = 0; i < count; i++){
            mElements.push_back(CreateElement(uilist));
        }
        mNextElement = CreateElement(uilist);
    }
}

// fn_8056EA14 - draw
void UIListSlot::Draw(const UIListWidgetDrawState& drawstate, const UIListState& liststate, const Transform& ctf,
    UIComponent::State compstate, Box* box, DrawCommand cmd){
    RndTransformable* root = RootTrans();
    if(root){
        int thesize = drawstate.mElements.size();
        if(thesize > mElements.size()){
            MILO_FAIL("%i isn't enough elements (need %i)", mElements.size(), thesize);
        }
        Transform tf78(root->WorldXfm());
        Transform tfa8;
        UIListProvider* prov = liststate.Provider();
        for(int i = 0; i < thesize; i++){
            const UIListElementDrawState& curdrawstate = drawstate.mElements[i];
            if(curdrawstate.unk0){
                float d10 = 1.0f;
                UIColor* uicolor = 0;
                if(!box){
                    if(mSlotDrawType == kUIListSlotDrawHighlight && curdrawstate.mDisplay != drawstate.mHighlightDisplay ||
                        mSlotDrawType == kUIListSlotDrawNoHighlight && curdrawstate.mDisplay == drawstate.mHighlightDisplay){
                        continue;
                    }

                    UIListWidgetState slotoverride = prov->SlotElementStateOverride(curdrawstate.mShowing, curdrawstate.mData, this, curdrawstate.mElementState);
                    UIComponent::State curcompstate = curdrawstate.mComponentState;
                    uicolor = DisplayColor(slotoverride, curcompstate);
                    uicolor = prov->SlotColorOverride(curdrawstate.mShowing, curdrawstate.mData, this, uicolor);
                    d10 = curdrawstate.mAlpha;
                    if(curcompstate == UIComponent::kDisabled) d10 *= DisabledAlphaScale();
                    prov->PreDraw(curdrawstate.mShowing, curdrawstate.mData, this);
                }
                tfa8 = tf78;
                if(ParentList()) ParentList()->AdjustTrans(tfa8, curdrawstate);
                CalcXfm(ctf, curdrawstate.mPos, tfa8);
                if(cmd != kExcludeFirst || i > 0){
                    mElements[i]->Draw(tfa8, d10, uicolor, box);
                }
                if(cmd == kDrawFirst) return;
            }
        }
    }
}

void UIListSlot::Fill(const UIListProvider& prov, int display, int j, int k){
    if(RootTrans()){
        MILO_ASSERT(display < mElements.size(), 0x8F);
        mElements[display]->Fill(prov, j, k);
    }
}

void UIListSlot::StartScroll(int i, bool b){
    if(b && RootTrans()){
        UIListSlotElement* next = mNextElement;
        mElements.insert(i < 0 ? mElements.begin() : mElements.end(), next);
        mNextElement = 0;
    }
}

void UIListSlot::CompleteScroll(const UIListState& liststate, int i){
    
}

void UIListSlot::Poll(){
    for(std::vector<UIListSlotElement*>::iterator it = mElements.begin(); it != mElements.end(); it++){
        (*it)->Poll();
    }
}

void UIListSlot::ResourceCopy(const UIListWidget* w){
    UIListWidget::ResourceCopy(w);
    mMatchName = w->Name();
}

SAVE_OBJ(UIListSlot, 0xC6)

BEGIN_LOADS(UIListSlot)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListWidget)
    int ty;
    bs >> ty;
    mSlotDrawType = (UIListSlotDrawType)ty;
END_LOADS

BEGIN_COPYS(UIListSlot)
    COPY_SUPERCLASS(UIListWidget)
    CREATE_COPY_AS(UIListSlot, s)
    MILO_ASSERT(s, 0xD8);
    COPY_MEMBER_FROM(s, mSlotDrawType)
END_COPYS

BEGIN_HANDLERS(UIListSlot)
    HANDLE_SUPERCLASS(UIListWidget)
    HANDLE_CHECK(0xDE)
END_HANDLERS

BEGIN_PROPSYNCS(UIListSlot)
    SYNC_PROP_SET(slot_draw_type, (int)mSlotDrawType, mSlotDrawType = (UIListSlotDrawType)_val.Int(0))
    SYNC_SUPERCLASS(UIListWidget)
END_PROPSYNCS