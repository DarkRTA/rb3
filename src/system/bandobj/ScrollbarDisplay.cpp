#include "bandobj/ScrollbarDisplay.h"
#include "ui/UI.h"
#include "ui/UIListDir.h"
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

void ScrollbarDisplay::UpdateSavedListInfo(){
    if(m_pList){
        int num = m_pList->NumProviderData() - m_pList->NumDisplay();
        UIListState& state = m_pList->GetListState();
        if(state.ScrollPastMaxDisplay()) num += state.MaxDisplay();
        if(num < 1) num = 1;
        int iFirstShowing = m_pList->FirstShowing();
        if(iFirstShowing != unk144 || num != unk140){
            MILO_ASSERT(iFirstShowing >= 0, 0xA2);
            if(iFirstShowing > num) iFirstShowing = num;
            unk140 = num;
            unk144 = iFirstShowing;
            m_fSavedPosition = (float)unk144 / (float)unk140;
            MILO_ASSERT(m_fSavedPosition >= 0.0f, 0xAC);
            MILO_ASSERT(m_fSavedPosition <= 1.0f, 0xAD);
        }
        num = m_pList->NumProviderData();
        int disp = m_pList->NumDisplay();
        if(disp != unk14c || num != unk140){
            unk148 = num;
            unk14c = disp;
            if(unk14c < unk148) m_fSavedScale = (float)unk14c / (float)unk148;
            else m_fSavedScale = 1.0f;
            MILO_ASSERT(m_fSavedScale >= 0.0f, 0xC3);
            MILO_ASSERT(m_fSavedScale <= 1.0f, 0xC4);
            if(GetListAttached()) SetHeight(GetListHeight());
        }
    }
}

float ScrollbarDisplay::GetListHeight() const {
    MILO_ASSERT(m_pList, 0xDF);
    float f = 0;
    UIListDir* dir = m_pList->GetUIListDir();
    if(dir) f = dir->ElementSpacing();
    return f * m_pList->NumDisplay();
}

DECOMP_FORCEACTIVE(ScrollbarDisplay, "m_pThumbTopBone", "m_pThumbBottomBone", "fHeight >= 0", "m_pTopBone", "m_pBottomBone", "m_pThumbGroup")

void ScrollbarDisplay::UpdateScrollbarHeightAndPosition(){
    MILO_ASSERT(m_pTopBone, 0xFF);
    MILO_ASSERT(m_pBottomBone, 0x100);
    if(GetListAttached()){
        SetLocalPos(Vector3(mListXOffset, 0, mListYOffset));
    }
    if(mScrollbarHeight < mMinThumbHeight) mScrollbarHeight = mMinThumbHeight;
    Vector3 v28(m_pTopBone->mLocalXfm.v);
    v28.z -= mScrollbarHeight;
    m_pBottomBone->SetLocalPos(v28);
}

void ScrollbarDisplay::UpdateThumbScaleAndPosition(){
    MILO_ASSERT(m_pThumbTopBone, 0x11B);
    MILO_ASSERT(m_pThumbBottomBone, 0x11C);
    MILO_ASSERT(m_pTopBone, 0x11D);
    MILO_ASSERT(m_pBottomBone, 0x11E);
    float scale = GetSavedScale();
    float pos = GetSavedPosition();
    scale *= mScrollbarHeight;
    Vector3 v4c(m_pTopBone->mLocalXfm.v);
    v4c.z -= (pos * (mScrollbarHeight - scale));
    m_pThumbTopBone->SetLocalPos(v4c);
    Vector3 v58(m_pThumbTopBone->mLocalXfm.v);
    v58.z -= scale;
    m_pThumbBottomBone->SetLocalPos(v58);
    MILO_ASSERT(m_pThumbGroup, 0x13E);
    if(m_fSavedScale < 1.0f) m_pThumbGroup->SetShowing(true);
    else m_pThumbGroup->SetShowing(false);
}

void ScrollbarDisplay::DrawShowing(){
    RndDir* pDir = mResource->Dir();
    MILO_ASSERT(pDir, 0x14E);
    UpdateSavedListInfo();
    UpdateScrollbarHeightAndPosition();
    UpdateThumbScaleAndPosition();
    if(mAlwaysShow || m_fSavedScale < 1.0f){
        pDir->SetWorldXfm(WorldXfm());
        pDir->Draw();
    }
}

void ScrollbarDisplay::Update(){
    UIComponent::Update();
    const DataArray* pTypeDef = TypeDef();
    MILO_ASSERT(pTypeDef, 0x163);
    RndDir* pDir = mResource->Dir();
    MILO_ASSERT(pDir, 0x166);
    m_pTopBone = pDir->Find<RndMesh>(pTypeDef->FindStr(top_bone), true);
    m_pBottomBone = pDir->Find<RndMesh>(pTypeDef->FindStr(bottom_bone), true);
    m_pThumbTopBone = pDir->Find<RndMesh>(pTypeDef->FindStr(thumb_top_bone), true);
    m_pThumbBottomBone = pDir->Find<RndMesh>(pTypeDef->FindStr(thumb_bottom_bone), true);
    MILO_ASSERT(m_pThumbTopBone, 0x171);
    MILO_ASSERT(m_pThumbBottomBone, 0x172);
    MILO_ASSERT(m_pTopBone, 0x173);
    MILO_ASSERT(m_pBottomBone, 0x174);
    m_pThumbGroup = pDir->Find<RndGroup>(pTypeDef->FindStr(thumb_group), true);
    MILO_ASSERT(m_pThumbGroup, 0x178);
}

void ScrollbarDisplay::SetList(BandList* blist){
    m_pList = blist;
    if(!m_pList) SetListAttached(false);
}

void ScrollbarDisplay::SetListAttached(bool b){
    BandList* blist = GetList();
    if(b && blist){
        SetTransParent(blist, false);
    }
    else {
        PanelDir* pDir = dynamic_cast<PanelDir*>(Dir());
        MILO_ASSERT(pDir, 0x197);
        SetTransParent(pDir, false);
    }
}

bool ScrollbarDisplay::GetListAttached() const {
    BandList* blist = GetList();
    RndTransformable* parent = TransParent();
    bool ret = false;
    if(blist){
        if(blist == parent) ret = true;
    }
    return ret;
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