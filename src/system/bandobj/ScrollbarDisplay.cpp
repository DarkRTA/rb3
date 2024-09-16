#include "bandobj/ScrollbarDisplay.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(ScrollbarDisplay);

void ScrollbarDisplay::Init(){
    Register();
    TheUI->InitResources("ScrollbarDisplay");
}

ScrollbarDisplay::ScrollbarDisplay() : m_pList(this, 0), mScrollbarHeight(200.0f), mAlwaysShow(0), mListXOffset(0), mListYOffset(0), mMinThumbHeight(1.0f),
    m_pTopBone(0), m_pBottomBone(0), m_pThumbTopBone(0), m_pThumbBottomBone(0), m_pThumbGroup(0), unk140(-1), unk144(-1), unk148(-1), unk14c(-1), m_fSavedPosition(0), m_fSavedScale(0) {

}

ScrollbarDisplay::~ScrollbarDisplay(){
    
}

BEGIN_COPYS(ScrollbarDisplay)
    COPY_SUPERCLASS(UIComponent)
END_COPYS

void ScrollbarDisplay::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty){
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(ScrollbarDisplay, pDisplay);
    MILO_ASSERT(pDisplay, 0x44);
    COPY_MEMBER_FROM(pDisplay, m_pList)
    COPY_MEMBER_FROM(pDisplay, mAlwaysShow)
    COPY_MEMBER_FROM(pDisplay, mListXOffset)
    COPY_MEMBER_FROM(pDisplay, mListYOffset)
    COPY_MEMBER_FROM(pDisplay, mScrollbarHeight)
    COPY_MEMBER_FROM(pDisplay, mMinThumbHeight)
}

SAVE_OBJ(ScrollbarDisplay, 0x57)

BEGIN_LOADS(ScrollbarDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void ScrollbarDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    bs >> m_pList;
    bs >> mAlwaysShow;
    if(gRev < 1){ bool b; bs >> b; }
    bs >> mListXOffset;
    bs >> mListYOffset;
    bs >> mScrollbarHeight;
    if(gRev >= 2) bs >> mMinThumbHeight;
    UIComponent::PreLoad(bs);
}

void ScrollbarDisplay::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void ScrollbarDisplay::Enter(){ UIComponent::Enter(); }

void ScrollbarDisplay::UpdateThumbScaleAndPosition(){
    GetSavedPosition();
    GetSavedScale();
}

void ScrollbarDisplay::SetAlwaysShow(bool b){ mAlwaysShow = b; }
void ScrollbarDisplay::SetListXOffset(float f){ mListXOffset = f; }
void ScrollbarDisplay::SetListYOffset(float f){ mListYOffset = f; }
void ScrollbarDisplay::SetMinThumbHeight(float f){ mMinThumbHeight = f; }
void ScrollbarDisplay::SetHeight(float f){
    mScrollbarHeight = f;
    if(mScrollbarHeight < mMinThumbHeight) mScrollbarHeight = mMinThumbHeight;
}

BEGIN_HANDLERS(ScrollbarDisplay)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x1E9)
END_HANDLERS

BEGIN_PROPSYNCS(ScrollbarDisplay)
    SYNC_PROP_SET(scrollbar_list, GetList(), SetList(_val.Obj<BandList>(0)))
    SYNC_PROP_SET(always_show, GetAlwaysShow(), SetAlwaysShow(_val.Int(0)))
    SYNC_PROP_SET(list_attached, GetListAttached(), SetListAttached(_val.Int(0)))
    SYNC_PROP_SET(list_x_offset, GetListXOffset(), SetListXOffset(_val.Float(0)))
    SYNC_PROP_SET(list_y_offset, GetListYOffset(), SetListYOffset(_val.Float(0)))
    SYNC_PROP_SET(scrollbar_height, GetHeight(), SetHeight(_val.Float(0)))
    SYNC_PROP_SET(min_thumb_height, GetMinThumbHeight(), SetMinThumbHeight(_val.Float(0)))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS