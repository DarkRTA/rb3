#include "ui/UIListProvider.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Locale.h"

void UIListProvider::Text(int, int, UIListLabel* listlabel, UILabel* label) const {
    if(TheLoadMgr.EditMode()){
        label->SetEditText(listlabel->GetDefaultText());
    }
    else {
        label->SetTextToken(gNullStr);
    }
}

RndMat* UIListProvider::Mat(int, int, UIListMesh* mesh) const {
    return mesh->DefaultMat();
}

void UIListProvider::UpdateExtendedText(int, int, UILabel* label) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended text without an override provider method. Label = %s", label->Name());
        label->SetTextToken(gNullStr);
    }
}

void UIListProvider::UpdateExtendedMesh(int, int, RndMesh* mesh) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended mesh without an override provider method. Mesh = %s", mesh->Name());
        mesh->SetMat(0);
    }
}

void UIListProvider::UpdateExtendedCustom(int, int, Hmx::Object* obj) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended custom object without an override provider method. object = %s", obj->Name());
    }
}

void DataProvider::Text(int i, int j, UIListLabel* listlabel, UILabel* label) const {
    DataNode& node = mData->Node(j + mOffset);
    if(node.Type() == kDataArray){
        if(!TheLoadMgr.EditMode() && unkd){
            Message msg("set_token_fmt", node);
            label->Handle(msg, false);
        }
        else if(TheLoadMgr.EditMode()){
            label->SetEditText(Localize(node.Array(0)->Sym(0), 0));
        }
        else {
            label->SetTextToken(node.Array(0)->Sym(0));
        }
    }
    else if(TheLoadMgr.EditMode()){
        label->SetEditText(Localize(node.ForceSym(0), 0));
    }
    else {
        label->SetTextToken(node.ForceSym(0));
    }
    if(mFluidWidth){
        float* curwidth = (float*)&mWidths[j];
        *curwidth = label->GetDrawWidth();
    }
}

void DataProvider::SetData(DataArray* arr){
    if(mData && mData){ // ???
        mData->Release();
        mData = 0;
    }
    mData = arr;
    mData->AddRef();
    if(mFluidWidth){
        mWidths.clear();
        mWidths.insert(mWidths.begin() + NumData(), 0.0f);
    }
}

void DataProvider::Disable(Symbol sym){
    std::list<Symbol>::iterator it = unk10.begin();
    for(; it != unk10.end(); it++){
        if(*it == sym) break;
    }
}