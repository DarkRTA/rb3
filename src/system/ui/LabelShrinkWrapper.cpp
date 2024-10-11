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

// fn_8054A614
void LabelShrinkWrapper::UpdateAndDrawWrapper(){
    MILO_ASSERT(m_pLabel, 0x62);
    Vector3 topleft, topright, bottomleft, bottomright;
    Vector3 vec1, vec2;
    float w = m_pLabel->GetDrawWidth();
    float h = m_pLabel->GetDrawHeight();
    m_pLabel->InqMinMaxFromWidthAndHeight(w, h, m_pLabel->Alignment(), vec1, vec2);
    float v1x = vec1.x;
    float v2x = vec2.x;
    float v2z = vec2.z;
    float v1z = vec1.z;
    SetWorldXfm(m_pLabel->WorldXfm());

    m_pTopLeftBone->SetLocalPos(v1x, 0.0f, v2z);
    m_pTopRightBone->SetLocalPos(v2x, 0.0f, v2z);
    m_pBottomLeftBone->SetLocalPos(v1x, 0.0f, v1z);
    m_pBottomRightBone->SetLocalPos(v2x, 0.0f, v1z);
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

// fn_8054A82C
void LabelShrinkWrapper::Update(){
    UIComponent::Update();
    const DataArray* pTypeDef = TypeDef();
    MILO_ASSERT(pTypeDef, 0xA3);
    RndDir* pDir = mResource->Dir();
    MILO_ASSERT(pDir, 0xA6);
    m_pTopLeftBone = pDir->Find<RndMesh>(pTypeDef->FindStr(topleft_bone), true);
    MILO_ASSERT(m_pTopLeftBone, 0xAE);
    m_pTopRightBone = pDir->Find<RndMesh>(pTypeDef->FindStr(topright_bone), true);
    MILO_ASSERT(m_pTopRightBone, 0xB0);
    m_pBottomLeftBone = pDir->Find<RndMesh>(pTypeDef->FindStr(bottomleft_bone), true);
    MILO_ASSERT(m_pBottomLeftBone, 0xB2);
    m_pBottomRightBone = pDir->Find<RndMesh>(pTypeDef->FindStr(bottomright_bone), true);
    MILO_ASSERT(m_pBottomRightBone, 0xB4);
}

void LabelShrinkWrapper::SetShouldShow(bool b){ m_pShow = b; }
void LabelShrinkWrapper::SetLabel(UILabel* l){ m_pLabel = l; }

BEGIN_HANDLERS(LabelShrinkWrapper)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xCC)
END_HANDLERS

BEGIN_PROPSYNCS(LabelShrinkWrapper)
    SYNC_PROP_SET(label, Label(), SetLabel(_val.Obj<UILabel>()))
    SYNC_PROP_SET(show, m_pShow, SetShouldShow(_val.Int()))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
