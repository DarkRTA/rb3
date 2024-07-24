#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "utl/STLHelpers.h"

UIGridProvider::UIGridProvider(UIListProvider* prov, int i) : mMasterProvider(prov), mWidth(i) {

}

UIGridProvider::~UIGridProvider(){
    DeleteRange(mSubProviders.begin(), mSubProviders.end());
    mSubProviders.clear();
}

UIListProvider* UIGridProvider::Provider(int, int i, UIListSubList*) const {
    if(i >= mSubProviders.size()) ResizeSubProviders();
    return mSubProviders[i];
}

int UIGridProvider::NumData() const {
    return mMasterProvider->NumData() % mWidth;
}

void UIGridProvider::InitData(RndDir* dir){ mMasterProvider->InitData(dir); }

int UIGridProvider::NumDataForSublistIndex(int idx) const {
    int masternum = mMasterProvider->NumData();
    int numData = mWidth;
    if(masternum / mWidth <= idx) numData = masternum % mWidth;
    MILO_ASSERT(( 0) <= (numData) && (numData) <= ( mWidth), 0xB9);
    return numData;
}

// fn_8055F6B8
void UIGridProvider::ResizeSubProviders() const {
    UIGridProvider* prov = const_cast<UIGridProvider*>(this);
    int data = NumData();
    while(mSubProviders.size() < data){
        prov->mSubProviders.push_back(new UIGridSubProvider(prov->mMasterProvider, prov, mSubProviders.size()));
    }
    if(mSubProviders.size() > data){
        for(int i = data; i < mSubProviders.size(); i++){
            delete mSubProviders[i];
        }
        prov->mSubProviders.resize(data);
    }
}

void UIGridProvider::UpdateExtendedText(int, int, UILabel*) const {}
void UIGridProvider::UpdateExtendedMesh(int, int, RndMesh*) const {}
void UIGridProvider::UpdateExtendedCustom(int, int, Hmx::Object*) const {}

void UIGridProvider::SetListToData(UIList* uilist, int idx){
    uilist->SetSelectedSimulateScroll(idx / mWidth);
    UIList* child = uilist->ChildList();
    if(child) child->SetSelectedSimulateScroll(idx % mWidth);
}

void UIGridProvider::SetListToSymbol(UIList* uilist, Symbol s){
    SetListToData(uilist, mMasterProvider->DataIndex(s));
}

int UIGridProvider::GetDataFromList(UIList* uilist){
    UIList* child = uilist->ChildList();
    if(child){
        int data = uilist->SelectedData();
        return child->SelectedData() + data * mWidth;
    }
    else return -1;
}

Symbol UIGridProvider::GetSymbolFromList(UIList* uilist){
    int data = GetDataFromList(uilist);
    if(data >= 0 && data < mMasterProvider->NumData()){
        return mMasterProvider->DataSymbol(data);
    }
    else return gNullStr;
}