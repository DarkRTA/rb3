#include "ui/LabelShrinkWrapper.h"
#include "ui/UILabel.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(LabelShrinkWrapper)

void LabelShrinkWrapper::Init(){
    Register();
    TheUI->InitResources("LabelShrinkWrapper");
}

LabelShrinkWrapper::LabelShrinkWrapper() : m_pLabel(this, 0), m_pShow(0), m_pTopLeftBone(0), m_pTopRightBone(0), m_pBottomLeftBone(0), m_pBottomRightBone(0) {

}

LabelShrinkWrapper::~LabelShrinkWrapper(){

}

BEGIN_COPYS(LabelShrinkWrapper)
    CREATE_COPY_AS(LabelShrinkWrapper, p)
    MILO_ASSERT(p, 0x2F);
    COPY_MEMBER_FROM(p, m_pLabel)
    COPY_MEMBER_FROM(p, m_pShow)
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
    bs >> m_pLabel >> m_pShow;
    UIComponent::PreLoad(bs);
}

void LabelShrinkWrapper::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void LabelShrinkWrapper::UpdateAndDrawWrapper(){
    MILO_ASSERT(m_pLabel, 0x62);
}

void LabelShrinkWrapper::DrawShowing(){
    if(m_pLabel && m_pShow){
        RndDir* pDir = mResource->Dir();
        MILO_ASSERT(pDir, 0x8B);
        UpdateAndDrawWrapper();
        pDir->SetWorldXfm(WorldXfm());
        pDir->Draw();
    }
}

void LabelShrinkWrapper::Poll(){ UIComponent::Poll(); }

void LabelShrinkWrapper::Update(){
    UIComponent::Update();
    DataArray* pTypeDef = mTypeDef;
    MILO_ASSERT(pTypeDef, 0xA3);
    RndDir* pDir = mResource->Dir();
    MILO_ASSERT(pDir, 0xA6);
    m_pTopLeftBone = pDir->Find<RndMesh>(pTypeDef->FindStr(topleft_bone), false);
    MILO_ASSERT(m_pTopLeftBone, 0xAE);
    m_pTopRightBone = pDir->Find<RndMesh>(pTypeDef->FindStr(topright_bone), false);
    MILO_ASSERT(m_pTopRightBone, 0xB0);
    m_pBottomLeftBone = pDir->Find<RndMesh>(pTypeDef->FindStr(bottomleft_bone), false);
    MILO_ASSERT(m_pBottomLeftBone, 0xB2);
    m_pBottomRightBone = pDir->Find<RndMesh>(pTypeDef->FindStr(bottomright_bone), false);
    MILO_ASSERT(m_pBottomRightBone, 0xB4);
}

void LabelShrinkWrapper::SetShouldShow(bool b){ m_pShow = b; }
void LabelShrinkWrapper::SetLabel(UILabel* l){ m_pLabel = l; }

BEGIN_HANDLERS(LabelShrinkWrapper)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xCC)
END_HANDLERS

BEGIN_PROPSYNCS(LabelShrinkWrapper)
    SYNC_PROP_SET(label, (Hmx::Object*)m_pLabel, SetLabel(_val.Obj<UILabel>(0)))
    SYNC_PROP_SET(show, m_pShow, SetShouldShow(_val.Int(0)))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS