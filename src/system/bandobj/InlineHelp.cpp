#include "InlineHelp.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

INIT_REVS(InlineHelp)
float InlineHelp::sLastUpdatedTime;
float InlineHelp::sRotationTime;
float InlineHelp::sLabelRot;
bool InlineHelp::sHasFlippedTextThisRotation = 0;
bool InlineHelp::sNeedsTextUpdate = 0;
bool InlineHelp::sRotated = 0;

void InlineHelp::ActionElement::SetToken(Symbol s, bool secondary) {
    if (!secondary) {
        mPrimaryToken = s;
        mPrimaryStr = Localize(s, NULL);
    } else {
        mSecondaryToken = s;
        mSecondaryStr = Localize(s, NULL);
    }
}

void InlineHelp::ActionElement::SetString(const char* s, bool b) {
    if (!b) {
        mPrimaryToken = gNullStr;
        mPrimaryStr = s;
    } else {
        mSecondaryToken = gNullStr;
        mSecondaryStr = s;
    }
}

Symbol InlineHelp::ActionElement::GetToken(bool b) const {
    if (b) return mSecondaryToken;
    return mPrimaryToken;
}

const char* InlineHelp::ActionElement::GetText(bool b) const {
    if (b && HasSecondaryStr()) return mSecondaryStr.c_str();
    return mPrimaryStr.c_str();
}

void InlineHelp::ActionElement::SetConfig(DataNode& dn, bool b) {
    if (dn.Type() == kDataArray) {
        DataArray* da = dn.Array();
        if (da->Size() == 0) return;
        FormatString fs(Localize(da->Sym(0), NULL));
        for (int i = 1; i < da->Size(); i++) {
            DataNode& dn2 = da->Evaluate(i);
            if (dn2.Type() == kDataSymbol) {
                fs << Localize(dn2.Sym(), NULL);
            } else {
                fs << dn2;
            }
        }
        SetString(fs.Str(), b);
    } else {
        SetToken(dn.Sym(), b);
    }
}

void InlineHelp::Init() {
    Register();
    TheUI->InitResources("InlineHelp");
}

InlineHelp::InlineHelp() : mUseConnectedControllers(0), mHorizontal(1), mSpacing(0), unk_0x12C(0), mTextColor(this, NULL) { }

InlineHelp::~InlineHelp() {
    int siz = mTextLabels.size();
    for (int i = 0; i < siz; i++) {
        delete mTextLabels[i];
    }
}

BEGIN_COPYS(InlineHelp)
    CREATE_COPY_AS(InlineHelp, h)
    MILO_ASSERT(h, 129);
    COPY_SUPERCLASS_FROM(UIComponent, h)
    Update();
END_COPYS

void InlineHelp::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty) {
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(InlineHelp, h);
    MILO_ASSERT(h, 139);
    COPY_MEMBER_FROM(h, mHorizontal)
    COPY_MEMBER_FROM(h, mSpacing)
    COPY_MEMBER_FROM(h, mConfig)
    COPY_MEMBER_FROM(h, mTextColor)
    COPY_MEMBER_FROM(h, mUseConnectedControllers)
    UpdateIconTypes(false);
}

SAVE_OBJ(InlineHelp, 158)

BEGIN_LOADS(InlineHelp)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void InlineHelp::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    bs >> mHorizontal;
    bs >> mSpacing;
    bs >> mConfig;
    if (gRev >= 1) bs >> mTextColor;
    if (u16(gRev + 0xFFFE) <= 1) { int x; bs >> x; }
    if (gRev >= 3) {
        bs >> mUseConnectedControllers;
    }
    UIComponent::PreLoad(bs);
}

void InlineHelp::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

void InlineHelp::Enter(){
    UIComponent::Enter();
    UpdateIconTypes(true);
    SyncLabelsToConfig();
}

void InlineHelp::Poll(){
    UIComponent::Poll();
    float uisecs = TheTaskMgr.UISeconds();
    if(uisecs != sLastUpdatedTime){
        sNeedsTextUpdate = false;
        if(uisecs > sRotationTime){
            float f1 = uisecs - sRotationTime;
            if(f1 >= 1.0f){
                sHasFlippedTextThisRotation = false;
                sRotationTime = uisecs + 5.0f;
                SetLabelRotationPcts(0.0f);
            }
            else {
                if(!sHasFlippedTextThisRotation && f1 >= 0.5f){
                    sHasFlippedTextThisRotation = true;
                    sRotated = sRotated == 0;
                    sNeedsTextUpdate = true;
                }
                SetLabelRotationPcts(f1);
            }
        }
        sLastUpdatedTime = uisecs;
    }
    if(sNeedsTextUpdate) UpdateLabelText();
}

void InlineHelp::SetActionToken(JoypadAction a, DataNode& node){
    bool found = false;
    for(std::vector<ActionElement>::iterator it = mConfig.begin(); it != mConfig.end(); ++it){
        if((*it).mAction == a){
            (*it).SetConfig(node, false);
            found = true;
            break;
        }
    }
    if(!found){
        ActionElement el(a);
        el.SetConfig(node, false);
        mConfig.push_back(el);
    }
    SyncLabelsToConfig();
}

void InlineHelp::ClearActionToken(JoypadAction a){
    for(std::vector<ActionElement>::iterator it = mConfig.begin(); it != mConfig.end(); ++it){
        if((*it).mAction == a){
            mConfig.erase(it);
            SyncLabelsToConfig();
            return;
        }
    }
}

BinStream& operator>>(BinStream& bs, InlineHelp::ActionElement& ae) {
    { int x; bs >> x; ae.mAction = (JoypadAction)x; }
    Symbol s; bs >> s; ae.SetToken(s, false);
    if (InlineHelp::gRev >= 2)  { bs >> s; ae.SetToken(s, true); }
    return bs;
}

DataNode InlineHelp::OnSetConfig(const DataArray* da){
    mConfig.clear();
    DataArray* arr = da->Array(2);
    for(int i = 0; i < arr->Size(); i++){
        DataArray* loopArr = arr->Array(i);
        ActionElement el((JoypadAction)loopArr->Int(0));
        el.SetConfig(arr->Node(1), false);
        if(loopArr->Size() > 2) el.SetConfig(arr->Node(2), true);
        mConfig.push_back(el);
    }
    SyncLabelsToConfig();
    return DataNode(1);
}

void InlineHelp::UpdateTextColors(){
    for(std::vector<UILabel*>::iterator it = mTextLabels.begin(); it != mTextLabels.end(); ++it){
        (*it)->SetColorOverride(mTextColor);
    }
}

void InlineHelp::Update(){
    UIComponent::Update();
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0x187);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0x18A);
    unk_0x12C = dir->Find<BandLabel>(t->FindStr(text_label), true);
    SyncLabelsToConfig();
}

void InlineHelp::UpdateIconTypes(bool b){
    mIconTypes.clear();
    mIconTypes.push_back(vocals);
    mIconTypes.push_back(guitar);
    mIconTypes.push_back(drums);
    mIconTypes.push_back(keys);
}

void InlineHelp::SyncLabelsToConfig(){
    ResetRotation();
    int cfg_size = mConfig.size();
    int labels_size = mTextLabels.size();
    if(cfg_size > labels_size){
        for(; labels_size < cfg_size; labels_size++){
            BandLabel* lbl = Hmx::Object::New<BandLabel>();
            lbl->ResourceCopy(unk_0x12C);
            lbl->SetColorOverride(mTextColor);
            mTextLabels.push_back(lbl);
        }
    }
    else {
        if(labels_size > cfg_size){
            for(; cfg_size < labels_size; cfg_size++){
                delete mTextLabels[cfg_size];
            }
            mTextLabels.resize(cfg_size);
        }
    }
    UpdateLabelText();
}

String InlineHelp::GetIconStringFromAction(int idx){
    String ret;
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0x1C4);
    DataArray* actionArr = t->FindArray(action_chars, true);
    for(std::vector<Symbol>::iterator it = mIconTypes.begin(); it != mIconTypes.end(); ++it){
        const char* str = actionArr->FindArray(*it, true)->Str(idx + 1);
        char c = *str;
        if(ret.find(c) == String::npos) ret += c;
    }
    return ret;
}

void InlineHelp::ResetRotation(){
    sRotated = 0;
    sHasFlippedTextThisRotation = 0;
    sRotationTime = TheTaskMgr.UISeconds() + 5.0f;
    SetLabelRotationPcts(0.0f);
}

void InlineHelp::SetLabelRotationPcts(float f){
    if(f < 0.5f) sLabelRot = f * -240.0f;
    else sLabelRot = f * -240.0f - 120.0f;
}

void InlineHelp::UpdateLabelText(){
    int size = mConfig.size();
    for(int i = 0; i < size; i++){
        String icon = GetIconStringFromAction(mConfig[i].mAction);
        if(icon.empty()) mTextLabels[i]->SetTextToken(gNullStr);
        else mTextLabels[i]->SetTokenFmt(inline_help_fmt, icon.c_str(), mConfig[i].GetText(sRotated));
    }
}

BEGIN_HANDLERS(InlineHelp)
    HANDLE_ACTION(set_action_token, SetActionToken((JoypadAction)_msg->Int(2), _msg->Node(3)))
    HANDLE_ACTION(clear_action_token, ClearActionToken((JoypadAction)_msg->Int(2)))
    HANDLE(set_config, OnSetConfig)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x201)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(InlineHelp::ActionElement)
    SYNC_PROP(action, (int&)o.mAction)
    SYNC_PROP_SET(text_token, o.GetToken(false), o.SetToken(_val.Sym(), false))
    SYNC_PROP_SET(secondary_token, o.GetToken(true), o.SetToken(_val.Sym(), true))
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(InlineHelp)
    SYNC_PROP_MODIFY_ALT(config, mConfig, SyncLabelsToConfig())
    SYNC_PROP(horizontal, mHorizontal)
    SYNC_PROP(spacing, mSpacing)
    SYNC_PROP_MODIFY_ALT(text_color, mTextColor, UpdateTextColors())
    SYNC_PROP(use_connected_controllers, mUseConnectedControllers)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
